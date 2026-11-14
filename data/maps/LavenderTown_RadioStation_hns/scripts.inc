LavenderTown_RadioStation_hns_MapScripts::
	.byte 0

LavenderTown_RadioStation_EventScript_Officer::
	msgbox LavenderTown_RadioStation_Text_Officer, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Receptionist::
	msgbox LavenderTown_RadioStation_Text_Receptionist, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_SuperNerd::
	msgbox LavenderTown_RadioStation_Text_SuperNerd1, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Director::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_DirectorGotRadio
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart
	msgbox LavenderTown_RadioStation_Text_Gentleman, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart::
	msgbox LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox LavendertownRadioStation_Text_Upgraded_Radio, MSGBOX_DEFAULT
	waitfanfare
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_KANTO_RADIO_GOT
	release
	end
LavenderTown_RadioStation_EventScript_DirectorGotRadio::	
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Host::
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_Host2
	msgbox LavenderTown_RadioStation_Text_SuperNerd2, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_Host2::
	msgbox LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Directory::
	msgbox LavenderTown_RadioStation_Text_Directory, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Sign::
	msgbox LavenderTown_RadioStation_Text_PokeFluteSign, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Library::
	msgbox LavenderTown_RadioStation_Text_ReferenceLibrary, MSGBOX_SIGN
	end

LavenderTown_RadioStation_Text_Receptionist:
	.string "ברוכים הבאים! אפשר להסתובב\n"
	.string "בחופשיות בכל הקומה הזאת.$"

LavenderTown_RadioStation_Text_Officer:
	.string "מצטער, אבל מותר לסייר רק\n"
	.string "בקומת הקרקע.\p"
	.string "מאז שכנופיית פושעים השתלטה על\n"
	.string "מגדל הרדיו בג'וטו, הגברנו את האבטחה.$"

LavenderTown_RadioStation_Text_SuperNerd1:
	.string "הרבה אנשים עובדים קשה כאן\n"
	.string "במגדל הרדיו.\p"
	.string "הם בטח עושים כמיטב יכולתם\n"
	.string "כדי להפיק תוכניות טובות.$"

LavenderTown_RadioStation_Text_Gentleman:
	.string "אוי, לא, לא, לא!\p"
	.string "אנחנו לא משדרים מאז\n"
	.string "שמפעל החשמל הושבת.\p"
	.string "אם לא אוכל לשדר, כל המאמצים\n"
	.string "שלי להקים את התחנה ירדו לטמיון.\p"
	.string "אני אפשוט רגל!$"

LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart:
	.string "אה! אז אתה {PLAYER}, זה שפתר\n"
	.string "את הבעיה של מפעל החשמל?\p"
	.string "בזכותך לא איבדתי את העבודה שלי.\p"
	.string "אני אומר לך, הצלת אותי!\p"
	.string "בבקשה, זה בשבילך, כאות תודה.$"

LavendertownRadioStation_Text_Upgraded_Radio:
	.string "{PLAYER} קיבל את\n"
	.string "שדרוג הרדיו!$"

LavenderTown_RadioStation_Text_Gentleman_GotExpnCard:
	.string "עם הדבר הזה אפשר לקלוט את\n"
	.string "תוכניות הרדיו כאן בקאנטו.\p"
	.string "גאהאהאהאהא!$"

LavenderTown_RadioStation_Text_SuperNerd2:
	.string "היי, שלום!\p"
	.string "אני מנהל המוזיקה המופלא!\p"
	.string "הא? הרדיו שלך לא יכול לקלוט את\n"
	.string "תוכניות המוזיקה שלי. כמה חבל!\p"
	.string "עם שדרוג כרטיס הרחבה תוכל לקלוט\n"
	.string "אותן. כדאי לך להשיג אחד!$"

LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard:
	.string "היי, שלום!\p"
	.string "אני מנהל המוזיקה המופלא!\p"
	.string "אני אחראי למנגינות המהממות\n"
	.string "שעולות לשידור.\p"
	.string "אל תהיה מרובע. תקלוט את\n"
	.string "המוזיקה שלך ישר מהאוויר!$"

LavenderTown_RadioStation_Text_Directory:
	.string "קומה 1: קבלה\n"
	.string "קומה 2: מכירות\p"
	.string "קומה 3: משאבי אנוש\n"
	.string "קומה 4: הפקה\p"
	.string "קומה 5: לשכת מנהל התחנה$"

LavenderTown_RadioStation_Text_PokeFluteSign:
	.string "המריצו את הפוקימונים בצלילים הרכים\n"
	.string "של חליל הפוקימון בערוץ 20$"

LavenderTown_RadioStation_Text_ReferenceLibrary:
	.string "וואו! מדף מלא בדיסקים\n"
	.string "ובסרטונים של פוקימונים.\p"
	.string "זו בטח ספריית העיון.$"

