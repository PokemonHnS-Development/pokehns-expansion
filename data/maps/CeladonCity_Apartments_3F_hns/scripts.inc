CeladonCity_Apartments_3F_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_3F_EventScript_Sign::
	msgbox CeladonMansion3F_Text_DevRoomSign, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_Programmer::
	msgbox GameFreak_Text_Programmer, MSGBOX_NPC
	end

CeladonCity_Apartments_3F_EventScript_GraphicArtist::
	msgbox GameFreak_Text_GraphicArtist, MSGBOX_NPC
	end

CeladonCity_Apartments_3F_EventScript_Program::
	msgbox CeladonMansion3F_Text_GameProgram, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_Picture::
	msgbox CeladonMansion3F_Text_Drawing, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_CharacterDesigner::
	msgbox GameFreak_Text_CharacterDesigner, MSGBOX_NPC
	end

GameFreak_Text_GameDesigner:
	.string "Is that right?\p"
	.string "I'm the GAME DESIGNER!\p"
	.string "Filling up your POKéDEX is tough,\n"
	.string "but don't give up!$"

GameFreak_Text_GameDesignerCompletedPokedex:
	.string "Wow! Excellent! You completed\n"
	.string "your POKéDEX!\p"
	.string "Congratulations!$"

GameFreak_Text_GraphicArtist:
	.string "אני המעצב הגרפי.\p"
	.string "אני ציירתי אותך!$"

GameFreak_Text_GraphicArtistPrintDiploma:
	.string "I'm the GRAPHIC ARTIST.\p"
	.string "Oh, you completed your POKéDEX?\p"
	.string "Want me to print out your\n"
	.string "DIPLOMA?$"

GameFreak_Text_GraphicArtistRefused:
	.string "Give me a shout if you want your\n"
	.string "DIPLOMA printed.$"

GameFreak_Text_GraphicArtistError:
	.string "Something's wrong. I'll have to\n"
	.string "cancel printing.$"

GameFreak_Text_Programmer:
	.string "מי, אני? אני המתכנתת.\p"
	.string "כדאי לשחק במכונות המזל!$"

GameFreak_Text_CharacterDesigner:
	.string "התאומות מקסימות, נכון?\p"
	.string "גם ג'סמין יפה.\p"
	.string "אוי, אני מת עליהן!$"

CeladonMansion3F_Text_DevRoomSign:
	.string "חדר הפיתוח של גיים פריק$"

CeladonMansion3F_Text_Drawing:
	.string "זה ציור מפורט של\n"
	.string "בחורה יפה.$"

CeladonMansion3F_Text_GameProgram:
	.string "זו תוכנת המשחק. אם תתעסק איתה,\n"
	.string "זה עלול להכניס באג למשחק!$"

CeladonMansion3F_Text_ReferenceMaterial:
	.string "It's crammed with reference\n"
	.string "materials. There's even a\n"
	.string "POKé DOLL.$"
