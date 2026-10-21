"""Host-side provenance checker tests, not algorithm/firmware emulation."""
import json
from pathlib import Path
import shutil
import tempfile
import unittest
from validate import HERE, check, elf_loads, file_offset


class RoomReconcileEvidenceTests(unittest.TestCase):
    def test_committed_evidence(self):
        self.assertEqual(check()['functions'], 15)

    def test_non_elf_rejected(self):
        with self.assertRaisesRegex(ValueError, 'ELF32'):
            elf_loads(b'not firmware')

    def test_non_executable_and_cross_boundary_rejected(self):
        load = (1, 0x100, 0x200, 0, 4, 4, 4, 4)
        with self.assertRaisesRegex(ValueError, 'executable'):
            file_offset([load], 0x200, 2)
        with self.assertRaisesRegex(ValueError, 'mapping'):
            file_offset([(*load[:6], 5, 4)], 0x202, 4)

    def test_c_tamper_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            dest = Path(temp) / 'exports'
            shutil.copytree(HERE / 'exports', dest)
            c = next(dest.rglob('*.c'))
            c.write_bytes(c.read_bytes() + b'changed')
            with self.assertRaisesRegex(ValueError, 'C identity'):
                check(exports=dest)

    def test_selected_entry_tamper_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            dest = Path(temp) / 'exports'
            shutil.copytree(HERE / 'exports', dest)
            selected = next(dest.rglob('selected.json'))
            data = json.loads(selected.read_text())
            data[0]['address'] = '0x00000000'
            selected.write_text(json.dumps(data))
            with self.assertRaisesRegex(ValueError, 'selected identity'):
                check(exports=dest)


if __name__ == '__main__':
    unittest.main()
