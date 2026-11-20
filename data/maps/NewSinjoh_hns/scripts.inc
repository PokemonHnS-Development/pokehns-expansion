NewSinjoh_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_On_Transition
	.byte 0

NewSinjoh_On_Transition:
    setflag FLAG_VISITED_NEW_SINJOH
	end

NewSinjoh_EventScript_TriggerNorthGate::
	lock
	msgbox NewSinjoh_Text_TriggerNorthGate, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	release
	end

NewSinjoh_Text_TriggerNorthGate:
	.string "עדיף לא לתת לנערות הקימונו לחכות.$"

NewSinjoh_EventScript_PetStantler::
    lock
	faceplayer
	playmoncry SPECIES_STANTLER, 0
	msgbox NewSinjoh_Text_Stantler_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Text_Stantler_Cry:
    .string "לררררר!$"

NewSinjoh_EventScript_Steven::
	msgbox NewSinjoh_Text_Steven, MSGBOX_AUTOCLOSE
	end

NewSinjoh_Text_Steven:
	.string "סטיבן: גברתי, אפשר לעזור לך\n"
	.string "להגיע למעיין ההוא?\p"
	.string "נראה שיש שם הרבה מקום.$"

NewSinjoh_MilkMan_EventScript_Seller::
	lock
	faceplayer
	checkitem ITEM_MOOMOO_MILK, 99
	goto_if_eq VAR_RESULT, 1, MilkMan_EventScript_Battle
	showmoneybox 0, 0
	msgbox NewSinjoh_MilkMan_text_BuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk
	msgbox NewSinjoh_MilkMan_NoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_EventScript_MilkMan_BuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox NewSinjoh_MilkMan_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk

	msgbox NewSinjoh_MilkMan_GotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox NewSinjoh_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_BagFull::
	msgbox NewSinjoh_MilkMan_NoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_MilkMan_NotEnough::
	msgbox NewSinjoh_MilkMan_NoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_text_BuyMilk:
	.string "אני החלבן.\p"
	.string "החלב שלי טעים.\p"
	.string "אם תרצה ממנו היום, זה יעלה ¥500.$"

NewSinjoh_MilkMan_GotMilk:
	.string "הנה, בבקשה!\n"
	.string "הוא מועשר במה שהעולם רוצה.$"

NewSinjoh_MilkMan_NoMoney:
	.string "מצטער.\n"
	.string "תשיג קצת כסף, ואז נעשה עסק!$"

NewSinjoh_MilkMan_NoRoom:
	.string "נראה שהתיק שלך מלא.$"

NewSinjoh_MilkMan_NoSale:
	.string "אתה לא רוצה?\n"
	.string "יש בו את מה שמגיע לעולם.$"

NewSinjoh_MilkMan_Text_WouldYouLikeAnother:
	.string "מה דעתך על עוד אחד?$"

NewSinjoh_Text_GotMilk:
	.string "{PLAYER} קיבל חלב מומו.$"

MilkMan_EventScript_Battle:: 
    msgbox MilkMan_Battle_text
    Trainerbattle_no_intro TRAINER_MILKMAN_HNS, NewSinjoh_MilkMan_text_Lose
    release
    end

MilkMan_Battle_text:
	.string "אני החלבן,\p"
	.string "החלב שלי טעים.\p"
	.string "היום יש משלוח מיוחד!$"

NewSinjoh_MilkMan_text_Lose:
	.string "העולם הזה מושלם.\n"
	.string "נכון?$"

NewSinjoh_Script_TravelMart::
	lock
	faceplayer
	message NewSinjoh_Text_TravelShopGreeting
	waitmessage
	pokemart NewSinjoh_Pokemart_TravelShop
	msgbox NewSinjoh_Text_TravelShopEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Pokemart_TravelShop:
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_ELIXER
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_MAX_LURE
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NONE

NewSinjoh_Text_TravelShopGreeting:
	.string "ברוכים הבאים לחנות הציוד הקטנה שלי.\n"
	.string "איך אפשר לעזור?$"

NewSinjoh_Text_TravelShopEnd:
	.string "נשמח לראות אותך שוב.$"

Script_NewSinjoh_Traveler_Brother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_TravelBrother_Greeting
	release
	end

NewSinjoh_Text_TravelBrother_Greeting:
    .string "כל המוצרים שלנו תוצרת בית\n"
    .string "וגידול מקומי!\p"
    .string "אחותי הגדולה פתחה את החנות,\p"
    .string "כי רשת חנויות הפוקימון לא מוכנה\n"
    .string "לפתוח סניף כל כך רחוק מעיר גדולה.$"

NewSinjoh_EventScript_Josh::
	msgbox NewSinjoh_Text_Josh, MSGBOX_NPC
	end

NewSinjoh_Text_Josh:
	.string "המקום הזה מטורף!\p"
	.string "להסתיר את המעיינות החמים\n"
	.string "האלה מהעולם זו שערורייה.\p"
	.string "אני הולך לספר לכל החברים שלי!$"

NewSinjoh_EventScript_Janice::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_JaniceAfter
	msgbox NewSinjoh_Text_Janice, MSGBOX_NPC
	end
NewSinjoh_EventScript_JaniceAfter::
	msgbox NewSinjoh_Text_JaniceAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Janice:
	.string "המעיינות האלה קסומים, אבל יש לי הרגשה\n"
	.string "שהמקומיים נועצים בנו מבטים עוינים.$"
NewSinjoh_Text_JaniceAfter:
	.string "המעיינות האלה קסומים,\n"
	.string "והמקומיים כל כך נחמדים כשמכירים אותם!$"

NewSinjoh_EventScript_OldLady1::
	msgbox NewSinjoh_Text_OldLady1, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady1:
	.string "אין כמו נוף יפה כדי להחיות\n"
	.string "את הנשמה הזקנה שלי.$"

NewSinjoh_EventScript_OldLady2::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady2Steven
	msgbox NewSinjoh_Text_OldLady2, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady2Steven::
	msgbox NewSinjoh_Text_OldLady2Steven, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady2:
	.string "נהדר, עכשיו התיירים האלה\n"
	.string "משתלטים על המעיינות החמים שלנו!\p"
	.string "בזמן האחרון צרה רודפת צרה!$"
NewSinjoh_Text_OldLady2Steven:
	.string "איזה בחור צעיר ונאה!\p"
	.string "אולי התיירים האלה לא\n"
	.string "כל כך גרועים בסך הכול.$"

NewSinjoh_EventScript_OldLady3::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady3After
	msgbox NewSinjoh_Text_OldLady3, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady3After::
	msgbox NewSinjoh_Text_OldLady3After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady3:
	.string "איך האישה ההיא יכולה להיות\n"
	.string "כל כך גסה כלפי האורחים שלנו?\p"
	.string "היא צריכה לטבול קצת במעיינות.\p"
	.string "יש מספיק מקום לכולם.$"
NewSinjoh_Text_OldLady3After:
	.string "נראה שכולם כאן\n"
	.string "מתחילים להתרגל זה לזה.\p"
	.string "יופי!$"

NewSinjoh_EventScript_SpringsSage::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_SpringsSageAfter
	msgbox NewSinjoh_Text_SpringsSage, MSGBOX_NPC
	end
NewSinjoh_EventScript_SpringsSageAfter::
	msgbox NewSinjoh_Text_SpringsSageAfter, MSGBOX_NPC
	end

NewSinjoh_Text_SpringsSage:
	.string "מאז שהגיעו החדשים,\n"
	.string "הקהילה שלנו סובלת מפילוג ומריבות.\p"
	.string "לא משנה מה נקודת המבט שלך,\n"
	.string "ברור שהאיזון הופר.\p"
	.string "יש לנהוג באדיבות כלפי\n"
	.string "המקומיים והתיירים כאחד.$"
NewSinjoh_Text_SpringsSageAfter:
	.string "המצב השתפר מאז\n"
	.string "שהפוקימונים האגדיים הורגעו.\p"
	.string "האיזון חזר לסינג'ו.$"

NewSinjoh_EventScript_Sage2::
	msgbox NewSinjoh_Text_Sage2, MSGBOX_NPC
	end

NewSinjoh_Text_Sage2:
	.string "הזמנים משתנים, אבל הסטנטלר עדיין\n"
	.string "מתאספים. ועל כך נוכל להודות.$"

NewSinjoh_EventScript_Daughter::
	msgbox NewSinjoh_Text_Daughter, MSGBOX_NPC
	end

NewSinjoh_Text_Daughter:
    .string "ויייייי!!\p"
    .string "תראי, אמא!\n"
    .string "בלי ידיים!\p"
    .string "בדיוק כמו גולשי הסנובורד!$"

NewSinjoh_EventScript_Mother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Mother, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWSINJOH_MOTHER, DIR_EAST
	release
	end

NewSinjoh_Text_Mother:
    .string "תראה איך הקטנה המתוקה שלי מחליקה!\p"
    .string "משטח ההחלקה הזה קיים כבר דורות, אבל\n"
    .string "הילדים לא השתמשו בו עד שהגיעו החדשים.$"

NewSinjoh_EventScript_Welcome_Sign::
	msgbox NewSinjoh_Text_Welcome_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Welcome_Sign:
	.string "סינג'ו החדשה$"

NewSinjoh_EventScript_Resturant_Sign::
	msgbox NewSinjoh_Text_Resturant_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Resturant_Sign:
	.string "בית קפה משפחתי$"

NewSinjoh_EventScript_Cave_Sign::
	msgbox NewSinjoh_Text_Cave_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Cave_Sign:
	.string "מערת המעיינות החמים$"

NewSinjoh_EventScript_Hiker::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_HikerAfter
	msgbox NewSinjoh_Text_Hiker, MSGBOX_NPC
	end
NewSinjoh_EventScript_HikerAfter::
	msgbox NewSinjoh_Text_HikerAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Hiker:
	.string "העסקים פורחים!\p"
	.string "אבל המחירים עלו מאז שאנשי העיר\n"
	.string "התחילו להתעניין בעיירה הקטנה שלנו.$"
NewSinjoh_Text_HikerAfter:
	.string "העסקים פורחים!\p"
	.string "ובזכות הטיפים הנדיבים של הבחור\n"
	.string "עם השיער הכסוף, המחירים ירדו!$"

NewSinjoh_EventScript_OldLady4::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady4After
	msgbox NewSinjoh_Text_OldLady4, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady4After::
	msgbox NewSinjoh_Text_OldLady4After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady4:
	.string "אני מוכרת רק למקומיים!$"
NewSinjoh_Text_OldLady4After:
	.string "אני עדיין מוכרת רק למקומיים!$"

NewSinjoh_EventScript_Item_DuskBall::
	finditem ITEM_DUSK_BALL
    end


