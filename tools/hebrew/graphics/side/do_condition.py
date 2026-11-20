from gfx import *
import shutil
# pokeblock/use_screen/condition.png is byte-identical in English to pokenav/left_headers/condition.png
# (same "CONDITION" banner); take the Pokégear group's Hebrew ("כושר") as is.
P = 'graphics/pokeblock/use_screen/condition.png'
A = 'graphics/pokenav/left_headers/condition.png'
en_a = gpaths.english(A)
en_p = gpaths.english(P)
assert en_a == en_p
shutil.copyfile(os.path.join(WT, A), gpaths.write_target(P))
print(pair(P, 4))
