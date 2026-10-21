#!/usr/bin/env python3
"""Synthetic tests of saved-data checks, not execution of decompiled firmware."""
import gzip
import hashlib
from pathlib import Path
import sqlite3
import struct
import tempfile
import unittest
import zlib

import check_saved


def vint(value):
    result = bytearray()
    while value >= 128:
        result.append((value & 127) | 128)
        value >>= 7
    result.append(value)
    return bytes(result)


def scalar(number, value):
    return vint(number << 3) + vint(value)


def blob(number, value):
    return vint((number << 3) | 2) + vint(len(value)) + value


class MetadataCaptureChecks(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.archive = Path(self.tmp.name)
        self.db = sqlite3.connect(':memory:')
        self.addCleanup(self.db.close)
        self.db.execute('CREATE TABLE bakmaps (id integer primary key, map blob)')
        self.region = bytearray(0x13f120)
        self.region[0x31da0] = self.region[0x31da4] = 1
        struct.pack_into('<ii', self.region, 0x31da8, 1024, 1024)
        start = 0x31db0 + 512 * 1024 + 512
        self.region[start:start + 2] = bytes([16, 17 | 0x40])
        struct.pack_into('<I', self.region, 0x131fac, 2)
        struct.pack_into('<I', self.region, 0x131fb0 + 24, 16)
        struct.pack_into('<I', self.region, 0x131fb0 + 28 + 24, 17)
        pixels = bytes([0, 255])
        native = struct.pack('<6sHHIiiII', b'RRSLAM', 2, 20, 20, 0, 0, 2, 1)
        native += pixels + hashlib.md5(pixels).digest()
        (self.archive / 'user_map0').write_bytes(native)
        self.write_region()
        self.write_image()

    def write_region(self):
        # Independently compressed multipart data, encrypt=1 as in real captures.
        middle = len(self.region) // 2
        message = b''.join(scalar(n, v) for n, v in
                           [(10, 5), (20, 1), (30, 1), (40, len(self.region))])
        message += blob(50, zlib.compress(self.region[:middle]))
        message += blob(50, zlib.compress(self.region[middle:]))
        (self.archive / 'PersistData_2.data').write_bytes(blob(20, message))

    def write_image(self, left=512, cells=bytes([16 << 3, 17 << 3])):
        image = b'rr' + struct.pack('<H', 20) + bytes(16)
        image += struct.pack('<HHIIiiII', 2, 28, 2, 2, 512, left, 1, 2) + cells
        self.db.execute('INSERT OR REPLACE INTO bakmaps VALUES (0, ?)', (gzip.compress(image),))

    def test_multipart_capture_and_flagged_room_ids(self):
        self.assertEqual(check_saved.region5(self.archive / 'PersistData_2.data'), self.region)
        result = check_saved.check_capture(self.archive, 2, 0, self.db)
        self.assertEqual(result['image_cells_matched'], 2)
        self.assertEqual(result['upper_cell_bits_present'], [0, 64])

    def test_valid_native_checksum_does_not_bypass_room_mismatch(self):
        self.write_image(cells=bytes([16 << 3, 18 << 3]))
        with self.assertRaises(AssertionError):
            check_saved.check_capture(self.archive, 2, 0, self.db)

    def test_same_dimensions_do_not_bypass_origin_mismatch(self):
        self.write_image(left=513)
        with self.assertRaises(AssertionError):
            check_saved.check_capture(self.archive, 2, 0, self.db)

    def test_mapping_id_mismatch_rejected(self):
        struct.pack_into('<I', self.region, 0x131fb0 + 28 + 24, 18)
        self.write_region()
        with self.assertRaises(AssertionError):
            check_saved.check_capture(self.archive, 2, 0, self.db)


if __name__ == '__main__':
    unittest.main()
