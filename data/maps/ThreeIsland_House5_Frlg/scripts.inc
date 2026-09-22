ThreeIsland_House5_Frlg_MapScripts::
	.byte 0

ThreeIsland_House5_EventScript_LittleGirl::
	lock
	faceplayer
	goto_if_set FLAG_RESCUED_LOSTELLE, ThreeIsland_House5_EventScript_LittleGirlLostelleFound
	msgbox ThreeIsland_House5_Text_ImNotLostelle
	release
	end

ThreeIsland_House5_EventScript_LittleGirlLostelleFound::
	msgbox ThreeIsland_House5_Text_IllGoPlayWithLostelle
	release
	end

ThreeIsland_House5_Text_ImNotLostelle::
	.string "¿Yo?\n"
	.string "No soy LOSTELLE.\p"
	.string "Seguro que fue al\n"
	.string "BERRY FOREST, I think.\p"
	.string "Allí recoge BAYAS para hacer\n"
	.string "lunch.$"

ThreeIsland_House5_Text_IllGoPlayWithLostelle::
	.string "Creo que iré a jugar con LOSTELLE\n"
	.string "today.$"

