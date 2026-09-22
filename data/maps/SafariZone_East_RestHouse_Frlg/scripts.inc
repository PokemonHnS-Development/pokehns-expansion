SafariZone_East_RestHouse_Frlg_MapScripts::
	.byte 0

SafariZone_East_RestHouse_EventScript_Rocker::
	msgbox SafariZone_East_Text_CaughtChanseyAllWorthwhile, MSGBOX_NPC
	end

SafariZone_East_RestHouse_EventScript_Scientist::
	msgbox SafariZone_East_Text_HowManyDidYouCatch, MSGBOX_NPC
	end

SafariZone_East_RestHouse_EventScript_BaldingMan::
	msgbox SafariZone_East_Text_TiredFromAllTheFun, MSGBOX_NPC
	end

SafariZone_East_Text_HowManyDidYouCatch::
	.string "¿Cuántos atrapaste?\n"
	.string "¡Estoy agotado del esfuerzo!$"

SafariZone_East_Text_CaughtChanseyAllWorthwhile::
	.string "¡Atrapé un CHANSEY!\p"
	.string "Eso hace que valga la pena.$"

SafariZone_East_Text_TiredFromAllTheFun::
	.string "¡Uff!\n"
	.string "¡Estoy cansado de tanta diversión!$"

