CeladonCity_House1_hns_MapScripts::
	.byte 0

CeladonCity_House1_EventScript_Chef::
	msgbox CeladonCity_House1_Text_ChefEatathon, MSGBOX_NPC
	end

CeladonCity_House1_EventScript_Fisher1::
	lock
	msgbox CeladonCity_House1_Text_Fisher1Snarfle, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher1Concentration, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_Fisher2::
	lock
	msgbox CeladonCity_House1_Text_Fisher2GulpChew, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher2Quantity, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_EAST
	release
	end

CeladonCity_House1_EventScript_Fisher3::
	lock
	msgbox CeladonCity_House1_Text_Fisher3MunchMunch, MSGBOX_DEFAULT
	faceplayer
	msgbox CeladonCity_House1_Text_Fisher3GoldenrodIsBest, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_EAST
	release
	end

CeladonCity_House1_EventScript_Teacher::
	lock
	msgbox CeladonCity_House1_Text_TeacherCrunchCrunch, MSGBOX_DEFAULT
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_House1_EventScript_TeacherCoincase
	msgbox CeladonCity_House1_Text_TeacherKeepEating, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_TeacherCoincase::
	msgbox CeladonCity_House1_Text_TeacherNoCoinCase, MSGBOX_DEFAULT
	turnobject VAR_LAST_TALKED, DIR_WEST
	release
	end

CeladonCity_House1_EventScript_Sign::
	msgbox CeladonCity_House1_Text_EatathonContestPoster, MSGBOX_SIGN
	end

CeladonCity_House1_Text_ChefEatathon:
	.string "היי!\p"
	.string "אנחנו עורכים מרתון אכילה.\p"
	.string "אנחנו לא יכולים להגיש לך אוכל\n"
	.string "כרגע. סליחה.$"

CeladonCity_House1_Text_Fisher1Snarfle:
	.string "…זלילה, לעיסה…$"

CeladonCity_House1_Text_Fisher1Concentration:
	.string "לא לדבר איתי!\p"
	.string "זה יהרוס לי את הריכוז!$"

CeladonCity_House1_Text_Fisher2GulpChew:
	.string "…בליעה… לעיסה…$"

CeladonCity_House1_Text_Fisher2Quantity:
	.string "אצלי כמות עדיפה על איכות!\p"
	.string "אני שמח כשאני שבע!$"

CeladonCity_House1_Text_Fisher3MunchMunch:
	.string "נשנוש, נשנוש…$"

CeladonCity_House1_Text_Fisher3GoldenrodIsBest:
	.string "האוכל כאן טוב, אבל בגולדנרוד\n"
	.string "יש את האוכל הכי טוב שיש.$"

CeladonCity_House1_Text_TeacherCrunchCrunch:
	.string "קראנץ'… קראנץ'…$"

CeladonCity_House1_Text_TeacherNoCoinCase:
	.string "אף אחד כאן לא ייתן לך\n"
	.string "ארנק מטבעות. כדאי לחפש בג'וטו.$"

CeladonCity_House1_Text_TeacherKeepEating:
	.string "קראנץ'… קראנץ'…\p"
	.string "אני יכולה להמשיך לאכול!\p"
	.string "עוד, שף!$"

CeladonCity_House1_Text_EatathonContestPoster:
	.string "מרתון אכילה! בלי הגבלת זמן!\p"
	.string "קרב בלי סוף! הזולל הכי גדול\n"
	.string "אוכל הכול בחינם!$"

