# Party Pokémon helpers for the harness (decrypt/encrypt BoxPokemon).
import struct
OFF = [[0,0,0,0,0,0,1,1,2,3,2,3,1,1,2,3,2,3,1,1,2,3,2,3],
       [1,1,2,3,2,3,0,0,0,0,0,0,2,3,1,1,3,2,2,3,1,1,3,2],
       [2,3,1,1,3,2,2,3,1,1,3,2,0,0,0,0,0,0,3,2,3,2,1,1],
       [3,2,3,2,1,1,3,2,3,2,1,1,3,2,3,2,1,1,0,0,0,0,0,0]]
SIZE = 100
def read_mon(e, state, slot):
    base = e.s('gPlayerParty') + slot * SIZE
    words = e.read_words(state, base, SIZE // 4)
    raw = bytearray(struct.pack('<25I', *words))
    pers, otid = struct.unpack_from('<II', raw, 0)
    key = pers ^ otid
    sec = bytearray(raw[32:80])
    for i in range(12):
        v = struct.unpack_from('<I', sec, i*4)[0] ^ key
        struct.pack_into('<I', sec, i*4, v)
    subs = {t: sec[OFF[t][pers % 24]*12:OFF[t][pers % 24]*12+12] for t in range(4)}
    return base, raw, sec, subs, pers, otid
def info(e, state, slot):
    base, raw, sec, subs, pers, otid = read_mon(e, state, slot)
    s0, s3 = subs[0], subs[3]
    species = struct.unpack_from('<H', s0, 0)[0] & 0x7ff
    item = struct.unpack_from('<H', s0, 2)[0] & 0x3ff
    friend = s0[9]
    w = struct.unpack_from('<I', s3, 8)[0]
    return dict(species=species, item=item, friendship=friend, abilityNum=(w >> 29) & 3)
def set_friendship(e, state_in, state_out, slot, val):
    base, raw, sec, subs, pers, otid = read_mon(e, state_in, slot)
    i0 = OFF[0][pers % 24] * 12
    sec[i0 + 9] = val
    chk = 0
    for i in range(12):
        v = struct.unpack_from('<I', sec, i*4)[0]
        chk += v + (v >> 16)
    chk &= 0xffff
    key = pers ^ otid
    cmds = [f"loadstate {state_in}", f"w16 {base+28:x} {chk}"]
    for i in range(12):
        v = struct.unpack_from('<I', sec, i*4)[0] ^ key
        cmds.append(f"w32 {base+32+i*4:x} {v}")
    cmds.append(f"savestate {state_out}")
    e.run(cmds)
    return state_out
def free_last_slot(e, state_in, state_out):
    base = e.s('gPlayerParty') + 5 * SIZE
    cmds = [f"loadstate {state_in}"] + [f"w32 {base+i*4:x} 0" for i in range(25)]
    cmds += [f"w8 {e.s('gPlayerPartyCount'):x} 5", f"savestate {state_out}"]
    e.run(cmds); return state_out
