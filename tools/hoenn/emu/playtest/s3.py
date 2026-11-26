from ptx import *
import json, shutil
e=Emu("pt.gba","pt.elf")
LOG={}
def run_gym(key,st,*a,**k):
    s,log=gym_run(e,st,*a,**k); LOG[key]=log; json.dump(LOG,open("pt/gyms.json","w"),indent=1)
    print("DONE",key,s,flush=True); return s
def talk_npc(key,st,mapname,match,keys=None,presses=12,out=None):
    out=out or f"pt/{key}.ss"
    obj=next(o for o in objects(mapname) if match in str(o[4]))
    g,n=map_of(mapname)
    for px,py,face in spots_next_to(mapname,obj[2],obj[3]):
        s=e.go(st,g,n,px,py,"_tn.ss")
        if e.where(s)[1:3]!=(px,py): continue
        t=e.talk(s,out,face=face,keys=keys or ["A"]+["B"]*presses,wait=110,shots=f"pt/{key}")
        if t: LOG[key]=[(key,t)]; json.dump(LOG,open("pt/gyms.json","w"),indent=1); print("DONE",key,flush=True); return out
    LOG[key]=[(key,["(could not reach)"])]; return st
st="pt/s2_called.ss"
st=run_gym("brawly",st,"DewfordTown_Gym","g2","Brawly")
# Wattson: favor first
st=talk_npc("wattson_gate",st,"MauvilleCity_Gym","Wattson")
g,n=map_of("NewMauville_Inside")
s=e.go(st,g,n,33,7,"_nm.ss")
s=e.walk(s,"_nm2.ss","U")
t=e.talk(s,"pt/nm_gen.ss",keys=["A"]*4,wait=110,shots="pt/g3_gen")
s=e.go("pt/nm_gen.ss",g,n,33,5,"_nm3.ss")
t+=e.talk(s,"pt/nm_gen.ss",face="UP",keys=["A"]+["B"]*4,wait=110); LOG["generator"]=[("generator",t)]
print("GEN",t,e.getvar("pt/nm_gen.ss",0) if False else "",flush=True)
st=run_gym("wattson","pt/nm_gen.ss","MauvilleCity_Gym","g3","Wattson")
st=run_gym("flannery",st,"LavaridgeTown_Gym_1F","g4","Flannery",extra_maps=("LavaridgeTown_Gym_B1F",))
s=e.go(st,*map_of("LavaridgeTown"),9,11,"_lv.ss")
t=e.walk_read(s,"pt/call4.ss","RL"*20,shots="pt/call4"); LOG["call_after_4"]=[("walk",t)]; st="pt/call4.ss"
print("CALL4",t,flush=True)
st=run_gym("norman",st,"PetalburgCity_Gym","g5","Norman")
st=talk_npc("winona_r119",st,"Route119","WinonaRoute119")
st=run_gym("winona",st,"FortreeCity_Gym","g6","Winona")
st=talk_npc("cozmo",st,"FallarborTown_CozmosHouse","Cozmo")
st=talk_npc("spacecenter",st,"MossdeepCity_SpaceCenter_1F","SpaceCenterMeteorite")
st=run_gym("tateliza",st,"MossdeepCity_Gym","g7","TateAndLiza")
st=run_gym("juan",st,"SootopolisCity_Gym_1F","g8","Juan",extra_maps=("SootopolisCity_Gym_B1F",))
s=e.go(st,*map_of("SootopolisCity"),31,18,"_so.ss")
t=e.walk_read(s,"pt/call8.ss","UD"*20,shots="pt/call8"); LOG["call_after_8"]=[("walk",t)]
json.dump(LOG,open("pt/gyms.json","w"),indent=1)
print("CALL8",t); print("ALLDONE")
