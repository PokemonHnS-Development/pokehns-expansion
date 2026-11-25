from ptx import *
e=Emu("pt.gba","pt.elf")
s=e.poke("pt/base.ss","pt/start.ss",flags_on=[0x892,0x1f3,0x1dd,0x893],vars_={0x408b:7,0x4076:16})
s=e.go(s,11,4,13,12,"pt/oak_w.ss")
print("WHERE",e.where(s))
t=e.talk(s,"pt/oak1.ss",face="UP",presses=22,shots="pt/s0_oak")
for x in t: print("OAK>",x)
