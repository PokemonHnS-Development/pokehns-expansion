from ptx import *
import json, sys
e=Emu("pt.gba","pt.elf")
L={}
def save(): json.dump(L,open("pt/s11.json","w"),indent=1)
def talk(key,st,mapname,match,keys=None,idx=0):
    objs=[o for o in objects(mapname) if match in str(o[4])]
    obj=objs[idx]
    g,n=map_of(mapname)
    for px,py,face in spots_next_to(mapname,obj[2],obj[3]):
        s=e.go(st,g,n,px,py,"_t11.ss")
        if e.where(s)[1:3]!=(px,py): continue
        t=e.talk(s,f"pt/{key}.ss",face=face,keys=keys or ["A"]+["B"]*14,wait=110,shots=f"pt/{key}")
        if t: L[key]=t; save(); print("DONE",key,len(t),flush=True); return f"pt/{key}.ss"
    L[key]=["(no text / unreachable)"]; save(); print("FAIL",key,flush=True); return st
def battle(key,st,mapname,match,pre=8,post=16,idx=0):
    obj=[o for o in objects(mapname) if match in str(o[4])][idx]
    t,won=battle_npc(e,st,mapname,obj[2],obj[3],f"pt/{key}.ss",pre=pre,post=post,shots=f"pt/{key}")
    L[key]=[f"won={won}"]+t; save(); print("DONE",key,won,flush=True)
    return f"pt/{key}.ss" if won is not None else st
L=json.load(open("pt/s11.json"))
st="pt/archie.ss"
st=battle("summit",st,"MtPyre_Summit","SummitLeaders",pre=14,post=20)
s=e.go(st,*map_of("MtPyre_Summit"),22,12,"_mp.ss")
t=e.walk_read(s,"pt/teamscall.ss","LR"*20,shots="pt/teamscall"); L["teams_call"]=t; save(); print("CALL",t,flush=True); st="pt/teamscall.ss"
st=talk("letter",st,"MossdeepCity_StevensHouse","Letter")
st=talk("stone",st,"MossdeepCity_StevensHouse","StevensStone",keys=["A","A","A","A","A","A","B","B","B","B","B"])
st=talk("mindreader",st,"MossdeepCity_GameCorner_1F","HoennSeek_EventScript_MindReader",keys=["A"]*3+["B"]*10)
st=talk("tester1",st,"Route120","Route120_EventScript_Steven")
st=talk("mrstone_scope",st,"RustboroCity_DevonCorp_3F","MrStone")
st=talk("tester2",st,"Route120","Route120_EventScript_Steven")
st=battle("kecleon",st,"Route120","BridgeKecleon")
st=talk("castform",st,"Route119_WeatherInstitute_2F","Castform") if any("Castform" in str(o[4]) for o in objects("Route119_WeatherInstitute_2F")) else st
st=talk("eggwoman",st,"LavaridgeTown","EggWoman")
st=talk("fossil",st,"RustboroCity_DevonCorp_2F","FossilScientist")
print("FINAL",st)
