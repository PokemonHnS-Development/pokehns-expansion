BattleFrontier_ShowCaughtBannedSpecies::
	goto_if_eq VAR_0x8005, 0, BattleFrontier_ShowCaughtBannedSpeciesEnd
	msgbox BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ShowCaughtBannedSpeciesEnd
	callnative ShowBattleFrontierCaughtBannedSpecies
	waitstate
BattleFrontier_ShowCaughtBannedSpeciesEnd:
	return


BattleFrontier_DoYouWantToSeeTheListOfCaughtBannedSpecies:
	.string "רוצה לראות את רשימת מיני\n"
	.string "הפוקימונים שאסור להביא?$"
