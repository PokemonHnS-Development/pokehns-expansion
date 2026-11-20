@ Hand over to the ROM's own ending for Red, the tail of MtSilver_SummitDay_EventScript_RedOnDefeat
@ (MtSilver_SummitDay_hns:45-63) without its text: respawn in New Bark Town, the land ribbon,
@ FLAG_DEFEATED_RED, then special GameClear (Hall of Fame record and credits). Run on the summit
@ after `settrainerflag` for the post-Sinjoh Red variant (MtSilver_SummitDay_EventScript_RedPostOBC).
	settrainerflag TRAINER_RED_POSTOBC_HNS
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	special GivePartyMonLandRibbon
	setflag FLAG_HIDE_MTSILVER_RED
	setflag FLAG_DEFEATED_RED
	setflag FLAG_END_NUZLOCKE
	clearflag FLAG_HIDE_MTSILVER_RED
	special GameClear
	waitstate
	end
