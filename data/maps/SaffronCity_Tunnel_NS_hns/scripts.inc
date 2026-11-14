SaffronCity_Tunnel_NS_hns_MapScripts::
	.byte 0

SaffronCity_Tunnel_NS_EventScript_BaldingMan::
	lock
	faceplayer
	goto_if_set FLAG_ITEM_UNDERGROUND_PATH_TM_EXPLOSION, SaffronCity_Tunnel_NS_EventScript_BaldingManAfter
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManIntro, MSGBOX_DEFAULT
	checkitem ITEM_RAGE_CANDY_BAR
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_Tunnel_NS_EventScript_BaldingManDetected
	closemessage
	release
	end

SaffronCity_Tunnel_NS_EventScript_BaldingManDetected::
	playse SE_PIN
	applymovement LOCALID_SAFFRONTUNNEL_UNCLE_RAGE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SAFFRONTUNNEL_UNCLE_RAGE
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManCandybarDetected, MSGBOX_DEFAULT
	removeitem ITEM_RAGE_CANDY_BAR
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManGaveCandybar, MSGBOX_DEFAULT
	giveitem ITEM_TM_EXPLOSION
	setflag FLAG_ITEM_UNDERGROUND_PATH_TM_EXPLOSION
SaffronCity_Tunnel_NS_EventScript_BaldingManAfter::
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManGaveTm, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_Tunnel_NS_Text_BaldingManIntro:
	.string "אין סיבה לפחד,\n"
	.string "אני לא אדם רע.\p"
	.string "מקום כזה…\n"
	.string "מושך אנשים מרושעים.\p"
	.string "בסוף הם עוד\n"
	.string "יעשו צרות…\p"
	.string "אני מתעצבן רק מלחשוב\n"
	.string "על זה.$"

SaffronCity_Tunnel_NS_Text_BaldingManCandybarDetected:
	.string "אהא!\n"
	.string "זה חטיף זעם!\p"
	.string "אפשר לקבל אותו?\n"
	.string "בבקשה!$"

SaffronCity_Tunnel_NS_Text_BaldingManGaveCandybar:
	.string "{PLAYER} נתן את חטיף הזעם\n"
	.string "לאיש שבמעבר התת-קרקעי.\p"
	.string "נשנוש!\p"
	.string "איזה עצבים!\p"
	.string "אבל זה כל כך טעים!\p"
	.string "נשנוש נשנוש!\p"
	.string "אררג! זה מעצבן אותי!\p"
	.string "נשנוש נשנוש!\p"
	.string "אררג…\p"
	.string "…………פיו!\p"
	.string "אני מרגיש הרבה יותר טוב!\n"
	.string "תודה על הממתק!\p"
	.string "אני רוצה לתת לך את זה!$"

SaffronCity_Tunnel_NS_Text_BaldingManGaveTm:
	.string "מ”מ 64 מכיל…………\p"
	.string "טיק-\n"
	.string "            טוק\p"
	.string "טיק-\n"
	.string "            טוק\p"
	.string "טיק-\n"
	.string "            טוק\p"
	.string "טיק-\n"
	.string "            טוק\p"
	.string "טיק……\n"
	.string "…………………\p"
	.string "…………………\n"
	.string "קה-בום!!!$"

