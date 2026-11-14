CianwoodHouse1_hns_MapScripts::
	.byte 0

CianwoodHouse1_EventScript_Hermit::
	lock
	faceplayer
	msgbox CianwoodCity_Text_OldManIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_LUGIA_OR_HOOH, 2, CianwoodHouse1_EventScript_HermitHooh
	checkitem ITEM_TIDAL_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitTidalBell
	msgbox CianwoodCity_Text_WhirlIslandsStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitTidalBell::
	msgbox CianwoodCity_Text_TidalBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitHooh::
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitClearBell
	msgbox CianwoodCity_Text_BellTowerStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitClearBell::
	msgbox CianwoodCity_Text_ClearBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_OldManIntro:
	.string "אני לא זוכרת מתי מישהו\n"
	.string "בא לבקר אותי בפעם האחרונה.\p"
	.string "כשהייתי צעירה, גם אני הייתי\n"
	.string "מאמנת פוקימונים.\p"
	.string "ניסיתי להגיע אל המגדל\n"
	.string "ולצלול לתוך האוקיינוס.\p"
	.string "השקעתי הרבה מאמץ\n"
	.string "במגוון דברים.\p"
	.string "טוב, היום אני לוקחת הכול בקלות\n"
	.string "ומקשיבה לגלים ולרוח על החוף.$"

CianwoodCity_Text_BellTowerStory:
	.string "שמעת על מגדל הבדיל\n"
	.string "באקרוטיק?\p"
	.string "בראש המגדל יש מה שנקרא\n"
	.string "פעמונים צלולים.\p"
	.string "הם לא משמיעים אף צליל,\n"
	.string "גם ברוחות חזקות.\p"
	.string "יש רק דרך אחת לגרום להם\n"
	.string "לצלצל.\p"
	.string "צריך להשיג עוד פעמון צלול,\n"
	.string "בדיוק כמו אלה שבראש המגדל.\p"
	.string "חיפשתי אותו כשהייתי צעירה.\n"
	.string "אבל אף פעם לא השגתי אחד…$"

CianwoodCity_Text_WhirlIslandsStory:
	.string "שמעת על איי המערבולת?\p"
	.string "בבריכה שלמרגלות המפל שם\n"
	.string "יש מה שנקרא פעמוני גאות.\p"
	.string "הם לא משמיעים אף צליל,\n"
	.string "גם כשהגלים מתנפצים.\p"
	.string "יש רק דרך אחת לגרום להם\n"
	.string "לצלצל.\p"
	.string "צריך להשיג עוד פעמון גאות,\n"
	.string "בדיוק כמו אלה שלמרגלות המפל.\p"
	.string "חיפשתי אותו כשהייתי צעירה.\n"
	.string "אבל אף פעם לא השגתי אחד…$"

CianwoodCity_Text_ClearBellReaction:
	.string "הו! הצלחת להשיג\n"
	.string "פעמון צלול?\p"
	.string "החלום הישן שלי…\n"
	.string "אני מבינה…\p"
	.string "הצלחת…\n"
	.string "… …אני שומעת את זה!\p"
	.string "צלצול הפעמונים ברוח, שמגיע\n"
	.string "מכיוון מגדל הבדיל…$"

CianwoodCity_Text_TidalBellReaction:
	.string "הו! הצלחת להשיג\n"
	.string "פעמון גאות?\p"
	.string "החלום הישן שלי…\n"
	.string "אני מבינה…\p"
	.string "הצלחת…\n"
	.string "… …אני שומעת את זה!\p"
	.string "צלצול הפעמונים ברוח הים,\n"
	.string "שמגיע מכיוון איי המערבולת…$"
