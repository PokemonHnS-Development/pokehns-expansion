from ptx import *
import json
e=Emu("pt.gba","pt.elf")
L=json.load(open("pt/gyms.json"))
def lead(key,st,mapname,match,pre=10,post=18):
    obj=next(o for o in objects(mapname) if match in str(o[4]))
    t,won=battle_npc(e,st,mapname,obj[2],obj[3],f"pt/{key}_L.ss",pre=pre,post=post,shots=f"pt/{key}_L")
    L[key+"_leader2"]=[(f"leader won={won}",t)]; json.dump(L,open("pt/gyms.json","w"),indent=1)
    print("DONE",key,won,flush=True)
    return f"pt/{key}_L.ss" if won else st
st="pt/nm3.ss"
st=lead("g3",st,"MauvilleCity_Gym","Wattson")
st=lead("g5",st,"PetalburgCity_Gym","Norman",pre=14)
st=lead("g7",st,"MossdeepCity_Gym","TateAndLiza",pre=14)
st=lead("g8",st,"SootopolisCity_Gym_1F","Juan",pre=20)
print("FINAL",st)
