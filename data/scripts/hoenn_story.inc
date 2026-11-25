@ Hoenn & Seek (part 11+): story items with new givers in the post-Emerald Hoenn.
@ See claude/hns-hoenn-world-details.md ("Story items: who gives them now").

@ ---------------------------------------------------------------- Flannery: Go-Goggles
@ Called from LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated (Emerald's rival used to bring them).
HoennSeek_EventScript_FlanneryGoGoggles::
	goto_if_set FLAG_RECEIVED_GO_GOGGLES, HoennSeek_EventScript_FlanneryGoGogglesEnd
	msgbox HoennSeek_Text_FlanneryGoGoggles, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox HoennSeek_Text_FlanneryGoGogglesExplain, MSGBOX_DEFAULT
HoennSeek_EventScript_FlanneryGoGogglesEnd::
	return

@ ---------------------------------------------------------------- Wattson: Basement Key, then TM Thunderbolt
@ Called from MauvilleCity_Gym_EventScript_WattsonDefeated.
HoennSeek_EventScript_WattsonBasementKey::
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, HoennSeek_EventScript_WattsonBasementKeyEnd
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
HoennSeek_EventScript_WattsonBasementKeyEnd::
	return

@ After the New Mauville generator is off, gym Wattson gives the reward his outdoor self used to.
HoennSeek_EventScript_WattsonThunderbolt::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- Mr. Stone (Devon Corp 3F)
@ HnS already gives the Exp. Share at new game, so his thank-you gift is a Lucky Egg.
@ FLAG_RECEIVED_EXP_SHARE (Hoenn-owned) records that he gave it.
HoennSeek_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, HoennSeek_EventScript_MrStoneAfterGift
	msgbox HoennSeek_Text_MrStoneWelcome, MSGBOX_DEFAULT
	giveitem ITEM_LUCKY_EGG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	goto_if_set FLAG_HOENN_SCOPE_BROKEN, HoennSeek_EventScript_MrStoneScope
	msgbox HoennSeek_Text_MrStoneFieldTest, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_MrStoneEnd
HoennSeek_EventScript_MrStoneAfterGift::
	goto_if_set FLAG_HOENN_SCOPE_BROKEN, HoennSeek_EventScript_MrStoneScope
HoennSeek_EventScript_MrStoneAfterGiftText::
	msgbox HoennSeek_Text_MrStoneAfterGift, MSGBOX_DEFAULT
HoennSeek_EventScript_MrStoneEnd::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ Part 14: the Route 120 tester's prototype broke; Mr. Stone has the finished model.
HoennSeek_EventScript_MrStoneScope::
	goto_if_set FLAG_RECEIVED_DEVON_SCOPE, HoennSeek_EventScript_MrStoneAfterGiftText
	msgbox HoennSeek_Text_MrStoneScopeBroke, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_DEVON_SCOPE
	msgbox HoennSeek_Text_MrStoneScopeExplain, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_MrStoneEnd

@ ---------------------------------------------------------------- Route 120 field tester (part 14)
@ Called from Route120_EventScript_Steven while the player has no DEVON SCOPE.
@ His prototype shorts out, so the player has to fetch the finished model from
@ Mr. Stone in Rustboro and come back.
HoennSeek_EventScript_TesterNoScope::
	goto_if_set FLAG_HOENN_SCOPE_BROKEN, HoennSeek_EventScript_TesterWaiting
	msgbox HoennSeek_Text_TesterIntro, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE120_STEVEN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	playse SE_M_THUNDERBOLT2
	waitse
	msgbox HoennSeek_Text_TesterSparks, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE120_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox HoennSeek_Text_TesterBroken, MSGBOX_DEFAULT
	setflag FLAG_HOENN_SCOPE_BROKEN
	release
	end

HoennSeek_EventScript_TesterWaiting::
	msgbox HoennSeek_Text_TesterWaiting, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------- HOENN TV news (part 14)
@ Called at the top of EventScript_TV. Fake fights set VAR_HOENN_NEWS; the next
@ TV the player checks shows that story once, then TV goes back to normal.
HoennSeek_EventScript_TVNews::
	goto_if_eq VAR_HOENN_NEWS, 0, HoennSeek_EventScript_TVNewsNone
	call_if_eq VAR_HOENN_NEWS, 1, HoennSeek_EventScript_TVNewsAutograph
	call_if_eq VAR_HOENN_NEWS, 2, HoennSeek_EventScript_TVNewsSong
	setvar VAR_HOENN_NEWS, 0
	releaseall
	end
HoennSeek_EventScript_TVNewsNone::
	return

HoennSeek_EventScript_TVNewsAutograph::
	msgbox HoennSeek_Text_TVNewsAutograph, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_TVNewsSong::
	msgbox HoennSeek_Text_TVNewsSong, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------- Text

HoennSeek_Text_FlanneryGoGoggles:
	.string "FLANNERY: Oh, and one more thing!\p"
	.string "If you're heading into the desert on\n"
	.string "ROUTE 111, you'll want these.$"

HoennSeek_Text_FlanneryGoGogglesExplain:
	.string "FLANNERY: With those GO-GOGGLES on,\n"
	.string "the sandstorm won't stop you.\p"
	.string "Go see what's hiding out there!$"

HoennSeek_Text_MrStoneWelcome:
	.string "MR. STONE: Ah, a TRAINER from far\n"
	.string "away! Welcome to DEVON.\p"
	.string "A few years ago, some of HOENN's young\n"
	.string "TRAINERS helped us through a great\l"
	.string "deal of trouble.\p"
	.string "I never could thank them enough.\n"
	.string "So please, take this instead!$"

HoennSeek_Text_MrStoneFieldTest:
	.string "MR. STONE: That LUCKY EGG will help\n"
	.string "your POKéMON grow faster.\p"
	.string "Oh, and if you pass through ROUTE 120,\n"
	.string "say hello to our field tester.\p"
	.string "We're trying out a new DEVON SCOPE\n"
	.string "out there. It's quite something!$"

HoennSeek_Text_MrStoneScopeBroke:
	.string "MR. STONE: Our tester on ROUTE 120\n"
	.string "called. The prototype DEVON SCOPE\l"
	.string "went up in sparks, did it?\p"
	.string "Ha ha! That's what field tests are\n"
	.string "for. Here, take the finished model\l"
	.string "back to him!$"

HoennSeek_Text_MrStoneScopeExplain:
	.string "MR. STONE: That SCOPE reveals\n"
	.string "POKéMON that can't be seen.\p"
	.string "There are KECLEON hiding all around\n"
	.string "FORTREE. Keep it, and have fun!$"

HoennSeek_Text_TesterIntro:
	.string "Oh! A TRAINER! Perfect timing.\p"
	.string "Something invisible is blocking this\n"
	.string "bridge. Watch, I'll show you with\l"
	.string "DEVON's new SCOPE…$"

HoennSeek_Text_TesterSparks:
	.string "The tester switched on the DEVON\n"
	.string "SCOPE…\p"
	.string "Bzzzt! Sparks flew out of it!$"

HoennSeek_Text_TesterBroken:
	.string "Ack! The prototype's fried!\p"
	.string "MR. STONE has the finished model at\n"
	.string "DEVON CORPORATION in RUSTBORO.\p"
	.string "I can't leave the bridge unwatched.\n"
	.string "Could you fetch it for me?$"

HoennSeek_Text_TesterWaiting:
	.string "MR. STONE at DEVON CORPORATION in\n"
	.string "RUSTBORO has the finished SCOPE.\p"
	.string "I'll keep an eye on this bridge\n"
	.string "until you're back!$"

HoennSeek_Text_TVNewsAutograph:
	.string "HOENN TV NEWS FLASH!\p"
	.string "The champion from JOHTO has been\n"
	.string "spotted on HOENN's routes, signing\l"
	.string "autographs for excited fans!\p"
	.string "Where will {PLAYER} turn up next?\n"
	.string "Stay tuned!$"

HoennSeek_Text_TVNewsSong:
	.string "HOENN TV MUSIC CORNER!\p"
	.string "A new song about the JOHTO champion\n"
	.string "is climbing the charts!\p"
	.string "It's called “{PLAYER}'s THEME.”\n"
	.string "Our phones haven't stopped ringing!$"

HoennSeek_Text_MrStoneAfterGift:
	.string "MR. STONE: My son, STEVEN? He's off\n"
	.string "somewhere digging up rare stones, no\l"
	.string "doubt.\p"
	.string "He was always that way, even as a boy.$"

@ Steven's house, Mossdeep (part 12/13): the old Beldum ball is Steven's stone
@ collection. Pick any one stone that isn't a key item or a Mega Stone:
@ evolution stones or the other stones (lists in src/hoenn_specials.c).
HoennSeek_EventScript_StevensStone::
	lockall
	msgbox HoennSeek_Text_StevensStoneNote, MSGBOX_DEFAULT
HoennSeek_EventScript_StevensStoneKind::
	message HoennSeek_Text_StevensStoneWhichKind
	waitmessage
	dynmultichoice 15, 2, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_StonesEvolution, HoennSeek_Text_StonesOther, HoennSeek_Text_StonesLeave
	goto_if_ge VAR_RESULT, 2, HoennSeek_EventScript_StevensStoneLeave
	copyvar VAR_0x8004, VAR_RESULT
	message HoennSeek_Text_StevensStoneWhichOne
	waitmessage
	special HoennPushStoneList
	dynmultistack 15, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, HoennSeek_EventScript_StevensStoneKind
	copyvar VAR_0x8005, VAR_RESULT
	specialvar VAR_0x8006, HoennStoneFromIndex
	bufferitemname STR_VAR_1, VAR_0x8006
	msgbox HoennSeek_Text_StevensStoneTakeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_StevensStoneKind
	giveitem VAR_0x8006
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_StevensStoneBagFull
	removeobject LOCALID_STEVENS_HOUSE_BALL
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	releaseall
	end

HoennSeek_EventScript_StevensStoneLeave::
	msgbox HoennSeek_Text_StevensStoneLeave, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_StevensStoneBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_Text_StevensStoneNote:
	.string "It's a case full of stones. There's\n"
	.string "a note tucked under the lid.\p"
	.string "“Take whichever one you like.\n"
	.string "Just one, mind you! --STEVEN”$"

HoennSeek_Text_StevensStoneWhichKind:
	.string "Which kind of stone?$"

HoennSeek_Text_StevensStoneWhichOne:
	.string "Which one?$"

HoennSeek_Text_StevensStoneTakeIt:
	.string "Take the {STR_VAR_1}?$"

HoennSeek_Text_StevensStoneLeave:
	.string "{PLAYER} left the case on the table.$"

HoennSeek_Text_StonesEvolution:
	.string "EVOLUTION$"

HoennSeek_Text_StonesOther:
	.string "OTHER$"

HoennSeek_Text_StonesLeave:
	.string "LEAVE IT$"
