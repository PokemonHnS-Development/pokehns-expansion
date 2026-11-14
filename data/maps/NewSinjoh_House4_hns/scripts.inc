NewSinjoh_House4_hns_MapScripts::
	.byte 0

NewSinjoh_Cafe_Script_Sister::
	lock
	faceplayer
	message NewSinjoh_Cafe_Text_ResturantGreeting
	waitmessage
	pokemart NewSinjoh_Cafe_Pokemart_Resturant
	msgbox NewSinjoh_Cafe_Text_ResturantEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Cafe_Pokemart_Resturant:
	.2byte ITEM_YACHE_BERRY
    .2byte ITEM_LANSAT_BERRY
    .2byte ITEM_ROWAP_BERRY
    .2byte ITEM_BERRY_JUICE
	.2byte ITEM_SODA_POP
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_LEEK
	.2byte ITEM_BIG_ROOT
	.2byte ITEM_NONE
	release
	end

NewSinjoh_Cafe_Text_ResturantGreeting:
	.string "ש-שלום! ברוכים הבאים לבית הקפה שלנו!\n"
	.string "איך אפשר לעזור לך היום?$"

NewSinjoh_Cafe_Text_ResturantEnd:
	.string "נשמח לראות אותך שוב!$"

NewSinjoh_Cafe_EventScript_BaldingMan::
	msgbox NewSinjoh_Cafe_Text_BaldingMan, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_BaldingMan:
	.string "משפחה מקומית מנהלת את בית הקפה\n"
	.string "הזה מאז ומעולם, עד כמה שזוכרים.\p"
	.string "הבת הצעירה שלהם, שם, לא רגילה\n"
	.string "לשרת כל כך הרבה זרים.$"

NewSinjoh_Cafe_EventScript_ScientistF::
	msgbox NewSinjoh_Cafe_Text_ScientistF, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_ScientistF:
	.string "המשקה הזה כל כך טו--וב!\n"
	.string ".......\p"
	.string ".......\p"
	.string "חה-חה-חה\p"
	.string ".......$"

NewSinjoh_Cafe_EventScript_ScientistM::
	lock
	faceplayer
	msgbox NewSinjoh_Cafe_Text_ScientistM, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_Cafe_Text_ScientistM:
	.string "בבקשה, סלח לעמיתה שלי…\p"
	.string "המשקאות כאן חזקים יותר ממה\n"
	.string "שאנחנו רגילים אליו בהואן.\p"
	.string "ניסיתי להזהיר אותה, אבל היא\n"
	.string "אמרה שהיא צריכה להשתחרר קצת.\p"
	.string "משלחת המחקר הזאת הייתה\n"
	.string "קשה לכולנו.$"

NewSinjoh_Cafe_EventScript_Gentleman::
	msgbox NewSinjoh_Cafe_Text_Gentleman, MSGBOX_NPC
	end

NewSinjoh_Cafe_Text_Gentleman:
	.string "על מה אתה בוהה, ילד?\p"
	.string "אין שום בעיה שגבר והפוקימון\n"
	.string "שלו אוכלים ליד אותו שולחן.$"

NewSinjoh_EventScript_Scyther::
	lock
	faceplayer
	playmoncry SPECIES_SCYTHER, 0
	msgbox NewSinjoh_Text_Scyther, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Text_Scyther:
	.string "סייייי!$"
