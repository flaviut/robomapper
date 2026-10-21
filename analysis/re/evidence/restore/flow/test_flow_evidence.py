"""Source-named regression tests for the lane's instruction validator."""
import json
import unittest
from validate import HERE, ROOT, check_instruction, elf_offset, validate


class FlowEvidenceTests(unittest.TestCase):
    def test_published_flow_records(self):
        self.assertEqual(validate()['status'], 'passed')

    def test_changed_instruction_bytes_rejected(self):
        f = next(f for f in json.loads((HERE / 'instructions.json').read_text())
                 if f['program'] == 'RoboController' and f['address'] == '0x00030958')
        row = f['instructions'][0]
        data = bytearray((ROOT / 'binaries/4.3.5_1612/opt/rockrobo/cleaner/bin/RoboController').read_bytes())
        data[elf_offset(data, int(row['address'], 16), len(bytes.fromhex(row['bytes'])))] ^= 1
        with self.assertRaises(AssertionError):
            check_instruction(data, row)

    def test_odd_virtual_instruction_address_rejected(self):
        with self.assertRaises(AssertionError):
            check_instruction(b'', {'address': '0x30959', 'bytes': '00bf'})

    def test_unmapped_instruction_address_rejected(self):
        data = (ROOT / 'binaries/4.3.5_1612/opt/rockrobo/cleaner/bin/RoboController').read_bytes()
        with self.assertRaises(AssertionError):
            check_instruction(data, {'address': '0x80000000', 'bytes': '00bf'})


if __name__ == '__main__':
    unittest.main()
