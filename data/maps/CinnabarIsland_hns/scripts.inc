CinnabarIsland_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0
	
CinnabarIsland_OnTransition:
	setflag FLAG_VISITED_CINNABAR_ISLAND
	callnative SetTimeBasedEncounters
	end

CinnabarIsland_EventScript_Blaine::
    lock
    faceplayer
    msgbox CinnabarIsland_Text_Blaine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_CINNABAR_BLAINE
    removeobject LOCALID_CINNABAR_BLAINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_BLAINE
    release
    end

CinnabarIsland_Text_Blaine:
    .string "בליין: לעולם לא אוותר, עד היום\n"
    .string "שבו אבנה מחדש את מכון סיננבר!\p"
    .string "עד אז אהיה בדוג'ו הלחימה.$"



CinnabarIsland_EventScript_Blue::
	lock
	faceplayer
	goto_if_eq VAR_NUM_BADGES, 15, CinnabarIsland_EventScript_BlueActive
	msgbox CinnabarIsland_Text_BlueBefore, MSGBOX_NPC
	release
	end

CinnabarIsland_EventScript_BlueActive::
	msgbox CinnabarIsland_Text_Blue, MSGBOX_NPC
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CINNABAR_BLUE
	removeobject LOCALID_CINNABAR_BLUE
	clearflag FLAG_HIDE_VIRIDIAN_BLUE
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end


CinnabarIsland_Text_BlueBefore:
	.string "מי אתה?\p"
	.string "טוב, די ברור שאתה\n"
	.string "מאמן…\p"
	.string "קוראים לי בלו.\p"
	.string "פעם הייתי האלוף, אם כי\n"
	.string "רק לזמן קצר…\p"
	.string "רד המתערב הזה גמר אותי…\p"
	.string "בכל מקרה, מה אתה רוצה? אתה\n"
	.string "רוצה לאתגר אותי או משהו?\p"
	.string "…לא נעים לי להגיד, אבל\n"
	.string "אין לי מצב רוח לקרב עכשיו.\p"
	.string "תסתכל טוב מסביב…\p"
	.string "הר געש מתפרץ, ובן רגע\n"
	.string "עיירה שלמה נעלמת.\p"
	.string "אנחנו יכולים להמשיך לנצח ולהפסיד\n"
	.string "בקרבות פוקימונים.\p"
	.string "אבל אם הטבע רק זז קצת,\n"
	.string "אפשר להפסיד הכול בשנייה.\p"
	.string "…\p"
	.string "ככה זה…\p"
	.string "אבל בכל זאת, אני עדיין מאמן.\p"
	.string "כשאני רואה יריב חזק,\n"
	.string "מתחשק לי להילחם.\p"
	.string "אם אתה רוצה להילחם בי,\n"
	.string "תצטרך קודם 15 תגים.\p"
	.string "אז אתמודד איתך.$"

CinnabarIsland_Text_Blue:
	.string "מי אתה?\p"
	.string "טוב, די ברור שאתה\n"
	.string "מאמן…\p"
	.string "קוראים לי בלו.\p"
	.string "פעם הייתי האלוף, אם כי\n"
	.string "רק לזמן קצר…\p"
	.string "רד המתערב הזה גמר אותי…\p"
	.string "בכל מקרה, מה אתה רוצה? אתה\n"
	.string "רוצה לאתגר אותי או משהו?\p"
	.string "…לא נעים לי להגיד, אבל\n"
	.string "אין לי מצב רוח לקרב עכשיו.\p"
	.string "תסתכל טוב מסביב…\p"
	.string "הר געש מתפרץ, ובן רגע\n"
	.string "עיירה שלמה נעלמת.\p"
	.string "אנחנו יכולים להמשיך לנצח ולהפסיד\n"
	.string "בקרבות פוקימונים.\p"
	.string "אבל אם הטבע רק זז קצת,\n"
	.string "אפשר להפסיד הכול בשנייה.\p"
	.string "…\p"
	.string "ככה זה…\p"
	.string "אבל בכל זאת, אני עדיין מאמן.\p"
	.string "כשאני רואה יריב חזק,\n"
	.string "מתחשק לי להילחם.\p"
	.string "אם אתה רוצה להילחם בי,\n"
	.string "בוא למכון וירידיאן.\p"
	.string "אז אתמודד איתך.$"

CinnabarIsland_EventScript_Sign::
	msgbox CinnabarIsland_Text_Sign, MSGBOX_SIGN
	end

CinnabarIsland_EventScript_GymSign::
	msgbox CinnabarIsland_Text_GymSign, MSGBOX_SIGN
	end

CinnabarIsland_Text_GymSign:
	.string "יש כאן הודעה…\p"
	.string "מכון סיננבר עבר לאיי הקצף.\p"
	.string "בליין$"

CinnabarIsland_Text_Sign:
	.string "האי סיננבר\p"
	.string "עיירת האש של התשוקה הבוערת$"

