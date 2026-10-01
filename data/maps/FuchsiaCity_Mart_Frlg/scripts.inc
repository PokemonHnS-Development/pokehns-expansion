FuchsiaCity_Mart_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Mart_EventScript_CooltrainerF::
	msgbox FuchsiaCity_Mart_Text_DidYouTryXSpeed, MSGBOX_NPC
	end

FuchsiaCity_Mart_EventScript_Gentleman::
	msgbox FuchsiaCity_Mart_Text_DontTheyHaveSafariZonePennants, MSGBOX_NPC
	end

FuchsiaCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FuchsiaCity_Mart_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
FuchsiaCity_Mart_Items::
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_NONE
	release
	end

FuchsiaCity_Mart_Text_DontTheyHaveSafariZonePennants::
	.string "¿No tienen banderines\n"
	.string "promocionar la ZONA SAFARI?\p"
	.string "¿Qué tal unas linternas de papel?\n"
	.string "¿Acaso no hay ni calendarios?$"

FuchsiaCity_Mart_Text_DidYouTryXSpeed::
	.string "¿Probaste la VELOCIDAD X?\n"
	.string "Acelera a un POKéMON en batalla.$"

