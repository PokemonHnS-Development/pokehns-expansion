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
	.string "Hace poco me hice entrenador.\p"
	.string "Mi hijo me animó a hacerlo.\p"
	.string "Me impresiona la selección de\n"
	.string "objetos tan útiles.$"

CeladonDeptStore2F_Text_Youngster:
	.string "A mi papá le cuesta mucho\n"
	.string "aprender los nombres de los objetos\l"
	.string "y cómo se deben usar…$"

CeladonDeptStore2F_Text_Directory:
	.string "¡Objetos top para entrenadores!\p"
	.string "2F: MERCADO DE ENTRENADORES$"

