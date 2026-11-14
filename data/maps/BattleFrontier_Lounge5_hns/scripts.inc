BattleFrontier_Lounge5_hns_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl_hns::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting_hns, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns
	chooseboxmon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsEgg_hns
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirl_hnsEgg_hns::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman_hns::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt_hns::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy_hns::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting_hns::
	.string "הי-הי!\n"
	.string "אני יודעת מה פוקימונים חושבים!\p"
	.string "נו, בבקשה!\n"
	.string "אפשר לראות את הפוקימון שלך?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown_hns::
	.string "בוז!\n"
	.string "קמצן!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "It will battle even if it has a lot\l"
	.string "of ouchies!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow_hns::
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow_hns::
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "It says it worries about itself whether\l"
	.string "or not it has a lot of ouchies!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow_hns::
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow_hns::
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "It says it likes to be sneaky even\l"
	.string "if it has a lot of ouchies!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg_hns::
	.string "זה טיפשי! הביצה עוד ישנה!\n"
	.string "אני לא יכולה לדבר איתה!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon_hns::
	.string "כמה מקסים! הגברת הקטנה הזאת\n"
	.string "טוענת שהיא מבינה פוקימונים!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound_hns::
	.string "יש לי הרגשה שהילדה הקטנה\n"
	.string "אומרת משהו עמוק.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot_hns::
	.string "אני יודע משהו!\p"
	.string "הילדה הקטנה הזאת משחקת הרבה\n"
	.string "בבית האדום!$"

