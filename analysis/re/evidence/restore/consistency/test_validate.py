"""Negative controls for evidence validation; no firmware execution."""
import copy
import struct
import unittest

import validate


class InstructionEvidenceValidationTests(unittest.TestCase):
    def setUp(self):
        self.evidence = validate.load(validate.HERE / 'evidence.json')
        self.raw = (validate.ROOT / self.evidence['tracked_input']).read_bytes()
        self.functions = validate.load(validate.HERE / 'focused/selected.json')

    def test_all_focused_instruction_bytes_match_pinned_elf(self):
        self.assertGreater(validate.verify_instructions(self.raw, self.functions), 2000)

    def test_tampered_instruction_is_rejected(self):
        functions = copy.deepcopy(self.functions)
        functions[0]['instructions'][0]['bytes'] = '0000'
        with self.assertRaisesRegex(ValueError, 'bytes differ'):
            validate.verify_instructions(self.raw, functions)

    def test_odd_entry_is_rejected(self):
        functions = copy.deepcopy(self.functions)
        functions[0]['address'] = '0x1c621'
        with self.assertRaisesRegex(ValueError, 'Odd entry'):
            validate.verify_instructions(self.raw, functions)

    def test_wrong_loader_mapping_is_rejected(self):
        functions = copy.deepcopy(self.functions)
        functions[0]['entry_file_offsets'] = [0]
        with self.assertRaisesRegex(ValueError, 'Entry mapping differs'):
            validate.verify_instructions(self.raw, functions)

    def test_non_file_backed_va_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'No unique file-backed'):
            validate.file_offset(self.raw, 0xffffffff, 4)

    def test_invalid_elf_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'Expected ELF32'):
            validate.file_offset(b'not an ELF', 0, 1)

    def test_nonzero_load_mapping_is_not_assumed_identity(self):
        raw = bytearray(128)
        raw[:6] = b'\x7fELF\x01\x01'
        struct.pack_into('<I', raw, 28, 52)
        struct.pack_into('<HH', raw, 42, 32, 1)
        struct.pack_into('<IIIIIIII', raw, 52, 1, 100, 0x10000, 0, 28, 28, 5, 4)
        self.assertEqual(validate.file_offset(raw, 0x10004, 4), 104)


if __name__ == '__main__':
    unittest.main()
