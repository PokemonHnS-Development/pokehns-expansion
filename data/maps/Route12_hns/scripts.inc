Route12_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route12_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route12_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route12_EventScript_Martin::
	trainerbattle_single TRAINER_MARTIN_HNS, Route12_Text_FisherMartinSeen, Route12_Text_FisherMartinBeaten
	msgbox Route12_Text_FisherMartinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Stephen::
	trainerbattle_single TRAINER_STEPHEN_HNS, Route12_Text_FisherStephenSeen, Route12_Text_FisherStephenBeaten
	msgbox Route12_Text_FisherStephenAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Barney::
	trainerbattle_single TRAINER_BARNEY_HNS, Route12_Text_FisherBarneySeen, Route12_Text_FisherBarneyBeaten
	msgbox Route12_Text_FisherBarneyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Kyle::
	trainerbattle_single TRAINER_KYLE_HNS, Route12_Text_FisherKyleSeen, Route12_Text_FisherKyleBeaten, Route12_EventScript_RegisterKyle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route12_EventScript_RematchKyle
	msgbox Route12_Text_FisherKyleAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_RegisterKyle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route12_Text_KyleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KYLE_HNS
	release
	end

Route12_EventScript_RematchKyle::
	trainerbattle_rematch TRAINER_KYLE_HNS, Route12_Text_KyleRematchIntro, Route12_Text_KyleRematchDefeat
	msgbox Route12_Text_KylePostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_KYLE_2_HNS, Route12_EventScript_RematchKyleTryGiveItem
	end

Route12_EventScript_RematchKyleTryGiveItem::
	checkitem ITEM_BLUE_SHARD
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_BLUE_SHARD
	closemessage
	end

Route12_EventScript_NewFisher::
	msgbox Route12_Text_NewFisher, MSGBOX_NPC
	end

Route12_EventScript_Elixir::
	finditem ITEM_ELIXIR
	end

Route12_EventScript_Calcium::
	finditem ITEM_CALCIUM
	end

Route12_EventScript_Magikarp::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	msgbox Route12_Text_Magikarp, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route12_EventScript_Tentacruel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route12_Text_Magikarp:
	.string "מג'יקארפ: קאאאארפ.$"

Route12_Text_NewFisher:
	.string "זהירות, משהו אכזרי חי\n"
	.string "במים האלה.$"

Route12_Text_FisherMartinSeen:
	.string "סבלנות היא המפתח גם לדיג\n"
	.string "וגם לפוקימונים.$"

Route12_Text_FisherMartinBeaten:
	.string "גוואאה!$"

Route12_Text_FisherMartinAfterBattle:
	.string "אני חסר סבלנות מדי בשביל דיג…$"

Route12_Text_FisherStephenSeen:
	.string "אני מרגיש כל כך טוב כשאני דג\n"
	.string "ומקשיב למוזיקה ברדיו שלי.$"

Route12_Text_FisherStephenBeaten:
	.string "הרדיו המטופש שלי הסיח את דעתי!$"

Route12_Text_FisherStephenAfterBattle:
	.string "שמעת כבר את תוכניות הרדיו\n"
	.string "של קאנטו? יש כאן מבחר טוב.$"

Route12_Text_FisherBarneySeen:
	.string "מה הדבר הכי חשוב\n"
	.string "בחיי היום-יום שלנו?$"

Route12_Text_FisherBarneyBeaten:
	.string "התשובה - מיד בהמשך!$"

Route12_Text_FisherBarneyAfterBattle:
	.string "אני חושב שחשמל הוא הדבר הכי\n"
	.string "חשוב בחיי היום-יום שלנו.\p"
	.string "אחרת, אנשים לא היו עושים כזה רעש\n"
	.string "כשמפעל החשמל הפסיק לעבוד.$"

Route12_Text_KyleRegister:
	.string "אני אזכור את זה.\n"
	.string "תן לי את המספר שלך!$"

Route12_Text_KyleRematchIntro:
	.string "שכחת?\n"
	.string "בוא נראה!$"

Route12_Text_KyleRematchDefeat:
	.string "זכרת.$"

Route12_Text_KylePostRematch:
	.string "הריגוש שבקרב כמעט טוב\n"
	.string "כמו לתפוס דג גדול!$"

Route12_Text_FisherKyleSeen:
	.string "אתה זוכר?$"

Route12_Text_FisherKyleBeaten:
	.string "אז אתה כן זוכר?$"

Route12_Text_FisherKyleAfterBattle:
	.string "המשיכה שמרגישים בחכה כשפוקימון\n"
	.string "נתפס בקרס…\p"
	.string "זו ההרגשה הכי טובה שיש\n"
	.string "לדייג כמוני.$"

Route12_EventScript_Sign::
	msgbox Route12_Text_Sign, MSGBOX_SIGN
	end

Route12_EventScript_FishingSign::
	msgbox Route12_Text_FishingSpotSign, MSGBOX_SIGN
	end

Route12_Text_Sign:
	.string "דרך 12\p"
	.string "צפונה אל העיירה לבנדר$"

Route12_Text_FishingSpotSign:
	.string "מקום דיג$"

