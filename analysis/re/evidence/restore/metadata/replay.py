#!/usr/bin/env python3
"""Copy (never open) the closed baseline, re-export this lane and compare.

Example from repository root:
  python3 analysis/re/evidence/restore/metadata/replay.py \
    --out analysis/re/evidence/restore/metadata/scratch/replay-NEW
The output must be new. Projects, inventories and logs stay ignored/private.
No annotations, function creation, imports, or firmware execution are performed.
"""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
DEFAULT_TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--tool', type=Path, default=DEFAULT_TOOL)
    args = parser.parse_args()
    out = args.out.resolve()
    if out.exists():
        raise ValueError('Use a new private output directory')
    out.mkdir(parents=True)
    project = out / 'project'
    commands = []

    def run(parts):
        subprocess.run(parts, check=True)
        commands.append({'argv': [str(p) for p in parts], 'status': 'ok'})

    run([sys.executable, str(args.tool), 'copy', str(project)])
    evidence = json.loads((HERE / 'evidence.json').read_text())
    target = out / 'exports'
    for binary in evidence['binaries']:
        program = binary['program']
        export = out / program
        run([sys.executable, str(args.tool), 'run', str(project), program,
             '--functions', *binary['selected_entries'], '--out', str(export)])
        dest = target / program
        dest.mkdir(parents=True)
        selected = sorted(json.loads((export / 'selected.json').read_text()),
                          key=lambda f: int(f['address'], 16))
        expected = json.loads((HERE / 'exports' / program / 'selected.json').read_text())
        assert selected == expected, f'{program}: selected metadata/instruction difference'
        (dest / 'selected.json').write_text(json.dumps(selected, indent=2) + '\n')
        for path in export.glob('*.c'):
            assert path.read_bytes() == (HERE / 'exports' / program / path.name).read_bytes()
            shutil.copy2(path, dest / path.name)
    run([sys.executable, str(HERE / 'validate.py'), '--root', str(ROOT), '--exports', str(target)])
    (out / 'replay-result.json').write_text(json.dumps({'status': 'ok', 'commands': commands,
        'comparison': 'all seven C files and selected records match fresh closed-baseline copy'}, indent=2) + '\n')
    print('OK: seven exports reproduced; no annotations or recovery requests applied')


if __name__ == '__main__':
    main()
