MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "De joven, viajé por todo el mundo\n"
	.string "como ENTRENADOR POKéMON.\p"
	.string "Ahora que soy un viejo cascarrabias,\n"
	.string "mi único gusto es ver a los jóvenes\l"
	.string "ENTRENADORES luchar.$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "The door appears to be locked.$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "Un ENTRENADOR llamado {STR_VAR_1}\n"
	.string "está visitando mi casa.\p"
	.string "¿Te gustaría desafiar el Torneo\n"
	.string "¿{STR_VAR_1}?$"

RS_MysteryEventsHouse_Text_YouWontBattle:
	.string "¿No lucharás? Me decepciona\n"
	.string "no poder verte combatir…$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "¡Oh, bien, bien!\p"
	.string "Pero mi casa no es muy resistente.\p"
	.string "¿Podrías limitar el combate a\n"
	.string "un duelo de 3 contra 3?$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "Antes de que luchen, deberían\n"
	.string "guardar su progreso.$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "I hope to see a good match!$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "Así que quedó en un empate.\p"
	.string "¡Fue un duelo brillante donde\n"
	.string "nadie cedió ni un paso!$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "¡Eso fue superlativo!\p"
	.string "¡Vaya, fue como verme a mí mismo\n"
	.string "en mi juventud otra vez!$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "¡Ah, qué mala suerte!\p"
	.string "Pero fue un buen combate.\n"
	.string "Espero que ganes la próxima vez.$"
