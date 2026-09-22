SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "MONTE PIRÓ...\p"
	.string "En su cima hay dos orbes puestos\n"
	.string "uno junto al otro. ¿Lo sabías?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Sí, dos orbes uno junto al otro...\p"
	.string "Verlos ahí juntos...\n"
	.string "Es, de algún modo, relajante...$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "¿De verdad?\n"
	.string "Tal vez deberías ir a verlos...$"

