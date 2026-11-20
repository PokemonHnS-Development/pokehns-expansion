#!/usr/bin/env python3
"""Build inventory.json, live_labels.json and batches.json in the output folder from the
outputs of extract.py, fr_style_graph.py and mapgraph2.py there."""
import json, re, os, glob, collections, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import invconfig as C
from extract import plain_runs, encode

SRC = C.SRC
SCR = C.OUT
NOTES = C.OUT

asm = json.load(open(f'{SCR}/asm_strings.json'))
cstr = json.load(open(f'{SCR}/c_strings.json'))
frg = json.load(open(f'{SCR}/fr_style_graph.json'))
mg2 = json.load(open(f'{SCR}/mapgraph2.json'))
es_files = C.ES_FILES

maps = {}
for f in glob.glob(f'{SRC}/data/maps/*/map.json'):
    d = json.load(open(f))
    maps[d['name']] = d
name2id = {n: d['id'] for n, d in maps.items()}

# ------------------------------------------------------------------ tiers
TIER_NAME = {1: 'core UI, system text and names', 2: 'battle text', 3: 'main story (story order)',
             4: 'side content', 5: 'post-game', 6: 'rarely seen / debug / link / unverified'}

# story stages for the 560 hns maps: (regex on map name without _hns, tier, stage, label)
STAGES = [
    (r'^(NewBarkTown|Route29$|Gate_Route29_Route46|Route46)', 3, 1, 'New Bark, Route 29'),
    (r'^(CherrygroveCity|Route30|Route31|Gate_Route31_VioletCity|DarkCave_SouthSide)', 3, 2, 'Cherrygrove, Routes 30-31'),
    (r'^(VioletCity|SproutTower|Route32|RuinsOfAlph|Gate_RuinsOfAlph|UnionCave|Route33)', 3, 3, 'Violet, Sprout Tower, Ruins of Alph, Union Cave'),
    (r'^(AzaleaTown|SlowpokeWell|IlexForest|Gate_AzaleaTown_IlexForest|Gate_IlexForest_Route34|Route34)', 3, 4, 'Azalea, Slowpoke Well, Ilex Forest'),
    (r'^(GoldenrodCity_RadioTower|GoldenrodCity_Underground)', 3, 8, 'Radio Tower takeover, Goldenrod Underground'),
    (r'^(GoldenrodCity_GameCorner)', 4, 41, 'Game Corner'),
    (r'^(GoldenrodCity|Route35|Gate_GoldenrodCity_Route35|NationalPark_Normal|Gate_NationalPark|Route36|Route37)', 3, 5, 'Goldenrod, National Park, Routes 35-37'),
    (r'^(NationalPark_BugContest)', 4, 40, 'Bug-Catching Contest'),
    (r'^(EcruteakCity|BurnedTower|Gate_EcruteakCity_Route38|Route38|Route39)', 3, 6, 'Ecruteak, Burned Tower, Routes 38-39'),
    (r'^(OlivineCity_Port|VermilionCity_Port|SSAqua)', 5, 50, 'S.S. Aqua'),
    (r'^(OlivineCity|Route40$|Route41|CianwoodCity|Cianwood)', 3, 7, 'Olivine, Lighthouse, Cianwood'),
    (r'^(Route42|Gate_EcruteakCity_Route42|MtMortar|Mahoganytown|MahoganyTown|Route43|Gate_MahoganyTown_Route43|Gate_Route43|LakeOfRage|RocketHideout)', 3, 8, 'Mahogany, Lake of Rage, Rocket Hideout'),
    (r'^(Route44|IcePath|BlackthornCity|DragonsDen|Route45|DarkCave_NorthSide|WhirlIslands|TinTower|BellchimeTrail)', 3, 9, 'Ice Path, Blackthorn, Whirl Islands, Tin Tower'),
    (r'^(Route27|Route26|TohjoFalls|ReceptionGate|VictoryRoadKanto|Route23|IndigoPlateau|PokemonLeague)', 3, 10, 'Routes 26-27, Victory Road, Pokemon League'),
    (r'^(SafariZone|Route47|Route48|CliffEdge|EmbeddedTower)', 4, 42, 'Safari Zone, Routes 47-48, Cliff Edge'),
    (r'^(ContestHall|LilycoveCity_Contest|UnusedContestHall)', 4, 43, 'Contests'),
    (r'^(VermilionCity|Route6|Route11|DiglettsCave|SaffronCity|Gate_SaffronCity|Saffron_Temp|Route5|Route7|Route8|CeladonCity|Gate_CeladonCity|LavenderTown|Route12|Route10|RockTunnel|Route9|CeruleanCity|Route24|Route25|Route4|MtMoon|PewterCity|Route3|Route2|Gate_Route2|Gate_ViridianForest|ViridianForest|ViridianCity|Route1$|Route22|PalletTown|Route21|CinnabarIsland|Route20|SeafoamIslands|Route19|FuchsiaCity|Gate_FuchsiaCity|Route18|Route17|Route16|Route15|Route14|Route13|Route28|CeruleanCave)', 5, 51, 'Kanto'),
    (r'^(MtSilver|SnowsweptCavern|Route49|Route50|NewSinjoh|SinjohRuins)', 5, 52, 'Mt. Silver, Sinjoh'),
    (r'^(BattleFrontier|BattlePyramidSquare|FallarborTown_BattleTent|SlateportCity_BattleTent|VerdanturfTown_BattleTent)', 5, 53, 'Battle Frontier, Battle Tents'),
    (r'^(TrainerHill|Gate_Route40_TrainerHill)', 5, 54, 'Trainer Hill'),
    (r'^(Melemele|Akala|UlaUla|Ulaula|Poni|AlolaWater)', 5, 55, 'Alola islands'),
    (r'^(BirthIsland|FaravayIsland|FarawayIsland|SouthernIsland)', 5, 56, 'Event islands'),
    (r'^(TradeCenter|UnionRoom|BattleColosseum|TestMap|Trees)', 6, 60, 'Link rooms, test maps'),
]

def stage_of_hns(name):
    base = re.sub(r'_hns$', '', name)
    for rx, tier, st, label in STAGES:
        if re.search(rx, base):
            return tier, st, label
    return 6, 69, 'unclassified'

# non-map files: (tier, order, group)
FIXED = {}
def fx(tier, order, group, *files):
    for f in files:
        FIXED[f] = (tier, order, group)

# tier 1: names first (the glossary must be locked before dialogue), then UI
fx(1, 1, 'names', 'src/data/types_info.h', 'src/pokemon.c', 'src/battle_main.c',
   'src/data/region_map/region_map_sections.json')
fx(1, 1.5, 'names', 'src/data/trainers_hns.party', 'src/data/battle_partners.party')
fx(1, 2, 'names', 'src/data/items.h')
fx(1, 3, 'names', 'src/data/moves_info.h')
fx(1, 4, 'names', 'src/data/abilities.h')
fx(1, 5, 'species (Gen 1-3: standard play)', 'src/data/pokemon/species_info/gen_1_families.h',
   'src/data/pokemon/species_info/gen_2_families.h', 'src/data/pokemon/species_info/gen_3_families.h',
   'src/data/pokemon/species_info/shared_dex_text.h', 'src/data/pokemon/species_info.h')
fx(1, 16, 'species (Gen 4-9: cross-gen evolutions, randomizer)', *[f'src/data/pokemon/species_info/gen_{i}_families.h' for i in range(4, 10)])
fx(1, 10, 'new game, menus', 'src/strings.c')
fx(1, 11, 'new game, menus', 'data/text/oak_speech_hns.inc', 'src/oak_speech_hns.c', 'src/challenge_menu.c',
   'src/main_menu.c', 'src/option_menu.c', 'src/start_menu.c', 'src/rtc.c', 'data/text/save.inc')
fx(1, 12, 'bag, party, summary, PC, naming', 'src/item_menu.c', 'src/item_use.c', 'src/item.c', 'src/party_menu.c',
   'src/data/party_menu.h', 'src/pokemon_summary_screen.c', 'src/pokemon_storage_system.c', 'src/player_pc.c',
   'data/text/pc.inc', 'data/text/pc_transfer.inc', 'data/scripts/pc.inc', 'data/scripts/pc_transfer.inc',
   'src/naming_screen.c', 'src/text_input_strings.c', 'src/string_util.c')
fx(1, 13, 'Pokedex, map, Pokegear', 'src/pokedex_plus_hgss.c', 'src/pokedex_area_screen.c', 'src/dexnav.c',
   'data/scripts/dexnav.inc', 'src/region_map.c', 'src/field_region_map.c', 'src/landmark.c', 'src/map_name_popup.c',
   'src/pokenav_main_menu.c', 'src/pokenav_menu_handler_gfx.c', 'src/pokenav_list.c', 'src/pokenav_match_call_gfx.c',
   'src/pokenav_match_call_list.c', 'src/pokenav_conditions_gfx.c', 'src/pokenav_conditions_search_results.c',
   'src/pokenav_ribbons_summary.c')
fx(1, 14, 'overworld common', 'data/event_scripts.s', 'src/data/script_menu.h', 'src/script_menu.c', 'src/scrcmd.c',
   'data/text/obtain_item.inc', 'data/scripts/obtain_item.inc', 'data/text/pkmn_center_nurse.inc',
   'data/scripts/pkmn_center_nurse.inc', 'data/text/mart_clerk.inc', 'data/scripts/field_move_scripts_hns.inc',
   'data/scripts/field_move_scripts.inc', 'data/text/surf.inc', 'data/scripts/surf.inc', 'data/scripts/repel.inc',
   'src/field_screen_effect.c', 'src/field_specials.c', 'src/fishing.c', 'src/field_weather.c', 'src/data/help_window.h',
   'data/scripts/check_furniture.inc', 'data/text/check_furniture.inc', 'data/scripts/players_house.inc',
   'data/scripts/std_msgbox.inc', 'data/scripts/trainer_battle.inc', 'data/scripts/flash.inc',
   'src/data/speaker_names.h')
fx(1, 15, 'follower Pokemon', 'src/follower_helper.c', 'src/data/text/follower_messages.h', 'data/scripts/follower.inc')
# tier 2: battle
fx(2, 20, 'battle', 'src/battle_message.c', 'src/battle_controller_player.c', 'src/battle_controller_oak_old_man.c',
   'src/battle_z_move.c', 'src/battle_interface.c', 'src/battle_setup.c')
# tier 3: story-wide text that is not a map file
fx(3, 1, 'story-wide', 'data/text/match_call_hns.inc', 'data/scripts/new_game.inc', 'data/scripts/mom_savings.inc')
fx(3, 10, 'Pokemon League', 'data/scripts/elite_four.inc', 'data/scripts/pokemon_league.inc', 'data/scripts/hall_of_fame.inc')
fx(3, 11, 'credits', 'src/data/credits_hns.h')
# tier 4: side content
fx(4, 40, 'Bug-Catching Contest', 'data/scripts/bug_contest.inc')
fx(4, 41, 'Game Corner', 'src/roulette.c', 'src/slot_machine.c', 'src/voltorb_flip.c', 'data/scripts/roulette.inc')
fx(4, 43, 'Contests', 'src/contest.c', 'src/contest_painting.c', 'src/data/contest_moves.h', 'src/data/contest_text_tables.h',
   'src/data/contest_opponents.h', 'data/scripts/contest_hall.inc', 'data/text/tv.inc')
fx(4, 44, 'day care, tutors, relearner', 'data/scripts/day_care.inc', 'data/scripts/move_tutors.inc', 'data/text/move_tutors.inc',
   'data/text/move_relearner.inc', 'data/scripts/move_relearner.inc')
fx(4, 45, 'berries, apricorns, Pokeblocks', 'src/berry.c', 'data/scripts/berry_tree.inc', 'data/text/berries.inc',
   'src/berry_tag_screen.c', 'src/berry_blender.c', 'data/scripts/berry_blender.inc', 'data/text/blend_master.inc',
   'src/pokeblock.c', 'src/pokeblock_feed.c', 'src/use_pokeblock.c', 'data/scripts/apricorn_tree.inc')
fx(4, 46, 'phone, radio', 'src/pokenav_match_call_data.c', 'data/text/match_call.inc', 'src/data/text/radio_strings.h', 'src/match_call.c')
for h in glob.glob(f'{SRC}/src/data/easy_chat/*.h'):
    FIXED[os.path.relpath(h, SRC)] = (4, 47, 'Easy Chat words')
fx(4, 48, 'decorations, ribbons, trades, misc side', 'src/data/decoration/header.h', 'src/data/decoration/description.h',
   'src/data/text/ribbon_descriptions.h', 'src/data/text/gift_ribbon_descriptions.h', 'src/data/trade.h', 'src/trader.c',
   'src/sliding_puzzle.c', 'src/trainer_fan_club.c', 'data/scripts/mauville_man.inc', 'data/text/mauville_man.inc',
   'data/text/pokedex_rating.inc', 'data/scripts/pokedex_rating.inc', 'data/text/pokemon_news.inc',
   'data/text/questionnaire.inc', 'data/scripts/questionnaire.inc', 'data/scripts/secret_base.inc',
   'data/scripts/shared_secret_base.inc', 'data/text/secret_base_trainers.inc', 'data/text/abnormal_weather.inc',
   'data/scripts/abnormal_weather.inc', 'data/scripts/safari_zone.inc', 'src/data/lilycove_lady.h', 'src/tv.c',
   'data/scripts/tv.inc', 'data/scripts/aide.inc', 'src/mail.c', 'src/lilycove_lady.c')
# tier 5: post-game
fx(5, 53, 'Battle Frontier', 'src/battle_dome.c', 'src/frontier_util.c', 'src/data/battle_frontier/battle_frontier_trainers.h',
   'src/data/battle_frontier/battle_tent.h', 'src/data/battle_frontier/apprentice.h', 'data/text/apprentice.inc',
   'data/text/battle_tent.inc', 'data/scripts/battle_frontier.inc', 'data/scripts/battle_pike.inc',
   'data/scripts/battle_pike_hns.inc', 'data/scripts/apprentice.inc')
fx(5, 54, 'Trainer Hill / Trainer Tower', 'src/data/battle_frontier/trainer_hill.h', 'src/trainer_tower_sets.c',
   'src/trainer_tower.c', 'data/scripts/trainer_hill.inc')
# tier 6: rare
fx(6, 60, 'link, Union Room, cable club', 'src/data/union_room.h', 'data/text/cable_club.inc', 'data/scripts/cable_club.inc',
   'data/scripts/cable_club_frlg.inc', 'data/scripts/record_mix.inc', 'data/text/record_mix.inc', 'src/dodrio_berry_picking.c')
fx(6, 61, 'Mystery Gift / events', 'src/mystery_event_msg.c', 'src/mystery_gift_scripts.c', 'data/text/event_ticket_1.inc',
   'data/text/event_ticket_2.inc', 'data/scripts/mystery_event_club.inc', 'src/berry_fix_program.c', 'src/save_failed_screen.c')
fx(6, 62, 'debug', 'src/debug.c', 'src/battle_debug.c', 'data/scripts/debug.inc', 'src/data/debug_trainers.party',
   'src/pokemon_sprite_visualizer.c', 'src/data/battle_environment.h', 'data/scripts/config.inc', 'data/scripts/test_signpost.inc')

GENERATED = {  # generated header -> source to edit
    'src/data/trainers.h': 'src/data/trainers.party',
    'src/data/trainers_frlg.h': 'src/data/trainers_frlg.party',
    'src/data/trainers_hns.h': 'src/data/trainers_hns.party',
    'src/data/battle_partners.h': 'src/data/battle_partners.party',
    'src/data/debug_trainers.h': 'src/data/debug_trainers.party',
    'src/data/region_map/region_map_entries.h': 'src/data/region_map/region_map_sections.json',
}

entries = []
live_labels = {}

def es_mark(f):
    return f in es_files

# ------------------------------------------------------------------ asm files
fr_reached = set(frg['reached_inherited']); fr_unreached = set(frg['unreached_inherited'])
for f, recs in sorted(asm.items()):
    L = [r for r in recs if r['letters']]
    if not L:
        continue
    live = [r for r in L if r['reach_release_nodebug']]
    dbg = [r for r in L if r['reach_release'] and not r['reach_release_nodebug']]
    meta = [r for r in live if r['via'] == ['metatile']]
    m = re.match(r'data/maps/([^/]+)/scripts.inc', f)
    e = dict(file=f, strings_total=len(L), strings_live=len(live), strings_debug_only=len(dbg),
             strings_metatile_only=len(meta), chars_live=sum(r['chars'] for r in live),
             braille=sum(1 for r in live if r['braille']), es_touched=es_mark(f))
    notes = []
    evidence = []
    if m:
        name = m.group(1)
        gv = maps.get(name, {}).get('game_version', 'emerald')
        e['kind'] = 'map_script_hns' if gv == 'hns' else f'map_script_{gv}'
        e['map_loadable'] = gv == 'hns'
        if gv == 'hns':
            tier, st, label = stage_of_hns(name)
            e['map_reached'] = name2id[name] not in mg2['unreached']
            if not e['map_reached']:
                notes.append('map not reached by warps/connections/script warps')
            how = mg2['reached'].get(name2id[name])
            if how and how[0] == 'code-script':
                notes.append('map reached only through a script warp in code-referenced scripts (UNVERIFIED in game)')
        else:
            e['map_reached'] = False
            evidence.append('header absent from hns build: map.json game_version="%s" (tools/mapjson/mapjson.cpp:722-733 and :474-478 write NULL in gMapGroups)' % gv)
            if name in fr_reached:
                e['fr_status'] = 'fr_reachable'
            elif name in fr_unreached:
                e['fr_status'] = 'fr_unreachable'
            refmaps = sorted(set(mm for r in live for mm in r['maps']))
            if refmaps:
                st_list = [stage_of_hns(mm) for mm in refmaps]
                tier, st, label = min(st_list, key=lambda x: (x[0], x[1]))
                notes.append('live labels are reused by: ' + ', '.join(refmaps[:6]) + (' ...' if len(refmaps) > 6 else ''))
            elif live and name.startswith('BattleFrontier'):
                tier, st, label = 5, 53, 'Battle Frontier'
                notes.append('live labels are referenced from C (Battle Frontier code tables)')
            else:
                tier, st, label = 6, 63, 'inherited text reached only through C / metatile behaviours'
            if meta and len(meta) == len(live):
                tier, st, label = 6, 63, 'inherited text reached only through metatile behaviours'
                notes.append('all live labels hang off GetInteractedMetatileScript (TV/door/shelf behaviours); shown only if an H&S tileset uses that behaviour (UNVERIFIED)')
        e['stage'] = label
    else:
        e['kind'] = 'script_common' if f.startswith('data/scripts/') else ('text_common' if f.startswith('data/text/') else 'event_scripts')
        if f in FIXED:
            tier, st, label = FIXED[f]
        else:
            refmaps = sorted(set(mm for r in live for mm in r['maps']))
            if refmaps:
                tier, st, label = min((stage_of_hns(mm) for mm in refmaps), key=lambda x: (x[0], x[1]))
                notes.append('reached from maps: ' + ', '.join(refmaps[:5]) + (' ...' if len(refmaps) > 5 else ''))
            elif live:
                tier, st, label = 4, 49, 'side (referenced from C)'
            else:
                tier, st, label = 6, 62, 'debug'
        e['stage'] = label
        if meta and len(meta) == len(live) and live:
            notes.append('all live labels hang off GetInteractedMetatileScript (UNVERIFIED in game)')
    if live and len(live) < len(L):
        notes.append(f'{len(L) - len(live) - len(dbg)} dead labels: translate only the labels in live_labels.json')
    if e['braille']:
        notes.append(f"{e['braille']} braille strings (.braille)")
    if dbg and not live:
        e['reach_class'] = 'debug-only'
    elif live and len(live) == len(L):
        e['reach_class'] = 'live'
    elif live:
        e['reach_class'] = 'partial'
    else:
        e['reach_class'] = 'dead'
    if e['reach_class'] == 'debug-only':
        tier, st, label = 6, 62, 'debug'
        e['stage'] = label
    e['reachable'] = e['reach_class'] in ('live', 'partial', 'debug-only')
    e['strings'] = len(live) if live else len(dbg)
    e['priority'] = tier if e['reachable'] else None
    e['order'] = st
    e['evidence'] = evidence
    e['notes'] = notes
    entries.append(e)
    if e['reachable']:
        live_labels[f] = dict(live=[r['label'] for r in live], debug_only=[r['label'] for r in dbg],
                              dead=[r['label'] for r in L if not r['reach_release']])

# map script files without any text: listed so that every map file is marked
have = set(e['file'] for e in entries)
for sp in sorted(glob.glob(f'{SRC}/data/maps/*/scripts.inc')):
    f = os.path.relpath(sp, SRC)
    if f in have:
        continue
    name = f.split('/')[2]
    gv = maps.get(name, {}).get('game_version', 'emerald')
    reached = gv == 'hns' and name2id[name] not in mg2['unreached']
    e = dict(file=f, kind='map_script_hns' if gv == 'hns' else f'map_script_{gv}', strings=0, strings_total=0,
             strings_live=0, strings_debug_only=0, strings_metatile_only=0, chars_live=0, braille=0,
             reach_class='no-text', reachable=reached, priority=None, order=99, stage=None,
             map_loadable=gv == 'hns', map_reached=reached, es_touched=es_mark(f),
             evidence=[] if gv == 'hns' else ['header absent from hns build (game_version="%s")' % gv],
             notes=['no player-visible text' + ('' if reached or gv != 'hns' else '; map not reached by warps/connections/script warps')])
    entries.append(e)

# ------------------------------------------------------------------ C files
owners = {}
def ckey(t):
    for run in sorted(plain_runs(t), key=len, reverse=True):
        if len(run) >= 6:
            e = encode(run)
            if e is not None and len(e) >= 6:
                return e
    return None
for f, recs in cstr.items():
    for r in recs:
        r['_k'] = ckey(r['text'])
        if r['_k']:
            owners.setdefault(r['_k'], set()).add(f)
C_OVERRIDES = {
    'src/data/credits.h': ('dead', 'included only by src/credits.c, whose body is under #if !IS_FRLG && !IS_HNS (src/credits.c:27, :1627)'),
}
DO_NOT_TRANSLATE = {'src/string_util.c': 'sDigits hex table (string_util.c:14); not text',
                    'src/dodrio_berry_picking.c': 'Japanese/ABC/0123 placeholder tables (dodrio_berry_picking.c:3064-3066)'}
for f, recs in sorted(cstr.items()):
    if f in GENERATED:
        continue
    L = [r for r in recs if r['letters']]
    if not L:
        continue
    uniq = [r for r in L if r['_k'] and len(owners[r['_k']]) == 1]
    found = [r for r in uniq if r['rom_release']]
    ratio = len(found) / len(uniq) if uniq else None
    file_live = ratio is None or ratio >= 0.5
    live = 0
    for r in L:
        if r['_k'] and len(owners[r['_k']]) == 1:
            live += 1 if r['rom_release'] else 0
        else:
            live += 1 if file_live else 0
    if ratio is None:
        cls = 'unverified'
    elif ratio >= 0.75:
        cls = 'live' if live >= 0.9 * len(L) else 'partial'
    elif ratio <= 0.25:
        cls = 'dead'
        live = 0
    else:
        cls = 'partial'
    if cls == 'unverified':
        named = [r for r in L if r.get('var') and re.match(r'^[sg][A-Z]', r['var']) and 'sym_release' in r]
        if named and len(named) == len(L):
            alive = sum(1 for r in named if r['sym_release'])
            # a present symbol proves the literal is linked; an absent one proves little
            # (LTO can fold a tiny const array into its users), so absence stays unverified
            if alive == len(L):
                cls = 'live'; live = len(L)
            elif alive > 0:
                cls = 'partial'; live = alive
    if f in C_OVERRIDES:
        cls, why = C_OVERRIDES[f]
        live = len(L) if cls == 'live' else 0
    kind = 'c_data' if f.startswith('src/data/') else 'c_source'
    tier, st, label = FIXED.get(f, (4, 49, 'side (C)'))
    notes = []
    evidence = [f'release ROM: {len(found)}/{len(uniq)} unique searchable literals present (pokehns-release.gba)']
    if f in C_OVERRIDES:
        evidence.append(C_OVERRIDES[f][1])
    elif any(r.get('var') and 'sym_release' in r for r in L) and ratio is None:
        evidence.append('named statics checked against pokehns-release.elf symbols')
    if f in DO_NOT_TRANSLATE:
        notes.append('do not translate: ' + DO_NOT_TRANSLATE[f])
        cls = 'not-text'
    if cls == 'unverified':
        notes.append('only short or duplicated literals; ROM search cannot decide (UNVERIFIED)')
    dead_ex = [f"{r['line']}" for r in uniq if not r['rom_release']][:8]
    if cls in ('partial', 'live') and dead_ex:
        notes.append(f'{len(uniq) - len(found)} literal(s) compiled out (absent from the release ROM; skip them), e.g. lines ' + ', '.join(dead_ex) + (' ...' if len(uniq) - len(found) > 8 else ''))
    e = dict(file=f, kind=kind, strings_total=len(L), strings_live=live if cls != 'not-text' else 0,
             strings_debug_only=0, strings_metatile_only=0,
             chars_live=sum(r['chars'] for r in L) if cls in ('live', 'unverified') else None,
             reach_class=cls, es_touched=es_mark(f), stage=label, order=st, evidence=evidence, notes=notes)
    if label == 'debug' or f in ('src/debug.c', 'src/battle_debug.c', 'src/pokemon_sprite_visualizer.c'):
        if cls in ('live', 'partial', 'unverified'):
            e['reach_class'] = 'debug-only'
            e['strings_debug_only'] = live
            e['strings_live'] = 0
    if f == 'src/data/battle_environment.h':
        notes.append('names are in ROM inside gBattleEnvironmentInfo but only printed by the sprite visualizer (pokemon_sprite_visualizer.c:991), which is absent from the release ROM')
        e['reach_class'] = 'debug-only'; e['strings_debug_only'] = len(L); e['strings_live'] = 0
    e['reachable'] = e['reach_class'] in ('live', 'partial', 'debug-only', 'unverified')
    e['strings'] = e['strings_live'] if e['strings_live'] else e['strings_debug_only']
    e['priority'] = (6 if e['reach_class'] == 'debug-only' else tier) if e['reachable'] else None
    entries.append(e)

# credits / pokedex old dex notes
# ------------------------------------------------------------------ generated sources
def party_names(path):
    names = []
    for line in open(f'{SRC}/{path}', encoding='utf-8'):
        m = re.match(r'^Name:\s*(.*?)\s*$', line)
        if m and re.search(r'[A-Za-z]', re.sub(r'\{[^}]*\}', '', m.group(1))):
            names.append(m.group(1))
    return names
PARTY = {
    'src/data/trainers_hns.party': ('live', 'compiled for IS_HNS (src/data.c:233-239)'),
    'src/data/trainers.party': ('dead', 'only compiled when !IS_FRLG && !IS_HNS (src/data.c:233-239)'),
    'src/data/trainers_frlg.party': ('dead', 'only compiled when IS_FRLG (src/data.c:233-239)'),
    'src/data/battle_partners.party': ('live', 'included by src/battle_partner.c:19; which partners appear in H&S is UNVERIFIED'),
    'src/data/debug_trainers.party': ('debug-only', 'included by src/debug.c:5175'),
}
for f, (cls, why) in PARTY.items():
    ns = party_names(f)
    u = sorted(set(ns))
    tier, st, label = FIXED.get(f, (6, 62, 'debug') if cls == 'debug-only' else (5, 69, 'dead'))
    e = dict(file=f, kind='party', strings_total=len(u), strings_live=len(u) if cls == 'live' else 0,
             strings_debug_only=len(u) if cls == 'debug-only' else 0, strings_metatile_only=0, chars_live=None,
             reach_class=cls, es_touched=es_mark(f), stage=label, order=st,
             evidence=[why, f'generates {[g for g, s in GENERATED.items() if s == f][0]} at build time (trainer_rules.mk)'],
             notes=[f'{len(ns)} Name: lines, {len(u)} distinct names; edit the .party file, never the generated .h'])
    e['reachable'] = cls in ('live', 'debug-only')
    e['strings'] = e['strings_live'] or e['strings_debug_only']
    e['priority'] = (6 if cls == 'debug-only' else tier) if e['reachable'] else None
    entries.append(e)
rj = json.load(open(f'{SRC}/src/data/region_map/region_map_sections.json'))
hns_names = [s for s in rj['hns_map_sections'] if s.get('name')]
emr_names = [s for s in rj['map_sections'] if s.get('name')]
entries.append(dict(file='src/data/region_map/region_map_sections.json', kind='json', strings_total=len(hns_names) + len(emr_names),
                    strings_live=len(hns_names), strings_debug_only=0, strings_metatile_only=0, chars_live=sum(len(s['name']) for s in hns_names),
                    reach_class='partial', es_touched=es_mark('src/data/region_map/region_map_sections.json'),
                    stage='names', order=1, reachable=True, strings=len(hns_names), priority=1,
                    evidence=['template src/data/region_map/region_map_sections.json.txt:5-8 emits hns_map_sections under #if IS_HNS',
                              'generates src/data/region_map/region_map_entries.h (json_data_rules.mk:4-6)'],
                    notes=[f'translate the {len(hns_names)} names in "hns_map_sections"; the {len(emr_names)} in "map_sections" are the non-hns branch',
                           'FireRed fork has a hebrew_name field per section (brief §3a)']))

# ------------------------------------------------------------------ code logic (no strings, language-specific code)
CODE_LOGIC = [
    ('src/item.c', 'English plural: appends "s" when an item has no plural name (item.c:194, 196-212); items.h has ITEM_PLURAL_NAME for 183 items'),
    ('src/battle_interface.c', 'English possessive for the ability pop-up: appends "\'" and "s" unless the name ends in s (battle_interface.c:2775-2778)'),
    ('src/pokedex_plus_hgss.c', 'search-by-name letter groups ABC..YZ built from CHAR_ ranges (pokedex_plus_hgss.c:1489-1497)'),
    ('src/international_string_util.c', 'category line order "<category> POKéMON"; the Spanish fork swapped it (git diff Release-v2.0.6 es/master -- src/international_string_util.c)'),
    ('src/berry_tag_screen.c', 'metric size suffix "cm" built from CHAR_c, CHAR_m (berry_tag_screen.c:180)'),
    ('src/union_room_chat.c', 'chat keyboard tables and case mapping from CHAR_ constants (union_room_chat.c, 52 CHAR_x uses)'),
    ('include/config/general.h', 'CHAR_DEC_SEPARATOR is CHAR_PERIOD; the Spanish fork switched it to CHAR_COMMA'),
    ('include/constants/global.h', 'ITEM_NAME_LENGTH 20 (global.h:174); the Spanish fork raised it to 21; check every length change against the save blocks first'),
]
existing = {e['file']: e for e in entries}
for f, why in CODE_LOGIC:
    if f in existing:
        existing[f]['notes'].append('language logic: ' + why)
        continue
    entries.append(dict(file=f, kind='code_logic', strings_total=0, strings_live=0, strings_debug_only=0, strings_metatile_only=0,
                        chars_live=None, reach_class='live', es_touched=es_mark(f), stage='language logic in code', order=99,
                        reachable=True, strings=0, priority=None, evidence=[], notes=[why]))

# ------------------------------------------------------------------ batches
work = [e for e in entries if e['reachable'] and e['strings'] > 0 and e['kind'] != 'code_logic']
for e in work:
    e['_sort'] = (e['priority'], e['order'], e['file'])
work.sort(key=lambda e: e['_sort'])
batches = []
cur = []; cur_n = 0; cur_tier = None
def close():
    global cur, cur_n
    if cur:
        batches.append(cur)
    cur = []; cur_n = 0
for e in work:
    n = e['strings']
    if cur_tier is not None and e['priority'] != cur_tier:
        close()
    cur_tier = e['priority']
    if n > 600:
        close(); batches.append([e]); continue
    if cur and cur_n + n > 600 and cur_n >= 300:
        close()
    elif cur and cur_n + n > 600 and cur_n < 300:
        # would overshoot: close anyway if it gets too big, keep small files together otherwise
        if cur_n + n > 750:
            close()
    cur.append(e); cur_n += n
close()
# merge any batch under 150 strings into its smaller neighbour of the same tier
def bsize(b):
    return sum(e['strings'] for e in b)
changed = True
while changed:
    changed = False
    for i, b in enumerate(batches):
        if bsize(b) >= 150:
            continue
        cands = [j for j in (i - 1, i + 1) if 0 <= j < len(batches) and batches[j][0]['priority'] == b[0]['priority']]
        if not cands:
            continue
        j = min(cands, key=lambda j: bsize(batches[j]))
        if j < i:
            batches[j] = batches[j] + b
        else:
            batches[j] = b + batches[j]
        del batches[i]
        changed = True
        break
for i, b in enumerate(batches, 1):
    for e in b:
        e['batch'] = f'B{i:02d}'
for e in entries:
    e.setdefault('batch', None)
    e.pop('_sort', None)
    if e['kind'] == 'map_script_hns' and e['reach_class'] == 'dead':
        e['notes'].append('every label in this _hns file is unreferenced (dead copies; the game shows other labels)')

# ------------------------------------------------------------------ write json
ORDER_KEYS = ['file', 'kind', 'strings', 'reachable', 'batch', 'priority', 'notes', 'reach_class', 'strings_total',
              'strings_live', 'strings_debug_only', 'strings_metatile_only', 'chars_live', 'braille', 'stage', 'order',
              'map_loadable', 'map_reached', 'fr_status', 'es_touched', 'evidence']
for e in entries:
    if not e['reachable']:
        e['stage'] = None
    e['notes'] = '; '.join(e['notes'])
out = []
for e in sorted(entries, key=lambda e: (e['batch'] or 'ZZZ', e['priority'] or 9, e['order'], e['file'])):
    out.append({k: e[k] for k in ORDER_KEYS if k in e})
json.dump(out, open(f'{NOTES}/inventory.json', 'w'), indent=1, ensure_ascii=False)
json.dump(live_labels, open(f'{NOTES}/live_labels.json', 'w'), indent=0)
json.dump([[e['file'] for e in b] for b in batches], open(f'{SCR}/batches.json', 'w'), indent=0)
print('entries', len(out), 'work files', len(work), 'batches', len(batches))
tot = collections.Counter()
for b in batches:
    print(b[0]['batch'], 'P%d' % b[0]['priority'], sum(e['strings'] for e in b), len(b), b[0]['file'], '...', b[-1]['file'])
