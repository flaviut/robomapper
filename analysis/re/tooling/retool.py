#!/usr/bin/env python3
"""Pinned Ghidra headless import, private copy, annotation replay and focused export."""
import argparse
import hashlib
import json
from pathlib import Path
import shlex
import shutil
import subprocess
import struct
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
BASE = HERE.parent / "baseline"
HOME = Path("/nix/store/cw1zbnv33wxw1svbsw2a6jl0j6rq7jxh-ghidra-12.0.4/lib/ghidra")
HEADLESS = HOME / "support/analyzeHeadless"
PROJECT = "pinned"


def load(path):
    return json.loads(Path(path).read_text())


def save(path, data):
    Path(path).write_text(json.dumps(data, indent=2) + "\n")


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def pinned():
    manifest = load(ROOT / "analysis/re/manifest.json")
    groups = {}
    for b in manifest["binaries"]:
        path = ROOT / b["path"]
        actual = digest(path)
        if actual != b["sha256"] or path.stat().st_size != b["size"]:
            raise ValueError(f"Pinned input mismatch: {path}")
        group = groups.setdefault(actual, {"sha256": actual, "program": path.resolve().name,
                                         "resolved_path": str(path.resolve()), "aliases": []})
        group["aliases"].append(b["path"])
    return list(groups.values())


def elf_base(path):
    data = Path(path).read_bytes()
    if data[:6] != b"\x7fELF\x01\x01":
        raise ValueError("Only the pinned ELF32 little-endian inputs are supported")
    phoff = struct.unpack_from("<I", data, 28)[0]
    entsize, count = struct.unpack_from("<HH", data, 42)
    loads = [struct.unpack_from("<IIIIIIII", data, phoff + i * entsize)
             for i in range(count)]
    return hex(min(p[2] for p in loads if p[0] == 1))


def unlocked(directory):
    locks = list(Path(directory).glob("*.lock*"))
    if locks:
        raise ValueError(f"Project is locked; close Ghidra first: {locks}")


def headless(directory, program, request, output, importing=None):
    output = Path(output).resolve()
    if output.exists():
        raise ValueError(f"Use a fresh output directory, not {output}")
    output.mkdir(parents=True)
    request_path = output / "request.json"
    save(request_path, request)
    cmd = [str(HEADLESS), str(Path(directory).resolve()), PROJECT]
    cmd += (["-import", str(importing), "-loader-imagebase", elf_base(importing)]
            if importing else ["-process", program, "-noanalysis"])
    cmd += ["-max-cpu", "2", "-scriptPath", str(HERE), "-postScript", "ReTool.java",
            str(request_path), str(output), "-log", str(output / "ghidra.log"),
            "-scriptlog", str(output / "script.log")]
    started = time.time()
    with (output / "console.log").open("w") as log:
        completed = subprocess.run(cmd, stdout=log, stderr=subprocess.STDOUT)
    result_path = output / "result.json"
    result = load(result_path) if result_path.exists() else {"status": "missing-script-result"}
    console = (output / "console.log").read_text()
    saved = "REPORT: Save succeeded" in console
    ok = (completed.returncode == 0 and result["status"] == "ok" and saved
          and result.get("program") == program)
    record = {"argv": cmd, "command": shlex.join(cmd), "exit_code": completed.returncode,
              "script_result": result, "save_confirmed": saved, "success": ok,
              "seconds": round(time.time() - started, 3)}
    save(output / "invocation.json", record)
    if not ok:
        raise RuntimeError(f"Ghidra failed; inspect {output}/console.log and result.json: {result}")
    unlocked(directory)
    print(f"OK {program}: {output}")


def bootstrap(args):
    groups = pinned()
    if list(BASE.iterdir()):
        raise ValueError("Baseline exists; never re-bootstrap or mutate it")
    for group in groups:
        headless(BASE, group["program"], {"sha256": group["sha256"], "inventory": True},
                 HERE / "bootstrap" / group["program"], importing=group["resolved_path"])
    index = {"project": PROJECT, "ghidra_version": "12.0.4", "binaries": groups}
    save(BASE / "index.json", index)
    unlocked(BASE)
    save(HERE / "bootstrap-summary.json", {"status": "ok", "command": "python3 retool.py bootstrap",
         "index": str(BASE / "index.json"), "imports": [load(HERE / "bootstrap" / b["program"] / "invocation.json") for b in groups]})


def private_copy(args):
    dest = Path(args.dest).resolve()
    if dest == BASE or BASE in dest.parents or dest.exists():
        raise ValueError("Copy destination must be new and outside the immutable baseline")
    unlocked(BASE)
    dest.mkdir(parents=True)
    shutil.copy2(BASE / f"{PROJECT}.gpr", dest)
    shutil.copytree(BASE / f"{PROJECT}.rep", dest / f"{PROJECT}.rep")
    shutil.copy2(BASE / "index.json", dest)
    print(dest / f"{PROJECT}.gpr")


def run(args):
    directory = Path(args.project).resolve()
    output = Path(args.out).resolve()
    if directory == BASE or BASE in directory.parents or output == BASE or BASE in output.parents:
        raise ValueError("Baseline is immutable: use a private project copy")
    unlocked(directory)
    groups = load(directory / "index.json")["binaries"]
    matches = [b for b in groups if args.binary == b["program"] or args.binary == b["sha256"]]
    if len(matches) != 1:
        raise ValueError("Binary must be an unambiguous program name or full SHA256 from index.json")
    b = matches[0]
    request = {"sha256": b["sha256"], "export": args.functions, "inventory": args.inventory}
    if args.annotations:
        ann = load(args.annotations)
        # Reject a wrong identity before launching Ghidra, as well as inside the script.
        if ann.get("sha256") != b["sha256"]:
            raise ValueError("HASH_MISMATCH before launch/mutation")
        request["annotations"] = ann
    headless(directory, b["program"], request, output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="action", required=True)
    p = sub.add_parser("bootstrap", help="one-time import of pinned inputs; refuses existing baseline")
    p.set_defaults(call=bootstrap)
    p = sub.add_parser("copy", help="copy closed baseline to a new private directory")
    p.add_argument("dest"); p.set_defaults(call=private_copy)
    p = sub.add_parser("run", help="reopen private project, optionally annotate, inspect and export")
    p.add_argument("project"); p.add_argument("binary"); p.add_argument("--annotations")
    p.add_argument("--functions", nargs="*", default=[])
    p.add_argument("--inventory", action="store_true"); p.add_argument("--out", required=True)
    p.set_defaults(call=run)
    args = parser.parse_args()
    try:
        args.call(args)
    except Exception as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
