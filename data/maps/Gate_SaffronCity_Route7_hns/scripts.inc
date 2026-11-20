Gate_SaffronCity_Route7_hns_MapScripts::
	.byte 0

Gate_SaffronCity_Route7_EventScript_Guard::
	goto_if_set FLAG_RETURNED_MACHINE_PART, Gate_SaffronCity_Route7_EventScript_GuardReturnedPart
	msgbox Route7_Text_SaffronGuard_PowerPlant, MSGBOX_NPC
	end

Gate_SaffronCity_Route7_EventScript_GuardReturnedPart::
	msgbox Route7_Text_SaffronGuard_Serious, MSGBOX_NPC
	end

Route7_Text_SaffronGuard_PowerPlant:
	.string "שמעת על התאונה\n"
	.string "במפעל החשמל?\p"
	.string "הוא נמצא במזרח, קרוב\n"
	.string "לעיירה לבנדר.$"

Route7_Text_SaffronGuard_Serious:
	.string "אני לוקח את עבודת השמירה\n"
	.string "שלי ברצינות.\p"
	.string "היי! יש לך פוקדקס.\p"
	.string "בסדר. אפשר לעבור.$"
