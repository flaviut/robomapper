#!/usr/bin/env python3
"""Negative/control cases for the lane's ELF evidence checker."""
import copy
import struct
import unittest
from validate import file_offset, verify_instructions


def fixture():
    data = bytearray(0x120)
    data[:6] = b'\x7fELF\x01\x01'
    struct.pack_into('<I', data, 28, 52)
    struct.pack_into('<HH', data, 42, 32, 1)
    struct.pack_into('<IIIIIIII', data, 52, 1, 0x100, 0x1000, 0, 0x20, 0x40, 5, 4)
    data[0x100:0x102] = b'\x00\xbf'
    functions = [{'address': '0x1000', 'entry_file_offsets': [0x100],
                  'instructions': [{'address': '0x1000', 'bytes': '00bf'}]}]
    return data, functions


class BackupDependencyValidationTests(unittest.TestCase):
    def test_nonidentity_mapping_and_instruction_control(self):
        data, functions = fixture()
        self.assertEqual(file_offset(data, 0x1000, 2), 0x100)
        self.assertEqual(verify_instructions(data, functions), 1)

    def test_changed_instruction_rejected(self):
        data, functions = fixture()
        data[0x100] ^= 1
        with self.assertRaisesRegex(ValueError, 'bytes differ'):
            verify_instructions(data, functions)

    def test_odd_entry_and_wrong_offset_rejected(self):
        data, functions = fixture()
        for key, value in [('address', '0x1001'), ('entry_file_offsets', [0])]:
            bad = copy.deepcopy(functions)
            bad[0][key] = value
            with self.assertRaises(ValueError):
                verify_instructions(data, bad)

    def test_bss_and_unmapped_address_rejected(self):
        data, _ = fixture()
        for address in [0x101f, 0x1020, 0x9000]:
            with self.assertRaises(ValueError):
                file_offset(data, address, 2)

    def test_missing_entry_instruction_rejected(self):
        data, functions = fixture()
        functions[0]['instructions'] = []
        with self.assertRaisesRegex(ValueError, 'Missing entry'):
            verify_instructions(data, functions)

    def test_duplicate_instruction_rejected(self):
        data, functions = fixture()
        functions[0]['instructions'] *= 2
        with self.assertRaises(ValueError):
            verify_instructions(data, functions)

    def test_bad_elf_and_empty_ranges_rejected(self):
        data, _ = fixture()
        with self.assertRaises(ValueError):
            file_offset(bytes(512), 0x1000, 2)
        with self.assertRaises(ValueError):
            file_offset(data, 0x1000, 0)


if __name__ == '__main__':
    unittest.main()
