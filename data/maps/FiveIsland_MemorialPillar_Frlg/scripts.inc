FiveIsland_MemorialPillar_Frlg_MapScripts::
	.byte 0

FiveIsland_MemorialPillar_EventScript_MemorialMan::
	lock
	goto_if_set FLAG_GOT_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42
	goto_if_set FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_ReturnedForTM42
	msgbox FiveIsland_MemorialPillar_Text_ScrubScrub
	closemessage
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_FacePlayer
	waitmovement 0
	delay 45
	msgbox FiveIsland_MemorialPillar_Text_YourMonsLookHealthy
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox FiveIsland_MemorialPillar_Text_ThisIsWhereIBuriedMyOnix
	release
	end

FiveIsland_MemorialPillar_EventScript_AlreadyGotTM42::
	msgbox FiveIsland_MemorialPillar_Text_ScrubScrubTectonix
	release
	end

FiveIsland_MemorialPillar_EventScript_ReturnedForTM42::
	msgbox FiveIsland_MemorialPillar_Text_StillHaveThingAsMyThanks
	giveitem ITEM_TM42
	goto_if_eq VAR_RESULT, FALSE, FiveIsland_MemorialPillar_EventScript_NoRoomForTM42
	call FiveIsland_MemorialPillar_EventScript_ReceivedTM42
	release
	end

FiveIsland_MemorialPillar_EventScript_Memorial::
	lockall
	goto_if_set FLAG_GOT_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced
	goto_if_set FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR, FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced
	msgbox FiveIsland_MemorialPillar_Text_HereLiesTectonixLemonadeOffering
	checkitem ITEM_LEMONADE
	goto_if_eq VAR_RESULT, TRUE, FiveIsland_MemorialPillar_EventScript_AskPlaceLemonade
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_AskPlaceLemonade::
	msgbox FiveIsland_MemorialPillar_Text_LeaveAnotherLemonadeOffering, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FiveIsland_MemorialPillar_EventScript_PlaceLemonade
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_PlaceLemonade::
	removeitem ITEM_LEMONADE
	msgbox FiveIsland_MemorialPillar_Text_PlacedCanOfLemonade
	closemessage
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 45
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox FiveIsland_MemorialPillar_Text_ThankYouPleaseTakeThis
	giveitem ITEM_TM42
	goto_if_eq VAR_RESULT, FALSE, FiveIsland_MemorialPillar_EventScript_NoRoomForTM42
	call FiveIsland_MemorialPillar_EventScript_ReceivedTM42
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_ReceivedTM42::
	msgbox FiveIsland_MemorialPillar_Text_BeGoodToYourMonsToo
	applymovement LOCALID_MEMORIAL_MAN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	setflag FLAG_GOT_TM42_AT_MEMORIAL_PILLAR
	return

FiveIsland_MemorialPillar_EventScript_NoRoomForTM42::
	setflag FLAG_NO_ROOM_FOR_TM42_AT_MEMORIAL_PILLAR
	msgbox FiveIsland_MemorialPillar_Text_DontHaveRoomForIt
	releaseall
	end

FiveIsland_MemorialPillar_EventScript_MemorialLemonadeAlreadyPlaced::
	msgbox FiveIsland_MemorialPillar_Text_HereLiesTectonix
	releaseall
	end

FiveIsland_MemorialPillar_Text_MiloIntro::
	.string "Soy el mayor de los HERMANOS\n"
	.string "HERMANOS PÁJARO.\p"
	.string "Lo mejor de las aves…\n"
	.string "tiene que ser el pico.$"

FiveIsland_MemorialPillar_Text_MiloDefeat::
	.string "Oh, so sharp!$"

FiveIsland_MemorialPillar_Text_MiloPostBattle::
	.string "Puedes volar a la ISLA CUATRO\n"
	.string "para llegar aquí.$"

FiveIsland_MemorialPillar_Text_ChazIntro::
	.string "Soy el hermano mediano de los\n"
	.string "HERMANOS PÁJARO.\p"
	.string "Lo mejor de las aves…\n"
	.string "tiene que ser el pico.$"

FiveIsland_MemorialPillar_Text_ChazDefeat::
	.string "Flap, flap!$"

FiveIsland_MemorialPillar_Text_ChazPostBattle::
	.string "Había un tipo muy sombrío\n"
	.string "por allá.$"

FiveIsland_MemorialPillar_Text_HaroldIntro::
	.string "Soy el menor de los HERMANOS\n"
	.string "HERMANOS PÁJARO.\p"
	.string "Lo mejor de las aves…\n"
	.string "Es el plumón.$"

FiveIsland_MemorialPillar_Text_HaroldDefeat::
	.string "El plumón es tan suave…\n"
	.string "Me da sueño…$"

FiveIsland_MemorialPillar_Text_HaroldPostBattle::
	.string "Me llena de alegría cuando\n"
	.string "bird POKéMON beg playfully…$"

FiveIsland_MemorialPillar_Text_ScrubScrub::
	.string "Scrub, scrub…$"

FiveIsland_MemorialPillar_Text_YourMonsLookHealthy::
	.string "Hello…\n"
	.string "Your POKéMON look healthy…$"

FiveIsland_MemorialPillar_Text_ThisIsWhereIBuriedMyOnix::
	.string "Aquí enterré a mi ONIX…\n"
	.string "Se llamaba TECTONIX…$"

FiveIsland_MemorialPillar_Text_HereLiesTectonixLemonadeOffering::
	.string "“Aquí yace TECTONIX” está grabado\n"
	.string "sobre una roca.\p"
	.string "Hay una LIMONADA colocada como\n"
	.string "ofrenda frente a la tumba.$"

FiveIsland_MemorialPillar_Text_LeaveAnotherLemonadeOffering::
	.string "¿Quieres dejar otra\n"
	.string "LIMONADA como ofrenda?$"

FiveIsland_MemorialPillar_Text_PlacedCanOfLemonade::
	.string "{PLAYER} puso una lata de LIMONADA\n"
	.string "frente a la tumba.$"

FiveIsland_MemorialPillar_Text_ThankYouPleaseTakeThis::
	.string "Gr-gracias...\p"
	.string "Era la favorita de mi TECTONIX.\n"
	.string "drink…\p"
	.string "Ni siquiera te conozco, pero tu\n"
	.string "acto de bondad…\p"
	.string "Eso me animó un poco.\p"
	.string "¿Puedes tomar esto como mi\n"
	.string "thanks?$"

FiveIsland_MemorialPillar_Text_BeGoodToYourMonsToo::
	.string "Please be good to your POKéMON,\n"
	.string "de vergüenza.$"

FiveIsland_MemorialPillar_Text_DontHaveRoomForIt::
	.string "Si no tienes espacio para ello,\n"
	.string "Lo guardaré hasta la próxima.$"

FiveIsland_MemorialPillar_Text_StillHaveThingAsMyThanks::
	.string "Ah, eres tú de aquella vez…\p"
	.string "Todavía tengo esa cosa que quería\n"
	.string "darte como agradecimiento.$"

FiveIsland_MemorialPillar_Text_ScrubScrubTectonix::
	.string "Scrub, scrub…\p"
	.string "… … …\n"
	.string "TECTONIX…$"

FiveIsland_MemorialPillar_Text_HereLiesTectonix::
	.string "Rocas y piedras están apiladas\n"
	.string "con cuidado como un hito.\p"
	.string "“Aquí yace TECTONIX” está grabado\n"
	.string "sobre una roca.$"

