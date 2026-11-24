#!/usr/bin/env python3
"""Create or apply UPS patches (byuu's format, as used for HnS releases).

    ups.py create BASE.gba MODIFIED.gba OUT.ups
    ups.py apply  BASE.gba PATCH.ups OUT.gba

Standard library only. Output is compatible with Rom Patcher JS, Flips, etc.
"""
import sys
import zlib

MAGIC = b"UPS1"


def _enc(n):
    out = bytearray()
    while True:
        x = n & 0x7F
        n >>= 7
        if n == 0:
            out.append(0x80 | x)
            return bytes(out)
        out.append(x)
        n -= 1


def _dec(buf, pos):
    data, shift = 0, 1
    while True:
        x = buf[pos]
        pos += 1
        data += (x & 0x7F) * shift
        if x & 0x80:
            return data, pos
        shift <<= 7
        data += shift


def _crc(b):
    return zlib.crc32(b) & 0xFFFFFFFF


def create(src, dst):
    out = bytearray(MAGIC)
    out += _enc(len(src)) + _enc(len(dst))
    n, i, last = len(dst), 0, 0
    while i < n:
        s = src[i] if i < len(src) else 0
        if s == dst[i]:
            i += 1
            continue
        out += _enc(i - last)
        while i < n:
            s = src[i] if i < len(src) else 0
            x = s ^ dst[i]
            if x == 0:
                break
            out.append(x)
            i += 1
        out.append(0)
        i += 1
        last = i
    out += _crc(src).to_bytes(4, "little") + _crc(dst).to_bytes(4, "little")
    out += _crc(out).to_bytes(4, "little")
    return bytes(out)


def apply(src, patch):
    if patch[:4] != MAGIC:
        raise ValueError("not a UPS patch")
    if _crc(patch[:-4]) != int.from_bytes(patch[-4:], "little"):
        raise ValueError("patch CRC mismatch (corrupt patch)")
    in_crc = int.from_bytes(patch[-12:-8], "little")
    out_crc = int.from_bytes(patch[-8:-4], "little")
    if _crc(src) != in_crc:
        raise ValueError("base ROM CRC mismatch: use an unmodified Pokemon - Emerald Version (U)")
    pos = 4
    in_size, pos = _dec(patch, pos)
    out_size, pos = _dec(patch, pos)
    dst = bytearray(src[:out_size].ljust(out_size, b"\0"))
    i, end = 0, len(patch) - 12
    while pos < end:
        skip, pos = _dec(patch, pos)
        i += skip
        while True:
            x = patch[pos]
            pos += 1
            if x == 0:
                i += 1
                break
            if i < out_size:
                dst[i] ^= x
            i += 1
    if _crc(dst) != out_crc:
        raise ValueError("output CRC mismatch")
    return bytes(dst)


def main(argv):
    if len(argv) != 5 or argv[1] not in ("create", "apply"):
        print(__doc__.strip(), file=sys.stderr)
        return 2
    a = open(argv[2], "rb").read()
    b = open(argv[3], "rb").read()
    result = create(a, b) if argv[1] == "create" else apply(a, b)
    if argv[1] == "create":
        # Always prove the patch round-trips before writing it.
        if apply(a, result) != b:
            raise SystemExit("internal error: patch does not reproduce the target ROM")
    open(argv[4], "wb").write(result)
    print(f"{argv[1]}: wrote {argv[4]} ({len(result):,} bytes)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
