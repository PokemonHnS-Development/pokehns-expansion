RuinsOfAlph_WordsRoom2_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, RuinsOfAlph_WordsRoom2_hns_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_CipherWordsOnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, HoennSeek_EventScript_CipherWordsOnFrame
	.byte 0

@ Hoenn & Seek 2.0 part 27a: tonight's glowing word (data/scripts/hoenn_cipher.inc).
RuinsOfAlph_WordsRoom2_hns_OnLoad:
	setvar VAR_0x8004, 2
	special HoennCipherDrawRoom
	end
