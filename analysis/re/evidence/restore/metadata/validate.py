#!/usr/bin/env python3
"""Check hash/ELF-byte provenance and focused dependency invariants; no firmware runs."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def check(root, exports):
    evidence = json.loads((HERE / 'evidence.json').read_text())
    counts = {'binaries': 0, 'functions': 0, 'instructions': 0, 'claim_anchors': 0}
    for identity in evidence['binaries']:
        program = identity['program']
        data = (root / identity['tracked_input']).read_bytes()
        assert hashlib.sha256(data).hexdigest() == identity['sha256']
        assert data[:6] == b'\x7fELF\x01\x01'
        phoff = struct.unpack_from('<I', data, 28)[0]
        entsize, n = struct.unpack_from('<HH', data, 42)
        loads = [struct.unpack_from('<IIIIIIII', data, phoff + i * entsize)
                 for i in range(n)]
        loads = [p for p in loads if p[0] == 1]
        assert min(p[2] for p in loads) == 0
        selected = json.loads((exports / program / 'selected.json').read_text())
        assert [f['address'] for f in selected] == identity['selected_entries']
        instructions = {}
        for function in selected:
            address = int(function['address'], 16)
            assert address % 2 == 0 and function['thumb_mode'] == 1
            maps = [p for p in loads if p[2] <= address < p[2] + p[4]]
            assert len(maps) == 1
            assert function['entry_file_offsets'] == [maps[0][1] + address - maps[0][2]]
            c = (exports / program / (function['address'] + '.c')).read_bytes()
            assert c.startswith(b'/* Decompiled C, NOT recovered source; need not compile.')
            assert identity['sha256'].encode() in c[:300]
            assert hashlib.sha256(c).hexdigest() == identity['c_sha256'][function['address']]
            for instruction in function['instructions']:
                a = int(instruction['address'], 16)
                raw = bytes.fromhex(instruction['bytes'])
                maps = [p for p in loads if p[2] <= a and a + len(raw) <= p[2] + p[4]]
                assert a % 2 == 0 and len(maps) == 1 and maps[0][6] & 1
                offset = maps[0][1] + a - maps[0][2]
                assert data[offset:offset + len(raw)] == raw, instruction
                instructions[instruction['address']] = instruction
                counts['instructions'] += 1
            counts['functions'] += 1
        for group in evidence['instruction_groups']:
            if group['program'] != program:
                continue
            for instruction in group['instructions']:
                assert instructions[instruction['address']] == instruction
                counts['claim_anchors'] += 1
        counts['binaries'] += 1
    # The byte intervals are half-open. Neither setter includes mappings or restrictions.
    full = (0x31da0, 0x31da0 + 0x1001a4)
    grid = (0x31da4, 0x31da4 + 0x10000c)
    assert full[1] == 0x131f44 and grid[1] == 0x131db0
    assert full[0] + 0x100010 == grid[1]
    assert full[1] - grid[1] == 404
    assert 0x131fac >= full[1] and 0x13e9f0 >= full[1]
    assert 0x318e8 < full[0] and 0x31c0c < full[0] and 0x132330 >= full[1]
    # Demonstrate why equality of dimensions and/or checksum cannot establish ID stability:
    # low six bits are conditional IDs; upper bits are not room numbers.
    assert ((0x50 & 0x3f) == 16) and 0x50 != 16
    print(json.dumps({'status': 'ok', 'counts': counts,
                      'limits': 'Identity/bytes, interval arithmetic and recorded anchors only; '
                                'not algorithm execution or runtime safety validation.'}, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    parser.add_argument('--exports', type=Path, default=HERE / 'exports')
    args = parser.parse_args()
    check(args.root, args.exports)


if __name__ == '__main__':
    main()
