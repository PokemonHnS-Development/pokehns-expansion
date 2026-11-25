# ex.py STATE PREFIX MAP [MAP...] : explore maps, save json, print condensed + flags
import sys, json, re
from ptx import *
e=Emu("pt.gba","pt.elf")
st,prefix=sys.argv[1],sys.argv[2]
SUS=re.compile(r"POK[ée]NAV|MOM\b|Mom\b|your (dad|father|mom)|RIVAL|\{VAR\}\?|moved here|CHAMPION|MAGMA|AQUA|\?\?|NORMAN.*(son|daughter) [A-Z]+\b",re.I)
allr={}
for m in sys.argv[3:]:
    r=explore(e,st,m,f"pt/{prefix}_{m[:14]}",presses=10)
    allr[m]=r
    print(f"##### {m}")
    for k,sc,xy,t,shot in r:
        if not t: print(f"  [NO TEXT] {sc} {xy}"); continue
        if k=="sign" and len(t[0])<60 and not SUS.search(t[0]): continue
        body=" // ".join(t)
        flag="  <<SUS" if SUS.search(body) else ""
        print(f"  {sc.split('EventScript_')[-1]} {xy}: {body[:300]}{flag}")
json.dump(allr,open(f"pt/{prefix}.json","w"),indent=1)
