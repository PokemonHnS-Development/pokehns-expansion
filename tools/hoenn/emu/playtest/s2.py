from ptx import *
e=Emu("pt.gba","pt.elf")
st,log=gym_run(e,"pt/birch1.ss","RustboroCity_Gym","s2",leader_match="Roxanne")
st2,t=walk_outside(e,st,"RustboroCity",27,23,"s2")
log.append(("walk outside (call?)",t))
dump(log,"pt/s2.json")
print("FINAL",st2,e.where(st2))
