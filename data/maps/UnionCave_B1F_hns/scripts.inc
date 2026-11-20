UnionCave_B1F_hns_MapScripts::
	.byte 0

UnionCave_B1F_EventScript_HikerPhillip::
	trainerbattle_single TRAINER_PHILLIP_HNS, UnionCave_B1F_Text_HikerPhillipSeen, UnionCave_B1F_Text_HikerPhillipBeaten
	msgbox UnionCave_B1F_Text_HikerPhillipAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_HikerLeonard::
	trainerbattle_single TRAINER_LEONARD_HNS, UnionCave_B1F_Text_HikerLeonardSeen, UnionCave_B1F_Text_HikerLeonardBeaten
	msgbox UnionCave_B1F_Text_HikerLeonardAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacAndrew::
	trainerbattle_single TRAINER_ANDREW_HNS, UnionCave_B1F_Text_PokemaniacAndrewSeen, UnionCave_B1F_Text_PokemaniacAndrewBeaten
	msgbox UnionCave_B1F_Text_PokemaniacAndrewAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_PokemaniacCalvin::
	trainerbattle_single TRAINER_CALVIN_HNS, UnionCave_B1F_Text_PokemaniacCalvinSeen, UnionCave_B1F_Text_PokemaniacCalvinBeaten
	msgbox UnionCave_B1F_Text_PokemaniacCalvinAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B1F_EventScript_Item_RockTomb::
	finditem ITEM_TM_ROCK_TOMB
	end

UnionCave_B1F_EventScript_Item_Xdefend::
	finditem ITEM_X_DEFEND
	end

UnionCave_B1F_Text_HikerPhillipSeen:
	.string "עבר הרבה זמן מאז שראיתי\n"
	.string "בן אדם אחר.\p"
	.string "אין מה להתבייש. קדימה, לקרב!$"

UnionCave_B1F_Text_HikerPhillipBeaten:
	.string "אררר…$"

UnionCave_B1F_Text_HikerPhillipAfter:
	.string "אני אבוד כבר הרבה זמן…\p"
	.string "לא רע לי פה, אבל אני רעב נורררא!$"

UnionCave_B1F_Text_HikerLeonardSeen:
	.string "תראו תראו! אורח!$"

UnionCave_B1F_Text_HikerLeonardBeaten:
	.string "וואהאהאה! יש בך אש!$"

UnionCave_B1F_Text_HikerLeonardAfter:
	.string "אני גר כאן למטה.\p"
	.string "גם אתה יכול, אם מתחשק לך.\p"
	.string "יש פה המון מקום, כמו שרואים.$"

UnionCave_B1F_Text_PokemaniacAndrewSeen:
	.string "מי שם?\p"
	.string "עזוב אותי ואת הפוקימונים שלי בשקט!$"

UnionCave_B1F_Text_PokemaniacAndrewBeaten:
	.string "לך… לך מפה!$"

UnionCave_B1F_Text_PokemaniacAndrewAfter:
	.string "רק אני והפוקימונים שלי.\n"
	.string "אני מאושר עד הגג.$"

UnionCave_B1F_Text_PokemaniacCalvinSeen:
	.string "באתי עד לכאן כדי לערוך את\n"
	.string "מחקר הפוקימונים שלי.\p"
	.string "אדגים לך את הממצאים שלי\n"
	.string "בקרב אמיתי!$"

UnionCave_B1F_Text_PokemaniacCalvinBeaten:
	.string "בסוף דווקא הדגמת עליי!$"

UnionCave_B1F_Text_PokemaniacCalvinAfter:
	.string "כדאי שאסכם ואפרסם את\n"
	.string "ממצאי המחקר שלי.\p"
	.string "אולי אפילו אתפרסם כמו פרופ' אלם.$"
