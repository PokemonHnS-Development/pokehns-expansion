Melemele_House_3_hns_MapScripts::
	.byte 0


Melemele_House3_Woman::
	lock
	faceplayer
	msgbox Melemele_House3_Woman_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House3_Man::
	lock
	faceplayer
	msgbox Melemele_House3_Man_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House3_Woman_Text_0:
	.string "Island life here is so peaceful!\p"
	.string "And it's nice that my grandkids are just\n"
	.string "a quick boat ride away in Kanto!$"

Melemele_House3_Man_Text_0:
	.string "Dang tourists!\p"
	.string "My realtor said this place would be\n"
	.string "quiet… but I guess its cheaper to \l"
	.string "travel here than all the way to Alola.$"
