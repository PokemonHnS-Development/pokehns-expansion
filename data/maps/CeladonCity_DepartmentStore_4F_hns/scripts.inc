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
	.string "Vengo a comprar CARTAS SURF para\n"
	.string "enviárselas a mi novia.\p"
	.string "Espera, ¿ya no quedan?$"

CeladonDeptStore4F_Text_Youngster:
	.string "Este es el único lugar donde\n"
	.string "puedes comprar CARTAS AMOR.\p"
	.string "Al menos lo era. Dicen que\n"
	.string "se han agotado.$"

CeladonDeptStore4F_Text_Directory:
	.string "¡Exprésate con regalos!\p"
	.string "4F: REGALOS WISEMAN$"
