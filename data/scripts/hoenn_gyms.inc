@ Hoenn & Seek (part 13b): gym prerequisites, Rare Candies, leader rematches,
@ and the Hoenn League (Elite Four + Wallace as the final badge).

@ ---------------------------------------------------------------- shared
HoennSeek_EventScript_GateOpen::
	return

@ Every leader gives 3 Rare Candies with the badge (called after the gym TM).
HoennSeek_EventScript_GymRareCandies::
	msgbox HoennSeek_Text_GymRareCandies, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 3
	return

@ ---------------------------------------------------------------- Norman: 4 badges first
@ Called right after Norman's lock/faceplayer.
HoennSeek_EventScript_NormanGate::
	goto_if_set FLAG_HOENN_STAMP_GYM_5, HoennSeek_EventScript_GateOpen
	specialvar VAR_RESULT, HoennGetStampCount
	goto_if_ge VAR_RESULT, 4, HoennSeek_EventScript_GateOpen
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox HoennSeek_Text_NormanGate, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Wattson: New Mauville first
@ He hands over the Basement Key before the battle, and only battles once the
@ generator is off (VAR_NEW_MAUVILLE_STATE 2). Thunderbolt still comes after.
HoennSeek_EventScript_WattsonGate::
	goto_if_set FLAG_HOENN_STAMP_GYM_3, HoennSeek_EventScript_GateOpen
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, HoennSeek_EventScript_WattsonGateReady
	lock
	faceplayer
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, HoennSeek_EventScript_WattsonGateRemind
	msgbox HoennSeek_Text_WattsonFavor, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox HoennSeek_Text_WattsonFavorAfter, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_WattsonGateRemind::
	msgbox HoennSeek_Text_WattsonGateRemind, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_WattsonGateReady::
	return

@ ---------------------------------------------------------------- Tate & Liza: Cozmo's meteorite
HoennSeek_EventScript_TateAndLizaGate::
	goto_if_set FLAG_HOENN_STAMP_GYM_7, HoennSeek_EventScript_GateOpen
	goto_if_set FLAG_HOENN_METEORITE_DELIVERED, HoennSeek_EventScript_GateOpen
	lock
	faceplayer
	msgbox HoennSeek_Text_TateAndLizaGate, MSGBOX_DEFAULT
	release
	end

@ Prof. Cozmo (Fallarbor) hands over the meteorite to deliver.
HoennSeek_EventScript_Cozmo::
	lock
	faceplayer
	goto_if_set FLAG_HOENN_METEORITE_DELIVERED, HoennSeek_EventScript_CozmoThanks
	goto_if_set FLAG_HOENN_COZMO_GAVE_METEORITE, HoennSeek_EventScript_CozmoRemind
	msgbox HoennSeek_Text_CozmoAsk, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_HOENN_COZMO_GAVE_METEORITE
	msgbox HoennSeek_Text_CozmoAskAfter, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_CozmoRemind::
	msgbox HoennSeek_Text_CozmoRemind, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_CozmoThanks::
	msgbox HoennSeek_Text_CozmoThanks, MSGBOX_DEFAULT
	release
	end

@ Space Center 1F scientist (the one by the window) takes the meteorite.
HoennSeek_EventScript_SpaceCenterMeteorite::
	goto_if_set FLAG_HOENN_METEORITE_DELIVERED, MossdeepCity_SpaceCenter_1F_EventScript_Scientist
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_SpaceCenter_1F_EventScript_Scientist
	lock
	faceplayer
	msgbox HoennSeek_Text_SpaceCenterMeteorite, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	removeitem ITEM_METEORITE
	setflag FLAG_HOENN_METEORITE_DELIVERED
	msgbox HoennSeek_Text_SpaceCenterMeteoriteAfter, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Winona: at the Weather Institute
@ She waits outside the Weather Institute on Route 119 until you talk to her;
@ removeobject sets FLAG_HOENN_WINONA_BACK (her Route 119 object's flag).
HoennSeek_EventScript_WinonaRoute119::
	lock
	faceplayer
	msgbox HoennSeek_Text_WinonaRoute119, MSGBOX_DEFAULT
	closemessage
	playse SE_M_FLY
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

@ Fortree Gym OnTransition: Winona's gym object hides until she's back.
HoennSeek_EventScript_FortreeGymWinona::
	call_if_unset FLAG_HOENN_WINONA_BACK, HoennSeek_EventScript_FortreeGymHideWinona
	call_if_set FLAG_HOENN_WINONA_BACK, HoennSeek_EventScript_FortreeGymShowWinona
	return
HoennSeek_EventScript_FortreeGymHideWinona::
	setflag FLAG_HOENN_WINONA_GYM_HIDDEN
	return
HoennSeek_EventScript_FortreeGymShowWinona::
	clearflag FLAG_HOENN_WINONA_GYM_HIDDEN
	return

HoennSeek_EventScript_FortreeGuideWinonaAway::
	goto_if_set FLAG_HOENN_WINONA_BACK, HoennSeek_EventScript_GateOpen
	msgbox HoennSeek_Text_FortreeGuideWinonaAway, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------- leader rematches
@ After Wallace, every leader takes a rematch by talking (scaled to Lv 85,
@ src/hoenn_scaling.c). The trainer flag is cleared so the same team battles.
HoennSeek_EventScript_RematchAsk::
	msgbox HoennSeek_Text_LeaderRematchAsk, MSGBOX_YESNO
	return

HoennSeek_EventScript_RematchDecline::
	msgbox HoennSeek_Text_LeaderRematchDecline, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_RematchDone::
	msgbox HoennSeek_Text_LeaderRematchAfter, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_RematchRoxanne::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_ROXANNE_1
	trainerbattle_no_intro TRAINER_ROXANNE_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchBrawly::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_BRAWLY_1
	trainerbattle_no_intro TRAINER_BRAWLY_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchWattson::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_WATTSON_1
	trainerbattle_no_intro TRAINER_WATTSON_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchFlannery::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_FLANNERY_1
	trainerbattle_no_intro TRAINER_FLANNERY_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchNorman::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_NORMAN_1
	trainerbattle_no_intro TRAINER_NORMAN_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchWinona::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_WINONA_1
	trainerbattle_no_intro TRAINER_WINONA_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchTateAndLiza::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_TATE_AND_LIZA_1
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, HoennSeek_Text_LeaderRematchGo, HoennSeek_Text_LeaderRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons
	goto HoennSeek_EventScript_RematchDone

HoennSeek_EventScript_RematchJuan::
	call HoennSeek_EventScript_RematchAsk
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_RematchDecline
	cleartrainerflag TRAINER_JUAN_1
	trainerbattle_no_intro TRAINER_JUAN_1, HoennSeek_Text_LeaderRematchDefeat
	goto HoennSeek_EventScript_RematchDone

@ ---------------------------------------------------------------- Hoenn League
@ The Elite Four rooms use VAR_HOENN_E4_STATE (VAR_ELITE_4_STATE is HnS's).
@ Entering the League lobby resets the run.
HoennSeek_EventScript_ResetHoennE4::
	setvar VAR_HOENN_E4_STATE, 0
	clearflag FLAG_DEFEATED_ELITE_4_SIDNEY
	clearflag FLAG_DEFEATED_ELITE_4_PHOEBE
	clearflag FLAG_DEFEATED_ELITE_4_GLACIA
	clearflag FLAG_DEFEATED_ELITE_4_DRAKE
	return

@ The door guards want all eight Hoenn badges.
HoennSeek_EventScript_LeagueBadgeCheck::
	specialvar VAR_RESULT, HoennGetStampCount
	goto_if_lt VAR_RESULT, 8, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	return

@ Wallace's room, after the battle: the League badge, then the Hall of Fame.
HoennSeek_EventScript_WallaceDefeated::
	goto_if_set FLAG_HOENN_STAMP_WALLACE, HoennSeek_EventScript_WallaceRematchWon
	msgbox HoennSeek_Text_WallaceBadge, MSGBOX_DEFAULT
	message HoennSeek_Text_ReceivedLeagueBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	setflag FLAG_HOENN_STAMP_WALLACE
	msgbox HoennSeek_Text_WallaceHallOfFame, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_WallaceToHallOfFame
HoennSeek_EventScript_WallaceRematchWon::
	msgbox HoennSeek_Text_WallaceRematchWon, MSGBOX_DEFAULT
HoennSeek_EventScript_WallaceToHallOfFame::
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	waitmovement 0
	delay 20
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

@ Hall of Fame, after the record: no GameClear (that is HnS's ending);
@ reset the League and go back to the lobby.
HoennSeek_EventScript_HallOfFameDone::
	call HoennSeek_EventScript_ResetHoennE4
	clearflag FLAG_ENTERED_ELITE_FOUR
	msgbox HoennSeek_Text_HallOfFameDone, MSGBOX_DEFAULT
	call HoennSeek_EventScript_BMBackCall @ part 16d: May calls, they're back
	closemessage
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	warp MAP_EVER_GRANDE_CITY_POKEMON_LEAGUE_1F, 9, 10
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------- text
HoennSeek_Text_GymRareCandies:
	.string "The POKéMON LEAGUE also sends these\n"
	.string "to every HOENN BADGE winner.$"

HoennSeek_Text_NormanGate:
	.string "NORMAN: So you're the TRAINER from\n"
	.string "JOHTO that everyone's talking about.\p"
	.string "Every GYM sends its results to the\n"
	.string "LEAGUE, and I read them all. MAY\l"
	.string "calls asking about you every week.\p"
	.string "You have {STR_VAR_1} HOENN BADGES.\n"
	.string "I only battle TRAINERS with four.\p"
	.string "It's how I've always run this GYM.\n"
	.string "Come back when you have them.$"

HoennSeek_Text_WattsonFavor:
	.string "WATTSON: Wahahaha! A challenger!\p"
	.string "But hold on. Before we battle, I need\n"
	.string "a favor from someone with power.\p"
	.string "NEW MAUVILLE, under ROUTE 110, has\n"
	.string "a generator that's running wild.\p"
	.string "If it isn't shut off, MAUVILLE could\n"
	.string "go up in sparks! Here, the key!$"

HoennSeek_Text_WattsonFavorAfter:
	.string "WATTSON: Get to the BASEMENT KEY door\n"
	.string "on ROUTE 110's water and shut that\l"
	.string "generator off.\p"
	.string "Then we'll have our\n"
	.string "battle! Wahahaha!$"

HoennSeek_Text_WattsonGateRemind:
	.string "WATTSON: The NEW MAUVILLE generator\n"
	.string "is still running!\p"
	.string "Shut it off, and then I'll give you\n"
	.string "the shock of your life!$"

HoennSeek_Text_TateAndLizaGate:
	.string "TATE: We knew you'd come…\p"
	.string "LIZA: …but you're early.\p"
	.string "TATE: We foresee you carrying a\n"
	.string "METEORITE from FALLARBOR…\p"
	.string "LIZA: …to our SPACE CENTER.\p"
	.string "TATE: Once it's there…\n"
	.string "LIZA: …we'll battle!$"

HoennSeek_Text_CozmoAsk:
	.string "PROF. COZMO: Oh, a TRAINER from\n"
	.string "JOHTO? Perfect timing!\p"
	.string "The MOSSDEEP SPACE CENTER wants to\n"
	.string "study my METEORITE from METEOR\l"
	.string "FALLS. But I can't leave my work.\p"
	.string "Would you take it there for me?$"

HoennSeek_Text_CozmoAskAfter:
	.string "PROF. COZMO: Funny thing… The GYM\n"
	.string "twins in MOSSDEEP phoned to say a\l"
	.string "visitor would bring it.\p"
	.string "They're never wrong, those two!$"

HoennSeek_Text_CozmoRemind:
	.string "PROF. COZMO: The SPACE CENTER is in\n"
	.string "MOSSDEEP. Take good care of\l"
	.string "my METEORITE!$"

HoennSeek_Text_CozmoThanks:
	.string "PROF. COZMO: The SPACE CENTER called!\n"
	.string "My METEORITE arrived safely.\p"
	.string "Thank you so much!$"

HoennSeek_Text_SpaceCenterMeteorite:
	.string "Is that PROF. COZMO's METEORITE?\n"
	.string "We've been waiting for this!$"

HoennSeek_Text_SpaceCenterMeteoriteAfter:
	.string "Thank you! We'll take very good care\n"
	.string "of it.\p"
	.string "Oh, and the GYM LEADERS said to send\n"
	.string "you over when you got here. Strange…\l"
	.string "How did they know?$"

HoennSeek_Text_WinonaRoute119:
	.string "WINONA: Oh? A challenger, all the way\n"
	.string "out here?\p"
	.string "I've been helping the WEATHER\n"
	.string "INSTITUTE track a storm. My bird\l"
	.string "POKéMON read the winds well.\p"
	.string "But the storm has passed, and a GYM\n"
	.string "LEADER shouldn't keep a\l"
	.string "TRAINER waiting.\p"
	.string "I'll fly back to FORTREE. Meet me at\n"
	.string "the GYM!$"

HoennSeek_Text_FortreeGuideWinonaAway:
	.string "Bad news, though. WINONA's away!\p"
	.string "She's helping the WEATHER INSTITUTE\n"
	.string "on ROUTE 119. Go find her there!$"

HoennSeek_Text_LeaderRematchAsk:
	.string "Now that you've beaten WALLACE, I'd\n"
	.string "like to test myself again.\p"
	.string "My POKéMON are at full strength.\n"
	.string "Will you battle me?$"

HoennSeek_Text_LeaderRematchGo:
	.string "Then show us a champion's strength!$"

HoennSeek_Text_LeaderRematchDecline:
	.string "I understand. I'll be here whenever\n"
	.string "you're ready.$"

HoennSeek_Text_LeaderRematchDefeat:
	.string "Incredible… You're even stronger\n"
	.string "than before!$"

HoennSeek_Text_LeaderRematchAfter:
	.string "Thank you for the battle.\n"
	.string "Come back anytime!$"

HoennSeek_Text_WallaceBadge:
	.string "WALLACE: In HOENN, the LEAGUE gives\n"
	.string "one last BADGE to the TRAINER who\l"
	.string "defeats its CHAMPION.\p"
	.string "You already hold JOHTO's and KANTO's\n"
	.string "titles. Take HOENN's mark, too.$"

HoennSeek_Text_ReceivedLeagueBadge:
	.string "{PLAYER} received the HOENN LEAGUE\n"
	.string "BADGE from WALLACE.$"

HoennSeek_Text_WallaceHallOfFame:
	.string "WALLACE: Keep the title of CHAMPION?\n"
	.string "No, I know you won't stay.\p"
	.string "But your POKéMON belong in our HALL\n"
	.string "OF FAME. Come with me.$"

HoennSeek_Text_WallaceRematchWon:
	.string "WALLACE: Magnificent, once again.\n"
	.string "Let's record this team as well.$"

HoennSeek_Text_HallOfFameDone:
	.string "Your team has been recorded in the\n"
	.string "HOENN HALL OF FAME.\p"
	.string "The ELITE FOUR await a rematch\n"
	.string "whenever you return.$"
