@ Story step 6b: after the Kanto-champion Hall of Fame. Route 28, Mt. Silver, the Sinjoh storyline
@ to its end (VAR_SINJOH_STORYLINE 13: Arceus caught, Steven back in New Sinjoh). End states; the
@ 16-plate quest's items are not reproduced.

@ Route 28: Oak's scientist (Route28_EventScript_Trigger_Scientist:21-42); Mt. Silver
@ (MtSilver_Outside_OnTransition:8)
	setvar VAR_ROUTE28_SCIENTIST, 2
	setflag FLAG_HIDE_ROUTE28_SCIENTIST
	setflag FLAG_VISITED_MT_SILVER
@ Mt. Silver Pokemon Center: Meara's bonus content (MtSilver_PokemonCenter_EventScript_Meara_
@ BonusContentPrompt:20-42), the waterfall-room scientist (MtSilver_1F_WaterfallRoom_Scientist_Scene:32-33)
	setflag FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_STEVEN
	setflag FLAG_MT_SILVER_1F_HIDE_SCIENTIST
	setvar VAR_SINJOH_STORYLINE, 2
@ Snowswept Cavern, Route 49, New Sinjoh, the kimono hideout, the Sinjoh lab
@ (Snowswept_Cavern_Eventscript_Machamp:160, Route49_EventScripts_KimonoGirl:86-87,
@ NewSinjoh_On_Transition:6, NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos:42,
@ SinjohRuins_Lab_EventScript_IntroChoseYes:91, _16Plates:815, SinjohRuins_Lab_FinalPlateScene:263)
	setflag FLAG_ROUTE_49_KIMONOGIRL
	setflag FLAG_VISITED_NEW_SINJOH
	setvar VAR_SINJOH_STORYLINE, 8
@ Sinjoh Ruins: the stairs scene, Steven's battle, the Arceus room, Arceus caught, Steven leaves
@ (SinjohRuins_StairsScene:142, SinjohRuins_EventScript_TriggerStevenBattleRight:240-254,
@ SinjohRuins_ArceusRoom_TriggerScene:71-101, _EventScript_Arceus:283-310, _TriggerSteven:337-339)
	settrainerflag TRAINER_STEVEN_HNS
	setflag FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setflag FLAG_HIDE_SINJOHRUINS_STEVEN
	clearflag FLAG_HIDE_NEWSINJOH_STEVEN
	setvar VAR_SINJOH_STORYLINE, 13
	givemon SPECIES_ARCEUS, 100, ITEM_NONE, BALL_ULTRA
	end
