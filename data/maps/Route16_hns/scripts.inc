Route16_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route16_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route16_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route16_EventScript_Sign::
	msgbox Route16_Text_Sign, MSGBOX_SIGN
	end

Route16_Text_Sign:
	.string "שביל האופניים\n"
	.string "ירידה חופשית כל הדרך למטה!$"
