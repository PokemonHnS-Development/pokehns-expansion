FuchsiaCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_EventScript_CityEnter
	.byte 0

FuchsiaCity_EventScript_CityEnter::
	setflag FLAG_VISITED_FUCHSIA_CITY
	end

FuchsiaCity_EventScript_BaobaCall::
	lock
	setspeaker FuchsiaCity_Text_BaobaName
	pokenavcall FuchsiaCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_BAOBA_QUEST_STATE, 1
	setvar VAR_FUCHSIA_CITY_STATE, 1
	release
	end

FuchsiaCity_Text_BaobaName:
	.string "באובה$"

FuchsiaCity_Text_Baoba:
	.string "הפקח באובה: {PLAYER}!\p"
	.string "כאן הפקח באובה.\p"
	.string "קרה משהו נורא!\p"
	.string "אזור הספארי הישן שלי בעיר פושיה\n"
	.string "נקנה ונפתח מחדש!\p"
	.string "וכנראה שיש בו פוקימונים\n"
	.string "אקזוטיים חדשים!\p"
	.string "זה פוגע לי בעסק!\p"
	.string "{PLAYER}, אתה חייב לתפוס פוקימון\n"
	.string "באזור הספארי החדש ולהראות לי.\p"
	.string "אני חייב לדעת על הפוקימונים\n"
	.string "ה”אקזוטיים” האלה.\p"
	.string "בבקשה, {PLAYER}, העסק שלי תלוי בך!$"

FuchsiaCity_EventScript_Dratini::
	lock
	showmonpic SPECIES_DRATINI, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kangaskhan::
	lock
	showmonpic SPECIES_KANGASKHAN, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Cubone::
	lock
	showmonpic SPECIES_CUBONE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Omanyte::
	lock
	showmonpic SPECIES_OMANYTE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kabuto::
	lock
	showmonpic SPECIES_KABUTO, 10, 3
	delay 60
	hidemonpic
	release
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_Youngster, MSGBOX_NPC
	end

FuchsiaCity_EventScript_PokefanM::
	msgbox FuchsiaCity_Text_PokefanM, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Teacher::
	msgbox FuchsiaCity_Text_Teacher, MSGBOX_NPC
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_Sign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	msgbox FuchsiaCity_Text_GymSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZone::
	msgbox FuchsiaCity_Text_SafariZone, MSGBOX_NPC
	end

FuchsiaCity_Text_Youngster:
	.string "אחד מחברי הרביעייה העילית היה\n"
	.string "פעם המנהיג של מכון פושיה.$"

FuchsiaCity_Text_PokefanM:
	.string "כשקוגה הצטרף לרביעייה העילית,\n"
	.string "הבת שלו ירשה את מקומו כמנהיגת המכון.$"

FuchsiaCity_Text_Teacher:
	.string "אזור הספארי עבר לניהול חדש.\p"
	.string "ויש בו המון פוקימונים חדשים!$"

FuchsiaCity_Text_Sign:
	.string "העיר פושיה\p"
	.string "הביטו! זהו ורוד התשוקה!$"

FuchsiaCity_Text_GymSign:
	.string "מכון הפוקימון של העיר פושיה\n"
	.string "מנהיגה: ג'אנין\p"
	.string "מאסטרית הנינג'ה הרעילה$"

FuchsiaCity_Text_SafariZoneOfficeSign:
	.string "There's a notice here…\p"
	.string "SAFARI ZONE OFFICE is closed until\n"
	.string "further notice.$"

FuchsiaCity_Text_SafariZone:
	.string "אזור הספארי\n"
	.string "כעת בבעלות חברת דבון$"

FuchsiaCity_Text_SafariZoneClosedSign:
	.string "The WARDEN is traveling abroad.\p"
	.string "Therefore, the SAFARI ZONE is\n"
	.string "closed.$"

FuchsiaCity_Text_NoLitteringSign:
	.string "No littering.\p"
	.string "Please take your waste with you.$"

