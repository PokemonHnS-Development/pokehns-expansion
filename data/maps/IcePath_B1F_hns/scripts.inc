IcePath_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePath_B1F_OnTransition
	.byte 0

IcePath_B1F_OnTransition:
	callnative SetTimeBasedEncounters
	end

IcePath_B1F_EventScript_PuzzleSkipButton::
	lock
	msgbox IcePath_B1F_Text_PuzzleSkipButton, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, IcePath_B1F_EventScript_PuzzleSkipButtonNo
	warp MAP_ICE_PATH_B1F_HNS, 15, 12
	release
	end

IcePath_B1F_EventScript_PuzzleSkipButtonNo::
	release
	end

IcePath_B1F_Text_PuzzleSkipButton::
	.string "לדלג על החידה הזאת?$"

IcePath_B1F_EventScript_Item_Iron::
	finditem ITEM_IRON
	end
IcePath_B1F_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

IcePath_B1F_EventScript_Sign::
	msgbox IcePath_B1F_Text_Sign, MSGBOX_SIGN
	end

IcePath_B1F_Text_Sign:
	.string "סכנה! קרח סדוק\n"
	.string "לרכוב מהר על אופניים\p"
	.string "להחליף הילוך בלחיצה על …\n"
	.string "השלט דהוי…$"

