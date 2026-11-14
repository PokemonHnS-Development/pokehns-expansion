NewSinjoh_House1_hns_MapScripts::
	.byte 0


NewSinjoh__House1_EventScripts_Elizabeth::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER, NewSinjoh_House1_EventScript_Elizabeth_AfterGift
    msgbox NewSinjoh_House1_Text_Looking4Celebi MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House1_EventScript_Decline
    checkspecies SPECIES_CELEBI
    goto_if_eq VAR_RESULT, TRUE, NewSinjoh_House1_EventScript_GiveWooperPaldea
	msgbox NewSinjoh_House1_Text_NicePokemonButNotCelebi, MSGBOX_DEFAULT
    release
    end

NewSinjoh_House1_EventScript_Decline::
	msgbox NewSinjoh_House1_Text_Decline, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_House1_EventScript_GiveWooperPaldea::
	playse SE_PIN
    applymovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH
    msgbox NewSinjoh_House1_OffersWooper MSGBOX_DEFAULT
    setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_WOOPER_PALDEA
    bufferspeciesname STR_VAR_1, SPECIES_WOOPER_PALDEA
    givemon SPECIES_WOOPER_PALDEA, 5
	call Common_EventScript_GiftMon
	setflag FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER
	closemessage
    release
    end

NewSinjoh_House1_Text_Looking4Celebi:
    .string "היי, מאמן!\p"
    .string "באת כל הדרך מהעיירה\n"
    .string "ניו בארק?\p"
    .string "יש לי בקשה למישהו\n"
    .string "שטייל הרבה כמוך.\p"
    .string "אתה מבין, הפוקימון שאני הכי אוהבת\n"
    .string "בעולם הוא במקרה הפוקימון המיתי סלבי.\p"
    .string "אם במקרה יש לך אחד, תוכל\n"
    .string "להראות לי אותו?$"

NewSinjoh_House1_Text_NicePokemonButNotCelebi:
    .string "יש לך פוקימון נפלא מאוד, אבל\n"
    .string "זה לא בדיוק מה שחיפשתי…$"

NewSinjoh_House1_OffersWooper:
    .string "זה הוא! זה סלבי אמיתי וחי!!\p"
    .string "תודה רבה שהבאת אותו\n"
    .string "כל הדרך צפונה כדי שאראה אותו.\p"
    .string "הנה, בת הזוג שלי תפסה במקרה\n"
    .string "יותר מדי כאלה בטיול שלה לאזור רחוק…\p"
    .string "בבקשה, קח את הוופר המיוחד הזה\n"
    .string "כאות תודה, {PLAYER}.$"

NewSinjoh_House1_Text_Decline:
	.string "חבל. ממש רציתי\n"
	.string "לראות אחד.$"

NewSinjoh_House1_Text_TakeCareOfWooper:
    .string "Take good care of that WOOPER\n"
	.string "for me okay?$"

NewSinjoh_House1_EventScript_Elizabeth_AfterGift::
	msgbox NewSinjoh_House1_Text_GoodToSeeYouAgain MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Text_GoodToSeeYouAgain:
    .string "טוב לראות אותך שוב,\n"
    .string "{PLAYER}.\p"
    .string "איך אתה מטפל\n"
    .string "בוופר ההוא?$"

NewSinjoh_House1_Bookshelf::
    lock
	msgbox NewSinjoh_House1_Bookshelf_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Bookshelf_Text:
    .string "זה מדף עמוס במשחקי מחשב\n"
    .string "ורומנים גרפיים!$"

NewSinjoh_House1_Eevee::
    lock
	faceplayer
	playmoncry SPECIES_EEVEE, 0
	msgbox NewSinjoh_House1_Text_Eevee_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_House1_Text_Eevee_Cry:
    .string "וי וי?$"
