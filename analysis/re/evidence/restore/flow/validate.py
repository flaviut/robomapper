#!/usr/bin/env python3
"""Check identity, ELF-backed instruction bytes, even anchors and generated-C hashes."""
import hashlib
import json
from pathlib import Path
import struct
from discover import HERE, ROOT


def elf_offset(data, va, size):
    assert data[:6] == b'\x7fELF\x01\x01'
    ph = struct.unpack_from('<I', data, 28)[0]
    width, count = struct.unpack_from('<HH', data, 42)
    offsets = []
    for i in range(count):
        kind, off, start, _, filesz, _, flags, _ = struct.unpack_from('<8I', data, ph + i * width)
        if kind == 1 and flags & 1 and start <= va and va + size <= start + filesz:
            offsets.append(off + va - start)
    assert len(offsets) == 1, (hex(va), size, offsets)
    return offsets[0]


def sections(data):
    shoff = struct.unpack_from('<I', data, 32)[0]
    width, count, names = struct.unpack_from('<HHH', data, 46)
    rows = [struct.unpack_from('<10I', data, shoff + i * width) for i in range(count)]
    strings = data[rows[names][4]:rows[names][4] + rows[names][5]]
    return {strings[r[0]:].split(b'\0', 1)[0].decode(): r for r in rows}


def entry_boundary_proofs(binaries, records):
    proofs = []
    for program in ('RoboController', 'libroboipc.so'):
        data = binaries[program]
        ss = sections(data)
        for f in (f for f in records if f['program'] == program):
            entry = int(f['address'], 16)
            row = {'program': program, 'sha256': f['sha256'], 'entry': f['address']}
            if program == 'RoboController':
                section = ss['.ARM.exidx']
                entries = []
                for off in range(0, section[5], 8):
                    word = struct.unpack_from('<I', data, section[4] + off)[0] & 0x7fffffff
                    displacement = word - (1 << 31) if word & (1 << 30) else word
                    entries.append((section[3] + off + displacement, section[3] + off, word))
                i = next(i for i, x in enumerate(entries) if x[0] == entry)
                row.update(kind='exact ELF EHABI start', table_va=hex(entries[i][1]),
                           prel31_word=hex(entries[i][2]), next_start=hex(entries[i+1][0]))
            else:
                dyn = ss['.dynsym']
                names = ss['.dynstr']
                strings = data[names[4]:names[4] + names[5]]
                matches = []
                for off in range(0, dyn[5], dyn[9]):
                    name, value, size, info, _, _ = struct.unpack_from('<IIIBBH', data, dyn[4] + off)
                    if info & 15 == 2 and value & ~1 == entry:
                        matches.append({'symbol': strings[name:].split(b'\0', 1)[0].decode(),
                                        'symbol_value': hex(value), 'symbol_size': size})
                assert len(matches) == 1
                row.update(kind='surviving ELF dynamic FUNC symbol; Thumb bit separate', **matches[0])
            proofs.append(row)
    return proofs


def check_instruction(data, row):
    va, raw = int(row['address'], 16), bytes.fromhex(row['bytes'])
    assert va % 2 == 0, row
    off = elf_offset(data, va, len(raw))
    assert data[off:off + len(raw)] == raw, row


def validate():
    manifest = json.loads((ROOT / 'binaries/4.3.5_1612/manifest.json').read_text())
    inputs = {Path(b['path']).name: b for b in manifest['files'] if b.get('kind') == 'elf'}
    records = json.loads((HERE / 'instructions.json').read_text())
    binaries, n = {}, 0
    for f in records:
        name = f['program']
        if name not in binaries:
            meta = inputs[name]
            data = (ROOT / 'binaries/4.3.5_1612' / meta['path']).read_bytes()
            assert hashlib.sha256(data).hexdigest() == meta['sha256'] == f['sha256']
            binaries[name] = data
        assert f['sha256'] == inputs[name]['sha256']
        assert int(f['address'], 16) % 2 == 0
        raw = (HERE / f['c_file']).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == f['c_sha256']
        assert b'Decompiled C, NOT recovered source; need not compile.' in raw
        assert f['sha256'].encode() in raw and f['address'].encode() in raw
        for row in f['instructions']:
            check_instruction(binaries[name], row)
            n += 1
    proofs = entry_boundary_proofs(binaries, records)
    assert json.loads((HERE / 'entry-boundaries.json').read_text()) == proofs
    by_entry = {(f['program'], f['address']): {i['address']: i for i in f['instructions']} for f in records}
    required = [
        ('libroboipc.so', '0x0000637c', '0x00006388', 'ubfx r3,r6,#0x10,#0x8'),
        ('libroboipc.so', '0x0000637c', '0x00006390', 'add.w r3,r3,r3, lsl #0x4'),
        ('libroboipc.so', '0x0000637c', '0x00006398', 'add.w r0,r3,r6, lsr #0x18'),
        ('libroboipc.so', '0x0000637c', '0x0000637e', 'movs r2,#0x4c'),
        ('RoboController', '0x00030958', '0x00030970', 'strd r2,r3,[r5,#0x3a0]!'),
        ('RoboController', '0x00030958', '0x00030986', 'movs r3,#0x3c'),
        ('RoboController', '0x00026288', '0x000263b8', 'movs r2,#0x1b'),
        ('RoboController', '0x00026288', '0x000263bc', 'movt r2,#0x201'),
        ('RoboController', '0x00023768', '0x00023b88', 'cmp r3,#0x10'),
        ('RoboController', '0x00023768', '0x00024068', 'movw r12,#0x836'),
        ('RoboController', '0x000367ac', '0x000373a4', 'ldrd r0,r1,[r8,#0x3a0]!'),
        ('RoboController', '0x000367ac', '0x000373ae', 'bne.w 0x00036ece'),
        ('RoboController', '0x000367ac', '0x000373f6', 'bl 0x0002cae8'),
        ('RoboController', '0x000367ac', '0x00037402', 'cmp.w r9,#0x1'),
    ]
    for program, entry, va, text in required:
        assert by_entry[program, entry][va]['instruction'] == text, (program, va)
    return {'status': 'passed', 'binary_hashes': len(binaries), 'functions': len(records),
            'instruction_byte_checks': n, 'claim_anchor_checks': len(required),
            'independent_elf_entry_boundary_checks': len(proofs),
            'scope': 'Static byte/ELF/C consistency and exact claim anchors, not runtime behavior.'}


if __name__ == '__main__':
    print(json.dumps(validate(), indent=2))
