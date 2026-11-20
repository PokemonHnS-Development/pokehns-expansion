export DEVKITPRO=/opt/devkitpro DEVKITARM=/opt/devkitpro/devkitARM
export HNS_RUNNER=../hns-tools/emu/hnsrun
E=tools/hebrew/emu
T=$E/scripts/r4_battle_options
R=../hns-tools/scratch/screens/r4_battle_options_gen4_ui_and_quick_run
S=../hns-tools/emu/saves_screens/r4_bogq
HE_ROM=$R/rom/pokehns-clip.gba
EN_ROM=../pokehns-en/pokehns.gba
# r4 tours (this folder)
he4() { HNS_SAVES=${SAVES:-$S/base} HNS_WORK=$R/work HNS_SRC=../pokehns-release python3 $T/r4opt.py tour $HE_ROM $R/he/${OUTSUB:-r4} --tours $T --clip "$@"; }
en4() { HNS_SAVES=${SAVES:-$S/base} HNS_WORK=$R/work_en HNS_SRC=../pokehns-en python3 $T/r4opt.py tour $EN_ROM $R/en/${OUTSUB:-r4} --tours $T "$@"; }
# existing tours (tools/hebrew/emu/tours) on a save variant: SAVES=$S/g4 heT OUTSUB REGEX
heT() { local o=$1; shift; HNS_SAVES=${SAVES:-$S/g4} HNS_WORK=$R/work HNS_SRC=../pokehns-release python3 $E/hns.py --rom $HE_ROM tour $HE_ROM $R/he/$o --clip --only "$@"; }
enT() { local o=$1; shift; HNS_SAVES=${SAVES:-$S/g4} HNS_WORK=$R/work_en HNS_SRC=../pokehns-en python3 $E/hns.py --rom $EN_ROM tour $EN_ROM $R/en/$o --only "$@"; }
# the r2 tours with their own wrappers, on the Gen 4 saves
BFF=$E/scripts/r2_battle_frontier_facilities; RIV=$E/scripts/r2_rival_names; SF=$E/scripts/r2_safari_pokeblock_bug_contest
heX() { local w=$1 d=$2 o=$3; shift 3; HNS_SAVES=${SAVES:-$S/g4} HNS_WORK=$R/work HNS_SRC=../pokehns-release python3 $w tour $HE_ROM $R/he/$o --tours $d --clip "$@"; }
enX() { local w=$1 d=$2 o=$3; shift 3; HNS_SAVES=${SAVES:-$S/g4} HNS_WORK=$R/work_en HNS_SRC=../pokehns-en python3 $w tour $EN_ROM $R/en/$o --tours $d "$@"; }
