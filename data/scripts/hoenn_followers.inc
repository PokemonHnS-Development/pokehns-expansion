@ Hoenn & Seek 2.0 (part 4b): trainer followers.
@ tools/hoenn/gen_hoenn_followers.py puts a Pokémon next to gym leaders, the Elite Four and
@ Red (data/hoenn/trainer_followers.json). Talking to one plays its cry, like the overworld
@ Pokémon in Hoenn's scenery (HoennSeek_EventScript_OWMon); this is a separate script so
@ each generator only replaces its own objects.
HoennSeek_EventScript_TrainerFollower::
	lock
	faceplayer
	special HoennOWMonCry
	waitmoncry
	release
	end
