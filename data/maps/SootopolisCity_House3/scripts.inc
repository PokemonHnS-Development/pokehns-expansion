SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Eres ENTRENADOR POKéMON, ¿verdad?\p"
	.string "JUAN de CIUDAD ARRECIFE tiene fans.\n"
	.string "¡Incluso más que su alumno WALLACE!\p"
	.string "¿Tú tienes alguno?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "Oh, entonces eres bastante fuerte.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Ay, Dios mío...\n"
	.string "Eso es un poco solitario.\p"
	.string "Esfuérzate un poco más para tener\n"
	.string "tus propios fans.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "Hay fans dedicados que vienen hasta\n"
	.string "fuera de HOENN.\p"
	.string "Fue una locura cuando fui al\n"
	.string "CLUB DE FANS en CIUDAD VERAZ.$"

