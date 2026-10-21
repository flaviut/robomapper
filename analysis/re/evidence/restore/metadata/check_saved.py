#!/usr/bin/env python3
"""Read-only aggregate checks of private captures. Never writes decoded payloads.

Field numbers follow the robopersist.proto descriptor embedded in the hash-pinned
librobopersist.so (see evidence.json); this is not a general persistence decoder.
The saved encrypt flag is not used as a decoder selector (existing P07 evidence).
Application IMAGE interpretation is a saved-data hypothesis checked by equality,
not independently recovered application-message firmware semantics.
"""
import argparse
import gzip
import hashlib
import json
from pathlib import Path
import sqlite3
import struct
import zlib


def varint(data, pos):
    value = 0
    for shift in range(0, 70, 7):
        byte = data[pos]
        pos += 1
        value |= (byte & 127) << shift
        if byte < 128:
            return value, pos
    raise ValueError('overlong varint')


def fields(data):
    pos = 0
    while pos < len(data):
        tag, pos = varint(data, pos)
        number, wire = tag >> 3, tag & 7
        if wire == 0:
            value, pos = varint(data, pos)
        elif wire == 2:
            size, pos = varint(data, pos)
            value = data[pos:pos + size]
            assert len(value) == size
            pos += size
        else:
            raise ValueError(f'unexpected wire type {wire}')
        yield number, value


def region5(path):
    regions = []
    for number, value in fields(path.read_bytes()):
        if number != 20:
            continue
        values = list(fields(value))
        scalar = {n: v for n, v in values if n != 50}
        if scalar.get(10, 0) != 5:
            continue
        # These captures set encrypt=1 but store ordinary zlib streams; test
        # decoding directly, as the existing persistence path ignores that flag.
        parts = [zlib.decompress(v) if scalar.get(20, 0) else v
                 for n, v in values if n == 50]
        payload = b''.join(parts)
        assert len(payload) == scalar[40] == 0x13f120
        regions.append(payload)
    assert len(regions) == 1
    return regions[0]


def check_capture(archive, flag, app_id, db):
    r5 = region5(archive / f'PersistData_{flag}.data')
    s = 0x31da0
    width, height = struct.unpack_from('<ii', r5, s + 8)
    assert (width, height) == (1024, 1024)
    assert r5[s] == r5[s + 4] == 1
    cells = r5[s + 16:s + 16 + width * height]
    ids = {v & 0x3f for v in cells} - {0}
    count = struct.unpack_from('<I', r5, 0x131fac)[0]
    assert count <= 32
    mapping_ids = [struct.unpack_from('<I', r5, 0x131fb0 + i * 28 + 24)[0]
                   for i in range(count)]
    assert len(set(mapping_ids)) == count
    assert ids == set(mapping_ids), 'captured grid and default mapping IDs differ'

    native = (archive / f'user_map{app_id}').read_bytes()
    magic, version, hdr_size, scale, left, top, w, h = struct.unpack_from('<6sHHIiiII', native)
    assert (magic, version, hdr_size, scale) == (b'RRSLAM', 2, 20, 20)
    assert len(native) == 30 + w * h + 16
    assert hashlib.md5(native[30:-16]).digest() == native[-16:]

    rows = db.execute('SELECT map FROM bakmaps WHERE id=?', (app_id,)).fetchall()
    assert len(rows) == 1
    app = gzip.decompress(rows[0][0])
    assert app[:2] == b'rr'
    pos = struct.unpack_from('<H', app, 2)[0]
    images = []
    while pos + 8 <= len(app):
        block_type, header_size, data_size = struct.unpack_from('<HHI', app, pos)
        assert header_size >= 8
        end = pos + header_size + data_size
        assert end <= len(app)
        if block_type == 2:
            assert header_size == 28
            _, app_top, app_left, app_h, app_w = struct.unpack_from('<IiiII', app, pos + 8)
            assert (app_w, app_h) == (w, h)
            assert (app_left, app_top) == (left + 512, top + 512)
            assert data_size == w * h
            assert 0 <= app_left <= width - w and 0 <= app_top <= height - h
            pixels = app[pos + header_size:end]
            matches = sum((pixels[y * w + x] >> 3) ==
                          (cells[(y + app_top) * width + x + app_left] & 0x3f)
                          for y in range(h) for x in range(w))
            assert matches == w * h
            images.append(matches)
        pos = end
    assert len(images) == 1
    # No names, coordinates, restrictions or cell payloads are emitted.
    return {'flag': flag, 'application_id': app_id, 'image_cells_matched': images[0],
            'mapping_count': count, 'all_nonzero_ids_have_default_mappings': True,
            'ids_in_conditional_reuse_range_16_to_31': all(16 <= v <= 31 for v in ids),
            'segmentation_tail_nonzero_bytes': sum(v != 0 for v in r5[s + 0x100010:s + 0x1001a4]),
            'upper_cell_bits_present': sorted({v & 0xc0 for v in cells}),
            'native_digest_valid': True, 'application_origin_shift_matches': True}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--analysis-root', type=Path, required=True)
    args = parser.parse_args()
    archive = args.analysis_root / 'archive/mnt/data/rockrobo'
    db = sqlite3.connect((archive / 'robot.db').resolve().as_uri() + '?mode=ro', uri=True)
    try:
        result = [check_capture(archive, f, a, db) for f, a in [(2, 0), (6, 4)]]
    finally:
        db.close()
    print(json.dumps({'status': 'ok', 'scope': 'two private captured pairs; no firmware execution',
                      'checks': result}, indent=2))


if __name__ == '__main__':
    main()
