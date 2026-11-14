SSAqua_RoomSSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSSW_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE_HNS, SSAqua_RoomSSW_Text_FirebreatherLyleSeen, SSAqua_RoomSSW_Text_FirebreatherLyleBeaten
	msgbox SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_EventScript_Ken::
	trainerbattle_single TRAINER_KEN_HNS, SSAqua_RoomSSW_Text_BugCatcherKenSeen, SSAqua_RoomSSW_Text_BugCatcherKenBeaten
	msgbox SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_Text_FirebreatherLyleSeen:
    .string "אני נוסע לקאנטו להעלות\n"
    .string "מופעי יריקת אש!$"

SSAqua_RoomSSW_Text_FirebreatherLyleBeaten:
    .string "פשש… הלהבה קטנטנה…$"

SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle:
    .string "כנראה שאש חלשה על הים.\n"
    .string "זה לא משנה? באמת?$"

SSAqua_RoomSSW_Text_BugCatcherKenSeen:
    .string "אני נוסע לסבתא שלי\n"
    .string "לתפוס קצת חרקים!$"

SSAqua_RoomSSW_Text_BugCatcherKenBeaten:
    .string "אוווו, וואו. אתה קשוח!$"

SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle:
    .string "אפשר למצוא הרבה פוקימונים\n"
    .string "בעצים של ג'וטו!$"
