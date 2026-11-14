LavenderTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_OnTransition
	.byte 0

LavenderTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN_HNS
	end

LavenderTown_PokemonCenter_EventScript_Gent::
	msgbox LavenderTown_PokemonCenter1F_Text_Gentleman, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Teacher::
	msgbox LavenderTown_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Youngster::
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart::
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart, MSGBOX_NPC
	end

LavenderTown_PokemonCenter1F_Text_Gentleman:
	.string "מצפון ללבנדר נמצאת מערת האבן.\n"
	.string "עוברים דרכה כדי להגיע למפעל החשמל.$"

LavenderTown_PokemonCenter1F_Text_Teacher:
	.string "יש תוכנית רדיו שמשמיעה\n"
	.string "מוזיקה של חליל פוקימון.\p"
	.string "הו? אה, הרדיו שלך צריך\n"
	.string "שדרוג רדיו כדי לקלוט אותה.\p"
	.string "אולי תחנת הרדיו כאן בעיירה\n"
	.string "תוכל לתת לך אחד?$"

LavenderTown_PokemonCenter1F_Text_Youngster:
	.string "אם מפעל החשמל לא עובד,\n"
	.string "גם הרכבת המגנטית לא תיסע…\p"
	.string "זה גם אומר שתחנת הרדיו\n"
	.string "לא יכולה לשדר…$"

LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart:
	.string "מנהל תחנת הרדיו היה ממש מאושר.\p"
	.string "הוא אמר שהם חזרו לשדר,\n"
	.string "כי מפעל החשמל שוב פועל כסדרו.$"
