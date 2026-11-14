Route44_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route44_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route44_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route44_EventScript_Wilton::
	trainerbattle_single TRAINER_WILTON_HNS, Route44_Text_FisherWilton1Seen, Route44_Text_FisherWilton1Beaten, Route44_EventScript_RegisterWilton
	goto_if_set FLAG_WILTON_HAS_ITEM_HNS, Route44_EventScript_WiltonGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route44_EventScript_RematchWilton
	msgbox Route44_Text_FisherWiltonHugePoliwag, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterWilton::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_WiltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WILTON_HNS
	release
	end

Route44_EventScript_RematchWilton::
	trainerbattle_rematch TRAINER_WILTON_HNS, Route44_Text_WiltonRematchIntro, Route44_Text_WiltonRematchDefeat
	msgbox Route44_Text_WiltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonGiveItem::
	msgbox Route44_Text_WiltonHasItem, MSGBOX_DEFAULT
	giveitem VAR_WILTON_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route44_EventScript_WiltonNoRoom
	clearflag FLAG_WILTON_HAS_ITEM_HNS
	msgbox Route44_Text_WiltonGaveItem, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonNoRoom::
	msgbox Route44_Text_WiltonNoRoom, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR_HNS, Route44_Text_FisherEdgarSeen, Route44_Text_FisherEdgarBeaten
	msgbox Route44_Text_FisherEdgarAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Vance::
	trainerbattle_single TRAINER_VANCE_HNS, Route44_Text_BirdKeeperVance1Seen, Route44_Text_BirdKeeperVance1Beaten, Route44_EventScript_RegisterVance
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route44_EventScript_RematchVance
	msgbox Route44_Text_BirdKeeperVanceBirds, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterVance::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_VanceRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VANCE_HNS
	release
	end

Route44_EventScript_RematchVance::
	trainerbattle_rematch TRAINER_VANCE_HNS, Route44_Text_VanceRematchIntro, Route44_Text_VanceRematchDefeat
	msgbox Route44_Text_VancePostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Phil::
	trainerbattle_single TRAINER_PHIL_HNS, Route44_Text_PsychicPhilSeen, Route44_Text_PsychicPhilBeaten
	msgbox Route44_Text_PsychicPhilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Zach::
	trainerbattle_single TRAINER_ZACH_HNS, Route44_Text_PokemaniacZachSeen, Route44_Text_PokemaniacZachBeaten
	msgbox Route44_Text_PokemaniacZachAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN_HNS, Route44_Text_CooltrainermAllenSeen, Route44_Text_CooltrainermAllenBeaten
	msgbox Route44_Text_CooltrainermAllenAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Cybil::
	trainerbattle_single TRAINER_CYBIL_HNS, Route44_Text_CooltrainerfCybilSeen, Route44_Text_CooltrainerfCybilBeaten
	msgbox Route44_Text_CooltrainerfCybilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Sign1::
	msgbox Route44_Text_Sign1, MSGBOX_SIGN
	end

Route44_EventScript_Sign2::
	msgbox Route44_Text_Sign2, MSGBOX_SIGN
	end

Route44_EventScript_Item_MaxRepel::
	finditem ITEM_MAX_REPEL
	end

Route44_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route44_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route44_Text_FisherWilton1Seen:
    .string "אוי!\p"
    .string "בגללך פספסתי פוליוואג!\n"
    .string "מה אתה מתכוון לעשות בקשר לזה?$"

Route44_Text_FisherWilton1Beaten:
    .string "פשוט תשכח מזה.$"

Route44_Text_FisherWiltonHugePoliwag:
    .string "הפוליוואג הזה שברח לי…\n"
    .string "הוא היה ענק.\p"
    .string "אני נשבע שהוא היה\n"
    .string "באורך 16 רגל!$"

Route44_Text_WiltonRegister:
    .string "הפוליוואג הזה שברח לי…\n"
    .string "הוא היה ענק.\p"
    .string "אני נשבע שהוא היה\n"
    .string "באורך 16 רגל!$"

Route44_Text_WiltonRematchIntro:
    .string "אוי!\p"
    .string "בגללך פספסתי פוליוואג!\n"
    .string "מה אתה מתכוון לעשות בקשר לזה?$"

Route44_Text_WiltonRematchDefeat:
    .string "פשוט תשכח מזה.$"

Route44_Text_WiltonPostRematch:
    .string "הפוליוואג הזה שברח לי…\n"
    .string "הוא היה ענק.\p"
    .string "אני נשבע שהוא היה\n"
    .string "באורך 16 רגל!$"

Route44_Text_WiltonHasItem:
    .string "היי! העליתי בחכה משהו\n"
    .string "שהוא לא פוקימון!\p"
    .string "הנה, זה בשבילך!$"

Route44_Text_WiltonGaveItem:
    .string "אודיע לך אם אדוג\n"
    .string "עוד משהו!$"

Route44_Text_WiltonNoRoom:
    .string "הממ, התיק שלך מלא.\p"
    .string "תחזור כשיהיה לך מקום.$"

Route44_Text_FisherEdgarSeen:
    .string "אני דג עד שאני כבר לא יכול.\p"
    .string "אני גם נלחם עד שאני קורס.\p"
    .string "ככה זה ביני לבין\n"
    .string "הפוקימונים שלי.$"

Route44_Text_FisherEdgarBeaten:
    .string "הממממ… משהו פה לא בסדר.$"

Route44_Text_FisherEdgarAfter:
    .string "זה 100 ניצחונות מול 101 הפסדים.\p"
    .string "אני לא אלחם שוב בזמן הקרוב.$"

Route44_Text_BirdKeeperVance1Seen:
    .string "אתה מכיר את פוקימוני\n"
    .string "הציפורים האגדיים?$"

Route44_Text_BirdKeeperVance1Beaten:
    .string "וואו! אתה ממש תותח.$"

Route44_Text_BirdKeeperVanceBirds:
    .string "ארטיקונו, זאפדוס ומולטרס הם\n"
    .string "שלושת פוקימוני הציפורים האגדיים.\p"
    .string "אבל שמעתי שיש עוד\n"
    .string "ציפורים אגדיות.$"

Route44_Text_VanceRegister:
    .string "ארטיקונו, זאפדוס ומולטרס הם\n"
    .string "שלושת פוקימוני הציפורים האגדיים.\p"
    .string "אבל שמעתי שיש עוד\n"
    .string "ציפורים אגדיות.$"

Route44_Text_VanceRematchIntro:
    .string "אתה מכיר את פוקימוני\n"
    .string "הציפורים האגדיים?$"

Route44_Text_VanceRematchDefeat:
    .string "וואו! אתה ממש תותח.$"

Route44_Text_VancePostRematch:
    .string "ארטיקונו, זאפדוס ומולטרס הם\n"
    .string "שלושת פוקימוני הציפורים האגדיים.\p"
    .string "אבל שמעתי שיש עוד\n"
    .string "ציפורים אגדיות.$"

Route44_Text_PsychicPhilSeen:
    .string "אני הולך לנצח, בטוח!$"

Route44_Text_PsychicPhilBeaten:
    .string "אררג… איזה הפסד מזעזע…$"

Route44_Text_PsychicPhilAfter:
    .string "חשוב להאמין באמת\n"
    .string "במה שאתה עושה.$"

Route44_Text_PokemaniacZachSeen:
    .string "אני אעשה הכול כדי לשים יד\n"
    .string "על פוקימונים נדירים!$"

Route44_Text_PokemaniacZachBeaten:
    .string "אוווה, הפוקימונים שלך\n"
    .string "כל כך מושכים.$"

Route44_Text_PokemaniacZachAfter:
    .string "אם לפוקימון יש צבעים שונים\n"
    .string "מהרגיל, הוא שווה יותר.\p"
    .string "מה? אתה אומר שזה לא נכון?$"

Route44_Text_CooltrainermAllenSeen:
    .string "אני רואה עליך שאתה\n"
    .string "מאמן טוב.\p"
    .string "אני טוב בפוקימונים, ואני\n"
    .string "רואה שגם אתה.$"

Route44_Text_CooltrainermAllenBeaten:
    .string "אוף! זה הפסד מוחלט מצידי.$"

Route44_Text_CooltrainermAllenAfter:
    .string "וואו. יש לך הרבה תגים.\p"
    .string "אין פלא שאתה כל כך חזק.\p"
    .string "מעניין אם מורטי ממכון אקרוטיק\n"
    .string "עדיין מתאמן?\p"
    .string "הוא ממש ריסק אותי.$"

Route44_Text_CooltrainerfCybilSeen:
    .string "אתה נראה חזק.\p"
    .string "מאמנים טובים מחפשים יריבים\n"
    .string "קשוחים באופן אינסטינקטיבי.$"

Route44_Text_CooltrainerfCybilBeaten:
    .string "לא! ככה זה בכלל לא ילך.$"

Route44_Text_CooltrainerfCybilAfter:
    .string "כולנו משתפרים כשאנחנו חווים\n"
    .string "הרבה קרבות.\p"
    .string "נלחמתי המון כדי להיות מה שאני\n"
    .string "היום - מאמנת עילית.$"

Route44_Text_Sign1:
    .string "דרך 44\n"
    .string "שביל הקרח לפניך$"

Route44_Text_Sign2:
    .string "דרך 44\p"
    .string "העיירה מהגוני - העיר בלקתורן$"

