BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	chooseboxmon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "Ehehe!\n"
	.string "I can tell what POKéMON are thinking!\p"
	.string "Please!\n"
	.string "Can I see your POKéMON?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "Boo!\n"
	.string "Cheapie!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להילחם!\n"
	.string "הוא יילחם גם כשממש כואב לו!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להילחם!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא ידאג לעצמו!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להילחם!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא יהפוך לערמומי!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא שומר על עצמו!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא ירביץ בחזרה!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא שומר על עצמו!\p"
	.string "הוא אומר שהוא דואג לעצמו\n"
	.string "בין אם כואב לו הרבה ובין אם לא!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא שומר על עצמו!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא יהפוך לערמומי!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להיות ערמומי!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא ירביץ בחזרה!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להיות ערמומי!\p"
	.string "אבל אם כואב לו מספיק,\n"
	.string "הוא ידאג לעצמו!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow::
	.string "הממ…\p"
	.string "הוא אומר שהוא אוהב להיות ערמומי!\p"
	.string "הוא אומר שהוא אוהב להיות ערמומי\n"
	.string "גם כשממש כואב לו!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "That's silly! An EGG is asleep!\n"
	.string "I can't talk to it!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "How charming!\n"
	.string "That little lady claims she can\l"
	.string "understand POKéMON!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "I have this feeling that the little girl\n"
	.string "is saying something profound.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "I know something!\p"
	.string "That little girl plays at the red house\n"
	.string "a lot!$"

