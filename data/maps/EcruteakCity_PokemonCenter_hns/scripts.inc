EcruteakCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EcruteakCity_PokemonCenter_OnTransition
	.byte 0

EcruteakCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY_HNS
	end

EcruteakCity_PokemonCenter_EventScript_Bill::
	lock
	delay 30
	playse SE_PC_OFF
	delay 55
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill1, MSGBOX_DEFAULT
	msgbox EcruteakCity_PokemonCenter1F_Text_Bill2, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, EcruteakCity_PokemonCenter_EventScript_BillLeaveBot
	call_if_eq VAR_FACING, DIR_WEST, EcruteakCity_PokemonCenter_EventScript_BillLeaveTop
	playse SE_EXIT
	setflag FLAG_HIDE_ECRUTEAK_BILL
	removeobject LOCALID_ECRUTEAK_BILL
	setflag FLAG_SYS_PC_BILL
	clearflag FLAG_HIDE_GOLDENROD_BILL
	release
	end

EcruteakCity_PokemonCenter_EventScript_BillFaceDown::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_SOUTH
	return

EcruteakCity_PokemonCenter_EventScript_BillFaceRight::
	turnobject LOCALID_ECRUTEAK_BILL, DIR_EAST
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveTop::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillTop
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_BillLeaveBot::
	applymovement LOCALID_ECRUTEAK_BILL, EcruteakCity_PokemonCenter_Movement_BillBot
	waitmovement 0
	return

EcruteakCity_PokemonCenter_EventScript_Hiker::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Woman::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakCity_PokemonCenter1F_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_PokemonCenter_Movement_BillTop:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

EcruteakCity_PokemonCenter_Movement_BillBot:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end


EcruteakCity_PokemonCenter1F_Text_Bill1:
	.string "היי, אני ביל. ואיך קוראים לך?\p"
	.string "הממ, {PLAYER}, אה?\n"
	.string "הגעת בדיוק בזמן.$"

EcruteakCity_PokemonCenter1F_Text_Bill2:
	.string "בדיוק סיימתי לכוונן את\n"
	.string "מערכת אחסון הפוקימונים שלי.\p"
	.string "מכיר את המחשב שבו מאחסנים\n"
	.string "את כל הפוקימונים שלך?\p"
	.string "אני פיתחתי אותו בעצמי!\p"
	.string "אחרי ההתקנה הזאת, המחשב שלי פועל\n"
	.string "בכל מרכזי הפוקימון בג'וטו ובקאנטו.\p"
	.string "אני חייב למהר בחזרה לגולדנרוד\n"
	.string "לראות את המשפחה.\p"
	.string "אתה מוזמן לבקר מתי שתרצה!\p"
	.string "ביי-ביי!$"

EcruteakCity_PokemonCenter1F_Text_PokefanM:
	.string "הריקוד של נערות הקימונו\n"
	.string "פשוט נפלא.\p"
	.string "בדיוק כמו הדרך שבה הן\n"
	.string "משתמשות בפוקימונים שלהן.$"

EcruteakCity_PokemonCenter1F_Text_PokefanM_Mobile:
	.string "You must be hoping to battle more\n"
	.string "people, right?\p"
	.string "There's apparently some place where\n"
	.string "trainers gather.\p"
	.string "Where, you ask?\p"
	.string "It's a little past OLIVINE CITY.$"

EcruteakCity_PokemonCenter1F_Text_CooltrainerF:
	.string "מורטי, מנהיג המכון, הוא\n"
	.string "מגנייייב.\p"
	.string "וגם הפוקימונים שלו ממש קשוחים.$"

EcruteakCity_PokemonCenter1F_Text_GymGuide:
	.string "אגם הזעם…\p"
	.string "להקת גרידוס שהופיעה שם…\p"
	.string "אני מריח פה קנוניה. אני פשוט יודע!$"

