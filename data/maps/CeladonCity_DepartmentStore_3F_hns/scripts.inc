CeladonCity_DepartmentStore_3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept3_EventScript_Youngster::
	msgbox CeladonDeptStore3F_Text_Youngster, MSGBOX_NPC
	end
CeladonDept3_EventScript_Gbakid1::
	msgbox CeladonDeptStore3F_Text_GameboyKid1, MSGBOX_NPC
	end
CeladonDept3_EventScript_Gbakid2::
	msgbox CeladonDeptStore3F_Text_GameboyKid2, MSGBOX_NPC
	end
CeladonDept3_EventScript_SuperNerd::
	msgbox CeladonDeptStore3F_Text_SuperNerd, MSGBOX_NPC
	end
CeladonDept3_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart CeladonDept3_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
CeladonDept3_Pokemart:
	.2byte ITEM_TM_SAFEGUARD
	.2byte ITEM_TM_CAPTIVATE
	.2byte ITEM_TM_STEALTH_ROCK
	.2byte ITEM_TM_BRINE
	.2byte ITEM_TM_AVALANCHE
	.2byte ITEM_TM_DARK_PULSE
	.2byte ITEM_TM_GYRO_BALL
	.2byte ITEM_TM_DREAM_EATER
	.2byte ITEM_TM_GIGA_IMPACT
	.2byte ITEM_TM_ENDURE
	pokemartlistend

CeladonDept3_EventScript_Directory::
	msgbox CeladonDeptStore3F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore3F_Text_Youngster:
	.string "אני לא מצליח להחליט על איזה\n"
	.string "פוקימון להשתמש במ”מ הזה…$"

CeladonDeptStore3F_Text_GameboyKid1:
	.string "אוי לא! החלפתי את הפוקימון שלי\n"
	.string "בלי להוריד ממנו את השדרוג.$"

CeladonDeptStore3F_Text_GameboyKid2:
	.string "יש! סוף סוף אני מקבל\n"
	.string "פוריגון!\p"
	.string "אני לא טוב במכונות המזל, אז אף פעם\n"
	.string "לא הצלחתי להשיג מספיק מטבעות…\p"
	.string "…מה?\p"
	.string "הפוריגון שהוחלף הפך\n"
	.string "לפוקימון אחר!$"

CeladonDeptStore3F_Text_SuperNerd:
	.string "בחנות המ”מ מוכרים כמה מהלכים נדירים.$"

CeladonDeptStore3F_Text_Directory:
	.string "ק3: חנות המ”מ\p"
	.string "חזקו את הפוקימונים שלכם!$"

