#!/usr/bin/env python3
"""Hoenn & Seek 2.0 (parts 6a/6b): wild encounter tables for special-weather days.

Reads data/hoenn/weather_wild.json (rules; its comment explains them) and
data/hoenn/weather_cycles.json (which maps have which special weather), takes each
map's normal tables from data/hoenn/wild_encounters_hoenn.json (Hoenn) or
src/data/wild_encounters.json (Johto/Kanto), and writes:
  - data/hoenn/wild_encounters_weather.json: the weather tables, labelled
    <base>_<Weather>[_<Time>]. tools/wild_encounters/wild_encounters_to_header.py
    appends them after every other table, so each becomes a second
    WildPokemonHeader for its map, after the normal one. On the map's special day
    HoennWeatherWildHeader() (src/hoenn_time.c) picks that later header.
  - hoenn-docs/weather-tables.md: per map and table, the species' share before and
    after, for review.
Deterministic; re-run after changing wild tables, the cycle list or the rules.
"""
import copy, glob, json, os, re, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
P = lambda *a: os.path.join(ROOT, *a)
TIMES = ("Morning", "Day", "Evening", "Night")
RATES = {"land_mons": [20, 20, 10, 10, 10, 10, 5, 5, 4, 4, 1, 1], "water_mons": [60, 30, 5, 4, 1]}
KIND = {"land": "land_mons", "water": "water_mons"}


def species_data():
    """SPECIES_X -> set of TYPE_ names, and SPECIES_X -> (level, SPECIES_Y) level evolutions."""
    types, evo, cur = {}, {}, None
    pat = re.compile(r"^\s*\[(SPECIES_\w+)\]\s*=|\.types\s*=\s*MON_TYPES\(([^)]*)\)"
                     r"|\.evolutions\s*=\s*EVOLUTION\(\s*\{(EVO_\w+),\s*([^,]+),\s*(SPECIES_\w+)", re.M)
    for path in sorted(glob.glob(P("src/data/pokemon/species_info/*.h"))):
        for m in pat.finditer(open(path).read()):
            if m.group(1):
                cur = m.group(1)
            elif m.group(2) and cur and cur not in types:
                types[cur] = {t.strip()[5:] for t in m.group(2).split(",")}
            elif m.group(3) and cur and cur not in evo and m.group(3) == "EVO_LEVEL" and m.group(4).strip().isdigit():
                evo[cur] = (int(m.group(4)), m.group(5))
    return types, evo


TYPES, EVO = species_data()


def evolve(species, level):
    while species in EVO and EVO[species][0] <= level:
        species = EVO[species][1]
    return species


def split_label(label):
    for t in TIMES:
        if label.endswith("_" + t):
            return label[: -len(t) - 1], t
    return label, None


def factor(species, rule):
    """Weight multiplier: boosted types x2, suppressed x0.25, others x1 (boost wins)."""
    t = TYPES.get(species, set())
    if t & set(rule["boost"]):
        return 2.0
    if t & set(rule["suppress"]):
        return 0.25
    return 1.0


def reweight(table, kind, rule, fixed):
    """The weather copy of a table. The slots keep their rates and levels; `fixed`
    ({slot: species}) are placed first (weather-only extras, hand fixes). Every other
    slot goes, most common first, to the species furthest below its target share:
    its normal share x factor(), scaled so the targets fill the remaining slots.
    A species with a normal share of 5 % or more keeps at least one slot."""
    rates = RATES[kind]
    mons = table["mons"]
    base = {}
    for i, m in enumerate(mons):
        base[m["species"]] = base.get(m["species"], 0) + rates[i]
    free = [i for i in range(len(mons)) if i not in fixed]
    pool = sum(rates[i] for i in free)
    weight = {sp: share * factor(sp, rule) for sp, share in base.items()}
    total = sum(weight.values())
    target = {sp: w * pool / total for sp, w in weight.items()}
    got = {sp: 0 for sp in base}
    first = {}
    for i, m in enumerate(mons):
        first.setdefault(m["species"], i)
    out = copy.deepcopy(table)
    for i in sorted(free, key=lambda i: (-rates[i], i)):
        sp = max(base, key=lambda s: (target[s] - got[s], -first[s]))
        out["mons"][i]["species"] = sp
        got[sp] += rates[i]
    # Nothing with a real share (5 %+) disappears: it takes back the rarest free
    # slot of a species that has more than one.
    for sp in sorted(base, key=lambda s: first[s]):
        if base[sp] < 5 or got[sp]:
            continue
        for i in sorted(free, key=lambda i: (rates[i], -i)):
            owner = out["mons"][i]["species"]
            if sum(1 for j in free if out["mons"][j]["species"] == owner) > 1:
                out["mons"][i]["species"] = sp
                got[sp] += rates[i]
                got[owner] -= rates[i]
                break
    for i, sp in fixed.items():
        out["mons"][i]["species"] = evolve(sp, out["mons"][i]["min_level"])
    return out


def shares(table, kind):
    rates, out = RATES[kind], {}
    for i, m in enumerate(table["mons"]):
        n = m["species"][8:].title()
        out[n] = out.get(n, 0) + (rates[i] if i < len(rates) else 0)
    return out


def main():
    cfg = json.load(open(P("data/hoenn/weather_wild.json")))
    cycles = json.load(open(P("data/hoenn/weather_cycles.json")))["groups"]
    sources = {"hoenn": json.load(open(P("data/hoenn/wild_encounters_hoenn.json")))["encounters"],
               "hns": json.load(open(P("src/data/wild_encounters.json")))["wild_encounter_groups"][0]["encounters"]}
    out, report = [], ["# Weather encounter tables (generated)", "",
                       "Generated by `tools/hoenn/gen_hoenn_weather_wild.py` from `data/hoenn/weather_wild.json`. "
                       "For each map: the special weather, then per table the species' encounter share (%) on a normal day → on the special day. "
                       "**Bold** = only on the special day.", ""]
    for g in cycles:
        rule_name = g["weather"]
        rule = cfg["rules"][rule_name]
        base_rule = rule_name
        if "same_as" in rule:
            base_rule = rule["same_as"]
            rule = cfg["rules"][base_rule]
        for name in g["maps"]:
            region = "hns" if name.endswith("_hns") else "hoenn"
            if region not in cfg["regions"] and not (region == "hns" and "johto_kanto" in cfg["regions"]):
                continue
            fix = cfg["maps"].get(name, {})
            if fix.get("skip"):
                continue
            mid = json.load(open(P("data/maps", name, "map.json")))["id"]
            entries = [e for e in sources[region] if e.get("map") == mid]
            if not entries:
                continue
            extras = cfg["extras"].get("hoenn" if region == "hoenn" else "johto_kanto", {}).get(base_rule, {})
            report.append("## %s (%s)" % (name, rule["suffix"].lower()))
            for e in entries:
                shared, time = split_label(e["base_label"])
                w = {"map": mid, "base_label": "%s_%s%s" % (shared, rule["suffix"], "_" + time if time else "")}
                for key, val in e.items():
                    if key in ("map", "base_label"):
                        continue
                    if key in RATES:
                        kind = [k for k, v in KIND.items() if v == key][0]
                        fixed = {int(i): "SPECIES_" + sp for i, sp in extras.get(kind, {}).items()}
                        fixed.update({int(i): "SPECIES_" + sp for i, sp in fix.get(kind, {}).items()})
                        fixed = {i: sp for i, sp in fixed.items() if i < len(val["mons"])}
                        t = reweight(val, key, rule, fixed)
                        before, after = shares(val, key), shares(t, key)
                        cells = []
                        for sp in sorted(set(before) | set(after), key=lambda s: (-after.get(s, 0), s)):
                            a, b = before.get(sp, 0), after.get(sp, 0)
                            cells.append(("**%s** %d" % (sp, b)) if not a else "%s %d → %d" % (sp, a, b))
                        report.append("- %s, %s: %s" % (time or "Day", key[:-5], "; ".join(cells)))
                        w[key] = t
                    else:
                        w[key] = copy.deepcopy(val)  # fishing, rock smash, hidden: unchanged
                out.append(w)
            report.append("")
    json.dump({"_comment": "Generated by tools/hoenn/gen_hoenn_weather_wild.py. Do not edit.", "encounters": out},
              open(P("data/hoenn/wild_encounters_weather.json"), "w"), indent=2)
    open(P("hoenn-docs/weather-tables.md"), "w").write("\n".join(report) + "\n")
    print("%d weather tables" % len(out))


if __name__ == "__main__":
    main()
