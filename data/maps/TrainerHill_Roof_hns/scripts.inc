TrainerHill_Roof_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Roof_hns_OnLoad
	.byte 0

TrainerHill_Roof_hns_OnLoad::
	setflag FLAG_TEMP_HIDE_FOLLOWER
	end

TrainerHill_Roof_hns_EventScript_Owner::
	trainerhill_settrainerflags
	lock
	faceplayer
	trainerhill_getownerstate
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_Arrived
	case 1, TrainerHill_Roof_hns_EventScript_GivePrize
	case 2, TrainerHill_Roof_hns_EventScript_AlreadyReceivedPrize
TrainerHill_Roof_hns_EventScript_Arrived::
	msgbox TrainerHill_Roof_hns_Text_YouFinallyCameBravo, MSGBOX_DEFAULT
TrainerHill_Roof_hns_EventScript_GivePrize::
	trainerhill_giveprize
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_ReceivePrize
	case 1, TrainerHill_Roof_hns_EventScript_NoRoomForPrize
	case 2, TrainerHill_Roof_hns_EventScript_CheckFinalTime
TrainerHill_Roof_hns_EventScript_ReceivePrize::
	msgbox TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift, MSGBOX_DEFAULT
	playfanfare MUS_LEVEL_UP
	message gText_ObtainedTheItem
	waitfanfare
	waitmessage
	goto TrainerHill_Roof_hns_EventScript_CheckFinalTime

TrainerHill_Roof_hns_EventScript_NoRoomForPrize::
	msgbox TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift, MSGBOX_DEFAULT
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	msgbox TrainerHill_Roof_hns_Text_FullUpBeBackLaterForThis, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_CheckFinalTime

TrainerHill_Roof_hns_EventScript_CheckFinalTime::
	trainerhill_finaltime
	switch VAR_RESULT
	case 0, TrainerHill_Roof_hns_EventScript_NewRecord
	case 1, TrainerHill_Roof_hns_EventScript_NoNewRecord
	case 2, TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
TrainerHill_Roof_hns_EventScript_NewRecord::
	msgbox TrainerHill_Roof_hns_Text_GotHereMarvelouslyQuickly, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
	end

TrainerHill_Roof_hns_EventScript_NoNewRecord::
	msgbox TrainerHill_Roof_hns_Text_YouWerentVeryQuick, MSGBOX_DEFAULT
	goto TrainerHill_Roof_hns_EventScript_EndSpeakToOwner
	end

TrainerHill_Roof_hns_EventScript_EndSpeakToOwner::
	msgbox TrainerHill_Roof_hns_Text_ArriveZippierNextTime, MSGBOX_DEFAULT
	release
	end

TrainerHill_Roof_hns_EventScript_AlreadyReceivedPrize::
	msgbox TrainerHill_Roof_hns_Text_ArriveZippierNextTime, MSGBOX_DEFAULT
	release
	end

TrainerHill_Roof_hns_Text_YouFinallyCameBravo:
	.string "הממ! הממ!\p"
	.string "סוף סוף באת!\n"
	.string "כן, הגעת!\p"
	.string "רגע! אל תגיד כלום! אני יודע למה\n"
	.string "טרחת להגיע עד לכאן לבד!\p"
	.string "רצית לפגוש אותי, הבעלים\n"
	.string "של גבעת המאמנים, כי…\p"
	.string "אתה רוצה להקים איתי צוות זוגי!\n"
	.string "יו-הו!\p"
	.string "…אה?\n"
	.string "לא בגלל זה?\p"
	.string "בכל אופן, צפיתי בך בדרך למעלה.\n"
	.string "קרבות נפלאים! בראבו, באמת!$"

TrainerHill_Roof_hns_Text_HaveTheMostMarvelousGift:
	.string "למישהו נפלא כמוך יש לי את המתנה\n"
	.string "הנפלאה ביותר, וגם קצת כסף על המאמץ!$"

TrainerHill_Roof_hns_Text_FullUpBeBackLaterForThis:
	.string "אוי, לא, אין מקום לעוד דברים!\n"
	.string "תחזור לקחת את זה אחר כך!$"

TrainerHill_Roof_hns_Text_GotHereMarvelouslyQuickly:
	.string "הו, רגע אחד! האם ייתכן שהגעת\n"
	.string "לכאן במהירות נפלאה?\p"
	.string "כמה נהדר! לא היה צורך למהר\n"
	.string "כל כך כדי לראות אותי!\p"
	.string "זה כל כך משמח. אדאג שלוח השיאים\n"
	.string "בדלפק הקבלה יעודכן!$"

TrainerHill_Roof_hns_Text_YouWerentVeryQuick:
	.string "אבל, אוי…\n"
	.string "לא ממש מיהרת להגיע לכאן.$"

TrainerHill_Roof_hns_Text_ArriveZippierNextTime:
	.string "אולי אשמח יותר אם בפעם הבאה\n"
	.string "תגיע לכאן מהר יותר.\p"
	.string "אז אשמח להקים איתך\n"
	.string "צוות זוגי!\p"
	.string "עד הפגישה הבאה, אמיגו!$"
