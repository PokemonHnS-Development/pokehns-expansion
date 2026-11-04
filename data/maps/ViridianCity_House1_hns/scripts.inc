ViridianCity_House1_hns_MapScripts::
	.byte 0

ViridianCity_House1_EventScript_Pokefan::
	msgbox ViridianCity_House1_Text_PokefanM, MSGBOX_NPC
	end

ViridianCity_House1_EventScript_Lass::
	msgbox ViridianCity_House1_Text_Lass, MSGBOX_NPC
	end


ViridianCity_House1_EventScript_Speary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House1_Text_Speary, MSGBOX_DEFAULT
	waitmoncry
	release
	end

ViridianCity_House1_EventScript_Rattey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
	msgbox ViridianCity_House1_Text_Rattey, MSGBOX_DEFAULT
	waitmoncry
	release
	end

ViridianCity_House1_Text_PokefanM:
	.string "אתה משקיע הרבה מחשבה\n"
	.string "בבחירת שמות לפוקימונים שלך?\p"
	.string "כינויים טובים מוסיפים הרבה\n"
	.string "לכיף של החלפות עם אחרים.$"

ViridianCity_House1_Text_Lass:
	.string "קוראים להם כידי, הספירו,\n"
	.string "ורטי, הרטטה.$"

ViridianCity_House1_Text_Speary:
	.string "כידי: צ'-צ'ון!$"

ViridianCity_House1_Text_Rattey:
	.string "רטי: קיקייי!$"

