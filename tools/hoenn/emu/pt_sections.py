#!/usr/bin/env python3
"""Section scripts for Claude's playtest (part 20). Run from the harness dir with
pt.gba/pt.elf; states and shots go to pt/. Each function takes a state and returns
(state_out, log) where log is a list of (label, texts)."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from pt import *

def trainers_run(e, state, map_name, prefix, log):
    for i, (x, y, sc, fl) in enumerate(trainers(map_name)):
        t, won = battle_npc(e, state, map_name, x, y, f"pt/{prefix}_{i}.ss", shots=f"pt/{prefix}_{i}")
        log.append((f"trainer {sc} won={won}", t))
        if won: state = f"pt/{prefix}_{i}.ss"
    return state

def gym_run(e, state, gym_map, prefix, leader_match, guide_match="GymGuide", post=16, extra_maps=()):
    log = []
    for j, m in enumerate(extra_maps):
        state = trainers_run(e, state, m, f"{prefix}_x{j}", log)
    objs = objects(gym_map)
    guide = [o for o in objs if guide_match in str(o[4])]
    if guide:
        t = talk_to(e, state, gym_map, guide_match, f"pt/{prefix}_guide.ss", presses=6, shots=f"pt/{prefix}_guide")
        log.append(("guide", t))
    for i, (x, y, sc, fl) in enumerate(trainers(gym_map)):
        t, won = battle_npc(e, state, gym_map, x, y, f"pt/{prefix}_tr{i}.ss", shots=f"pt/{prefix}_tr{i}")
        log.append((f"trainer {sc} won={won}", t))
        if won: state = f"pt/{prefix}_tr{i}.ss"
    leader = next(o for o in objs if leader_match in str(o[4]))
    t, won = battle_npc(e, state, gym_map, leader[2], leader[3], f"pt/{prefix}_leader.ss", pre=10, post=post,
                        shots=f"pt/{prefix}_leader")
    log.append((f"leader won={won}", t))
    return (f"pt/{prefix}_leader.ss" if won else state), log

def walk_outside(e, state, map_name, x, y, prefix, steps=40):
    """Walk back and forth outdoors so step hooks (event calls) run; returns texts seen."""
    g, n = map_of(map_name)
    s = e.go(state, g, n, x, y, f"pt/{prefix}_out.ss")
    s = e.walk(s, f"pt/{prefix}_walk.ss", "LR" * (steps // 2))
    t = e.talk(s, f"pt/{prefix}_call.ss", keys=["A"] * 14, wait=110, shots=f"pt/{prefix}_call")
    return f"pt/{prefix}_call.ss", t

def dump(log, path):
    json.dump(log, open(path, "w"), indent=1)
    for label, t in log:
        print("==", label)
        for x in t: print("   >", x)

START_FLAGS = [0x892, 0x1F3, 0x1DD, 0x893]          # PokéGear menu, match call, machine part, game clear
START_VARS = {0x408B: 7, 0x4076: 16}                # S.S. Aqua state, badge count

def s0_arrival(e, base, log):
    s = e.set_battle_style(base, "pt/start.ss")
    s = e.poke(s, "pt/start.ss", flags_on=START_FLAGS, vars_=START_VARS)
    s = e.go(s, 11, 4, 13, 12, "pt/oak_w.ss")
    log.append(("Oak", e.talk(s, "pt/oak1.ss", face="UP", presses=22, shots="pt/s0_oak")))
    s = e.go("pt/oak1.ss", 15, 3, 8, 9, "pt/verm_w.ss")
    log.append(("Vermilion sailor", e.talk(s, "pt/verm2.ss", face="DOWN", wait=90, shots="pt/s0_sail",
                                          keys=["A"] + ["DOWN"] * 5 + ["A"] * 6)))
    return "pt/verm2.ss"

def s1_birch(e, st, log):
    g, n = map_of("LittlerootTown_ProfessorBirchsLab")
    s = e.go(st, g, n, 6, 5, "pt/birch_w.ss")
    log.append(("Birch", e.talk(s, "pt/birch1.ss", face="UP", keys=["A"] + ["B"] * 16, wait=120, shots="pt/s1_birch")))
    return "pt/birch1.ss"
