Gate_EcruteakCity_Route38_hns_MapScripts::
	.byte 0

Route38_EventScript_Officer::
	lock
	faceplayer
	msgbox Route38_Text_EcruteakGateOfficer, MSGBOX_DEFAULT
	closemessage
	release
	end

Route38_Text_EcruteakGateOfficer:
	.string "מאיפה אמרת שבאת?\p"
	.string "העיירה ניו בארק?\p"
	.string "פרופ' אלם גר שם, נכון?\p"
	.string "עשית דרך ארוכה כדי להגיע לכאן.$"
