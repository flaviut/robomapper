#!/usr/bin/env python3
"""Reproduce only this bounded static slice using a closed-baseline private copy."""
import argparse
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
# Required source-root harness owns the immutable baseline; only its copy operation reads it.
TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')
ENTRIES = ['0x1c620', '0x1d10c', '0x17fcc', '0x17cdc',
           '0xd1c8', '0xd44c', '0xd578', '0xda1c']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True,
                        help='New directory under ignored lane-local scratch/')
    args = parser.parse_args()
    out = args.out.resolve()
    if out.exists() or not out.is_relative_to(HERE / 'scratch'):
        parser.error('Output must be new and inside this lane scratch/')
    out.mkdir(parents=True)
    project = out / 'project'

    def run(*argv):
        subprocess.run([sys.executable, *map(str, argv)], check=True, cwd=ROOT)

    run(TOOL, 'copy', project)
    run(TOOL, 'run', project, 'librobopersist.so', '--annotations',
        ROOT / 'analysis/re/annotations/librobopersist.so.json',
        '--functions', *ENTRIES, '--out', out / 'base')
    run(TOOL, 'run', project, 'librobopersist.so', '--annotations',
        HERE / 'annotations.json', '--functions', *ENTRIES, '--out', out / 'annotated')
    # A separate process reopens the saved project without replaying annotations.
    run(TOOL, 'run', project, 'librobopersist.so', '--functions', *ENTRIES,
        '--out', out / 'reopened')
    run(HERE / 'validate.py', '--exports', out / 'annotated',
        '--reopened', out / 'reopened', '--out', out / 'validation.json')


if __name__ == '__main__':
    main()
