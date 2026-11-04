"""Settings the inventory scripts share. build.py fills them in from its arguments before it runs
the scripts; nothing here has a default."""
SRC = None        # the English source tree the strings are counted in
OUT = None        # the folder every script reads its inputs from and writes its outputs to
NM = None         # arm-none-eabi-nm
BUILDS = {}       # 'release' and 'std' -> (ROM, ELF, linker map) of two builds of SRC
ES_FILES = set()  # files the Spanish fork changed (inventory.json es_touched); empty if unknown
