@ Hoenn & Seek 2.0, lane B: parts 31b, 34a, 29, 30a, 30b, 33, 36 and 35a (Kanto, the Safari Zone, the birds, Mewtwo/Mew, Hoenn's weather legendaries).
@ Lane B's scenes, phone calls and texts go in this file (or a new data/scripts/hoenn_*.inc
@ of its own); the other lane has its own file, so the two never edit the same lines.
@ Rules: hoenn-docs/lanes/README.md. C code: src/hoenn_lane_b.c.

@ ---------------------------------------------------------------- event calls

@ The PokéGear event-call switch (HoennSeek_EventScript_PhoneEvent, hoenn_phone.inc)
@ falls through to lane A's cases, then to lane B's. Add one case per call:
@ 	case HOENN_CALL_X, HoennSeek_EventScript_CallX
HoennSeek_EventScript_PhoneEventLaneB::
	switch VAR_0x8004
	releaseall @ no call matched: the end of the chain
	end
