#!/usr/bin/env python3
"""Compare saved Valetudo HTTP maps without treating new IDs/nonces as geometry."""
import argparse
import json
from pathlib import Path


def load(path):
    value = json.loads(Path(path).read_text())
    if value.get("__class") != "ValetudoMap":
        raise ValueError("Expected a ValetudoMap")
    if value.get("metaData", {}).get("defaultMap"):
        raise ValueError("Startup placeholder; wait for the real map")
    for key in ["size", "pixelSize", "layers", "entities"]:
        if key not in value:
            raise ValueError(f"Missing {key}")
    if not isinstance(value["layers"], list) or not value["layers"]:
        raise ValueError("Missing map layers")
    if not isinstance(value["entities"], list):
        raise ValueError("Expected map entities")
    return value


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("before")
    parser.add_argument("after")
    args = parser.parse_args()
    try:
        before, after = load(args.before), load(args.after)
    except (OSError, ValueError, AttributeError) as error:
        parser.exit(1, f"{error}\n")
    different = [key for key in ["size", "pixelSize", "layers", "entities"]
                 if before[key] != after[key]]
    if before.get("metaData", {}).get("version") != after.get("metaData", {}).get("version"):
        different.append("metaData.version")
    print(json.dumps({"match": not different, "different": different,
                      "layers": len(after["layers"]), "entities": len(after["entities"])}))
    return int(bool(different))


if __name__ == "__main__":
    raise SystemExit(main())
