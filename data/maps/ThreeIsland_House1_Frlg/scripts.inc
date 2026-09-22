ThreeIsland_House1_Frlg_MapScripts::
	.byte 0

ThreeIsland_House1_EventScript_Lostelle::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	msgbox ThreeIsland_House1_Text_YoureAlwaysSoCool
	release
	end

ThreeIsland_House1_EventScript_DisplayCase::
	msgbox ThreeIsland_House1_Text_RareRocksGemsDisplayed, MSGBOX_SIGN
	end

ThreeIsland_House1_Text_YoureAlwaysSoCool::
	.string "LOSTELLE: Hi, {PLAYER}!\n"
	.string "¡Siempre eres tan genial!\p"
	.string "También prepararé el almuerzo\n"
	.string "day, {PLAYER}.$"

ThreeIsland_House1_Text_RareRocksGemsDisplayed::
	.string "Se exhiben rocas y gemas raras.$"

