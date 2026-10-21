"""Source-named rejection checks for the writer-host evidence validator."""
import copy
import json
import unittest
from config_data import embedded, ccm_decrypt, mapped
from evidence import HERE, original_entries, verify_instruction


class WriterHostEvidenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data, cls.payload, cls.key, cls.nonce, cls.aad, cls.plaintext, cls.config = embedded()
        cls.instruction = json.loads((HERE/'proof/selected.json').read_text())[0]['instructions'][0]

    def test_original_entry_and_instruction(self):
        symbols, exidx = original_entries(self.data)
        self.assertIn(0x15edc,symbols)
        self.assertIn(0x18ad4,exidx)
        verify_instruction(self.data,self.instruction)

    def test_changed_instruction_rejected(self):
        row = copy.deepcopy(self.instruction)
        row['bytes'] = '00'*len(bytes.fromhex(row['bytes']))
        with self.assertRaisesRegex(ValueError,'bytes differ'):
            verify_instruction(self.data,row)

    def test_odd_instruction_rejected(self):
        row = dict(self.instruction,address='0x15edd')
        with self.assertRaisesRegex(ValueError,'odd instruction'):
            verify_instruction(self.data,row)

    def test_unmapped_va_rejected(self):
        with self.assertRaisesRegex(ValueError,'unmapped'):
            mapped(self.data,0xdeadbeef,4)

    def test_changed_ciphertext_rejected(self):
        payload = bytearray(self.payload)
        payload[0] ^= 1
        with self.assertRaisesRegex(ValueError,'rejected'):
            ccm_decrypt(bytes(payload[:-4]),bytes(payload[-4:]),self.key,self.nonce,self.aad)

    def test_changed_tag_rejected(self):
        tag = bytearray(self.payload[-4:])
        tag[0] ^= 1
        with self.assertRaisesRegex(ValueError,'rejected'):
            ccm_decrypt(self.payload[:-4],bytes(tag),self.key,self.nonce,self.aad)

    def test_changed_aad_rejected(self):
        aad = bytes([self.aad[0]^1])+self.aad[1:]
        with self.assertRaisesRegex(ValueError,'rejected'):
            ccm_decrypt(self.payload[:-4],self.payload[-4:],self.key,self.nonce,aad)

    def test_authenticated_default_owner(self):
        self.assertEqual(self.config['pluginsPath'],'/opt/rockrobo/cleaner/lib')
        plugins = [p['common']['plugin'] for p in self.config['plugins']]
        self.assertEqual(plugins[4:6],['librrslamdrv.so','librrnavdrv.so'])


if __name__ == '__main__':
    unittest.main()
