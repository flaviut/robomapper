#!/usr/bin/env python3
"""Replay one of the two reviewed recovery requests on a NEW private baseline copy."""
import argparse
import importlib.util
import json
from pathlib import Path
import shlex
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
TOOL = HERE.parent / 'tooling' / 'retool.py'
spec = importlib.util.spec_from_file_location('shared_retool', TOOL)
retool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(retool)


def recover(project, request, output, expect_rejection=False):
    project, request, output = map(lambda p: Path(p).resolve(), (project, request, output))
    base = retool.BASE.resolve()
    if project == base or base in project.parents or output == base or base in output.parents:
        raise ValueError('immutable baseline; use retool.py copy first')
    if (project / 'pinned.rep').is_symlink() or base in (project / 'pinned.rep').resolve().parents:
        raise ValueError('private repository must not alias baseline')
    if project.name == 'baseline' or not (project / 'pinned.gpr').is_file():
        raise ValueError('closed private baseline copy required')
    retool.unlocked(project)
    q = json.loads(request.read_text())
    if q['program'] not in ('AppProxy', 'WatchDoge'):
        raise ValueError('only the two reviewed recoveries are supported')
    groups = retool.load(project / 'index.json')['binaries']
    if len([b for b in groups if b['program'] == q['program']]) != 1:
        raise ValueError('private copy identity index is ambiguous')
    if output.exists():
        raise ValueError('use a new output directory')
    output.mkdir(parents=True)
    result_path = output / 'result.json'
    cmd = [str(retool.HEADLESS), str(project), retool.PROJECT,
           '-process', q['program'], '-noanalysis', '-max-cpu', '2',
           '-scriptPath', str(HERE / 'scripts'), '-postScript', 'RecoverBounded.java',
           str(request), str(result_path), '-log', str(output / 'ghidra.log'),
           '-scriptlog', str(output / 'script.log')]
    started = time.time()
    with (output / 'console.log').open('w') as f:
        proc = subprocess.run(cmd, stdout=f, stderr=subprocess.STDOUT)
    result = retool.load(result_path) if result_path.exists() else {'status': 'missing-script-result'}
    console = (output / 'console.log').read_text()
    saved = 'REPORT: Save succeeded' in console
    valid = result.get('status') == ('rejected' if expect_rejection else 'ok')
    if expect_rejection:
        valid = valid and result.get('rejection_no_semantic_mutation') is True
    ok = proc.returncode == 0 and valid and saved and 'ERROR REPORT SCRIPT ERROR' not in console
    record = {'argv': cmd, 'command': shlex.join(cmd), 'exit_code': proc.returncode,
              'save_confirmed': saved, 'expected_rejection': expect_rejection,
              'result': result, 'success': ok, 'seconds': round(time.time() - started, 3)}
    retool.save(output / 'invocation.json', record)
    retool.unlocked(project)
    if not ok:
        raise RuntimeError(f'recovery did not satisfy checks; inspect {output}')
    print(f'OK {q["program"]}: {result["status"]}; {output}')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('project')
    parser.add_argument('request')
    parser.add_argument('--out', required=True)
    parser.add_argument('--expect-rejection', action='store_true', help='test-only: require rejection with identical semantic fingerprint')
    args = parser.parse_args()
    try:
        recover(args.project, args.request, args.out, args.expect_rejection)
    except Exception as e:
        print(f'ERROR: {e}', file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
