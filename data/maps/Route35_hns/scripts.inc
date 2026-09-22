Route35_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route35_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route35_OnTransition: 
	callnative SetTimeBasedEncounters
	end	

Route35_EventScript_CamperIvan::
	trainerbattle_single TRAINER_IVAN_HNS, Route35_Text_CamperIvanSeen, Route35_Text_CamperIvanBeaten
	msgbox Route35_Text_CamperIvanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_CamperElliot::
	trainerbattle_single TRAINER_ELLIOT_HNS, Route35_Text_CamperElliotSeen, Route35_Text_CamperElliotBeaten
	msgbox Route35_Text_CamperElliotAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerBrooke::
	trainerbattle_single TRAINER_BROOKE_HNS, Route35_Text_PicnickerBrookeSeen, Route35_Text_PicnickerBrookeBeaten
	msgbox Route35_Text_PicnickerBrookeAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PicnickerKim::
	trainerbattle_single TRAINER_KIM_HNS, Route35_Text_PicnickerKimSeen, Route35_Text_PicnickerKimBeaten
	msgbox Route35_Text_PicnickerKimAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BirdKeeperBryan::
	trainerbattle_single TRAINER_BRYAN_HNS, Route35_Text_BirdKeeperBryanSeen, Route35_Text_BirdKeeperBryanBeaten
	msgbox Route35_Text_BirdKeeperBryanAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_JugglerIrwin::
	trainerbattle_single TRAINER_IRWIN_HNS, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten, Route35_EventScript_RegisterIrwin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route35_EventScript_RematchIrwin
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterIrwin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_IrwinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_IRWIN_HNS
	release
	end

Route35_EventScript_RematchIrwin::
	trainerbattle_rematch TRAINER_IRWIN_HNS, Route35_Text_JugglerIrwinSeen, Route35_Text_JugglerIrwinBeaten
	msgbox Route35_Text_JugglerIrwinAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_BugCatcherArnie::
	trainerbattle_single TRAINER_ARNIE_HNS, Route35_Text_BugCatcherArnieSeen, Route35_Text_BugCatcherArnieBeaten, Route35_EventScript_RegisterArnie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route35_EventScript_RematchArnie
	msgbox Route35_Text_BugCatcherArnieAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_RegisterArnie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route35_Text_ArnieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ARNIE_HNS
	release
	end

Route35_EventScript_RematchArnie::
	trainerbattle_rematch TRAINER_ARNIE_HNS, Route35_Text_ArnieRematchIntro, Route35_Text_ArnieRematchDefeat
	msgbox Route35_Text_ArniePostRematch, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_FirebreatherWalt::
	trainerbattle_single TRAINER_WALT_HNS, Route35_Text_FirebreatherWaltSeen, Route35_Text_FirebreatherWaltBeaten
	msgbox Route35_Text_FirebreatherWaltAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_PolicemanDirk::
	trainerbattle_single TRAINER_DIRK_HNS, Route35_Text_OfficerDirkSeen, Route35_Text_OfficerDirkBeaten
	msgbox Route35_Text_OfficerDirkAfter, MSGBOX_AUTOCLOSE
	end

Route35_EventScript_Sign1::
	lock
	msgbox Route35_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Sign2::
	lock
	msgbox Route35_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route35_EventScript_Item_Payback::
	finditem ITEM_TM_PAYBACK
	end

Route35_EventScript_Item_Nugget::
	finditem ITEM_BIG_NUGGET
	end

Route35_EventScript_Item_ParalyzeHeal::
	finditem ITEM_PARALYZE_HEAL
	end

Route35_Text_CamperIvanSeen:
	.string "He obtenido datos de POKéMON por\n"
	.string "mi radio. ¡Creo que estoy listo!$"

Route35_Text_CamperIvanBeaten:
	.string "¡Me rindo!$"

Route35_Text_CamperIvanAfter:
	.string "La música de la radio cambia el\n"
	.string "humor de los POKéMON salvajes.$"

Route35_Text_CamperElliotSeen:
	.string "¡Le demostraré a mi novia que soy\n"
	.string "el mejor!$"

Route35_Text_CamperElliotBeaten:
	.string "Desearía que hubieras perdido por mí...$"

Route35_Text_CamperElliotAfter:
	.string "Fui humillado delante de mi\n"
	.string "novia...$"

Route35_Text_PicnickerBrookeSeen:
	.string "Mi novio es débil, no puedo\n"
	.string "confiar en él.$"

Route35_Text_PicnickerBrookeBeaten:
	.string "¡Oh, cielos! ¡Eres muy fuerte!$"

Route35_Text_PicnickerBrookeAfter:
	.string "Confío más en mis POKéMON que en\n"
	.string "mi novio.$"

Route35_Text_PicnickerKimSeen:
	.string "¿Vas al GIMNASIO? ¡Yo también!$"

Route35_Text_PicnickerKimBeaten:
	.string "Oh. I couldn't win...$"

Route35_Text_PicnickerKimAfter:
	.string "Las MEDALLAS son lindas. Las\n"
	.string "colecciono.$"

Route35_Text_BirdKeeperBryanSeen:
	.string "¿Qué tipo de BALLS usas?$"

Route35_Text_BirdKeeperBryanBeaten:
	.string "¡Ay! ¡No fui lo bastante rápida!$"

Route35_Text_BirdKeeperBryanAfter:
	.string "Algunos POKéMON huyen rápido.\p"
	.string "Intenta atraparlos con la\n"
	.string "FAST BALL de KURT.\p"
	.string "Cuando hallo una BAYA ASPEAR, yo\n"
	.string "llévaselo a KURT.\p"
	.string "Él lo convierte en una BALL única.$"

Route35_Text_JugglerIrwinSeen:
	.string "¡Contempla mi destreza con la PELOTA!$"

Route35_Text_JugglerIrwinBeaten:
	.string "¡Uf! ¡Qué descarga!$"

Route35_Text_JugglerIrwinAfter:
	.string "Iba a deslumbrarte con mi\n"
	.string "POKéMON premiado.\p"
	.string "¡Pero tu destreza me electrizó!$"

Route35_Text_BugCatcherArnieSeen:
	.string "Iré a cualquier lugar donde\n"
	.string "aparezcan POKéMON bicho.$"

Route35_Text_BugCatcherArnieBeaten:
	.string "¿Eh? No debí perder eso...$"

Route35_Text_BugCatcherArnieAfter:
	.string "Mi VENONAT ganó el Concurso de\n"
	.string "Bichos en el PARQUE NACIONAL.$"

Route35_Text_IrwinRegister:
	.string "Iba a deslumbrarte con mi\n"
	.string "POKéMON premiado.\p"
	.string "¡Pero tu destreza me electrizó!$"

Route35_Text_ArnieRegister:
	.string "Mi VENONAT ganó el Concurso de\n"
	.string "Bichos en el PARQUE NACIONAL.$"

Route35_Text_ArnieRematchIntro:
	.string "Iré a cualquier lugar donde\n"
	.string "aparezcan POKéMON bicho.$"

Route35_Text_ArnieRematchDefeat:
	.string "¿Eh? No debí perder eso...$"

Route35_Text_ArniePostRematch:
	.string "Mi VENONAT ganó el Concurso de\n"
	.string "Bichos en el PARQUE NACIONAL.$"

Route35_Text_BugCatcherArnieYanma:
	.string "¡Guau... Mira todos esos YANMA!\p"
	.string "Estoy tan impactado que no me muevo.$"

Route35_Text_FirebreatherWaltSeen:
	.string "Practico mi aliento de fuego.$"

Route35_Text_FirebreatherWaltBeaten:
	.string "¡Ay! ¡Me quemé la punta de la nariz!$"

Route35_Text_FirebreatherWaltAfter:
	.string "La Marcha POKéMON de la radio\n"
	.string "atrae POKéMON salvajes.$"

Route35_Text_OfficerDirkSeen:
	.string "¡El peligro acecha en la noche!$"

Route35_Text_OfficerDirkBeaten:
	.string "Whoops!$"

Route35_Text_OfficerDirkAfter:
	.string "Sabes, la noche es divertida a su\n"
	.string "manera.\p"
	.string "Pero no te excedas, ¿está bien?$"

Route35_Text_OfficerDirkTough:
	.string "Tus POKéMON se ven muy fuertes.\p"
	.string "Podrías ir a cualquier lugar seguro.$"

Route35_Text_Sign:
	.string "ROUTE 35$"

Route35_Text_Sign2:
	.string "NATIONAL PARK GATE$"
