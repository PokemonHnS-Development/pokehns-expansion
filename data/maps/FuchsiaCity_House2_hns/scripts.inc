FuchsiaCity_House2_hns_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_Granddaughter::	
	goto_if_set FLAG_TEMP_1, FuchsiaCity_House2_EventScript_Granddaughter2
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter1, MSGBOX_NPC
	setflag FLAG_TEMP_1
	end

FuchsiaCity_House2_EventScript_Granddaughter2::
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter2, MSGBOX_NPC
	end

FuchsiaCity_House2_EventScript_Photo::
	msgbox FuchsiaCity_House2_Text_WardenPhoto, MSGBOX_NPC
	end

FuchsiaCity_House2_Text_WardensGranddaughter1:
	.string "סבא שלי הוא הפקח של\n"
	.string "אזור הספארי.\p"
	.string "כלומר, הוא היה…\p"
	.string "הוא החליט לצאת לחופשה\n"
	.string "ונסע לבדו אל מעבר לים.\p"
	.string "הוא הפסיק לנהל את אזור הספארי\n"
	.string "ככה, פתאום.$"

FuchsiaCity_House2_Text_WardensGranddaughter2:
	.string "הרבה אנשים התאכזבו כשאזור הספארי\n"
	.string "נסגר, אבל סבא כל כך עקשן…$"

FuchsiaCity_House2_Text_WardenPhoto:
	.string "זו תמונה של איש זקן מחייך,\n"
	.string "מוקף בפוקימונים.$"

FuchsiaCity_House2_Text_SafariZonePhoto:
	.string "It's a photo of a huge grassy plain\n"
	.string "with rare POKéMON frolicking in it.$"
