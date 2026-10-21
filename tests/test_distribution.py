"""Check the files HACS installs, including the robot executable."""

import json
from pathlib import Path
import unittest

_ROOT = Path(__file__).resolve().parents[1]
_COMPONENT = _ROOT / "custom_components" / "map_editor"


class DistributionTests(unittest.TestCase):
    def test_translations_match(self):
        self.assertEqual(json.loads((_COMPONENT / "strings.json").read_text()),
                         json.loads((_COMPONENT / "translations/en.json").read_text()))

    def test_hacs_layout(self):
        manifest = json.loads((_COMPONENT / "manifest.json").read_text())
        hacs = json.loads((_ROOT / "hacs.json").read_text())
        self.assertEqual(manifest["domain"], _COMPONENT.name)
        self.assertEqual(manifest["name"], hacs["name"])
        self.assertTrue(manifest["config_flow"])
        self.assertNotIn("mqtt", manifest["dependencies"])
        for path in ("frontend/panel.js", "frontend/panel.css", "tools/save.sh", "tools/map-maint"):
            self.assertTrue((_COMPONENT / path).is_file())


if __name__ == "__main__":
    unittest.main()
