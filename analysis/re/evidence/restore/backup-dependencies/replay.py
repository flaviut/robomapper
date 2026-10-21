#!/usr/bin/env python3
"""Fresh sequential export/reopen from private copied baseline; no firmware execution."""
import argparse
from pathlib import Path
import subprocess
import sys
from validate import HERE, ROOT, load

TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    out = args.out.resolve()
    if out.exists() or not out.is_relative_to(HERE / 'scratch'):
        parser.error('Use a new directory inside this lane scratch/')
    out.mkdir(parents=True)

    def run(*argv):
        subprocess.run([sys.executable, *map(str, argv)], cwd=ROOT, check=True)

    run(TOOL, 'copy', out / 'project')
    evidence = load(HERE / 'evidence.json')
    # No new entries or annotations: all names/signatures/ABI remain baseline values.
    for phase in ['exports', 'reopened']:
        for program in evidence['programs']:
            run(TOOL, 'run', out / 'project', program['name'], '--functions',
                *program['entries'], '--out', out / phase / program['name'])
    run(HERE / 'validate.py', '--exports', out / 'exports', '--reopened',
        out / 'reopened', '--out', out / 'validation.json')


if __name__ == '__main__':
    main()
