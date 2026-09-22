VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: Perdí contra ti, {PLAYER}, pero\n"
	.string "ya no me siento mal.\p"
	.string "Tengo un nuevo propósito en la vida.\n"
	.string "Junto a mi RALTS, voy a\l"
	.string "retar GIMNASIOS POKéMON y ser\l"
	.string "un gran ENTRENADOR.\p"
	.string "Por favor, mírame, {PLAYER}.\n"
	.string "Voy a ser más fuerte que tú.\p"
	.string "Cuando lo logre, te retaré\n"
	.string "a otra batalla.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "WALLY: Mírame, {PLAYER}.\nVoy a ser más fuerte que tú.\pCuando lo consiga, te retaré\na otro combate.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "UNCLE: Oh! {PLAYER}{KUN}!\n"
	.string "WALLY está al lado.\p"
	.string "Pero, niño, hay algo que tengo que\n"
	.string "decirte.\p"
	.string "Este entorno natural está haciendo\n"
	.string "maravillas por la salud de WALLY.\p"
	.string "Tal vez no sea solo el entorno.\n"
	.string "Podrían ser los POKéMON los que le\l"
	.string "dan esperanza al chico.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY se ha ido...\n"
	.string "Se escapó solo...$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "TÍO: ¿De veras?\nWALLY se marchó tan lejos por su\lcuenta...\pBueno, hay que reconocer que es\nel hijo de mi hermano menor.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: ¿Tú eres...?\n"
	.string "¡Ah, claro, ya entiendo!\p"
	.string "Eres el {PLAYER} de quien WALLY\n"
	.string "me estuvo hablando.\p"
	.string "Soy la prima de WALLY.\n"
	.string "¡Mucho gusto!\p"
	.string "Creo que WALLY está mucho más\n"
	.string "animado y sano desde que vino.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: No te preocupes por WALLY.\n"
	.string "Él estará bien.\p"
	.string "Conozco a mi primito, y él tiene\n"
	.string "POKéMON con él también.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Gracias a ti, podré ver a mi novia\n"
	.string "cada día.\l"
	.string "¿Feliz? ¡Claro que lo estoy!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "El novio de mi hija es una persona\n"
	.string "muy decidida y apasionada.\p"
	.string "Ha estado cavando un túnel sin parar\n"
	.string "solo para poder ver a mi hija.\p"
	.string "Mi hija está algo preocupada,\n"
	.string "así que va mucho al túnel.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "Es increíble. El novio de mi hija\n"
	.string "¡cavaba el túnel a mano!\p"
	.string "¡Es increíble!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "Si le pasara algo a WALLY,\nnunca podría mirar a sus\lpadres de PETALIA a los ojos...$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "¿WALLY estuvo en CIUDAD COLOSALIA?\pSus padres en CIUDAD PETALIA se\nasombrarían al oírlo!$"

