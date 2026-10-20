#!/usr/bin/env python3
"""Copy vendor ELF files, library aliases and MCU payloads from an unpacked rootfs."""

import argparse
import hashlib
import json
import shutil
from pathlib import Path


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def select(source):
    vendor = source / "opt/rockrobo"
    if not vendor.is_dir():
        raise ValueError(f"Missing vendor tree: {vendor}")

    selected = []
    for path in sorted(vendor.rglob("*")):
        if not path.is_file():
            continue

        with path.open("rb") as stream:
            magic = stream.read(4)

        if magic == b"\x7fELF":
            selected.append((path, "elf"))
            continue

        if path.parent == vendor / "firmware/img" and path.suffix == ".bin":
            selected.append((path, "mcu-firmware"))

    if not selected:
        raise ValueError("No binaries found")

    # Keep library alias chains intact without copying targets outside the snapshot.
    paths = {path for path, _ in selected}
    for path, _ in selected:
        if not path.is_symlink():
            continue

        target = path.readlink()
        if target.is_absolute() or path.parent / target not in paths:
            raise ValueError(f"Alias target is outside the selected files: {path}")

    return selected


def extract(source, output, firmware):
    if source == output or source in output.parents or output in source.parents:
        raise ValueError("Source and output trees must be separate")

    selected = select(source)
    entries = []
    for path, kind in selected:
        rel = path.relative_to(source)
        dest = output / rel
        sha = digest(path)
        entry = {"path": rel.as_posix(), "kind": kind,
                 "size": path.stat().st_size, "sha256": sha}
        dest.parent.mkdir(parents=True, exist_ok=True)

        if path.is_symlink():
            target = path.readlink()
            entry["target"] = str(target)
            if dest.is_symlink():
                if dest.readlink() != target:
                    raise ValueError(f"Refusing to replace changed alias: {dest}")
            elif dest.exists():
                raise ValueError(f"Expected an alias: {dest}")
            else:
                dest.symlink_to(target)
        elif dest.exists() or dest.is_symlink():
            if dest.is_symlink() or digest(dest) != sha:
                raise ValueError(f"Refusing to replace changed binary: {dest}")
        else:
            shutil.copy2(path, dest)

        entries.append(entry)

    # Check aliases after all targets exist, including multi-hop SONAME chains.
    for entry in entries:
        if digest(output / entry["path"]) != entry["sha256"]:
            raise ValueError(f"Copy hash mismatch: {entry['path']}")

    manifest = {"firmware": firmware, "source": "unpacked rootfs",
                "scope": "Vendor ELF files and aliases under /opt/rockrobo; MCU payloads in firmware/img",
                "files": entries}
    text = json.dumps(manifest, indent=2) + "\n"
    manifest_path = output / "manifest.json"
    if manifest_path.exists() and manifest_path.read_text() != text:
        raise ValueError(f"Refusing to replace changed manifest: {manifest_path}")
    manifest_path.write_text(text)

    files = [entry for entry in entries if "target" not in entry]
    print(f"Verified {len(files)} files, {len(entries) - len(files)} aliases, "
          f"{sum(entry['size'] for entry in files)} bytes: {output}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path("analysis/rootfs"))
    parser.add_argument("--output", type=Path, default=Path("binaries/4.3.5_1612"))
    parser.add_argument("--firmware", default="4.3.5_1612")
    args = parser.parse_args()
    extract(args.source.resolve(), args.output.resolve(), args.firmware)


if __name__ == "__main__":
    main()
