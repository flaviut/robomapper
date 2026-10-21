#!/usr/bin/env python3
"""Static evidence checks only; never runs firmware or opens a Ghidra baseline."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[4]


def load(path):
    return json.loads(Path(path).read_text())


def file_offset(data, va, size):
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError("Expected ELF32 little endian")
    phoff = struct.unpack_from("<I", data, 28)[0]
    entsize, count = struct.unpack_from("<HH", data, 42)
    hits = []
    for i in range(count):
        kind, off, addr, _, filesz, _, _, _ = struct.unpack_from(
            "<IIIIIIII", data, phoff + i * entsize)
        if kind == 1 and addr <= va and va + size <= addr + filesz:
            hits.append(off + va - addr)
    if len(hits) != 1:
        raise ValueError(f"No unique file-backed PT_LOAD for {va:#x}+{size}")
    return hits[0]


def verify_instructions(data, functions):
    count = 0
    for f in functions:
        entry = int(f["address"], 16)
        if entry & 1:
            raise ValueError(f"Odd entry: {entry:#x}")
        seen = set()
        for ins in f["instructions"]:
            va = int(ins["address"], 16)
            raw = bytes.fromhex(ins["bytes"])
            if va & 1 or va in seen or not raw:
                raise ValueError(f"Invalid instruction record: {va:#x}")
            seen.add(va)
            off = file_offset(data, va, len(raw))
            if data[off:off + len(raw)] != raw:
                raise ValueError(f"Instruction bytes differ at {va:#x}")
            count += 1
        if f.get("entry_file_offsets") is not None:
            if f["entry_file_offsets"] != [file_offset(data, entry, 1)]:
                raise ValueError(f"Entry mapping differs: {entry:#x}")
    return count


def direct_calls(f, target):
    return [i["address"] for i in f["instructions"]
            if i["instruction"].split()[0] in ("bl", "blx")
            and target in i["flows"]]


def validate(export_dir=HERE / "focused", reopened=None):
    evidence = load(HERE / "evidence.json")
    manifest = load(ROOT / "analysis/re/manifest.json")
    record = next(b for b in manifest["binaries"]
                  if b["path"] == evidence["tracked_input"])
    data = (ROOT / record["path"]).read_bytes()
    assert hashlib.sha256(data).hexdigest() == record["sha256"] == evidence["sha256"]
    assert len(data) == record["size"]
    functions = load(export_dir / "selected.json")
    assert [f["address"] for f in functions] == evidence["selected_entries"]
    count = verify_instructions(data, functions)
    for name, digest in evidence["export_sha256"].items():
        if name == "types.json":
            assert hashlib.sha256((HERE / "focused" / name).read_bytes()).hexdigest() == digest
            assert load(export_dir / name) == load(HERE / "focused" / name)
        else:
            assert hashlib.sha256((export_dir / name).read_bytes()).hexdigest() == digest, name
        if name.endswith(".c"):
            text = (export_dir / name).read_text()
            assert "Decompiled C, NOT recovered source; need not compile" in text
            assert evidence["sha256"] in text
    by = {f["address"]: f for f in functions}
    loader = by["0x0001c620"]
    assert direct_calls(loader, "0x0000d1c8") == ["0x0001ca04"]
    assert direct_calls(loader, "0x0000d578") == ["0x0001ca20"]
    assert direct_calls(loader, "0x0000d44c") == ["0x0001ca4a"]
    assert direct_calls(loader, "0x0000da1c") == []
    # Key branch/dataflow preconditions, not a general symbolic execution proof.
    ins = {i["address"]: i for i in loader["instructions"]}
    expected = {
        "0x0001ca12": "movs r5,#0x0",
        "0x0001ca24": "adds r3,r0,#0x1",
        "0x0001ca28": "beq 0x0001caba",
        "0x0001ca32": "beq.w 0x0001c778",
        "0x0001ca3c": "cmp r5,#0x0",
        "0x0001ca3e": "beq.w 0x0001c778",
        "0x0001caaa": "movs r5,#0x1",
        "0x0001caac": "b 0x0001ca36",
        "0x0001c84e": "bne.w 0x0001c6f2",
        "0x0001c858": "b 0x0001c6f2",
    }
    for va, text in expected.items():
        assert ins[va]["instruction"] == text, va
    for claim in evidence["claims"]:
        for group in claim["evidence"]:
            source = {i["address"]: i for i in by[group["function_entry"]]["instructions"]}
            assert group["instructions"]
            for i in group["instructions"]:
                assert source[i["address"]] == i
    worker = by["0x0001d10c"]
    assert direct_calls(worker, "0x0000da1c") == ["0x0001d1f2"]
    assert direct_calls(worker, "0x0000d44c") == ["0x0001d20a"]
    companions = load(HERE / "dependencies.json")
    context_count = 0
    identities = {}
    for context in companions["instruction_context"]:
        program = context["program"]
        binary = next(b for b in manifest["binaries"] if Path(b["path"]).name == program)
        raw = (ROOT / binary["path"]).read_bytes()
        assert hashlib.sha256(raw).hexdigest() == binary["sha256"] == context["sha256"]
        identities[program] = binary["sha256"]
        source = load(ROOT / context["source"])
        by_entry = {f["address"]: f for f in source}
        for f in context["functions"]:
            assert by_entry[f["address"]] == f
        context_count += verify_instructions(raw, context["functions"])
    for row in companions["constructor_paths"]:
        raw = (ROOT / next(b["path"] for b in manifest["binaries"]
                           if Path(b["path"]).name == "librrslamdrv.so")).read_bytes()
        expected = row["path"].encode() + b"\x00"
        off = file_offset(raw, int(row["string_va"], 16), len(expected))
        assert raw[off:off + len(expected)] == expected
    if reopened:
        for name in evidence["export_sha256"]:
            if name == "types.json":
                assert load(export_dir / name) == load(reopened / name), name
            else:
                assert (export_dir / name).read_bytes() == (reopened / name).read_bytes(), name
    return {"status": "passed", "focused_functions": len(functions),
            "focused_instructions_verified_against_ELF": count,
            "context_instructions_verified_against_ELF": context_count,
            "constructor_literals_verified": len(companions["constructor_paths"]),
            "binary_sha256": {evidence["program"]: evidence["sha256"], **identities},
            "reopened_comparison": "passed" if reopened else "not requested",
            "limits": "Byte identity and explicit branch preconditions; not firmware execution, full symbolic execution, runtime completion or durability."}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exports", type=Path, default=HERE / "focused")
    parser.add_argument("--reopened", type=Path)
    parser.add_argument("--out", type=Path)
    args = parser.parse_args()
    result = validate(args.exports, args.reopened)
    text = json.dumps(result, indent=2) + "\n"
    if args.out:
        args.out.write_text(text)
    print(text, end="")
