Route45_hns_MapScripts::
	.byte 0

Route45_EventScript_Erik::
	trainerbattle_single TRAINER_ERIK_HNS, Route45_Text_HikerErikSeen, Route45_Text_HikerErikBeaten
	msgbox Route45_Text_HikerErikAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Michael::
	trainerbattle_single TRAINER_MICHAEL_HNS, Route45_Text_HikerMichaelSeen, Route45_Text_HikerMichaelBeaten
	msgbox Route45_Text_HikerMichaelAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Parry::
	trainerbattle_single TRAINER_PARRY_HNS, Route45_Text_HikerParrySeen, Route45_Text_HikerParryBeaten, Route45_EventScript_RegisterParry
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route45_EventScript_RematchParry
	msgbox Route45_Text_HikerParryAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterParry::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_ParryRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_PARRY_HNS
	release
	end

Route45_EventScript_RematchParry::
	trainerbattle_rematch TRAINER_PARRY_HNS, Route45_Text_ParryRematchIntro, Route45_Text_ParryRematchDefeat
	msgbox Route45_Text_ParryPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Timothy::
	trainerbattle_single TRAINER_TIMOTHY_HNS, Route45_Text_HikerTimothySeen, Route45_Text_HikerTimothyBeaten
	msgbox Route45_Text_HikerTimothyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kenji::
	trainerbattle_single TRAINER_KENJI_HNS, Route45_Text_BlackbeltKenjiSeen, Route45_Text_BlackbeltKenjiBeaten, Route45_EventScript_RegisterKenji
	goto_if_set FLAG_KENJI_HAS_ITEM_HNS, Route45_EventScript_KenjiGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route45_EventScript_RematchKenji
	msgbox Route45_Text_BlackbeltKenjiAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterKenji::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_KenjiRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KENJI_HNS
	release
	end

Route45_EventScript_RematchKenji::
	trainerbattle_rematch TRAINER_KENJI_HNS, Route45_Text_KenjiRematchIntro, Route45_Text_KenjiRematchDefeat
	msgbox Route45_Text_KenjiPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiGiveItem::
	msgbox Route45_Text_KenjiHasItem, MSGBOX_DEFAULT
	giveitem VAR_KENJI_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route45_EventScript_KenjiNoRoom
	clearflag FLAG_KENJI_HAS_ITEM_HNS
	msgbox Route45_Text_KenjiGaveItem, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiNoRoom::
	msgbox Route45_Text_KenjiNoRoom, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Ryan::
	trainerbattle_single TRAINER_RYAN_HNS, Route45_Text_CooltrainermRyanSeen, Route45_Text_CooltrainermRyanBeaten
	msgbox Route45_Text_CooltrainermRyanAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kelly::
	trainerbattle_single TRAINER_KELLY_HNS, Route45_Text_CooltrainerfKellySeen, Route45_Text_CooltrainerfKellyBeaten
	msgbox Route45_Text_CooltrainerfKellyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Quentin::
	trainerbattle_single TRAINER_QUENTIN_HNS, Route45_Text_CamperQuentinSeen, Route45_Text_CamperQuentinBeaten
	msgbox Route45_Text_CamperQuentinAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Sign::
	msgbox Route45_Text_Sign, MSGBOX_SIGN
	end

Route45_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route45_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

Route45_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

Route45_EventScript_Item_Nugget::
	finditem ITEM_NUGGET
	end

Route45_Text_HikerErikSeen:
    .string "צריך להיות מוכן לכל דבר!\p"
    .string "בוא נראה אם הפוקימונים שלך\n"
    .string "גודלו כראוי!$"

Route45_Text_HikerErikBeaten:
    .string "אוי, הפסדתי!$"

Route45_Text_HikerErikAfter:
    .string "אחזור לשביל הקרח של בלקתורן\n"
    .string "ואתאמן עוד קצת.$"

Route45_Text_HikerMichaelSeen:
    .string "יו! יש בך להט!\n"
    .string "אבל אתה יודע מה?\p"
    .string "כשזה מגיע ללהט טהור,\n"
    .string "אין עליי!$"

Route45_Text_HikerMichaelBeaten:
    .string "לפוקימונים שלי לא היה מספיק להט!$"

Route45_Text_HikerMichaelAfter:
    .string "וואו, כמה שאני אוהב הגדלת נ”ח!\n"
    .string "ממממ, טעים!\p"
    .string "אני כל הזמן שותה את המנות\n"
    .string "של הפוקימונים שלי!\p"
    .string "אני לא יכול להתאפק!$"

Route45_Text_HikerParrySeen:
    .string "הפוקימונים שלי מלאי עוצמה!$"

Route45_Text_HikerParryBeaten:
    .string "וואהאהאה! אני המפסיד הגדול!$"

Route45_Text_HikerParryAfter:
    .string "אני לא כל כך טוב בחשיבה,\n"
    .string "מבין?\p"
    .string "אז אני פשוט פורץ קדימה בכוח!$"

Route45_Text_ParryRegister:
    .string "אני לא כל כך טוב בחשיבה,\n"
    .string "מבין?\p"
    .string "אז אני פשוט פורץ קדימה בכוח!$"

Route45_Text_ParryRematchIntro:
    .string "הפוקימונים שלי מלאי עוצמה!$"

Route45_Text_ParryRematchDefeat:
    .string "וואהאהאה! אני המפסיד הגדול!$"

Route45_Text_ParryPostRematch:
    .string "אני לא כל כך טוב בחשיבה,\n"
    .string "מבין?\p"
    .string "אז אני פשוט פורץ קדימה בכוח!$"

Route45_Text_HikerTimothySeen:
    .string "למה אני מטפס על הרים?\p"
    .string "כי הם שם.\p"
    .string "למה אני מאמן פוקימונים?\p"
    .string "כי הם שם!$"

Route45_Text_HikerTimothyBeaten:
    .string "הפסדים… גם הם שם!$"

Route45_Text_HikerTimothyAfter:
    .string "הדבר הכי טוב שקרה לי אי פעם\n"
    .string "היה לגלות את הפוקימונים.$"

Route45_Text_HikerParryGivesIron:
    .string "I just can't find a way to win!\p"
    .string "Keep it up!\p"
    .string "Oh, and take this -- it's the\n"
    .string "gift you couldn't take when we\n"
    .string "last met.$"

Route45_Text_BlackbeltKenjiSeen:
    .string "התאמנתי כאן לבד.\p"
    .string "חזה בפירות עמלי!$"

Route45_Text_BlackbeltKenjiBeaten:
    .string "ואאאאררר!$"

Route45_Text_BlackbeltKenjiAfter:
    .string "המצב מחייב צעדים קיצוניים.\p"
    .string "עליי לעלות להרים ולהתאמן\n"
    .string "בבדידות.$"

Route45_Text_KenjiRegister:
    .string "המצב מחייב צעדים קיצוניים.\p"
    .string "עליי לעלות להרים ולהתאמן\n"
    .string "בבדידות.$"

Route45_Text_KenjiRematchIntro:
    .string "התאמנתי כאן לבד.\p"
    .string "חזה בפירות עמלי!$"

Route45_Text_KenjiRematchDefeat:
    .string "ואאאאררר!$"

Route45_Text_KenjiPostRematch:
    .string "המצב מחייב צעדים קיצוניים.\p"
    .string "עליי לעלות להרים ולהתאמן\n"
    .string "בבדידות.$"

Route45_Text_KenjiHasItem:
    .string "היי! אני לוקח הפסקה\n"
    .string "מהאימונים.\p"
    .string "מצאתי משהו טוב כשהייתי\n"
    .string "בחוץ. הנה, קח את זה!$"

Route45_Text_KenjiGaveItem:
    .string "תשתמש בזה היטב!\p"
    .string "אני צריך לחזור לאימונים.\n"
    .string "אוווווואאאררר!$"

Route45_Text_KenjiNoRoom:
    .string "הממ, התיק שלך מלא.\p"
    .string "תחזור כשיהיה לך מקום.$"

Route45_Text_BlackbeltKenjiMorning:
    .string "I'm going to train a bit more\n"
    .string "before I break for lunch.$"

Route45_Text_BlackbeltKenjiNight:
    .string "We had plenty of rest at lunch, so\p"
    .string "now we're all ready to go again!\p"
    .string "We're going to train again!$"

Route45_Text_CooltrainermRyanSeen:
    .string "מה דעתך על\n"
    .string "גידול פוקימונים?$"

Route45_Text_CooltrainermRyanBeaten:
    .string "זכית בכבוד שלי.$"

Route45_Text_CooltrainermRyanAfter:
    .string "אני רואה שאתה מגדל את\n"
    .string "הפוקימונים שלך באכפתיות.\p"
    .string "הקשר שתבנה יציל אותך\n"
    .string "במצבים קשים.$"

Route45_Text_CooltrainerfKellySeen:
    .string "מה אסטרטגיית הקרב שלך?\p"
    .string "זה טיפשי להשתמש במהלכים חזקים\n"
    .string "בלי שום הבחנה.$"

Route45_Text_CooltrainerfKellyBeaten:
    .string "בסדר. הפסדתי.$"

Route45_Text_CooltrainerfKellyAfter:
    .string "אני לא בעד מהלכים חזקים\n"
    .string "מדי.\p"
    .string "אני רוצה לנצח, אבל אני גם\n"
    .string "לא רוצה לפגוע בפוקימונים.$"

Route45_Text_CamperQuentinSeen:
    .string "אני ממש, ממש קשוח!$"

Route45_Text_CamperQuentinBeaten:
    .string "בגבעת המאמנים הייתי קשוח…$"

Route45_Text_CamperQuentinAfter:
    .string "היית פעם בגבעת המאמנים?\p"
    .string "שם אני אף פעם, אף פעם\n"
    .string "לא מפסיד, אבל…$"

Route45_Text_Sign:
    .string "דרך 45\n"
    .string "בהמשך: דרך הררית$"
