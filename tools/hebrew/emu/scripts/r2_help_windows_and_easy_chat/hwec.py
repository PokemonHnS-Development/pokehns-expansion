#!/usr/bin/env python3
"""hns.py plus the r2/r3 service ops (r3bf.py: drive, pick, vars; r2sf.py: textwatch, burst,
scenewatch, scrollshots, scrollmem, warpraw, startmenux, ss, sl, loc, playwhile, bagseek, bagpocket,
waitwarp) and the ops the help-window and Easy Chat tours (hw_*.txt, ec_*.txt, mail_*.txt) use.
Run:  hwec.py tour ROM OUT --tours <this folder> [--clip] [--only RE]

Easy Chat ops (src/easy_chat.c; struct EasyChatScreen in include/easy_chat.h, sWordData layout in
the same header with EC_NUM_GROUPS 22, EC_NUM_ALPHABET_GROUPS 27, EC_MAX_WORDS_IN_GROUP 270):
    ecwait [MAX]                 run until Task_EasyChatScreen reads input (tState == 1,
                                 MAINSTATE_HANDLE_INPUT, src/easy_chat.c:1315) and the screen is quiet
    ec KEY [N]                   tap KEY N times (default 1), ecwait after each
    ecstate                      print inputState, cursors, scroll offsets, current phrase
    ecslot ROW COL               move the phrase cursor (INPUTSTATE_PHRASE) to ROW, COL
    ecbutton COL                 move the cursor onto footer button COL (0 DEL ALL, 1 CANCEL, 2 OK)
    ecgroup GROUP                keyboard in group mode: move to GROUP (EC_GROUP_* or a number) by its
                                 index in sWordData->unlockedGroupIds, no press
    ecletter ROW COL             keyboard in alphabet mode: move to ROW, COL, no press
    ecword WORD                  word select: move the cursor onto WORD (EC_WORD_* or a number) by its
                                 index in sWordData->selectedGroupWords, no press
    ecputword ROW COL GROUP WORD [PREFIX]   slot ROW,COL <- WORD through the UI (A, group, A, word,
                                 A); PREFIX_kbd / PREFIX_list shots on the way when given
    ecgroups PREFIX              keyboard in group mode: shot every visible page of group names,
                                 scrolling DOWN to the last row (PREFIX_01..)
    eclist PREFIX [MAX]          word select: shot the first page, then SELECT (page down) until the
                                 list ends (PREFIX_01..)

On a ROM whose src/easy_chat.c mirrors the Easy Chat columns under TEXT_RTL (LEFT moves to the next
column), ecslot, ecbutton, ecgroup, ecletter and ecword press LEFT for the next column and RIGHT
for the previous one; `ec` taps the key it is given.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", ".."))                                # tools/hebrew/emu
sys.path.insert(0, os.path.join(HERE, "..", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(HERE, "..", "r3_frontier"))
import hns  # noqa: E402
import r3bf  # noqa: E402,F401  (registers the r2 + r3 ops)
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

# struct EasyChatScreen (include/easy_chat.h:20-44)
ECS = dict(type=0x00, templateId=0x01, numColumns=0x02, numRows=0x03, inputState=0x04,
           mainCursorColumn=0x05, mainCursorRow=0x06, maxWords=0x07, inAlphabetMode=0x09,
           keyboardColumn=0x0A, keyboardRow=0x0B, keyboardScrollOffset=0x0C, keyboardLastRow=0x0D,
           wordSelectScrollOffset=0x0E, wordSelectLastRow=0x0F, wordSelectColumn=0x10,
           wordSelectRow=0x11, currentPhrase=0x3C)
# struct EasyChatScreenWordData (include/easy_chat.h:107-115)
WD_NUMGROUPS, WD_GROUPIDS = 0x00, 0x02
WD_SELWORDS = 0x02 + 2 * 22 + 2 * 27 + 2 * 27 * 270 + 44     # 0x3984
WD_NUMSEL = WD_SELWORDS + 2 * 270                             # 0x3BA0
INPUTSTATES = ["PHRASE", "MAIN_SCREEN_BUTTONS", "KEYBOARD", "WORD_SELECT", "EXIT_PROMPT",
               "DELETE_ALL_YES_NO", "CONFIRM_WORDS_YES_NO", "QUIZ_QUESTION", "WAIT_FOR_MSG",
               "START_CONFIRM_LYRICS", "CONFIRM_LYRICS_YES_NO"]


_EC_CACHE = {}
_MIRROR_CACHE = {}


def ec_mirrored(emu):
    """True when the tree under test swaps LEFT and RIGHT on the mirrored Easy Chat columns: TEXT_RTL
    is TRUE in include/config/text.h and src/easy_chat.c maps DPAD_LEFT to the next column."""
    import re
    src = hns.src_dir(emu.elf)
    if src not in _MIRROR_CACHE:
        try:
            cfg = open(os.path.join(src, "include", "config", "text.h"), encoding="utf-8").read()
            ec = open(os.path.join(src, "src", "easy_chat.c"), encoding="utf-8").read()
        except OSError:
            cfg = ec = ""
        _MIRROR_CACHE[src] = bool(re.search(r"#define\s+TEXT_RTL\s+TRUE", cfg)
                                  and re.search(r"JOY_REPEAT\(DPAD_LEFT\)\)\s*return MoveKeyboardCursor\(INPUT_RIGHT\)", ec))
    return _MIRROR_CACHE[src]


def _next_col(emu):
    """The key that moves an Easy Chat cursor to the next column."""
    return "LEFT" if ec_mirrored(emu) else "RIGHT"


def _prev_col(emu):
    return "RIGHT" if ec_mirrored(emu) else "LEFT"


def ec_const(emu, name):
    """EC_GROUP_* / EC_WORD_* from include/constants/easy_chat.h of the tree under test (hns.py's
    resolve_const does not include that header), else hns.resolve_const."""
    if not name.startswith("EC_"):
        return emu.const(name)
    src = hns.src_dir(emu.elf)
    if src not in _EC_CACHE:
        import re
        tab = {}
        txt = open(os.path.join(src, "include", "constants", "easy_chat.h"), encoding="utf-8").read()
        for m in re.finditer(r"^#define\s+(EC_\w+)\s+(.+?)\s*(?://.*)?$", txt, re.M):
            tab[m.group(1)] = m.group(2)
        _EC_CACHE[src] = tab
    tab = _EC_CACHE[src]

    def ev(n, depth=0):
        expr = tab[n]
        import re
        expr = re.sub(r"\b(EC_\w+)\b", lambda m: str(ev(m.group(1), depth + 1)), expr)
        return int(eval(expr, {"__builtins__": {}}))
    if name not in tab:
        raise HnsError("%s not in %s/include/constants/easy_chat.h" % (name, src))
    return ev(name)


def _s8(v):
    return v - 256 if v >= 128 else v


def _ecs(emu):
    p = emu.r32(emu.sym("sEasyChatScreen"))
    if not p:
        raise HnsError("Easy Chat: sEasyChatScreen is NULL (callback2 %s)" % emu.cb2_name())
    return p


def _get(emu, field):
    v = emu.r8(_ecs(emu) + ECS[field])
    return _s8(v) if field in ("mainCursorColumn", "mainCursorRow", "keyboardColumn", "keyboardRow",
                               "wordSelectColumn", "wordSelectRow") else v


def ec_wait(emu, mx=900):
    emu.wait_until(lambda: any(d[0] == 1 for d in emu.task_data("Task_EasyChatScreen")), mx,
                   "Task_EasyChatScreen to read input", step=1)
    emu.wait_quiet(mx)
    emu.frames(2)


def ec_tap(emu, key):
    emu.tap(key, 0)
    emu.frames(2)
    ec_wait(emu)


def _shot(emu, name):
    r3bf._shot(emu, name)


@script_op("ecwait")
def _op_ecwait(emu, f, path):
    ec_wait(emu, _arg(f, 1, 900))
    print("ecwait ok @%d" % emu.sync())


@script_op("ec")
def _op_ec(emu, f, path):
    for _ in range(_arg(f, 2, 1)):
        ec_tap(emu, f[1])
    print("ec %s x%d: state %s @%d" % (f[1], _arg(f, 2, 1), INPUTSTATES[_get(emu, "inputState")], emu.sync()))


def ec_state(emu):
    p = _ecs(emu)
    vals = {k: _get(emu, k) for k in ECS if k != "currentPhrase"}
    phrase = [emu.r16(p + ECS["currentPhrase"] + 2 * i) for i in range(vals["maxWords"])]
    return vals, phrase


@script_op("ecstate")
def _op_ecstate(emu, f, path):
    vals, phrase = ec_state(emu)
    print("ecstate %s %s phrase %s @%d" % (INPUTSTATES[vals["inputState"]],
                                           " ".join("%s=%d" % kv for kv in vals.items() if kv[0] != "inputState"),
                                           ["%04X" % w for w in phrase], emu.sync()))


def ec_slot(emu, row, col):
    for _ in range(12):
        r, c = _get(emu, "mainCursorRow"), _get(emu, "mainCursorColumn")
        if (r, c) == (row, col) and _get(emu, "inputState") == 0:
            return
        if r != row:
            ec_tap(emu, "DOWN" if r < row else "UP")
        else:
            ec_tap(emu, _next_col(emu) if c < col else _prev_col(emu))
    raise HnsError("ecslot: cursor at %d,%d, wanted %d,%d" % (_get(emu, "mainCursorRow"),
                                                             _get(emu, "mainCursorColumn"), row, col))


@script_op("ecslot")
def _op_ecslot(emu, f, path):
    ec_slot(emu, int(f[1]), int(f[2]))
    print("ecslot %s %s ok @%d" % (f[1], f[2], emu.sync()))


@script_op("ecbutton")
def _op_ecbutton(emu, f, path):
    want = int(f[1])
    rows = _get(emu, "numRows")
    for _ in range(16):
        st, r, c = _get(emu, "inputState"), _get(emu, "mainCursorRow"), _get(emu, "mainCursorColumn")
        if st == 1 and c == want:
            break
        if st != 1:
            ec_tap(emu, "UP" if r == 0 else "DOWN")       # UP from row 0 wraps onto the buttons
            continue
        ec_tap(emu, _next_col(emu) if c < want else _prev_col(emu))
    if _get(emu, "inputState") != 1 or _get(emu, "mainCursorColumn") != want:
        raise HnsError("ecbutton: state %s col %d" % (INPUTSTATES[_get(emu, "inputState")],
                                                       _get(emu, "mainCursorColumn")))
    print("ecbutton %d ok (rows %d) @%d" % (want, rows, emu.sync()))


def _wd(emu):
    p = emu.r32(emu.sym("sWordData"))
    if not p:
        raise HnsError("Easy Chat: sWordData is NULL")
    return p


def ec_group(emu, group):
    wd = _wd(emu)
    n = emu.r16(wd + WD_NUMGROUPS)
    ids = [emu.r16(wd + WD_GROUPIDS + 2 * i) for i in range(n)]
    if group not in ids:
        raise HnsError("ecgroup: group %d is not unlocked (%s)" % (group, ids))
    idx = ids.index(group)
    row, col = idx // 2, idx % 2
    for _ in range(40):
        r = _get(emu, "keyboardRow") + _get(emu, "keyboardScrollOffset")
        c = _get(emu, "keyboardColumn")
        if r == row and c == col:
            return idx
        if c == -1:
            ec_tap(emu, _next_col(emu))
        elif r != row:
            ec_tap(emu, "DOWN" if r < row else "UP")
        else:
            ec_tap(emu, _next_col(emu) if c < col else _prev_col(emu))
    raise HnsError("ecgroup: cursor stuck")


@script_op("ecgroup")
def _op_ecgroup(emu, f, path):
    idx = ec_group(emu, ec_const(emu, f[1]))
    print("ecgroup %s (index %d) ok @%d" % (f[1], idx, emu.sync()))


@script_op("ecletter")
def _op_ecletter(emu, f, path):
    row, col = int(f[1]), int(f[2])
    for _ in range(30):
        r, c = _get(emu, "keyboardRow"), _get(emu, "keyboardColumn")
        if (r, c) == (row, col):
            break
        if c == -1:
            ec_tap(emu, _next_col(emu))
        elif r != row:
            ec_tap(emu, "DOWN" if r < row else "UP")
        else:
            ec_tap(emu, _next_col(emu) if c < col else _prev_col(emu))
    print("ecletter %d %d: at %d,%d @%d" % (row, col, _get(emu, "keyboardRow"), _get(emu, "keyboardColumn"), emu.sync()))


def ec_words(emu):
    wd = _wd(emu)
    n = emu.r16(wd + WD_NUMSEL)
    return [emu.r16(wd + WD_SELWORDS + 2 * i) for i in range(n)]


def ec_word(emu, word):
    words = ec_words(emu)
    if word not in words:
        raise HnsError("ecword: word %04X not in the open list (%d words)" % (word, len(words)))
    idx = words.index(word)
    row, col = idx // 2, idx % 2
    for _ in range(400):
        r = _get(emu, "wordSelectRow") + _get(emu, "wordSelectScrollOffset")
        c = _get(emu, "wordSelectColumn")
        if r == row and c == col:
            return idx
        if r != row:
            ec_tap(emu, "DOWN" if r < row else "UP")
        else:
            ec_tap(emu, _next_col(emu) if c < col else _prev_col(emu))
    raise HnsError("ecword: cursor stuck")


@script_op("ecword")
def _op_ecword(emu, f, path):
    idx = ec_word(emu, ec_const(emu, f[1]))
    print("ecword %s (index %d) ok @%d" % (f[1], idx, emu.sync()))


@script_op("ecputword")
def _op_ecputword(emu, f, path):
    row, col, group, word = int(f[1]), int(f[2]), ec_const(emu, f[3]), ec_const(emu, f[4])
    prefix = f[5] if len(f) > 5 else None
    ec_slot(emu, row, col)
    ec_tap(emu, "A")
    if _get(emu, "inAlphabetMode"):
        ec_tap(emu, "SELECT")
    ec_group(emu, group)
    if prefix:
        _shot(emu, prefix + "_kbd")
    ec_tap(emu, "A")
    if _get(emu, "inputState") != 3:
        raise HnsError("ecputword: no word list (state %s)" % INPUTSTATES[_get(emu, "inputState")])
    ec_word(emu, word)
    if prefix:
        _shot(emu, prefix + "_list")
    ec_tap(emu, "A")
    _, phrase = ec_state(emu)
    slot = row * _get(emu, "numColumns") + col
    if phrase[slot] != word:
        raise HnsError("ecputword: slot %d holds %04X, wanted %04X" % (slot, phrase[slot], word))
    print("ecputword %d,%d <- %s ok @%d" % (row, col, f[4], emu.sync()))


@script_op("ecgroups")
def _op_ecgroups(emu, f, path):
    prefix = f[1]
    n = 1
    _shot(emu, "%s_%02d" % (prefix, n))
    last = _get(emu, "keyboardLastRow")
    while _get(emu, "keyboardRow") + _get(emu, "keyboardScrollOffset") < last - 1:
        before = _get(emu, "keyboardScrollOffset")
        ec_tap(emu, "DOWN")
        if _get(emu, "keyboardScrollOffset") != before:
            n += 1
            _shot(emu, "%s_%02d" % (prefix, n))
    print("ecgroups %s: %d shot(s), last row %d @%d" % (prefix, n, last, emu.sync()))


@script_op("eclist")
def _op_eclist(emu, f, path):
    prefix, mx = f[1], _arg(f, 2, 80)
    n = 1
    _shot(emu, "%s_%02d" % (prefix, n))
    while n < mx:
        before = _get(emu, "wordSelectScrollOffset")
        ec_tap(emu, "SELECT")
        if _get(emu, "wordSelectScrollOffset") == before:
            break
        n += 1
        _shot(emu, "%s_%02d" % (prefix, n))
    print("eclist %s: %d page(s), %d words @%d" % (prefix, n, len(ec_words(emu)), emu.sync()))


# struct PartyMenuInternal (src/party_menu.c:186-204): task, exitCallback, a u32 bitfield, then
# windowId[3] at +12, actions[8] at +15, numActions at +23. The action ids are the enum at
# src/party_menu.c:85-121 (7 MENU_MAIL, 8 MENU_TAKE_MAIL, 9 MENU_READ, 10 MENU_CANCEL2).
PMI_ACTIONS, PMI_NUMACTIONS = 15, 23


@script_op("partyact")
def _op_partyact(emu, f, path):
    """partyact ACTIONID: in an open party-menu action list, move the cursor (menu:sMenu+2) onto
    the row whose action is ACTIONID, no press."""
    want = int(f[1], 0)
    p = emu.r32(emu.sym("sPartyMenuInternal"))
    n = emu.r8(p + PMI_NUMACTIONS)
    acts = [emu.r8(p + PMI_ACTIONS + i) for i in range(n)]
    if want not in acts:
        raise HnsError("partyact: action %d not in %s" % (want, acts))
    idx = acts.index(want)
    try:
        cur = emu.sym("menu:sMenu") + 2
    except HnsError:
        cur = emu.sym("sMenu") + 2
    for _ in range(12):
        c = emu.r8(cur)
        if c == idx:
            break
        emu.tap("DOWN" if c < idx else "UP", 4)
        emu.wait_quiet(300)
    if emu.r8(cur) != idx:
        raise HnsError("partyact: cursor stayed %d" % emu.r8(cur))
    emu.frames(2)
    print("partyact %d: row %d of %s @%d" % (want, idx, acts, emu.sync()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
