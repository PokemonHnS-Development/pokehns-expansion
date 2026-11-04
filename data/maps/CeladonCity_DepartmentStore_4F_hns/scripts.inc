CeladonCity_DepartmentStore_4F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept_EventScript_Supernerd::
	msgbox CeladonDeptStore4F_Text_SuperNerd, MSGBOX_NPC
	end
CeladonDept_EventScript_Youngster::
	msgbox CeladonDeptStore4F_Text_Youngster, MSGBOX_NPC
	end
CeladonDept_EventScript_Directory::
	msgbox CeladonDeptStore4F_Text_Directory, MSGBOX_NPC
	end

CeladonDeptStore4F_Text_SuperNerd:
	.string "באתי לקנות דואר גלישה כדי לשלוח\n"
	.string "לחברה שלי.\p"
	.string "רגע, נגמר להם המלאי?$"

CeladonDeptStore4F_Text_Youngster:
	.string "זה המקום היחיד שבו אפשר\n"
	.string "לקנות דואר מקסים.\p"
	.string "לפחות עד עכשיו. אומרים\n"
	.string "שנגמר להם המלאי.$"

CeladonDeptStore4F_Text_Directory:
	.string "הביעו את עצמכם במתנות!\p"
	.string "ק4: מתנות החכם$"
