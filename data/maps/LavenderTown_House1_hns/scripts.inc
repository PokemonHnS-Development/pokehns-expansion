LavenderTown_House1_hns_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_Girl::
	msgbox LavenderTown_House1_Text_Girl, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Guy::
	msgbox LavenderTown_House1_Text_Guy, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Marowak::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAROWAK, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Marowak, MSGBOX_DEFAULT
	waitmoncry
	msgbox LavenderTown_House1_Text_Marowak2, MSGBOX_DEFAULT
	closemessage
	release
	end

LavenderTown_House1_Text_Girl:
	.string "אפשר להאמין?\p"
	.string "יש אנשים שנמאס להם לטפל\n"
	.string "בפוקימונים.\p"
	.string "סבא אוסף פוקימונים מסכנים\n"
	.string "וחסרי בית ומטפל בהם.$"
LavenderTown_House1_Text_Guy:
	.string "מר פוג'י אכן גר כאן, אבל כרגע הוא\n"
	.string "לא בבית. הוא אמור להיות בבית הנשמות.$"
LavenderTown_House1_Text_Marowak:
	.string ".............................$"

LavenderTown_House1_Text_Marowak2:
	.string "המארוואק שקט, אבל הוא\n"
	.string "נראה די מאושר.$"

