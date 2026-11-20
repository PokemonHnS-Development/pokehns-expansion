SSAqua_PlayersRoom_hns_MapScripts::
	.byte 0

SSAquaRooms_EventScript_Bed::
	specialvar VAR_RESULT, IsPokecenterChallengeActivated
	goto_if_eq VAR_RESULT, TRUE, SSAquaRooms_EventScript_Bed_PokecenterChallenge
	lockall
	msgbox SSAquaRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

SSAquaRooms_EventScript_Bed_PokecenterChallenge::
	msgbox SSAquaRooms_Text_TakeRestOnBed_PokecenterChallenge, MSGBOX_DEFAULT
	closemessage
	release
	end


SSAquaRooms_Text_TakeRestOnBed_PokecenterChallenge:
	.string "סליחה, אתגר מרכז הפוקימון\n"
	.string "פעיל במשחק שלך!$"

SSAquaRooms_Text_TakeRestOnBed:
	.string "יש כאן מיטה…\n"
	.string "אפשר לנוח קצת.$"
