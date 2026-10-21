import copy
import json
from pathlib import Path
import tempfile
import unittest
from replay import HERE, package
from validate import ROOT, REL, check_instruction, offset, validate

class NativeRouteEvidenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data=(ROOT/REL).read_bytes()
        cls.row=json.loads((HERE/'bounded.json').read_text())['pseudo_thumb_linear_not_cfg'][0]

    def test_focused_validation(self):
        self.assertEqual(validate()['status'],'passed')

    def test_changed_instruction_rejected(self):
        row=copy.deepcopy(self.row);row['bytes']='0000'
        with self.assertRaises(AssertionError):check_instruction(self.data,row)

    def test_odd_instruction_rejected(self):
        row=copy.deepcopy(self.row);row['address']='0x683e1'
        with self.assertRaises(AssertionError):check_instruction(self.data,row)

    def test_unmapped_va_rejected(self):
        with self.assertRaises(AssertionError):offset(self.data,0xffffffff,4)

    def test_data_pointer_mapping_not_fixed_zero_delta(self):
        self.assertEqual(offset(self.data,0x304b78,4),0x2f4b78)

    def test_java_json_key_order_is_canonicalized(self):
        # Reproduced initial replay failure: Java Map.of key order differs across JVMs.
        # Test the packaging path rather than treating raw JSON ordering as semantic drift.
        # Supply the committed bounded ranges padded into the original discovery range shape.
        b=json.loads((HERE/'bounded.json').read_text())
        raw=[]
        for r,lo,hi in [(b['ranges'][0],0x18e848,0x18edb3),(b['ranges'][1],0x190908,0x190deb)]:
            x=dict(r);x['start']=hex(lo);x['end']=hex(hi)
            prefix=int(r['start'],16)-lo;suffix=hi-int(r['end'],16)
            x['raw_bytes']='00'*prefix+r['raw_bytes']+'00'*suffix;raw.append(x)
        b['ranges']=raw
        reverse=lambda obj:{k:reverse(v) for k,v in reversed(list(obj.items()))} if isinstance(obj,dict) else [reverse(x) for x in obj] if isinstance(obj,list) else obj
        with tempfile.TemporaryDirectory() as td:
            p=Path(td);s=p/'selected';s.mkdir()
            records=json.loads((HERE/'selected.json').read_text())
            for f in records:
                original=f['c_file'];f['c_file']=Path(original).name;f.pop('c_sha256')
                (s/f['c_file']).write_bytes((HERE/original).read_bytes())
            (s/'selected.json').write_text(json.dumps(records))
            a=p/'a.json';c=p/'b.json';a.write_text(json.dumps(b));c.write_text(json.dumps(reverse(b)))
            self.assertNotEqual(a.read_bytes(),c.read_bytes())
            package(s,a,p/'a');package(s,c,p/'b')
            self.assertEqual((p/'a/bounded.json').read_bytes(),(p/'b/bounded.json').read_bytes())
            self.assertEqual((p/'a/bounded.json').read_bytes(),(HERE/'bounded.json').read_bytes())

if __name__=='__main__':unittest.main()
