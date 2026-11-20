NewSinjoh_House2_hns_MapScripts::
	.byte 0


NewSinjoh_House2_EventScripts_DeskLady::
    lock
	msgbox NewSinjoh_House2_DeskLady_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_DeskLady_Text::
    .string "שלום לך, ילד יקר…\p"
    .string "ברוך הבא ל… טוב, אפשר לקרוא לזה\n"
    .string "הספרייה של סינג'ו החדשה.\p"
    .string "בעצם, כאן אנחנו שומרים את כל\n"
    .string "התיעוד של ההיסטוריה של העיירה,\p"
    .string "וגם את כל הספרות שאנחנו\n"
    .string "מייבאים מאזורים אחרים…$"

NewSinjoh_House2_EventScript_Torkoal::
	lock
	faceplayer
	playmoncry SPECIES_TORKOAL, 0
	msgbox NewSinjoh_Hosue2_Text_CryTorkoal, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Hosue2_Text_CryTorkoal:
	.string "טוווור?$"

NewSinjoh_House2_EventScript_BookShelf_North::
    lock
	msgbox NewSinjoh_House2_Text_Bookshelf_North MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_North:
    .string "המדף דחוס בספרים עתיקים\n"
    .string "בכריכות עור.\p"
    .string "השפה לא מוכרת.$"

NewSinjoh_House2_EventScript_BookShelf_South::
    lock
	msgbox NewSinjoh_House2_Text_Bookshelf_South MSGBOX_DEFAULT
	release
	end

NewSinjoh_House2_Text_Bookshelf_South:
    .string "המדף דחוס בספרים\n"
    .string "על פוקימונים.\p"
    .string "הספרים האלה נראים חדשים\n"
    .string "ומוכרים יותר.$"
