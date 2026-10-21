#!/usr/bin/env python3
"""Original ELF/hash checks for the bounded native route. Not runtime or semantic validation."""
import hashlib
import json
from pathlib import Path
import struct
from replay import HERE, ROOT, ENTRIES

REL = 'binaries/4.3.5_1612/opt/rockrobo/cleaner/lib/librrnavdrv.so'
SHA = '603a3b2f23034592569b5f4ab761a19bdbf5e51699805dea031def9453891475'

def offset(data, va, size, executable=False):
    assert data[:6] == b'\x7fELF\x01\x01'
    ph = struct.unpack_from('<I', data, 28)[0]
    width, count = struct.unpack_from('<HH', data, 42)
    matches = []
    for i in range(count):
        kind, off, start, _, filesz, _, flags, _ = struct.unpack_from('<8I', data, ph+i*width)
        if kind == 1 and (not executable or flags & 1) and start <= va and va+size <= start+filesz:
            matches.append(off+va-start)
    assert len(matches) == 1, (hex(va), size, matches)
    return matches[0]

def read(data, va, size):
    off = offset(data,va,size)
    return data[off:off+size]

def word(data, va):
    return struct.unpack('<I',read(data,va,4))[0]

def check_instruction(data,row):
    va=int(row['address'],16);raw=bytes.fromhex(row['bytes'])
    assert va%2 == 0
    off=offset(data,va,len(raw),True)
    assert data[off:off+len(raw)] == raw

def elf_evidence(data):
    # Independent PREL31 decoding of original ELF EHABI starts.
    ph=struct.unpack_from('<I',data,28)[0];width,count=struct.unpack_from('<HH',data,42)
    exidx=[struct.unpack_from('<8I',data,ph+i*width) for i in range(count)]
    exidx=next(p for p in exidx if p[0]==0x70000001)
    starts=[]
    for n in range(0,exidx[4],8):
        w=word(data,exidx[2]+n)&0x7fffffff
        starts.append(exidx[2]+n+(w-(1<<31) if w&(1<<30) else w))
    bounds=[]
    for a in [int(e,16) for e in ENTRIES]+[0x18e91c,0x190908]:
        i=starts.index(a);bounds.append({'entry':hex(a),'next_ehabi_start':hex(starts[i+1])})
    assert 0x683e0 not in starts
    mappings=[]
    for a in [0x2a31ec,0x2a31fc,0x2a3204,0x2a32c4,0x2a347c]:
        event,wire=struct.unpack('<II',read(data,a,8))
        mappings.append({'table_row':hex(a),'event':hex(event),'wire_id':hex(wire),'original_bytes':read(data,a,8).hex()})
    assert [(m['event'],m['wire_id']) for m in mappings] == [('0x52','0x3022302'),('0x54','0x2033203'),('0x55','0x2033204'),('0x70','0x1022106'),('0xb3','0x2033212')]
    signed=lambda a:struct.unpack('<i',read(data,a,4))[0]
    assert signed(0x18ed8c)+0x18ea10 == signed(0x18ed90)+0x18ea2a == 0x2a2f4c
    assert signed(0x18fe54)+0x18f20e == signed(0x18fe58)+0x18f22c == 0x2a2f4c
    callback_table=signed(0x6927c)+0x690ac+8
    assert callback_table == 0x304b78 and word(data,callback_table)==0x683e1
    return {'input':REL,'sha256':SHA,'table_base':'0x2a2f4c','rows':mappings,'ehabi_boundaries':bounds,
            'completion_pointer':{'va':hex(callback_table),'file_offset':hex(offset(data,callback_table,4)),
                                  'thumb_value':hex(word(data,callback_table)),
                                  'entry_status':'0x683e0 is not an EHABI start; no function created'},
            'request_channel':{'source':3,'destination':2,'index':3*17+2}}

def validate():
    data=(ROOT/REL).read_bytes();assert hashlib.sha256(data).hexdigest()==SHA
    records=json.loads((HERE/'selected.json').read_text());n=0
    assert [f['address'] for f in records]==ENTRIES
    for f in records:
        raw=(HERE/f['c_file']).read_bytes()
        assert hashlib.sha256(raw).hexdigest()==f['c_sha256']
        assert SHA.encode() in raw and b'Decompiled C, NOT recovered source' in raw
        for row in f['instructions']:check_instruction(data,row);n+=1
    listing=json.loads((HERE/'bounded.json').read_text());assert listing['sha256']==SHA
    for r in listing['ranges']:
        raw=bytes.fromhex(r['raw_bytes']);assert len(raw)==int(r['end'],16)-int(r['start'],16)+1
        assert read(data,int(r['start'],16),len(raw))==raw
        for row in r['instructions']:check_instruction(data,row);n+=1
    for row in listing['pseudo_thumb_linear_not_cfg']:check_instruction(data,row);n+=1
    assert json.loads((HERE/'elf-evidence.json').read_text())==elf_evidence(data)
    ins={i['address']:i['instruction'] for r in listing['ranges'] for i in r['instructions']}
    ins.update({i['address']:i['instruction'] for i in listing['pseudo_thumb_linear_not_cfg']})
    required={'0x0018e992':'movs r0,#0x2','0x0018e996':'blx 0x0003c320',
              '0x0018ea28':'ldr.w r7,[r3,r1,lsl #0x3]','0x0018ea34':'add.w r6,r2,#0xc',
              '0x000683ee':'cmp r2,#0x55','0x000683fe':'movs r3,#0x52','0x00068400':'movs r3,#0x70',
              '0x0006840a':'bl 0x00067ad0','0x00190c06':'blx 0x0003c444'}
    for a,s in required.items():assert ins[a]==s,(a,s)
    return {'status':'passed','binary_hashes':1,'generated_c_files':len(records),'instruction_byte_checks':n,
            'claim_anchor_checks':len(required),'elf_boundary_checks':6,
            'scope':'Static original-byte/hash/anchor consistency; no runtime safety or semantic proof.'}

if __name__=='__main__':print(json.dumps(validate(),indent=2))
