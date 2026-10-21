#!/usr/bin/env python3
"""Inspect or repack fixed-frame RRSLAM v2 grids offline."""

import argparse
import hashlib
import json
from pathlib import Path
import struct

HEADER = struct.Struct('<6sHHIiiII')


def load_map(path):
    data = path.read_bytes()
    if len(data) < HEADER.size + 16:
        raise ValueError('Truncated map')

    magic, version, size, scale, left, top, width, height = HEADER.unpack_from(data)
    if (magic, version, size, scale) != (b'RRSLAM', 2, 20, 20):
        raise ValueError('Unsupported map header')

    if not width or not height or len(data) != HEADER.size + width * height + 16:
        raise ValueError('Invalid map dimensions')

    pixels = data[HEADER.size:-16]
    if hashlib.md5(pixels).digest() != data[-16:]:
        raise ValueError('Grid checksum mismatch')

    return data[:HEADER.size], pixels, {
        'version': version, 'viewHeaderBytes': size, 'scale': scale,
        'left': left, 'top': top, 'width': width, 'height': height,
        'gridMD5': data[-16:].hex(), 'fileSHA256': hashlib.sha256(data).hexdigest()
    }


def load_pgm(path, width, height):
    data = path.read_bytes()
    pos = 0
    tokens = []

    # Read only the header: whitespace can also be a legitimate first pixel.
    while len(tokens) < 4:
        if pos >= len(data):
            raise ValueError('Truncated PGM header')
        if data[pos:pos + 1] == b'#':
            end = data.find(b'\n', pos)
            if end < 0:
                raise ValueError('Unterminated PGM comment')
            pos = end + 1
            continue
        if data[pos] in b' \t\r\n':
            pos += 1
            continue

        end = pos
        while end < len(data) and data[end] not in b' \t\r\n':
            end += 1
        tokens.append(data[pos:end])
        pos = end

    if tokens != [b'P5', str(width).encode(), str(height).encode(), b'255']:
        raise ValueError('Expected same-size 8-bit binary PGM')
    if pos >= len(data) or data[pos] not in b' \t\r\n':
        raise ValueError('Missing PGM raster separator')

    pos += 2 if data[pos:pos + 2] == b'\r\n' else 1
    pixels = data[pos:]
    if len(pixels) != width * height:
        raise ValueError('Invalid PGM raster size')
    return pixels


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=['inspect', 'export', 'pack'])
    parser.add_argument('map', type=Path)
    parser.add_argument('paths', nargs='*', type=Path)
    args = parser.parse_args()
    expected = {'inspect': 0, 'export': 1, 'pack': 2}[args.mode]
    if len(args.paths) != expected:
        parser.error('inspect MAP | export MAP OUT.pgm | pack MAP EDITED.pgm OUT.map')

    header, pixels, info = load_map(args.map)
    if args.mode == 'inspect':
        print(json.dumps(info, indent=2))
        return

    width, height = info['width'], info['height']
    if args.mode == 'export':
        result = f'P5\n{width} {height}\n255\n'.encode() + pixels
    else:
        pixels = load_pgm(args.paths[0], width, height)
        result = header + pixels + hashlib.md5(pixels).digest()

    # Require a new destination so a typo cannot overwrite an existing map.
    with args.paths[-1].open('xb') as target:
        target.write(result)


if __name__ == '__main__':
    main()
