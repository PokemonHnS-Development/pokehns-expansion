from ptx import *
import json, os, sys
e=Emu("pt.gba","pt.elf")
maps=[m for m in json.load(open("pt/sweep_maps.json")) if not m.endswith("PokemonCenter_2F") and "EverGrandeCity_Hall" not in m and m!="EverGrandeCity_HallOfFame"]
out={}
if os.path.exists("pt/sweep.json"): out=json.load(open("pt/sweep.json"))
st="pt/redcall3.ss"
for m in maps:
    if m in out: continue
    try:
        r=explore_fast(e,st,m,f"pt/sw/{m}",presses=9)
    except Exception as ex:
        r=[("error",str(ex),None,[],None)]
    out[m]=r; json.dump(out,open("pt/sweep.json","w"),indent=1)
    print(m,len(r),flush=True)
print("SWEEPDONE")
