@ Hoenn & Seek (part 20a): overworld Pokémon placed by tools/hoenn/gen_hoenn_ow_mons.py.
@ Talking to one turns it toward you and plays its cry.
HoennSeek_EventScript_OWMon::
	lock
	faceplayer
	special HoennOWMonCry
	waitmoncry
	release
	end
