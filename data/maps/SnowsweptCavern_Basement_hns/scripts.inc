SnowsweptCavern_Basement_hns_MapScripts::
	.byte 0


SnowsweptB_EventScript_PsychicRaphael::
    trainerbattle_single TRAINER_RAPHAEL_HNS, SnowsweptB_Text_PsychicRaphael_Seen, SnowsweptB_Text_PsychicRaphael_Beaten
    msgbox SnowsweptB_Text_PsychicRaphael_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_PsychicRaphael_Seen:
    .string "I foresaw our encounter\n"
    .string "eons ago.\l"
    .string "You're fate is sealed.$"

SnowsweptB_Text_PsychicRaphael_Beaten:
    .string "How?!\n"
    .string "Are you able to bend fate itself?$"

SnowsweptB_Text_PsychicRaphael_After:
    .string "I can't belive my visions\n"
    .string "were wrong...$"