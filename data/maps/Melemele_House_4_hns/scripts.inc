Melemele_House_4_hns_MapScripts::
	.byte 0


Melemele_House4_Man::
	lock
	faceplayer
	msgbox Melemele_House4_Man_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Woman::
	lock
	faceplayer
	msgbox Melemele_House4_Woman_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Man_Text_0:
	.string "We're vacationing on the Alola Isles!\p"
	.string "It's just like the Alola Region,\n"
	.string "but closer to Kanto!\p"
	.string "I saved so much on travel expenses!$"

Melemele_House4_Woman_Text_0:
	.string "My boyfriend told me we were going to\n"
	.string "Alola…\p"
	.string "I had assumed it would be the Alola\n"
	.string "Region, not the small isles off the\l"
	.string "coast of Kanto.$"
