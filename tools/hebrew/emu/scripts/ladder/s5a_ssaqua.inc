@ Story step 5a: after the League. Elm's S.S. Ticket, Oak's National Pokedex at Olivine port, the
@ S.S. Aqua's maiden voyage to Vermilion. Runs on top of ladder 4 (Hall of Fame done, Elm's
@ after-League call already played: VAR_NEWBARK_TOWN_STATE 7, VAR_NEWBARKTOWN_LABSTATE 10).
@ The arrival itself is `rungoto SSAqua_1F_EventScript_LeaveBoat` (the ROM's Kanto flagheap
@ plus the warp to Vermilion port).

@ Elm's lab: the S.S. Ticket (NewBarkTown_Lab_EventScript_ElmSSTicket:483-490)
	additem ITEM_SS_TICKET
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
@ Olivine port: Oak upgrades the Pokedex (OlivineCity_PortInside_EventScript_Oak:10-40)
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_HIDE_OLIVINE_PORT_OAK
@ Olivine port: boarding (OlivinePort_EventScript_Sailor_MaidenVoyage:190-200)
	setvar VAR_SSAQUA_STATE, 1
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setflag FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER
	clearflag FLAG_HIDE_SSAQUA_SAILOR
	clearflag FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER
@ On board: the grandpa, Stanly, the granddaughter, the reunion, arrival
@ (SSAqua_1F_Trigger_Grandpa:...-196, SSAqua_RoomNW_EventScript_Stanly:26,
@ SSAqua_CaptainsRoom_EventScript_Granddaughter:28-30, SSAqua_RoomSSE_EventScript_ReuinionScene:39,
@ SSAqua_1F_EventScript_Arrived:7-20)
	setflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setflag FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER
	clearflag FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER
	setvar VAR_SSAQUA_STATE, 6
	end
