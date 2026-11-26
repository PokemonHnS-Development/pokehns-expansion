@ Hoenn & Seek (part 16d): PokéGear event calls (src/hoenn_phone.c), Wally on the phone,
@ Birch giving Brendan's and May's numbers, and the Johto starters back at Elm's lab.
@ Contact lines (when YOU call May, Brendan or Wally) are in src/pokenav_match_call_data.c.

@ ---------------------------------------------------------------- event calls

@ Started from the overworld step hook with the call's ID in VAR_0x8004.
HoennSeek_EventScript_PhoneEvent::
	lockall
	switch VAR_0x8004
	case HOENN_CALL_BADGE1, HoennSeek_EventScript_CallBadge1
	case HOENN_CALL_BADGE4, HoennSeek_EventScript_CallBadge4
	case HOENN_CALL_BADGE8, HoennSeek_EventScript_CallBadge8
	case HOENN_CALL_ELM, HoennSeek_EventScript_CallElm
	case HOENN_CALL_TEAMS, HoennSeek_EventScript_CallTeams
	case HOENN_CALL_RED, HoennSeek_EventScript_CallRed
	case HOENN_CALL_CONTEST, HoennSeek_EventScript_CallContest
	case HOENN_CALL_BASE, HoennSeek_EventScript_CallBase
	case HOENN_CALL_SITES, HoennSeek_EventScript_CallSites
	case HOENN_CALL_JK_BASE, HoennSeek_EventScript_CallJohtoKantoBase
	case HOENN_CALL_STRAIT, HoennSeek_EventScript_CallStrait
	case HOENN_CALL_STARTER_FOUND, HoennSeek_EventScript_CallStarterFound
	case HOENN_CALL_KANTO_STARTER, HoennSeek_EventScript_CallKantoStarter
	case HOENN_CALL_POND, HoennSeek_EventScript_CallPond @ 2.0 part 18 (hoenn_species.inc)
	case HOENN_CALL_RALTS, HoennSeek_EventScript_CallRalts
	case HOENN_CALL_KIYO, HoennSeek_EventScript_CallKiyo
	case HOENN_CALL_SCIZOR, HoennSeek_EventScript_CallScizor
	releaseall
	end

HoennSeek_EventScript_CallBadge1::
	setflag FLAG_HOENN_CALL_BADGE1
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallBadge1
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallBadge4::
	setflag FLAG_HOENN_CALL_BADGE4
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallBadge4
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallBadge8::
	setflag FLAG_HOENN_CALL_BADGE8
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallBadge8
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallTeams::
	setflag FLAG_HOENN_CALL_TEAMS
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallTeams
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallRed::
	setflag FLAG_HOENN_CALL_RED
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallRed
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallContest::
	setflag FLAG_HOENN_CALL_CONTEST
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallContest
	goto HoennSeek_EventScript_CallEnd

@ Brendan: one of Birch's aides saw you duck into your new secret base (part 18).
HoennSeek_EventScript_CallBase::
	setflag FLAG_HOENN_CALL_BASE
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallBase
	goto HoennSeek_EventScript_CallEnd

@ May: your base is at one of the reopened legendary sites (2.0 part 12). Birch's
@ aides chart those sites for the League now that they're open again, and one of
@ them tells her.
HoennSeek_EventScript_CallSites::
	setflag FLAG_HOENN_CALL_SITES
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallSites
	goto HoennSeek_EventScript_CallEnd

@ Brendan: your base is in Johto or Kanto (2.0 part 13a). A HIKER he battled on
@ the way through saw the name on the base's entrance.
HoennSeek_EventScript_CallJohtoKantoBase::
	setflag FLAG_HOENN_CALL_JK_BASE
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallJohtoKantoBase
	goto HoennSeek_EventScript_CallEnd

@ May: you surfed the Tidal Strait into Hoenn (2.0 part 14). MR. BRINEY saw you
@ from his boat and phoned Norman, who told May.
HoennSeek_EventScript_CallStrait::
	setflag FLAG_HOENN_CALL_STRAIT
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallStrait
	goto HoennSeek_EventScript_CallEnd

@ Elm (2.0 part 15a): Birch sent back two Johto starters he'd been raising for
@ Elm, and the unclaimed one got loose; the call says where a ferry sailor saw
@ it (data/scripts/hoenn_starters.inc). VAR_STARTER_MON 0 Chikorita: Totodile at
@ Lake of Rage (part 15b), 1 Cyndaquil: Chikorita on Route 46, 2 Totodile:
@ Cyndaquil at the Burned Tower.
HoennSeek_EventScript_CallElm::
	setflag FLAG_HOENN_CALL_ELM
	setspeaker HoennSeek_Text_NameElm
	goto_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_CallElmChikorita
	goto_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_CallElmCyndaquil
	pokenavcall HoennSeek_Text_CallElmTotodile
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallElmChikorita:
	pokenavcall HoennSeek_Text_CallElmChikorita
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_CallElmCyndaquil:
	pokenavcall HoennSeek_Text_CallElmCyndaquil
	goto HoennSeek_EventScript_CallEnd

@ Elm (2.0 part 15a, Brendan's until 17r): his lab's escapee is with you.
HoennSeek_EventScript_CallStarterFound::
	setflag FLAG_HOENN_CALL_STARTER_FOUND
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	call_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_BufferChikorita
	call_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_BufferCyndaquil
	setspeaker HoennSeek_Text_NameElm
	pokenavcall HoennSeek_Text_CallStarterFound
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_BufferChikorita:
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	return
HoennSeek_EventScript_BufferCyndaquil:
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	return

@ 2.0 part 16: May, once Bulbasaur or Charmander has chosen you (Bill told Birch).
HoennSeek_EventScript_CallKantoStarter::
	setflag FLAG_HOENN_CALL_KANTO_STARTER
	goto_if_set FLAG_HOENN_SQUIRTLE_DONE, HoennSeek_EventScript_CallSquirtle
	bufferspeciesname STR_VAR_1, SPECIES_BULBASAUR
	call_if_set FLAG_HOENN_CHARMANDER_DONE, HoennSeek_EventScript_BufferCharmander
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallKantoStarter
	goto HoennSeek_EventScript_CallEnd
HoennSeek_EventScript_BufferCharmander:
	bufferspeciesname STR_VAR_1, SPECIES_CHARMANDER
	return
@ Part 17: the Squirtle Squad's leader, if it's with you when the call rings.
HoennSeek_EventScript_CallSquirtle:
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallSquirtle
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallEnd::
	waitmessage
	delay 30
	closemessage
	releaseall
	end

@ May's call after the first Hall of Fame (was Norman's in part 16a).
@ Called from HoennSeek_EventScript_HallOfFameDone.
HoennSeek_EventScript_BMBackCall::
	goto_if_set FLAG_HOENN_BM_BACK_CALLED, HoennSeek_EventScript_BMBackCallDone
	closemessage
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_BMBackCall
	waitmessage
	delay 30
	setflag FLAG_HOENN_BM_BACK_CALLED
	clearflag FLAG_HOENN_HIDE_BM_OUTSIDE
HoennSeek_EventScript_BMBackCallDone::
	return

@ Birch, after Mudkip: Brendan's and May's numbers.
HoennSeek_EventScript_BirchGivesNumbers::
	msgbox HoennSeek_Text_BirchNumbers, MSGBOX_DEFAULT
	closemessage
	delay 30
	setflag FLAG_HOENN_BM_PHONE
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox HoennSeek_Text_BMRegistered, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

@ ---------------------------------------------------------------- Wally (Victory Road exit)

@ Replaces VictoryRoad_1F_EventScript_ExitWally (map.json swap). He asks for your
@ number after the first win; his calls arm the rematch (src/hoenn_phone.c).
HoennSeek_EventScript_VRWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat, HoennSeek_EventScript_VRWallyRegister
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_VRWallyRematch
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end
HoennSeek_EventScript_VRWallyRegister::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox HoennSeek_Text_WallyRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	setvar VAR_0x8004, TRAINER_WALLY_VR_2
	special SetMatchCallRegisteredFlag
	setflag FLAG_HOENN_WALLY_PHONE
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox HoennSeek_Text_WallyRegistered, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	release
	end
HoennSeek_EventScript_VRWallyRematch::
	trainerbattle_rematch TRAINER_WALLY_VR_2, HoennSeek_Text_WallyRematchIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox HoennSeek_Text_WallyRematchAfter, MSGBOX_AUTOCLOSE
	end

@ ---------------------------------------------------------------- text

HoennSeek_Text_NameMay:
	.string "MAY$"
HoennSeek_Text_NameBrendan:
	.string "BRENDAN$"
HoennSeek_Text_NameElm:
	.string "PROF. ELM$"

@ Hoenn & Seek (part 16d) — PokéGear text. Lines were word-wrapped at 30 columns when written.
@ Every phone line names who told the caller (their dads, the gym leaders' LEAGUE reports,
@ PROF. OAK, MAXIE...). Keep that up when adding lines.
HoennSeek_Text_CallBadge1::
	.string "Hi, {PLAYER}! It's MAY! We\n"
	.string "haven't met, but PROF. BIRCH\l"
	.string "gave you my number!\p"
	.string "My dad just told me you won\n"
	.string "your first HOENN BADGE!\p"
	.string "Gym leaders report every match\n"
	.string "to the LEAGUE, and Dad's a gym\l"
	.string "leader. So he hears\l"
	.string "everything first!\p"
	.string "BRENDAN and I are still in\n"
	.string "KANTO, training at the foot of\l"
	.string "MT. SILVER.\p"
	.string "BRENDAN says hi. Well… he\n"
	.string "grunted. Same thing! Bye!$"

HoennSeek_Text_CallBadge4::
	.string "…It's BRENDAN. Four\n"
	.string "badges already.\p"
	.string "My dad heard from NORMAN.\n"
	.string "They're neighbors, so they\l"
	.string "talk about you over the\l"
	.string "fence now.\p"
	.string "Dad also does volcano research\n"
	.string "with TEAM MAGMA these days.\p"
	.string "He says TABITHA at their\n"
	.string "station near LAVARIDGE has\l"
	.string "been asking around for help.\l"
	.string "If you're nearby.\p"
	.string "That's all. Keep going.$"

HoennSeek_Text_CallBadge8::
	.string "{PLAYER}! It's MAY!\n"
	.string "EIGHT BADGES!\p"
	.string "Dad says the LEAGUE already\n"
	.string "knows you're coming. EVER\l"
	.string "GRANDE's buzzing!\p"
	.string "We're almost done here. RED\n"
	.string "still hasn't said a single\l"
	.string "word to us. Not one!\p"
	.string "Beat WALLACE, okay? Then we'll\n"
	.string "come home and battle you\l"
	.string "ourselves!$"

HoennSeek_Text_CallElmChikorita::
	.string "Hello, {PLAYER}! It's PROF. ELM!\p"
	.string "Congratulations on your first\n"
	.string "BADGE! But I have bad news, too.\p"
	.string "One of my lab's POKéMON got out!\n"
	.string "A CHIKORITA I was raising for\l"
	.string "the next new TRAINER.\p"
	.string "My aide saw it heading up ROUTE\n"
	.string "46, following a sweet smell.\p"
	.string "If you find it, it should know my\n"
	.string "lab's scent on you. Good luck!$"

HoennSeek_Text_CallElmCyndaquil::
	.string "Hello, {PLAYER}! It's PROF. ELM!\p"
	.string "Congratulations on your first\n"
	.string "BADGE! But I have bad news, too.\p"
	.string "One of my lab's POKéMON got out!\n"
	.string "A CYNDAQUIL I was raising for\l"
	.string "the next new TRAINER.\p"
	.string "Someone saw a little flame near\n"
	.string "ECRUTEAK's BURNED TOWER, at night.\p"
	.string "If you find it, it should know my\n"
	.string "lab's scent on you. Good luck!$"

HoennSeek_Text_CallElmTotodile::
	.string "Hello, {PLAYER}! It's PROF. ELM!\p"
	.string "Congratulations on your first\n"
	.string "BADGE! But I have bad news, too.\p"
	.string "One of my lab's POKéMON got out!\n"
	.string "A TOTODILE I was raising for\l"
	.string "the next new TRAINER.\p"
	.string "A fisherman at the LAKE OF RAGE\n"
	.string "says something keeps stealing\l"
	.string "his bait. I bet it's our TOTODILE!\p"
	.string "If you find it, it should know my\n"
	.string "lab's scent on you. Good luck!$"

HoennSeek_Text_CallStarterFound::
	.string "{PLAYER}! It's PROF. ELM!\p"
	.string "My aide says our {STR_VAR_1}\n"
	.string "is with you now! It must have\l"
	.string "smelled the lab on you.\p"
	.string "I was so worried about it. It\n"
	.string "couldn't be in better hands.\l"
	.string "Take good care of it!$"

HoennSeek_Text_CallSquirtle::
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "PROF. BIRCH's aide just got\n"
	.string "off the ferry from VERMILION.\p"
	.string "The whole port was talking about\n"
	.string "a SQUIRTLE gang that put out a\l"
	.string "fire, and the TRAINER who left\l"
	.string "with their leader!\p"
	.string "That was you, wasn't it?\n"
	.string "I knew it!$"

HoennSeek_Text_CallKantoStarter::
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "PROF. BIRCH was on the phone\n"
	.string "with BILL from CERULEAN today.\p"
	.string "He says the whole town is talking\n"
	.string "about you and a {STR_VAR_1}!\p"
	.string "They hardly ever pick a TRAINER\n"
	.string "on their own. It must really\l"
	.string "like you!$"

HoennSeek_Text_CallTeams::
	.string "It's BRENDAN. My dad was out\n"
	.string "at MT. CHIMNEY with\l"
	.string "MAXIE today.\p"
	.string "MAXIE says you beat him and\n"
	.string "ARCHIE at once. On MT. PYRE,\l"
	.string "of all places.\p"
	.string "He also told Dad about a tower\n"
	.string "in KANTO where GROUDON and\l"
	.string "KYOGRE are resting.\p"
	.string "…Dad wants to see it. So do I.\n"
	.string "Tell me if you find it.$"

HoennSeek_Text_CallRed::
	.string "{PLAYER}!! PROF. OAK just\n"
	.string "called both our dads!\p"
	.string "You beat RED! You actually\n"
	.string "beat RED!\p"
	.string "BRENDAN pretended not to care,\n"
	.string "then went straight back out to\l"
	.string "train. Typical!\p"
	.string "We're home if you ever want a\n"
	.string "rematch. Doubles, of course!$"

HoennSeek_Text_BMBackCall::
	.string "{PLAYER}! It's MAY! Dad told me\n"
	.string "you beat WALLACE!\p"
	.string "So guess what? BRENDAN and I\n"
	.string "just got back to LITTLEROOT!\p"
	.string "We're waiting outside. Come\n"
	.string "battle us! Both of us! Hurry!$"

HoennSeek_Text_MayPhone0::
	.string "MAY: Hi, it's MAY! We're in\n"
	.string "KANTO, near MT. SILVER.\p"
	.string "RED is up there somewhere.\n"
	.string "BRENDAN says we need more\l"
	.string "training. I say we need\l"
	.string "more snacks!$"

HoennSeek_Text_MayPhone1::
	.string "MAY: Dad keeps telling me\n"
	.string "about your gym battles. The\l"
	.string "leaders all call him!\p"
	.string "Oh! TEAM AQUA does sea rescues\n"
	.string "now. Dad says MATT at the\l"
	.string "SLATEPORT harbor is always\l"
	.string "asking for help.$"

HoennSeek_Text_MayPhone2::
	.string "MAY: Four BADGES! Did you\n"
	.string "battle my dad in\l"
	.string "PETALBURG yet?\p"
	.string "He'd never tell me if he lost.\n"
	.string "Tell me everything!\p"
	.string "Oh, and if you're in LILYCOVE,\n"
	.string "try the CONTEST HALL! I watch\l"
	.string "every show on TV.$"

HoennSeek_Text_MayPhone3::
	.string "MAY: We're packing up! RED\n"
	.string "still won't talk. At all. It's\l"
	.string "so creepy!\p"
	.string "Beat WALLACE and we'll\n"
	.string "come home!$"

HoennSeek_Text_MayPhone4::
	.string "MAY: We're back in LITTLEROOT!\n"
	.string "Come battle us! BRENDAN is\l"
	.string "pretending he isn't excited.$"

HoennSeek_Text_MayPhone5::
	.string "MAY: How's the TORCHIC from my\n"
	.string "BLAZIKEN? Raise it well!\p"
	.string "And PROF. OAK opened MT.\n"
	.string "SILVER for you, right? RED is\l"
	.string "waiting. Don't let him\l"
	.string "scare you!$"

HoennSeek_Text_MayPhone6::
	.string "MAY: You beat RED! Everyone in\n"
	.string "LITTLEROOT knows. Dad told the\l"
	.string "whole town!\p"
	.string "Come over for a\n"
	.string "rematch anytime!$"

HoennSeek_Text_BrendanPhone0::
	.string "BRENDAN: …It's BRENDAN. We're\n"
	.string "camped near MT. SILVER.\p"
	.string "RED stood there and stared at\n"
	.string "us. Then he won. That's it.$"

HoennSeek_Text_BrendanPhone1::
	.string "BRENDAN: My dad and NORMAN are\n"
	.string "neighbors. NORMAN hears about\l"
	.string "every gym battle, so Dad\l"
	.string "does too.\p"
	.string "Dad works with TEAM MAGMA on\n"
	.string "volcano research now. If you\l"
	.string "pass the old hideout, TABITHA\l"
	.string "might need a hand.$"

HoennSeek_Text_BrendanPhone2::
	.string "BRENDAN: WALLY called me. He's\n"
	.string "training at the end of VICTORY\l"
	.string "ROAD now.\p"
	.string "He's serious about it. Don't\n"
	.string "go easy on him.$"

HoennSeek_Text_BrendanPhone3::
	.string "BRENDAN: Eight. The ELITE FOUR\n"
	.string "are tough. WALLACE is tougher.\p"
	.string "Dad's doing fieldwork at the\n"
	.string "SAFARI ZONE off ROUTE 121. He\l"
	.string "says the north side has POKéMON\l"
	.string "from JOHTO. Bring BLOCKS.\p"
	.string "We'll be home soon.$"

HoennSeek_Text_BrendanPhone4::
	.string "BRENDAN: We're back. MAY won't\n"
	.string "stop talking about you.\l"
	.string "Come by.$"

HoennSeek_Text_BrendanPhone5::
	.string "BRENDAN: You beat us. Fine.\p"
	.string "PROF. OAK will let you up MT.\n"
	.string "SILVER now. Go see RED.\l"
	.string "Don't blink.$"

HoennSeek_Text_BrendanPhone6::
	.string "BRENDAN: Dad's still talking\n"
	.string "about that tower in KANTO\l"
	.string "MAXIE told him about.\p"
	.string "GROUDON and KYOGRE, resting.\n"
	.string "…I'd like to see that.$"

HoennSeek_Text_BrendanPhone7::
	.string "BRENDAN: PROF. OAK called my\n"
	.string "dad. You beat RED.\p"
	.string "…I'm going back up that\n"
	.string "mountain someday. You'll see.$"

HoennSeek_Text_WallyPhone0::
	.string "WALLY: Hi, {PLAYER}! I'm still\n"
	.string "training at VICTORY ROAD.\p"
	.string "My GARDEVOIR and I get a\n"
	.string "little stronger every day!$"

HoennSeek_Text_WallyPhone1::
	.string "WALLY: You beat WALLACE! I\n"
	.string "knew you could!\p"
	.string "I'm still at VICTORY ROAD.\n"
	.string "Come battle me again sometime!$"

HoennSeek_Text_WallyCall1::
	.string "Hi, {PLAYER}! It's WALLY!\p"
	.string "I climbed all of VICTORY ROAD\n"
	.string "today without stopping once!\l"
	.string "My doctor would be so proud!$"

HoennSeek_Text_WallyCall2::
	.string "It's WALLY! My uncle in\n"
	.string "MAUVILLE says hi.\p"
	.string "He says I've grown taller. I\n"
	.string "think my GARDEVOIR did too!$"

HoennSeek_Text_WallyCallBattle::
	.string "{PLAYER}, it's WALLY!\p"
	.string "I'm at VICTORY ROAD. I think\n"
	.string "I'm ready for another battle.\l"
	.string "Will you come?$"

HoennSeek_Text_WallyRegister::
	.string "WALLY: That was amazing… Can I\n"
	.string "have your number? I want to\l"
	.string "call you when I'm ready to\l"
	.string "battle again!$"

HoennSeek_Text_WallyRegistered::
	.string "Registered WALLY in\n"
	.string "the POKéGEAR.$"

HoennSeek_Text_WallyRematchIntro::
	.string "WALLY: {PLAYER}! You came! I've\n"
	.string "been training every day.\l"
	.string "Let's battle!$"

HoennSeek_Text_WallyRematchAfter::
	.string "WALLY: I'll call you again\n"
	.string "when I'm stronger. That's\l"
	.string "a promise!$"

HoennSeek_Text_BirchNumbers::
	.string "PROF. BIRCH: Here, take BRENDAN's\n"
	.string "and MAY's numbers, too.\p"
	.string "They're off in KANTO, but\n"
	.string "they'd love to hear from a\l"
	.string "JOHTO trainer!$"

HoennSeek_Text_BMRegistered::
	.string "Registered BRENDAN and MAY in\n"
	.string "the POKéGEAR.$"

HoennSeek_Text_LabStarterNoRoom::
	.string "There's no room for it in your\n"
	.string "party or BOXES.$"

HoennSeek_Text_CallBase::
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "One of Dad's aides was out on\n"
	.string "fieldwork and saw you climb into a\l"
	.string "SECRET BASE! Nice!\p"
	.string "MAY and I built one on ROUTE 111\n"
	.string "back when we were rivals. She\l"
	.string "filled it with dolls. Every inch.\p"
	.string "FORTREE's shop has desks and\n"
	.string "chairs. LILYCOVE's DEPT. STORE has\l"
	.string "the rest. Don't let MAY decorate!$"

HoennSeek_Text_CallJohtoKantoBase::
	.string "{PLAYER}! It's BRENDAN! A HIKER I\n"
	.string "just battled swears he found a\l"
	.string "SECRET BASE way out here!\p"
	.string "He said the name on it was\n"
	.string "{PLAYER}. I knew it was you!\p"
	.string "I thought SECRET POWER only worked\n"
	.string "in HOENN. Turns out a hollow tree\l"
	.string "or a cracked rock is all it needs.\p"
	.string "MAY wants to visit. Hide the\n"
	.string "DOLLS, or she'll take them home!$"

HoennSeek_Text_CallStrait::
	.string "{PLAYER}! It's MAY! Dad just got a\n"
	.string "call from MR. BRINEY.\p"
	.string "He was sailing past ROUTE 105 and\n"
	.string "saw someone SURF in from the west,\l"
	.string "right out of the TIDAL STRAIT!\p"
	.string "Nobody's crossed it since that\n"
	.string "whirlpool kicked up. He said the\l"
	.string "SURFER looked just like you!\p"
	.string "BRENDAN wants to try it next.\n"
	.string "I told him to take the ferry!$"

HoennSeek_Text_CallSites::
	.string "{PLAYER}! It's MAY! PROF. BIRCH's\n"
	.string "aides are charting the old\l"
	.string "legendary sites for the LEAGUE,\l"
	.string "now that they're open again.\p"
	.string "One of them just called me,\n"
	.string "laughing. Someone made a SECRET\l"
	.string "BASE inside one. It was you!\p"
	.string "The POKéMON that slept there\n"
	.string "are long gone, so it's all yours.\p"
	.string "BRENDAN says it's spooky. I say\n"
	.string "it needs dolls. Lots of dolls!$"

HoennSeek_Text_CallContest::
	.string "{PLAYER}! It's MAY! I just saw you\n"
	.string "win a CONTEST on TV!\p"
	.string "The CONTEST HALL broadcasts every\n"
	.string "show. Even out here in KANTO!\p"
	.string "I used to enter CONTESTS all the\n"
	.string "time before I got serious about\l"
	.string "battling. I still miss the ribbons!\p"
	.string "Win a MASTER RANK one for me, okay?$"

