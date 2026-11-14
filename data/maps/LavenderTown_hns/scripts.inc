LavenderTown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_EventScript_CityEnter
	.byte 0

LavenderTown_EventScript_CityEnter::
	setflag FLAG_VISITED_LAVENDER_TOWN
	end

LavenderTown_EventScript_PokefanM::
	msgbox LavenderTown_Text_PokefanM, MSGBOX_NPC
	end

LavenderTown_EventScript_Teacher::
	msgbox LavenderTown_Text_Teacher, MSGBOX_NPC
	end

LavenderTown_EventScript_Gramps::
	msgbox LavenderTown_Text_Gramps, MSGBOX_NPC
	end

LavenderTown_EventScript_Youngster::
	msgbox LavenderTown_Text_Youngster, MSGBOX_NPC
	end

LavenderTown_EventScript_TownSign::
	msgbox LavenderTown_Text_Sign, MSGBOX_SIGN
	end

LavenderTown_EventScript_RadioTowerSign::
	msgbox LavenderTown_Text_KantoRadioStationSign, MSGBOX_SIGN
	end

LavenderTown_EventScript_VolunteerSign::
	msgbox LavenderTown_Text_VolunteerPokemonHouseSign, MSGBOX_SIGN
	end

LavenderTown_EventScript_SoulHouseSign::
	msgbox LavenderTown_Text_SoulHouseSign, MSGBOX_SIGN
	end

LavenderTown_Text_PokefanM:
	.string "זה בניין מרשים, הא?\p"
	.string "זה מגדל הרדיו של קאנטו.$"

LavenderTown_Text_Teacher:
	.string "בקאנטו יש הרבה תוכניות רדיו טובות.$"

LavenderTown_Text_Gramps:
	.string "אנשים באים מכל מקום כדי לחלוק כבוד\n"
	.string "לנשמות הפוקימונים שהלכו לעולמם.$"

LavenderTown_Text_Youngster:
	.string "צריך חליל פוקימון כדי להעיר\n"
	.string "פוקימונים ישנים.\p"
	.string "כל מאמן חייב לדעת את זה!$"

LavenderTown_Text_Sign:
	.string "העיירה לבנדר\p"
	.string "העיירה הסגולה הנעלה$"

LavenderTown_Text_KantoRadioStationSign:
	.string "תחנת הרדיו של קאנטו\p"
	.string "התוכניות האהובות עליכם\n"
	.string "בשידור מסביב לשעון!$"

LavenderTown_Text_VolunteerPokemonHouseSign:
	.string "בית המתנדבים לפוקימונים\n"
	.string "של לבנדר$"

LavenderTown_Text_SoulHouseSign:
	.string "בית הנשמות\p"
	.string "שנשמות הפוקימונים ינוחו בשלום$"
