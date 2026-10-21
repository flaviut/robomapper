#!/usr/bin/env python3
"""Static-only recovery/export replay. Never executes firmware; requires a NEW output directory."""
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
SOURCE = Path('/home/user/tmp/illegalplainape/analysis/re')


def load(path):
    return json.loads(path.read_text())


def run(out, source):
    if out.exists():
        raise ValueError('output must be new; keep it in ignored lane-local .scratch')
    out.mkdir(parents=True)
    spec = importlib.util.spec_from_file_location('lifecycle_retool', source / 'tooling/retool.py')
    tool = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(tool)
    commands = []

    def checked(argv):
        proc = subprocess.run(list(map(str, argv)), capture_output=True, text=True)
        commands.append({'argv': list(map(str, argv)), 'exit_code': proc.returncode})
        (out / ('command-%d.txt' % len(commands))).write_text(proc.stdout + proc.stderr)
        output = proc.stdout + proc.stderr
        headless_failed = str(argv[0]) == str(tool.HEADLESS) and (
            'ERROR REPORT SCRIPT ERROR' in output or 'REPORT: Save succeeded' not in output)
        if proc.returncode or headless_failed:
            raise RuntimeError('command failed: inspect private command logs')

    project = out / 'project'
    checked([sys.executable, source / 'tooling/retool.py', 'copy', project])
    checked([sys.executable, source / 'recovery/recover.py', project,
             source / 'recovery/requests/WatchDoge.json', '--out', out / 'recover-feeder'])
    result = out / 'recover-signal-mask.json'
    checked([tool.HEADLESS, project, 'pinned', '-process', 'WatchDoge', '-noanalysis',
             '-max-cpu', '2', '-scriptPath', HERE / 'scripts', '-postScript',
             'RecoverLifecycle.java', HERE / 'request.json', result])
    recovery = load(result)
    assert recovery['status'] == 'ok' and recovery['committed']
    assert recovery['byte_identity'] and recovery['no_existing_function_change']
    # A separate reopen exports the actual saved function, without replaying recovery.
    entries = ['0x1abd8', '0x1af18', '0x1ac08']
    checked([sys.executable, source / 'tooling/retool.py', 'run', project, 'WatchDoge',
             '--annotations', HERE / 'annotations.json', '--functions', *entries,
             '--out', out / 'annotated'])
    checked([sys.executable, source / 'tooling/retool.py', 'run', project, 'WatchDoge',
             '--functions', *entries, '--out', out / 'reopened'])
    for name in ['selected.json', 'types.json'] + ['0x%08x.c' % int(a, 16) for a in entries]:
        assert (out / 'annotated' / name).read_bytes() == (out / 'reopened' / name).read_bytes(), name
    # An unchanged request cannot add a second overlapping function. Rejection must roll back.
    rejection = out / 'rejection.json'
    checked([tool.HEADLESS, project, 'pinned', '-process', 'WatchDoge', '-noanalysis',
             '-max-cpu', '2', '-scriptPath', HERE / 'scripts', '-postScript',
             'RecoverLifecycle.java', HERE / 'request.json', rejection])
    rejected = load(rejection)
    assert rejected['status'] == 'rejected' and rejected['rejection_no_semantic_mutation']
    assert 'CONFLICT' in rejected['error']
    summary = {'status': 'passed', 'commands': commands, 'recovery': recovery,
               'rejection': rejected, 'reopen_byte_identical': True,
               'c_sha256': {a: hashlib.sha256((out / 'reopened' / ('0x%08x.c' % int(a, 16))).read_bytes()).hexdigest()
                            for a in entries}}
    (out / 'validation.json').write_text(json.dumps(summary, indent=2) + '\n')
    print('PASS: bounded recovery, unchanged existing functions/bytes, saved reopen, rejection rollback')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--source-re', type=Path, default=SOURCE,
                        help='existing source-root tooling/recovery; baseline is copied, never opened')
    args = parser.parse_args()
    run(args.out.resolve(), args.source_re.resolve())
