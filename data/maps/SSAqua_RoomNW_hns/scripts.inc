SSAqua_RoomNW_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, SSAqua_RoomNW_OnTransition
	.byte 0

SSAqua_RoomNW_OnTransition::
    goto_if_ge VAR_SSAQUA_STATE, 3, SSAqua_RoomNW_SetTrainerPos
    end

SSAqua_RoomNW_SetTrainerPos::
    setobjectxyperm 2, 2, 6
    setobjectxyperm 3, 4, 3
    end

SSAqua_RoomNW_EventScript_Stanly::
    lock
    faceplayer
    msgbox SSAqua_RoomNW_Text_SailorStanlySeen, MSGBOX_DEFAULT
    trainerbattle_no_intro TRAINER_STANLY_HNS, SSAqua_RoomNW_Text_SailorStanlyBeaten
	msgbox SSAqua_RoomNW_Text_SailorStanlyAfterBattle, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    delay 60
    playse SE_DOOR
    removeobject LOCALID_SSAQUA_SLEEPYSAILOR
    fadescreenswapbuffers FADE_FROM_BLACK
    setvar VAR_SSAQUA_STATE, 3
	end

SSAqua_RoomNW_EventScript_Edward::
    trainerbattle_single TRAINER_EDWARD_HNS, SSAqua_RoomNW_Text_GentlemanEdwardSeen, SSAqua_RoomNW_Text_GentlemanEdwardBeaten
	msgbox SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNW_EventScript_Corey::
    trainerbattle_single TRAINER_COREY_HNS, SSAqua_RoomNW_Text_BurglarCoreySeen, SSAqua_RoomNW_Text_BurglarCoreyBeaten
	msgbox SSAqua_RoomNW_Text_BurglarCoreyAfterBattle, MSGBOX_AUTOCLOSE
	end


SSAqua_RoomNW_Text_SailorStanlySeen:
	.string "כן, אני מלח, בהחלט.\p"
	.string "לא התבטלתי!\p"
	.string "התא הזה היה פנוי, אז\n"
	.string "רק חטפתי תנומה קצרה!\p"
	.string "אה, לא משנה! קדימה, לקרב!$"

SSAqua_RoomNW_Text_SailorStanlyBeaten:
	.string "סליחה! הכול באשמתי!$"

SSAqua_RoomNW_Text_SailorStanlyAfterBattle:
	.string "בתור מלח, אני חייב לעשות\n"
	.string "עבודה פיזית. זה מתיש!$"

SSAqua_RoomNW_Text_GentlemanEdwardSeen:
	.string "אוי, לא. איבדתי משהו\n"
	.string "חשוב מאוד.$"

SSAqua_RoomNW_Text_GentlemanEdwardBeaten:
	.string "אני… אני לא מוצא את זה…$"

SSAqua_RoomNW_Text_GentlemanEdwardAfterBattle:
	.string "אני מוותר. אין צורך לחפש.\p"
	.string "פשוט תשכח מזה!$"

SSAqua_RoomNW_Text_BurglarCoreySeen:
	.string "יששש! איזה מזל!$"

SSAqua_RoomNW_Text_BurglarCoreyBeaten:
	.string "איזה חוסר מזל! הפסדתי!$"

SSAqua_RoomNW_Text_BurglarCoreyAfterBattle:
	.string "מצאתי פה מטבע יפה.\p"
	.string "מישהו בטח איבד אותו…$"
