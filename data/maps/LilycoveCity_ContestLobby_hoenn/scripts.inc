@ Hoenn & Seek: Lilycove's own contest lobby. Same floor plan, staff and
@ contest system as HnS's Viridian lobby (LilycoveCity_ContestLobby_hns), whose
@ scripts it reuses. The ambient NPCs are the Viridian NPCs' twins.

LilycoveCity_ContestLobby_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_ContestLobby_hoenn_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_ContestLobby_OnFrame_hns
	.byte 0

@ Contests are held on HnS's shared stages; this flag sends you back here.
LilycoveCity_ContestLobby_hoenn_OnTransition:
	setflag FLAG_HOENN_LILYCOVE_CONTEST
	end

@ Called from ContestHall_EventScript_SetExitWarp_hns
HoennSeek_EventScript_ContestSetExitWarp::
	goto_if_eq VAR_CONTEST_TYPE, CONTEST_TYPE_LINK, HoennSeek_EventScript_ContestSetExitWarpLink
	warp MAP_LILYCOVE_CITY_CONTEST_LOBBY_HOENN, 14, 4
	waitstate
	end

HoennSeek_EventScript_ContestSetExitWarpLink::
	warp MAP_LILYCOVE_CITY_CONTEST_LOBBY_HOENN, 15, 4
	waitstate
	end

HoennSeek_EventScript_TwinReceptionist::
	goto_if_set FLAG_HOENN_MET_CONTEST_TWIN, LilycoveCity_ContestLobby_EventScript_ContestReceptionist_hns
	lock
	faceplayer
	msgbox HoennSeek_Text_TwinReceptionist, MSGBOX_DEFAULT
	setflag FLAG_HOENN_MET_CONTEST_TWIN
	release
	goto LilycoveCity_ContestLobby_EventScript_ContestReceptionist_hns

HoennSeek_EventScript_TwinBlackBelt::
	msgbox HoennSeek_Text_TwinBlackBelt, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinSailor::
	msgbox HoennSeek_Text_TwinSailor, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinGentleman::
	msgbox HoennSeek_Text_TwinGentleman, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinFisherman::
	msgbox HoennSeek_Text_TwinFisherman, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinFatMan::
	msgbox HoennSeek_Text_TwinFatMan, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinGameboyKid::
	msgbox HoennSeek_Text_TwinGameboyKid, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinLittleGirl::
	msgbox HoennSeek_Text_TwinLittleGirl, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinTwin::
	msgbox HoennSeek_Text_TwinTwin, MSGBOX_NPC
	end

HoennSeek_Text_TwinReceptionist:
	.string "Welcome to the POKéMON CONTEST HALL\n"
	.string "of LILYCOVE CITY!\p"
	.string "…You look like you've seen a ghost.\n"
	.string "You must have met my twin sister at\l"
	.string "the VIRIDIAN desk.\p"
	.string "We keep one ledger between us, so\n"
	.string "your ranks count at both halls.\p"
	.string "And no, I won't tell you which of us\n"
	.string "is older. It's a sore subject.$"

HoennSeek_Text_TwinBlackBelt:
	.string "My twin brother enters CONTESTS over\n"
	.string "in VIRIDIAN.\p"
	.string "He thinks HIS POKéMON is the cutest\n"
	.string "being in all existence.\p"
	.string "He's wrong. Mine is.\n"
	.string "The world will know! Uheheheh.$"

HoennSeek_Text_TwinSailor:
	.string "I stroll in here every day to look\n"
	.string "at all the POKéMON.\p"
	.string "My twin does the same in VIRIDIAN.\n"
	.string "We compare notes by phone.\p"
	.string "So far we've seen the exact same\n"
	.string "POKéMON every single day. Spooky.$"

HoennSeek_Text_TwinGentleman:
	.string "Ah, a CONTEST! A feast for the eyes!\p"
	.string "My twin paints the VIRIDIAN hall.\n"
	.string "We swapped canvases once, and\l"
	.string "nobody noticed. Not even the MUSEUM.$"

HoennSeek_Text_TwinFisherman:
	.string "I lavished care on this POKéMON,\n"
	.string "day in and day out.\p"
	.string "My twin did the very same thing,\n"
	.string "with the very same species, in\l"
	.string "VIRIDIAN.\p"
	.string "If we both win today, I'm asking\n"
	.string "for a rematch… between our twins.$"

HoennSeek_Text_TwinFatMan:
	.string "The TOUGHNESS CONTEST is extreme,\n"
	.string "man! I swoon!\p"
	.string "My twin swoons at the VIRIDIAN one.\n"
	.string "Between us, we cover every show.\l"
	.string "We're very efficient swooners.$"

HoennSeek_Text_TwinGameboyKid:
	.string "I made {POKEBLOCK}S with Mom, Dad, Big\n"
	.string "Sister, and Big Sister's twin.\p"
	.string "Wait. Is everyone in this building\n"
	.string "somebody's twin?\p"
	.string "Am I a twin?! I have to call Mom.$"

HoennSeek_Text_TwinLittleGirl:
	.string "My twin got a {POKEBLOCK} CASE at the\n"
	.string "VIRIDIAN desk, so I came here and\l"
	.string "got one too!\p"
	.string "Mom says matching stuff is the only\n"
	.string "thing that stops us arguing.$"

HoennSeek_Text_TwinTwin:
	.string "I'm a twin! My other half is making\n"
	.string "{POKEBLOCK}S in VIRIDIAN right now.\p"
	.string "Back home, everyone points at us.\n"
	.string "Here, nobody even looks twice.\p"
	.string "It's nice not being the only twins\n"
	.string "in the room for once!$"
