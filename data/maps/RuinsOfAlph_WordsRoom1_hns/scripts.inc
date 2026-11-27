RuinsOfAlph_WordsRoom1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlph_WordsRoom1_hns_OnLoad
	.byte 0

@ Hoenn & Seek 2.0 part 27a: the Rosetta line (data/scripts/hoenn_cipher.inc).
RuinsOfAlph_WordsRoom1_hns_OnLoad:
	setvar VAR_0x8004, 1
	special HoennCipherDrawRoom
	end
