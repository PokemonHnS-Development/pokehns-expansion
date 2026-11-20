CianwoodHouse3_hns_MapScripts::
	.byte 0

CianwoodCity_EventScript_Kirk::
	lock
	faceplayer
	goto_if_eq VAR_SHUCKIE, 1, CianwoodCity_EventScript_KirkGivenShuckie
	goto_if_eq VAR_SHUCKIE, 3, CianwoodCity_EventScript_KirkReturnedShuckie
	msgbox CianwoodCity_Text_ManiacAskShuckle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_KirkDeclined

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SHUCKLE
	bufferspeciesname STR_VAR_1, SPECIES_SHUCKLE
	givenamedmon 2
	call Common_EventScript_GiftMonNamed

	setvar VAR_SHUCKIE, 1
	release
	end

CianwoodCity_EventScript_KirkDeclined::
	msgbox CianwoodCity_Text_ManiacIfHeComesBack, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkGivenShuckie::
	goto_if_set FLAG_BADGE01_GET, CianwoodCity_EventScript_KirkReturnShuckie
	msgbox CianwoodCity_Text_ManiacHowsdoing, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkReturnShuckie::
	msgbox CianwoodCity_Text_ManiacAskReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_KirkDeclineReturnShuckie
	removenamedmon 2
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, CianwoodCity_EventScript_KirkNotRight
	goto_if_eq VAR_RESULT, 3, CianwoodCity_EventScript_KirkKeepShuckie
	playse MUS_OBTAIN_ITEM
	callnative UpdateFollowingPokemon
	msgbox CianwoodCity_Text_ManiacReturnedMon, MSGBOX_DEFAULT
	waitse
	msgbox CianwoodCity_Text_ManiacThankYou, MSGBOX_DEFAULT
	setvar VAR_SHUCKIE, 3
	release
	end

CianwoodCity_EventScript_KirkDeclineReturnShuckie::
	msgbox CianwoodCity_Text_ManiacRobbed2, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkNotRight::
	msgbox CianwoodCity_Text_ManiacRobbed, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkKeepShuckie::
	msgbox CianwoodCity_Text_ManiacShuckleLikesYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SHUCKIE, 3
	release
	end

CianwoodCity_EventScript_KirkReturnedShuckie::
	msgbox CianwoodCity_Text_ManiacHappinessSpeech, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_Text_ManiacAskShuckle:
	.string "אני, אני בהלם!\p"
	.string "בחור בערך בגילך, עם עיניים\n"
	.string "חודרות ושיער ארוך, נכנס לכאן.\p"
	.string "הוא הפחיד אותי עד שנתתי לו\n"
	.string "את הפוקימון היקר שלי!\p"
	.string "נשאר לי עוד אחד,\n"
	.string "אבל מה אם הוא יחזור?\p"
	.string "אתה נראה חזק. תוכל לשמור\n"
	.string "על הפוקימון שלי לזמן מה?$"

CianwoodCity_Text_ManiacTakeCareShuckle:
	.string "Oh, thank you!\p"
	.string "Take good care of it, please!$"

CianwoodCity_Text_ManiacGotShuckle:
	.string "{PLAYER} received a POKéMON.$"

CianwoodCity_Text_ManiacPartyFull:
	.string "Your POKéMON party is full.$"

CianwoodCity_Text_ManiacIfHeComesBack:
	.string "אוי, לא… מה אעשה\n"
	.string "אם הוא יחזור?$"

CianwoodCity_Text_ManiacHowsdoing:
	.string "היי! מה שלום הפוקימון שלי?$"

CianwoodCity_Text_ManiacAskReturn:
	.string "היי! מה שלום הפוקימון שלי?\p"
	.string "נראה לי שעכשיו כבר אין סכנה,\n"
	.string "אז אפשר לקבל אותו בחזרה?$"

CianwoodCity_Text_ManiacThankYou:
	.string "תודה!$"

CianwoodCity_Text_ManiacShuckleNotThere:
	.string "Hey, you don't have my POKéMON\n"
	.string "with you.$"

CianwoodCity_Text_ManiacShuckleLikesYou:
	.string "הפוקימון שלי התחיל לחבב אותך.\p"
	.string "בסדר, כדאי שתשאיר אותו אצלך.\p"
	.string "אבל תבטיח להיות טוב אליו!$"

CianwoodCity_Text_ManiacRobbed:
	.string "הממ, משהו כאן לא בסדר.$"

CianwoodCity_Text_ManiacRobbed2:
	.string "אוי, לא, לא… זה כמו\n"
	.string "לשדוד אותי.$"

CianwoodCity_Text_ManiacHappinessSpeech:
	.string "בשביל פוקימונים, אושר זה להיות\n"
	.string "עם אדם שמתייחס אליהם יפה.$"

CianwoodCity_Text_ManiacLastMon:
	.string "If I take my POKéMON back,\n"
	.string "what are you going to use\n"
	.string "in battle?$"


CianwoodCity_Text_ManiacReturnedMon:
	.string "{PLAYER} החזיר את שאקי.$"
