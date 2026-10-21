#!/usr/bin/env python3
"""Decode embedded saved data with host OpenSSL EVP, never execute firmware code.

The ciphertext/key/nonce/AAD coordinates and CCM parameters are instruction-derived
from rr_unpacking: 0x1d372..0x1d3da. No MCU image is selected or accessed.
"""
import ctypes as C
import hashlib
import json
import platform
from pathlib import Path
import struct
from import_export import ROOT, BINARY, SHA256

CRYPTO = '/nix/store/14cfdqp8w2iw188vhjfaz2wg8pzbghp3-openssl-3.6.3/lib/libcrypto.so.3'
CRYPTO_SHA256 = '8918f69f4b445a460d7ec594aa5bfcbecaf898d335683b7468312c28cc2f2f8c'


def loads(data):
    phoff = struct.unpack_from('<I', data, 28)[0]
    size, count = struct.unpack_from('<HH', data, 42)
    return [p for i in range(count) if (p := struct.unpack_from('<8I', data, phoff+i*size))[0] == 1]


def mapped(data, address, size):
    matches = [p for p in loads(data) if p[2] <= address and address+size <= p[2]+p[4]]
    if len(matches) != 1:
        raise ValueError('unmapped or ambiguous VA')
    p = matches[0]
    offset = p[1]+address-p[2]
    return data[offset:offset+size]


def ccm_decrypt(ciphertext, tag, key, nonce, aad):
    library = Path(CRYPTO).read_bytes()
    assert hashlib.sha256(library).hexdigest() == CRYPTO_SHA256, 'native host crypto identity mismatch'
    identity = library[:20]
    assert platform.machine() == 'x86_64'
    assert identity[:6] == b'\x7fELF\x02\x01' and struct.unpack_from('<H', identity, 18)[0] == 62, 'native host ELF64 only'
    lib = C.CDLL(CRYPTO)
    lib.EVP_CIPHER_CTX_new.restype = C.c_void_p
    lib.EVP_aes_128_ccm.restype = C.c_void_p
    lib.EVP_CIPHER_CTX_free.argtypes = [C.c_void_p]
    lib.EVP_DecryptInit_ex.argtypes = [C.c_void_p,C.c_void_p,C.c_void_p,C.c_void_p,C.c_void_p]
    lib.EVP_CIPHER_CTX_ctrl.argtypes = [C.c_void_p,C.c_int,C.c_int,C.c_void_p]
    lib.EVP_DecryptUpdate.argtypes = [C.c_void_p,C.c_void_p,C.POINTER(C.c_int),C.c_void_p,C.c_int]
    ctx = lib.EVP_CIPHER_CTX_new()
    def ok(value):
        if value != 1:
            raise ValueError('host CCM authentication/initialization rejected')
    try:
        ok(lib.EVP_DecryptInit_ex(ctx,lib.EVP_aes_128_ccm(),None,None,None))
        ok(lib.EVP_CIPHER_CTX_ctrl(ctx,9,len(nonce),None))
        ok(lib.EVP_CIPHER_CTX_ctrl(ctx,17,len(tag),C.c_char_p(tag)))
        ok(lib.EVP_DecryptInit_ex(ctx,None,None,C.c_char_p(key),C.c_char_p(nonce)))
        length = C.c_int()
        ok(lib.EVP_DecryptUpdate(ctx,None,C.byref(length),None,len(ciphertext)))
        ok(lib.EVP_DecryptUpdate(ctx,None,C.byref(length),C.c_char_p(aad),len(aad)))
        out = C.create_string_buffer(len(ciphertext))
        ok(lib.EVP_DecryptUpdate(ctx,out,C.byref(length),C.c_char_p(ciphertext),len(ciphertext)))
        return out.raw[:length.value]
    finally:
        lib.EVP_CIPHER_CTX_free(ctx)


def embedded():
    data = (ROOT/BINARY).read_bytes()
    assert hashlib.sha256(data).hexdigest() == SHA256
    pointer = struct.unpack('<I',mapped(data,0x2f2f4,4))[0]
    length = struct.unpack('<I',mapped(data,0x308ec,4))[0]
    payload = mapped(data,pointer,length)
    key = bytes(a^b for a,b in zip(mapped(data,0x1e304,16),mapped(data,0x1e314,16)))
    nonce_va = struct.unpack('<I',mapped(data,0x1d410,4))[0]
    aad, nonce = mapped(data,nonce_va-8,8), mapped(data,nonce_va,13)
    plaintext = ccm_decrypt(payload[:-4],payload[-4:],key,nonce,aad)
    config = json.loads(plaintext)
    return data, payload, key, nonce, aad, plaintext, config


if __name__ == '__main__':
    _, payload, _, _, _, plaintext, config = embedded()
    # Publish only exact map-host-relevant config fields, not the entire embedded configuration.
    print(json.dumps({'ciphertext_and_tag_size':len(payload),'plaintext_sha256':hashlib.sha256(plaintext).hexdigest(),
        'config_keys':list(config),'pluginsPath':config.get('pluginsPath'),'plugins':[
            p.get('common') for p in config.get('plugins',[])]},indent=2))
