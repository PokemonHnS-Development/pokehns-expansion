CeruleanCity_House2_hns_MapScripts::
	.byte 0

CeruleanCity_House2_EventScript_Woman::
	msgbox CeruleanPolice_Text_PokefanF, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_Man::
	msgbox CeruleanPolice_Text_FishingGuru, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_Diglett::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox CeruleanPolice_Text_Diglett, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeruleanPolice_Text_FishingGuru:
	.string "שמעתי שאיזה טיפוס חשוד\n"
	.string "מסתובב כאן בהיחבא.\p"
	.string "לא אעבור על זה בשתיקה\n"
	.string "אם יתברר שהוא גנב.$"

CeruleanPolice_Text_PokefanF:
	.string "פעם כבר שדדו אותנו.$"

CeruleanPolice_Text_Diglett:
	.string "דיגלט: דאג דאג.$"
