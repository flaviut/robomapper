#!/usr/bin/env python3
"""Read-only, bounded ELF dependency/import screen; no firmware execution or payload decoding.

This is a candidate screen, not proof of complete writer coverage. Dynamic loading,
stripped private calls, raw syscalls and external programs are not excluded by it.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
LIBS = {'librobopersist.so', 'librrnavdrv.so', 'librrslamdrv.so'}
SYMBOL = re.compile(r'PersistSave|PersistMapInfoFileDelete|SerializeMultiMapInfo|GetSharedUserMapInfo|DeserializeMultiMapInfo|sqlite3_(open|exec|prepare|step|close)|SaveGrid')


def screen():
    paths = subprocess.check_output(['git', 'ls-files', 'binaries'], cwd=ROOT, text=True).splitlines()
    candidates = []
    screened = 0
    for relative in paths:
        path = ROOT / relative
        if path.suffix == '.json' or path.read_bytes()[:4] != b'\x7fELF':
            continue
        screened += 1
        dep = subprocess.run(['readelf', '-d', str(path)], capture_output=True, text=True, check=True)
        sym = subprocess.run(['readelf', '-Ws', str(path)], capture_output=True, text=True, check=True)
        libraries = sorted(set(re.findall(r'Shared library: \[(.*?)\]', dep.stdout)))
        symbols = sorted(set(line.split()[-1] for line in sym.stdout.splitlines()
                             if ' UND ' in line and SYMBOL.search(line)))
        if LIBS.intersection(libraries) or symbols:
            candidates.append({'path': relative, 'sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
                               'needed': libraries, 'selected_undefined_symbols': symbols,
                               'classification': 'candidate only; dependency/import is not a write call'})
    return {'format_version': 1, 'screened_tracked_elf_paths': screened,
            'filter': {'needed_any': sorted(LIBS), 'undefined_symbol_regex': SYMBOL.pattern},
            'limitations': ['Not a complete writer inventory: private/dlopen/raw-syscall paths and untracked external programs remain.',
                           'Undefined symbol presence does not identify its caller or prove execution.'],
            'candidates': candidates}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    args.out.write_text(json.dumps(screen(), indent=2) + '\n')
