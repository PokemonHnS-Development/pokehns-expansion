Gate_IlexForest_Route34_hns_MapScripts::
	.byte 0

Route34IlexForestGate_EventScript_Lass::
	lock
	faceplayer
	msgbox Route34IlexForestGate_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34IlexForestGate_EventScript_Butterfree::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BUTTERFREE, CRY_MODE_NORMAL
	msgbox Route34IlexForestGate_Text_Butterfree, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34IlexForestGate_Text_Lass:
	.string "ראית את המקדש\n"
	.string "לכבוד מגן היער?\p"
	.string "הוא שומר על היער\n"
	.string "מעבר לגבולות הזמן.\p"
	.string "אני חושבת שהוא בטח\n"
	.string "פוקימון מסוג עשב.$"

Route34IlexForestGate_Text_Butterfree:
	.string "בטרפרי: פרייה!$"
