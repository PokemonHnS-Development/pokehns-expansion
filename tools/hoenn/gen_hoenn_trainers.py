#!/usr/bin/env python3
"""Hoenn & Seek (part 14): apply data/hoenn/trainer_curation.json to the Hoenn maps.

    tools/hoenn/gen_hoenn_trainers.py

Run before gen_hoenn_ids.py (which reads data/hoenn/trainer_roles.json) and
gen_hoenn_gyms.py. It writes:
  data/hoenn/trainer_objects.json   every trainer object on a kept map, with its
                                    ORIGINAL script (made once; keeps re-runs idempotent)
  data/scripts/hoenn_trainers.inc   new scripts for battle/hopeful/strong/fake/npc objects
  data/hoenn/trainer_roles.json     role per trainer + the names gen_hoenn_ids must skip
  src/data/hoenn_scaled_trainers.h  hopeful/strong/rematch lists for src/hoenn_scaling.c
  src/data/hoenn_rematches.h        part 16c: gRematchTable entries for phone trainers
  src/data/hoenn_match_call.h       part 16c: their PokeGear call entries (+ _decls.h)
  data/text/match_call_hoenn.inc    part 16c: their call texts (data/hoenn/phone_texts.json)
and swaps the object scripts (and, for NPCs, trainer type/sight) in the map.json files.
"""
import hashlib, json, os, re, sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
P = lambda *a: os.path.join(ROOT, *a)
FAKE_KINDS = ("follower", "autograph", "cheer", "foresee", "song")
NO_ID_ROLES = ("npc", "drop")
MAX_FAKES = 0x100

# ------------------------------------------------------------------ text pools
# Lines are at most ~36 characters; \n = next line, \l = scroll, \p = new box.
INTRO = {
    "hopeful": [
        "I know who you are. The champion\\nfrom JOHTO.\\pI'll probably lose. But I'd never\\nforgive myself if I didn't try!",
        "They say you beat RED himself.\\nI don't care! Battle me anyway!",
        "I've trained for a day like this.\\nEven if I lose, I'll learn something!",
        "Everyone told me not to challenge\\nyou. That only makes me want to more!",
        "Win or lose, I want to feel a\\nchampion's strength up close!",
        "My POKéMON are shaking…\\nBut they want this as much as I do!",
    ],
    "hopeful_double": [
        "We know we're outmatched.\\nBut two of us beat as one!",
        "Together we might stand a chance…\\nMaybe! Let's go!",
    ],
    "strong": [
        "A champion from JOHTO, out here?\\nI've been waiting for a real test.",
        "Finally, someone worth battling.\\nDon't hold back on my account.",
        "Nobody on this route can beat me.\\nLet's see if you can.",
        "Your name reached HOENN long before\\nyou did. Show me it's earned!",
        "Strong TRAINERS seek out stronger\\nones. That's why I'm here.",
    ],
    "strong_double": [
        "Two of us against one champion.\\nThat sounds about fair!",
    ],
}

FAKE = {
    "follower": [
        "Hey, you! Let's battle right-\\p…Is that your {STR_VAR_2}?\\nIt's staring right at me…\\pY-you know what? Never mind!\\nI just remembered I'm busy!",
        "Hey! You look like an easy-\\p…Whoa. {STR_VAR_1} looks like it's\\nbeen through a hundred battles.\\pI'll… find someone else. Bye!",
        "A TRAINER! Battle me, battle-\\p…Your {STR_VAR_2} just yawned at me.\\nThat's never a good sign.\\pLet's just say you won, OK?",
    ],
    "follower_none": "Hey! Let's batt-\\pWait. Those BADGES on your TRAINER\\nCARD… You're the JOHTO champion!\\pForget I said anything!",
    "follower_after": "I'm going to stand over here and\\nnot make eye contact. Thanks.",
    "autograph": [
        "!!! No way! You're {PLAYER}!\\nThe champion from JOHTO!\\pCould you sign my hat? Please?",
        "Excuse me! You're {PLAYER}, right?\\nI saw you on JOHTO TV!\\pWould you sign my notebook?",
        "It's really you! {PLAYER}!\\pI have to get your autograph!\\nHere, sign my towel!",
    ],
    "autograph_signed": "{PLAYER} signed it with a flourish.",
    "autograph_thanks": "I'm never washing this again!\\nWait till everyone hears about this!",
    "autograph_after": "I'm going to frame your autograph!",
    "cheer": [
        "I was going to challenge you…\\pBut I heard what you did in JOHTO\\nand KANTO. I'll train some more first.\\pGood luck with the HOENN GYMS!",
        "Wait, aren't you…? Wow.\\nI'm nowhere near ready for you.\\pBut I'm rooting for you!\\nGo show HOENN what you've got!",
    ],
    "cheer_after": "HOENN's GYM LEADERS are tougher\\nthan they look. Hang in there!",
    "foresee": [
        "I foresaw this meeting…\\pI also foresaw how our battle ends.\\nLet's skip it, shall we?",
        "Your future flickered into my mind\\nbefore you arrived.\\pIn it, I lost. Badly.\\nI'll pass, thank you.",
    ],
    "foresee_after": "My visions are never wrong.\\nWell… rarely.",
    "song": [
        "Yo! You're {PLAYER}, the JOHTO\\nchampion? I'm writing a song about\\lyou! Here's the first verse!\\p“From far away, a TRAINER came…\\nSixteen BADGES and a famous name!”\\pCatchy, right? I'm sending it to the\\nTV station!",
    ],
    "song_after": "Keep your eyes on HOENN TV!\\nThe song's gonna be huge!",
}
NEWS_KIND = {"autograph": 1, "song": 2}

NPC_GROUPS = {
    "swim": ("Swimmer M", "Swimmer F", "Tuber M", "Tuber F"),
    "tri": ("Triathlete",),
    "fish": ("Fisherman",),
    "bird": ("Bird Keeper",),
    "camp": ("Picnicker", "Camper"),
    "sea": ("Sailor",),
    "kid": ("Youngster", "Lass", "School Kid", "Bug Catcher"),
    "bug": ("Bug Maniac",),
    "mind": ("Psychic", "Hex Maniac"),
    "rock": ("Hiker", "Ruin Maniac", "Kindler"),
    "posh": ("Beauty", "Lady", "Rich Boy", "Gentleman", "Aroma Lady", "Parasol Lady"),
    "music": ("Guitarist",),
    "breed": ("Pkmn Breeder", "Pokefan", "Collector", "Pokemaniac"),
}
NPC = {
    "swim": [
        "HOENN's warm currents are the best\\ntraining there is. For me, anyway.",
        "I swam all the way out here.\\nBattling can wait. I need a breather.",
        "The sea's been so calm these past\\nfew years. Nothing like the old days.",
    ],
    "tri": [
        "Run, bike, swim, repeat!\\nI'm training for the HOENN triathlon.",
        "My legs are burning!\\nNo battles today, sorry.",
    ],
    "fish": [
        "Shh! You'll scare off the big one!",
        "The fish bite best when you're\\npatient. Patience is everything.",
    ],
    "bird": [
        "Bird POKéMON ride the sea breeze\\nhere. Look up, you'll see them!",
        "I'm just watching the sky today.\\nIt's a good day for flying.",
    ],
    "camp": [
        "We're camping out here all week!\\nThe stars at night are amazing.",
        "I packed way too many sandwiches.\\nWant one? No? More for me!",
    ],
    "sea": [
        "Ahoy! I've sailed these waters for\\nyears. HOENN's sea is like no other.",
        "The ferries from KANTO bring all\\nsorts of TRAINERS these days.",
    ],
    "kid": [
        "I'm gonna be a GYM LEADER someday!\\nJust you wait!",
        "My mom says I can't battle until\\nI finish my homework. Ugh.",
    ],
    "bug": [
        "I'm looking for rare BUG POKéMON.\\nWatch where you step!",
    ],
    "mind": [
        "The spirits are quiet today.\\nThat's… unusual.",
        "I sense a powerful aura around you.\\nI'd rather not test it.",
    ],
    "rock": [
        "These mountains were here long before\\nany of us. Respect them.",
        "I'm sure there are ruins hidden\\nsomewhere in HOENN. I'll keep digging!",
    ],
    "posh": [
        "I'm simply here to enjoy the scenery.\\nBattling would ruin my outfit.",
        "Such a lovely day for a stroll.\\nDon't you agree?",
    ],
    "music": [
        "I'm working on a new song.\\nNeed some peace and quiet for it.",
    ],
    "breed": [
        "Raising POKéMON takes love and\\npatience. Yours look well cared for.",
    ],
    "misc": [
        "Lovely day out, isn't it?",
    ],
}


def pick(pool, key):
    return int(hashlib.md5(key.encode()).hexdigest(), 16) % len(pool)


def labels(text):
    out, cur = {}, None
    for line in text.splitlines():
        m = re.match(r"^(\w+)::?\s*$", line)
        if m:
            cur = m.group(1)
            out[cur] = []
        elif cur:
            out[cur].append(line.strip())
    return out


def party_classes():
    info, cur = {}, None
    for line in open(P("src/data/trainers.party")):
        m = re.match(r"=== (TRAINER_\w+) ===", line)
        if m:
            cur = m.group(1)
        elif cur and line.startswith("Class:"):
            info[cur] = line.split(":", 1)[1].strip()
    return info


def build_manifest(kept):
    """Every object on a kept map whose (original) script starts a trainer battle."""
    out = []
    for m in sorted(kept):
        sp = P("data/maps", m, "scripts.inc")
        labs = labels(open(sp).read()) if os.path.exists(sp) else {}
        d = json.load(open(P("data/maps", m, "map.json")))
        for i, o in enumerate(d.get("object_events", [])):
            body = labs.get(o.get("script", ""), [])[:8]
            t = None
            for line in body:
                t = re.match(r"trainerbattle_(\w+)\s+(TRAINER_\w+)", line)
                if t:
                    break
            if not t:
                continue
            out.append({"map": m, "index": i, "graphics_id": o["graphics_id"], "script": o["script"],
                        "macro": t.group(1), "trainer": t.group(2),
                        "trainer_type": o.get("trainer_type"), "sight": o.get("trainer_sight_or_berry_tree_id")})
    return out


def battle_texts(map_name, script, labs):
    """(macro, intro, defeat, notenough, after) from an Emerald trainer script."""
    body = labs.get(script, [])
    tb = None
    for i, line in enumerate(body):
        m = re.match(r"trainerbattle_(single|double)\s+(TRAINER_\w+),\s*(\w+),\s*(\w+)(?:,\s*(\w+))?", line)
        if m:
            tb, rest = m, body[i + 1:]
            break
    if not tb:
        return None
    kind, intro, defeat = tb.group(1), tb.group(3), tb.group(4)
    notenough = tb.group(5) if kind == "double" else None
    after, seen, todo = None, set(), [rest]
    while todo and not after:
        lines = todo.pop(0)
        for line in lines:
            m = re.match(r"msgbox\s+(\w+),\s*MSGBOX_\w+", line)
            if m:
                after = m.group(1)
                break
            m = re.match(r"goto\s+(\w+)$", line)
            if m and m.group(1) not in seen:
                seen.add(m.group(1))
                todo.append(labs.get(m.group(1), []))
            if line in ("end", "release"):
                break
    return kind, intro, defeat, notenough, after or defeat


def emerald_rematch_table():
    """Emerald's normal rematch trainers: {first trainer: (rematch trainer ids, map)}."""
    src = open(P("src/battle_setup.c")).read()
    start = src.index("#else", src.index("const struct RematchTrainer gRematchTable"))
    body = src[start:src.index("};", start)]
    out = {}
    for m in re.finditer(r"\[(REMATCH_\w+)\]\s*=\s*REMATCH\((.*?)\),?\s*$", body, re.M):
        if m.group(1) == "REMATCH_WALLY_VR":
            break
        args = [a.strip() for a in m.group(2).split(",")]
        out[args[0]] = (args[1:-1], args[-1])
    return out


def free_rematch_slots():
    """REMATCH_* enum names HnS leaves unused for normal trainers (after KAREN, before ALEX_HNS)."""
    names = re.findall(r"^\s*(REMATCH_\w+),", open(P("include/constants/rematches.h")).read(), re.M)
    return names[names.index("REMATCH_KAREN") + 1:names.index("REMATCH_ALEX_HNS")]


def all_texts():
    """label -> raw .string lines, from data/text/trainers.inc and every map's scripts.inc."""
    out = {}
    files = [P("data/text/trainers.inc")] + [P("data/maps", d, "scripts.inc") for d in os.listdir(P("data/maps"))]
    for path in files:
        if not os.path.exists(path):
            continue
        for m in re.finditer(r"^(\w+)::?\n((?:\t\.string .*\n)+)", open(path).read(), re.M):
            out.setdefault(m.group(1), m.group(2))
    return out


def wrap_boxes(boxes, width=26):
    """Phone text: each box is word-wrapped; lines join with \\n then \\l, boxes with \\p."""
    def vis(w):
        return len(re.sub(r"\{PLAYER\}", "XXXXXXX", re.sub(r"\{STR_VAR_\d\}", "XXXXXXXXXX", w)))
    out = []
    # two-speaker lines ("AMY: ... LIV: ...") get a box per speaker
    boxes = [b for box in boxes for b in re.split(r"(?<=[.!?…]) (?=[A-Z]{2,}: )", box)]
    for box in boxes:
        lines, cur = [], ""
        for w in box.split():
            if cur and vis(cur) + 1 + vis(w) > width:
                lines.append(cur)
                cur = w
            else:
                cur = f"{cur} {w}" if cur else w
        lines.append(cur)
        out.append(lines[0] + "".join(("\\n" if i == 1 else "\\l") + l for i, l in enumerate(lines[1:], 1)))
    return "\\p".join(out)


def main():
    cur = json.load(open(P("data/hoenn/trainer_curation.json")))
    kept = json.load(open(P("data/hoenn/maps.json")))["items"]
    classes = party_classes()

    man_path = P("data/hoenn/trainer_objects.json")
    if os.path.exists(man_path):
        manifest = json.load(open(man_path))
    else:
        manifest = build_manifest(kept)
        with open(man_path, "w") as f:
            json.dump(manifest, f, indent=1)
            f.write("\n")

    def role_of(trainer, map_name=None):
        if map_name and "_Gym" in map_name:
            return "keep"
        if map_name and map_name in cur["maps"]:
            return cur["maps"][map_name]
        if trainer in cur["trainers"]:
            return cur["trainers"][trainer]
        if trainer.startswith(tuple(cur.get("drop_prefixes", ()))):
            return "drop"
        if map_name:
            return cur["classes"].get(classes.get(trainer, ""), "keep")
        return "keep"

    # Roles for every trainer the Hoenn scripts mention (placed or scripted).
    referenced = set()
    for m in kept:
        sp = P("data/maps", m, "scripts.inc")
        if os.path.exists(sp):
            referenced |= set(re.findall(r"\bTRAINER_[A-Z0-9_]+\b", open(sp).read()))
    roles = {}
    for o in manifest:
        r = role_of(o["trainer"], o["map"])
        prev = roles.get(o["trainer"])
        if prev and prev != r:
            sys.exit(f"{o['trainer']} has two roles: {prev} / {r}")
        roles[o["trainer"]] = r
    for t in sorted(referenced - set(roles)):
        if t in classes:
            roles[t] = role_of(t)
    for t, r in roles.items():
        if r not in ("keep", "battle", "hopeful", "strong", "npc", "drop") and not (r.startswith("fake:") and r[5:] in FAKE_KINDS):
            sys.exit(f"{t}: unknown role {r}")

    fakes = sorted(t for t, r in roles.items() if r.startswith("fake:"))
    if len(fakes) > MAX_FAKES:
        sys.exit("too many fake fights for HOENN_FAKE_FLAGS")
    fake_flag = {t: i for i, t in enumerate(fakes)}

    # Part 16c: Emerald's rematch trainers who still battle register in the PokeGear.
    # They take the rematch slots HnS leaves free; each gets one rematch team (the
    # last Emerald tier), scaled to the gym-ace level in-game (src/hoenn_scaling.c).
    em_rematch = emerald_rematch_table()
    phone = sorted(t for t in em_rematch if roles.get(t) in ("battle", "hopeful", "strong"))
    slots = free_rematch_slots()
    if len(phone) > len(slots):
        sys.exit(f"{len(phone)} phone trainers but only {len(slots)} free rematch slots")
    rematch_id = {t: em_rematch[t][0][-1] for t in phone}
    phone_texts = json.load(open(P("data/hoenn/phone_texts.json")))
    missing = [t for t in phone if t not in phone_texts]
    if missing:
        sys.exit(f"data/hoenn/phone_texts.json has no texts for {missing}")
    text_src = all_texts()

    # ---- scripts
    out = ["@ Generated by tools/hoenn/gen_hoenn_trainers.py from data/hoenn/trainer_curation.json. Do not edit.",
           "@ Hoenn & Seek (part 14): trainers who don't battle (NPCs), '!' walk-ups that turn",
           "@ into something else (fake fights), and Emerald trainers with new intros.", ""]
    texts = {}

    def text(label, s):
        texts[label] = s
        return label

    def tname(t):
        return t[len("TRAINER_"):].title().replace("_", "")

    def gear_text(label):
        """Emerald text, or a POKeGEAR copy when it mentions the POKeNAV."""
        raw = text_src.get(label)
        if raw is None or "POKéNAV" not in raw:
            return label
        new = "HoennSeek_Text_Gear_" + label
        body = "".join(re.findall(r'\.string "(.*)"', raw)).replace("POKéNAVS", "POKéGEARS").replace("POKéNAV", "POKéGEAR")
        texts[new] = body[:-1] if body.endswith("$") else body
        return new

    def phone_script(label, t, kind, intro, defeat, notenough, after, o, labs):
        body = labs.get(o["script"], [])
        reg = remlab = None
        for line in body:
            m = re.match(r"trainerbattle_(?:single|double)\s+.*,\s*(\w+_EventScript_\w+)\s*$", line)
            if m:
                reg = m.group(1)
            m = re.match(r"goto_if_eq\s+VAR_RESULT,\s*TRUE,\s*(\w+)", line)
            if m:
                remlab = m.group(1)
        regtext = None
        for lab_lines in labs.values():  # the msgbox right before register_matchcall
            for i, l in enumerate(lab_lines):
                if l == f"register_matchcall {t}" and i and lab_lines[i - 1].startswith("msgbox"):
                    regtext = regtext or re.match(r"msgbox\s+(\w+)", lab_lines[i - 1]).group(1)
        rem = next((l for l in labs.get(remlab, []) if l.startswith("trainerbattle_rematch")), None)
        remafter = next((re.match(r"msgbox\s+(\w+)", l).group(1) for l in labs.get(remlab, []) if l.startswith("msgbox")), after)
        if not (regtext and rem):
            sys.exit(f"{o['map']} {o['script']}: can't parse the register/rematch scripts")
        rargs = [a.strip() for a in rem.split(None, 1)[1].split(",")]
        rmacro = rem.split()[0]
        lines = [f"{label}::"]
        if kind == "double":
            lines.append(f"\ttrainerbattle_double {t}, {intro}, {defeat}, {notenough}, {label}_Register")
        else:
            lines.append(f"\ttrainerbattle_single {t}, {intro}, {defeat}, {label}_Register")
        lines += ["\tspecialvar VAR_RESULT, ShouldTryRematchBattle",
                  f"\tgoto_if_eq VAR_RESULT, TRUE, {label}_Rematch",
                  f"\tmsgbox {after}, MSGBOX_AUTOCLOSE", "\tend", "",
                  f"{label}_Register::", "\tspecial PlayerFaceTrainerAfterBattle", "\twaitmovement 0",
                  f"\tmsgbox {gear_text(regtext)}, MSGBOX_DEFAULT", f"\tregister_matchcall {t}", "\trelease", "\tend", "",
                  f"{label}_Rematch::", f"\t{rmacro} {t}, " + ", ".join(gear_text(a) for a in rargs[1:]),
                  f"\tmsgbox {gear_text(remafter)}, MSGBOX_AUTOCLOSE", "\tend", ""]
        return lines

    done = set()
    swaps = {}  # (map, index) -> (script, npc?)
    labs_cache = {}
    for o in manifest:
        t, r = o["trainer"], roles[o["trainer"]]
        if r in ("keep", "drop"):
            continue
        label = f"HoennSeek_EventScript_T_{tname(t)}"
        swaps[(o["map"], o["index"])] = (label, r == "npc")
        if t in done:
            continue
        done.add(t)
        cls = classes.get(t, "")
        if r == "npc":
            group = next((g for g, cs in NPC_GROUPS.items() if cls in cs), "misc")
            n = pick(NPC[group], t)
            out += [f"{label}::", f"\tmsgbox {text(f'HoennSeek_Text_Npc_{group}_{n}', NPC[group][n])}, MSGBOX_NPC", "\tend", ""]
        elif r.startswith("fake:"):
            kind = r[5:]
            flag = f"HOENN_FAKE_FLAGS_START + {fake_flag[t]}"
            pool = FAKE[kind]
            n = pick(pool, t)
            done_label = f"{label}_Done"
            out += [f"{label}::", f"\tgoto_if_set {flag}, {done_label}", "\tlock", "\tfaceplayer", f"\tsetflag {flag}"]
            if kind == "follower":
                out += ["\tspecialvar VAR_RESULT, HoennBufferFollower",
                        "\tgoto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_FakeNoFollower",
                        f"\tmsgbox {text(f'HoennSeek_Text_Fake_follower_{n}', pool[n])}, MSGBOX_DEFAULT"]
            elif kind == "autograph":
                out += [f"\tmsgbox {text(f'HoennSeek_Text_Fake_autograph_{n}', pool[n])}, MSGBOX_DEFAULT",
                        "\tgoto HoennSeek_EventScript_FakeSign"]
            elif kind == "song":
                out += [f"\tmsgbox {text(f'HoennSeek_Text_Fake_song_{n}', pool[n])}, MSGBOX_DEFAULT",
                        f"\tsetvar VAR_HOENN_NEWS, {NEWS_KIND['song']}"]
            else:
                out += [f"\tmsgbox {text(f'HoennSeek_Text_Fake_{kind}_{n}', pool[n])}, MSGBOX_DEFAULT"]
            out += ["\trelease", "\tend", f"{done_label}::",
                    "\tcallnative HoennSeek_EndScriptIfSeeing, requests_effects=1",
                    f"\tmsgbox HoennSeek_Text_Fake_{kind}_After, MSGBOX_NPC", "\tend", ""]
        else:
            if o["map"] not in labs_cache:
                labs_cache[o["map"]] = labels(open(P("data/maps", o["map"], "scripts.inc")).read())
            bt = battle_texts(o["map"], o["script"], labs_cache[o["map"]])
            if not bt:
                sys.exit(f"{o['map']} {o['script']}: can't parse the trainer battle for role {r}")
            kind, intro, defeat, notenough, after = bt
            if r in ("hopeful", "strong"):
                pool = INTRO[r + ("_double" if kind == "double" else "")]
                n = pick(pool, t)
                intro = text(f"HoennSeek_Text_Intro_{r}{'_double' if kind == 'double' else ''}_{n}", pool[n])
            if t in phone:
                out += phone_script(label, t, kind, intro, defeat, notenough, after, o, labs_cache[o["map"]])
                continue
            if kind == "double":
                out += [f"{label}::", f"\ttrainerbattle_double {t}, {intro}, {defeat}, {notenough}"]
            else:
                out += [f"{label}::", f"\ttrainerbattle_single {t}, {intro}, {defeat}"]
            out += [f"\tmsgbox {after}, MSGBOX_AUTOCLOSE", "\tend", ""]

    out += ["@ ---------------------------------------------------------------- shared fake-fight tails",
            "HoennSeek_EventScript_FakeNoFollower::",
            "\tmsgbox HoennSeek_Text_Fake_follower_None, MSGBOX_DEFAULT",
            "\trelease", "\tend", "",
            "HoennSeek_EventScript_FakeSign::",
            "\tplayfanfare MUS_OBTAIN_ITEM",
            "\tmessage HoennSeek_Text_Fake_autograph_Signed",
            "\twaitfanfare", "\twaitmessage",
            "\tmsgbox HoennSeek_Text_Fake_autograph_Thanks, MSGBOX_DEFAULT",
            f"\tsetvar VAR_HOENN_NEWS, {NEWS_KIND['autograph']}",
            "\trelease", "\tend", ""]
    texts["HoennSeek_Text_Fake_follower_None"] = FAKE["follower_none"]
    texts["HoennSeek_Text_Fake_autograph_Signed"] = FAKE["autograph_signed"]
    texts["HoennSeek_Text_Fake_autograph_Thanks"] = FAKE["autograph_thanks"]
    for k in FAKE_KINDS:
        texts[f"HoennSeek_Text_Fake_{k}_After"] = FAKE[f"{k}_after"]
    out.append("@ ---------------------------------------------------------------- text")
    for label in sorted(texts):
        out.append(f"{label}:")
        parts = re.split(r"(?<=\\[npl])", texts[label])
        for i, part in enumerate(parts):
            out.append(f'\t.string "{part}{"$" if i == len(parts) - 1 else ""}"')
        out.append("")
    with open(P("data/scripts/hoenn_trainers.inc"), "w") as f:
        f.write("\n".join(out))

    # ---- map.json swaps (restore the original first, so roles can change)
    by_map = {}
    for o in manifest:
        by_map.setdefault(o["map"], []).append(o)
    for m, objs in by_map.items():
        path = P("data/maps", m, "map.json")
        raw = open(path).read()
        d = json.loads(raw)
        for o in objs:
            ev = d["object_events"][o["index"]]
            if ev["graphics_id"] != o["graphics_id"]:
                sys.exit(f"{m}: object {o['index']} changed since the manifest was made")
            ev["script"] = o["script"]
            ev["trainer_type"] = o["trainer_type"]
            ev["trainer_sight_or_berry_tree_id"] = o["sight"]
            sw = swaps.get((m, o["index"]))
            if sw:
                ev["script"] = sw[0]
                if sw[1]:
                    ev["trainer_type"] = "TRAINER_TYPE_NONE"
                    ev["trainer_sight_or_berry_tree_id"] = "0"
        new = json.dumps(d, indent=2, ensure_ascii=False) + "\n"
        if new != raw:
            open(path, "w").write(new)

    # ---- roles + scaling lists
    exclude = sorted(t for t, r in roles.items() if r in NO_ID_ROLES or r.startswith("fake:"))
    with open(P("data/hoenn/trainer_roles.json"), "w") as f:
        json.dump({"roles": dict(sorted(roles.items())), "exclude": exclude,
                   "fake_flags": {t: i for t, i in fake_flag.items()},
                   "rematch": rematch_id}, f, indent=1)
        f.write("\n")
    with open(P("src/data/hoenn_scaled_trainers.h"), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_trainers.py from data/hoenn/trainer_curation.json. Do not edit.\n")
        for r, name in (("strong", "sHoennStrongTrainers"), ("hopeful", "sHoennHopefulTrainers")):
            f.write(f"static const u16 {name}[] =\n{{\n")
            f.write("".join(f"    {t},\n" for t in sorted(t for t, x in roles.items() if x == r)))
            f.write("};\n\n")
        f.write("// Part 16c: phone rematch teams (gym-ace level, no gap).\nstatic const u16 sHoennRematchTrainers[] =\n{\n")
        f.write("".join(f"    {rematch_id[t]},\n" for t in phone))
        f.write("};\n")
    gen16 = "// Generated by tools/hoenn/gen_hoenn_trainers.py (part 16c). Do not edit.\n"
    with open(P("src/data/hoenn_rematches.h"), "w") as f:
        f.write(gen16 + "// Hoenn phone trainers in the rematch slots HnS leaves free. Included inside HnS's gRematchTable.\n")
        for t, slot in zip(phone, slots):
            r = rematch_id[t]
            f.write(f"    [{slot}] = REMATCH({t}, {r}, {r}, {r}, {r}, {em_rematch[t][1]}),\n")
    def cname(t):
        return "Hoenn" + tname(t)
    with open(P("src/data/hoenn_match_call_decls.h"), "w") as f:
        f.write(gen16)
        for t in phone:
            f.write("".join(f"extern const u8 MatchCall_HNS_{cname(t)}_{k}[];\n" for k in ("General1", "General2", "Battle")))
    with open(P("src/data/hoenn_match_call.h"), "w") as f:
        f.write(gen16 + "// Included inside sHnsMatchCallTrainers (src/match_call.c).\n")
        f.write("".join(f"    HNS_MC_ENTRY2({cname(t)}, {t}),\n" for t in phone))
    with open(P("data/text/match_call_hoenn.inc"), "w") as f:
        f.write("@ Generated by tools/hoenn/gen_hoenn_trainers.py from data/hoenn/phone_texts.json. Do not edit.\n")
        for t in phone:
            pt = phone_texts[t]
            for k, boxes in (("General1", pt["general"][0]), ("General2", pt["general"][1]), ("Battle", pt["battle"])):
                body = wrap_boxes(boxes)
                parts = re.split(r"(?<=\\[npl])", body)
                f.write(f"MatchCall_HNS_{cname(t)}_{k}::\n")
                f.write("".join(f'\t.string "{p}{"$" if i == len(parts) - 1 else ""}"\n' for i, p in enumerate(parts)))
            f.write("\n")
    print(f"phone: {len(phone)} Hoenn trainers in {len(slots)} free rematch slots")
    count = {}
    for r in roles.values():
        k = "fake" if r.startswith("fake:") else r
        count[k] = count.get(k, 0) + 1
    print("roles:", dict(sorted(count.items())), f"-> {len(roles) - len(exclude)} trainers keep an ID")


if __name__ == "__main__":
    main()
