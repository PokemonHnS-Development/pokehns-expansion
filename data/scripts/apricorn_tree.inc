ApricornTreeScript::
	lock
	faceplayer
	message ApricornTree_Text_Intro
	waitmessage
	waitbuttonpress
	special ObjectEventInteractionGetApricornTreeData
	goto_if_gt VAR_0x8005, 0, ApricornTree_EventScript_WantToPick
	message ApricornTree_Text_Empty
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_EventScript_WantToPick::
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox ApricornTree_Text_WantToPick, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, ApricornTree_EventScript_PickApricorn
	goto_if_eq VAR_RESULT, NO, ApricornTree_EventScript_CancelPickingApricorn

.set APRICORN_NORMAL_BAG_FULL, 0
.set APRICORN_NORMAL_SPACE_IN_BAG, 1

ApricornTree_EventScript_PickApricorn::
	special ObjectEventInteractionPickApricornTree
	call EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq VAR_0x8006, APRICORN_NORMAL_BAG_FULL, ApricornTree_EventScript_PocketFull
	message ApricornTree_Text_PickedTheApricorn
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	copyvar VAR_0x8006 VAR_0x8004
.endif
	delay 10
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	showberrydescription
.endif
	playfanfare MUS_OBTAIN_BERRY
	waitmessage
	waitfanfare
	waitbuttonpress
	message ApricornTree_Text_PutAwayApricorn
	waitmessage
	waitbuttonpress
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hideitemdescription
.endif
	release
	end

ApricornTree_EventScript_PocketFull::
	message ApricornTree_Text_PocketFull
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_EventScript_CancelPickingApricorn::
	message ApricornTree_Text_ApricornLeftUnpicked
	waitmessage
	waitbuttonpress
	release
	end

ApricornTree_Text_Intro:
	.string "¡Es un árbol de Bellotas!$"

ApricornTree_Text_Empty:
	.string "No hay Bellotas...$"

ApricornTree_Text_WantToPick:
	.string "...¡Es {STR_VAR_2} {STR_VAR_1}!\n"
	.string "¿Quieres recoger la\l"
	.string "¿{STR_VAR_1}?$"

ApricornTree_Text_PickedTheApricorn:
	.string "{PLAYER} obtuvo\n"
	.string "{STR_VAR_2} {STR_VAR_1}.$"

ApricornTree_Text_PutAwayApricorn:
	.string "{PLAYER} guardó la\n"
	.string "{STR_VAR_1} en\l"
	.string "el BOLSILLO {STR_VAR_3} de la BOLSA.$"

ApricornTree_Text_PocketFull:
	.string "El BOLSILLO {STR_VAR_3} está lleno.\p"
	.string "{PLAYER} desistió de la\n"
	.string "{STR_VAR_1}...$"

ApricornTree_Text_ApricornLeftUnpicked:
	.string "{PLAYER} desistió de la\n"
	.string "{STR_VAR_1}...$"
