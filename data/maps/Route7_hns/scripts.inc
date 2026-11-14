Route7_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route7_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route7_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route7_EventScript_Sign::
	msgbox Route7_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route7_EventScript_Door::
	msgbox Route7_Text_LockedDoor, MSGBOX_SIGN
	end

Route7_Text_UndergroundPathSign:
	.string "מה זה העלון הזה?\p"
	.string "… מאמנים גסי רוח ערכו\n"
	.string "קרבות במעבר התת-קרקעי.\p"
	.string "עקב תלונות גוברות של תושבי האזור,\n"
	.string "המעבר נסגר עד הודעה חדשה.\p"
	.string "משטרת סלדון$"

Route7_Text_LockedDoor:
	.string "זה נעול…$"

