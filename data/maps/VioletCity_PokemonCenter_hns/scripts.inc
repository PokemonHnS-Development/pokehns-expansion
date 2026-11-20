VioletCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Pokecenter_OnTransition
	.byte 0

VioletCity_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_VIOLET_CITY_HNS
	end

VioletCity_PokemonCenter_EventScript_Aide::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TOGEPI_EGG, VioletCity_PokemonCenter_EventScript_Aide_Received
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	goto_if_eq VAR_0x8004, 1, VioletCity_PokemonCenter_EventScript_Aide_Offer @ party limit of 1: the Egg goes to the PC
	getpartysize
	goto_if_eq VAR_RESULT, VAR_0x8004, VioletCity_PokemonCenter_EventScript_AideNoRoom
VioletCity_PokemonCenter_EventScript_Aide_Offer::
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end


VioletCity_PokemonCenter_EventScript_Aide_FullParty::
	msgbox VioletCity_PokeCenter_Text_ElmsAideFullParty, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_AideNoRoom::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Refuse::
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	goto_if_eq VAR_0x8004, 1, VioletCity_PokemonCenter_EventScript_Aide_GiveEgg @ party limit of 1: the Egg goes to the PC
	getpartysize
	goto_if_eq VAR_RESULT, VAR_0x8004, VioletCity_PokemonCenter_EventScript_Aide_FullParty
VioletCity_PokemonCenter_EventScript_Aide_GiveEgg::
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	giveegg SPECIES_TOGEPI
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon @ party limit of 1 and every BOX full
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PC, VioletCity_PokemonCenter_EventScript_Aide_EggSentToPC
	setflag FLAG_RECEIVED_TOGEPI_EGG
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveItem, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE_SMALL
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_EggSentToPC::
	msgbox VioletCity_PokeCenter_Text_ElmsAideEggToPC, MSGBOX_DEFAULT
	closemessage
	return

VioletCity_PokemonCenter_EventScript_Aide_Received::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EVentScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Man::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_Text_BookshelfWoman::
	lock
	faceplayer
	msgbox VioletCity_PokeCenter_Text_BooksAreGreat, MSGBOX_DEFAULT
	closemessage
	release
	end


VioletCity_PokeCenter_Text_ElmsAideFavor:
	.string "{PLAYER}, הרבה זמן לא התראינו.\p"
	.string "פרופ' אלם ביקש ממני למצוא אותך.\p"
	.string "יש לו עוד בקשה.\p"
	.string "תסכים לקחת את ביצת הפוקימון?$"

VioletCity_PokeCenter_Text_ElmsAideNoRoom:
	.string "{PLAYER}, הרבה זמן לא התראינו.\p"
	.string "פרופ' אלם ביקש ממני למצוא אותך.\p"
	.string "יש לו עוד בקשה.\p"
	.string "תסכים לקחת את ביצת הפוקימון?\p"
	.string "אה, רגע… קודם צריך\n"
	.string "לפנות מקום בקבוצה שלך.$"

VioletCity_PokeCenter_Text_ElmsAideGiveEgg:
	.string "גילינו שפוקימון לא בוקע\n"
	.string "עד שהוא גדל בתוך הביצה.\p"
	.string "כדי לבקוע, הוא גם צריך להיות\n"
	.string "יחד עם פוקימונים פעילים אחרים.\p"
	.string "{PLAYER}, רק עליך אנחנו יכולים לסמוך.$"

VioletCity_PokeCenter_Text_ElmsAideGiveItem:
	.string "אה, וזה עשוי לעזור כשהיא תבקע.$"

VioletCity_PokeCenter_Text_ElmsAideFullParty:
	.string "אוי, לא. אין לך מקום לעוד פוקימונים.\p"
	.string "אחכה כאן עד שיתפנה מקום לביצה.$"

VioletCity_PokeCenter_Text_ElmsAideEggToPC:
	.string "אה, אבל אין לך מקום לעוד פוקימונים.\p"
	.string "אל דאגה, שלחתי את הביצה\n"
	.string "למחשב של ביל בשבילך.$"

VioletCity_PokeCenter_Text_ElmsAideRefuse:
	.string "א-אבל… פרופ' אלם ביקש דווקא אותך…$"

VioletCity_PokeCenter_Text_BooksAreGreat:
	.string "בזמן שהפוקימונים שלי מתאוששים,\n"
	.string "אני אוהבת לקרוא ספר טוב.$"

VioletCity_PokeCenter_Text_MobileAdapter:
	.string "I just battled a friend in\n"
	.string "CIANWOOD over a link.\p"
	.string "If you connect a MOBILE ADAPTER,\n"
	.string "you can link with a friend far\l"
	.string "away.$"

VioletCity_PokeCenter_Text_GameboyKid:
	.string "בחור בשם ביל יצר את מערכת\n"
	.string "אחסון הפוקימונים במחשב.$"

VioletCity_PokeCenter_Text_Gentleman:
	.string "זה היה לפני בערך שלוש שנים.\p"
	.string "צוות רוקט השתמש בפוקימונים\n"
	.string "למטרות רעות.\p"
	.string "אבל הצדק ניצח: ילד צעיר\n"
	.string "פירק את החבורה שלהם.$"

VioletCity_PokeCenter_Text_Youngster:
	.string "פוקימונים הם חכמים. הם לא יצייתו\n"
	.string "למאמן שהם לא מכבדים.\p"
	.string "בלי תגי המכון המתאימים,\n"
	.string "הם פשוט יעשו מה שבא להם.$"
