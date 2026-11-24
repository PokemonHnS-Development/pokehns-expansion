@ Hoenn & Seek: legendary sites sealed until 2.0.
@ Everything that seals them lives in one commit so it can be reverted:
@   - data/hoenn/exclude.json drops the sites' maps (Sky Pillar, Sealed Chamber,
@     Regi caves, Terra/Marine Cave, Seafloor Cavern, Cave of Origin, islands),
@     so tools/mapjson parks their entrance warps at 0x7FFF;
@   - each entrance gets a sign event running HoennSeek_EventScript_SealedSite
@     (Routes 105, 111, 120, 131, Sootopolis, Underwater Route 128) or a step
@     trigger (Underwater Route 134);
@   - Route 130 never shows Mirage Island, Sootopolis never swaps in the
@     legends layout, and the Weather Institute never starts abnormal weather.
HoennSeek_EventScript_SealedSite::
	lockall
	msgbox HoennSeek_Text_SealedSite, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_Text_SealedSite:
	.string "The way in is sealed tight.\p"
	.string "It feels as if something is sleeping\n"
	.string "deep inside…$"

@ For entrances you walk onto (the Sealed Chamber hole on Underwater Route 134).
HoennSeek_EventScript_SealedSiteStepBack::
	lockall
	msgbox HoennSeek_Text_SealedSite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, HoennSeek_Movement_StepBackUp
	waitmovement 0
	releaseall
	end

HoennSeek_Movement_StepBackUp:
	walk_up
	step_end
