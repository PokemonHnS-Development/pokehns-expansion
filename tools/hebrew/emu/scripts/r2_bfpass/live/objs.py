def objs():
    base = emu.sym("gObjectEvents")
    out = []
    for i in range(16):
        b = emu.read(base + 0x24 * i, 0x24)
        if not (b[0] & 1):
            continue
        gfx = int.from_bytes(b[4:6], "little")
        x = int.from_bytes(b[0x10:0x12], "little", signed=True) - 7
        y = int.from_bytes(b[0x12:0x14], "little", signed=True) - 7
        out.append((i, b[8], hex(gfx), b[7], x, y, b[0x18] & 0xF))
    print("objs (slot, localId, gfx, trainerType, x, y, facing):", out)
