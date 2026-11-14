FuchsiaCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_PokemonCenter_OnTransition
	.byte 0

FuchsiaCity_PokemonCenter_OnTransition::
	setflag FLAG_TEMP_1
	setrespawn HEAL_LOCATION_FUCHSIA_CITY_HNS
	end

FuchsiaCity_PokemonCenter_EventScript_CooltrainerM::
	msgbox FuchsiaCity_PokemonCenter1F_Text_CooltrainerM, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox FuchsiaCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_EventScript_JanineClone::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAPOKECENTER_WOMAN, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAPOKECENTER_WOMAN
	clearflag FLAG_TEMP_1
	addobject LOCALID_FUCHSIAPOKECENTER_JASMINE
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator2, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAPOKECENTER_JASMINE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAPOKECENTER_JASMINE
	clearflag FLAG_TEMP_2
	addobject LOCALID_FUCHSIAPOKECENTER_WOMAN
	applymovement LOCALID_FUCHSIAPOKECENTER_WOMAN, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	release
	closemessage
	end

FuchsiaCity_PokemonCenter1F_Text_CooltrainerM:
	.string "היי! יש לך פוקדקס\n"
	.string "מסוג חדש לגמרי.\p"
	.string "פרופ' אוק נתן לך אותו?$"

FuchsiaCity_PokemonCenter1F_Text_CooltrainerF:
	.string "קיבלתי הלם רציני במכון.\p"
	.string "היו שם המון בנות שנראו\n"
	.string "בדיוק אותו דבר.$"

FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1:
	.string "אני ג'אנין! הוקוס פוקוס… פוף!$"

FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator2:
	.string "רואה? עכשיו אני נראית בדיוק כמוה!$"

