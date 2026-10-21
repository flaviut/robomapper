#!/usr/bin/env python3
"""Fresh sequential baseline-copy/private-import/reopen replay, lane-local only."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys
from evidence import ENTRIES, package, save, validate
from import_export import HERE, ROOT, TOOL, harness


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out',type=Path,required=True)
    parser.add_argument('--record',action='store_true',help='package first proof; refuses existing proof')
    args = parser.parse_args()
    out = args.out.resolve()
    assert HERE/'.scratch' in out.parents and not out.exists()
    out.mkdir(parents=True)
    commands = []
    def run(argv, log=None):
        result = subprocess.run(list(map(str,argv)),cwd=ROOT,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        if log:
            log.write_text(result.stdout)
        commands.append({'command':' '.join(map(str,argv)),'exit_code':result.returncode,
            'result':'passed' if result.returncode == 0 else 'failed'})
        save(out/'commands.json',commands)
        assert result.returncode == 0, result.stdout[-4000:]
    project = out/'project'
    run([sys.executable,TOOL,'copy',project])
    for name, importing in [('import',True),('reopened',False)]:
        argv = [sys.executable,HERE/'import_export.py','--project',project,'--out',out/name,'--functions',*ENTRIES]
        if importing:
            argv.append('--import-program')
        run(argv)
    for rel in ['selected.json','types.json']+[f+'.c' for f in ENTRIES]:
        assert (out/'import'/rel).read_bytes() == (out/'reopened'/rel).read_bytes(), 'reopen differs: '+rel
    inspect = out/'inspect'
    inspect.mkdir()
    run([harness().HEADLESS,project,'pinned','-process','rr_loader','-noanalysis','-readOnly','-max-cpu','2',
        '-scriptPath',HERE,'-postScript','InspectHost.java',inspect/'thread.json'],inspect/'console.log')
    assert 'ERROR' not in (inspect/'console.log').read_text()
    semantic = out/'semantic'
    package(out/'reopened',semantic)
    # Canonical JSON avoids Java Map iteration order, without ignoring any fields.
    (semantic/'thread.json').write_text(json.dumps(json.loads((inspect/'thread.json').read_text()),indent=2,sort_keys=True)+'\n')
    validation = validate(semantic)
    proof = HERE/'proof'
    if args.record:
        assert not proof.exists()
        shutil.copytree(semantic,proof)
    else:
        expected = sorted(str(p.relative_to(proof)) for p in proof.rglob('*') if p.is_file())
        actual = sorted(str(p.relative_to(semantic)) for p in semantic.rglob('*') if p.is_file())
        assert expected == actual
        for rel in expected:
            assert (proof/rel).read_bytes() == (semantic/rel).read_bytes(), 'fresh replay differs: '+rel
        validation['published_artifacts_identical'] = len(expected)
    validation['commands'] = commands
    validation['limits'] = 'Byte/reopen equality is not semantic correctness or runtime safety.'
    save(out/'validation.json',validation)
    print('PASS: fresh private import, saved reopen, authenticated data decode, focused byte-identical artifacts' if not args.record else 'PASS: initial proof packaged')


if __name__ == '__main__':
    main()
