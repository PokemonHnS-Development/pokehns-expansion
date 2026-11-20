OlivineCity_PortOutside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	.byte 0

OlivineCity_PortOutside_EventScript_Sabrina::
    lock
    faceplayer
    msgbox OlivineCity_PortOutside_Text_Sabrina, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_OLIVINE_SABRINA
    removeobject LOCALID_OLIVINE_SABRINA
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_SABRINA
    release
    end

OlivineCity_PortOutside_Text_Sabrina:
    .string "סברינה: פתאום, בלי שום סיבה,\n"
    .string "מתחשק לי לראות את הים.\p"
    .string "נתראה בדוג'ו הלחימה.$"

OlivineCity_PortOutside_EventScript_Fisherman1::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_PortFisherman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_EventScript_Fisherman2::
	lock
	faceplayer
	msgbox OlivineCity_PortOutside_Text_Fisherman2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_PortOutside_Text_PortFisherman1:
	.string "ספינת אקווה המהירה הפליגה פעם\n"
	.string "לקאנטו בימי שני ושישי.\p"
	.string "אבל עכשיו היא מפליגה\n"
	.string "כמעט כל הזמן!$"

OlivineCity_PortOutside_Text_Fisherman2:
	.string "אה, כן, דג לי פה בנחת.$"
