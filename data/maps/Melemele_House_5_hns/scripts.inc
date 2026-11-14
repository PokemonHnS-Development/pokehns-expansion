Melemele_House_5_hns_MapScripts::
	.byte 0


Melemele_House5_Mom::
	lock
	faceplayer
	msgbox Melemele_House5_Mom_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House5_Son::
	lock
	faceplayer
	msgbox Melemele_House5_Son_Text_0
	applymovement melemele_elio Melemele_House5_Son_Movement
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement
	msgbox Melemele_House5_Son_Text_1, MSGBOX_AUTOCLOSE
	playmoncry SPECIES_MEOWTH, 0
	waitmoncry
	release
	end


Melemele_House5_Cat::
	lock
	faceplayer
	playmoncry SPECIES_MEOWTH, 0
	msgbox Melemele_House5_Cat_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end

Melemele_House5_Son_Movement:
	jump_in_place_down
	jump_in_place_down
	step_end

Melemele_House5_Mom_Text_0:
	.string "אני שוקלת לעבור לאזור אלולה\n"
	.string "עם הבן שלי, אליו.\p"
	.string "כאן באיים אנחנו רק מקבלים\n"
	.string "טעימה קטנה!$"

Melemele_House5_Son_Text_0:
	.string "הי הי… תופסת זה כל כך כיף!$"

Melemele_House5_Son_Text_1:
	.string "נסה לתפוס אותי, מיאו!$"

Melemele_House5_Cat_Text_0:
	.string "מיאאאוווררררררר!!!$"
