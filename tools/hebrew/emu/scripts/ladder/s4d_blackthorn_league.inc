@ Story step 4d: Ice Path, Blackthorn (badge 8), Elm's Master Ball, the Kimono Girls and Ho-Oh,
@ Route 27/26, Victory Road, up to the Champion's room. The Hall of Fame itself is NOT faked here:
@ ladder4_league.txt hands over to the ROM's own Lance-defeat warp and Hall of Fame scripts.

@ Ice Path 1F: the Kimono Girl, HM07 Waterfall (IcePath_1F_EventScript_KimonoGirlPush:41-45, finditem:17)
	setflag FLAG_HIDE_ICE_PATH_KIMONO
	setvar VAR_ICE_PATH_STATE, 1
	additem ITEM_HM_WATERFALL
@ Blackthorn Gym: Clair (BlackthornGym_EventScript_Clair:200-211)
	setflag FLAG_VISITED_BLACKTHORN_CITY
	settrainerflag TRAINER_CLAIR_1_HNS
	setflag FLAG_DEFEATED_BLACKTHORN_GYM
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers_hns
	setvar VAR_BLACKTHORN_CITY_STATE, 2
@ Dragon's Den shrine: the elder's quiz, Clair hands over the Rising Badge
@ (DragonsDen_Shrine_EventScript_ClairEnter:226-283)
	setflag FLAG_BADGE08_GET
	addvar VAR_NUM_BADGES, 1
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	clearflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setvar VAR_BLACKTHORN_CITY_STATE, 3
@ Dragon's Den cavern: Clair's TM on the way out (DragonsDen_Cavern_Trigger_ClairLeft:27-33,
@ DragonsDen_Cavern_EventScript_Clair:93)
	additem ITEM_TM_DRAGON_PULSE
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setvar VAR_BLACKTHORN_CITY_STATE, 4
@ Blackthorn: Elm calls about the Master Ball (BlackthornCity_EventScript_Call:26-36)
	setvar VAR_BLACKTHORN_CITY_STATE, 5
	setvar VAR_NEWBARKTOWN_LABSTATE, 7
@ Elm's lab: the Master Ball (NewBarkTown_Lab_EventScript_ElmMasterBall:441-448)
	additem ITEM_MASTER_BALL
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
@ Ecruteak: the rival at the theater door (EcruteakCity_Trigger_Silver:61-98)
	setvar VAR_ECRUTEAK_CITY_THEATER, 5
@ Dance Theater: the five Kimono Girls, the Clear Bell (EcruteakCity_Theater_EventScript_LegendaryCutscene
@ :683-692, the five battles :693-746, EcruteakCity_Theater_EventScript_Hooh:832-845)
	settrainerflag TRAINER_ZUKI_HNS
	settrainerflag TRAINER_NAOKO_HNS
	settrainerflag TRAINER_MIKI_HNS
	settrainerflag TRAINER_SAYO_HNS
	settrainerflag TRAINER_KUNI_HNS
	additem ITEM_CLEAR_BELL
	clearflag FLAG_HIDE_TINTOWER_GUARD
	clearflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	setvar VAR_COMPLETED_HO_OH, 2
	setvar VAR_COMPLETED_LUGIA, 3
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	setvar VAR_NEWBARKTOWN_LABSTATE, 9
	setvar VAR_ECRUTEAK_CITY_THEATER, 7
@ Tin Tower roof: Ho-Oh caught (TinTower_RoofDay_EventScript_HoOh:169-197, _CaughtHooh:230-238).
@ The Ho-Oh itself is given by the party file.
	setflag FLAG_CAUGHT_HO_OH
	setflag FLAG_HIDE_HO_OH
	setflag FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	setvar VAR_ECRUTEAK_CITY_THEATER, 8
	setvar VAR_COMPLETED_HO_OH, 3
@ Route 27: first steps into Kanto (Route27_EventScript_FirstSteps:22-49), Baoba's call
@ (Route27_EventScript_BaobaCall:10-18)
	setflag FLAG_VISITED_KANTO
	setflag FLAG_HIDE_VICTORY_ROAD_SILVER
	setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	setflag FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK
	clearflag FLAG_GOT_TM_SANDSTORM
	clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
	setvar VAR_ROUTE27_STATE, 1
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
	setvar VAR_ROUTE27_BAOBA_CALL, 1
@ Route 26 reception gate: 8 badges and Ho-Oh done, the guard lets the player pass
@ (Route26North_Trigger:4-6, ReceptionGate_Trigger:31-44)
	setflag FLAG_VISITED_RECEPTION_GATE
	setvar VAR_ROUTE27_STATE, 2
@ Victory Road: the last rival battle (VictoryRoadKanto_1F_Trigger:14-39; VAR_STARTER_MON 1 ->
@ TRAINER_RIVAL_TOTODILE_5_HNS)
	settrainerflag TRAINER_RIVAL_TOTODILE_5_HNS
	setvar VAR_ROUTE27_STATE, 3
@ Indigo Plateau Pokemon Center (IndigoPlateau_PokemonCenter_Enter:15-18)
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_LEAGUE_STATE, 1
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU_HNS
@ Elite Four and Lance (PokemonLeague_*Room_EventScript_*OnDefeat: VAR_LEAGUE_STATE 2..5, then 6
@ in PokemonLeague_WillsRoom_EventScript_LanceOnDefeatJohto:72-138, which warps to the Hall of Fame)
	settrainerflag TRAINER_WILL_1_HNS
	settrainerflag TRAINER_KOGA_1_HNS
	settrainerflag TRAINER_BRUNO_1_HNS
	settrainerflag TRAINER_KAREN_1_HNS
	settrainerflag TRAINER_LANCE_1_HNS
	setvar VAR_LEAGUE_STATE, 5
	end
