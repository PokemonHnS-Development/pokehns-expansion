CeladonCity_DepartmentStore_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept2_EventScript_Pokefan::
	msgbox CeladonDeptStore2F_Text_PokefanM, MSGBOX_NPC
	end

CeladonDept2_EventScript_Youngster::
	msgbox CeladonDeptStore2F_Text_Youngster, MSGBOX_NPC
	end

CeladonDept2_EventScript_Directory::
	msgbox CeladonDeptStore2F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore2F_Text_PokefanM:
	.string "רק לאחרונה הפכתי למאמן.\p"
	.string "הבן שלי עודד אותי לעשות את זה.\p"
	.string "אני מתרשם מהמבחר של\n"
	.string "פריטים שימושיים.$"

CeladonDeptStore2F_Text_Youngster:
	.string "לאבא שלי קשה ללמוד את השמות\n"
	.string "של הפריטים ואיך משתמשים בהם…$"

CeladonDeptStore2F_Text_Directory:
	.string "פריטים מעולים למאמנים!\p"
	.string "ק2: שוק המאמנים$"

