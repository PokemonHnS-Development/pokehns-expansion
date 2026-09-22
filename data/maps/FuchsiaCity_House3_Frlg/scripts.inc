FuchsiaCity_House3_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House3_EventScript_MoveDeleter::
	lock
	faceplayer
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter::
	msgbox FuchsiaCity_House3_Text_WhichMonShouldForgetMove
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, FuchsiaCity_House3_EventScript_CancelForgetMove
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FuchsiaCity_House3_EventScript_CantForgetMoveEgg
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, FuchsiaCity_House3_EventScript_CantForgetOnlyMove
	msgbox FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House3_EventScript_ForgetMove
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ForgetMove::
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely
	release
	end

FuchsiaCity_House3_EventScript_CantForgetOnlyMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonOnlyKnowsOneMove
	release
	end

FuchsiaCity_House3_EventScript_CantForgetMoveEgg::
	msgbox FuchsiaCity_House3_Text_NoEggShouldKnowMoves
	release
	end

FuchsiaCity_House3_EventScript_CancelForgetMove::
	msgbox FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves
	release
	end

FuchsiaCity_House3_Text_WouldYouLikeToForgetMove::
	.string "Uh…\n"
	.string "Oh, sí, soy el BORRADOR DE MOVS.\p"
	.string "I can make POKéMON forget their\n"
	.string "tipo NORMAl.\p"
	.string "¿Quieres que haga eso?$"

FuchsiaCity_House3_Text_WhichMonShouldForgetMove::
	.string "¿Qué POKéMON debería olvidar un\n"
	.string "move?$"

FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten::
	.string "¿Qué movimiento se debe olvidar?$"

FuchsiaCity_House3_Text_MonOnlyKnowsOneMove::
	.string "{STR_VAR_1} parece conocer solo\n"
	.string "move…$"

FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten::
	.string "¡Hm! ¿{STR_VAR_2} de {STR_VAR_1}?\n"
	.string "¿Ese movimiento debe olvidarse?$"

FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely::
	.string "¡Funcionó a la perfección!\p"
	.string "{STR_VAR_1} ha olvidado\n"
	.string "{STR_VAR_2} por completo.$"

FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves::
	.string "Vuelve si hay otros\n"
	.string "movimientos que olvidar.$"

FuchsiaCity_House3_Text_NoEggShouldKnowMoves::
	.string "¿Qué?\n"
	.string "Ningún HUEVO debe saber movimientos.$"

