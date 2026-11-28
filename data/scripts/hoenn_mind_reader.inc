@ Hoenn & Seek (part 14a): the Mossdeep guru, in Emerald's old link-games
@ building (MossdeepCity_GameCorner_1F). He reads a Pokémon's hidden potential:
@   POTENTIAL  raises one IV to 31            1 STAR PIECE per stat
@   ABILITY    swaps to the other ability     1 STAR PIECE
@              awakens the hidden ability     3 STAR PIECES
@ He can't focus until Tate & Liza are beaten (FLAG_HOENN_STAMP_GYM_7).
@ Specials are in src/hoenn_specials.c; VAR_0x8004 is the party slot.

HoennSeek_EventScript_MindReader::
	lock
	faceplayer
	goto_if_unset FLAG_HOENN_STAMP_GYM_7, HoennSeek_EventScript_MindReaderClouded
	goto_if_set FLAG_HOENN_MET_MIND_READER, HoennSeek_EventScript_MindReaderMenu
	msgbox HoennSeek_Text_MindReaderIntro, MSGBOX_DEFAULT
	setflag FLAG_HOENN_MET_MIND_READER
HoennSeek_EventScript_MindReaderMenu::
	message HoennSeek_Text_MindReaderWhatShallIRead
	waitmessage
	dynmultichoice 17, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_MindReaderPotential, HoennSeek_Text_MindReaderAbility, HoennSeek_Text_MindReaderNothing
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_MindReaderPotential
	goto_if_eq VAR_RESULT, 1, HoennSeek_EventScript_MindReaderAbility
	goto HoennSeek_EventScript_MindReaderBye

HoennSeek_EventScript_MindReaderClouded::
	msgbox HoennSeek_Text_MindReaderClouded, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderBye::
	msgbox HoennSeek_Text_MindReaderBye, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderNoStarPiece::
	msgbox HoennSeek_Text_MindReaderNoStarPiece, MSGBOX_DEFAULT
	release
	end

@ Sets VAR_0x8004 to a party slot and STR_VAR_1 to its nickname,
@ or ends the conversation if nothing (or an egg) was picked.
HoennSeek_EventScript_MindReaderChooseMon::
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, HoennSeek_EventScript_MindReaderBye
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, HoennSeek_EventScript_MindReaderEgg
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	return

HoennSeek_EventScript_MindReaderEgg::
	msgbox HoennSeek_Text_MindReaderEgg, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
HoennSeek_EventScript_MindReaderPotential::
	checkitem ITEM_STAR_PIECE
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MindReaderNoStarPiece
	msgbox HoennSeek_Text_MindReaderWhichMon, MSGBOX_DEFAULT
	call HoennSeek_EventScript_MindReaderChooseMon
HoennSeek_EventScript_MindReaderPickStat::
	message HoennSeek_Text_MindReaderWhichStat
	waitmessage
	special HoennPushIVList
	dynmultistack 15, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, HoennSeek_EventScript_MindReaderBye
	copyvar VAR_0x8005, VAR_RESULT
	specialvar VAR_RESULT, HoennCheckIV
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_MindReaderStatMaxed
	msgbox HoennSeek_Text_MindReaderConfirmStat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_MindReaderPickStat
	removeitem ITEM_STAR_PIECE
	specialvar VAR_RESULT, HoennMaxIV
	call HoennSeek_EventScript_MindReaderTrance
	msgbox HoennSeek_Text_MindReaderStatDone, MSGBOX_DEFAULT
	checkitem ITEM_STAR_PIECE
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MindReaderBye
	goto HoennSeek_EventScript_MindReaderPickStat

HoennSeek_EventScript_MindReaderStatMaxed::
	msgbox HoennSeek_Text_MindReaderStatMaxed, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_MindReaderPickStat

@ ---------------------------------------------------------------------------
HoennSeek_EventScript_MindReaderAbility::
	checkitem ITEM_STAR_PIECE
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MindReaderNoStarPiece
	msgbox HoennSeek_Text_MindReaderWhichMon, MSGBOX_DEFAULT
	call HoennSeek_EventScript_MindReaderChooseMon
	specialvar VAR_RESULT, HoennCountOtherAbilities
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_MindReaderOneAbility
	message HoennSeek_Text_MindReaderWhichAbility
	waitmessage
	special HoennPushAbilityList
	dynmultistack 15, 0, FALSE, 3, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, HoennSeek_EventScript_MindReaderBye
	copyvar VAR_0x8005, VAR_RESULT
	special HoennBufferAbilitySlot
	goto_if_eq VAR_0x8005, 2, HoennSeek_EventScript_MindReaderHiddenAbility
	setvar VAR_0x8006, 1
	msgbox HoennSeek_Text_MindReaderConfirmAbility, MSGBOX_YESNO
	goto HoennSeek_EventScript_MindReaderPayAbility

HoennSeek_EventScript_MindReaderHiddenAbility::
	setvar VAR_0x8006, 3
	msgbox HoennSeek_Text_MindReaderConfirmHidden, MSGBOX_YESNO
HoennSeek_EventScript_MindReaderPayAbility::
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_MindReaderBye
	checkitem ITEM_STAR_PIECE, VAR_0x8006
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MindReaderNotEnough
	removeitem ITEM_STAR_PIECE, VAR_0x8006
	special HoennSetAbilitySlot
	call HoennSeek_EventScript_MindReaderTrance
	msgbox HoennSeek_Text_MindReaderAbilityDone, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderOneAbility::
	msgbox HoennSeek_Text_MindReaderOneAbility, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderNotEnough::
	msgbox HoennSeek_Text_MindReaderNotEnough, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderTrance::
	closemessage
	fadescreenspeed FADE_TO_WHITE, 4
	playse SE_M_MOONLIGHT
	waitse
	fadescreenspeed FADE_FROM_WHITE, 4
	playfanfare MUS_LEVEL_UP
	waitfanfare
	return

@ ---------------------------------------------------------------------------
@ His assistant explains the prices; the wall has a star chart.
HoennSeek_EventScript_MindReaderAide::
	lock
	faceplayer
	goto_if_unset FLAG_HOENN_STAMP_GYM_7, HoennSeek_EventScript_MindReaderAideClouded
	msgbox HoennSeek_Text_MindReaderAide, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MindReaderAideClouded::
	msgbox HoennSeek_Text_MindReaderAideClouded, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_StarChart::
	msgbox HoennSeek_Text_StarChart, MSGBOX_SIGN
	end

@ ---------------------------------------------------------------------------
HoennSeek_Text_MindReaderClouded:
	.string "…Hm? You wish me to read\n"
	.string "your POKéMON?\p"
	.string "I cannot. Not now.\p"
	.string "The twins' minds are so loud on\n"
	.string "this island… They drown out my own.\p"
	.string "Show TATE and LIZA their limits.\n"
	.string "Then MOSSDEEP will grow quiet enough\l"
	.string "for me to listen.$"

HoennSeek_Text_MindReaderIntro:
	.string "Ah… The island is quiet at last.\n"
	.string "The twins have been humbled.\p"
	.string "And you are the one who did it.\n"
	.string "I saw you coming, of course.\p"
	.string "I read the hearts of POKéMON.\p"
	.string "Every one of them carries potential,\n"
	.string "written like starlight. Some of it\l"
	.string "is buried very deep.\p"
	.string "I can draw it out… but the stars\n"
	.string "ask a price.\p"
	.string "A STAR PIECE. A sliver of the sky,\n"
	.string "to focus my mind.$"

HoennSeek_Text_MindReaderWhatShallIRead:
	.string "What shall I read today?$"

HoennSeek_Text_MindReaderPotential:
	.string "POTENTIAL$"

HoennSeek_Text_MindReaderAbility:
	.string "ABILITY$"

HoennSeek_Text_MindReaderNothing:
	.string "NOTHING$"

HoennSeek_Text_MindReaderBye:
	.string "The stars will wait for you.$"

HoennSeek_Text_MindReaderNoStarPiece:
	.string "You carry no STAR PIECE.\p"
	.string "Without one, my mind wanders.\n"
	.string "Come back when the sky has given\l"
	.string "you a piece of itself.$"

HoennSeek_Text_MindReaderWhichMon:
	.string "Which POKéMON shall I read?$"

HoennSeek_Text_MindReaderEgg:
	.string "That one has not yet hatched.\n"
	.string "There is nothing to read but dreams.$"

HoennSeek_Text_MindReaderWhichStat:
	.string "I see {STR_VAR_1}'s potential…\n"
	.string "Which shall I draw out?$"

HoennSeek_Text_MindReaderStatMaxed:
	.string "{STR_VAR_1}'s {STR_VAR_2} already shines\n"
	.string "as brightly as it can.$"

HoennSeek_Text_MindReaderConfirmStat:
	.string "To draw out {STR_VAR_1}'s full\n"
	.string "{STR_VAR_2}, I need one STAR PIECE.\p"
	.string "Shall I begin?$"

HoennSeek_Text_MindReaderStatDone:
	.string "…It is done.\p"
	.string "{STR_VAR_1}'s {STR_VAR_2} has reached\n"
	.string "its full potential!$"

HoennSeek_Text_MindReaderWhichAbility:
	.string "{STR_VAR_1} hides another way of\n"
	.string "being. Which shall I awaken?$"

HoennSeek_Text_MindReaderOneAbility:
	.string "{STR_VAR_1} knows only one way of\n"
	.string "being. There is nothing else\l"
	.string "to awaken.$"

HoennSeek_Text_MindReaderConfirmAbility:
	.string "To awaken {STR_VAR_2} in\n"
	.string "{STR_VAR_1}, I need one STAR PIECE.\p"
	.string "Shall I begin?$"

HoennSeek_Text_MindReaderConfirmHidden:
	.string "{STR_VAR_2}…\n"
	.string "That one is buried very deep.\p"
	.string "Drawing it out will take three\n"
	.string "STAR PIECES. Shall I begin?$"

HoennSeek_Text_MindReaderNotEnough:
	.string "You don't carry enough STAR PIECES.\n"
	.string "The stars do not bargain.$"

HoennSeek_Text_MindReaderAbilityDone:
	.string "…It is done.\p"
	.string "{STR_VAR_1} has awakened\n"
	.string "{STR_VAR_2}!$"

HoennSeek_Text_MindReaderAideClouded:
	.string "The MASTER hasn't been able to\n"
	.string "focus since those twins took over\l"
	.string "the GYM.\p"
	.string "He says their minds are “very loud.”\n"
	.string "Don't ask me what that means.$"

HoennSeek_Text_MindReaderAide:
	.string "The MASTER reads a POKéMON's\n"
	.string "hidden potential.\p"
	.string "One STAR PIECE draws out one stat\n"
	.string "to its fullest.\p"
	.string "One STAR PIECE changes its ability.\n"
	.string "A hidden ability takes three.\p"
	.string "STAR PIECES wash up on HOENN's\n"
	.string "routes and seafloor.\p"
	.string "Wild STARYU sometimes carry them,\n"
	.string "too. Try taking one off them!$"

HoennSeek_Text_StarChart:
	.string "It's a chart of the night sky.\p"
	.string "Some of the stars are circled\n"
	.string "in red ink.$"
