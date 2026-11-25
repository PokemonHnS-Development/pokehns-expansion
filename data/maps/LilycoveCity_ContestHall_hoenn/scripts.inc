@ Hoenn & Seek: Lilycove's own walk-in contest hall (same floor plan as
@ LilycoveCity_ContestHall_hns, whose stage scripts it reuses). The chatty
@ NPCs are their Viridian counterparts' twins.

LilycoveCity_ContestHall_hoenn_MapScripts::
	.byte 0

HoennSeek_EventScript_TwinHallOldMan::
	msgbox HoennSeek_Text_TwinHallOldMan, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinHallWorker::
	msgbox HoennSeek_Text_TwinHallWorker, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinHallPicnicker::
	msgbox HoennSeek_Text_TwinHallPicnicker, MSGBOX_NPC
	end

HoennSeek_EventScript_TwinHallSailor::
	msgbox HoennSeek_Text_TwinHallSailor, MSGBOX_NPC
	end

HoennSeek_Text_TwinHallOldMan:
	.string "This POKéMON won the BEAUTY CONTEST\n"
	.string "before. Today it won SMARTNESS!\p"
	.string "My twin's POKéMON did the same thing\n"
	.string "in VIRIDIAN. Same day. Same species.\p"
	.string "We've agreed never to speak of it.$"

HoennSeek_Text_TwinHallWorker:
	.string "I've entered a bunch of CONTESTS to\n"
	.string "see how things work.\p"
	.string "Cool moves win COOLNESS CONTESTS.\n"
	.string "Cute moves win CUTENESS CONTESTS.\p"
	.string "And everyone in this hall has a twin\n"
	.string "in the VIRIDIAN hall.\p"
	.string "I'm pretty sure that last one isn't\n"
	.string "a game mechanic.$"

HoennSeek_Text_TwinHallPicnicker:
	.string "That young man who won earlier had\n"
	.string "a whole bunch of {POKEBLOCK}S.\p"
	.string "Or was that his twin? I can never\n"
	.string "tell which hall I'm in anymore.$"

HoennSeek_Text_TwinHallSailor:
	.string "Whoa, isn't this place humongous!\p"
	.string "It's exactly as humongous as the hall\n"
	.string "in VIRIDIAN. To the tile. I checked.\p"
	.string "I had the time. My twin's sailing my\n"
	.string "shift today.$"
