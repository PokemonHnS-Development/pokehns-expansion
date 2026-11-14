OlivineCity_House2_hns_MapScripts::
	.byte 0

OlivineCity_EventScript_Punisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBro, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_PunisherBoy::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBoy, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PunishmentBro:
	.string "בדרך לסיאנווד יש\n"
	.string "ארבעה איים נטושים.\p"
	.string "ילדים רעים נלקחים\n"
	.string "לאיים האלה כעונש!$"

OlivineCity_Text_PunishmentBoy:
	.string "כל פעם שאני מסתבך בצרות,\n"
	.string "אחי הגדול תמיד מפחיד אותי.$"
