#!/usr/bin/env python3
"""Replay final annotations/selected entries without ignored lane or proof inputs.

Use --plan to inspect source dependencies, or --out NEW_DIRECTORY to replay.
A closed local baseline is copied when available. Otherwise the shared harness
imports only manifest binaries into a new private project (never shared baseline).
Pinned Ghidra/Python are prerequisites; firmware is never executed.
"""
import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys

RE = Path(__file__).resolve().parents[1]
ROOT = RE.parents[1]
TOOL = RE / 'tooling/retool.py'
RECOVERY = RE / 'recovery/recover.py'


def load(path):
    return json.loads(Path(path).read_text())


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def save(path, value):
    Path(path).write_text(json.dumps(value, indent=2) + '\n')


def source_plan():
    manifest = load(RE / 'manifest.json')
    index = load(RE / 'evidence/index.json')
    paths = [Path(__file__).resolve(), RE / 'manifest.json', RE / 'evidence/index.json',
             TOOL, RE / 'tooling/ReTool.java', RECOVERY, RE / 'recovery/scripts/RecoverBounded.java']
    paths += [RE / 'annotations' / (p['program'] + '.json') for p in index['programs']]
    paths += [ROOT / b['path'] for b in manifest['binaries']]
    recoveries = [s for s in index['sources'] if s['owner'] == 'recovery']
    assert {(s['program'], int(s['entries'][0], 16)) for s in recoveries} == {('AppProxy', 0x3c5b4), ('WatchDoge', 0x1af18)}
    for s in recoveries:
        request = RE / s['recovery_request']
        assert digest(request) == s['request_sha256'], 'Recovery request identity mismatch'
        paths.append(request)
    for b in manifest['binaries']:
        assert digest(ROOT / b['path']) == b['sha256'], 'Pinned binary mismatch'
    records = []
    for p in paths:
        name = str(p.relative_to(ROOT))
        # Visible includes not-yet-staged deliverables. This does not stage anything.
        ignored = subprocess.run(['git', '-C', str(ROOT), 'check-ignore', '--no-index', '-q', name])
        assert ignored.returncode == 1, 'Missing/ignored replay dependency: ' + name
        records.append({'path': name, 'sha256': digest(p)})
    return index, recoveries, records


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--plan', action='store_true')
    parser.add_argument('--out', type=Path)
    args = parser.parse_args()
    index, recoveries, dependencies = source_plan()
    if args.plan:
        print(json.dumps({'dependencies': dependencies, 'private_cache': 'analysis/re/baseline (optional, generated)',
                          'external_prerequisite': 'Pinned Ghidra 12.0.4 from manifest/shared harness'}, indent=2))
        return
    if not args.out:
        parser.error('--out NEW_DIRECTORY is required unless --plan is used')
    out = args.out.resolve()
    assert not out.exists(), 'Use a NEW output directory'
    assert out.parent == RE / 'canonical', 'Private replay output must be under canonical/'
    out.mkdir()
    project = out / 'project'
    commands = []
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1')

    def command(argv):
        print(shlex.join(map(str, argv)), flush=True)
        result = subprocess.run(list(map(str, argv)), text=True, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        commands.append({'command': shlex.join(map(str, argv)), 'exit_code': result.returncode,
                         'result': 'passed' if result.returncode == 0 else 'failed', 'summary': result.stdout.strip()})
        save(out / 'commands.json', commands)
        assert result.returncode == 0, result.stdout

    if (RE / 'baseline/pinned.gpr').exists():
        command([sys.executable, TOOL, 'copy', project])
        baseline_mode = 'copied closed local baseline with shared retool.py'
    else:
        # Reuse the shared import path, but keep its outputs/project private.
        sys.dont_write_bytecode = True
        spec = importlib.util.spec_from_file_location('shared_retool', TOOL)
        retool = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(retool)
        project.mkdir()
        groups = retool.pinned()
        for group in groups:
            retool.headless(project, group['program'], {'sha256': group['sha256']},
                            out / ('import-' + group['program']), importing=group['resolved_path'])
        retool.save(project / 'index.json', {'project': retool.PROJECT, 'ghidra_version': '12.0.4', 'binaries': groups})
        baseline_mode = 'imported manifest binaries privately with shared harness; no shared bootstrap'
    for s in recoveries:
        command([sys.executable, RECOVERY, project, RE / s['recovery_request'], '--out', out / ('recover-' + s['program'])])
    comparisons = []
    for p in index['programs']:
        program = p['program']
        annotation = RE / 'annotations' / (program + '.json')
        assert load(annotation)['sha256'] == p['sha256']
        functions = [f for f in index['functions'] if f['program'] == program]
        assert len(functions) == p['selected_count']
        export = out / ('export-' + program)
        command([sys.executable, TOOL, 'run', project, program, '--annotations', annotation,
                 '--functions', *[f['address'] for f in functions], '--out', export])
        invocation, result = load(export / 'invocation.json'), load(export / 'result.json')
        assert invocation['success'] and invocation['save_confirmed'] and result['status'] == 'ok'
        assert result['program'] == program and result['sha256'] == p['sha256']
        selected = load(export / 'selected.json')
        assert {f['address'] for f in selected} == {f['address'] for f in functions}
        assert {x.stem for x in export.glob('*.c')} == {f['address'] for f in functions}
        for f in functions:
            assert digest(export / (f['address'] + '.c')) == f['c_sha256'], 'C differs: ' + program + ':' + f['address']
        comparisons.append({'program': program, 'functions': len(functions), 'all_index_c_hashes_match': True,
                            'selected_sha256': digest(export / 'selected.json'), 'types_sha256': digest(export / 'types.json')})
    save(out / 'result.json', {'status': 'passed', 'baseline_mode': baseline_mode, 'source_dependencies': dependencies,
                              'commands': commands, 'programs': comparisons,
                              'note': 'No lane, rootfs, bootstrap metadata or private proof input loaded. Final index supplies selection/C hashes. Optional baseline is generated cache.'})
    print('PASS: final replay; all', sum(x['functions'] for x in comparisons), 'C hashes match')


if __name__ == '__main__':
    main()
