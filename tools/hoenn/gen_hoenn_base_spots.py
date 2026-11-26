#!/usr/bin/env python3
"""Hoenn & Seek (2.0 parts 12 and 12b): secret bases at the reopened legendary sites.

Reads data/hoenn/base_spots.json.

"chambers" (part 12b) are new base groups, appended after Emerald's 24 (IDs 240+). For each:
  * a secondary tileset data/tilesets/secondary/secret_base/<name>_hoenn/: the tiles of an
    existing cave base ("from") and its palettes, with palette 6's floor (2-5), wall (6-9)
    and outline (1) colours replaced. All cave bases share one set of metatiles, so only the
    colours (and the source's texture) change. Declared in src/data/tilesets/hoenn_tilesets.h
    (included at the end of src/tilesets.c).
  * a layout (a copy of the template base's blocks) and a map (the template's map.json with
    the new ids), appended to layouts.json and to gMapGroup_IndoorDynamic, where every base
    map must live (secret_base.c warps into MAP_GROUP(MAP_SECRET_BASE_RED_CAVE1)).
  * defines in include/constants/hoenn_secret_bases.h: the group, its first ID, the row for
    sSecretBaseEntrancePositions and the map-number check CurMapIsSecretBase() needs (the
    new maps come after SHRUB4 in the group).

"spots" are entrances. For each:
  * the General tileset's closed cave indent (METATILE_General_<Colour>CaveIndent) is written
    into the map's layout .bin at x,y, with collision 1 and elevation 0 (what Emerald's own
    spots use), so Secret Power (MetatileBehavior_IsSecretBaseCave) accepts it and
    ToggleSecretBaseEntranceMetatile can open it;
  * a "secret_base" bg event is added on that tile (SetOccupiedSecretBaseEntranceMetatiles
    reopens the player's base from it on later visits);
  * SECRET_BASE_HOENN_<NAME> = the group's first ID rounded down to the tens + the variant.
    HOENN_IS_SITE_BASE(id) is true for every spot here (May's phone call uses it).

Re-runs give the same result.
"""
import json, os, re, shutil, struct

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
SB = "data/tilesets/secondary/secret_base"
EMERALD_GROUPS = 24  # SECRET_BASE_RED_CAVE1 .. SECRET_BASE_SHRUB4
BASE_MAP_GROUP = "gMapGroup_IndoorDynamic"

INDENT = {  # include/constants/metatile_labels.h
    "Red": 0x1A0,
    "Yellow": 0x1A8,
    "Blue": 0x1B0,
}


def load(path):
    return json.load(open(P(path)))


def save(path, data):
    with open(P(path), "w") as fh:
        json.dump(data, fh, indent=2, ensure_ascii=False)
        fh.write("\n")


def camel(name):
    return "".join(w.capitalize() for w in name.split("_"))


def group_base_ids():
    """SECRET_BASE_<GROUP>_1 -> its ID, from include/constants/secret_bases.h."""
    text = open(P("include/constants/secret_bases.h")).read()
    return {m.group(1): int(m.group(2)) for m in re.finditer(r"#define SECRET_BASE_(\w+)_1\s+(\d+)", text)}


def read_pal(path):
    return [tuple(int(c) for c in l.split()[:3]) for l in open(P(path)).read().split("\n")[3:19]]


def write_pal(path, colours):
    with open(P(path), "w", newline="") as fh:
        fh.write("JASC-PAL\r\n0100\r\n16\r\n" + "".join("%d %d %d\r\n" % tuple(c) for c in colours))


def build_chamber(ch, layouts, groups, tileset_defs):
    """Tileset, layout and map for one chamber base. Returns its header defines."""
    name, cam = ch["name"], camel(ch["name"])
    ts = ch["tileset"]
    ts_dir = f"{SB}/{name.lower()}_hoenn"
    os.makedirs(P(ts_dir, "palettes"), exist_ok=True)
    shutil.copyfile(P(SB, ts["from"], "tiles.png"), P(ts_dir, "tiles.png"))
    for i in range(16):
        pal = read_pal(f"{SB}/{ts['from']}/palettes/{i:02d}.pal")
        if i == 6:
            pal[1] = ts["outline"]
            pal[2:6] = ts["floor"]
            pal[6:10] = ts["wall"]
        write_pal(f"{ts_dir}/palettes/{i:02d}.pal", pal)
    sym = f"SecretBase{cam}Hoenn"
    tileset_defs.append(
        f"// {ch['name']} chamber base: {ts['from']} tiles, palette 6 recoloured (data/hoenn/base_spots.json).\n"
        f"const u32 gTilesetTiles_{sym}[] = INCBIN_U32(\"{ts_dir}/tiles.4bpp\");\n"
        f"const u16 gTilesetPalettes_{sym}[][16] =\n{{\n"
        + "".join(f"    INCBIN_U16(\"{ts_dir}/palettes/{i:02d}.gbapal\"),\n" for i in range(16))
        + "};\n"
        f"const struct Tileset gTileset_{sym} =\n{{\n"
        f"    .isCompressed = FALSE,\n    .isSecondary = TRUE,\n"
        f"    .tiles = gTilesetTiles_{sym},\n    .palettes = gTilesetPalettes_{sym},\n"
        f"    .metatiles = gMetatiles_SecretBaseSecondary,\n"
        f"    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,\n"
        f"    .callback = NULL,\n}};\n")

    # Layout: the template's blocks, our tileset.
    tmpl_map = load(f"data/maps/{ch['template']}/map.json")
    tmpl_lay = next(l for l in layouts["layouts"] if l.get("id") == tmpl_map["layout"])
    map_name = f"SecretBase_{cam}_hoenn"
    lay_id = f"LAYOUT_SECRET_BASE_{name}_HOENN"
    lay_dir = f"data/layouts/{map_name}"
    os.makedirs(P(lay_dir), exist_ok=True)
    shutil.copyfile(P(tmpl_lay["blockdata_filepath"]), P(lay_dir, "map.bin"))
    shutil.copyfile(P(tmpl_lay["border_filepath"]), P(lay_dir, "border.bin"))
    lay = dict(tmpl_lay, id=lay_id, name=f"{map_name}_Layout", secondary_tileset=f"gTileset_{sym}",
               border_filepath=f"{lay_dir}/border.bin", blockdata_filepath=f"{lay_dir}/map.bin",
               game_version="hns", layout_version="emerald")
    idx = next((i for i, l in enumerate(layouts["layouts"]) if l.get("id") == lay_id), None)
    if idx is None:
        layouts["layouts"].append(lay)
    else:
        layouts["layouts"][idx] = lay

    # Map: the template's map.json (decoration objects, record-mix trainer, exit warp).
    m = dict(tmpl_map, id=f"MAP_SECRET_BASE_{name}_HOENN", name=map_name, layout=lay_id, game_version="hns")
    os.makedirs(P("data/maps", map_name), exist_ok=True)
    save(f"data/maps/{map_name}/map.json", m)
    if map_name not in groups[BASE_MAP_GROUP]:
        groups[BASE_MAP_GROUP].append(map_name)

    group = f"SECRET_BASE_HOENN_GROUP_{name}"
    first = ch["group_index"] * 10 + 1
    assert ch["group_index"] >= EMERALD_GROUPS and first + 3 < 256, name  # variants 1-4 at most
    cx, cy = ch["computer"]
    return {
        "defines": [f"#define {group}_1 {first}", f"#define {group} SECRET_BASE_GROUP({ch['group_index']})"],
        "entrance": f"[{group}] = MAP_NUM(MAP_SECRET_BASE_{name}_HOENN), 0, {cx}, {cy},",
        "mapnum": f"(mapNum) == MAP_NUM(MAP_SECRET_BASE_{name}_HOENN)",
        "group": f"HOENN_{name}",
        "first": first,
    }


def place_spot(spot, base_id, const, layouts):
    mpath = f"data/maps/{spot['map']}/map.json"
    m = load(mpath)
    layout = next(l for l in layouts["layouts"] if l.get("id") == m["layout"])
    assert layout["primary_tileset"] == "gTileset_General", layout["id"]
    bin_path = P(layout["blockdata_filepath"])
    data = bytearray(open(bin_path, "rb").read())
    off = (spot["y"] * layout["width"] + spot["x"]) * 2
    struct.pack_into("<H", data, off, INDENT[spot["indent"]] | (1 << 10))  # collision 1, elevation 0
    open(bin_path, "wb").write(bytes(data))

    bgs = [b for b in m["bg_events"]
           if not (b["type"] == "secret_base" and b["x"] == spot["x"] and b["y"] == spot["y"])]
    bgs.append({"type": "secret_base", "x": spot["x"], "y": spot["y"], "elevation": 0, "secret_base_id": const})
    if bgs != m["bg_events"]:
        m["bg_events"] = bgs
        save(mpath, m)


def main():
    cfg = load("data/hoenn/base_spots.json")
    kept = set(load("data/hoenn/maps.json")["items"])
    layouts = load("data/layouts/layouts.json")
    groups = load("data/maps/map_groups.json")
    firsts = group_base_ids()

    chamber_defs, entrances, mapnums, tileset_defs = [], [], [], []
    for ch in cfg.get("chambers", []):
        c = build_chamber(ch, layouts, groups, tileset_defs)
        chamber_defs += c["defines"]
        entrances.append(c["entrance"])
        mapnums.append(c["mapnum"])
        firsts[c["group"]] = c["first"]
    assert [ch["group_index"] for ch in cfg.get("chambers", [])] == list(range(EMERALD_GROUPS, EMERALD_GROUPS + len(entrances)))

    spot_defs, site_ids = [], []
    for spot in cfg["spots"]:
        assert spot["map"] in kept, f"{spot['map']} is not a kept Hoenn map"
        base_id = firsts[spot["group"]] // 10 * 10 + spot["variant"]
        new_group = spot["group"].startswith("HOENN_")
        assert 0 < base_id < 256 and (new_group or 5 <= spot["variant"] <= 9), (spot["name"], base_id)
        const = f"SECRET_BASE_HOENN_{spot['name']}"
        spot_defs.append(f"#define {const} {base_id}  // {spot['group']}, variant {spot['variant']}: {spot['map']} ({spot['x']},{spot['y']})")
        site_ids.append(f"(id) == {const}")
        place_spot(spot, base_id, const, layouts)

    save("data/layouts/layouts.json", layouts)
    save("data/maps/map_groups.json", groups)

    with open(P("src/data/tilesets/hoenn_tilesets.h"), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_base_spots.py from data/hoenn/base_spots.json.\n")
        f.write("// Hoenn & Seek tilesets, included at the end of src/tilesets.c.\n\n")
        f.write("\n".join(tileset_defs))

    with open(P("include/constants/hoenn_secret_bases.h"), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_base_spots.py from data/hoenn/base_spots.json.\n")
        f.write("// Secret bases at Hoenn's reopened legendary sites (2.0 parts 12 and 12b).\n")
        f.write("// An ID is group * 10 + variant; Emerald's own spots use variants 1-4 of groups 0-23.\n")
        f.write("// Included by constants/secret_bases.h before NUM_SECRET_BASE_GROUPS.\n")
        f.write("#ifndef GUARD_CONSTANTS_HOENN_SECRET_BASES_H\n#define GUARD_CONSTANTS_HOENN_SECRET_BASES_H\n\n")
        f.write("// Chamber bases: new groups after SECRET_BASE_SHRUB4.\n")
        f.write("\n".join(chamber_defs) + "\n")
        f.write(f"#define HOENN_SECRET_BASE_GROUP_COUNT {len(entrances)}\n\n")
        f.write("// Rows for sSecretBaseEntrancePositions (map number, warp, PC x, PC y).\n")
        f.write("#define HOENN_SECRET_BASE_ENTRANCE_POSITIONS \\\n" + "".join(f"    {e} \\\n" for e in entrances) + "\n")
        f.write("// TRUE for a chamber base's map number (in the secret base map group).\n")
        f.write("#define HOENN_IS_CHAMBER_BASE_MAP_NUM(mapNum) (" + (" || ".join(mapnums) or "FALSE") + ")\n\n")
        f.write("// Entrance spots.\n" + "\n".join(spot_defs) + "\n\n")
        f.write("// TRUE for a base at one of the sites.\n")
        f.write("#define HOENN_IS_SITE_BASE(id) (" + " \\\n                             || ".join(site_ids) + ")\n\n#endif\n")
    print(f"{len(entrances)} chamber bases, {len(spot_defs)} spots")


if __name__ == "__main__":
    main()
