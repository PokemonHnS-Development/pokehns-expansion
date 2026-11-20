SaffronCity_CopyCatsHouse_1F_hns_MapScripts::
	.byte 0

SaffronCity_CopyCatsHouse_1F_EventScript_Mom::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_CopyCatsHouse_1F_EventScript_MomAfter
	msgbox CopycatsHouse1F_Text_PokefanF, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_MomAfter::
	msgbox CopycatsHouse1F_Text_PokefanF_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_Dad::
	msgbox CopycatsHouse1F_Text_PokefanM, MSGBOX_NPC
	end

SaffronCity_CopyCatsHouse_1F_EventScript_Blissey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BLISSEY, CRY_MODE_NORMAL
	msgbox CopycatsHouse1F_Text_Blissey, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CopycatsHouse1F_Text_PokefanM:
	.string "הבת שלי אוהבת לחקות אנשים.\p"
	.string "בזכות החיקויים שלה, כולם\n"
	.string "כאן קוראים לה ”חקיינית”.$"

CopycatsHouse1F_Text_PokefanF:
	.string "הבת שלי כל כך מרוכזת בעצמה…\p"
	.string "יש לה רק מעט חברים.$"

CopycatsHouse1F_Text_PokefanF_ReturnedPart:
	.string "היא איבדה לאחרונה את בובת הפוקימון\n"
	.string "שנער אחד נתן לה לפני שלוש שנים.\p"
	.string "מאז היא נעשתה טובה\n"
	.string "עוד יותר בחיקויים…$"

CopycatsHouse1F_Text_Blissey:
	.string "בליסי: בלייייסי!$"
