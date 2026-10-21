#!/usr/bin/env python3
"""Check bounded static artifacts against original ELF; never execute firmware."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def load(path):
    return json.loads(Path(path).read_text())


def file_offset(data, va, size):
    if data[:6] != b'\x7fELF\x01\x01' or size <= 0 or va < 0:
        raise ValueError('Expected ELF32 little endian and positive range')
    phoff = struct.unpack_from('<I', data, 28)[0]
    entsize, count = struct.unpack_from('<HH', data, 42)
    if entsize < 32:
        raise ValueError('Invalid program header size')
    hits = []
    for n in range(count):
        kind, off, addr, _, filesz, _, _, _ = struct.unpack_from(
            '<IIIIIIII', data, phoff + n * entsize)
        if kind == 1 and addr <= va and va + size <= addr + filesz:
            if off + va - addr + size > len(data):
                raise ValueError('Truncated segment')
            hits.append(off + va - addr)
    if len(hits) != 1:
        raise ValueError('No unique file-backed PT_LOAD')
    return hits[0]


def verify_instructions(data, functions):
    count = 0
    for f in functions:
        entry = int(f['address'], 16)
        if entry & 1 or f['entry_file_offsets'] != [file_offset(data, entry, 1)]:
            raise ValueError('Entry address/mapping mismatch')
        seen = set()
        for ins in f['instructions']:
            va, raw = int(ins['address'], 16), bytes.fromhex(ins['bytes'])
            if va & 1 or va in seen or not raw:
                raise ValueError('Invalid instruction address/bytes')
            seen.add(va)
            off = file_offset(data, va, len(raw))
            if data[off:off + len(raw)] != raw:
                raise ValueError('Instruction bytes differ')
            count += 1
        if entry not in seen:
            raise ValueError('Missing entry instruction')
    return count


def validate(exports=HERE / 'focused', reopened=None):
    evidence = load(HERE / 'evidence.json')
    counts = {}
    for program in evidence['programs']:
        name = program['name']
        data = (ROOT / program['input']).read_bytes()
        assert hashlib.sha256(data).hexdigest() == program['sha256']
        selected = load(exports / name / 'selected.json')
        assert [f['address'] for f in selected] == program['entries']
        counts[name] = verify_instructions(data, selected)
        for filename, digest in program['export_sha256'].items():
            actual = exports / name / filename
            if filename == 'types.json':
                assert load(actual) == load(HERE / 'focused' / name / filename)
                assert hashlib.sha256((HERE / 'focused' / name / filename).read_bytes()).hexdigest() == digest
            else:
                assert hashlib.sha256(actual.read_bytes()).hexdigest() == digest, actual
            if filename.endswith('.c'):
                assert 'Decompiled C, NOT recovered source' in actual.read_text()
                assert program['sha256'] in actual.read_text()
            if reopened:
                other = reopened / name / filename
                if filename == 'types.json':
                    assert load(actual) == load(other)
                else:
                    assert actual.read_bytes() == other.read_bytes()
        for literal in program['literals']:
            expected = literal['text'].encode() + b'\0'
            va = int(literal['va'], 16)
            off = file_offset(data, va, len(expected))
            assert data[off:off + len(expected)] == expected
            if 'pointer_va' in literal:
                ptr = struct.unpack_from('<I', data, file_offset(data, int(literal['pointer_va'], 16), 4))[0]
                assert ptr == va
            if 'pool_va' in literal:
                rel = struct.unpack_from('<I', data, file_offset(data, int(literal['pool_va'], 16), 4))[0]
                assert (rel + int(literal['pc_base'], 16)) & 0xffffffff == va
    for bounded in evidence['bounded_ELF_ranges']:
        program = next(p for p in evidence['programs'] if p['name'] == bounded['program'])
        data = (ROOT / program['input']).read_bytes()
        raw = bytes.fromhex(bounded['bytes'])
        va = int(bounded['va'], 16)
        off = file_offset(data, va, len(raw))
        assert off == bounded['file_offset']
        assert data[off:off + len(raw)] == raw
        # This bounded record is an existing Thumb unconditional branch, not an entry guess.
        word = int.from_bytes(raw, 'little')
        assert len(raw) == 2 and word & 0xf800 == 0xe000
        displacement = (word & 0x7ff) * 2
        if displacement & 0x800:
            displacement -= 0x1000
        assert va + 4 + displacement == 0xe06e0
    # Anchor references must be actual exported instructions, not invented addresses.
    for claim in evidence['claims']:
        for anchor in claim['anchors']:
            fs = load(exports / anchor['program'] / 'selected.json')
            f = next(f for f in fs if f['address'] == anchor['entry'])
            ins = {i['address']: i for i in f['instructions']}
            for va in anchor['instructions']:
                assert va in ins, (claim['id'], va)
    return {'status': 'passed', 'instructions_verified_against_original_ELF': counts,
            'functions': sum(len(p['entries']) for p in evidence['programs']),
            'literals': sum(len(p['literals']) for p in evidence['programs']),
            'reopened': 'passed' if reopened else 'not requested',
            'limits': 'Byte/replay identity and explicit anchors only; not semantic correctness, runtime existence, coherent snapshot or durability.'}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exports', type=Path, default=HERE / 'focused')
    parser.add_argument('--reopened', type=Path)
    parser.add_argument('--out', type=Path)
    args = parser.parse_args()
    text = json.dumps(validate(args.exports, args.reopened), indent=2) + '\n'
    if args.out:
        args.out.write_text(text)
    print(text, end='')
