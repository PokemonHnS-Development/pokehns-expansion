CeladonCity_Hotel_Frlg_MapScripts::
	.byte 0

CeladonCity_Hotel_EventScript_Receptionist::
	msgbox CeladonCity_Hotel_Text_ThisHotelIsForPeople, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_Beauty::
	msgbox CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBoyfriend::
	msgbox CeladonCity_Hotel_Text_WhyDidSheBringBrother, MSGBOX_NPC
	end

CeladonCity_Hotel_EventScript_BeautyBrother::
	msgbox CeladonCity_Hotel_Text_SisBroughtMeOnVacation, MSGBOX_NPC
	end

CeladonCity_Hotel_Text_ThisHotelIsForPeople::
	.string "POKéMON?\n"
	.string "No, este es un hotel para personas.\p"
	.string "Lo siento, pero estamos completos.$"

CeladonCity_Hotel_Text_OnVacationWithBrotherAndBoyfriend::
	.string "Estoy de vacaciones con mi hermano y\n"
	.string "novio.\p"
	.string "¡CIUDAD CELEDÓN es una ciudad muy bonita!$"

CeladonCity_Hotel_Text_WhyDidSheBringBrother::
	.string "Why?\n"
	.string "¿Por qué trajo a su hermano?$"

CeladonCity_Hotel_Text_SisBroughtMeOnVacation::
	.string "¡Yuju! ¡Estoy de vacaciones!\n"
	.string "Mi hermana me trajo! ¡Genial!$"

