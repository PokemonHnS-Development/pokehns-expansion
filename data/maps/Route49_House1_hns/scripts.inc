Route49_House1_hns_MapScripts::
	.byte 0

Route49_House1_EventScripts_OldMan::
    lock
	msgbox Route49_OLdMan_Text MSGBOX_DEFAULT
	release
	end

Route49_OLdMan_Text:
    .string "He appears to be resting blissfully..\n"
	.string "Better leave him be..$"


Route49_House1_EventScripts_OldWoman::
    lock
	faceplayer
	msgbox Route49_OldWoman_Text MSGBOX_DEFAULT
	release
	end

Route49_OldWoman_Text:
    .string "Oh..hello deary..\n"
	.string "I'm making my husband some\l"
	.string "soup while he rests...$"