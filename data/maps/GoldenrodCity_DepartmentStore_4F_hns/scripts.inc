GoldenrodCity_DepartmentStore_4F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore4_EventScript_Cooltrainer::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FCooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_GBAKid::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FGameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore4_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_4FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_4FCooltrainerM:
    .string "Hola. Amo los POKéMON fuertes.\p"
    .string "Les doy PROTEÍNA para subir\n"
    .string "su ATAQUE.$"

GoldenrodDeptStore_Text_4FBugCatcher:
    .string "El HIERRO sube la\n"
    .string "DEFENSA de tu POKéMON.$"

GoldenrodDeptStore_Text_4FGameboyKid:
    .string "Dicen que algunos POKéMON\n"
    .string "evolucionan solo al ser\l"
    .string "intercambiados por Cable Link\l"
    .string "GBA Game Link.\p"
    .string "Pfft...\p"
    .string "Qué desinformación.\p"
    .string "Conozco algunos de esos\n"
    .string "POKéMON:\l"
    .string "MACHOKE, KADABRA, HAUNTER y,\l"
    .string "este, GRAVELER,\l"
    .string "pero todos evolucionan al\l"
    .string "subir de nivel.$"

GoldenrodDeptStore4_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore4_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore4_Pokemart:
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

GoldenrodDeptStore_Text_4FDirectory:
    .string "¡Potenciemos tus POKéMON!\p"
    .string "CAJA MEDICINAS 4F$"
