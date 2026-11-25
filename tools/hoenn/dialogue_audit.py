#!/usr/bin/env python3
"""List the Hoenn text a player can actually reach that still assumes the Emerald story.

    tools/hoenn/dialogue_audit.py [--all] [MAP_PREFIX...]

Roots are the scripts on kept maps' objects, signs and map scripts (on load,
transition, resume). Coord/frame triggers are skipped: the post-Emerald var
values keep them from firing. From the roots it follows goto/call/branch targets
to every msgbox/message text, then flags texts that match the story patterns
(player gender branches, Mom, Norman as dad, {RIVAL}, Brendan/May, Magma/Aqua,
"moved here", champion). --all prints every reachable text, matched or not.

Branches on story vars are followed too, so some hits sit in dead branches; read
the script around each label before rewriting it."""
import json, os, re, sys

ROOT = os.path.join(os.path.dirname(__file__), "..", "..")
PATTERNS = {
    "gender": r"checkplayergender|MALE|FEMALE",
    "mom": r"\bMOM\b|\bMom\b|your mother",
    "dad": r"\bDAD\b|your (?:dad|father)|NORMAN's (?:kid|son|daughter|child)",
    "rival": r"\{RIVAL\}",
    "brendan_may": r"\bBRENDAN\b|\bMAY\b",
    "teams": r"MAGMA|AQUA|MAXIE|ARCHIE",
    "new": r"moved here|new in town|just moved|new neighbor|LITTLEROOT.*(?:new|move)",
    "champion": r"CHAMPION",
}

def labels(text):
    out, cur = {}, None
    for line in text.splitlines():
        m = re.match(r"^(\w+)::?\s*$", line)
        if m:
            cur = m.group(1); out[cur] = []
        elif cur:
            out[cur].append(line)
    return out

def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    show_all = "--all" in sys.argv
    kept = json.load(open(os.path.join(ROOT, "data/hoenn/maps.json")))["items"]
    # every label in every script/text file, so cross-file gotos resolve
    all_labels = {}
    files = [os.path.join(ROOT, "data/maps", m, "scripts.inc") for m in kept]
    files += [os.path.join(ROOT, "data/scripts", f) for f in os.listdir(os.path.join(ROOT, "data/scripts")) if f.endswith(".inc")]
    owner = {}
    for f in files:
        if os.path.exists(f):
            for k, v in labels(open(f).read()).items():
                all_labels[k] = v; owner[k] = f
    hits = 0
    for m in sorted(kept):
        if args and not any(m.startswith(a) for a in args):
            continue
        d = json.load(open(os.path.join(ROOT, "data/maps", m, "map.json")))
        roots = [o.get("script") for o in d.get("object_events", [])]
        roots += [b.get("script") for b in d.get("bg_events", []) if b.get("type") == "sign"]
        sp = os.path.join(ROOT, "data/maps", m, "scripts.inc")
        own = labels(open(sp).read()) if os.path.exists(sp) else {}
        for line in own.get(f"{m}_MapScripts", []):
            mm = re.match(r"\s*map_script MAP_SCRIPT_ON_(LOAD|TRANSITION|RESUME),\s*(\w+)", line)
            if mm: roots.append(mm.group(2))
        seen, texts, stack = set(), [], [r for r in roots if r and r != "0x0"]
        while stack:
            lab = stack.pop()
            if lab in seen or lab not in all_labels: continue
            seen.add(lab)
            body = all_labels[lab]
            if any(".string" in l for l in body):
                texts.append(lab); continue
            for l in body:
                for ref in re.findall(r"\b([A-Z]\w*_(?:EventScript|Text|Movement)_\w+|gText_\w+)", l):
                    stack.append(ref)
            # fall through into the next label when there's no end/goto/return
            if body and not re.search(r"^\s*(end|return|goto|step_end)\b", body[-1] if body else ""):
                pass
        for t in sorted(set(texts)):
            s = "".join(re.findall(r'\.string "(.*)"', "\n".join(all_labels[t])))
            tags = [k for k, p in PATTERNS.items() if re.search(p, s)]
            if tags or show_all:
                hits += 1
                print(f"{m}: {t} [{','.join(tags)}]\n    {s[:220]}")
    print(f"-- {hits} texts", file=sys.stderr)

if __name__ == "__main__":
    main()
