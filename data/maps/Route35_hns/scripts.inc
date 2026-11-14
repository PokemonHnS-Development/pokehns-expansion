Route35_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route35_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route35_OnTransition: 
	callnative SetTimeBasedEncounters
	end	

Route35_EventScript_CamperIvan::
	trainerbattle_single TRAINER_IVAN_HNS, Route35_Text_CamperIvanSeen, Route35_Text_CamperIvanBeaten
	msgbox Route35_Text_CamperIvanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_CamperElliot::
	trainerbattle_single TRAINER_ELLIOT_HNS, Route35_Text_CamperElliotSeen, Route35_Text_CamperElliotBeaten
	msgbox Route35_Text_CamperElliotAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerBrooke::
	trainerbattle_single TRAINER_BROOKE_HNS, Route35_Text_PicnickerBrookeSeen, Route35_Text_PicnickerBrookeBeaten
	msgbox Route35_Text_PicnickerBrookeAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerKim::
	trainerbattle_single TRAINER_KIM_HNS, Route35_Text_PicnickerKimSeen, Route35_Text_PicnickerKimBeaten
	msgbox Route35_Text_PicnickerKimAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BirdKeeperBryan::
	trainerbattle_single TRAINER_BRYAN_HNS, Route35_Text_BirdKeeperBryanSeen, Route35_Text_BirdKeeperBryanBeaten
	msgbox Route35_Text_BirdKeeperBryanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_JugglerIrwin::
	trainerbattle_single TRAINER_IRWIN_HNS, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten, Route35_EventScript_RegisterIrwin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route35_EventScript_RematchIrwin
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterIrwin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_IrwinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_IRWIN_HNS
	release
	end

Route35_EventScript_RematchIrwin::
	trainerbattle_rematch TRAINER_IRWIN_HNS, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BugCatcherArnie::
	trainerbattle_single TRAINER_ARNIE_HNS, Route35_Text_BugCatcherArnieSeen, Route35_Text_BugCatcherArnieBeaten, Route35_EventScript_RegisterArnie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route35_EventScript_RematchArnie
	msgbox Route35_Text_BugCatcherArnieAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterArnie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_ArnieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ARNIE_HNS
	release
	end

Route35_EventScript_RematchArnie::
	trainerbattle_rematch TRAINER_ARNIE_HNS, Route35_Text_ArnieRematchIntro, Route35_Text_ArnieRematchDefeat
	msgbox Route35_Text_ArniePostRematch, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_FirebreatherWalt::
	trainerbattle_single TRAINER_WALT_HNS, Route35_Text_FirebreatherWaltSeen, Route35_Text_FirebreatherWaltBeaten
	msgbox Route35_Text_FirebreatherWaltAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PolicemanDirk::
	trainerbattle_single TRAINER_DIRK_HNS, Route35_Text_OfficerDirkSeen, Route35_Text_OfficerDirkBeaten
	msgbox Route35_Text_OfficerDirkAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_Sign1::
	lock
	msgbox Route35_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Sign2::
	lock
	msgbox Route35_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Item_Payback::
	finditem ITEM_TM_PAYBACK
	end

Route35_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route35_EventScript_Item_ParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

Route35_Text_CamperIvanSeen:
	.string "קיבלתי מידע על פוקימונים\n"
	.string "מהרדיו שלי. נראה לי שאני טוב.$"

Route35_Text_CamperIvanBeaten:
	.string "אני נכנע!$"

Route35_Text_CamperIvanAfter:
	.string "המוזיקה ברדיו משנה את\n"
	.string "מצב הרוח של פוקימונים פראיים.$"

Route35_Text_CamperElliotSeen:
	.string "אני אראה לחברה שלי\n"
	.string "כמה אני תותח!$"

Route35_Text_CamperElliotBeaten:
	.string "חבל שלא הפסדת בשבילי…$"

Route35_Text_CamperElliotAfter:
	.string "הושפלתי מול\n"
	.string "החברה שלי…$"

Route35_Text_PicnickerBrookeSeen:
	.string "החבר שלי חלש,\n"
	.string "אז אני לא יכולה לסמוך עליו.$"

Route35_Text_PicnickerBrookeBeaten:
	.string "אוי, וואו! אתה כל כך חזק!$"

Route35_Text_PicnickerBrookeAfter:
	.string "אני יכולה לסמוך על הפוקימונים שלי\n"
	.string "יותר מאשר על החבר שלי.$"

Route35_Text_PicnickerKimSeen:
	.string "אתה הולך למכון? גם אני!$"

Route35_Text_PicnickerKimBeaten:
	.string "אוי. לא הצלחתי לנצח…$"

Route35_Text_PicnickerKimAfter:
	.string "תגי המכונים יפים.\n"
	.string "אני אוספת אותם.$"

Route35_Text_BirdKeeperBryanSeen:
	.string "באילו כדורים אתה משתמש?$"

Route35_Text_BirdKeeperBryanBeaten:
	.string "אוי! לא מהיר מספיק!$"

Route35_Text_BirdKeeperBryanAfter:
	.string "יש פוקימונים שבורחים מיד.\p"
	.string "כדאי לנסות לתפוס אותם\n"
	.string "בכדור זריז של קורט.\p"
	.string "בכל פעם שאני מוצא פירות אספר,\n"
	.string "אני מביא אותם לקורט.\p"
	.string "הוא הופך אותם לכדור מיוחד.$"

Route35_Text_JugglerIrwinSeen:
	.string "הביטו בלהטוטי הכדורים החינניים שלי!$"

Route35_Text_JugglerIrwinBeaten:
	.string "וואו! זה היה ממש הלם!$"

Route35_Text_JugglerIrwinAfter:
	.string "התכוונתי לסנוור אותך\n"
	.string "בפוקימונים המובחרים שלי.\p"
	.string "אבל הכישרון שלך חישמל אותי!$"

Route35_Text_BugCatcherArnieSeen:
	.string "אני אלך לכל מקום שבו\n"
	.string "מופיעים פוקימונים מסוג חרק.$"

Route35_Text_BugCatcherArnieBeaten:
	.string "מה? לא הייתי אמור להפסיד…$"

Route35_Text_BugCatcherArnieAfter:
	.string "בזכות הוונונאט שלי זכיתי\n"
	.string "בתחרות לכידת החרקים בפארק הלאומי.$"

Route35_Text_IrwinRegister:
	.string "התכוונתי לסנוור אותך\n"
	.string "בפוקימונים המובחרים שלי.\p"
	.string "אבל הכישרון שלך חישמל אותי!$"

Route35_Text_ArnieRegister:
	.string "בזכות הוונונאט שלי זכיתי\n"
	.string "בתחרות לכידת החרקים בפארק הלאומי.$"

Route35_Text_ArnieRematchIntro:
	.string "אני אלך לכל מקום שבו\n"
	.string "מופיעים פוקימונים מסוג חרק.$"

Route35_Text_ArnieRematchDefeat:
	.string "מה? לא הייתי אמור להפסיד…$"

Route35_Text_ArniePostRematch:
	.string "בזכות הוונונאט שלי זכיתי\n"
	.string "בתחרות לכידת החרקים בפארק הלאומי.$"

Route35_Text_BugCatcherArnieYanma:
	.string "Wow… Look at all those YANMA!\p"
	.string "I'm so blown away, I can't move.$"

Route35_Text_FirebreatherWaltSeen:
	.string "אני מתאמן ביריקת אש.$"

Route35_Text_FirebreatherWaltBeaten:
	.string "איי! חרכתי את קצה האף!$"

Route35_Text_FirebreatherWaltAfter:
	.string "מארש הפוקימונים ברדיו\n"
	.string "מושך פוקימונים פראיים.$"

Route35_Text_OfficerDirkSeen:
	.string "סכנה אורבת בלילה!$"

Route35_Text_OfficerDirkBeaten:
	.string "אופס!$"

Route35_Text_OfficerDirkAfter:
	.string "אתה יודע, גם ללילה יש\n"
	.string "כיף משלו.\p"
	.string "אבל בלי להגזים, טוב?$"

Route35_Text_OfficerDirkTough:
	.string "Your POKéMON look pretty tough.\p"
	.string "You could go anywhere safely.$"

Route35_Text_Sign:
	.string "דרך 35$"

Route35_Text_Sign2:
	.string "שער הפארק הלאומי$"
