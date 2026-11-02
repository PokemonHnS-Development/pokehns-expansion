#!/usr/bin/env python3
"""hns.py plus the r10 travel ops (scripts/r10_bridges/r10travel.py: visit, walkto, drive ...), the
r3 mart ops (scripts/r3_marts/mart.py: listshots, listgo, setmoney, setbp, setexpensive ...) and
setpocket (scripts/r8_bfe/r8bfe.py), plus the ops the r10 store tours use (tours/r10_stores):

    clerk X Y PREFIX [STOPTASK ...]
                         walk to the object standing at (X, Y) (across a counter when needed),
                         face it, A, one shot per page (PREFIX_01 ...) until the shop menu
                         (Task_ShopMenu), a choice menu, a new screen or a free player
    signat X Y DIR PREFIX
                         stand next to tile (X, Y) facing DIR (UP, DOWN, LEFT, RIGHT), A, then
                         as clerk
    buyopen PREFIX       on the BUY / SELL / QUIT menu: BUY, wait for the list, shot PREFIX
    buyeach PREFIX [FIRST] [LAST]
                         for every item row (FIRST..LAST, default all): cursor to it, A, shot
                         what follows (PREFIX_rNN_a: the quantity window with the total, the
                         price question with YES/NO, or a sold-out / no-money line); from the
                         quantity window A again and shot the price question (PREFIX_rNN_b);
                         then NO / B back to the list. Nothing is bought.
    buy PREFIX ROW UPS YES|NO
                         buy row ROW: A, shot the quantity window (PREFIX_q01), UP x UPS with a
                         shot after the last (PREFIX_qNN), A, shot the question (PREFIX_ask),
                         YES or NO; after YES every page that follows (PREFIX_done_NN: thanks,
                         the Premier Ball line, no room, ...) until the list takes input again
    buyclose PREFIX      B out of the list, shot the shop menu that comes back (PREFIX)
    shopquit PREFIX      QUIT on the shop menu, one shot per farewell page, until free
    sellopen PREFIX POCKET [ITEM]
                         from the shop menu: SELL with the bag on POCKET (and the cursor on the
                         first slot holding ITEM), shot PREFIX
    sellpockets PREFIX   in the sell bag: RIGHT through every pocket, a shot each
    sell PREFIX UPS YES|NO
                         A on the selected item; then a shot of each step: can't-sell line
                         (PREFIX_no), or the how-many window (PREFIX_q01, after UP x UPS
                         PREFIX_qNN), the price question (PREFIX_ask), YES/NO, the sold line
                         (PREFIX_sold) and the list after it (PREFIX_after)
    sellclose PREFIX     B out of the sell bag, shot the shop menu (PREFIX)
    setpcchallenge N     challengeSettings.tx_Challenges_PkmnCenter = N (SB3+0x18 bits 0-1;
                         byte 8 of struct ChallengeSettings, include/global.h:302)
    setbadges N          FLAG_BADGE01_GET .. +N-1 set, the other 8 Johto / 8 Kanto flags clear
    fillfull POCKET ITEM [QTY]
                         every slot of POCKET holds ITEM x QTY (default 999)
    info                 print money, BP, coins, badges and the location

Run:  stores.py tour ROM OUT --tours <emu>/tours/r10_stores [--clip] [--only RE]
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.normpath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, os.path.join(EMU, "scripts", "r10_bridges"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r3_marts"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r8_bfe"))
import r10travel as tr  # noqa: E402  (registers the r2-r10 ops)
import mart  # noqa: E402,F401  (listshots, listgo, setmoney, setbp, setexpensive, setinfinitetms)
import r8bfe  # noqa: E402,F401  (setpocket, dumpbag)
import hns  # noqa: E402
from hns import script_op, HnsError, TourTimeout, _arg  # noqa: E402

SB3_PKMN_CENTER = 0x10 + 0x08
NUM_BADGES = 16
POCKETS = {"POCKET_ITEMS": 0, "POCKET_MEDICINE": 1, "POCKET_POKE_BALLS": 2, "POCKET_TM_HM": 3,
           "POCKET_BERRIES": 4, "POCKET_KEY_ITEMS": 5}
BP_POCKET, BP_CURSOR, BP_SCROLL = 5, 8, 0x14          # struct BagPosition (include/item_menu.h)
MART_ITEMCOUNT = 12                                    # struct MartInfo.itemCount (src/shop.c)


def _shot(emu, name):
    emu.wait_quiet(900)
    emu.frames(2)
    emu.shot(name)
    emu.shots = getattr(emu, "shots", []) + [name]


def _ctx(emu, s):
    emu._ctx = s


def _talk_until_shop(emu, prefix, stops):
    n, how = emu.talk(prefix, 20, "-", ["Task_ShopMenu"] + list(stops))
    emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (prefix, i + 1) for i in range(n)]
    print("talk %s: %d page(s), ended %s @%d" % (prefix, n, how, emu.sync()))
    return n, how


@script_op("clerk")
def _op_clerk(emu, f, path):
    tr.install_textlog(emu)
    x, y, prefix = int(f[1]), int(f[2]), f[3]
    m = tr.current_map(emu)
    av = tr.avoid_tiles(m)
    _ctx(emu, "clerk %s (%d,%d)" % (m["id"], x, y))
    live = [o for o in tr.objects(emu) if (o[1], o[2]) == (x, y)]
    if not live:
        tr.approach_spot(emu, x, y, av)
        live = [o for o in tr.objects(emu) if (o[1], o[2]) == (x, y)]
    if not live:
        raise HnsError("clerk: no object at (%d,%d): %s" % (x, y, tr.objects(emu)))
    r = tr.go_and_face(emu, tr.object_stands(emu, x, y), av)
    if not isinstance(r, tuple):
        raise HnsError("clerk: could not stand next to (%d,%d): %s" % (x, y, r))
    emu.tap("A", 0)
    n, how = _talk_until_shop(emu, prefix, f[4:])
    if n == 0:
        raise HnsError("clerk %s: no text" % prefix)


@script_op("signat")
def _op_signat(emu, f, path):
    tr.install_textlog(emu)
    x, y, d, prefix = int(f[1]), int(f[2]), f[3].upper(), f[4]
    dx, dy = tr.FACE[d]
    m = tr.current_map(emu)
    _ctx(emu, "sign %s (%d,%d)" % (m["id"], x, y))
    # the same sign script on the same row (a row of vending machines): any one of them will do
    script = [b.get("script") for b in m.get("bg_events", []) if (b["x"], b["y"]) == (x, y)]
    xs = [x] + sorted((b["x"] for b in m.get("bg_events", [])
                       if b["y"] == y and b["x"] != x and script and b.get("script") == script[0]),
                      key=lambda bx: abs(bx - x))
    r = None
    for sx in xs:
        r = tr.go_and_face(emu, [((sx - dx, y - dy), d)], tr.avoid_tiles(m))
        if isinstance(r, tuple):
            break
    if not isinstance(r, tuple):
        raise HnsError("signat: could not stand at (%d,%d) facing %s: %s" % (x - dx, y - dy, d, r))
    emu.tap("A", 0)
    n, how = _talk_until_shop(emu, prefix, f[5:])
    if n == 0:
        raise HnsError("signat %s: no text" % prefix)


def _wait_tasks(emu, names, maxf=900, what=None):
    want = {}
    for n in names:
        try:
            want[emu.sym(n)] = n
        except HnsError:
            pass
    found = []

    def cond():
        found[:] = [want[fn] for _, fn, _ in emu.tasks() if fn in want]
        return bool(found)
    emu.wait_until(cond, maxf, what or "/".join(names), step=2)
    return found[0]


def _list_ready(emu):
    _wait_tasks(emu, ["Task_BuyMenu"], 900)
    emu.wait_quiet(900)
    emu.frames(4)


@script_op("buyopen")
def _op_buyopen(emu, f, path):
    tr.install_textlog(emu)
    _ctx(emu, "buy list")
    _wait_tasks(emu, ["Task_ShopMenu"], 600)
    emu.wait_quiet(600)
    emu.tap("A", 4)
    emu.wait_until(lambda: emu.cb2_name().endswith("CB2_BuyMenu"), 900, "the buy menu", step=4)
    _list_ready(emu)
    _shot(emu, f[1])


def _item_count(emu):
    return emu.r16(emu.sym("sMartInfo") + MART_ITEMCOUNT)


def _listgo(emu, want):
    for _ in range(200):
        cur = mart.list_pos(emu)
        if cur == want:
            break
        emu.tap("DOWN" if cur < want else "UP", 6)
        emu.wait_quiet(900)
    if mart.list_pos(emu) != want:
        raise HnsError("listgo %d: cursor stuck at %d" % (want, mart.list_pos(emu)))
    emu.frames(2)


# tasks that wait for A/B after a message that has no key-wait code of its own (src/shop.c)
KEY_TASKS = ["Task_ReturnToItemListAfterItemPurchase", "Task_ReturnToItemListAfterDecorationPurchase",
             "Task_ExitKurtShopAfterPurchase"]
AFTER_A = ["Task_BuyHowManyDialogueHandleInput", "Task_CallYesOrNoCallback"]


def _after_a(emu):
    """After A on a row: 'qty', 'yesno' or 'msg' (a line that waits for a key)."""
    def cond():
        if emu.tasks_named(AFTER_A):
            return True
        return emu.wants_key()
    emu.wait_until(cond, 900, "the quantity window, the YES/NO or a message", step=2)
    emu.wait_quiet(900)
    emu.frames(6)
    t = emu.tasks_named(AFTER_A)
    if t:
        return "qty" if t[0] == AFTER_A[0] else "yesno"
    return "msg"


def _ack_to_list(emu, prefix=None, maxpages=6):
    """A through message pages until the buy list takes input again (shot each page when PREFIX)."""
    n = 0
    for _ in range(maxpages):
        emu.wait_until(lambda: emu.wants_key() or emu.tasks_named(["Task_BuyMenu"] + KEY_TASKS) != [], 900,
                       "the list or the next page", step=2)
        if emu.tasks_named(["Task_BuyMenu"]):
            break
        emu.wait_quiet(900)
        n += 1
        if prefix:
            _shot(emu, "%s_%02d" % (prefix, n))
        emu.tap("A", 4)
    _list_ready(emu)
    return n


@script_op("buywait")
def _op_buywait(emu, f, path):
    """buywait PREFIX: the buy list opens by itself (Kurt): wait for it, shot PREFIX."""
    tr.install_textlog(emu)
    _ctx(emu, "buy list")
    emu.wait_until(lambda: emu.cb2_name().endswith("CB2_BuyMenu"), 1200, "the buy menu", step=4)
    _list_ready(emu)
    _shot(emu, f[1])


@script_op("buyeach")
def _op_buyeach(emu, f, path):
    tr.install_textlog(emu)
    prefix = f[1]
    cnt = _item_count(emu)
    first = _arg(f, 2, 0)
    last = _arg(f, 3, cnt - 1)
    for row in range(first, min(last, cnt - 1) + 1):
        _ctx(emu, "buyeach row %d" % row)
        _listgo(emu, row)
        emu.tap("A", 4)
        k = _after_a(emu)
        base = "%s_r%02d" % (prefix, row)
        _shot(emu, base + "_a")
        if k == "qty":
            emu.tap("A", 4)
            k2 = _after_a(emu)
            _shot(emu, base + "_b")
            if k2 == "yesno":
                emu.tap("B", 4)
            else:
                emu.tap("A", 4)
            _ack_to_list(emu)
        elif k == "yesno":
            emu.tap("B", 4)
            _ack_to_list(emu)
        else:
            emu.tap("A", 4)
            _ack_to_list(emu)
    print("buyeach %s: rows %d..%d of %d @%d" % (prefix, first, min(last, cnt - 1), cnt, emu.sync()))


@script_op("buy")
def _op_buy(emu, f, path):
    tr.install_textlog(emu)
    prefix, row, ups, yes = f[1], int(f[2]), int(f[3]), f[4].upper() == "YES"
    _ctx(emu, "buy row %d x%d %s" % (row, ups + 1, f[4]))
    _listgo(emu, row)
    emu.tap("A", 4)
    k = _after_a(emu)
    if k == "qty":
        _shot(emu, prefix + "_q01")
        for i in range(ups):
            emu.tap("UP" if ups < 50 else "UP", 3)
            emu.frames(2)
        if ups:
            emu.wait_quiet(300)
            _shot(emu, "%s_q%02d" % (prefix, ups + 1))
        emu.tap("A", 4)
        k = _after_a(emu)
    if k == "msg":
        _shot(emu, prefix + "_msg")
        emu.tap("A", 4)
        _ack_to_list(emu)
        return
    _shot(emu, prefix + "_ask")
    emu.tap("A" if yes else "B", 4)
    if yes:
        n = _ack_to_list(emu, prefix + "_done")
        _shot(emu, prefix + "_after")
        print("buy %s: %d page(s) after YES @%d" % (prefix, n, emu.sync()))
    else:
        _ack_to_list(emu)


@script_op("buymax")
def _op_buymax(emu, f, path):
    """buymax PREFIX ROW YES|NO: as buy, but DOWN once in the quantity window (1 wraps to the
    maximum the money or the bag allows)."""
    tr.install_textlog(emu)
    prefix, row, yes = f[1], int(f[2]), f[3].upper() == "YES"
    _ctx(emu, "buymax row %d %s" % (row, f[3]))
    _listgo(emu, row)
    emu.tap("A", 4)
    k = _after_a(emu)
    if k == "qty":
        _shot(emu, prefix + "_q01")
        emu.tap("DOWN", 4)
        emu.wait_quiet(300)
        _shot(emu, prefix + "_qmax")
        emu.tap("A", 4)
        k = _after_a(emu)
    if k == "msg":
        _shot(emu, prefix + "_msg")
        emu.tap("A", 4)
        _ack_to_list(emu)
        return
    _shot(emu, prefix + "_ask")
    emu.tap("A" if yes else "B", 4)
    if yes:
        _ack_to_list(emu, prefix + "_done")
        _shot(emu, prefix + "_after")
    else:
        _ack_to_list(emu)


@script_op("buyclose")
def _op_buyclose(emu, f, path):
    _ctx(emu, "buy list closed")
    _list_ready(emu)
    emu.tap("B", 4)
    emu.wait_until(lambda: emu.in_overworld() and bool(emu.tasks_named(["Task_ShopMenu"])), 900,
                   "the shop menu again", step=4)
    emu.wait_quiet(600)
    emu.frames(10)
    _shot(emu, f[1])


@script_op("shopquit")
def _op_shopquit(emu, f, path):
    tr.install_textlog(emu)
    _ctx(emu, "shop quit")
    _wait_tasks(emu, ["Task_ShopMenu"], 600)
    emu.wait_quiet(600)
    # the cursor to QUIT: the last row (BUY/SELL/QUIT or BUY/QUIT)
    emu.tap("B", 4)
    n, how = emu.talk(f[1], 10, "-")
    emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (f[1], i + 1) for i in range(n)]
    if how != "free":
        n2, how2 = tr.drive(emu, f[1] + "_x")
    emu.wait_until(emu.controllable, 900, "a free player", step=4)
    print("shopquit %s: %d page(s) @%d" % (f[1], n, emu.sync()))


def _pocket_slots(emu, p):
    base = emu.sym("gBagPockets") + 8 * p
    slots = emu.r32(base)
    cap = emu.r16(base + 4) & 0x3FF
    return [(emu.r16(slots + 4 * i)) for i in range(cap)]


@script_op("sellopen")
def _op_sellopen(emu, f, path):
    tr.install_textlog(emu)
    prefix = f[1]
    p = POCKETS[f[2]] if f[2] in POCKETS else int(f[2], 0)
    row = 0
    if len(f) > 3:
        iid = emu.const(f[3])
        slots = _pocket_slots(emu, p)
        if iid not in slots:
            raise HnsError("sellopen: %s not in pocket %s" % (f[3], f[2]))
        if p in (3, 4):
            # the bag sorts the TM and berry pockets when it opens: order by item id
            row = sorted(s for s in slots if s).index(iid)
        else:
            row = [s for s in slots if s].index(iid)
    bp = emu.sym("gBagPosition")
    shown = 8
    scroll = max(0, row - (shown - 1)) if row >= shown else 0
    emu.w8(bp + BP_POCKET, p)
    emu.w16(bp + BP_CURSOR + 2 * p, row - scroll)
    emu.w16(bp + BP_SCROLL + 2 * p, scroll)
    _ctx(emu, "sell %s %s" % (f[2], f[3] if len(f) > 3 else ""))
    _wait_tasks(emu, ["Task_ShopMenu"], 600)
    emu.wait_quiet(600)
    # BUY is row 0, SELL row 1 (sShopMenuActions_BuySellQuit); CreateShopMenu puts the cursor
    # on row 0 every time the menu is drawn (InitMenuInUpperLeftCornerNormal(.., 0), src/shop.c)
    emu.tap("DOWN", 6)
    emu.wait_quiet(200)
    _shot(emu, prefix + "_menu")
    emu.tap("A", 4)
    if not emu.wait32(emu.CB2, emu.sym("CB2_BagMenuRun"), 900):
        raise TourTimeout("sellopen: no CB2_BagMenuRun (callback2 %s)" % emu.cb2_name())
    _wait_tasks(emu, ["Task_BagMenu_HandleInput"], 900)
    emu.wait_quiet(900)
    emu.frames(10)
    _shot(emu, prefix)


@script_op("sellpockets")
def _op_sellpockets(emu, f, path):
    prefix = f[1]
    bp = emu.sym("gBagPosition")
    start = emu.r8(bp + BP_POCKET)
    for i in range(6):
        before = emu.r8(bp + BP_POCKET)
        emu.tap("RIGHT", 4)
        emu.wait_until(lambda: emu.r8(bp + BP_POCKET) != before, 120, "the next pocket", step=2)
        _wait_tasks(emu, ["Task_BagMenu_HandleInput"], 900)
        emu.wait_quiet(900)
        emu.frames(10)
        if emu.r8(bp + BP_POCKET) == start:
            break
        _shot(emu, "%s_p%d" % (prefix, emu.r8(bp + BP_POCKET)))


@script_op("sell")
def _op_sell(emu, f, path):
    tr.install_textlog(emu)
    prefix, ups, yes = f[1], int(f[2]), f[3].upper() == "YES"
    _ctx(emu, "sell x%d %s" % (ups + 1, f[3]))
    emu.tap("A", 4)
    qty_task = "Task_ChooseHowManyToSell"
    emu.wait_until(lambda: emu.wants_key() or bool(emu.tasks_named([qty_task, "Task_CallYesOrNoCallback"])),
                   900, "the sell message", step=2)
    emu.wait_quiet(900)
    emu.frames(6)
    if emu.tasks_named([qty_task]):
        _shot(emu, prefix + "_q01")
        for _ in range(ups):
            emu.tap("UP", 3)
            emu.frames(2)
        if ups:
            emu.wait_quiet(300)
            _shot(emu, "%s_q%02d" % (prefix, ups + 1))
        emu.tap("A", 4)
        emu.wait_until(lambda: bool(emu.tasks_named(["Task_CallYesOrNoCallback"])), 900, "the YES/NO", step=2)
        emu.wait_quiet(900)
        emu.frames(6)
    if emu.tasks_named(["Task_CallYesOrNoCallback"]):
        _shot(emu, prefix + "_ask")
        emu.tap("A" if yes else "B", 4)
        if yes:
            emu.wait_until(lambda: emu.wants_key() or bool(emu.tasks_named(["WaitAfterItemSell"])), 900,
                           "the sold line", step=2)
            emu.wait_quiet(900)
            emu.frames(10)
            _shot(emu, prefix + "_sold")
            emu.tap("A", 4)
    else:
        _shot(emu, prefix + "_no")
        emu.tap("A", 4)
    _wait_tasks(emu, ["Task_BagMenu_HandleInput"], 900)
    emu.wait_quiet(900)
    emu.frames(6)
    _shot(emu, prefix + "_after")


@script_op("sellclose")
def _op_sellclose(emu, f, path):
    _ctx(emu, "sell closed")
    _wait_tasks(emu, ["Task_BagMenu_HandleInput"], 900)
    emu.tap("B", 4)
    emu.wait_until(lambda: emu.in_overworld() and bool(emu.tasks_named(["Task_ShopMenu"])), 900,
                   "the shop menu after selling", step=4)
    emu.wait_quiet(600)
    emu.frames(10)
    _shot(emu, f[1])


@script_op("chat")
def _op_chat(emu, f, path):
    """chat PREFIX TOKEN ...: go on with the dialogue on screen. One shot per text page
    (PREFIX_<seg>_NN) and one of every choice menu; at each menu the next TOKEN: A (the selected
    row, YES), B (cancel, NO), dN / uN (DOWN / UP N times, then A), stay (leave the menu open and
    end). A menu with no token left gets B. Ends when the player is free, at the shop menu or on
    another screen."""
    tr.install_textlog(emu)
    prefix, toks = f[1], list(f[2:])
    emu._chat_b = 0
    seg = 0
    while True:
        seg += 1
        sp = "%s_%d" % (prefix, seg)
        _ctx(emu, "chat %s" % sp)
        n, how = emu.talk(sp, 30, "-", ["Task_ShopMenu"])
        emu.shots = getattr(emu, "shots", []) + ["%s_%02d" % (sp, i + 1) for i in range(n)]
        print("chat %s: %d page(s), ended %s @%d" % (sp, n, how, emu.sync()))
        if how == "free" or how.startswith("screen:") or how == "menu:Task_ShopMenu":
            return
        if not how.startswith("menu:"):
            raise HnsError("chat %s: ended %s" % (sp, how))
        if not toks:
            extra = getattr(emu, "_chat_b", 0) + 1
            emu._chat_b = extra
            if extra > 6:
                raise HnsError("chat %s: still in menus after 6 B presses" % sp)
            emu.tap("B", 4)
            emu.frames(4)
            continue
        emu._chat_b = 0
        t = toks.pop(0)
        if t == "stay":
            return
        if t in ("A", "B"):
            emu.tap(t, 4)
        elif t[0] in "du":
            for _ in range(int(t[1:])):
                emu.tap("DOWN" if t[0] == "d" else "UP", 6)
                emu.wait_quiet(200)
            emu.frames(4)
            _shot(emu, sp + "_pick")
            emu.tap("A", 4)
        else:
            raise HnsError("chat: bad token %s" % t)
        emu.frames(4)


def _script_texts(emu, label, nbytes=400):
    """Text pointers of the msgbox / message calls in the script at LABEL, in order: every
    'loadword 0, PTR' (0F 00 PTR32) with PTR in ROM, read from the ROM file."""
    base = emu.sym(label)
    rom = open(emu.rom, "rb").read()
    off = base - 0x08000000
    b = rom[off:off + nbytes]
    out = []
    for i in range(len(b) - 5):
        if b[i] == 0x0F and b[i + 1] == 0:
            ptr = int.from_bytes(b[i + 2:i + 6], "little")
            if 0x08000000 <= ptr < 0x0A000000:
                out.append(ptr)
    return out


@script_op("evtexts")
def _op_evtexts(emu, f, path):
    """evtexts ITEM LABEL:N ...: show the Nth (1-based) msgbox text of the ROM script at LABEL, for
    each argument in order, with STR_VAR_1/STR_VAR_2 = ITEM's name, from an event script in RAM
    (for lines a random roll hides). Follow with chat."""
    item = f[1]
    body = "lockall; bufferitemname STR_VAR_1, %s; bufferitemname STR_VAR_2, %s; " % (item, item)
    for a in f[2:]:
        lab, _, n = a.partition(":")
        ptrs = _script_texts(emu, lab)
        body += "msgbox 0x%08X, MSGBOX_DEFAULT; " % ptrs[int(n) - 1]
    body += "releaseall; end"
    print("evtexts: %s" % body)
    hns.event_start(emu, body, "evtexts")


@script_op("setcoins")
def _op_setcoins(emu, f, path):
    key = emu.r32(mart._sb2(emu) + 0xAC) & 0xFFFF
    emu.w16(mart._sb1(emu) + 0x498, int(f[1], 0) ^ key)
    print("setcoins %s" % f[1])


@script_op("tapA")
def _op_tapa(emu, f, path):
    """tapA: press A on whatever the player faces (no shot)."""
    emu.tap("A", 0)


@script_op("setpcchallenge")
def _op_setpcchallenge(emu, f, path):
    a = mart._sb3(emu) + SB3_PKMN_CENTER
    old = emu.r8(a)
    emu.w8(a, (old & ~3) | (int(f[1], 0) & 3))
    print("setpcchallenge %s: byte %08X %02X -> %02X" % (f[1], a, old, emu.r8(a)))


@script_op("setbadges")
def _op_setbadges(emu, f, path):
    n = int(f[1], 0)
    first = emu.const("FLAG_BADGE01_GET")
    for i in range(NUM_BADGES):
        emu.set_flag(first + i, i < n)
    print("setbadges %d" % n)


@script_op("fillfull")
def _op_fillfull(emu, f, path):
    p = POCKETS[f[1]] if f[1] in POCKETS else int(f[1], 0)
    item = emu.const(f[2])
    qty = _arg(f, 3, 999)
    bp = emu.sym("gBagPockets") + 8 * p
    slots, cap = emu.r32(bp), emu.r16(bp + 4) & 0x3FF
    key = emu.r32(emu.r32(emu.sym("gSaveBlock2Ptr")) + 0xAC) & 0xFFFF
    for i in range(cap):
        emu.w16(slots + 4 * i, item)
        emu.w16(slots + 4 * i + 2, qty ^ key)
    print("fillfull %s: %d slot(s) of %s x%d" % (f[1], cap, f[2], qty))


@script_op("info")
def _op_info(emu, f, path):
    sb1, sb2 = mart._sb1(emu), mart._sb2(emu)
    key = emu.r32(sb2 + 0xAC)
    money = emu.r32(sb1 + mart.SB1_MONEY) ^ key
    bp = emu.r16(sb2 + mart.SB2_BP)
    first = emu.const("FLAG_BADGE01_GET")
    badges = "".join("1" if emu.get_flag(first + i) else "0" for i in range(NUM_BADGES))
    print("info money %d bp %d badges %s loc %s" % (money, bp, badges, emu.location()))


if __name__ == "__main__":
    sys.argv[0] = hns.__file__
    sys.exit(hns.main())
