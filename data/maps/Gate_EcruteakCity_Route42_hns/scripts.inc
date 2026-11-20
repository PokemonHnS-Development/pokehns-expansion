Gate_EcruteakCity_Route42_hns_MapScripts::
	.byte 0

Gate_EcruteakCity_Route42_EventScript_Policeman::
	lock
	faceplayer
	msgbox Route42_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route42_Text_EcruteakGateOfficer:
	.string "מבפנים, הר המכתש הוא כמו מבוך.\p"
	.string "כדאי להיזהר שלא ללכת שם לאיבוד.$"

