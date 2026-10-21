#!/usr/bin/env python3
"""Sequential fresh baseline-copy replay. New ignored lane-local scratch only."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys
from validate import HERE, ROOT, check

TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--out', required=True, type=Path)
    a = p.parse_args()
    out = a.out.resolve()
    if out.exists() or not out.is_relative_to((HERE / 'scratch').resolve()):
        p.error('output must be new and inside lane scratch')
    subprocess.run(['git', 'check-ignore', '-q', str(out)], cwd=ROOT, check=True)
    out.mkdir(parents=True)
    commands = []

    def run(parts):
        subprocess.run([str(x) for x in parts], check=True)
        commands.append([str(x) for x in parts])

    run([sys.executable, TOOL, 'copy', out / 'project'])
    evidence = json.loads((HERE / 'evidence.json').read_text())
    for b in evidence['binaries']:
        program = b['program']
        dest = out / 'exports' / program
        run([sys.executable, TOOL, 'run', out / 'project', program,
             '--functions', *b['selected_entries'], '--out', dest])
        expected = HERE / 'exports' / program
        # Canonical selection is sorted numerically; no signatures/names are changed.
        actual = sorted(json.loads((dest / 'selected.json').read_text()), key=lambda f: int(f['address'], 16))
        if actual != json.loads((expected / 'selected.json').read_text()):
            raise ValueError('fresh selected records differ: ' + program)
        (dest / 'selected.json').write_text(json.dumps(actual, indent=2) + '\n')
        shutil.copy2(expected / 'entries.json', dest / 'entries.json')
        for c in expected.glob('*.c'):
            if c.read_bytes() != (dest / c.name).read_bytes():
                raise ValueError('fresh C differs: ' + str(c))
    result = {'status': 'ok', 'commands': commands, 'counts': check(ROOT, out / 'exports'),
              'comparison': 'All C and complete selected records identical; no annotations or function creation.',
              'limit': 'Reproducibility and byte equality are not semantic or runtime safety.'}
    (out / 'replay-result.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result['counts']))


if __name__ == '__main__':
    main()
