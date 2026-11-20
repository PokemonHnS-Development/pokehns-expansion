CeladonCity_DepartmentStore_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept1_EventScript_Receptionsit::
    msgbox CeladonDeptStore_Text_1FReceptionist, MSGBOX_NPC
    end

CeladonDept1_EventScript_Gent::
    msgbox CeladonDeptStore_Text_1FGentleman, MSGBOX_NPC
    end

CeladonDept1_EventScript_Teacher::
    msgbox CeladonDeptStore_Text_1FTeacher, MSGBOX_NPC
    end

CeladonDept1_EventScript_Directory::
    msgbox CeladonDeptStore_Text_1FDirectory, MSGBOX_SIGN
    end

CeladonDeptStore_Text_1FReceptionist:
    .string "שלום! ברוכים הבאים\n"
    .string "לכלבו של סלדון!\p"
    .string "לוח הקומות נמצא על הקיר.$"

CeladonDeptStore_Text_1FGentleman:
    .string "הכלבו הזה שייך לאותה רשת\n"
    .string "כמו זה שבעיר גולדנרוד.\p"
    .string "שניהם שופצו באותו זמן.$"

CeladonDeptStore_Text_1FTeacher:
    .string "זו הפעם הראשונה שלי כאן.\p"
    .string "המקום כל כך גדול…\p"
    .string "אני חוששת שאלך לאיבוד.$"

CeladonDeptStore_Text_1FDirectory:
    .string "ק1: דלפק שירות\p"
    .string "ק2: שוק המאמנים\p"
    .string "ק3: חנות המ”מ\p"
    .string "ק4: מתנות החכם\p"
    .string "ק5: בית מרקחת\p"
    .string "ק6: כיכר הגג$"
