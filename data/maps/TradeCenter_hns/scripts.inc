TradeCenter_hns_MapScripts::
	.byte 0

TradeCenter_EventScript_Attendant_hns::
	special Script_FacePlayer
	msgbox TradeCenter_Text_TakeSeatStartTrade, MSGBOX_DEFAULT
	special Script_ClearHeldMovement
	closemessage
	end
