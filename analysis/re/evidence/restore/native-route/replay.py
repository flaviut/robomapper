#!/usr/bin/env python3
"""Sequential static replay; fresh private baseline copy and focused existing entries only."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]
TOOL = Path('/home/user/tmp/illegalplainape/analysis/re/tooling/retool.py')
HEADLESS = Path('/nix/store/cw1zbnv33wxw1svbsw2a6jl0j6rq7jxh-ghidra-12.0.4/lib/ghidra/support/analyzeHeadless')
ENTRIES = ['0x0006905c', '0x00067ad0', '0x0018f1d4', '0x00190400']

def package(selected, listing, out):
    out.mkdir(parents=True)
    (out / 'c').mkdir()
    records = json.loads((selected / 'selected.json').read_text())
    for f in records:
        raw = (selected / f['c_file']).read_bytes()
        (out / 'c' / f['c_file']).write_bytes(raw)
        f['c_file'] = 'c/' + f['c_file']
        f['c_sha256'] = hashlib.sha256(raw).hexdigest()
    (out / 'selected.json').write_text(json.dumps(records, indent=2) + '\n')
    j = json.loads(listing.read_text())
    # Keep only the receive loop and outgoing dispatcher, not neighboring constructors/destructors.
    kept = []
    for r, lo, hi in [(j['ranges'][0], 0x18e91c, 0x18ed67), (j['ranges'][1], 0x190908, 0x190d77)]:
        start = int(r['start'], 16)
        raw = bytes.fromhex(r['raw_bytes'])[lo-start:hi-start+1]
        kept.append({'start': hex(lo), 'end': hex(hi), 'raw_bytes': raw.hex(),
                     'instructions': [i for i in r['instructions'] if lo <= int(i['address'],16) <= hi]})
    j['ranges'] = kept
    (out / 'bounded.json').write_text(json.dumps(j, indent=2, sort_keys=True) + '\n')

def run(cmd):
    print('+', ' '.join(map(str, cmd)), flush=True)
    subprocess.run(list(map(str, cmd)), cwd=ROOT, check=True)

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--out', type=Path, required=True)
    a = p.parse_args()
    out = a.out.resolve()
    assert HERE / 'scratch' in out.parents and not out.exists(), 'new ignored lane scratch required'
    out.mkdir(parents=True)
    project = out / 'project'
    run([sys.executable, TOOL, 'copy', project])
    for name in ['selected', 'reopened']:
        run([sys.executable, TOOL, 'run', project, 'librrnavdrv.so', '--functions', *ENTRIES, '--out', out / name])
    assert (out/'selected'/'selected.json').read_bytes() == (out/'reopened'/'selected.json').read_bytes()
    for entry in ENTRIES:
        assert (out/'selected'/(entry+'.c')).read_bytes() == (out/'reopened'/(entry+'.c')).read_bytes()
    target = out / 'listing.json'
    cmd = [HEADLESS, project, 'pinned', '-process', 'librrnavdrv.so', '-noanalysis', '-max-cpu', '2',
           '-scriptPath', HERE, '-postScript', 'RouteBounded.java', target]
    with (out/'console.log').open('w') as log:
        r = subprocess.run(list(map(str,cmd)), stdout=log, stderr=subprocess.STDOUT, cwd=ROOT)
    text = (out/'console.log').read_text()
    assert r.returncode == 0 and 'REPORT: Save succeeded' in text and 'SCRIPT ERROR' not in text and target.exists()
    package(out/'reopened', target, out/'semantic')
    paths = ['selected.json','bounded.json'] + ['c/'+e+'.c' for e in ENTRIES]
    for rel in paths:
        assert (HERE/rel).read_bytes() == (out/'semantic'/rel).read_bytes(), rel
    print('PASS: fresh baseline copy, sequential reopen, bounded read-only listing; six artifacts identical')

if __name__ == '__main__':
    main()
