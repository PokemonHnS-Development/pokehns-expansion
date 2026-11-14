MtMortar_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMortar_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

MtMortar_B1F_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end

MtMortar_B1F_EventScript_Item_Carbos::
    finditem ITEM_CARBOS
    end

MtMortar_B1F_EventScript_Item_PPUp::
    finditem ITEM_PP_UP
    end

MtMortar_B1F_EventScript_Item_MaxEther::
    finditem ITEM_MAX_ETHER
    end

MtMortar_B1F_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

MountMortar4_EventScript_Kiyo::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TYROGUE, MountMortar4_EventScript_KiyoAfter
	goto_if_set FLAG_BEAT_KIYO, MountMortar4_EventScript_KiyoTryGiveTyrogue
	msgbox MountMortar4_Text_KiyoIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KIYO_HNS, MountMortar4_Text_KiyoWin
	setflag FLAG_BEAT_KIYO
MountMortar4_EventScript_KiyoTryGiveTyrogue::
	msgbox MountMortar4_Text_KiyoTyrogueReward, MSGBOX_DEFAULT
	@HnS gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYROGUE
	bufferspeciesname STR_VAR_1, SPECIES_TYROGUE
	givemon SPECIES_TYROGUE, 25
	call Common_EventScript_GiftMon
	setflag FLAG_GOT_TYROGUE
MountMortar4_EventScript_KiyoAfter::
	msgbox MountMortar4_Text_KiyoGotTyrogue, MSGBOX_DEFAULT
	closemessage
	release
	end


MountMortar4_Text_KiyoIntro:
	.string "היי!\p"
	.string "אני מלך הקראטה!\n"
	.string "אני מתאמן כאן לבד בחושך!\p"
	.string "אתה! תילחם איתי!\n"
	.string "הוואאארגה!$"

MountMortar4_Text_KiyoWin:
	.string "וואאאארגה!\n"
	.string "הובסתי!$"

MountMortar4_Text_KiyoTyrogueReward:
	.string "אני… אני הרוס…\p"
	.string "האימונים שלי עדיין לא מספיקים…\p"
	.string "אבל הפסד זה הפסד.\n"
	.string "אני מודה בזה.\p"
	.string "כהוכחה לכך שניצחת אותי,\n"
	.string "אתן לך פוקימון נדיר מסוג קרב.$"

MountMortar4_Text_ReceiveTyrogue:
	.string "{PLAYER} received TYROGUE.$"

MountMortar4_Text_KiyoGotTyrogue:
	.string "טיירוג הוא מסוג קרב.\p"
	.string "הוא מתפתח לפוקימון\n"
	.string "קשוח יותר.\p"
	.string "תמשיך לעבוד קשה.\n"
	.string "גם אני אמשיך להתאמן.\p"
	.string "להתראות!$"

MountMortar4_Text_KiyoFullParty:
	.string "You have no room in your party!$"
