#!/usr/bin/env python3
"""Check hash-bound recorded instructions/EHABI, export hashes and candidate-screen reproducibility.
Does not execute original firmware. Ghidra creation/CFG/reopen/rollback checks are in replay.py.
"""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def load(path):
    return json.loads(path.read_text())


def digest(data):
    return hashlib.sha256(data).hexdigest()


class Elf:
    def __init__(self, path):
        self.data = path.read_bytes()
        assert self.data[:6] == b'\x7fELF\x01\x01'
        off = struct.unpack_from('<I', self.data, 28)[0]
        size, count = struct.unpack_from('<HH', self.data, 42)
        self.loads = [struct.unpack_from('<IIIIIIII', self.data, off + i * size)
                      for i in range(count)]

    def at(self, address, count):
        matches = [p for p in self.loads if p[0] == 1 and p[2] <= address
                   and address + count <= p[2] + p[4]]
        assert len(matches) == 1, hex(address)
        p = matches[0]
        offset = p[1] + address - p[2]
        return self.data[offset:offset + count]

    def prel31(self, address):
        word = struct.unpack('<I', self.at(address, 4))[0] & 0x7fffffff
        return address + (word - 0x80000000 if word & 0x40000000 else word)


def validate(saved_rootfs=None):
    checked = 0
    manifest = load(ROOT / 'analysis/re/manifest.json')['binaries']
    binaries = {Path(b['path']).name: b for b in manifest}
    elf = {}
    for name, b in binaries.items():
        elf[name] = Elf(ROOT / b['path'])
        assert digest(elf[name].data) == b['sha256']
    request = load(HERE / 'request.json')
    wd = elf['WatchDoge']
    entry, end = int(request['entry'], 16), int(request['bound_end'], 16)
    assert entry % 2 == 0 and end == 0x1ac07
    assert wd.at(entry, end - entry + 1).hex() == request['bound_bytes']
    assert wd.at(entry, 12).hex() == request['entry_bytes']
    table = int(request['unwind']['table_va'], 16)
    assert wd.prel31(table) == entry
    assert wd.prel31(table + 8) == int(request['unwind']['next_entry'], 16)
    assert wd.prel31(table + 8) == 0x1ac20 > 0x1ac08 > end
    ins = request['instructions']
    assert len(ins) == 19
    assert [(i['address'], i['instruction']) for i in ins if i['instruction'].startswith('blx ')] == [
        ('0x1abea', 'blx 0x00013850'), ('0x1abf4', 'blx 0x00013ab8'),
        ('0x1ac04', 'blx 0x0001376c')]
    rows = load(HERE / 'proof/selected.json')
    for row in rows:
        assert int(row['address'], 16) % 2 == 0
        assert 'Decompiled C, NOT recovered source' in (HERE / 'proof' / row['c_file']).read_text()
        for i in row['instructions']:
            assert wd.at(int(i['address'], 16), len(bytes.fromhex(i['bytes']))).hex() == i['bytes']
            checked += 1
    helper = next(r for r in rows if int(r['address'], 16) == entry)
    assert [(int(i['address'], 16), i['bytes'], i['instruction']) for i in helper['instructions']] == [
        (int(i['address'], 16), i['bytes'], i['instruction']) for i in ins]
    for record in load(HERE / 'instruction-clips.json')['records']:
        name = record['program']
        assert record['sha256'] == binaries[name]['sha256']
        source = load(ROOT / record['source'])
        function = next(f for f in source if f['address'] == record['entry'])
        assert record['name'] == function['name']
        for i in record['instructions']:
            assert i in function['instructions']
            assert elf[name].at(int(i['address'], 16), len(bytes.fromhex(i['bytes']))).hex() == i['bytes']
            checked += 1
    proof = load(HERE / 'proof/validation.json')
    assert proof['status'] == 'passed' and proof['reopen_byte_identical']
    assert proof['recovery']['no_existing_function_change'] and proof['recovery']['byte_identity']
    assert proof['rejection']['rejection_no_semantic_mutation']
    for relative, expected in proof['source_sha256'].items():
        assert digest((HERE / relative).read_bytes()) == expected
    lead = load(HERE / 'loader-lead.json')
    data = (ROOT / lead['binary_path']).read_bytes()
    assert digest(data) == lead['sha256']
    for record in lead['selected_string_records']:
        offset = int(record['file_offset'], 16)
        assert data[offset:offset + len(record['text']) + 1] == record['text'].encode() + b'\0'
    for address, expected in proof['c_sha256'].items():
        assert digest((HERE / 'proof' / ('0x%08x.c' % int(address, 16))).read_bytes()) == expected
    spec = importlib.util.spec_from_file_location('inventory', HERE / 'inventory.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    candidates = module.screen()
    assert candidates == load(HERE / 'writer-candidates.json')
    graph = load(HERE / 'graph.json')
    ids = {n['id'] for n in graph['nodes']}
    assert all(e['from'] in ids and e['to'] in ids for e in graph['edges'])
    assert graph['deployment'].startswith('blocked')
    configs = 0
    if saved_rootfs:
        for record in load(HERE / 'configuration.json')['records']:
            if record['saved_path'].startswith('analysis/'):
                continue  # local customization is deliberately not republished
            path = saved_rootfs / record['saved_path']
            assert digest(path.read_bytes()) == record['sha256']
            lines = path.read_text().splitlines()
            for excerpt in record['excerpts']:
                assert lines[excerpt['line'] - 1] == excerpt['text']
            configs += 1
    result = {'status': 'passed', 'instruction_records_checked': checked,
              'saved_config_files_checked': configs,
              'candidate_elf_paths_screened': candidates['screened_tracked_elf_paths'],
              'checks': ['tracked binary SHA256', 'PT_LOAD-backed instruction bytes',
                         'exact EHABI start and next ceiling', '19-instruction helper match',
                         'full saved helper export', 'all focused C hashes',
                         'candidate screen reproduced', 'graph node references',
                         'Ghidra evidence byte/function identity and rollback flags'],
              'limits': ['No runtime process/driver/MCU, writer exit, durability or restore validation.']}
    print(json.dumps(result, indent=2))
    return result


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--saved-rootfs', type=Path)
    p.add_argument('--out', type=Path)
    args = p.parse_args()
    result = validate(args.saved_rootfs)
    if args.out:
        args.out.write_text(json.dumps(result, indent=2) + '\n')
