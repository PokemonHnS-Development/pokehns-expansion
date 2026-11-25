from ptx import *
import json
e=Emu("pt.gba","pt.elf")
L={}
exec(open("s11.py").read().split("st=\"pt/call8.ss\"")[0].split("L={}")[1])  # reuse talk()/battle()/save()
def save(): json.dump(L,open("pt/s12.json","w"),indent=1)
def walkcall(key,st,mapname,x,y):
    s=e.go(st,*map_of(mapname),x,y,"_wc.ss")
    t=e.walk_read(s,f"pt/{key}.ss","LR"*20,shots=f"pt/{key}"); L[key]=t; save(); print("CALL",key,t,flush=True); return f"pt/{key}.ss"
st="pt/fossil.ss"
st=battle("kecleon",st,"Route120","Route120_EventScript_Steven",pre=8)
st=battle("vrwally",st,"VictoryRoad_1F","VRWally",pre=10,post=20)
st=talk("leagueguard",st,"EverGrandeCity_PokemonLeague_1F","DoorGuard",keys=["A"]*6)
for nm in ["Sidney","Phoebe","Glacia","Drake"]:
    st=battle(nm.lower(),st,f"EverGrandeCity_{nm}sRoom",nm,pre=12,post=12)
s=e.go(st,*map_of("EverGrandeCity_ChampionsRoom"),6,11,"_cr.ss")
t=e.talk(s,"_cr2.ss",keys=["A"]*14,wait=110,shots="pt/wallace_pre"); L["wallace_pre"]=t; save()
print("WALLACE in battle?",e.where("_cr2.ss"),flush=True)
st2="_cr2.ss"
for k in range(40):
    if not e.where(st2)[3]: break
    e.unstick_party(st2)
    ft,still=e.fight(st2,"_cr3.ss",rounds=12); st2="_cr3.ss"; L.setdefault("wallace_battle",[]).extend(ft)
t=e.talk(st2,"pt/wallace_post.ss",keys=["B"]*40,wait=120,shots="pt/wallace_post"); L["wallace_post"]=t; save()
print("POST",t,e.where("pt/wallace_post.ss"),flush=True)
st=walkcall("bmback","pt/wallace_post.ss","LittlerootTown",14,14)
st=battle("bm",st,"LittlerootTown","RivalsOutside",pre=14,post=30)
st=walkcall("elmcall",st,"LittlerootTown",14,14)
st=talk("labball",st,"NewBarkTown_Lab_hns","LabBallChikorita",keys=["A"]+["B"]*12)
st=talk("silverguard",st,"ReceptionGate_hns","SilverGuard")
st=battle("red",st,"MtSilver_SummitDay_hns","Red",pre=6,post=16)
st=walkcall("redcall",st,"NewBarkTown_hns",10,10)
print("FINAL",st)
