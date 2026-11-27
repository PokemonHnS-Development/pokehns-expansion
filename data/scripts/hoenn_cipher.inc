@ Hoenn & Seek 2.0 parts 27-28: the Unown Cipher at the Ruins of Alph (plan section 8).
@ Code and the design notes: src/hoenn_cipher.c. Flags: part 27a's section of
@ include/constants/hoenn_events.h.
@
@ Part 27a (Cipher A):
@ - Once all four panels are solved and you've been to Hoenn, Brendan calls (the
@   Ruins lab phoned Birch) and the lab researcher asks for help: a line of Unown
@   letters with Hoenn braille above it appeared in the big Words room.
@ - Words Room 1 (the Rosetta): reading the braille sets FLAG_HOENN_CIPHER_ROSETTA.
@ - Words Rooms 2-4 at night: a glowing word that changes by weekday. The first
@   time you see a weekday's word, a message notes it.
@ - The lab researcher counts the words; with all seven she sets
@   FLAG_HOENN_CIPHER_ALL_WORDS (part 27b's glyph sites follow the words).

@ ---- The lab researcher (RuinsOfAlph_Lab_hns, map.json script swap) ----------
HoennSeek_EventScript_AlphResearcher::
	specialvar VAR_RESULT, HoennCipherIsOpen
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_Scientist2
	lock
	faceplayer
	goto_if_set FLAG_HOENN_CIPHER_ROSETTA, HoennSeek_EventScript_AlphResearcherWords
	goto_if_set FLAG_HOENN_CIPHER_ASKED, HoennSeek_EventScript_AlphResearcherAgain
	setflag FLAG_HOENN_CIPHER_ASKED
	msgbox HoennSeek_Text_AlphResearcherAsk, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_AlphResearcherAgain:
	msgbox HoennSeek_Text_AlphResearcherAgain, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_AlphResearcherWords:
	specialvar VAR_RESULT, HoennCipherWordCount
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_AlphResearcherRosetta
	goto_if_ge VAR_RESULT, 7, HoennSeek_EventScript_AlphResearcherAllWords
	msgbox HoennSeek_Text_AlphResearcherCount, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_AlphResearcherRosetta:
	setflag FLAG_HOENN_CIPHER_ASKED
	msgbox HoennSeek_Text_AlphResearcherRosetta, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_AlphResearcherAllWords:
	goto_if_set FLAG_HOENN_CIPHER_ALL_WORDS, HoennSeek_EventScript_AlphResearcherAllWordsAgain
	setflag FLAG_HOENN_CIPHER_ALL_WORDS
	msgbox HoennSeek_Text_AlphResearcherAllWords, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_AlphResearcherAllWordsAgain:
	msgbox HoennSeek_Text_AlphResearcherAllWordsAgain, MSGBOX_DEFAULT
	release
	end

@ ---- Words Room 1: the Rosetta line (bg events on rows 2 and 3) ---------------
HoennSeek_EventScript_CipherRosetta::
	specialvar VAR_RESULT, HoennCipherIsOpen
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_CipherNothing
	lockall
	goto_if_set FLAG_HOENN_CIPHER_ROSETTA, HoennSeek_EventScript_CipherRosettaAgain
	msgbox HoennSeek_Text_CipherRosettaSee, MSGBOX_DEFAULT
	braillemessage HoennSeek_Braille_AtNightWeSpeak
	waitbuttonpress
	closebraillemessage
	msgbox HoennSeek_Text_CipherRosettaRead, MSGBOX_DEFAULT
	setflag FLAG_HOENN_CIPHER_ROSETTA
	playfanfare MUS_OBTAIN_ITEM
	message HoennSeek_Text_CipherCanReadUnown
	waitmessage
	waitfanfare
	msgbox HoennSeek_Text_CipherTellLab, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_CipherRosettaAgain:
	braillemessage HoennSeek_Braille_AtNightWeSpeak
	waitbuttonpress
	closebraillemessage
	msgbox HoennSeek_Text_CipherRosettaAgain, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_CipherNothing:
	end

@ ---- Words Rooms 2-4: tonight's word ------------------------------------------
@ Each room's ON_LOAD draws it (special HoennCipherDrawRoom); these run from its
@ ON_TRANSITION and ON_FRAME table.
HoennSeek_EventScript_CipherWordsOnTransition::
	specialvar VAR_RESULT, HoennCipherTonightWord
	call_if_eq VAR_RESULT, HOENN_CIPHER_NEW_WORD, HoennSeek_EventScript_CipherArmWord
	end

HoennSeek_EventScript_CipherArmWord:
	setvar VAR_TEMP_1, 1
	return

HoennSeek_EventScript_CipherWordsOnFrame::
	map_script_2 VAR_TEMP_1, 1, HoennSeek_EventScript_CipherNewWord
	.2byte 0

HoennSeek_EventScript_CipherNewWord::
	lockall
	setvar VAR_TEMP_1, 2
	specialvar VAR_RESULT, HoennCipherTonightWord
	msgbox HoennSeek_Text_CipherWordGlows, MSGBOX_DEFAULT
	special HoennCipherNoteWord
	playse SE_EXP_MAX
	message HoennSeek_Text_CipherNotedWord
	waitmessage
	waitse
	waitbuttonpress
	specialvar VAR_RESULT, HoennCipherWordCount
	goto_if_ge VAR_RESULT, 7, HoennSeek_EventScript_CipherSevenWords
	msgbox HoennSeek_Text_CipherWordsSoFar, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_CipherSevenWords:
	msgbox HoennSeek_Text_CipherSevenWords, MSGBOX_DEFAULT
	releaseall
	end

@ Bg events on row 3 of rooms 2-4: reading the glowing word again.
HoennSeek_EventScript_CipherWordSign::
	specialvar VAR_RESULT, HoennCipherTonightWord
	goto_if_eq VAR_RESULT, HOENN_CIPHER_NO_WORD, HoennSeek_EventScript_CipherNothing
	msgbox HoennSeek_Text_CipherWordSign, MSGBOX_SIGN
	end

@ ---- Brendan's call ------------------------------------------------------------
HoennSeek_EventScript_CallCipher::
	setflag FLAG_HOENN_CALL_CIPHER
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallCipher
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts ----------------------------------------------------------------------
HoennSeek_Braille_AtNightWeSpeak:
	brailleformat 0, 0, 0, 0, 0, 0
	.braille "AT NIGHT WE SPEAK$"

HoennSeek_Text_AlphResearcherAsk:
	.string "Oh! You solved all four panels in\n"
	.string "the RUINS, didn't you?\p"
	.string "Something happened after the last\n"
	.string "one. A tremor, deep in the RUINS.\p"
	.string "Now there's a new line on the floor\n"
	.string "of the big WORDS chamber, the one\l"
	.string "with six lines of writing.\p"
	.string "UNOWN letters, like the others…\n"
	.string "but above each one is a little\l"
	.string "square of raised dots.\p"
	.string "PROF. BIRCH in HOENN says dots like\n"
	.string "that are HOENN braille. Nobody here\l"
	.string "can read it.\p"
	.string "You've been to HOENN, haven't you?\n"
	.string "Could you take a look for us?$"

HoennSeek_Text_AlphResearcherAgain:
	.string "The new line is in the big WORDS\n"
	.string "chamber, the one with six lines\l"
	.string "of writing.\p"
	.string "It runs along the north wall.$"

HoennSeek_Text_AlphResearcherRosetta:
	.string "AT NIGHT WE SPEAK… The braille\n"
	.string "says it, and so do the UNOWN\l"
	.string "letters under it!\p"
	.string "One dot square for each UNOWN\n"
	.string "letter. It's a key to their whole\l"
	.string "alphabet!\p"
	.string "AT NIGHT… We've never studied the\n"
	.string "RUINS after dark. We all go home\l"
	.string "at sunset.\p"
	.string "You can go in, though. Please look\n"
	.string "at the WORDS chambers at night and\l"
	.string "tell me what you see!$"

HoennSeek_Text_AlphResearcherCount:
	.string "Night words so far: {STR_VAR_2}.\p"
	.string "That's {STR_VAR_1} of the seven days of\n"
	.string "the week.\p"
	.string "A different word every night…\n"
	.string "Keep going! I want them all.$"

HoennSeek_Text_AlphResearcherAllWords:
	.string "All seven! TOWER, MOON, ICE, WHIRL,\n"
	.string "MORTAR, UNION, FOAM…\p"
	.string "Wait. Those aren't just words.\n"
	.string "They're places!\p"
	.string "The BELL TOWER, MT. MOON, the ICE\n"
	.string "PATH, the WHIRL ISLANDS, MT. MORTAR,\l"
	.string "UNION CAVE and the SEAFOAM ISLANDS!\p"
	.string "Wild UNOWN turn up far from the\n"
	.string "RUINS sometimes. Maybe they go to\l"
	.string "those places… at night.$"

HoennSeek_Text_AlphResearcherAllWordsAgain:
	.string "TOWER, MOON, ICE, WHIRL, MORTAR,\n"
	.string "UNION, FOAM.\p"
	.string "Seven places for seven nights. I\n"
	.string "wonder what the UNOWN do there…$"

HoennSeek_Text_CipherRosettaSee:
	.string "A line of UNOWN letters is carved\n"
	.string "into the floor.\p"
	.string "Above each letter is a square of\n"
	.string "raised dots…$"

HoennSeek_Text_CipherRosettaRead:
	.string "It's HOENN braille! It reads\n"
	.string "AT NIGHT WE SPEAK.\p"
	.string "Each square of dots sits right\n"
	.string "above an UNOWN letter.\p"
	.string "The UNOWN letters spell out the\n"
	.string "same words, one by one!$"

HoennSeek_Text_CipherCanReadUnown:
	.string "{PLAYER} learned to read the\n"
	.string "UNOWN letters!$"

HoennSeek_Text_CipherTellLab:
	.string "The researchers in the lab will\n"
	.string "want to hear about this.$"

HoennSeek_Text_CipherRosettaAgain:
	.string "AT NIGHT WE SPEAK.\n"
	.string "The UNOWN letters say the same.$"

HoennSeek_Text_CipherWordGlows:
	.string "Some of the UNOWN letters on the\n"
	.string "floor are glowing!\p"
	.string "They weren't here in the daytime.\n"
	.string "They spell {STR_VAR_1}.$"

HoennSeek_Text_CipherNotedWord:
	.string "{PLAYER} wrote down the word\n"
	.string "{STR_VAR_1}.$"

HoennSeek_Text_CipherWordsSoFar:
	.string "Night words noted: {STR_VAR_1} of 7.\n"
	.string "Will it be the same tomorrow?$"

HoennSeek_Text_CipherSevenWords:
	.string "That's a word for every night of\n"
	.string "the week! The lab should see this.$"

HoennSeek_Text_CipherWordSign:
	.string "The glowing UNOWN letters spell\n"
	.string "{STR_VAR_1}.$"

HoennSeek_Text_CallCipher:
	.string "{PLAYER}! It's BRENDAN.\p"
	.string "The lab at the RUINS OF ALPH\n"
	.string "phoned my dad today.\p"
	.string "A new line turned up inside the\n"
	.string "RUINS, and it's got HOENN braille\l"
	.string "on it!\p"
	.string "They asked Dad how to read it.\n"
	.string "He told them you've been to HOENN.\p"
	.string "And they said you solved all four\n"
	.string "of their stone panels, too!\p"
	.string "Go see them at the lab, okay?\n"
	.string "Dad wants to know what it says!$"
