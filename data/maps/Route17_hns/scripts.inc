Route17_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route17_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route17_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route17_EventScript_Riley::
	trainerbattle_single TRAINER_RILEY_HNS, Route17_Text_BikerRileySeen, Route17_Text_BikerRileyBeaten, Route17_EventScript_RegisterRiley
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route17_EventScript_RematchRiley
	msgbox Route17_Text_BikerRileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_RegisterRiley::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route17_Text_RileyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_RILEY_HNS
	release
	end

Route17_EventScript_RematchRiley::
	trainerbattle_rematch TRAINER_RILEY_HNS, Route17_Text_RileyRematchIntro, Route17_Text_RileyRematchDefeat
	msgbox Route17_Text_RileyPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_RILEY_2_HNS, Route17_EventScript_RematchRileyTryGiveItem
	end

Route17_EventScript_RematchRileyTryGiveItem::
	checkitem ITEM_TM_TOXIC
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_TOXIC
	closemessage
	end

Route17_EventScript_Joel::
	trainerbattle_single TRAINER_JOEL_HNS, Route17_Text_BikerJoelSeen, Route17_Text_BikerJoelBeaten, Route17_EventScript_RegisterJoel
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route17_EventScript_RematchJoel
	msgbox Route17_Text_BikerJoelAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_RegisterJoel::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route17_Text_JoelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOEL_HNS
	release
	end

Route17_EventScript_RematchJoel::
	trainerbattle_rematch TRAINER_JOEL_HNS, Route17_Text_JoelRematchIntro, Route17_Text_JoelRematchDefeat
	msgbox Route17_Text_JoelPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_JOEL_2_HNS, Route17_EventScript_RematchJoelTryGiveItem
	end

Route17_EventScript_RematchJoelTryGiveItem::
	checkitem ITEM_TM_BRICK_BREAK
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_BRICK_BREAK
	closemessage
	end

Route17_EventScript_Glenn::
	trainerbattle_single TRAINER_GLENN_HNS, Route17_Text_BikerGlennSeen, Route17_Text_BikerGlennBeaten
	msgbox Route17_Text_BikerGlennAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_Charles::
	trainerbattle_single TRAINER_CHARLES_HNS, Route17_Text_BikerCharlesSeen, Route17_Text_BikerCharlesBeaten, Route17_EventScript_RegisterCharles
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route17_EventScript_RematchCharles
	msgbox Route17_Text_BikerCharlesAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_RegisterCharles::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route17_Text_CharlesRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CHARLES_HNS
	release
	end

Route17_EventScript_RematchCharles::
	trainerbattle_rematch TRAINER_CHARLES_HNS, Route17_Text_CharlesRematchIntro, Route17_Text_CharlesRematchDefeat
	msgbox Route17_Text_CharlesPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_CHARLES_2_HNS, Route17_EventScript_RematchCharlesTryGiveItem
	end

Route17_EventScript_RematchCharlesTryGiveItem::
	checkitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_BULK_UP
	closemessage
	end

Route17_Text_BikerRileySeen:
	.string "היי, אתה! אתה מג'וטו, הא?$"

Route17_Text_BikerRileyBeaten:
	.string "וואו, איזו בעיטה!$"

Route17_Text_BikerRileyAfterBattle:
	.string "אל תשתחצן, פרחח מג'וטו!$"

Route17_Text_BikerJoelSeen:
	.string "וואו. איזה אופניים מגניבים!$"

Route17_Text_BikerJoelBeaten:
	.string "אבל אתה לא רק נראה מגניב…$"

Route17_Text_BikerJoelAfterBattle:
	.string "אני נראה מגניב, אבל אני חלש,\n"
	.string "אז אני לא באמת מגניב.\p"
	.string "אני צריך להתאמן יותר קשה…$"

Route17_Text_BikerGlennSeen:
	.string "היי! רוצה קרב מהירות?$"

Route17_Text_BikerGlennBeaten:
	.string "וואי! יש לך מומנט מטורף!$"

Route17_Text_BikerGlennAfterBattle:
	.string "בשביל האופניים, רכיבה בלי ידיים\n"
	.string "נחשבת מגניבה.$"

Route17_Text_BikerCharlesSeen:
	.string "אנחנו כוכבי הכביש חסרי הפחד!$"

Route17_Text_BikerCharlesBeaten:
	.string "ארררג! התרסקתי ונשרפתי!$"

Route17_Text_BikerCharlesAfterBattle:
	.string "נהיגה פרועה גורמת לתאונות!\n"
	.string "לאט ובזהירות!$"

Route17_Text_RileyRegister:
	.string "לא רע בשביל ילד מג'וטו!$"

Route17_Text_RileyRematchIntro:
	.string "פרחחים מג'וטו מנצחים רק פעם אחת!$"

Route17_Text_RileyRematchDefeat:
	.string "חטפתי בעיטה…$"

Route17_Text_RileyPostRematch:
	.string "אולי בכל זאת כדאי לי\n"
	.string "להתאמן בג'וטו.$"

Route17_Text_JoelRegister:
	.string "אתה בכל זאת די מגניב!\n"
	.string "בוא נחליף מספרים!$"

Route17_Text_JoelRematchIntro:
	.string "נראה עכשיו מי יותר מגניב!$"

Route17_Text_JoelRematchDefeat:
	.string "עדיין לא מגניב מספיק…$"

Route17_Text_JoelPostRematch:
	.string "אמשיך להתאמן כדי להיות מגניב\n"
	.string "כמוך, ילד!$"

Route17_Text_CharlesRegister:
	.string "אתה שובר לבבות כמוני, ילד!\n"
	.string "תן לי את המספר שלך!$"

Route17_Text_CharlesRematchIntro:
	.string "אני לא רק כוכב כביש,\n"
	.string "אני גם שובר לבבות!$"

Route17_Text_CharlesRematchDefeat:
	.string "שוב התרסקתי ונשרפתי!$"

Route17_Text_CharlesPostRematch:
	.string "פגשתי מאמן כמוך ביונובה.\n"
	.string "אל תתרסק!$"

