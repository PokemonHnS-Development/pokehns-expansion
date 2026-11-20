ViridianCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ViridianCity_OnFrame
	.byte 0

ViridianCity_EventScript_CityEnter::
	setflag FLAG_VISITED_VIRIDIAN_CITY
	end

ViridianCity_OnFrame::
	map_script_2 VAR_OAK_MT_SILVER_CALL, 1, ViridianCity_EventScript_OakCall
	.2byte 0

ViridianCity_EventScript_OakCall::
	lock
	setspeaker ViridianCity_Text_OakName
	pokenavcall ViridianCity_Text_OakCall
	waitmessage
	delay 30
	setvar VAR_OAK_MT_SILVER_CALL, 2
	release
	end

ViridianCity_Text_OakName:
	.string "אוק$"

ViridianCity_Text_OakCall:
	.string "אוק: אה, {PLAYER}!\p"
	.string "בוא לבקר אותי במעבדה שלי\n"
	.string "בעיירה פאלט כשתהיה לך הזדמנות.$"

ViridianCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox ViridianCity_Text_CoffeeGramps_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_EventScript_GrampsDoubted
	msgbox ViridianCity_Text_CoffeeGramps_Believed, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_EventScript_GrampsDoubted::
	msgbox ViridianCity_Text_CoffeeGramps_Doubted, MSGBOX_DEFAULT
	closemessage
	release
	end

VirianCity_EventScript_GymGramps::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_Text_GrampsNearGym, MSGBOX_NPC
	end

VirianCity_EventScript_GymGrampsBlue::
	msgbox ViridianCity_Text_GrampsNearGym_BlueReturned, MSGBOX_NPC
	end

ViridianCity_EventScript_Fisher::
	goto_if_set FLAG_GOT_VIRIDIAN_TM_DREAM_EATER, ViridianCity_EventScript_FisherAfter
	msgbox ViridianCity_Text_DreamEaterFisher, MSGBOX_NPC
	giveitem ITEM_TM_DREAM_EATER
	setflag FLAG_GOT_VIRIDIAN_TM_DREAM_EATER
	end

ViridianCity_EventScript_FisherAfter::
	msgbox ViridianCity_Text_DreamEaterFisher_GotTM, MSGBOX_NPC
	end

ViridianCity_EventScript_Youngster::
	msgbox ViridianCity_Text_Youngster, MSGBOX_NPC
	end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_WelcomeSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_CitySign2::
	msgbox ViridianCity_Text_Sign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_Text_CoffeeGramps_Question:
	.string "היי, ילד! הרגע שתיתי אספרסו כפול,\n"
	.string "ואני מתפוצץ מאנרגיה!\p"
	.string "אני חייב לדבר עם מישהו,\n"
	.string "אז אסתפק בך!\p"
	.string "אולי עכשיו אני לא נראה משהו, אבל\n"
	.string "פעם הייתי מומחה בתפיסת פוקימונים.\p"
	.string "אתה מאמין לי?$"

ViridianCity_Text_CoffeeGramps_Believed:
	.string "טוב, טוב. כן, הייתי משהו\n"
	.string "יוצא דופן, אני אומר לך!$"

ViridianCity_Text_CoffeeGramps_Doubted:
	.string "מה? פרחח קטן שכמוך!\p"
	.string "אילו הייתי קצת יותר צעיר,\n"
	.string "הייתי מראה לך מה זה. המף!$"

ViridianCity_Text_GrampsNearGym:
	.string "למכון הזה לא היה מנהיג\n"
	.string "עד לא מזמן.\p"
	.string "בחור צעיר מפאלט הפך למנהיג,\n"
	.string "אבל הוא נעדר לעיתים קרובות.$"

ViridianCity_Text_GrampsNearGym_BlueReturned:
	.string "אתה הולך להילחם\n"
	.string "במנהיג?\p"
	.string "בהצלחה. תצטרך הרבה מזל.$"

ViridianCity_Text_DreamEaterFisherNew:
	.string "…Zzzzz…\p" 
	.string "Yawn!\p"
	.string "I must have dozed off in the sun.\p"
	.string "What? I remind you of somebody?\p"
	.string "I don't know, here, have this.$"


ViridianCity_Text_DreamEaterFisher_GotTM::
	.string "…זזזזז…$"

ViridianCity_Text_DreamEaterFisher:
	.string "פיהוק!\p"
	.string "כנראה נרדמתי בשמש.\p"
	.string "…חלמתי שדראוזי זולל\n"
	.string "לי את החלום. מוזר, לא?\p"
	.string "הא? מה זה?\p"
	.string "מאיפה הגיע המ”מ הזה?\p"
	.string "זה מצמרר! הנה,\n"
	.string "קח את המ”מ הזה.$"

ViridianCity_Text_DreamEaterFisher_GotDreamEater:
	.string "TM42 contains DREAM EATER…\p"
	.string "…Zzzzz…$"

ViridianCity_Text_Youngster:
	.string "שמעתי שביער וירידיאן מפוזרים\n"
	.string "הרבה פריטים על האדמה.$"

ViridianCity_Text_Sign:
	.string "העיר וירידיאן\p"
	.string "גן העדן הירוק הנצחי$"

ViridianCity_Text_GymSign:
	.string "מכון הפוקימון של העיר וירידיאן\n"
	.string "מנהיג: …\p"
	.string "שאר הכיתוב לא קריא…$"

ViridianCity_Text_WelcomeSign:
	.string "ברוכים הבאים לעיר וירידיאן,\p"
	.string "השער לרמת אינדיגו$"

ViridianCity_Text_TrainerHouseSign:
	.string "TRAINER HOUSE\p"
	.string "The Club for Top Trainer Battles$"
