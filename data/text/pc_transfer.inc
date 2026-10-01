gText_PkmnTransferredSomeonesPC::
	.string "{STR_VAR_2} fue transferido a\n"
	.string "la PC de ALGUIEN.\p"
	.string "Fue puesto en la \n"
	.string "CAJA “{STR_VAR_1}.”$"

gText_PkmnTransferredLanettesPC::
	.string "{STR_VAR_2} fue transferido a\n"
#if IS_FRLG || IS_HNS
	.string "la PC de BILL.\p"
#else
	.string "la PC de LANETTE.\p"
#endif
	.string "Fue puesto en la \n"
	.string "CAJA “{STR_VAR_1}.”$"

gText_PkmnTransferredSomeonesPCBoxFull::
	.string "CAJA “{STR_VAR_3}” en\n"
	.string "la PC de ALGUIEN estaba llena.\p"
	.string "{STR_VAR_2} fue transferido a\n"
	.string "CAJA “{STR_VAR_1}.”$"

gText_PkmnTransferredLanettesPCBoxFull::
	.string "CAJA “{STR_VAR_3}” en\n"
#if IS_FRLG || IS_HNS
	.string "la PC de BILL estaba llena.\p"
#else
	.string "la PC de LANETTE estaba llena.\p"
#endif
	.string "{STR_VAR_2} fue transferido a\n"
	.string "CAJA “{STR_VAR_1}.”$"

gText_PkmnSentToPCAfterCatch::
	.string "{STR_VAR_2} fue enviado a la\n"
	.string "PC de {B_PC_CREATOR_NAME}.\p"
	.string "Fue puesto en la \n"
	.string "CAJA “{STR_VAR_1}”.$"

gText_PlayerObtainedTheMon::
	.string "{PLAYER} obtuvo\n"
	.string "¡la {STR_VAR_1}!$"

gText_NoMoreRoomForPokemon::
	.string "¡No hay espacio para POKéMON!\p"
	.string "¡Las CAJAS de POKéMON están llenas\n"
	.string "y no aceptan más!$"

gText_NicknameThisPokemon::
	.string "¿Quieres ponerle un mote a\n"
	.string "este {STR_VAR_1}?$"
