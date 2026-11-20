Route27_House_hns_MapScripts::
	.byte 0

Route27_House_EventScript_Woman::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_TM_SANDSTORM, Route27_House_EventScript_WomanBeforeGiven
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanBeforeGiven::
	msgbox SandstormHouse_Text_Woman1, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, Route27_House_EventScript_WomanHighFriendship
	playfirstmoncry
	applymovement OBJ_EVENT_ID_FOLLOWER FollowerLookAway
	waitmovement OBJ_EVENT_ID_FOLLOWER
	applymovement OBJ_EVENT_ID_FOLLOWER Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_FOLLOWER
	msgbox SandstormHouse_Text_DisloyalMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_House_EventScript_WomanHighFriendship::
	playfirstmoncry
	applymovement OBJ_EVENT_ID_FOLLOWER FollowerDance
	waitmovement 0
	applymovement OBJ_EVENT_ID_FOLLOWER ContestHall_Movement_Heart
	waitmovement 0
	msgbox SandstormHouse_Text_LoyalMon, MSGBOX_DEFAULT
	giveitem ITEM_TM_SANDSTORM
	setflag FLAG_GOT_TM_SANDSTORM
	msgbox SandstormHouse_Text_TM37Description, MSGBOX_DEFAULT
	closemessage
	release
	end

Route27_Movement_FollowerJump:
	jump_in_place_down
	jump_in_place_down
	step_end

SandstormHouse_Text_Woman1:
    .string "לאן אתה הולך עם הפוקימונים?\p"
    .string "לליגת הפוקימון?\p"
    .string "הפוקימונים שלך נאמנים\n"
    .string "מספיק כדי שתנצח?\p"
    .string "בוא נראה…$"

SandstormHouse_Text_LoyalMon:
    .string "אה! הפוקימון שלך סומך עליך מאוד.\p"
    .string "נעים לראות מאמן טוב.\p"
    .string "הנה. מתנה למסע שלך.$"

SandstormHouse_Text_TM37Description:
    .string "מ”מ 37 הוא במקרה סופת חול.\p"
    .string "זה מהלך שגורם נזק לשני הצדדים בקרב.\p"
    .string "הוא מיועד למאמנים מתקדמים בלבד.\p"
    .string "תשתמש בו אם אתה מעז. בהצלחה!$"

SandstormHouse_Text_DisloyalMon:
    .string "אם הוא לא ילמד לסמוך עליך יותר,\n"
    .string "הדרך עלולה להיות קשה.\p"
    .string "אמון הוא הקשר שמחבר\n"
    .string "בין פוקימונים למאמנים.$"


