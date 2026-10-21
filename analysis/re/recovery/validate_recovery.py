#!/usr/bin/env python3
"""Two-pristine-copy proof; uses the shared harness for all annotation/C exports."""
import argparse
import copy
import hashlib
import json
from pathlib import Path
import subprocess
import sys

from recover import HERE, TOOL, recover, retool

PROGRAMS = {'AppProxy': '0x3c5b4', 'WatchDoge': '0x1af18'}
NAMES = {'AppProxy': 'CatalogBackupExternal', 'WatchDoge': 'WdogFeederThread'}
COMMENTS = {
    'AppProxy': 'Recovered from original Thumb bytes with exact EHABI start 0x3c5b4 and next start 0x3c5ec. Dereferences r1 as external-ID pointer, adds 2, calls 0x3c568 with a selected-native-flag output initialized to -1, and returns that selected output minus 2. The helper boolean is not the wrapper return. No external-ID bounds, file validity or cross-process completion inferred.',
    'WatchDoge': 'Recovered Thumb pthread callback: launcher 0x1ac08 passes 0x1af19; EHABI starts 0x1af18, next 0x1af6c. Logs time, flushes stdout, calls unresolved 0x1abd8 then 0x1ad68, sets word 0x345ec=1, calls 0x1aec8 then sleep(8) until that word is zero, calls 0x1ac20 and returns zero. Calls alone do not establish watchdog acceptance, map-writer quiescence, MCU behavior or persistence durability. No callback ABI signature imposed.'
}


def tree_hash(path):
    result = {}
    for p in sorted(Path(path).rglob('*')):
        if p.is_file():
            result[str(p.relative_to(path))] = retool.digest(p)
    return result


def run(command):
    subprocess.run([str(c) for c in command], check=True)


def export(project, program, output, annotations=None):
    command = [sys.executable, TOOL, 'run', project, program, '--functions', PROGRAMS[program], '--inventory', '--out', output]
    if annotations:
        command += ['--annotations', annotations]
    run(command)


def prove(out):
    if out.exists():
        raise ValueError('proof output must be new')
    out.mkdir(parents=True)
    baseline = tree_hash(retool.BASE)
    retool.save(out / 'baseline-before.json', baseline)
    identities = {b['program']: b for b in retool.load(retool.BASE / 'index.json')['binaries']}
    inputs_before = {p: retool.digest(identities[p]['resolved_path']) for p in PROGRAMS}
    source_hashes = {p: retool.digest(HERE / p) for p in ('recover.py', 'scripts/RecoverBounded.java', 'validate_recovery.py')}
    requests = {p: retool.load(HERE / 'requests' / (p + '.json')) for p in PROGRAMS}
    annotations = {}
    failures = []
    copies = []
    for label in ('a', 'b'):
        lane = out / label
        project = lane / 'project'
        run([sys.executable, TOOL, 'copy', project])
        if label == 'a':
            # All tests operate on the same still-pristine candidate and require identical
            # semantic fingerprints, including the test which fails AFTER disassembly.
            q = requests['AppProxy']
            tests = [
                ('hash-mismatch', {'sha256': '0' * 64}, 'HASH_MISMATCH'),
                ('entry-byte-mismatch', {'entry_bytes': '00' + q['entry_bytes'][2:]}, 'ENTRY_BYTES_MISMATCH'),
                ('odd-entry', {'entry': '0x3c5b5'}, 'ODD_ENTRY'),
                ('wrong-even-entry', {'entry': '0x3c5b6'}, 'UNREVIEWED_ENTRY_OR_BOUND'),
                ('wrong-bound', {'bound_end': '0x3c5eb'}, 'UNREVIEWED_ENTRY_OR_BOUND'),
                ('unexpected-context-request', {'expected_context': 'unexpected'}, 'unreviewed expected context'),
            ]
            bad_instructions = copy.deepcopy(q['instructions'])
            bad_instructions[-1]['instruction'] = 'deliberate-test-mismatch'
            tests.append(('rollback-after-disassembly', {'instructions': bad_instructions}, 'instruction mismatch'))
            for name, changes, error in tests:
                trial = dict(q, **changes)
                request = lane / 'negative-requests' / (name + '.json')
                request.parent.mkdir(parents=True, exist_ok=True)
                retool.save(request, trial)
                result = recover(project, request, lane / name, True)
                assert error in result['error'], result
                failures.append({'test': name, 'error': result['error'], 'no_semantic_mutation': result['rejection_no_semantic_mutation'], 'result': str((lane / name / 'result.json').relative_to(out))})
        for program in PROGRAMS:
            request = HERE / 'requests' / (program + '.json')
            result = recover(project, request, lane / ('recover-' + program))
            assert result['byte_identity'] and result['no_existing_function_change']
            pristine = lane / ('pristine-' + program)
            export(project, program, pristine)
            selected = retool.load(pristine / 'selected.json')[0]
            baseline_inv = retool.load(retool.HERE / 'bootstrap' / program / 'inventory.json')
            inventory = retool.load(pristine / 'inventory.json')
            old = {f['address']: f for f in baseline_inv['functions']}
            new = {f['address']: f for f in inventory['functions']}
            new.pop(selected['address'])
            assert old == new, 'existing inventory changed'
            assert selected['thumb_mode'] == 1
            assert selected['name'] == result['name'] and selected['body'] == result['body']
            # Schema-v1 expectations come from pristine AFTER-RECOVERY exports.
            if label == 'a':
                assert selected['name'].startswith('FUN_'), 'retain real symbols; review before rename'
                ann = {'version': 1, 'sha256': requests[program]['sha256'], 'types': [], 'functions': [{
                    'address': PROGRAMS[program], 'name': NAMES[program], 'plate_comment': COMMENTS[program],
                    'expect': {'name': selected['name'], 'plate_comment': selected['plate_comment']}}]}
                annotations[program] = HERE / 'annotations' / (program + '.json')
                annotations[program].parent.mkdir(exist_ok=True)
                if annotations[program].exists():
                    assert retool.load(annotations[program]) == ann
                else:
                    retool.save(annotations[program], ann)
            applied = lane / ('applied-' + program)
            reopened = lane / ('reopened-' + program)
            export(project, program, applied, annotations[program])
            export(project, program, reopened)  # New process; NO recovery or annotation replay.
            for f in ('selected.json', 'types.json', f'0x{int(PROGRAMS[program], 16):08x}.c'):
                assert (applied / f).read_bytes() == (reopened / f).read_bytes(), f
                if label == 'b':
                    assert (out / 'a' / ('reopened-' + program) / f).read_bytes() == (reopened / f).read_bytes(), f
            final = retool.load(reopened / 'selected.json')[0]
            assert final['name'] == NAMES[program] and final['plate_comment'] == COMMENTS[program]
            assert final['body'] == result['body']
            if label == 'a':
                result = recover(project, request, lane / ('existing-conflict-' + program), True)
                assert 'CODE_OR_DATA_CONFLICT' in result['error']
                failures.append({'test': 'existing-conflict-' + program, 'no_semantic_mutation': True, 'error': result['error']})
            copies.append({'copy': label, 'program': program, 'entry': selected['address'], 'body': selected['body'], 'instructions': len(selected['instructions']), 'recovery': str((lane / ('recover-' + program) / 'result.json').relative_to(out)), 'reopened_export': str(reopened.relative_to(out)), 'existing_inventory_identical': True, 'persisted': True})
    after = tree_hash(retool.BASE)
    retool.save(out / 'baseline-after.json', after)
    assert after == baseline, 'immutable baseline changed'
    assert inputs_before == {p: retool.digest(identities[p]['resolved_path']) for p in PROGRAMS}
    summary = {'status': 'passed', 'source_sha256': source_hashes, 'requests_sha256': {p: retool.digest(HERE / 'requests' / (p + '.json')) for p in PROGRAMS}, 'copies': copies, 'rejections': failures, 'baseline_tree_identical': True, 'binary_files_identical': True, 'binary_sha256': inputs_before, 'cross_copy_c_selected_types_identical': True, 'close_reopen_without_replay_identical': True, 'annotations': {p: str(a.relative_to(HERE)) for p, a in annotations.items()}, 'no_git_commands': True, 'no_staging_performed': True}
    retool.save(out / 'validation.json', summary)
    print(json.dumps(summary, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', required=True)
    args = parser.parse_args()
    prove(Path(args.out).resolve())


if __name__ == '__main__':
    main()
