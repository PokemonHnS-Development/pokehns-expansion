@ Hoenn & Seek (part 13): dialogue for a visitor from Johto.
@ New scripts for NPCs whose Emerald lines assumed you were Brendan or May,
@ plus a few that notice your follower Pokémon. Rewritten Emerald lines stay in
@ their own maps' scripts.inc.

@ ---------------------------------------------------------------------------
@ Gym guides: the greeting grows with your stamp count, then the gym's advice.
HoennSeek_EventScript_GymGuideGreeting::
	specialvar VAR_RESULT, HoennGetStampCount
	buffernumberstring STR_VAR_1, VAR_RESULT
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_GymGuideGreetingNew
	goto_if_lt VAR_RESULT, 4, HoennSeek_EventScript_GymGuideGreetingSome
	msgbox HoennSeek_Text_GymGuideGreetingMany, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_GymGuideGreetingNew::
	msgbox HoennSeek_Text_GymGuideGreetingNew, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_GymGuideGreetingSome::
	msgbox HoennSeek_Text_GymGuideGreetingSome, MSGBOX_DEFAULT
	return

HoennSeek_Text_GymGuideGreetingNew:
	.string "Yo! A new face, huh?\p"
	.string "Wait… Are you the TRAINER who came\n"
	.string "over on the ferry from KANTO?\p"
	.string "Word travels fast in HOENN!$"

HoennSeek_Text_GymGuideGreetingSome:
	.string "Yo! It's the JOHTO TRAINER who's\n"
	.string "been collecting our GYM BADGES!\p"
	.string "That's {STR_VAR_1} already, right?\n"
	.string "Not bad, not bad!$"

HoennSeek_Text_GymGuideGreetingMany:
	.string "Whoa! The JOHTO CHAMPION everyone's\n"
	.string "talking about!\p"
	.string "{STR_VAR_1} BADGES already? The GYM\n"
	.string "LEADERS are getting nervous!$"

@ ---------------------------------------------------------------------------
@ Littleroot: May lives with Norman's family, Brendan with Birch's.
HoennSeek_EventScript_MaysMom::
	lock
	faceplayer
	msgbox HoennSeek_Text_MaysMom, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HoennBufferFollower
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MomEnd
	msgbox HoennSeek_Text_MaysMomFollower, MSGBOX_DEFAULT
HoennSeek_EventScript_MomEnd::
	release
	end

HoennSeek_EventScript_BrendansMom::
	lock
	faceplayer
	msgbox HoennSeek_Text_BrendansMom, MSGBOX_DEFAULT
	release
	end

HoennSeek_Text_MaysMom:
	.string "Oh! Hello there!\n"
	.string "You must be the TRAINER from JOHTO.\p"
	.string "I'm MAY's mother. My husband NORMAN\n"
	.string "runs the GYM over in PETALBURG.\p"
	.string "MAY's off traveling again.\n"
	.string "That girl can't sit still for a\l"
	.string "minute… just like her father.\p"
	.string "If you run into her, tell her to\n"
	.string "call home once in a while!$"

HoennSeek_Text_MaysMomFollower:
	.string "And who's this? Your {STR_VAR_1}?\p"
	.string "Aren't you a sweetie!\n"
	.string "You can come in, too.$"

HoennSeek_Text_BrendansMom:
	.string "Oh, a visitor! Are you looking for\n"
	.string "my husband?\p"
	.string "PROF. BIRCH is out doing fieldwork,\n"
	.string "as usual. Or he's in his LAB. Or\l"
	.string "he's lost in the tall grass again.\p"
	.string "Our BRENDAN is just the same.\n"
	.string "He and MAY have been rivals since\l"
	.string "the day they met.\p"
	.string "You're from JOHTO? How exciting!\n"
	.string "BRENDAN would love to battle you.$"

@ The twin outside mistakes you for one of them, from a distance.
HoennSeek_EventScript_LittlerootTwin::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, HoennSeek_EventScript_LittlerootTwinMay
	msgbox HoennSeek_Text_TwinThoughtBrendan, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_LittlerootTwinMay::
	msgbox HoennSeek_Text_TwinThoughtMay, MSGBOX_DEFAULT
	release
	end

HoennSeek_Text_TwinThoughtBrendan:
	.string "BRENDAN! You're back!\p"
	.string "…Huh? Oh! Sorry!\n"
	.string "From over there you looked just\l"
	.string "like BRENDAN.\p"
	.string "You're from JOHTO? Is that far?\n"
	.string "Farther than OLDALE?$"

HoennSeek_Text_TwinThoughtMay:
	.string "MAY! You're back!\p"
	.string "…Huh? Oh! Sorry!\n"
	.string "From over there you looked just\l"
	.string "like MAY.\p"
	.string "You're from JOHTO? Is that far?\n"
	.string "Farther than OLDALE?$"

@ ---------------------------------------------------------------------------
@ Wally's family: he's grown up and trains at Victory Road now.
HoennSeek_EventScript_WallysDad::
	msgbox HoennSeek_Text_WallysDad, MSGBOX_NPC
	end

HoennSeek_EventScript_WallysMom::
	msgbox HoennSeek_Text_WallysMom, MSGBOX_NPC
	end

HoennSeek_EventScript_WallysAunt::
	msgbox HoennSeek_Text_WallysAunt, MSGBOX_NPC
	end

HoennSeek_Text_WallysDad:
	.string "Oh! Are you the TRAINER from JOHTO\n"
	.string "everyone's been talking about?\p"
	.string "Our son WALLY used to be so frail.\n"
	.string "Now he battles at VICTORY ROAD\l"
	.string "almost every day!\p"
	.string "If you meet him, go easy on him.\p"
	.string "…Actually, don't.\n"
	.string "He'd never forgive you.$"

HoennSeek_Text_WallysMom:
	.string "WALLY caught his very first POKéMON\n"
	.string "right here in PETALBURG, you know.\p"
	.string "That shy little RALTS is a GARDEVOIR\n"
	.string "now. Can you believe it?$"

HoennSeek_Text_WallysAunt:
	.string "Our nephew WALLY lived with us while\n"
	.string "he got his strength back.\p"
	.string "The clean air in VERDANTURF did him\n"
	.string "a world of good.\p"
	.string "Now he's off training at VICTORY\n"
	.string "ROAD. He still writes every week!$"

@ ---------------------------------------------------------------------------
@ Townsfolk who notice your follower (fall back to their Emerald line).
HoennSeek_EventScript_SlateportShopper::
	lock
	faceplayer
	specialvar VAR_RESULT, HoennBufferFollower
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_SlateportShopperPlain
	msgbox HoennSeek_Text_SlateportShopperFollower, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SlateportShopperPlain::
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_DEFAULT
	release
	end

HoennSeek_Text_SlateportShopperFollower:
	.string "Oh my! Is that your {STR_VAR_1}?\p"
	.string "I'd buy it something at the market,\n"
	.string "but I've already bought too much…\l"
	.string "again.$"

HoennSeek_EventScript_FortreeBoy::
	lock
	faceplayer
	specialvar VAR_RESULT, HoennBufferFollower
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_FortreeBoyPlain
	msgbox HoennSeek_Text_FortreeBoyFollower, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_FortreeBoyPlain::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_DEFAULT
	release
	end

HoennSeek_Text_FortreeBoyFollower:
	.string "Whoa, your {STR_VAR_1} climbed all\n"
	.string "those ladders after you?\p"
	.string "My mom won't even let BUG POKéMON\n"
	.string "in the house!$"

HoennSeek_EventScript_LavaridgeBather::
	lock
	faceplayer
	specialvar VAR_RESULT, HoennBufferFollower
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_LavaridgeBatherPlain
	msgbox HoennSeek_Text_LavaridgeBatherFollower, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_LavaridgeBatherPlain::
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_DEFAULT
	release
	end

HoennSeek_Text_LavaridgeBatherFollower:
	.string "Oh, you like hot springs, do you?\p"
	.string "And your {STR_VAR_1} looks like it\n"
	.string "could use a good soak, too.\p"
	.string "We get POKéMON from all over now.\n"
	.string "Even from JOHTO, it seems!$"

@ ---------------------------------------------------------------------------
@ Johto jokes.
HoennSeek_EventScript_GoldenrodExpat::
	msgbox HoennSeek_Text_GoldenrodExpat, MSGBOX_NPC
	end

HoennSeek_Text_GoldenrodExpat:
	.string "That accent… You're from JOHTO?\p"
	.string "Me too! I moved here from GOLDENROD\n"
	.string "CITY years ago.\p"
	.string "SLATEPORT's MARKET is nice, but it's\n"
	.string "no GOLDENROD DEPARTMENT STORE.\p"
	.string "And nobody here has even heard of\n"
	.string "the RADIO TOWER jingle!\p"
	.string "…Do you think the MOOMOO MILK\n"
	.string "would survive the ferry?$"

HoennSeek_EventScript_PacifidlogKid::
	msgbox HoennSeek_Text_PacifidlogKid, MSGBOX_NPC
	end

HoennSeek_Text_PacifidlogKid:
	.string "See, isn't it neat?\n"
	.string "These houses are on water!\p"
	.string "I was born here!\p"
	.string "You're from where? JOHTO?\p"
	.string "Never heard of it.\n"
	.string "Is it past SLATEPORT?$"
