CliffEdgeCave_hns_MapScripts::
	.byte 0

CliffEdgeCave_EventScript_BaldMan::
	lock
	faceplayer
	msgbox CliffEdgeCave_Text_Baldman, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeCave_Text_Baldman:
	.string "בפיצול דרכים במערה, כנראה שדרך אחת\n"
	.string "נכונה, והשנייה מובילה למבוי סתום.\p"
	.string "אבל אנשים לא יכולים שלא\n"
	.string "לנסות את שתיהן.$"
