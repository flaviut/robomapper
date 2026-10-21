#!/usr/bin/env python3
"""Bounded packaging and original-ELF checks for rr_loader; not a runtime safety check."""
import hashlib
import json
from pathlib import Path
import struct
from config_data import embedded, mapped, loads, CRYPTO
from import_export import HERE, ROOT, BINARY, SHA256

ENTRIES = ['0x'+format(x,'08x') for x in [0x15edc,0x16874,0x17038,0x170d8,0x17394,
    0x17e24,0x17fbc,0x180e4,0x181f0,0x187fc,0x1883c,0x188f8,0x18a68,0x18ad4,
    0x18c28,0x19058,0x19da8,0x19fa0,0x1d364]]


def digest(data):
    return hashlib.sha256(data).hexdigest()


def save(path, value):
    path.write_text(json.dumps(value,indent=2)+'\n')


def original_entries(data):
    shoff = struct.unpack_from('<I',data,32)[0]
    shsize, count = struct.unpack_from('<HH',data,46)
    sections = [struct.unpack_from('<10I',data,shoff+i*shsize) for i in range(count)]
    symbols = {}
    for section in sections:
        if section[1] != 11:  # SHT_DYNSYM only, original loader symbols
            continue
        strings = sections[section[6]]
        names = data[strings[4]:strings[4]+strings[5]]
        for offset in range(section[4],section[4]+section[5],section[9]):
            name, value, size, info, other, index = struct.unpack_from('<IIIBBH',data,offset)
            if info & 15 == 2 and index != 0:
                text = names[name:].split(b'\0')[0].decode()
                symbols.setdefault(value & ~1,[]).append({'name':text,'symbol_value':hex(value),'size':size})
    exidx = {}
    phoff = struct.unpack_from('<I',data,28)[0]
    phsize, count = struct.unpack_from('<HH',data,42)
    for i in range(count):
        p = struct.unpack_from('<8I',data,phoff+i*phsize)
        if p[0] != 0x70000001:
            continue
        for off in range(0,p[4],8):
            word = struct.unpack_from('<I',data,p[1]+off)[0] & 0x7fffffff
            delta = word-(1<<31) if word & (1<<30) else word
            entry = (p[2]+off+delta) & ~1
            exidx[entry] = {'table_va':hex(p[2]+off),'table_file_offset':hex(p[1]+off),
                            'bytes':data[p[1]+off:p[1]+off+8].hex()}
    return symbols, exidx


def verify_instruction(data, instruction):
    address = int(instruction['address'],16)
    if address & 1:
        raise ValueError('odd instruction VA')
    raw = bytes.fromhex(instruction['bytes'])
    if not raw or mapped(data,address,len(raw)) != raw:
        raise ValueError('instruction bytes differ')


def config_record():
    data, payload, key, nonce, aad, plaintext, config = embedded()
    common = [p['common'] for p in config['plugins']]
    plugins = []
    for index, item in enumerate(common):
        path = 'binaries/4.3.5_1612'+config['pluginsPath']+'/'+item['plugin']
        raw = (ROOT/path).read_bytes()
        symbols, _ = original_entries(raw)
        exports = [dict(address=hex(va),**symbol) for va, group in symbols.items() for symbol in group
                   if symbol['name'] == 'rr_load_plugin']
        plugins.append({'index':index,'common':item,'tracked_path':path,'sha256':digest(raw),
                        'rr_load_plugin_exports':exports})
    lib = Path(CRYPTO)
    import ctypes as C
    crypto = C.CDLL(CRYPTO)
    crypto.OpenSSL_version.argtypes = [C.c_int]
    crypto.OpenSSL_version.restype = C.c_char_p
    return {'classification':'Authenticated static decode of embedded default configuration; NOT active deployment',
        'program':BINARY,'sha256':SHA256,'host_crypto':{'path':CRYPTO,'sha256':digest(lib.read_bytes()),
        'version':crypto.OpenSSL_version(0).decode(),'architecture':'ELF64 little-endian x86_64'},
        'extract':{'pointer_va':'0x2f2f4','payload_va':'0x2f2f8','payload_file_offset':'0xf2f8',
        'length_va':'0x308ec','length_file_offset':'0x108ec','payload_size':len(payload),
        'key_source_vas':['0x1e304','0x1e314'],'key_combination':'16-byte XOR',
        'aad_va':'0x1e324','aad_size':8,'nonce_va':'0x1e32c','nonce_size':13,
        'tag_size':4,'cipher':'AES-128-CCM','tag_placement':'last four bytes',
        'ccm_authentication':'verified by native host EVP_DecryptUpdate return 1'},
        'payload_sha256':digest(payload),'plaintext_sha256':digest(plaintext),
        'config_keys':list(config),'debugLogLevel':config['debugLogLevel'],'pluginsPath':config['pluginsPath'],
        'plugins':plugins,'limits':['No full plaintext configuration is published.',
        'CCM authentication here corroborates extraction/algorithm consistency, not trusted-origin or runtime deployment.',
        'Plugin entry export presence is capability, not proof callback executes or finishes map writes.']}


def package(source, dest):
    dest.mkdir(parents=True)
    (dest/'c').mkdir()
    selected = json.loads((source/'selected.json').read_text())
    assert [f['address'] for f in selected] == ENTRIES
    for f in selected:
        raw = (source/f['c_file']).read_bytes()
        (dest/'c'/f['c_file']).write_bytes(raw)
        f['c_sha256'] = digest(raw)
        f['c_file'] = 'c/'+f['c_file']
    save(dest/'selected.json',selected)
    data = (ROOT/BINARY).read_bytes()
    symbols, exidx = original_entries(data)
    save(dest/'elf-evidence.json',{'program':BINARY,'sha256':SHA256,
        'pt_loads':[{'file_offset':hex(p[1]),'va':hex(p[2]),'file_size':hex(p[4]),'memory_size':hex(p[5]),'flags':p[6]} for p in loads(data)],
        'entries':[{'address':f['address'],'symbols':symbols.get(int(f['address'],16),[]),
            'exidx':exidx.get(int(f['address'],16))} for f in selected],
        'signal_table':{'va':'0x2f1c8','file_offset':'0xf1c8','record_size':16,
            'first_record_bytes':mapped(data,0x2f1c8,16).hex(),'first_signal':1,'thumb_handler_pointer':'0x18ad5'},
        'strings':[{'va':hex(va),'text':mapped(data,va,size).decode().rstrip('\0')} for va,size in
            [(0x1d6e4,8),(0x1d8c0,12),(0x1df8c,5),(0x1df3c,15),(0x1d8e4,2)]],
        'unrecovered_thread':{'ehabi':exidx[0x18314],'next_ehabi':exidx[0x18448],
            'qualification':'Pseudo decode only; no function creation or recovered CFG claim.'}})
    save(dest/'configuration.json',config_record())


def validate(root=HERE/'proof'):
    data = (ROOT/BINARY).read_bytes()
    assert digest(data) == SHA256
    selected = json.loads((root/'selected.json').read_text())
    assert [f['address'] for f in selected] == ENTRIES
    symbols, exidx = original_entries(data)
    count = 0
    for f in selected:
        entry = int(f['address'],16)
        assert entry & 1 == 0 and f['thumb_mode'] == 1
        assert entry in symbols or entry in exidx, 'original ELF entry boundary required'
        assert f['entry_file_offsets'] == [next(p[1]+entry-p[2] for p in loads(data) if p[2]<=entry<p[2]+p[4])]
        raw = (root/f['c_file']).read_bytes()
        assert digest(raw) == f['c_sha256'] and b'Decompiled C, NOT recovered source' in raw
        for instruction in f['instructions']:
            verify_instruction(data,instruction)
            count += 1
    assert json.loads((root/'configuration.json').read_text()) == config_record()
    elf = json.loads((root/'elf-evidence.json').read_text())
    assert elf['sha256'] == SHA256 and elf['program'] == BINARY
    assert elf['entries'] == [{'address':f['address'],'symbols':symbols.get(int(f['address'],16),[]),
        'exidx':exidx.get(int(f['address'],16))} for f in selected]
    assert elf['pt_loads'] == [{'file_offset':hex(p[1]),'va':hex(p[2]),'file_size':hex(p[4]),
        'memory_size':hex(p[5]),'flags':p[6]} for p in loads(data)]
    for row in elf['strings']:
        expected = row['text'].encode()+b'\0'
        assert mapped(data,int(row['va'],16),len(expected)) == expected
    assert elf['unrecovered_thread']['ehabi'] == exidx[0x18314]
    assert elf['unrecovered_thread']['next_ehabi'] == exidx[0x18448]
    assert elf['signal_table']['first_record_bytes'] == mapped(data,0x2f1c8,16).hex()
    assert struct.unpack('<4I',mapped(data,0x2f1c8,16)) == (1,0x1ddf0,0x1ddf8,0x18ad5)
    thread = json.loads((root/'thread.json').read_text())
    for instruction in thread['instructions']:
        verify_instruction(data,instruction)
    claims = json.loads((HERE/'claims.json').read_text())
    assert claims['sha256'] == SHA256
    anchors = {i['address'] for f in selected for i in f['instructions']}
    for claim in claims['claims']:
        assert set(claim['instruction_anchors']) <= anchors, claim['id']
    print(f'PASS: {len(selected)} original-ELF function entries, {count} selected instruction records, {len(thread["instructions"])} pseudo records, authenticated default config and seven plugin identities')
    return {'status':'passed','selected_functions':len(selected),'instruction_records':count,
            'pseudo_records':len(thread['instructions']),'configuration':'authenticated embedded default; deployment unproved'}


if __name__ == '__main__':
    validate()
