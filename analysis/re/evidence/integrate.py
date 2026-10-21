#!/usr/bin/env python3
"""Integrate authoritative static-analysis artifacts; never analyze or execute firmware.

Run from any directory with PYTHONDONTWRITEBYTECODE=1. Each --work directory
must be new. Recovery sources remain in their reviewed sibling layout.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys

RE = Path(__file__).resolve().parents[1]
ROOT = RE.parents[1]
LANES = ['persistence', 'catalog', 'grid', 'orchestration', 'watchdoge']
TOOL = RE / 'tooling/retool.py'
REC = RE / 'recovery'


def load(p):
    return json.loads(Path(p).read_text())


def save(p, value):
    p = Path(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(json.dumps(value, indent=2) + '\n')


def sha(p):
    h = hashlib.sha256()
    with Path(p).open('rb') as f:
        for b in iter(lambda: f.read(1024 * 1024), b''):
            h.update(b)
    return h.hexdigest()


def rel(p):
    return str(Path(p).relative_to(RE))


def addr(a):
    return int(a, 16)


def pristine_inventory(program):
    summary = load(RE / 'tooling/baseline-summary.json')
    item = next(p for p in summary['programs'] if p['program'] == program)
    return load(item['inventory'])


def snapshot():
    # Include private project bytes, not just exported analysis summaries.
    out = {}
    for root in [RE / 'baseline', RE / 'lanes', RE / 'tooling', REC]:
        h = hashlib.sha256()
        files = sorted(p for p in root.rglob('*') if p.is_file())
        for p in files:
            h.update(str(p.relative_to(root)).encode() + b'\0' + sha(p).encode() + b'\n')
        out[rel(root)] = {'files': len(files), 'tree_sha256': h.hexdigest()}
    return out


def sources():
    records = []
    for lane in LANES:
        base = RE / 'lanes' / lane
        h = load(base / 'handoff.json')
        e = load(base / 'evidence.json')
        assert h['status'] == 'ready' and not h.get('blockers'), (lane, 'blocked handoff')
        if lane == 'persistence':
            programs = [('librobopersist.so', base / 'annotations/librobopersist.so.json',
                         Path(h['reopen_output_path']), h['selected_export_addresses'])]
        elif lane == 'grid':
            programs = [('librrslamdrv.so', Path(h['annotation_files'][0]),
                         Path(h['reopen_output']), h['selected_export_addresses'])]
        elif lane == 'catalog':
            programs = [(p['program'], base / p['annotation_path'],
                         base / p['reopen_output_path'], p['selected_export_addresses']) for p in h['programs']]
        elif lane == 'orchestration':
            programs = [(prog, base / p['annotation_path'], base / p['reopen_output'],
                         p['entry_addresses']) for prog, p in h['programs'].items()]
        else:
            programs = [(p['program'], Path(p['annotation_file']), Path(p['reopen_path']),
                         p['selected_export_addresses']) for p in h['programs']]
        for prog, ann, reopened, selected in programs:
            d = load(ann)
            exported = load(reopened / 'selected.json')
            assert {addr(x['address']) for x in exported} == set(map(addr, selected))
            assert load(reopened / 'result.json')['status'] == 'ok'
            assert load(reopened / 'invocation.json')['success'] is True
            records.append({'owner': lane, 'program': prog, 'document': rel(ann),
                            'document_sha256': sha(ann), 'handoff': rel(base / 'handoff.json'),
                            'evidence': rel(base / 'evidence.json'), 'evidence_sha256': sha(base / 'evidence.json'),
                            'selected': rel(reopened / 'selected.json'), 'entries': selected,
                            'private_project': h.get('private_project_path', h.get('private_project'))})
    h = load(REC / 'handoff.json')
    proof = load(REC / 'proof-final/validation.json')
    assert proof['status'] == 'passed'
    for name, expected in h['runtime_source']['source_sha256'].items():
        assert sha(REC / name) == expected == proof['source_sha256'][name]
    for c in h['candidates']:
        if c['status'] != 'ready':
            continue
        assert sha(REC / c['recovery_request']) == c['request_sha256'] == proof['requests_sha256'][c['program']]
        assert sha(REC / c['annotation_document']) == c['annotation_sha256']
        records.append({'owner': 'recovery', 'program': c['program'],
                        'document': rel(REC / c['annotation_document']),
                        'document_sha256': c['annotation_sha256'], 'handoff': 'recovery/handoff.json',
                        'evidence': 'recovery/handoff.json', 'evidence_sha256': sha(REC / 'handoff.json'),
                        'selected': rel(REC / c['instructions']), 'entries': [c['entry']],
                        'recovery_request': rel(REC / c['recovery_request']),
                        'request_sha256': c['request_sha256']})
    assert len([r for r in records if r['owner'] == 'recovery']) == 2
    return records


def prepare(work):
    manifest = load(RE / 'manifest.json')
    assert not work.exists(), 'Use a NEW canonical work directory'
    assert work.parent == RE / 'canonical', 'Private work must be directly under canonical/'
    work.mkdir()
    identities = {}
    for b in manifest['binaries']:
        p = ROOT / b['path']
        assert sha(p) == b['sha256'] and p.stat().st_size == b['size']
        # Check the committed object, not merely another unpacked copy.
        committed_path = b['path']
        if p.is_symlink():
            link = subprocess.check_output(['git', '-C', str(ROOT), 'show', f"{manifest['input_commit']}:{b['path']}"]).decode()
            assert link == os.readlink(p), ('COMMITTED_ALIAS_MISMATCH', b['path'])
            committed_path = str(p.resolve().relative_to(ROOT))
        original = subprocess.check_output(['git', '-C', str(ROOT), 'show', f"{manifest['input_commit']}:{committed_path}"])
        assert hashlib.sha256(original).hexdigest() == b['sha256'], ('COMMITTED_CONTENT_MISMATCH', b['path'])
        identities.setdefault(b['sha256'], []).append(b['path'])
    staged = subprocess.check_output(['git', '-C', str(ROOT), 'diff', '--cached', '--name-only'], text=True)
    assert not staged, 'Pre-existing staged files require parent review'
    records = sources()
    groups, global_types = {}, {}
    for r in records:
        d = load(RE / r['document'])
        assert d['version'] == 1 and d['sha256'] in identities
        g = groups.setdefault(r['program'], {'version': 1, 'sha256': d['sha256'], 'types': [], 'functions': []})
        assert g['sha256'] == d['sha256']
        for t in d.get('types', []):
            if t['name'] in global_types:
                assert global_types[t['name']] == t, ('TYPE_CONFLICT', t, global_types[t['name']])
            global_types[t['name']] = t
            old = [x for x in g['types'] if x['name'] == t['name']]
            if not old:
                g['types'].append(t)
            else:
                assert old == [t], ('TYPE_CONFLICT', t, old)
        for f in d.get('functions', []):
            old = [x for x in g['functions'] if addr(x['address']) == addr(f['address'])]
            if old:
                assert {k:v for k,v in old[0].items() if k != 'address'} == {k:v for k,v in f.items() if k != 'address'}, ('OWNERSHIP_CONFLICT', r, f, old)
            else:
                g['functions'].append(f)
    # Match exact guards against pristine baseline, or pristine AFTER-RECOVERY metadata.
    for prog, d in groups.items():
        baseline = pristine_inventory(prog)
        assert baseline['sha256'] == d['sha256']
        current = {addr(f['address']): f for f in baseline['functions']}
        for r in records:
            if r['program'] == prog and r['owner'] == 'recovery':
                c = next(c for c in load(REC / 'handoff.json')['candidates'] if c.get('entry') in r['entries'])
                assert addr(c['entry']) not in current
                current[addr(c['entry'])] = {'name': c['initial_name'], 'signature': c['initial_signature'], 'plate_comment': c['initial_plate_comment']}
        names = {}
        for f in d['functions']:
            b = current[addr(f['address'])]
            for field, expected in f.get('expect', {}).items():
                assert b[field] == expected, ('EXPECT_CONFLICT', prog, f['address'], field, b[field], expected)
            for field in ['name', 'signature', 'plate_comment']:
                if field in f and b[field] != f[field]:
                    assert field in f.get('expect', {}), ('MISSING_GUARD', prog, f['address'], field)
            if b.get('name_source') == 'IMPORTED' and 'name' in f:
                assert f['name'] == b['name'], ('SURVIVING_SYMBOL', prog, f)
            if 'name' in f:
                assert f['name'] not in names, ('NAME_CONFLICT', prog, f['name'])
                names[f['name']] = f['address']
        d['functions'].sort(key=lambda f: addr(f['address']))
        assert 'ReSmoke' not in json.dumps(d)
        save(RE / 'annotations' / (prog + '.json'), d)
    save(work / 'plan.json', {'sources': records, 'programs': list(groups), 'identities': identities})
    save(work / 'immutable-before.json', snapshot())
    return records, groups


def run(work, groups):
    commands = []
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1')
    def command(args, output=None):
        text = shlex.join(map(str, args))
        print(text, flush=True)
        completed = subprocess.run(list(map(str, args)), env=env, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        commands.append({'command': text, 'result': 'passed' if completed.returncode == 0 else 'failed',
                         'exit_code': completed.returncode, 'output': rel(output) if output else None,
                         'summary': completed.stdout.strip()})
        save(work / 'commands.json', commands)
        assert completed.returncode == 0, completed.stdout
    project = work / 'project'
    command([sys.executable, TOOL, 'copy', project])
    # Read-only exact approved requests, before ANY annotation document.
    for prog in ['AppProxy', 'WatchDoge']:
        out = work / ('recover-' + prog)
        command([sys.executable, REC / 'recover.py', project, REC / 'requests' / (prog + '.json'), '--out', out], out)
    for prog in groups:
        entries = sorted({a for r in load(work / 'plan.json')['sources'] if r['program'] == prog for a in map(addr, r['entries'])})
        entries = [f'0x{a:08x}' for a in entries]
        for stage in ['applied', 'reopened']:
            out = work / (stage + '-' + prog)
            args = [sys.executable, TOOL, 'run', project, prog]
            if stage == 'applied':
                args += ['--annotations', RE / 'annotations' / (prog + '.json')]
            args += ['--functions', *entries, '--inventory', '--out', out]
            command(args, out)
    return commands


def verify(work):
    plan = load(work / 'plan.json')
    checks, functions, program_results, side_effects = [], [], [], []
    records = plan['sources']
    def check(condition, message):
        assert condition, message
        checks.append(message)
    for prog in plan['programs']:
        ann = load(RE / 'annotations' / (prog + '.json'))
        applied, reopened = [work / (stage + '-' + prog) for stage in ['applied', 'reopened']]
        selected = load(reopened / 'selected.json')
        selected_sources = [r for r in records if r['program'] == prog]
        wanted = {a for r in selected_sources for a in map(addr, r['entries'])}
        check({addr(f['address']) for f in selected} == wanted, prog + ': exact selected-entry union')
        for out in [applied, reopened]:
            result, inv = load(out / 'result.json'), load(out / 'invocation.json')
            check(result == {'program': prog, 'sha256': ann['sha256'], 'status': 'ok'}, str(out.name) + ': script identity/status')
            check(inv['success'] and inv['save_confirmed'] and inv['exit_code'] == 0, str(out.name) + ': successful project save')
            check({addr(p.stem) for p in out.glob('*.c')} == wanted, str(out.name) + ': focused C only')
        check('annotations' not in load(reopened / 'request.json'), prog + ': reopen without annotation replay')
        for name in ['selected.json', 'types.json', 'inventory.json']:
            check(load(applied / name) == load(reopened / name), prog + ': persisted ' + name)
        check('ReSmoke' not in json.dumps(selected) + json.dumps(load(reopened / 'types.json')), prog + ': no artificial smoke names')
        base = pristine_inventory(prog)
        before = {addr(f['address']): f for f in base['functions']}
        after = {addr(f['address']): f for f in load(reopened / 'inventory.json')['functions']}
        annotations = {addr(f['address']): f for f in ann['functions']}
        recovered = {addr(r['entries'][0]) for r in selected_sources if r['owner'] == 'recovery'}
        check(set(after) == set(before) | recovered, prog + ': only approved function additions')
        for a, b in before.items():
            f = after[a]
            check(f['body'] == b['body'], f'{prog}:{a:#x}: existing body unchanged')
            expected_name = annotations.get(a, {}).get('name', b['name'])
            check(f['name'] == expected_name, f'{prog}:{a:#x}: surviving name or explicit owned rename')
            if a not in annotations and f != b:
                # Ghidra propagates prototypes into existing PLT thunks. Preserve all
                # other fields, record exact propagated metadata for independent review.
                changes = {k: {'before': b[k], 'after': f[k]} for k in b if f[k] != b[k]}
                check(set(changes) <= {'signature', 'signature_source'}, f'{prog}:{a:#x}: unowned changes limited to propagated prototypes')
                side_effects.append({'program': prog, 'address': f'0x{a:08x}', 'changes': changes})
        dest = RE / 'decompiled' / prog
        dest.mkdir(parents=True, exist_ok=True)
        check(not list(dest.glob('*.c')), prog + ': fresh published C directory')
        for f in selected:
            a = addr(f['address'])
            filename = f['address'] + '.c'
            content = (reopened / filename).read_bytes()
            check(content == (applied / filename).read_bytes(), prog + ':' + f['address'] + ': C persists byte-for-byte')
            check(ann['sha256'].encode() in content and prog.encode() in content and f['address'].encode() in content,
                  prog + ':' + f['address'] + ': C identity header')
            provenance = []
            for r in selected_sources:
                if a not in set(map(addr, r['entries'])):
                    continue
                source_selected = load(RE / r['selected'])
                source_index = next(i for i, s in enumerate(source_selected) if addr(s['address']) == a)
                old = source_selected[source_index]
                check(old['body'] == f['body'] and old['instructions'] == f['instructions'],
                      prog + ':' + f['address'] + ': component instruction agreement ' + r['owner'])
                provenance.append({'owner': r['owner'], 'evidence': 'components/' + r['owner'] + '.json' if r['owner'] != 'recovery' else 'recovery/handoff.json',
                                   'original_evidence': r['evidence'], 'original_evidence_sha256': r['evidence_sha256'],
                                   'source_selected': r['selected'], 'source_selected_index': source_index,
                                   'annotation_document': r['document'], 'annotation_document_sha256': r['document_sha256']})
            check(bool(provenance), prog + ':' + f['address'] + ': evidence provenance')
            owner = [r['owner'] for r in selected_sources if any(addr(x['address']) == a for x in load(RE / r['document']).get('functions', []))]
            shutil.copyfile(reopened / filename, dest / filename)
            functions.append({'program': prog, 'sha256': ann['sha256'], 'binary_paths': plan['identities'][ann['sha256']],
                              'address': f['address'], 'name': f['name'], 'annotation_owners': owner,
                              'c': '../decompiled/' + prog + '/' + filename, 'c_sha256': sha(dest / filename),
                              'instructions': prog + '/selected.json', 'instruction_index': selected.index(f),
                              'provenance': provenance})
        target = RE / 'evidence' / prog
        target.mkdir(exist_ok=True)
        for name in ['selected.json', 'types.json']:
            shutil.copyfile(reopened / name, target / name)
        program_results.append({'program': prog, 'sha256': ann['sha256'], 'selected_count': len(selected),
                                'annotation_count': len(ann['functions']), 'types': prog + '/types.json',
                                'private_applied': rel(applied), 'private_reopened': rel(reopened),
                                'selected_sha256': sha(reopened / 'selected.json'), 'types_sha256': sha(reopened / 'types.json')})
    check(snapshot() == load(work / 'immutable-before.json'), 'baseline, component trees, shared tooling and recovery trees byte-identical')
    check(not subprocess.check_output(['git', '-C', str(ROOT), 'diff', '--cached', '--name-only'], text=True), 'no staged files')
    for b in load(RE / 'manifest.json')['binaries']:
        check(sha(ROOT / b['path']) == b['sha256'], b['path'] + ': final pinned hash')
    for lane in LANES:
        dest = RE / 'evidence/components' / (lane + '.json')
        dest.parent.mkdir(exist_ok=True)
        shutil.copyfile(RE / 'lanes' / lane / 'evidence.json', dest)
    for source in ['handoff.json', 'proof-final/validation.json', 'assessment/AppProxy/evidence.txt', 'assessment/WatchDoge/evidence.txt', 'assessment/librrnavdrv.so/evidence.txt']:
        dest = RE / 'evidence/recovery' / source
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(REC / source, dest)
    recovery_results = []
    for prog in ['AppProxy', 'WatchDoge']:
        out = work / ('recover-' + prog)
        inv = load(out / 'invocation.json')
        check(inv['success'] and inv['save_confirmed'], prog + ': tracked-layout recovery replay saved')
        for name in ['result.json', 'invocation.json']:
            dest = RE / 'evidence/recovery' / ('integration-' + prog) / name
            dest.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(out / name, dest)
        recovery_results.append({'program': prog, 'private_output': rel(out), 'result': 'recovery/integration-' + prog + '/result.json'})
    gaps = [
        'librrnavdrv.so startup original seed 0x20bac0 is interior; true EHABI candidate 0x20babc was not recovered. No substituted C.',
        'librrnavdrv.so completion callback 0x683e0 and AppProxy error callback 0x4afa8 remain absent baseline functions; no substituted C.',
        'WatchDoge call target 0x1abd8 remains unresolved; recovered feeder calls do not establish hardware acceptance.',
        'AppProxy IPC-to-navigation task/result bridge and correlation remain unresolved; do not concatenate local paths into end-to-end completion proof.',
        'No safe all-writer quiescence/restart, cross-file transaction, kernel/MCU reset safety or persistence durability established.',
        'Observed layout types and ABI corrections are not original C++ source; malformed-data safety, concurrency and decompiler artifacts remain component limitations.'
    ]
    validation = {'status': 'passed', 'check_count': len(checks), 'checks': checks,
                  'immutable_trees': load(work / 'immutable-before.json'), 'no_staged_files': True,
                  'programs': program_results, 'recovery': recovery_results,
                  'propagated_prototypes': side_effects, 'commands': load(work / 'commands.json')}
    save(RE / 'evidence/validation.json', validation)
    save(RE / 'evidence/index.json', {'version': 1, 'status': 'ready-for-independent-review',
         'firmware': load(RE / 'manifest.json')['firmware'], 'input_commit': load(RE / 'manifest.json')['input_commit'],
         'private_project': str(work / 'project/pinned.gpr'), 'private_work': str(work),
         'validation': 'validation.json', 'reproduction': 'integrate.py', 'programs': program_results,
         'sources': records, 'functions': functions, 'unresolved_claims': gaps,
         'recovery_note': 'Component pre-recovery gap comments are preserved verbatim; separate recovery owns the added AppProxy 0x3c5b4 and WatchDoge 0x1af18 entries. Startup remains a gap.',
         'review_gate': 'Required: fresh read-only semantic review and parent acceptance. Integration checks are not semantic/runtime acceptance.'})
    return validation


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--work', type=Path, required=True)
    args = parser.parse_args()
    work = args.work.resolve()
    try:
        _, groups = prepare(work)
        run(work, groups)
        validation = verify(work)
        print('PASS', validation['check_count'], 'integration checks')
    except Exception as exc:
        save(work / 'failure.json', {'status': 'blocked', 'error': repr(exc)})
        raise


if __name__ == '__main__':
    main()
