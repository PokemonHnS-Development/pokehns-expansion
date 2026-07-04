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

SnowsweptB_EventScript_SwimmerMaura::
    trainerbattle_single TRAINER_MAURA_HNS, SnowsweptB_Text_SwimmerMaura_Seen, SnowsweptB_Text_SwimmerMaura_Beaten
    msgbox SnowsweptB_Text_SwimmerMaura_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_SwimmerMaura_Seen:
    .string "Hey! Get out of the way!\n"
    .string "I'm swimin' here!$"

SnowsweptB_Text_SwimmerMaura_Beaten:
    .string "Alright, alright.\n"
    .string "I'll watch where I'm goin' geeze..$"

SnowsweptB_Text_SwimmerMaura_After:
    .string "I came all the way here from Unova\n"
    .string "to train and enjoy the local eats.$"

SnowsweptB_EventScript_SwimmerMasoto::
    trainerbattle_single TRAINER_MASOTO_HNS, SnowsweptB_Text_SwimmerMasoto_Seen, SnowsweptB_Text_SwimmerMasoto_Beaten
    msgbox SnowsweptB_Text_SwimmerMasoto_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_SwimmerMasoto_Seen:
    .string "This hotspring makes an\n"
    .string "exceptional place to train!\p"
    .string "Let's train together!$"

SnowsweptB_Text_SwimmerMasoto_Beaten:
    .string "Your teamwork is awe inspiring!\n"
    .string "Have you ever thought about\l"
    .string "becoming a couch before?$"

SnowsweptB_Text_SwimmerMasoto_After:
    .string "Make sure to take proper breaks inbetween\n"
    .string "training seasions!$"

SnowsweptB_EventScript_TriatheleteJoshua::
    faceplayer
    trainerbattle_single TRAINER_JOSHUA2_HNS, SnowsweptB_Text_TriatheleteJoshua_Seen, SnowsweptB_Text_TriatheleteJoshua_Beaten
    msgbox SnowsweptB_Text_TriatheleteJoshua_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_TriatheleteJoshua_Seen:
    .string "Yeah!\p"
    .string "Let's get pumped up!!$"

SnowsweptB_Text_TriatheleteJoshua_Beaten:
    .string "Maybe I got a little\n"
    .string "too pumped there..$"
  
SnowsweptB_Text_TriatheleteJoshua_After:
    .string "Maybe I need to drink\n"
    .string "some more nitro fuel..$"

SnowsweptB_EventScript_CamperDennis::
    trainerbattle_single TRAINER_DENNIS2_HNS, SnowsweptB_Text_CamperDennis_Seen, SnowsweptB_Text_CamperDennis_Beaten
    msgbox SnowsweptB_Text_CamperDennis_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_CamperDennis_Seen:
    .string "Yeah!\p"
    .string "Let's get pumped up!!$"

SnowsweptB_Text_CamperDennis_Beaten:
    .string "Maybe I got a little\n"
    .string "too pumped there..$"
  
SnowsweptB_Text_CamperDennis_After:
    .string "Maybe I need to drink\n"
    .string "some more nitro fuel..$"

Snowswept_EventScript_Item_SPLASHPLATE::
    finditem ITEM_SPLASH_PLATE
    addvar VAR_PLATECOUNTER, 1
    end

Snowswept_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

Snowswept_EventScript_Item_LavaCookie::
    finditem ITEM_LAVA_COOKIE
    end

SnowsweptB_EventScript_Sign::
    lock
    msgbox Snowswept_Text_TrainerTips
    release
    end

Snowswept_Text_TrainerTips:
    .string "Trainer Tips!\p"
    .string "Always fully explore\n"
    .string "your surroundings!\l"
    .string "You'll never know what\l"
    .string "you might find out there!$"