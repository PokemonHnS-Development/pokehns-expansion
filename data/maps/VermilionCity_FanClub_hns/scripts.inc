VermilionCity_FanClub_hns_MapScripts::
	.byte 0

VermilionCity_FanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_eq VAR_FAN_CLUB_GUY, 1, VermilionCity_FanClub_EventScript_ChairmanAfter
	msgbox PokemonFanClub_Text_Chairman_Intro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_FanClub_EventScript_ChairmanRefused
	msgbox PokemonFanClub_Text_Chairman_Rapidash, MSGBOX_DEFAULT
	msgbox PokemonFanClub_Text_Chairman_Gift, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_FAN_CLUB_GUY, 1
	msgbox PokemonFanClub_Text_Chairman_Candy, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ChairmanRefused::
	msgbox PokemonFanClub_Text_Chairman_Disappointed, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ChairmanAfter::
	msgbox PokemonFanClub_Text_Chairman_MoreTales, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_Woman1::
	msgbox PokemonFanClub_Text_Receptionist, MSGBOX_NPC
	end

VermilionCity_FanClub_EventScript_Woman2::
	msgbox PokemonFanClub_Text_Teacher, MSGBOX_NPC
	end

VermilionCity_FanClub_EventScript_ClefairyGuy::
	lock
	faceplayer
	msgbox PokemonFanClub_Text_ClefairyGuy_Adorable, MSGBOX_DEFAULT
	goto_if_eq VAR_FAN_CLUB_CLEFAIRY, 1, VermilionCity_FanClub_EventScript_ClefairyGiveDoll
	goto_if_ge VAR_FAN_CLUB_CLEFAIRY, 2, VermilionCity_FanClub_EventScript_ClefairyAfter
	msgbox PokemonFanClub_Text_ClefairyGuy_MakingDo, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ClefairyGiveDoll::
	msgbox PokemonFanClub_Text_ClefairyGuy_ReturnDoll, MSGBOX_DEFAULT
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL
	removeobject LOCALID_FAN_CLUB_CLEFAIRY_DOLL
	fadescreenswapbuffers FADE_FROM_BLACK
	giveitem ITEM_LOST_ITEM
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_FAN_CLUB_CLEFAIRY, 2
	msgbox PokemonFanClub_Text_ClefairyGuy_GoingToGetOne, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_ClefairyAfter::
	msgbox PokemonFanClub_Text_ClefairyGuy_GoingToGetOne, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_FanClub_EventScript_Bayleef::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BAYLEEF, CRY_MODE_NORMAL
	msgbox PokemonFanClub_Text_Bayleef, MSGBOX_DEFAULT
	waitmoncry
	release
	end


PokemonFanClub_Text_Chairman_Intro:
	.string "Soy el PRESIDENTE del CLUB\n"
	.string "de FANS de POKéMON.\p"
	.string "He criado más de 150 POKéMON.\p"
	.string "Soy muy exigente en cuanto a\n"
	.string "POKéMON planta.\p"
	.string "¿Viniste solo para oír hablar\n"
	.string "de mis POKéMON?$"

PokemonFanClub_Text_Chairman_Rapidash:
	.string "¡Bien! ¡Entonces escucha!\p"
	.string "Así que... mi RAPIDASH favorito...\p"
	.string "Es... lindo... adorable... listo...\n"
	.string "insoportablemente...\l"
	.string "además... increíble... oh... crees\l"
	.string "so?...\l"
	.string "que es mucho... salvaje... bello...\l"
	.string "amable...\l"
	.string "¡Me encanta!\p"
	.string "Abrazarlo... al... dormir... cálido\n"
	.string "y cariñoso...\l"
	.string "Ah, y... espectacular...\l"
	.string "radiante... simplemente divino...\p"
	.string "¡Uy! ¡Mira la hora!\n"
	.string "¡Te he retenido demasiado tiempo!$"

PokemonFanClub_Text_Chairman_Gift:
	.string "Gracias por escucharme.\n"
	.string "¡Quiero que tengas esto!$"

PokemonFanClub_Text_Chairman_Candy:
	.string "Es un CARAMELO RARO que hace\n"
	.string "POKéMON más fuertes.\p"
	.string "Prefiero que mis POKéMON sean\n"
	.string "fuertes luchando, así que tú\l"
	.string "puedes quedártelo.$"

PokemonFanClub_Text_Chairman_MoreTales:
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Vienes a verme por mi\n"
	.string "POKéMON otra vez?\p"
	.string "¿No? Oh... Tenía más historias\n"
	.string "que contar...$"

PokemonFanClub_Text_Chairman_Disappointed:
	.string "Qué decepción...\p"
	.string "Vuelve si quieres escuchar.$"

PokemonFanClub_Text_Receptionist:
	.string "Nuestro PRESIDENTE es muy vocal\n"
	.string "cuando habla de POKéMON...$"

@=Clefairy=Guy=========================================================================================================
PokemonFanClub_Text_ClefairyGuy_Adorable:
	.string "Amo cómo CLEFAIRY mueve el\n"
	.string "dedo cuando intenta usar\l"
	.string "METRÓNOMO.\p"
	.string "¡Es tan adorable!$"

PokemonFanClub_Text_ClefairyGuy_MakingDo:
	.string "Amo a CLEFAIRY, pero jamás\n"
	.string "podría atrapar uno.\p"
	.string "Así que me conformo con un\n"
	.string "MUÑECO POKéMON que encontré.$"

PokemonFanClub_Text_ClefairyGuy_ReturnDoll:
	.string "Ah, ya veo. La niña que perdió\n"
	.string "este MUÑECO POKéMON está triste...\p"
	.string "Vale. ¿Podrías llevar este\n"
	.string "MUÑECO POKéMON a esa pobre niña?\p"
	.string "Algún día haré amigo a un\n"
	.string "CLEFAIRY real por mi cuenta!$"

PokemonFanClub_Text_ClefairyGuy_GoingToGetOne:
	.string "Ya verás. Voy a conseguir un\n"
	.string "un CLEFAIRY real como amigo.$"

@============================================================================================================================

PokemonFanClub_Text_Teacher:
	.string "¡Mira a mi querido BAYLEEF!\p"
	.string "¡La hoja de su cabeza es linda!$"

PokemonFanClub_Text_ClefairyDoll:
	.string "¡Es un CLEFAIRY! ¿Eh?\p"
	.string "Ah, cierto. Es un MUÑECO\n"
	.string "POKé de CLEFAIRY.$"

PokemonFanClub_Text_Bayleef:
	.string "BAYLEEF: Li liif!$"

PokemonFanClub_Text_Listen:
	.string "Escuchemos todos con respeto a\n"
	.string "otros entrenadores.$"

PokemonFanClub_Text_Bragging:
	.string "¡Si alguien presume, presume\n"
	.string "tú también!$"
