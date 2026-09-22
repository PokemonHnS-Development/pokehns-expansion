VermilionCity_Mart_Frlg_MapScripts::
	.byte 0

VermilionCity_Mart_EventScript_CooltrainerF::
	msgbox VermilionCity_Mart_Text_MonsGoodOrBadDependingOnTrainer, MSGBOX_NPC
	end

VermilionCity_Mart_EventScript_BaldingMan::
	msgbox VermilionCity_Mart_Text_TeamRocketAreWickedPeople, MSGBOX_NPC
	end

VermilionCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VermilionCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
VermilionCity_Mart_Items::
	.2byte ITEM_POKE_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

VermilionCity_Mart_Text_TeamRocketAreWickedPeople::
	.string "Hay personas malvadas que\n"
	.string "use POKéMON for criminal acts.\p"
	.string "El TEAM ROCKET trafica con\n"
	.string "POKéMON, for example.\p"
	.string "They also abandon POKéMON that\n"
	.string "consideran impopulares o inútiles.\p"
	.string "Ese es el tipo de gente horrible\n"
	.string "que son, el EQUIPO ROCKET.$"

VermilionCity_Mart_Text_MonsGoodOrBadDependingOnTrainer::
	.string "I think POKéMON can be good or\n"
	.string "malo. Depende del ENTRENADOR.$"

