#!/usr/bin/env python3
"""Replay this bounded static slice into fresh ignored lane-local scratch."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from discover import HERE, ROOT, TOOL

SELECTIONS = {
    'AppProxy': ['0x00039aa4', '0x00039b08', '0x0003c6bc', '0x00037b78'],
    'RoboController': ['0x00030958', '0x00026288', '0x00023768', '0x000367ac',
                       '0x0002cae8', '0x00028678', '0x000271a0', '0x00027448'],
    'libroboipc.so': ['0x000063ec', '0x0000637c'],
}
# Keep the state-machine instruction record focused; full selected-function C is unchanged.
RANGES = [(0x36f78, 0x36f92), (0x37376, 0x37418), (0x384b2, 0x38502)]


def digest(b):
    return hashlib.sha256(b).hexdigest()


def package(sources, out):
    out.mkdir(parents=True)
    records = []
    for program, entries in SELECTIONS.items():
        found = {}
        for source in sources[program]:
            for f in json.loads((source / 'selected.json').read_text()):
                found[f['address']] = (f, source)
        for entry in entries:
            f, source = found[entry]
            f = dict(f)
            raw = (source / f['c_file']).read_bytes()
            identity = raw.decode().split(' * SHA256: ')[1].splitlines()[0]
            target = Path('c') / program / f['c_file']
            (out / target).parent.mkdir(parents=True, exist_ok=True)
            (out / target).write_bytes(raw)
            f.update(program=program, sha256=identity, c_file=str(target), c_sha256=digest(raw))
            if entry == '0x000367ac':
                f['instruction_scope'] = 'selected save-result branch only; not the full function body'
                f['instructions'] = [i for i in f['instructions'] if any(
                    lo <= int(i['address'], 16) <= hi for lo, hi in RANGES)]
            else:
                f['instruction_scope'] = 'whole selected function'
            records.append(f)
    (out / 'instructions.json').write_text(json.dumps(records, indent=2) + '\n')


def run(cmd):
    print('+', ' '.join(map(str, cmd)), flush=True)
    subprocess.run(list(map(str, cmd)), cwd=ROOT, check=True)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--out', type=Path, required=True)
    a = p.parse_args()
    out = a.out.resolve()
    assert (HERE / 'scratch') in out.parents and not out.exists()
    out.mkdir(parents=True)
    py = sys.executable
    project = out / 'baseline-copy'
    run([py, TOOL, 'copy', project])
    run([py, TOOL, 'run', project, 'AppProxy', '--functions', *SELECTIONS['AppProxy'], '--out', out / 'app'])
    for program, directory in [('RoboController', 'rc'), ('libroboipc.so', 'ipc')]:
        run([py, HERE / 'discover.py', '--program', program, '--import-program',
             '--project', out / (directory + '-project'), '--out', out / directory,
             '--functions', *SELECTIONS[program]])
        run([py, HERE / 'discover.py', '--program', program,
             '--project', out / (directory + '-project'), '--out', out / (directory + '-reopen'),
             '--functions', *SELECTIONS[program]])
        for entry in SELECTIONS[program]:
            assert (out / directory / (entry + '.c')).read_bytes() == (out / (directory + '-reopen') / (entry + '.c')).read_bytes()
        assert (out / directory / 'selected.json').read_bytes() == (out / (directory + '-reopen') / 'selected.json').read_bytes()
    package({'AppProxy': [out / 'app'], 'RoboController': [out / 'rc-reopen'],
             'libroboipc.so': [out / 'ipc-reopen']}, out / 'semantic')
    files = ['instructions.json'] + [str(p.relative_to(HERE)) for p in (HERE / 'c').rglob('*.c')]
    for rel in files:
        assert (HERE / rel).read_bytes() == (out / 'semantic' / rel).read_bytes(), rel
    print('PASS: fresh import, separate reopen and byte-identical focused artifacts:', len(files))


if __name__ == '__main__':
    main()
