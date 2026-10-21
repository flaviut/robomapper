#!/usr/bin/env python3
"""Validate recorded static evidence against original ELF; never execute firmware."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def require(value, message):
    if not value:
        raise ValueError(message)


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def elf_loads(data):
    require(data[:6] == b'\x7fELF\x01\x01', 'ELF32 little endian required')
    offset = struct.unpack_from('<I', data, 28)[0]
    size, count = struct.unpack_from('<HH', data, 42)
    require(size == 32, 'ELF program header size')
    return [p for i in range(count)
            if (p := struct.unpack_from('<IIIIIIII', data, offset + i * size))[0] == 1]


def file_offset(loads, address, length):
    matches = [p for p in loads if p[2] <= address and address + length <= p[2] + p[4]]
    require(len(matches) == 1 and matches[0][6] & 1, 'unique executable file-backed mapping')
    return matches[0][1] + address - matches[0][2]


def check(root=ROOT, exports=HERE / 'exports'):
    evidence = json.loads((HERE / 'evidence.json').read_text())
    counts = {'binaries': 0, 'functions': 0, 'instructions': 0, 'anchors': 0}
    for binary in evidence['binaries']:
        program = binary['program']
        data = (root / binary['tracked_input']).read_bytes()
        require(hashlib.sha256(data).hexdigest() == binary['sha256'], 'binary identity')
        loads = elf_loads(data)
        dest = exports / program
        require(digest(dest / 'selected.json') == binary['selected_sha256'], 'selected identity')
        require(digest(dest / 'entries.json') == binary['entries_sha256'], 'entry inventory identity')
        selected = json.loads((dest / 'selected.json').read_text())
        entries = {f['address']: f for f in json.loads((dest / 'entries.json').read_text())}
        require([f['address'] for f in selected] == binary['selected_entries'], 'selected entry set')
        instructions = {}
        for f in selected:
            require(all(f[k] == v for k, v in entries[f['address']].items()), 'surviving baseline metadata')
            a = int(f['address'], 16)
            require(a % 2 == 0, 'even entry')
            require(f['entry_file_offsets'] == [file_offset(loads, a, 1)], 'entry mapping')
            require(f['instructions'][0]['address'] == f['address'], 'entry starts instruction stream')
            c = dest / (f['address'] + '.c')
            require(digest(c) == binary['c_sha256'][f['address']], 'C identity')
            require(c.read_bytes().startswith(b'/* Decompiled C, NOT recovered source; need not compile.'), 'C disclaimer')
            for ins in f['instructions']:
                a = int(ins['address'], 16)
                raw = bytes.fromhex(ins['bytes'])
                require(a % 2 == 0 and len(raw) in (2, 4), 'instruction alignment/length')
                offset = file_offset(loads, a, len(raw))
                require(data[offset:offset + len(raw)] == raw, 'original instruction bytes')
                instructions[ins['address']] = ins
                counts['instructions'] += 1
            counts['functions'] += 1
        for group in evidence['instruction_groups']:
            if group['program'] == program:
                require(bool(group['instructions']), 'nonempty claim anchors')
                for ins in group['instructions']:
                    require(instructions[ins['address']] == ins, 'claim instruction anchor')
                    counts['anchors'] += 1
        for record in evidence.get('data_records', []):
            if record['program'] == program:
                raw = bytes.fromhex(record['bytes'])
                offset = file_offset(loads, int(record['address'], 16), len(raw))
                require(offset == record['file_offset'], 'literal mapping')
                require(data[offset:offset + len(raw)] == raw, 'literal bytes')
                require(struct.unpack('<f', raw)[0] == record['float32'], 'literal interpretation')
        counts['binaries'] += 1
    return counts


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, default=ROOT)
    p.add_argument('--exports', type=Path, default=HERE / 'exports')
    a = p.parse_args()
    print(json.dumps({'status': 'ok', 'counts': check(a.root, a.exports),
                      'limit': 'Identity, baseline metadata and bytes only; not semantic/runtime safety.'}, indent=2))
