SSAnne_1F_Room6_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room6_EventScript_Woman::
	lock
	faceplayer
	msgbox SSAnne_1F_Room6_Text_TakeAShortRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_1F_Room6_EventScript_DeclineHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SSAnne_1F_Room6_Text_GladEveryoneIsRefreshed
	release
	end

SSAnne_1F_Room6_EventScript_DeclineHeal::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SSAnne_1F_Room6_EventScript_DeclineHealMale
	msgbox SSAnne_1F_Room6_Text_SorryYouLookLikeMySister
	release
	end

SSAnne_1F_Room6_EventScript_DeclineHealMale::
	msgbox SSAnne_1F_Room6_Text_SorryYouLookLikeMyBrother
	release
	end

SSAnne_1F_Room6_Text_TakeAShortRest::
	.string "Te ves cansado. ¿Quieres\n"
	.string "descansar un poco?$"

SSAnne_1F_Room6_Text_GladEveryoneIsRefreshed::
	.string "Me alegra ver que todos están\n"
	.string "con buen ánimo y energía.$"

SSAnne_1F_Room6_Text_SorryYouLookLikeMyBrother::
	.string "Perdón por preocuparme tanto.\n"
	.string "Te pareces a mi hermanito…$"

SSAnne_1F_Room6_Text_SorryYouLookLikeMySister::
	.string "Perdón por preocuparme tanto.\n"
	.string "Pareces mi hermana menor…$"

