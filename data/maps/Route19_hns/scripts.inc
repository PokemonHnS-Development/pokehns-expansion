Route19_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route19_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route19_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route19_EventScript_Harold::
	trainerbattle_single TRAINER_HAROLD_HNS, Route19_Text_SwimmermHaroldSeen, Route19_Text_SwimmermHaroldBeaten
	msgbox Route19_Text_SwimmermHaroldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Tucker::
	trainerbattle_single TRAINER_TUCKER_HNS, Route19_Text_SwimmermTuckerSeen, Route19_Text_SwimmermTuckerBeaten
	msgbox Route19_Text_SwimmermTuckerAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Dawn::
	trainerbattle_single TRAINER_DAWN_HNS, Route19_Text_SwimmerfDawnSeen, Route19_Text_SwimmerfDawnBeaten
	msgbox Route19_Text_SwimmerfDawnAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Jerome::
	trainerbattle_single TRAINER_JEROME_HNS, Route19_Text_SwimmermJeromeSeen, Route19_Text_SwimmermJeromeBeaten
	msgbox Route19_Text_SwimmermJeromeAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Fatman::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FatmanBefore
	msgbox Route19_Text_Fisher1_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FatmanBefore::
	msgbox Route19_Text_Fisher2, MSGBOX_NPC
	end

Route19_EventScript_Sign::
	msgbox Route19_Text_Sign, MSGBOX_SIGN
	end

Route19_EventScript_SwimSign::
	msgbox Route19_Text_CarefulSwimmingSign, MSGBOX_SIGN
	end

CherryGroveCity_EventScript_Kingler::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KINGLER, CRY_MODE_NORMAL
	msgbox Route19_Text_Kingler, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route19_EventScript_Fisher::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FisherBefore
	msgbox Route19_Text_Fisher2_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FisherBefore::
	msgbox Route19_Text_FisherBefore, MSGBOX_NPC
	end

Route19_EventScript_Item_Brine::
    finditem ITEM_TM_BRINE
    end

Route19_Text_SwimmermHaroldSeen:
	.string "יצא לך פעם לשחות בים\n"
	.string "בלילה?$"

Route19_Text_SwimmermHaroldBeaten:
	.string "גלוב…$"

Route19_Text_SwimmermHaroldAfterBattle:
	.string "בלילה הים נהיה שחור. מרגישים\n"
	.string "כאילו הוא עומד לבלוע אותך.$"

Route19_Text_SwimmermTuckerSeen:
	.string "הא, הא… רק… עוד…\p"
	.string "קצת… עד… פושיה…$"

Route19_Text_SwimmermTuckerBeaten:
	.string "אני טובע!$"

Route19_Text_SwimmermTuckerAfterBattle:
	.string "הזמנתי… את החברה שלי לשחות\n"
	.string "עד פושיה… הא…$"

Route19_Text_SwimmerfDawnSeen:
	.string "אנשים חלשלושים מגעילים אותי!$"

Route19_Text_SwimmerfDawnBeaten:
	.string "בשחייה הייתי מנצחת אותך…$"

Route19_Text_SwimmerfDawnAfterBattle:
	.string "זו שחייה קצרה בין פושיה\n"
	.string "לאיי הקצף…\p"
	.string "נו באמת, איזה גבר גדול החבר שלי!\n"
	.string "איזה חלשלוש!$"

Route19_Text_SwimmermJeromeSeen:
	.string "שחייה? אני גרוע בזה.\p"
	.string "אני סתם משתכשך פה\n"
	.string "במים הרדודים.$"

Route19_Text_SwimmermJeromeBeaten:
	.string "חשבתי שאוכל לנצח.$"

Route19_Text_SwimmermJeromeAfterBattle:
	.string "אולי אני גרוע בשחייה, אבל\n"
	.string "אני אוהב את הים.$"

Route19_Text_Fisher1:
	.string "Sorry. This road is closed for\n"
	.string "construction.\p"
	.string "If you want to get to CINNABAR,\n"
	.string "you'd better go south from PALLET\n"
	.string "TOWN.$"

Route19_Text_Kingler:
	.string "קינגלר: קיייייייייייי$"

Route19_Text_Fisher1_RocksCleared:
	.string "אני כולי מיוזע. הגיע הזמן לשחות!$"

Route19_Text_Fisher2:
	.string "אוף, הקינגלר חוסם את החוף.$"

Route19_Text_FisherBefore:
	.string "אי אפשר לדוג\n"
	.string "עד שהקינגלר האלה יסתלקו מפה.$"

Route19_Text_Fisher2_RocksCleared:
	.string "הקינגלר האלה סוף סוף הלכו!\p"
	.string "עכשיו אני יכול לחזור לדוג.$"

Route19_Text_Sign:
	.string "דרך 19\p"
	.string "העיר פושיה - איי הקצף$"

Route19_Text_CarefulSwimmingSign:
	.string "Please be careful if you are\n"
	.string "swimming to SEAFOAM ISLANDS.\p"
	.string "FUCHSIA POLICE$"

