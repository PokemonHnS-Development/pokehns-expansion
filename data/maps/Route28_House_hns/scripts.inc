Route28_House_hns_MapScripts::
	.byte 0

Route28House_EventScript_Celebrity::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_STEEL_WING, Route28House_EventScript_CelebrityAfter
	msgbox Route28House_Text_Celebrity1, MSGBOX_NPC
	giveitem ITEM_TM_STEEL_WING
	setflag FLAG_GOT_TM_STEEL_WING
Route28House_EventScript_CelebrityAfter::
	msgbox Route28House_Text_Celebrity2, MSGBOX_NPC
	release
	end

Route28House_Text_Celebrity1:
	.string "¡Oh, cielos! Me encontraste.\pPor favor, no le digas a nadie.\pTe daré esto por guardar mi\nsecreto. ¿Por favor?$"

Route28House_Text_Celebrity2:
	.string "Es duro ser una gran celebridad.\p"
	.string "A donde voy, la gente me persigue.\p"
	.string "Solo quiero que me dejen en paz…$"

Route28House_Text_Fearow:
	.string "FEAROW: Feero!$"

