#!/usr/bin/env python3
"""Lane-private import/export; never expands the shared seven-program baseline."""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')
spec = importlib.util.spec_from_file_location('retool', TOOL)
retool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(retool)
INPUTS = {
    'RoboController': ('binaries/4.3.5_1612/opt/rockrobo/cleaner/bin/RoboController',
        'bf1d43313dd8beaa0c802f9ae4c666138b3bb518f69b4909a746285f3f3947cf'),
    'libroboipc.so': ('binaries/4.3.5_1612/opt/rockrobo/cleaner/lib/libroboipc.so',
        'a7a693c8edd37aa9367f680d2f742ef81f4b8007c97a7720fc02f35ded57a832'),
}


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--program', choices=INPUTS, default='RoboController')
    p.add_argument('--out', type=Path, required=True)
    p.add_argument('--project', type=Path, required=True)
    p.add_argument('--import-program', action='store_true')
    p.add_argument('--functions', nargs='*', default=[])
    a = p.parse_args()
    rel, sha = INPUTS[a.program]
    binary = ROOT / rel
    assert hashlib.sha256(binary.read_bytes()).hexdigest() == sha
    assert subprocess.check_output(['git', '-C', str(ROOT), 'ls-files', '--', rel], text=True).strip() == rel
    project, out = a.project.resolve(), a.out.resolve()
    assert HERE in project.parents and HERE in out.parents, 'lane-local outputs only'
    assert not out.exists(), 'fresh outputs only'
    retool.unlocked(project)
    project.mkdir(parents=True, exist_ok=True)
    out.mkdir(parents=True)
    q = {'sha256': sha, 'inventory': True, 'export': a.functions}
    (out / 'request.json').write_text(json.dumps(q, indent=2) + '\n')
    cmd = [str(retool.HEADLESS), str(project), 'pinned']
    if a.import_program:
        assert not (project / 'pinned.gpr').exists(), 'fresh import only'
        cmd += ['-import', str(binary), '-loader-imagebase', retool.elf_base(binary),
                '-processor', 'ARM:LE:32:v8', '-cspec', 'default']
    else:
        cmd += ['-process', a.program, '-noanalysis']
    cmd += ['-max-cpu', '2', '-scriptPath', str(retool.HERE) + ';' + str(HERE),
            '-postScript', 'FlowDiscover.java', str(out / 'discovery.json'),
            '-postScript', 'ReTool.java', str(out / 'request.json'), str(out),
            '-log', str(out / 'ghidra.log'), '-scriptlog', str(out / 'script.log')]
    with (out / 'console.log').open('w') as log:
        r = subprocess.run(cmd, stdout=log, stderr=subprocess.STDOUT)
    result = json.loads((out / 'result.json').read_text())
    saved = 'REPORT: Save succeeded' in (out / 'console.log').read_text()
    ok = r.returncode == 0 and result['status'] == 'ok' and saved
    (out / 'invocation.json').write_text(json.dumps({'argv': cmd, 'input': rel, 'sha256': sha,
        'language': 'ARM:LE:32:v8', 'compiler': 'default', 'image_base': retool.elf_base(binary),
        'exit_code': r.returncode, 'save_confirmed': saved, 'success': ok}, indent=2) + '\n')
    assert ok, out
    print('OK', out)


if __name__ == '__main__':
    main()
