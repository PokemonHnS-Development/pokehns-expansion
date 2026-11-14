Route34_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route34_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route34_OnTransition: 
	specialvar VAR_RESULT, GetDaycareState
	call_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_MapScript_EggReady
	callnative SetTimeBasedEncounters
	end	

Route34_MapScript_EggReady::
	setobjectxyperm LOCALID_ROUTE34_DAYCAREMAN, 30, 34
	return

Route34_EventScript_YoungsterSamuel::
	trainerbattle_single TRAINER_SAMUEL_HNS, Route34_Text_YoungsterSamuel_Seen, Route34_Text_YoungsterSamuel_Beaten
	msgbox Route34_Text_YoungsterSamuel_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_YoungsterIan::
	trainerbattle_single TRAINER_IAN_HNS, Route34_Text_YoungsterIan_Seen, Route34_Text_YoungsterIan_Beaten
	msgbox Route34_Text_YoungsterIan_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_CamperTodd::
	trainerbattle_single TRAINER_TODD_HNS, Route34_Text_CamperTodd_Seen, Route34_Text_CamperTodd_Beaten, Route34_EventScript_RegisterTodd
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route34_EventScript_RematchTodd
	msgbox Route34_Text_CamperTodd_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterTodd::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_ToddRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TODD_HNS
	release
	end

Route34_EventScript_RematchTodd::
	trainerbattle_rematch TRAINER_TODD_HNS, Route34_Text_ToddRematchIntro, Route34_Text_ToddRematchDefeat
	msgbox Route34_Text_ToddPostRematch, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_PicnickerGina::
	trainerbattle_single TRAINER_GINA_HNS, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten, Route34_EventScript_RegisterGina
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route34_EventScript_RematchGina
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterGina::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_GinaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GINA_HNS
	release
	end

Route34_EventScript_RematchGina::
	trainerbattle_rematch TRAINER_GINA_HNS, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_OfficerKeith::
	trainerbattle_single TRAINER_KEITH_HNS, Route34_Text_OfficerKeith_Seen, Route34_Text_OfficerKeith_Win
	msgbox Route34_Text_OfficerKeith_After, MSGBOX_AUTOCLOSE
	end


Route34_EventScript_PokefanMBrandon::
	trainerbattle_single TRAINER_BRANDON_HNS, Route34_Text_PokefanBrandon_Seen, Route34_Text_PokefanBrandon_Beaten
	msgbox Route34_Text_PokefanBrandon_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Irene::
	trainerbattle_single TRAINER_IRENE_HNS, Route34_Text_CooltrainerIrene_Seen, Route34_Text_CooltrainerIrene_Beaten
	msgbox Route34_Text_CooltrainerIrene_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Jenn::
	trainerbattle_single TRAINER_JENN_HNS, Route34_Text_CooltrainerJenn_Seen, Route34_Text_CooltrainerJenn_Beaten
	msgbox Route34_Text_CooltrainerJenn_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Kate::
	trainerbattle_single TRAINER_KATE_HNS, Route34_Text_CooltrainerKate_Seen, Route34_Text_CooltrainerKate_Beaten
	msgbox Route34_Text_CooltrainerKate_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Sign1::
	lock
	msgbox Route34_Text_Sign_Route34, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign2::
	lock
	msgbox Route34_Text_Sign_DayCare, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign3::
	lock
	msgbox Route34_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Item_SoftSand::
	finditem ITEM_SOFT_SAND
	end

Route34_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end
	
Route34_EventScript_Item_Embargo::
    finditem ITEM_TM_EMBARGO
    end


Route34_Text_YoungsterSamuel_Seen:
	.string "היי! אני מחפש מאנקי!$"

Route34_Text_YoungsterSamuel_Beaten:
	.string "הפסדתי לזר שעבר כאן!$"

Route34_Text_YoungsterSamuel_After:
	.string "אני הולך להתאמן עוד יותר קשה.\p"
	.string "אחרי הכול, אני רוצה להיות\n"
	.string "מנהיג מכון.$"

Route34_Text_YoungsterIan_Seen:
	.string "אני הכי טוב בכיתה שלי\n"
	.string "בפוקימונים.$"

Route34_Text_YoungsterIan_Beaten:
	.string "לא! יש מאמנים טובים ממני…$"

Route34_Text_YoungsterIan_After:
	.string "אני מתאמץ כדי להיות\n"
	.string "הכוכב של הכיתה.$"

Route34_Text_CamperTodd_Seen:
	.string "אני בטוח ביכולת שלי\n"
	.string "לגדל פוקימונים.\p"
	.string "רוצה לראות?$"

Route34_Text_CamperTodd_Beaten:
	.string "פישלתי באימונים שלי?$"

Route34_Text_CamperTodd_After:
	.string "אולי כדאי לי לקחת אחד למעון היום,\n"
	.string "או אולי להשתמש בכמה פריטים…$"

Route34_Text_ToddRegister:
	.string "אולי כדאי לי לקחת אחד למעון היום,\n"
	.string "או אולי להשתמש בכמה פריטים…$"

Route34_Text_ToddRematchIntro:
	.string "אני בטוח ביכולת שלי\n"
	.string "לגדל פוקימונים.\p"
	.string "רוצה לראות?$"

Route34_Text_ToddRematchDefeat:
	.string "פישלתי באימונים שלי?$"

Route34_Text_ToddPostRematch:
	.string "אולי כדאי לי לקחת אחד למעון היום,\n"
	.string "או אולי להשתמש בכמה פריטים…$"

Route34_Text_GinaRegister:
	.string "אתה חזק מדי בשביל להיות\n"
	.string "שותף לאימונים.$"

Route34_Text_PicnickerGina_Seen:
	.string "אתה מאמן?\p"
	.string "בוא נעשה קרב אימון.$"

Route34_Text_PicnickerGina_Beaten:
	.string "אוי, לא! אני פשוט לא מצליחה לנצח…$"

Route34_Text_PicnickerGina_After:
	.string "אתה חזק מדי בשביל להיות\n"
	.string "שותף לאימונים.$"

Route34_Text_OfficerKeith_Seen:
	.string "מי שם?\n"
	.string "מה אתה זומם?$"

Route34_Text_OfficerKeith_Win:
	.string "אתה ילד קטן וקשוח.$"

Route34_Text_OfficerKeith_After:
	.string "כן, הכול בסדר היום.\p"
	.string "תתנהג יפה ותתרחק מצרות.$"

Route34_Text_OfficerKeith_Daytime:
	.string "I'm on patrol for suspicious\n"
	.string "individuals.$"

Route34_Text_PokefanBrandon_Seen:
	.string "הרגע קיבלתי את הפוקימון שלי\n"
	.string "בחזרה ממעון היום.\p"
	.string "בוא נראה כמה הוא התחזק!$"

Route34_Text_PokefanBrandon_Beaten:
	.string "למה זה נגמר ככה?$"

Route34_Text_PokefanBrandon_After:
	.string "הפוקימון שלי חזר עם\n"
	.string "מהלכים חדשים.\p"
	.string "זה בלבל אותי לגמרי!$"

Route34_Text_Sign_IlexForest:
	.string "ILEX FOREST\n"
	.string "THROUGH THE GATE$"

Route34_Text_Sign_Route34:
	.string "דרך 34\n"
	.string "העיר גולדנרוד - העיירה אזייליה\p"
	.string "יער אילקס איפשהו באמצע$"

Route34_Text_TrainerTips:
	.string "טיפים למאמנים\p"
	.string "בעצי פירות צומחים פירות\n"
	.string "חדשים כמה פעמים ביום.\p"
	.string "כדאי לרשום איזה עץ\n"
	.string "נושא אילו פירות.$"

Route34_Text_CooltrainerIrene_Seen:
	.string "איירין: מי אתה?!$"

Route34_Text_CooltrainerIrene_Beaten:
	.string "איירין: אוווו! אתה חזק מדי!$"

Route34_Text_CooltrainerIrene_After1:
	.string "IRENE: My sister KATE will get you\n"
	.string "for this!$"

Route34_Text_CooltrainerIrene_After2:
	.string "איירין: החוף הזה נהדר, נכון?\p"
	.string "זה המפלט הסודי הקטן שלנו!$"

Route34_Text_CooltrainerJenn_Seen:
	.string "ג'ן: מה זה…?\n"
	.string "מה אתה עושה?$"

Route34_Text_CooltrainerJenn_Beaten:
	.string "ג'ן: סליחה, איירין! אחותי היקרה!$"

Route34_Text_CooltrainerJenn_After1:
	.string "JENN: Don't get cocky! My sister\n"
	.string "KATE is tough!$"

Route34_Text_CooltrainerJenn_After2:
	.string "ג'ן: אור השמש מחזק\n"
	.string "את הגוף.$"

Route34_Text_CooltrainerKate_Seen:
	.string "קייט: אני חייבת להחזיר לך\n"
	.string "על מה שעשית לאחיות שלי!$"

Route34_Text_CooltrainerKate_Beaten:
	.string "קייט: לא! אני לא מאמינה שהפסדתי.$"

Route34_Text_CooltrainerKate_GiveSoftSand:
	.string "KATE: You are so strong.\n"
	.string "We lost with no excuses...\p"
	.string "Here, take this!$"

Route34_Text_CooltrainerKate_After:
	.string "קייט: סליחה שהתנפלנו עליך.\p"
	.string "לא ציפינו שמישהו ימצא\n"
	.string "אותנו כאן. ממש הבהלת אותנו.$"


Route34_Text_Sign_DayCare:
	.string "מעון היום\p"
	.string "נגדל בשבילך את הפוקימונים שלך!$"
