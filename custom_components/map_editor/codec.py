"""Native map editing, independent of Home Assistant and SSH."""

import base64
import binascii
from dataclasses import dataclass
import hashlib
import io
import struct
import tarfile
import zlib

MAX_MAP = 16 * 1024 * 1024
MAX_ARCHIVE = 128 * 1024 * 1024
_SEGMENT = 0x31DA0


def encode(data: bytes) -> str:
    return base64.b64encode(data).decode("ascii")


def decode(value: str) -> bytes:
    if not isinstance(value, str) or len(value) > (MAX_MAP + 2) // 3 * 4:
        raise ValueError("Invalid map data.")
    try:
        data = base64.b64decode(value, validate=True)
    except (ValueError, binascii.Error) as err:
        raise ValueError("Invalid map encoding.") from err
    if len(data) > MAX_MAP or encode(data) != value:
        raise ValueError("Invalid map encoding.")
    return data


def inspect_map(data: bytes) -> dict:
    if not 46 <= len(data) <= MAX_MAP:
        raise ValueError("Invalid map size.")
    if data[:6] != b"RRSLAM" or struct.unpack_from("<HHI", data, 6) != (2, 20, 20):
        raise ValueError("Unsupported map header. Expected RRSLAM v2.")
    left, top, width, height = struct.unpack_from("<iiII", data, 14)
    if not width or not height or len(data) != 46 + width * height:
        raise ValueError("Invalid map dimensions.")
    digest = hashlib.md5(data[30:-16]).digest()
    if digest != data[-16:]:
        raise ValueError("Map checksum mismatch. Retry while the robot is idle.")
    return dict(width=width, height=height, left=left, top=top, scale=20,
                checksum=digest.hex(), cells=encode(data[30:-16]))


@dataclass(frozen=True)
class _Field:
    id: int
    value: int | bytes
    raw: bytes


def _varint(data: bytes, pos: int) -> tuple[int, int]:
    value = 0
    for shift in range(0, 49, 7):
        if pos >= len(data):
            break
        byte = data[pos]
        pos += 1
        value += (byte & 127) << shift
        if byte < 128:
            return value, pos
    raise ValueError("Invalid persistence integer.")


def _integer(value: int) -> bytes:
    result = bytearray()
    while value >= 128:
        result.append(value & 127 | 128)
        value >>= 7
    result.append(value)
    return bytes(result)


def _field(id: int, data: bytes) -> bytes:
    return _integer(id * 8 + 2) + _integer(len(data)) + data


def _fields(data: bytes) -> list[_Field]:
    result = []
    pos = 0
    while pos < len(data):
        start = pos
        tag, pos = _varint(data, pos)
        id, wire = divmod(tag, 8)
        if not id:
            raise ValueError("Invalid persistence field.")
        if wire == 0:
            value, pos = _varint(data, pos)
            result.append(_Field(id, value, data[start:pos]))
            continue
        if wire == 2:
            size, pos = _varint(data, pos)
        else:
            size = {1: 8, 5: 4}.get(wire, -1)
        if size < 0 or size > len(data) - pos:
            raise ValueError("Invalid persistence field.")
        value = data[pos:pos + size]
        pos += size
        result.append(_Field(id if wire == 2 else -id, value, data[start:pos]))
    return result


def _scalar(fields: list[_Field], id: int) -> int:
    values = [item.value for item in fields if item.id == id]
    value = values[-1] if values else 0
    if not isinstance(value, int):
        raise ValueError("Invalid persistence scalar.")
    return value


def _find(data: bytes, id: int):
    envelope = _fields(data)
    matches = [item for item in envelope if item.id == 20
               and isinstance(item.value, bytes) and _scalar(_fields(item.value), 10) == id]
    if len(matches) > 1:
        raise ValueError("Duplicate persistence region.")
    return envelope, matches[0] if matches else None


def _region(field: _Field):
    values = _fields(field.value)
    size = _scalar(values, 40)
    if not 0 < size <= MAX_MAP:
        raise ValueError("Unsupported persistence region size.")
    compressed = _scalar(values, 20)
    sizes = []
    parts = []
    total = 0
    for part in values:
        if part.id == 60:
            if isinstance(part.value, int):
                sizes.append(part.value)
            else:
                pos = 0
                while pos < len(part.value):
                    value, pos = _varint(part.value, pos)
                    sizes.append(value)
        if part.id != 50:
            continue
        if not isinstance(part.value, bytes) or total >= size:
            raise ValueError("Invalid persistence parts.")
        decoded = part.value
        if compressed:
            inflater = zlib.decompressobj()
            decoded = inflater.decompress(decoded, size - total + 1)
            if not inflater.eof or inflater.unused_data:
                raise ValueError("Invalid compressed persistence part.")
        total += len(decoded)
        parts.append(decoded)
    if total != size or not parts or sizes and sizes != list(map(len, parts)):
        raise ValueError("Incomplete persistence region.")
    return values, parts, compressed


def read_region(data: bytes, id: int) -> bytes | None:
    _, field = _find(data, id)
    return b"".join(_region(field)[1]) if field else None


def _replace_region(data: bytes, id: int, after: bytes) -> bytes:
    envelope, field = _find(data, id)
    if field is None:
        raise ValueError("Missing persistence region.")
    values, parts, compressed = _region(field)
    if after == b"".join(parts):
        return data
    if len(after) != sum(map(len, parts)):
        raise ValueError("Persistence region size changed.")

    # Keep unknown fields, part boundaries and unchanged compressed parts intact.
    index = offset = 0
    result = []
    for item in values:
        if item.id != 50:
            result.append(item.raw)
            continue
        before = parts[index]
        next_part = after[offset:offset + len(before)]
        index += 1
        offset += len(before)
        result.append(item.raw if before == next_part else
                      _field(50, zlib.compress(next_part) if compressed else next_part))
    replacement = _field(20, b"".join(result))
    return b"".join(replacement if item is field else item.raw for item in envelope)


def _grid(region: bytes, frame: dict):
    if len(region) != 0x13F120:
        raise ValueError("Unsupported room data.")
    if not region[_SEGMENT] or not region[_SEGMENT + 4]:
        return None
    width, height = struct.unpack_from("<ii", region, _SEGMENT + 8)
    if width <= 0 or height <= 0 or width * height > 1024 * 1024:
        raise ValueError("Invalid room dimensions.")
    return width, height, frame["left"] + (width + 1) // 2, frame["top"] + (height + 1) // 2


def inspect_rooms(data: bytes, frame: dict) -> bytes:
    rooms = bytearray(frame["width"] * frame["height"])
    region = read_region(data, 5)
    source = _grid(region, frame) if region is not None else None
    if source is None:
        return bytes(rooms)
    width, height, left, top = source
    for y in range(frame["height"]):
        sy = top + y
        if not 0 <= sy < height:
            continue
        for x in range(frame["width"]):
            sx = left + x
            if 0 <= sx < width:
                rooms[y * frame["width"] + x] = region[_SEGMENT + 16 + sy * width + sx] & 63
    return bytes(rooms)


def load_map(raster: bytes, persistence: bytes) -> dict:
    frame = inspect_map(raster)
    return {**frame, "rooms": encode(inspect_rooms(persistence, frame)),
            "native": {"raster": encode(raster), "persistence": encode(persistence)}}


@dataclass(frozen=True)
class Edit:
    raster: bytes
    persistence: bytes
    cells: bytes
    rooms: bytes


def parse_edit(data: dict) -> Edit:
    try:
        edit = Edit(decode(data["native"]["raster"]), decode(data["native"]["persistence"]),
                    decode(data["cells"]), decode(data["rooms"]))
    except (KeyError, TypeError) as err:
        raise ValueError("Incomplete map edit.") from err
    frame = inspect_map(edit.raster)
    if len(edit.cells) != frame["width"] * frame["height"] or len(edit.rooms) != len(edit.cells) or any(id > 63 for id in edit.rooms):
        raise ValueError("Invalid edited dimensions or room IDs.")
    return edit


def apply_edit(edit: Edit) -> tuple[bytes, bytes]:
    frame = inspect_map(edit.raster)
    before = inspect_rooms(edit.persistence, frame)
    persistence = edit.persistence
    if before != edit.rooms:
        region = bytearray(read_region(persistence, 5) or b"")
        target = _grid(region, frame)
        if target is None:
            raise ValueError("The map has no editable room grid.")
        width, height, left, top = target
        for index, (old, new) in enumerate(zip(before, edit.rooms, strict=True)):
            if old == new:
                continue
            x, y = index % frame["width"] + left, index // frame["width"] + top
            if not 0 <= x < width or not 0 <= y < height:
                raise ValueError("Room edit is outside the segmentation grid.")
            offset = _SEGMENT + 16 + y * width + x
            region[offset] = region[offset] & 0xC0 | new
        persistence = _replace_region(persistence, 5, bytes(region))
    return edit.raster[:30] + edit.cells + hashlib.md5(edit.cells).digest(), persistence


def pack_tar(files: dict[str, bytes]) -> bytes:
    stream = io.BytesIO()
    with tarfile.open(fileobj=stream, mode="w", format=tarfile.USTAR_FORMAT) as archive:
        for name, data in files.items():
            member = tarfile.TarInfo(name)
            member.size = len(data)
            member.mode = 0o600
            archive.addfile(member, io.BytesIO(data))
    result = stream.getvalue()
    if len(result) > MAX_ARCHIVE:
        raise ValueError("Archive too large.")
    return result


def read_tar(data: bytes) -> dict[str, bytes]:
    if len(data) > MAX_ARCHIVE or len(data) % 512:
        raise ValueError("Invalid backup size.")
    files = {}
    with tarfile.open(fileobj=io.BytesIO(data), mode="r:") as archive:
        for member in archive:
            if not member.isfile() or "/" in member.name or member.name in ("", ".", "..") or member.name in files:
                raise ValueError("Unsafe backup member.")
            if member.size > MAX_MAP:
                raise ValueError("Backup member too large.")
            files[member.name] = archive.extractfile(member).read()
    return files


def make_patch(edit: Edit, snapshot: dict[str, bytes]) -> dict[str, bytes]:
    catalog = read_region(snapshot["SharedMultiMapInfo"], 8)
    if catalog is None or len(catalog) != 0x9C or not catalog[0]:
        raise ValueError("Unsupported map catalog.")
    flag = struct.unpack_from("<i", catalog, 0x94)[0]
    entries = [catalog[1 + i * 0x24:1 + (i + 1) * 0x24] for i in range(4)]
    selected = [entry for entry in entries if entry[0] == flag]
    if not 2 <= flag <= 5 or len(selected) != 1 or not 6 <= selected[0][1] <= 9:
        raise ValueError("Cannot identify the active primary map.")
    raster, persistence = apply_edit(edit)
    return {"last_map": raster, "PersistData_1.data": persistence,
            f"user_map{flag - 2}": raster, f"PersistData_{flag}.data": persistence}
