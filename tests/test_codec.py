"""Native format invariants shared with the standalone editor."""

import hashlib
import struct
import unittest
import zlib

from custom_components.map_editor import codec


def integer(value):
    result = bytearray()
    while value >= 128:
        result.append(value & 127 | 128)
        value >>= 7
    return bytes(result + bytes([value]))


def field(id, value):
    if isinstance(value, int):
        return integer(id * 8) + integer(value)
    return integer(id * 8 + 2) + integer(len(value)) + value


def region(id, data):
    return field(20, field(10, id) + field(20, 1) + field(40, len(data))
                 + field(50, zlib.compress(data)) + field(60, len(data)))


def fixture():
    header = b"RRSLAM" + struct.pack("<HHIiiII", 2, 20, 20, -2, -2, 4, 4)
    cells = bytes([32] * 16)
    raster = header + cells + hashlib.md5(cells).digest()
    rooms = bytearray([77] * 0x13F120)
    struct.pack_into("<ii", rooms, 0x31DA8, 4, 4)
    rooms[0x31DB0:0x31DC0] = bytes([0x41] * 16)
    persistence = field(99, b"unknown") + region(5, rooms)
    data = {"native": {"raster": codec.encode(raster), "persistence": codec.encode(persistence)},
            "cells": codec.encode(cells), "rooms": codec.encode(bytes([1] * 16))}
    return data, bytes(rooms)


class CodecTests(unittest.TestCase):
    def test_noop_is_identical(self):
        data, _ = fixture()
        edit = codec.parse_edit(data)
        self.assertEqual(codec.apply_edit(edit), (edit.raster, edit.persistence))
        self.assertEqual(codec.load_map(edit.raster, edit.persistence)["rooms"], data["rooms"])

    def test_edits_preserve_unrelated_bytes(self):
        data, before = fixture()
        data["cells"] = codec.encode(bytes([255] + [32] * 15))
        data["rooms"] = codec.encode(bytes([1, 17] + [1] * 14))
        edit = codec.parse_edit(data)
        raster, persistence = codec.apply_edit(edit)
        expected = bytearray(before)
        expected[0x31DB1] = 0x40 | 17
        self.assertEqual(codec.read_region(persistence, 5), expected)
        self.assertEqual(raster[:30], edit.raster[:30])
        self.assertTrue(persistence.startswith(field(99, b"unknown")))
        self.assertEqual(codec.inspect_map(raster)["cells"], data["cells"])

    def test_invalid_input(self):
        for value in ("!!!", "YQ=", "YQ===", None, "YR=="):
            with self.subTest(value=value), self.assertRaises(ValueError):
                codec.decode(value)
        data, _ = fixture()
        data["rooms"] = codec.encode(bytes([64] * 16))
        with self.assertRaises(ValueError):
            codec.parse_edit(data)

    def test_corrupt_checksum(self):
        data, _ = fixture()
        raster = bytearray(codec.decode(data["native"]["raster"]))
        raster[30] ^= 1
        with self.assertRaisesRegex(ValueError, "checksum"):
            codec.inspect_map(raster)

    def test_region_bounds(self):
        bomb = field(20, field(10, 5) + field(20, 1) + field(40, 10)
                     + field(50, zlib.compress(bytes(100_000))))
        with self.assertRaises(ValueError):
            codec.read_region(bomb, 5)
        with self.assertRaises(ValueError):
            codec.read_region(region(5, b"abc") * 2, 5)

    def test_catalog_selection(self):
        data, _ = fixture()
        catalog = bytearray(0x9C)
        catalog[0:3] = bytes([1, 3, 7])
        struct.pack_into("<i", catalog, 0x94, 3)
        patch = codec.make_patch(codec.parse_edit(data), {"SharedMultiMapInfo": region(8, catalog)})
        self.assertEqual(set(patch), {"last_map", "PersistData_1.data", "user_map1", "PersistData_3.data"})
        self.assertEqual(patch["last_map"], patch["user_map1"])
        self.assertEqual(patch["PersistData_1.data"], patch["PersistData_3.data"])

    def test_archive(self):
        files = {"last_map": b"raster", "PersistData_1.data": b"rooms"}
        self.assertEqual(codec.read_tar(codec.pack_tar(files)), files)
        with self.assertRaises(ValueError):
            codec.read_tar(codec.pack_tar({"../escape": b"unsafe"}))


if __name__ == "__main__":
    unittest.main()
