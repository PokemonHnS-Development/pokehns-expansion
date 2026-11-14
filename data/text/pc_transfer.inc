gText_PkmnTransferredSomeonesPC::
	.string "{STR_VAR_2} הועבר\n"
	.string "למחשב של מישהו.\p"
	.string "הוא הונח בתיבה\n"
	.string "”{STR_VAR_1}”.$"

gText_PkmnTransferredLanettesPC::
	.string "{STR_VAR_2} הועבר\n"
#if IS_FRLG || IS_HNS
	.string "למחשב של ביל.\p"
#else
	.string "למחשב של לאנט.\p"
#endif
	.string "הוא הונח בתיבה\n"
	.string "”{STR_VAR_1}”.$"

gText_PkmnTransferredSomeonesPCBoxFull::
	.string "התיבה ”{STR_VAR_3}”\n"
	.string "במחשב של מישהו מלאה.\p"
	.string "{STR_VAR_2} הועבר\n"
	.string "לתיבה ”{STR_VAR_1}”.$"

gText_PkmnTransferredLanettesPCBoxFull::
	.string "התיבה ”{STR_VAR_3}”\n"
#if IS_FRLG || IS_HNS
	.string "במחשב של ביל מלאה.\p"
#else
	.string "במחשב של לאנט מלאה.\p"
#endif
	.string "{STR_VAR_2} הועבר\n"
	.string "לתיבה ”{STR_VAR_1}”.$"

gText_PkmnSentToPCAfterCatch::
	.string "{STR_VAR_2} נשלח\n"
	.string "למחשב של {B_PC_CREATOR_NAME}.\p"
	.string "הוא הונח בתיבה\n"
	.string "”{STR_VAR_1}”.$"

gText_PlayerObtainedTheMon::
	.string "{PLAYER} obtained\n"
	.string "the {STR_VAR_1}!$"

gText_NoMoreRoomForPokemon::
	.string "אין יותר מקום לפוקימונים!\p"
	.string "תיבות הפוקימונים מלאות\n"
	.string "ואי אפשר להכניס אליהן עוד!$"

gText_NicknameThisPokemon::
	.string "לתת כינוי ל{STR_VAR_1} הזה?$"
