Route10_PowerPlantBackRoom_hns_MapScripts::
	.byte 0


Route10_PowerPlantBackRoom_EventScript_Manager::
	lock
	faceplayer
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 0, Route10_PowerPlantBackRoom_EventScript_ManagerInitial
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 1, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 2, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 3, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 6, Route10_PowerPlantBackRoom_EventScript_ManagerCheckPart
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantBackRoom_EventScript_ManagerDone
	msgbox Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerInitial::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerWhoWouldRuinMyGenerator, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KANTO_ROCKET_STORY_STATE, 1
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerIWontForgiveCulprit, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerCheckPart::
	checkitem ITEM_MACHINE_PART
	goto_if_eq VAR_RESULT, FALSE, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	removeitem ITEM_MACHINE_PART
	msgbox Route10_PowerPlantBackRoom_Text_ManagerThatsThePart, MSGBOX_DEFAULT
	msgbox Route10_PowerPlantBackRoom_Text_ManagerTakeThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDER
	msgbox Route10_PowerPlantBackRoom_Text_ManagerTM07IsZapCannon, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KANTO_ROCKET_STORY_STATE, 7
	clearflag FLAG_HIDE_ROUTE25_MISTY
	setvar VAR_CERULEAN_CITY_STATE, 2
	setflag FLAG_HIDE_POWER_PLANT_ENGINEER
	setflag FLAG_RETURNED_MACHINE_PART
	setvar VAR_VERMILION_CITY_SAMSON, 1
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerDone::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_Engineer::
	msgbox Route10_PowerPlantBackRoom_Text_Engineer, MSGBOX_NPC
	end

Route10_PowerPlantBackRoom_Text_ManagerWhoWouldRuinMyGenerator:
	.string "מנהל: אני, אני, אני מוכן לפוצץ\n"
	.string "מישהו!\p"
	.string "מי העז להרוס לי את הגנרטור?\p"
	.string "השקעתי בו כל כך הרבה זמן!\p"
	.string "אם אתפוס אותו, הוא יטעם\n"
	.string "את תותח הזרם שלי!$"

Route10_PowerPlantBackRoom_Text_ManagerIWontForgiveCulprit:
	.string "מנהל: לא אסלח לו!\p"
	.string "האשם יכול לבכות ולהתנצל,\p"
	.string "אבל אני ארסק אותו בכל מקרה!\p"
	.string "גהאהאהאה!$"

Route10_PowerPlantBackRoom_Text_ManagerThatsThePart:
	.string "מנהל: אה! כן!\p"
	.string "זה החלק החסר מהגנרטור\n"
	.string "האהוב שלי! מצאת אותו?$"

Route10_PowerPlantBackRoom_Text_ManagerTakeThisTM:
	.string "וואהאה! תודה!\p"
	.string "הנה! המ”מ הזה הוא הפרס שלך!$"

Route10_PowerPlantBackRoom_Text_ManagerTM07IsZapCannon:
	.string "מנהל: המ”מ הזה מכיל את רעם.\p"
	.string "זה מהלך עוצמתי!\p"
	.string "אף אחד לא יגיד שהוא מדויק,\n"
	.string "אבל הוא מכה בעוצמה אדירה!$"

Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator:
	.string "מנהל: הגנרטור האהוב שלי!\p"
	.string "תמשיך להזרים חשמל!$"

Route10_PowerPlantBackRoom_Text_Engineer:
	.string "הדלת הזו לא בטוחה בלי חשמל.$"

