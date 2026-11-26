@ Hoenn & Seek 2.0 parts 15a and 15b: Johto starters (plan section 5).
@
@ The other two Johto starters no longer come from Elm's table or Route 27's
@ grass. Each one has a scene of its own, and every scene plays one of three
@ versions by VAR_STARTER_MON (0 Chikorita, 1 Cyndaquil, 2 Totodile):
@   your own species      watch-only: a family, nothing to catch
@   your rival's species  a wild one, a scaled battle (HoennSetupScaledWildBattle)
@   the unclaimed one     Birch's runaway: one of the two starters he sent Elm
@                         got loose; it smells Elm's lab on you and joins you
@                         (Lv 5 with an egg move, like Mudkip's level)
@ All of them wait until you've beaten Brendan & May (FLAG_HOENN_BEAT_BM), when
@ Elm calls about the runaway. Each scene has a "family" (the evolved parent and
@ one young one) and one young one that can stay behind; their hide flags are
@ decided on every arrival, so the time of day is checked when you walk in.
@ Chikorita and Cyndaquil came in part 15a, Totodile's Lake of Rage scene
@ in part 15b.

HoennSeek_EventScript_StarterEnd::
	end

@ ---- Chikorita: the hidden meadow behind Route 46's cave (daytime) ---------
@ Route 46's cave mouth (25,33) used to be a fake door in a pocket nothing
@ could reach; a cut tree at (20,33) now leads there (data/hoenn/composed_maps.json).

@ Who is in the meadow right now? VAR_RESULT: 0 nobody, 1 the family
@ (watch-only), 2 the lone Chikorita.
HoennSeek_EventScript_MeadowWho::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_StarterReturn
	gettimeofday
	goto_if_gt VAR_0x8000, HOENN_TIME_DAY, HoennSeek_EventScript_StarterReturn
	goto_if_eq VAR_STARTER_MON, 0, HoennSeek_EventScript_MeadowWhoFamily
	goto_if_set FLAG_HOENN_CHIKORITA_DONE, HoennSeek_EventScript_StarterReturn
	setvar VAR_RESULT, 2
	return
HoennSeek_EventScript_MeadowWhoFamily:
	setvar VAR_RESULT, 1
HoennSeek_EventScript_StarterReturn::
	return

HoennSeek_EventScript_MeadowOnTransition::
	setflag FLAG_HOENN_HIDE_MEADOW_FAMILY
	setflag FLAG_HOENN_HIDE_MEADOW_CHIKORITA
	call HoennSeek_EventScript_MeadowWho
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_StarterEnd
	clearflag FLAG_HOENN_HIDE_MEADOW_CHIKORITA
	goto_if_eq VAR_RESULT, 2, HoennSeek_EventScript_StarterEnd
	clearflag FLAG_HOENN_HIDE_MEADOW_FAMILY
	end

@ Route 46 trigger tiles (x 17, rows 30-33, in the big tall-grass patch): the
@ sweet aroma, once per visit, while someone is in the meadow.
HoennSeek_EventScript_Route46Aroma::
	setvar VAR_TEMP_1, 1
	call HoennSeek_EventScript_MeadowWho
	goto_if_eq VAR_RESULT, 0, HoennSeek_EventScript_StarterEnd
	lockall
	msgbox HoennSeek_Text_Route46Aroma, MSGBOX_DEFAULT
	releaseall
	end

@ Meadow trigger tiles (row 5): the first sighting, once.
HoennSeek_EventScript_MeadowFirstSight::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_HOENN_CHIKORITA_SCENE, HoennSeek_EventScript_StarterEnd
	goto_if_set FLAG_HOENN_HIDE_MEADOW_CHIKORITA, HoennSeek_EventScript_StarterEnd
	lockall
	setflag FLAG_HOENN_CHIKORITA_SCENE
	call HoennSeek_EventScript_StarterPanDown
	msgbox HoennSeek_Text_MeadowArrive, MSGBOX_DEFAULT
	goto_if_unset FLAG_HOENN_HIDE_MEADOW_FAMILY, HoennSeek_EventScript_MeadowFamilyScene
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_MEADOW_CHIKORITA, HoennSeek_Movement_StarterHop
	waitmovement 0
	waitmoncry
	call_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_MeadowLoneTag
	call_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_MeadowLoneWild
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end
HoennSeek_EventScript_MeadowLoneTag:
	msgbox HoennSeek_Text_MeadowLoneTag, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_MeadowLoneWild:
	msgbox HoennSeek_Text_MeadowLoneWild, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_MeadowFamilyScene:
	playmoncry SPECIES_MEGANIUM, CRY_MODE_NORMAL
	waitmoncry
	playse SE_M_SWEET_SCENT
	msgbox HoennSeek_Text_MeadowMeganium, MSGBOX_DEFAULT
	closemessage
	waitse
	applymovement LOCALID_HOENN_MEADOW_CHIKORITA_A, HoennSeek_Movement_StarterHop
	applymovement LOCALID_HOENN_MEADOW_CHIKORITA, HoennSeek_Movement_StarterHop
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_MeadowFamilyWatch, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end

HoennSeek_EventScript_MeadowMeganium::
	lock
	faceplayer
	playmoncry SPECIES_MEGANIUM, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_MeadowMeganiumTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_MeadowChikoritaFamily::
	lock
	faceplayer
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_MeadowChikoritaTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_MeadowSunkern::
	lock
	faceplayer
	playmoncry SPECIES_SUNKERN, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_MeadowSunkernTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The Chikorita that can stay: family member, Birch's runaway or a wild one.
HoennSeek_EventScript_MeadowChikorita::
	goto_if_eq VAR_STARTER_MON, 0, HoennSeek_EventScript_MeadowChikoritaFamily
	setvar VAR_0x8004, SPECIES_CHIKORITA
	goto_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_StarterWild
	lock
	faceplayer
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_ChikoritaJoins, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	givemon SPECIES_CHIKORITA, 5, move1=MOVE_AROMATHERAPY
	goto HoennSeek_EventScript_StarterJoined

@ ---- Cyndaquil: Burned Tower B1F, at night ---------------------------------
@ BurnedTower_B1F_hns's OnTransition calls HoennSeek_EventScript_BurnedTowerOnTransition
@ (one hook line). It sets VAR_TEMP_4 to 1 when the first sighting is due, which arms
@ the trigger tiles across the north of the pit (rows 11-13) and its south-west
@ way in (row 17): the first step there plays it.

HoennSeek_EventScript_BurnedTowerOnTransition::
	setflag FLAG_HOENN_HIDE_BT_FAMILY
	setflag FLAG_HOENN_HIDE_BT_CYNDAQUIL
	goto_if_unset FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_StarterReturn
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_StarterReturn
	goto_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_BurnedTowerFamily
	goto_if_set FLAG_HOENN_CYNDAQUIL_DONE, HoennSeek_EventScript_StarterReturn
	clearflag FLAG_HOENN_HIDE_BT_CYNDAQUIL
	goto_if_set FLAG_HOENN_CYNDAQUIL_SCENE, HoennSeek_EventScript_StarterReturn
HoennSeek_EventScript_BurnedTowerFamily:
	clearflag FLAG_HOENN_HIDE_BT_FAMILY
	clearflag FLAG_HOENN_HIDE_BT_CYNDAQUIL
	goto_if_set FLAG_HOENN_CYNDAQUIL_SCENE, HoennSeek_EventScript_StarterReturn
	setvar VAR_TEMP_4, 1
	return

@ The first sighting: the family warms itself by the embers while you watch
@ from behind a pillar. Watch-only (you chose Cyndaquil): they all leave.
@ Otherwise one Cyndaquil stays behind.
HoennSeek_EventScript_BurnedTowerFirstSight::
	lockall
	setvar VAR_TEMP_4, 0
	setflag FLAG_HOENN_CYNDAQUIL_SCENE
	setvar VAR_0x8008, 17
	setvar VAR_0x8009, 14
	call HoennSeek_EventScript_StarterPanTo
	msgbox HoennSeek_Text_BurnedTowerArrive, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_TYPHLOSION, CRY_MODE_NORMAL
	waitmoncry
	playse SE_M_FLAME_WHEEL
	msgbox HoennSeek_Text_BurnedTowerFlare, MSGBOX_DEFAULT
	closemessage
	waitse
	applymovement LOCALID_HOENN_BT_CYNDAQUIL_A, HoennSeek_Movement_StarterHop
	applymovement LOCALID_HOENN_BT_CYNDAQUIL, HoennSeek_Movement_StarterHop
	playse SE_M_EMBER
	waitmovement 0
	waitse
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	waitmoncry
	msgbox HoennSeek_Text_BurnedTowerCopy, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_HOENN_BT_TYPHLOSION
	removeobject LOCALID_HOENN_BT_CYNDAQUIL_A
	call_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_BurnedTowerAllLeave
	fadescreen FADE_FROM_BLACK
	call_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_BurnedTowerWatched
	call_if_eq VAR_STARTER_MON, 0, HoennSeek_EventScript_BurnedTowerStayedWild
	call_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_BurnedTowerStayedTag
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end
HoennSeek_EventScript_BurnedTowerAllLeave:
	removeobject LOCALID_HOENN_BT_CYNDAQUIL
	return
HoennSeek_EventScript_BurnedTowerWatched:
	msgbox HoennSeek_Text_BurnedTowerWatched, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BurnedTowerStayedWild:
	msgbox HoennSeek_Text_BurnedTowerStayedWild, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_BurnedTowerStayedTag:
	msgbox HoennSeek_Text_BurnedTowerStayedTag, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_BurnedTowerTyphlosion::
	lock
	faceplayer
	playmoncry SPECIES_TYPHLOSION, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_BurnedTowerTyphlosionTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_BurnedTowerCyndaquilFamily::
	lock
	faceplayer
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_BurnedTowerCyndaquilTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The Cyndaquil that can stay: family member, a wild one or Birch's runaway.
HoennSeek_EventScript_BurnedTowerCyndaquil::
	goto_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_BurnedTowerCyndaquilFamily
	setvar VAR_0x8004, SPECIES_CYNDAQUIL
	goto_if_eq VAR_STARTER_MON, 0, HoennSeek_EventScript_StarterWild
	lock
	faceplayer
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_CyndaquilJoins, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	givemon SPECIES_CYNDAQUIL, 5, move1=MOVE_EXTRASENSORY
	goto HoennSeek_EventScript_StarterJoined

@ ---- Totodile: the Lake of Rage's south cove, any time but night (15b) -------
@ LakeOfRage_hns's OnTransition calls HoennSeek_EventScript_LakeOnTransition
@ (one hook line). The cove is the water at x 24-28, rows 35-37, south of the
@ lake: it's water at high and low tide. When the first sighting is due, all
@ three stay hidden and VAR_TEMP_2 is 1, which arms the trigger tiles around
@ the cove (the shore to the south, rows 38-40; x 29 to the east; the water
@ to the north and west, so surfing in counts too). They surface in the scene.

HoennSeek_EventScript_LakeOnTransition::
	setflag FLAG_HOENN_HIDE_LAKE_FAMILY
	setflag FLAG_HOENN_HIDE_LAKE_TOTODILE
	goto_if_unset FLAG_HOENN_BEAT_BM, HoennSeek_EventScript_StarterReturn
	gettimeofday
	goto_if_eq VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_StarterReturn
	goto_if_unset FLAG_HOENN_TOTODILE_SCENE, HoennSeek_EventScript_LakeArm
	goto_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_LakeFamily
	goto_if_set FLAG_HOENN_TOTODILE_DONE, HoennSeek_EventScript_StarterReturn
	clearflag FLAG_HOENN_HIDE_LAKE_TOTODILE
	return
HoennSeek_EventScript_LakeFamily:
	clearflag FLAG_HOENN_HIDE_LAKE_FAMILY
	clearflag FLAG_HOENN_HIDE_LAKE_TOTODILE
	return
HoennSeek_EventScript_LakeArm:
	setvar VAR_TEMP_2, 1
	return

@ The first sighting: the family surfaces in the cove and splashes about.
@ Watch-only (you chose Totodile): they stay and play. Otherwise the
@ Feraligatr dives with one Totodile, and the other one hops ashore at (28,38),
@ where it is on later visits. Pokémon in the water can't be talked to from
@ land (the object takes the water's elevation), so the one you meet stands
@ on the shore: it surfaces at (28,37) for the scene (setobjectxyperm lasts
@ until you leave) and hops down.
HoennSeek_EventScript_LakeFirstSight::
	lockall
	setvar VAR_TEMP_2, 0
	setflag FLAG_HOENN_TOTODILE_SCENE
	msgbox HoennSeek_Text_LakeArrive, MSGBOX_DEFAULT
	closemessage
	playse SE_M_DIVE
	clearflag FLAG_HOENN_HIDE_LAKE_FAMILY
	clearflag FLAG_HOENN_HIDE_LAKE_TOTODILE
	addobject LOCALID_HOENN_LAKE_FERALIGATR
	waitse
	playmoncry SPECIES_FERALIGATR, CRY_MODE_NORMAL
	waitmoncry
	msgbox HoennSeek_Text_LakeFeraligatr, MSGBOX_DEFAULT
	closemessage
	playse SE_M_BUBBLE
	addobject LOCALID_HOENN_LAKE_TOTODILE_A
	setobjectxyperm LOCALID_HOENN_LAKE_TOTODILE, 28, 37
	addobject LOCALID_HOENN_LAKE_TOTODILE
	waitse
	applymovement LOCALID_HOENN_LAKE_TOTODILE_A, HoennSeek_Movement_StarterHop
	applymovement LOCALID_HOENN_LAKE_TOTODILE, HoennSeek_Movement_StarterHop
	playse SE_M_SURF
	waitmovement 0
	waitse
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	waitmoncry
	msgbox HoennSeek_Text_LakeSplash, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_LakeWatched
	playse SE_M_DIVE
	removeobject LOCALID_HOENN_LAKE_FERALIGATR
	removeobject LOCALID_HOENN_LAKE_TOTODILE_A
	waitse
	msgbox HoennSeek_Text_LakeDove, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_LAKE_TOTODILE, HoennSeek_Movement_LakeHopAshore
	waitmovement 0
	call_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_LakeStayedWild
	call_if_eq VAR_STARTER_MON, 0, HoennSeek_EventScript_LakeStayedTag
	releaseall
	end
HoennSeek_EventScript_LakeWatched:
	msgbox HoennSeek_Text_LakeWatched, MSGBOX_DEFAULT
	releaseall
	end
HoennSeek_EventScript_LakeStayedWild:
	msgbox HoennSeek_Text_LakeStayedWild, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_LakeStayedTag:
	msgbox HoennSeek_Text_LakeStayedTag, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_LakeFeraligatr::
	lock
	faceplayer
	playmoncry SPECIES_FERALIGATR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LakeFeraligatrTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_LakeTotodileFamily::
	lock
	faceplayer
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_LakeTotodileTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The Totodile that can stay: family member, a wild one or Birch's runaway.
HoennSeek_EventScript_LakeTotodile::
	goto_if_eq VAR_STARTER_MON, 2, HoennSeek_EventScript_LakeTotodileFamily
	setvar VAR_0x8004, SPECIES_TOTODILE
	goto_if_eq VAR_STARTER_MON, 1, HoennSeek_EventScript_StarterWild
	lock
	faceplayer
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_TotodileJoins, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	givemon SPECIES_TOTODILE, 5, move1=MOVE_DRAGON_DANCE
	goto HoennSeek_EventScript_StarterJoined

@ ---- Shared endings ----------------------------------------------------------

@ After givemon (VAR_0x8004 = species, STR_VAR_1 = its name). Sets the species'
@ DONE flag first: the nickname screen can change VAR_0x8004.
HoennSeek_EventScript_StarterJoined::
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_StarterNoRoom
	call HoennSeek_EventScript_StarterSetDone
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8004
	call Common_EventScript_GiftMon
	removeobject VAR_LAST_TALKED
	release
	end
HoennSeek_EventScript_StarterNoRoom:
	msgbox HoennSeek_Text_StarterNoRoom, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8004 = species. Caught: done. Knocked out: it runs off and is back on
@ your next visit (day or night). Ran: it stays where it is.
HoennSeek_EventScript_StarterWild::
	lock
	faceplayer
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	waitmoncry
	special HoennSetupScaledWildBattle
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_StarterCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_StarterFainted
	release
	end
HoennSeek_EventScript_StarterCaught:
	call HoennSeek_EventScript_StarterSetDone
	removeobject VAR_LAST_TALKED
	release
	end
HoennSeek_EventScript_StarterFainted:
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox HoennSeek_Text_StarterFled, MSGBOX_DEFAULT
	release
	end

@ The DONE flag of the species in VAR_0x8004.
HoennSeek_EventScript_StarterSetDone::
	call_if_eq VAR_0x8004, SPECIES_CHIKORITA, HoennSeek_EventScript_ChikoritaDone
	call_if_eq VAR_0x8004, SPECIES_CYNDAQUIL, HoennSeek_EventScript_CyndaquilDone
	call_if_eq VAR_0x8004, SPECIES_TOTODILE, HoennSeek_EventScript_TotodileDone
	return
HoennSeek_EventScript_ChikoritaDone:
	setflag FLAG_HOENN_CHIKORITA_DONE
	return
HoennSeek_EventScript_CyndaquilDone:
	setflag FLAG_HOENN_CYNDAQUIL_DONE
	return
HoennSeek_EventScript_TotodileDone:
	setflag FLAG_HOENN_TOTODILE_DONE
	return

@ Scenes pan the camera two tiles down so the family isn't under the text box.
HoennSeek_EventScript_StarterPanDown::
	setvar VAR_0x8007, 1
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraDown2
	waitmovement 0
	return
@ Pan the camera to the tile in VAR_0x8008/VAR_0x8009 from wherever the
@ player stands, one tile at a time (part 17r: the Burned Tower's family was
@ off screen when the scene started from the west stairs). StarterPanBack
@ walks it back to the player. Uses VAR_0x8004/0x8005 as the camera tile and
@ VAR_0x800A/0x800B for the player's tile.
HoennSeek_EventScript_StarterPanTo::
	setvar VAR_0x8007, 2
	getplayerxy VAR_0x8004, VAR_0x8005
	@ The player's tile, for the pan back: once the camera object moves,
	@ getplayerxy reports the camera's tile instead.
	copyvar VAR_0x800A, VAR_0x8004
	copyvar VAR_0x800B, VAR_0x8005
	special SpawnCameraObject
	goto HoennSeek_EventScript_CameraWalkTo

@ Walk the camera from VAR_0x8004/0x8005 to VAR_0x8008/0x8009, x first.
HoennSeek_EventScript_CameraWalkTo:
	goto_if_eq VAR_0x8004, VAR_0x8008, HoennSeek_EventScript_CameraWalkToY
	goto_if_lt VAR_0x8004, VAR_0x8008, HoennSeek_EventScript_CameraWalkRight
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraLeft1
	waitmovement 0
	subvar VAR_0x8004, 1
	goto HoennSeek_EventScript_CameraWalkTo
HoennSeek_EventScript_CameraWalkRight:
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraRight1
	waitmovement 0
	addvar VAR_0x8004, 1
	goto HoennSeek_EventScript_CameraWalkTo
HoennSeek_EventScript_CameraWalkToY:
	goto_if_eq VAR_0x8005, VAR_0x8009, HoennSeek_EventScript_StarterReturn
	goto_if_lt VAR_0x8005, VAR_0x8009, HoennSeek_EventScript_CameraWalkDown
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraUp1
	waitmovement 0
	subvar VAR_0x8005, 1
	goto HoennSeek_EventScript_CameraWalkToY
HoennSeek_EventScript_CameraWalkDown:
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraDown1
	waitmovement 0
	addvar VAR_0x8005, 1
	goto HoennSeek_EventScript_CameraWalkToY

HoennSeek_EventScript_StarterPanBack::
	goto_if_eq VAR_0x8007, 2, HoennSeek_EventScript_StarterPanBackFromTile
	goto_if_ne VAR_0x8007, 1, HoennSeek_EventScript_StarterReturn
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraUp2
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_0x8007, 0
	return

HoennSeek_EventScript_StarterPanBackFromTile:
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x8009
	copyvar VAR_0x8008, VAR_0x800A
	copyvar VAR_0x8009, VAR_0x800B
	call HoennSeek_EventScript_CameraWalkTo
	special RemoveCameraObject
	setvar VAR_0x8007, 0
	return

HoennSeek_Movement_CameraLeft1:
	walk_slow_left
	step_end
HoennSeek_Movement_CameraRight1:
	walk_slow_right
	step_end
HoennSeek_Movement_CameraUp1:
	walk_slow_up
	step_end
HoennSeek_Movement_CameraDown1:
	walk_slow_down
	step_end

HoennSeek_Movement_CameraDown2:
	walk_slow_down
	walk_slow_down
	step_end
HoennSeek_Movement_CameraUp2:
	walk_slow_up
	walk_slow_up
	step_end

HoennSeek_Movement_LakeHopAshore:
	jump_down
	face_down
	step_end

HoennSeek_Movement_StarterHop::
	jump_in_place_down
	jump_in_place_down
	step_end

@ ---- Text ---------------------------------------------------------------------

HoennSeek_Text_Route46Aroma::
	.string "A sweet aroma is drifting\n"
	.string "through the grass…\p"
	.string "It seems to come from past that\n"
	.string "small tree to the east.$"

HoennSeek_Text_MeadowArrive::
	.string "A hidden meadow, full of\n"
	.string "SUNKERN turning their faces to\l"
	.string "the sun…\p"
	.string "The sweet aroma is even\n"
	.string "stronger here.$"

HoennSeek_Text_MeadowMeganium::
	.string "A MEGANIUM is basking in the\n"
	.string "middle of the meadow.\p"
	.string "It spreads the petals around\n"
	.string "its neck, and the sweet aroma\l"
	.string "grows stronger still.$"

HoennSeek_Text_MeadowFamilyWatch::
	.string "Two CHIKORITA stretch out at\n"
	.string "its feet to soak up the sun.\p"
	.string "It's just how your own\n"
	.string "CHIKORITA liked to nap, back\l"
	.string "when you first met it in\l"
	.string "PROF. ELM's lab.$"

HoennSeek_Text_MeadowLoneTag::
	.string "A lone CHIKORITA is sunbathing\n"
	.string "among the SUNKERN.\p"
	.string "There's a ferry tag around its\n"
	.string "neck. It says: “TO PROF. ELM,\l"
	.string "NEW BARK TOWN.”$"

HoennSeek_Text_MeadowLoneWild::
	.string "A lone CHIKORITA is sunbathing\n"
	.string "among the SUNKERN.\p"
	.string "Just like the one your rival\n"
	.string "chose… It's a wild one!$"

HoennSeek_Text_MeadowMeganiumTalk::
	.string "MEGANIUM: Meeeh…\p"
	.string "It's basking calmly, keeping an\n"
	.string "eye on the little ones.$"

HoennSeek_Text_MeadowChikoritaTalk::
	.string "The CHIKORITA is dozing in the\n"
	.string "sun with its leaf held up high.$"

HoennSeek_Text_MeadowSunkernTalk::
	.string "SUNKERN: Kern!\p"
	.string "It turned its face back toward\n"
	.string "the sun.$"

HoennSeek_Text_ChikoritaJoins::
	.string "The CHIKORITA sniffs at\n"
	.string "your bag…\p"
	.string "It must smell PROF. ELM's lab\n"
	.string "on your things! It hops right\l"
	.string "up to you, ready to come along.$"

HoennSeek_Text_BurnedTowerArrive::
	.string "Something down here is glowing\n"
	.string "in the dark…\p"
	.string "{PLAYER} ducked behind a pillar\n"
	.string "to watch.$"

HoennSeek_Text_BurnedTowerFlare::
	.string "A TYPHLOSION is warming itself\n"
	.string "by the embers. Its collar of\l"
	.string "flames flares up!$"

HoennSeek_Text_BurnedTowerCopy::
	.string "Two CYNDAQUIL copy it, puffing\n"
	.string "little flames from their backs.\p"
	.string "When the embers die down, the\n"
	.string "TYPHLOSION heads out into\l"
	.string "the night…$"

HoennSeek_Text_BurnedTowerWatched::
	.string "…and the two CYNDAQUIL trot\n"
	.string "after it, still puffing flames.\p"
	.string "Your own CYNDAQUIL used to puff\n"
	.string "just like that.$"

HoennSeek_Text_BurnedTowerStayedWild::
	.string "…but one CYNDAQUIL stayed\n"
	.string "behind by the embers.\p"
	.string "Just like the one your rival\n"
	.string "chose… It's a wild one!$"

HoennSeek_Text_BurnedTowerStayedTag::
	.string "…but one CYNDAQUIL stayed\n"
	.string "behind by the embers.\p"
	.string "There's a ferry tag around its\n"
	.string "neck. It says: “TO PROF. ELM,\l"
	.string "NEW BARK TOWN.”$"

HoennSeek_Text_BurnedTowerTyphlosionTalk::
	.string "TYPHLOSION: Fshooo!\p"
	.string "It's keeping the embers alive\n"
	.string "for the little ones.$"

HoennSeek_Text_BurnedTowerCyndaquilTalk::
	.string "The CYNDAQUIL is curled up by\n"
	.string "the embers, its back\l"
	.string "flames flickering.$"

HoennSeek_Text_CyndaquilJoins::
	.string "The CYNDAQUIL sniffs at\n"
	.string "your bag…\p"
	.string "It must smell PROF. ELM's lab\n"
	.string "on your things! Its flames puff\l"
	.string "up as it trots over to you.$"

HoennSeek_Text_LakeArrive::
	.string "Something is splashing about in\n"
	.string "the shallows of the cove…$"

HoennSeek_Text_LakeFeraligatr::
	.string "A FERALIGATR surfaced!\p"
	.string "It opens its huge jaws wide and\n"
	.string "sprays water into the air.$"

HoennSeek_Text_LakeSplash::
	.string "Two TOTODILE pop up beside it,\n"
	.string "snapping at the falling spray!$"

HoennSeek_Text_LakeWatched::
	.string "They chase each other in circles\n"
	.string "around the FERALIGATR.\p"
	.string "Your own TOTODILE used to snap\n"
	.string "at the water just like that.$"

HoennSeek_Text_LakeDove::
	.string "The FERALIGATR dove, and one\n"
	.string "TOTODILE followed it down…$"

HoennSeek_Text_LakeStayedWild::
	.string "…but the other one hopped up\n"
	.string "onto the shore instead.\p"
	.string "Just like the one your rival\n"
	.string "chose… It's a wild one!$"

HoennSeek_Text_LakeStayedTag::
	.string "…but the other one hopped up\n"
	.string "onto the shore instead.\p"
	.string "There's a ferry tag around its\n"
	.string "neck. It says: “TO PROF. ELM,\l"
	.string "NEW BARK TOWN.”$"

HoennSeek_Text_LakeFeraligatrTalk::
	.string "FERALIGATR: Graaah!\p"
	.string "It's floating calmly, keeping\n"
	.string "an eye on the little ones.$"

HoennSeek_Text_LakeTotodileTalk::
	.string "The TOTODILE snaps playfully\n"
	.string "at the ripples.$"

HoennSeek_Text_TotodileJoins::
	.string "The TOTODILE sniffs at\n"
	.string "your bag…\p"
	.string "It must smell PROF. ELM's lab\n"
	.string "on your things! It waddles up\l"
	.string "to you, ready to come along.$"

HoennSeek_Text_StarterNoRoom::
	.string "There's no room for it in your\n"
	.string "party or BOXES.$"

HoennSeek_Text_StarterFled::
	.string "The {STR_VAR_1} ran off! It might\n"
	.string "come back another time.$"
