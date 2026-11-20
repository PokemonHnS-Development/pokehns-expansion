OlivineCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_OnFrame
	.byte 0

OlivineCity_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

OlivineCity_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

OlivineCity_OnFrame::
	map_script_2 VAR_SAFARI_ZONE_GATE_STATE, 1, OlivineCity_EventScript_BaobaCall
	map_script_2 VAR_TRIGGER_ELM_ROCKET_CALL, 1, Mahoganytown_EventScript_RocketTrigger
	.2byte 0

OlivineCity_EventScript_BaobaCall::
	lock
	setspeaker OlivineCity_Text_BaobaName
	pokenavcall OlivineCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_SAFARI_ZONE_GATE_STATE, 2
	release
	end

OlivineCity_Text_BaobaName:
	.string "באובה$"

OlivineCity_Text_Baoba:
	.string "{PLAYER}!\p"
	.string "כאן הפקח באובה.\p"
	.string "סליחה שגרמתי לך לחכות.\n"
	.string "סוף סוף פתחנו את אזור הספארי!\p"
	.string "אתה יודע איפה הוא נמצא?\p"
	.string "אתה מכיר את השער שבתוך המערה\n"
	.string "בעיר סיאנווד?\p"
	.string "אם תעבור דרכו ותלך עוד קצת,\n"
	.string "בקרוב תראה את אזור הספארי!\p"
	.string "אנחנו קצת מרוחקים, אבל\n"
	.string "בבקשה, בוא לבקר!$"

OlivineCity_EventScript_CityTrigger:: @FLAGHEAP
	setflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
	setflag FLAG_HIDE_OLIVINE_SILVER
	setflag FLAG_VISITED_OLIVINE_CITY
	clearflag FLAG_SAFARI_ZONE_WEST_EXPANSION
	clearflag FLAG_SAFARI_ZONE_EAST_EXPANSION
	clearflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	clearflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	setvar VAR_GETFLY, 0
	
	setvar VAR_OLIVINE_CITY_STATE, 1

	@cianwood flags
	setvar VAR_SUICUNE_ENCOUNTERS, 1
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setvar VAR_CIANWOOD_CITY_STATE, 1
	end

OlivineCity_EventScript_SilverTrigger::
	lock
	clearflag FLAG_HIDE_OLIVINE_SILVER
	opendoor 11, 27
	addobject LOCALID_OLIVINE_SILVER
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	delay 20 
	closedoor 11, 27
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverWalkToPlayer1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverWalkToPlayer2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverWalkToPlayer3
	msgbox OlivineCity_Text_SilverEncounter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverLeaveAdjust1
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverLeaveAdjust2
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverLeaveAdjust2
	applymovement LOCALID_OLIVINE_SILVER, OlivineCity_Movement_SilverLeave
	waitmovement 0
	setvar VAR_OLIVINE_CITY_STATE, 2
	setflag FLAG_HIDE_OLIVINE_SILVER
	removeobject LOCALID_OLIVINE_SILVER
	fadedefaultbgm
	release
	end

OlivineCity_EventScript_SilverWalkToPlayer1::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer1
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer2::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer2
	waitmovement 0
	return

OlivineCity_EventScript_SilverWalkToPlayer3::
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer3
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust1::
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkDown1
	waitmovement 0
	return

OlivineCity_EventScript_SilverLeaveAdjust2::
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkUp1
	waitmovement 0
	return

OlivineCity_Movement_SilverWalkToPlayer1:
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
OlivineCity_Movement_SilverWalkToPlayer2:
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
OlivineCity_Movement_SilverWalkToPlayer3:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end


OlivineCity_Movement_SilverLeave:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OlivineCity_Text_SilverEncounter:
	.string "שוב אתה?\n"
	.string "אין צורך להיות דרוך.\p"
	.string "אני לא מתעסק עם רכרוכיים\n"
	.string "כמוך.\p"
	.string "ואם כבר מדברים על חלשים,\n"
	.string "מנהיגת המכון של העיר לא כאן.\p"
	.string "כביכול היא מטפלת בפוקימון\n"
	.string "חולה במגדלור.\p"
	.string "המף! אוי, כמה עצוב!\n"
	.string "פשוט לוותר על פוקימונים חולים!\p"
	.string "פוקימון שלא יכול להילחם\n"
	.string "הוא חסר ערך!\p"
	.string "למה שלא תלך להתאמן\n"
	.string "במגדלור?\p"
	.string "מי יודע? אולי זה יהפוך אותך\n"
	.string "למאמן קצת יותר טוב!$"

OlivineCity_EventScript_Sailor1::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Sailor2::
	lock
	faceplayer
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
	waitmoncry
	release
	end

OlivineCity_EventScript_Sign::
	lock
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
	end

OlivineCity_EventScript_PortSign::
	lock
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_CafeSign::
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_GymSign::
	lock
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_LighthouseSign::
	lock
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
	end

OlivineCity_EventScript_Item_ChargeBeam::
	finditem ITEM_TM_CHARGE_BEAM
	end

OlivineCity_EventScript_EonTicketWoman::
	lock
	faceplayer
	checkitem ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
	goto_if_set FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanChamp::
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
	giveitem ITEM_AURORA_TICKET
	closemessage
	release
	end

OlivineCity_EventScript_EonTicketWomanAfter::
	msgbox OlivineCity_Text_EonTicketWoman3, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_CafeSign:
	.string "קפה אוליבין\p"
	.string "כאן מלחים חזקים נהנים\n"
	.string "מארוחות כוח דשנות$"

OlivineCity_Text_EonTicketWoman1:
	.string "קוראים לי מרי!\p"
	.string "סתם צוחקת, אבל אני מתה על\n"
	.string "תוכנית הרדיו של מרי!$"

OlivineCity_Text_EonTicketWoman2:
	.string "אתה בטח {PLAYER}!!!\p"
	.string "אני לא מאמינה! האלוף!\p"
	.string "שמעתי עליך בתוכנית הרדיו\n"
	.string "של מרי!\p"
	.string "הנה, זה בשבילך!$"

OlivineCity_Text_EonTicketWoman3:
	.string "אני לא מאמינה שפגשתי\n"
	.string "את האלוף!!!$"

OlivineCity_Text_Sailor1:
	.string "דרכים חשוכות מסוכנות\n"
	.string "בלילה.\p"
	.string "אבל בחושך המוחלט של הלילה,\n"
	.string "הים בוגדני עוד יותר!\p"
	.string "בלי אור המגדלור שינחה את הדרך,\n"
	.string "אף ספינה לא יכולה להפליג.$"

OlivineCity_Text_YoungsterPokegear:
	.string "הדבר הזה שיש לך… זה פוקיגיר, נכון?\n"
	.string "וואו, זה מגניב.$"

OlivineCity_Text_YoungsterPokedex:
	.string "Wow, you have a POKéDEX!\p"
	.string "That is just so awesome.$"

OlivineCity_Text_Sailor2:
	.string "הליגה מדרגת את ג'סמין\n"
	.string "כמנהיגה השישית בחוזקה!\p"
	.string "הה! איזה שטויות.\p"
	.string "אין סיכוי שפרייס יוכל לפגוע\n"
	.string "בפוקימונים מסוג פלדה של ג'סמין!\p"
	.string "בירוקרטיה, אם תשאל אותי.\p"
	.string "ממנה באמת צריך לפחד,\n"
	.string "זה בטוח!$"

OlivineCity_Text_Sign:
	.string "העיר אוליבין\p"
	.string "הנמל הקרוב ביותר לארצות זרות$"

OlivineCity_Text_PortSign:
	.string "נמל אוליבין\n"
	.string "רציף הספינה המהירה$"

OlivineCity_Text_GymSign:
	.string "מכון הפוקימון של העיר אוליבין\n"
	.string "מנהיגה: ג'סמין\p"
	.string "הנערה בשריון הפלדה$"

OlivineCity_Text_LighthouseSign:
	.string "מגדלור אוליבין\n"
	.string "הידוע גם בשם המגדלור המנצנץ$"

OlivineCity_Text_BattleTowerSign:
	.string "TRAINER HILL and\n"
	.string "BATTLE TENTS AHEAD.\p"
	.string "Opening Now!$"

OlivineCity_Text_Machoke:
	.string "מאצ'וק: צ'ו!$"
