MahoganyTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MahoganyTown_PokemonCenter_OnTransition
	.byte 0

MahoganyTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_MAHOGANY_TOWN_HNS
	end

MahoganyTown_PokemonCenter_EventScript_Hiker::
	msgbox MahoganyTown_PokemonCenter_Text_PokefanM, MSGBOX_NPC
	end
	
MahoganyTown_PokemonCenter_EventScript_Boy::
	msgbox MahoganyTown_PokemonCenter_Text_Youngster, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_EventScript_Girl::
	msgbox MahoganyTown_PokemonCenter_Text_CooltrainerF, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_PokefanM:
    .string "מה זה? צוות רוקט חזר?\p"
    .string "ראיתי כמה אנשים בשחור\n"
    .string "באגם הזעם…$"

MahoganyTown_PokemonCenter_Text_Youngster:
    .string "אני לא נותן לפוקימונים שלי\n"
    .string "להתפתח מוקדם מדי.\p"
    .string "אני מלמד אותם מהלכים מסוימים\n"
    .string "לפני שאני נותן להם להתפתח.$"

MahoganyTown_PokemonCenter_Text_CooltrainerF:
    .string "פוקימונים אכן מתחזקים כשהם\n"
    .string "מתפתחים,\p"
    .string "אבל הם גם לומדים\n"
    .string "מהלכים לאט יותר.$"
