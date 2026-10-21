#!/usr/bin/env python3
"""Repeatable proof in disposable tooling/smoke-proof-* directories only."""
import argparse
import json
from pathlib import Path
import shlex
import subprocess
import sys
import time
import retool as tool


def tree_hashes(directory):
    return {str(p.relative_to(directory)): tool.digest(p)
            for p in sorted(Path(directory).rglob("*")) if p.is_file()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", required=True)
    args = parser.parse_args()
    out = Path(args.out).resolve()
    if out.parent != tool.HERE or not out.name.startswith("smoke-proof-") or out.exists():
        raise ValueError("Use a new direct tooling/smoke-proof-* directory")
    out.mkdir()
    sources = ["retool.py", "ReTool.java", "smoke_test.py", "annotations.schema.json"]
    source_hashes = {name: tool.digest(tool.HERE / name) for name in sources}
    evidence = {"status": "running", "commands": [], "checks": [], "tooling_sha256": source_hashes}
    original = {b["sha256"]: b for b in tool.pinned()}
    baseline_before = tree_hashes(tool.BASE)
    evidence["pinned_inputs_before"] = list(original)
    tool.save(out / "evidence.json", evidence)

    def command(argv, label, success=True):
        argv = [str(x) for x in argv]
        start = time.time()
        cp = subprocess.run(argv, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        (out / (label + ".log")).write_text(cp.stdout)
        evidence["commands"].append({"argv": argv, "command": shlex.join(argv),
                                      "exit_code": cp.returncode, "expected_success": success,
                                      "seconds": round(time.time() - start, 3), "log": label + ".log"})
        tool.save(out / "evidence.json", evidence)
        if (cp.returncode == 0) != success:
            raise AssertionError(f"Unexpected exit for {label}: {cp.stdout}")
        return cp.stdout

    def check(name, truth):
        evidence["checks"].append({"name": name, "passed": bool(truth)})
        tool.save(out / "evidence.json", evidence)
        if not truth:
            raise AssertionError(name)

    def run(project, binary, label, addresses, annotations=None):
        argv = [sys.executable, tool.HERE / "retool.py", "run", project, binary,
                "--out", out / label, "--functions", *addresses]
        if annotations:
            argv += ["--annotations", annotations]
        command(argv, label)
        return tool.load(out / label / "selected.json")

    def c_body(path):
        # Identity headers are checked separately; no timestamps are generated.
        return Path(path).read_text().split("*/", 1)[1].strip()

    a, b = out / "private-a", out / "private-b"
    command([sys.executable, tool.HERE / "retool.py", "copy", a], "copy-a")
    command([sys.executable, tool.HERE / "retool.py", "copy", b], "copy-b")
    before = run(a, "WatchDoge", "watch-before", ["0x1ad68", "0x142e4"])
    persist = run(a, "librobopersist.so", "persist-before", ["0x1ab94"])
    check("persist_entry_is_thumb_push", persist[0]["thumb_mode"] == 1 and
          persist[0]["instructions"][0]["bytes"] == "2de9f047")
    check("watch_entry_is_thumb_push", before[0]["thumb_mode"] == 1 and
          before[0]["instructions"][0]["bytes"] == "2de9f041")
    check("VA_to_file_mapping_from_loader_sources", persist[0]["entry_file_offsets"] == [0x1ab94] and
          before[0]["entry_file_offsets"] == [0xad68])
    calls = [i for i in before[1]["instructions"] if "0x0001ad68" in i["flows"]]
    check("real_caller_has_two_direct_calls", len(calls) == 2 and all(i["instruction"].startswith("bl ") for i in calls))
    evidence["verified_anchors"] = [
        {"binary": "librobopersist.so", "address": "0x1ab94", "body": persist[0]["body"],
         "symbol": persist[0]["qualified_name"], "thumb": True,
         "file_offset": persist[0]["entry_file_offsets"][0]},
        {"binary": "WatchDoge", "address": "0x1ad68", "body": before[0]["body"], "thumb": True,
         "file_offset": before[0]["entry_file_offsets"][0],
         "caller": "0x142e4", "call_instructions": calls}]
    sha = next(h for h, x in original.items() if x["program"] == "WatchDoge")
    demo = {"version": 1, "sha256": sha,
            "types": [{"name": "ReSmokeU32", "declaration": "typedef unsigned int ReSmokeU32;"}],
            "functions": [{"address": "0x1ad68", "name": "ReSmokeHwInit",
                           "signature": "void ReSmokeHwInit(void)",
                           "plate_comment": "Tooling smoke only: verified Thumb entry; void/no-argument init signature.",
                           "expect": {k: before[0][k] for k in ["name", "signature", "plate_comment"]}}]}
    annotation = out / "annotations.json"
    tool.save(annotation, demo)
    first = run(a, "WatchDoge", "apply-a", ["0x1ad68", "0x142e4"], annotation)
    old_c = (out / "watch-before/0x000142e4.c").read_text()
    new_c = (out / "apply-a/0x000142e4.c").read_text()
    check("rename_visible_in_real_caller", "FUN_0001ad68();" in old_c and
          "ReSmokeHwInit();" in new_c and "FUN_0001ad68();" not in new_c)
    check("recovered_signature_applied", first[0]["signature"] == "void ReSmokeHwInit(void)" and
          first[0]["signature_source"] == "USER_DEFINED")
    check("durable_comment_applied", first[0]["plate_comment"] == demo["functions"][0]["plate_comment"])
    reopened = run(a, "WatchDoge", "reopen-a", ["0x1ad68", "0x142e4"])
    check("names_types_comments_survive_reopen", first == reopened and
          tool.load(out / "apply-a/types.json") == tool.load(out / "reopen-a/types.json"))
    check("shared_type_survives_reopen", any(t["path"] == "/shared/ReSmokeU32" and t["length"] == 4
                                             for t in tool.load(out / "reopen-a/types.json")))
    repeated = run(a, "WatchDoge", "reapply-a", ["0x1ad68", "0x142e4"], annotation)
    second = run(b, "WatchDoge", "apply-b", ["0x1ad68", "0x142e4"], annotation)
    check("idempotent_replay", repeated == first)
    check("pristine_second_copy_same_semantics", second == first and
          tool.load(out / "apply-a/types.json") == tool.load(out / "apply-b/types.json"))
    check("reopened_and_second_copy_same_C", all(
        c_body(out / "apply-a" / f["c_file"]) == c_body(out / "reopen-a" / f["c_file"]) ==
        c_body(out / "apply-b" / f["c_file"]) for f in first))
    check("C_export_has_identity", sha in new_c and "Function VA: 0x000142e4" in new_c and
          "Decompiled C, NOT recovered source" in new_c)

    bad_hash = dict(demo, sha256="0" * 64)
    bad_path = out / "bad-hash.json"
    tool.save(bad_path, bad_hash)
    before_hash = tree_hashes(b)
    output = command([sys.executable, tool.HERE / "retool.py", "run", b, "WatchDoge",
                      "--annotations", bad_path, "--out", out / "bad-hash-output"], "bad-hash", False)
    check("wrong_hash_rejected_before_launch_no_bytes_changed", "HASH_MISMATCH before launch/mutation" in output and
          before_hash == tree_hashes(b) and not (out / "bad-hash-output").exists())

    def reject(label, annotations, message):
        # Bypass Python preflight to exercise the in-Ghidra safety checks as well.
        request = {"sha256": sha, "annotations": annotations}
        directory = out / label
        try:
            tool.headless(b, "WatchDoge", request, directory)
            raise AssertionError(f"Unexpected success: {label}")
        except RuntimeError:
            result = tool.load(directory / "result.json")
            check(label, result["status"] == "error" and not result["annotations_committed"] and message in result["error"])
            evidence["commands"].append(tool.load(directory / "invocation.json"))
        now = run(b, "WatchDoge", label + "-recheck", ["0x1ad68", "0x142e4"])
        check(label + "-no-semantic-mutation", now == second and
              tool.load(out / (label + "-recheck") / "types.json") == tool.load(out / "apply-b/types.json"))

    reject("inner-hash-rejected", bad_hash, "HASH_MISMATCH")
    reject("missing-entry-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad6a", "name": "NotAnEntry"}]}, "Absent/ambiguous")
    reject("odd-anchor-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad69", "name": "ThumbTag"}]}, "Odd/Thumb-tagged")
    reject("name-conflict-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad68", "name": "ConflictingName"}]}, "Conflicting name")
    reject("comment-conflict-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad68", "plate_comment": "Conflicting comment"}]}, "Conflicting plate_comment")
    reject("signature-conflict-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad68", "signature": "int ReSmokeHwInit(int arg)"}]}, "Conflicting signature")
    reject("type-conflict-rejected", {"version": 1, "sha256": sha,
            "types": [{"name": "ReSmokeU32", "declaration": "typedef unsigned short ReSmokeU32;"}]}, "Conflicting shared type")
    reject("duplicate-anchor-rollback", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad68", "name": "ReSmokeRollback", "expect": {"name": "ReSmokeHwInit"}},
                          {"address": "0x1ad68", "name": "ReSmokeDuplicate"}]}, "Conflicting duplicate")
    reject("unsupported-field-rejected", {"version": 1, "sha256": sha,
            "functions": [{"address": "0x1ad68", "local_variables": []}]}, "Unsupported annotation field")
    check("tooling_sources_unchanged_during_proof", {name: tool.digest(tool.HERE / name) for name in sources} == source_hashes)
    check("all_original_pinned_hashes_unchanged", {b["sha256"]: b for b in tool.pinned()} == original)
    check("baseline_unchanged", tree_hashes(tool.BASE) == baseline_before)
    tool.unlocked(tool.BASE); tool.unlocked(a); tool.unlocked(b)
    check("baseline_and_private_projects_closed_unlocked", True)
    evidence["pinned_inputs_after"] = [b["sha256"] for b in tool.pinned()]
    evidence["baseline_files"] = baseline_before
    evidence["status"] = "passed"
    tool.save(out / "evidence.json", evidence)
    print(f"PASS: {len(evidence['checks'])} checks; {out / 'evidence.json'}")


if __name__ == "__main__":
    main()
