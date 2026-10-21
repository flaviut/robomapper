#!/usr/bin/env python3
"""Private tracked-input import through the source-root shared harness; no firmware execution."""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')
BINARY = 'binaries/4.3.5_1612/opt/rockrobo/cleaner/bin/rr_loader'
SHA256 = '020d6d7de7d282ecec3e845e4664113b11df82656701d42de7e901595c5f5125'


def harness():
    spec = importlib.util.spec_from_file_location('writer_host_retool', TOOL)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--import-program', action='store_true')
    parser.add_argument('--functions', nargs='*', default=[])
    args = parser.parse_args()
    project, out = args.project.resolve(), args.out.resolve()
    scratch = HERE / '.scratch'
    assert scratch in project.parents and scratch in out.parents, 'ignored lane-local scratch only'
    binary = ROOT / BINARY
    assert hashlib.sha256(binary.read_bytes()).hexdigest() == SHA256
    assert subprocess.check_output(['git', '-C', str(ROOT), 'ls-files', '--', BINARY], text=True).strip() == BINARY
    tool = harness()
    tool.unlocked(project)
    index = tool.load(project / 'index.json')
    assert all(b['program'] != 'rr_loader' for b in index['binaries']), 'baseline index must remain unchanged'
    request = {'sha256': SHA256, 'inventory': True, 'export': args.functions}
    tool.headless(project, 'rr_loader', request, out, importing=str(binary) if args.import_program else None)


if __name__ == '__main__':
    main()
