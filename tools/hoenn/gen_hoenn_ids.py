#!/usr/bin/env python3
"""Give Hoenn's Emerald flags, vars and trainers their own IDs in the HnS build.

    python3 tools/hoenn/gen_hoenn_ids.py

Why: in HnS, the Emerald names used by Hoenn scripts are either #defined to 0
(no-ops), collapsed onto one shared ID (all hidden-item flags), or aliased onto
HnS's own Johto/Kanto slots (e.g. VAR_ROUTE121_STATE == VAR_NEWBARKTOWN_LABSTATE).
Emerald trainer constants index HnS's trainer table (a Johto trainer's team).

This script reads the kept Hoenn maps (data/hoenn/maps.json), resolves every
name with the real compiler (with the remap disabled), and writes:

  include/constants/hoenn_flags.h     #undef/#define for remapped flags
  include/constants/hoenn_vars.h      #undef/#define for remapped vars
  include/constants/hoenn_trainers.h  #undef/#define for Hoenn trainers + counts
  src/data/trainers_hoenn.party       the Emerald teams for those trainers
  data/hoenn/remap_report.json        what was remapped/kept and why

Storage (see include/constants/hoenn_layout.h): flags and vars live in
SaveBlock3 (gSaveBlock3Ptr->hoennFlags / hoennVars), reached through hooks in
GetFlagPointer / GetVarPointer.
"""
import glob
import json
import os
import re
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.dirname(__file__))
from resolve_consts import resolve  # noqa: E402

# Must match include/constants/hoenn_layout.h
HOENN_FLAGS_START = 0x1800
HOENN_FLAGS_COUNT = 0x3C0          # story/item/hidden flags (0x1BC0-0x1BFF: hand-defined, hoenn_custom.h)
HOENN_TRAINER_FLAGS_START = 0x1C00
HOENN_TRAINER_FLAGS_COUNT = 0x400
HOENN_VARS_START = 0x7000
HOENN_VARS_COUNT = 0x70           # 0x7070-0x707F: hand-defined, hoenn_custom.h
HNS_TRAINERS = 653                 # TRAINERS_COUNT_HNS upstream; Hoenn trainers follow
HNS_MAX_TRAINERS = 864

# Flags that are genuinely the same thing in both regions: leave shared.
KEEP_FLAG_PREFIXES = ("FLAG_SYS_", "FLAG_BADGE0", "FLAG_RECEIVED_HM_", "FLAG_HIDE_MAP_NAME_POPUP", "FLAG_DONT_TRANSITION_MUSIC",
                      "FLAG_SAFE_FOLLOWER_MOVEMENT", "FLAG_FINITE_TMS", "FLAG_PENDING_DAYCARE_EGG",
                      "FLAG_ADVENTURE_STARTED", "FLAG_RECEIVED_BIKE")
# System flags HnS dropped (0 there) that Hoenn's braille puzzles need (2.0 part 12: the
# Sealed Chamber and Regi caves). src/braille_puzzles.c reads them too; the remap reaches C
# code because hoenn_flags.h is included at the end of flags.h.
REMAP_ZERO_SYS_FLAGS = {"FLAG_SYS_BRAILLE_DIG", "FLAG_SYS_REGIROCK_PUZZLE_COMPLETED",
                        "FLAG_SYS_REGISTEEL_PUZZLE_COMPLETED", "FLAG_SYS_BRAILLE_REGICE_COMPLETED"}
# Flags that are live in HnS but mean "this region's progress": give Hoenn its own.
FORCE_FLAG_PATTERNS = (r"^FLAG_HIDDEN_ITEM_",)
# Badges are NOT remapped: FLAG_BADGE01_GET etc. are the same names HnS uses for its own badges
# (and code does FLAG_BADGE01_GET + n). Hoenn gyms get stamp flags in their scripts instead (part 9).
SKIP_NAMES = {"TRAINER_BATTLE_CONTINUE_SCRIPT", "TRAINER_NONE"}
SKIP_TRAINER_PREFIXES = ("TRAINER_TYPE_", "TRAINER_PIC_", "TRAINER_CLASS_", "TRAINER_ENCOUNTER_MUSIC_", "TRAINER_BATTLE_")
IGNORE_PREFIXES = ("FLAG_TEMP_", "VAR_TEMP_", "VAR_OBJ_GFX_ID_", "VAR_0x8", "VAR_RESULT", "VAR_FACING",
                   "VAR_SPECIAL", "VAR_LAST_TALKED", "FLAG_HIDDEN_ITEMS_START")


def rd(p):
    with open(os.path.join(ROOT, p), errors="ignore") as f:
        return f.read()


def scan(files, pat):
    out = set()
    for f in files:
        if os.path.exists(os.path.join(ROOT, f)):
            out |= set(re.findall(pat, rd(f)))
    return {n for n in out if not n.startswith(IGNORE_PREFIXES)}


def species_key(name):
    return re.sub(r"[^A-Z0-9]+", "_", name.upper()).strip("_")


def species_evolutions():
    """SPECIES_X -> first evolution target, from src/data/pokemon/species_info."""
    evo, cur = {}, None
    for path in sorted(glob.glob(os.path.join(ROOT, "src/data/pokemon/species_info/*.h"))):
        text = open(path).read()
        for m in re.finditer(r"^\s*\[SPECIES_(\w+)\]\s*=|\.evolutions\s*=\s*EVOLUTION\(\{EVO_\w+,[^,]*,\s*SPECIES_(\w+)", text, re.M):
            if m.group(1):
                cur = m.group(1)
            elif cur and cur not in evo:
                evo[cur] = m.group(2)
    return evo


def evolve_block(block, evo, iv):
    head, _, mons = block.partition("\n\n")
    out = []
    for mon in mons.strip("\n").split("\n\n"):
        lines = [l for l in mon.split("\n") if not l.startswith("- ")]
        lines = [f"IVs: {iv} HP / {iv} Atk / {iv} Def / {iv} SpA / {iv} SpD / {iv} Spe" if l.startswith("IVs:") else l for l in lines]
        first = lines[0]
        name, sep, item = first.partition(" @ ")
        key = species_key(name)
        while key in evo and evo[key] != key:
            key = evo[key]
        lines[0] = key.replace("_", " ").title().replace(" ", "-") + (sep + item if sep else "")
        out.append("\n".join(lines))
    return head + "\n\n" + "\n\n".join(out) + "\n"


def main():
    kept = json.load(open(os.path.join(ROOT, "data/hoenn/maps.json")))["items"]
    hoenn_files = [f"data/maps/{m}/{x}" for m in kept for x in ("scripts.inc", "map.json")]
    # Hoenn & Seek's own scripts (part 16: they start battles with Emerald trainer IDs too).
    hoenn_files += sorted(os.path.relpath(p, ROOT) for p in glob.glob(os.path.join(ROOT, "data/scripts/hoenn_*.inc"))
                          if not p.endswith("hoenn_new_game.inc"))
    hns_maps = [os.path.relpath(os.path.dirname(p), ROOT) for p in glob.glob(os.path.join(ROOT, "data/maps/*/map.json"))
                if json.load(open(p)).get("game_version") == "hns"]
    hns_map_files = [f"{d}/{x}" for d in hns_maps for x in ("scripts.inc", "map.json")]

    # FLAG_HOENN_* / VAR_HOENN_* are hand-defined in constants/hoenn_custom.h.
    flags = {n for n in scan(hoenn_files, r"\bFLAG_[A-Z0-9_]+\b") if not n.startswith("FLAG_HOENN_")}
    vars_ = {n for n in scan(hoenn_files, r"\bVAR_[A-Z0-9_]+\b") if not n.startswith("VAR_HOENN_")}
    trainers = {t for t in scan(hoenn_files, r"\bTRAINER_[A-Z0-9_]+\b") if not t.endswith("_HNS") and not t.startswith(SKIP_TRAINER_PREFIXES)} - SKIP_NAMES

    hns_var_owned = set(re.findall(r"^#define\s+(VAR_\w+)", rd("include/constants/vars_hns.h"), re.M))
    hns_flag_text = rd("include/constants/flags_hns.h")
    hns_map_vars = scan(hns_map_files, r"\bVAR_[A-Z0-9_]+\b")

    # Resolve everything as HnS sees it today (remap disabled).
    all_hns_flags = set(re.findall(r"^#define\s+(FLAG_\w+)\s", hns_flag_text, re.M))
    all_vars = set(re.findall(r"^#define\s+(VAR_\w+)\s", rd("include/constants/vars.h") + rd("include/constants/vars_hns.h"), re.M))
    vals = resolve(flags | vars_ | trainers | all_hns_flags | all_vars, ("POKEMON_HNS", "HOENN_NO_REMAP"))

    def ids_to_names(names):
        d = {}
        for n in names:
            if vals.get(n):
                d.setdefault(vals[n], set()).add(n)
        return d
    flag_ids = ids_to_names(all_hns_flags)
    var_ids = ids_to_names(all_vars)

    report = {"flags": {}, "vars": {}, "trainers": {}}

    # ---- flags
    remap_flags = []
    for n in sorted(flags):
        v = vals.get(n)
        if v is None:
            report["flags"][n] = "undefined in HnS (left alone)"
            continue
        # FLAG_RECEIVED_HM_{FLY,DIVE,WATERFALL} are defined as 0 in HnS (unused there): give Hoenn real ones.
        if n.startswith(KEEP_FLAG_PREFIXES) and not (n.startswith("FLAG_RECEIVED_HM_") and v == 0) \
                and not (n in REMAP_ZERO_SYS_FLAGS and v == 0):
            report["flags"][n] = f"shared system flag {hex(v)}"
            continue
        forced = any(re.search(p, n) for p in FORCE_FLAG_PATTERNS)
        aliased = v and len(flag_ids.get(v, ())) > 1
        if v == 0 or forced or aliased:
            remap_flags.append(n)
            report["flags"][n] = "remapped: " + ("was 0 (no-op)" if v == 0 else "region progress" if forced else f"shared ID {hex(v)} with {sorted(flag_ids[v] - {n})[:2]}")
        else:
            report["flags"][n] = f"kept {hex(v)}"
    # hidden-item flags first: their offset from FLAG_HIDDEN_ITEMS_START must fit 13 bits
    remap_flags.sort(key=lambda n: (not n.startswith("FLAG_HIDDEN_ITEM_"), n))
    if len(remap_flags) > HOENN_FLAGS_COUNT:
        sys.exit(f"too many Hoenn flags: {len(remap_flags)} > {HOENN_FLAGS_COUNT}")

    # ---- vars
    remap_vars = []
    for n in sorted(vars_):
        v = vals.get(n)
        others = sorted(var_ids.get(v, set()) - {n}) if v else []
        if n in hns_var_owned or n in hns_map_vars:
            report["vars"][n] = f"kept: HnS owns or uses this name ({hex(v) if v else v})"
        elif any(o == n + "_UNSAFE" for o in others):
            report["vars"][n] = f"kept: engine var HnS deliberately shares ({hex(v)})"
        else:
            remap_vars.append(n)
            report["vars"][n] = "remapped: " + (f"aliased onto {others[:2]}" if others else f"Emerald-only slot {hex(v) if v else v}")
    if len(remap_vars) > HOENN_VARS_COUNT:
        sys.exit(f"too many Hoenn vars: {len(remap_vars)} > {HOENN_VARS_COUNT}")

    # ---- trainers
    party = rd("src/data/trainers.party")
    blocks = {}
    for m in re.finditer(r"^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)", party, re.M | re.S):
        blocks[m.group(1)] = m.group(0)
    # Part 14: trainers curated out (NPCs, fake fights, unreachable story trainers) get no ID.
    roles_path = os.path.join(ROOT, "data/hoenn/trainer_roles.json")
    if os.path.exists(roles_path):
        trainers -= set(json.load(open(roles_path))["exclude"])
        # Part 16c: phone trainers' rematch teams (the last Emerald tier) get IDs too.
        trainers |= set(json.load(open(roles_path)).get("rematch", {}).values())
    # Part 14: data/hoenn/trainer_parties.party replaces Emerald teams. A block's lines
    # before the first blank line replace those header keys; the rest replaces the Pokemon.
    over_path = os.path.join(ROOT, "data/hoenn/trainer_parties.party")
    if os.path.exists(over_path):
        for m in re.finditer(r"^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)", rd("data/hoenn/trainer_parties.party"), re.M | re.S):
            name, body = m.group(1), m.group(2).strip("\n")
            if name not in blocks:
                sys.exit(f"trainer_parties.party: unknown trainer {name}")
            o_head, _, o_mons = body.partition("\n\n")
            head, _, mons = blocks[name].partition("\n\n")
            head_lines = head.split("\n")
            for line in o_head.split("\n"):
                key = line.split(":", 1)[0] + ":"
                idx = [i for i, l in enumerate(head_lines) if l.startswith(key)]
                if idx:
                    head_lines[idx[0]] = line
                else:
                    head_lines.append(line)
            blocks[name] = "\n".join(head_lines) + "\n\n" + (o_mons.strip("\n") or mons.strip("\n")) + "\n"
    # Part 14: hopeful/strong route trainers are scaled to Lv 54-72 in-game, so evolve
    # their Pokemon fully and drop Emerald's movesets (level-up moves come from the new level).
    if os.path.exists(roles_path):
        roles = json.load(open(roles_path))["roles"]
        overridden = set(re.findall(r"^=== (TRAINER_\w+) ===", rd("data/hoenn/trainer_parties.party"), re.M)) if os.path.exists(over_path) else set()
        evo = species_evolutions()
        for t, r in roles.items():
            if r in ("hopeful", "strong") and t in blocks and t not in overridden:
                blocks[t] = evolve_block(blocks[t], evo, 24 if r == "strong" else 12)
        for t in json.load(open(roles_path)).get("rematch", {}).values():
            if t in blocks and t not in overridden:
                blocks[t] = evolve_block(blocks[t], evo, 28)
    missing = sorted(t for t in trainers if t not in blocks)
    if missing:
        sys.exit(f"Hoenn scripts reference trainers with no Emerald party data: {missing}")
    hoenn_trainers = sorted(trainers)
    if len(hoenn_trainers) > HOENN_TRAINER_FLAGS_COUNT:
        sys.exit("too many Hoenn trainers for the trainer flag block")
    trainers_count = HNS_TRAINERS + len(hoenn_trainers)
    max_trainers = max(HNS_MAX_TRAINERS, (trainers_count + 7) // 8 * 8)
    for i, t in enumerate(hoenn_trainers):
        report["trainers"][t] = HNS_TRAINERS + i

    # ---- write headers
    gen = "// Generated by tools/hoenn/gen_hoenn_ids.py from data/hoenn/maps.json. Do not edit.\n"

    def header(guard, body):
        return (f"#ifndef {guard}\n#define {guard}\n{gen}// Hoenn & Seek: give Hoenn its own IDs. Disabled by HOENN_NO_REMAP (used by the generator).\n"
                "// IS_HNS must be known here: config/randomizer.h includes constants/vars.h before\n"
                "// constants/global.h in the .s files, and the include guard would then skip the remap.\n"
                "#include \"constants/global.h\"\n"
                f"#if IS_HNS && !defined(HOENN_NO_REMAP)\n{body}#endif\n#endif // {guard}\n")

    fb = "".join(f"#undef {n}\n#define {n} 0x{HOENN_FLAGS_START + i:X}\n" for i, n in enumerate(remap_flags))
    fb += f"#define HOENN_FLAGS_USED {len(remap_flags)}\n"
    vb = "".join(f"#undef {n}\n#define {n} 0x{HOENN_VARS_START + i:X}\n" for i, n in enumerate(remap_vars))
    vb += f"#define HOENN_VARS_USED {len(remap_vars)}\n"
    tb = "".join(f"#undef {t}\n#define {t} {HNS_TRAINERS + i}\n" for i, t in enumerate(hoenn_trainers))
    tb += (f"#define HOENN_TRAINERS_START {HNS_TRAINERS}\n"
           f"#undef TRAINERS_COUNT_HNS\n#define TRAINERS_COUNT_HNS {trainers_count}\n"
           f"#undef MAX_TRAINERS_COUNT_HNS\n#define MAX_TRAINERS_COUNT_HNS {max_trainers}\n")
    for path, guard, body in (("include/constants/hoenn_flags.h", "GUARD_CONSTANTS_HOENN_FLAGS_H", fb),
                              ("include/constants/hoenn_vars.h", "GUARD_CONSTANTS_HOENN_VARS_H", vb),
                              ("include/constants/hoenn_trainers.h", "GUARD_CONSTANTS_HOENN_TRAINERS_H", tb)):
        with open(os.path.join(ROOT, path), "w") as f:
            f.write(header(guard, body))

    with open(os.path.join(ROOT, "src/data/trainers_hoenn.party"), "w") as f:
        f.write("".join(blocks[t].rstrip("\n") + "\n\n" for t in hoenn_trainers))
    with open(os.path.join(ROOT, "data/hoenn/remap_report.json"), "w") as f:
        json.dump(report, f, indent=1, sort_keys=True)
        f.write("\n")

    kept_flags = sum(1 for v in report["flags"].values() if not v.startswith("remapped"))
    print(f"flags: {len(remap_flags)} remapped, {kept_flags} kept shared")
    print(f"vars:  {len(remap_vars)} remapped, {len(vars_) - len(remap_vars)} kept shared")
    print(f"trainers: {len(hoenn_trainers)} Hoenn trainers -> IDs {HNS_TRAINERS}..{trainers_count - 1}; "
          f"TRAINERS_COUNT_HNS={trainers_count}, MAX_TRAINERS_COUNT_HNS={max_trainers}")


if __name__ == "__main__":
    main()
