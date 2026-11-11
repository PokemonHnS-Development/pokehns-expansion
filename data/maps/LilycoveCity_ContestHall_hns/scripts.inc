@ All the LOCALID constants used in this file are essentially redundant.
@ They're all used to have the NPC the player talked to turn back so they're facing
@ their original direction (because they're watching/participating in the contests).
@ They could all be substituted for VAR_LAST_TALKED.
LilycoveCity_ContestHall_hns_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1_hns::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2_hns::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl_hns::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor_hns::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1_hns::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1_hns::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear_hns, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest_hns:
	.string "הפוקימון הזה כבר ניצח כאן פעם\n"
	.string "בתחרות יופי.\p"
	.string "ונחש מה? היום הבאתי אותו\n"
	.string "לנצח בתחרות חוכמה!\p"
	.string "היכולות שלי מפחידות אפילו אותי…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests_hns:
	.string "השתתפתי בהמון תחרויות,\n"
	.string "אז אני מתחיל להבין איך זה עובד.\p"
	.string "בתחרות מגניבות, מהלכים מגניבים\n"
	.string "מתקבלים היטב כהופעה.\p"
	.string "אבל מהלכים חכמים ומהלכים חמודים,\n"
	.string "למשל, לא מתקבלים היטב.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks_hns:
	.string "לבחור הצעיר שניצח קודם היו\n"
	.string "המון פוקיבלוקים מסוגים שונים.\p"
	.string "אפשר לנצח אם יש כל כך הרבה\n"
	.string "מהדברים האלה?$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous_hns:
	.string "וואו, המקום הזה ענקי!\p"
	.string "המתח באוויר… זה לא כמו\n"
	.string "אולם תחרויות באיזה חור נידח.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal_hns:
	.string "מנחה: ובכן, פוקימונים חכמים\n"
	.string "ומאמניהם, אתם מוכנים?!\p"
	.string "תנו את המיטב שלכם!\n"
	.string "שיתחילו ההופעות!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest_hns:
	.string "שופט: נהנים מהתחרות?\p"
	.string "אפשר לחזור עם שלושה חברים, ואז\n"
	.string "כולכם תוכלו להשתתף בתחרות!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest_hns:
	.string "איי-יי-יי-יי…\n"
	.string "נרשמתי לתחרות הלא נכונה.\p"
	.string "רשמתי את הפוקימון הקשוח הזה\n"
	.string "לתחרות החוכמה…\p"
	.string "קדימה, תדהים אותם עם ניפוץ סלע\n"
	.string "שנראה חכם.$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart_hns:
	.string "השקעתי שנים רבות ואת כל חוכמתי\n"
	.string "כדי שהפוקימון הזה יהיה חכם.\p"
	.string "הוא לא יובס בקלות על ידי\n"
	.string "הפוקימון של איזה פרחח צעיר.\p"
	.string "אשתי היקרה, את רואה את זה?$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext_hns:
	.string "הנה זה!\p"
	.string "אם הפוקימון שלי יבצע עכשיו מהלך\n"
	.string "חכם, ההתלהבות של הקהל תגיע לשיא!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife_hns:
	.string "אוי ואבוי!\p"
	.string "הזובאט המתוק שלי עושה התעלקות\n"
	.string "כל כך חמודה, שהשתמשתי בה שוב ושוב!\p"
	.string "אבל האנשים המרושעים האלה בכלל\n"
	.string "לא מעריכים את זה!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa_hns:
	.string "קיאאאה! אתה יפהפה, סבא!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves_hns:
	.string "גם כשמאמנים רושמים אותו סוג פוקימון,\n"
	.string "כל אחד מופיע עם מהלכים אחרים.\p"
	.string "בדיוק כמו שלאנשים יש סגנונות\n"
	.string "שונים בקרב.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers_hns:
	.string "לדעתי הפוקימונים נראים חכמים\n"
	.string "יותר מהמאמנים שלהם. בהרבה.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests_hns:
	.string "בסופו של דבר, אני עדיין אוהבת\n"
	.string "תחרויות חוכמה.\p"
	.string "הצבע הירוק האינטלקטואלי הזה…\n"
	.string "הוא כל כך… כל כך… מגניב.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest_hns:
	.string "מנחה: גם אתה משתתף בתחרות\n"
	.string "היופי? בהצלחה!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty_hns:
	.string "שופט: אה, כל פוקימון כאן הוא\n"
	.string "מופת של יופי טהור!\p"
	.string "אוי, כמעט שכחתי לתת להם ציון!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty_hns:
	.string "פוקימון יפה כל כך…\n"
	.string "אין עוד אחד כמוהו.\p"
	.string "העיניים של כולם יהיו דבוקות\n"
	.string "ליפהפה שלי.$"

LilycoveCity_ContestHall_Text_OverdidGrooming_hns:
	.string "וואאאה!\p"
	.string "הברשתי וטיפחתי את הפוקימון שלי\n"
	.string "בקפידה לקראת התחרות…\p"
	.string "אבל הגזמתי…\n"
	.string "הפרווה של הפוקימון שלי נהייתה פרועה…\p"
	.string "מה אני אעשה?$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam_hns:
	.string "המהלך קרן זוהרת שלי כל כך מסנוור,\n"
	.string "שהשופט לא יוכל לראות אותו.\p"
	.string "אה, רגע אחד…\n"
	.string "אז זה יהיה חסר טעם!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe_hns:
	.string "הפוקימון היפה הזה נראה בדיוק\n"
	.string "כמוני כשהייתי צעירה.\p"
	.string "ברגע שאמרתי את זה, בעלי התיז\n"
	.string "את הקפה ששתה.\p"
	.string "אמרתי משהו מצחיק?$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy_hns:
	.string "האמת, כשאני מנצחת בתחרות יופי,\n"
	.string "זה בהחלט משמח אותי.\p"
	.string "יותר מהרגיל, בכל אופן.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon_hns:
	.string "וואהאהאהא!\p"
	.string "תראו את כל הפוקימונים היפים האלה!\n"
	.string "אני פשוט מת על כל הזוהר הזה!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone_hns:
	.string "אי אפשר תמיד לנצח רק בזכות\n"
	.string "היופי.\p"
	.string "צריך לטפח את הפוקימון כך\n"
	.string "שיהיה מבריק ויפה כמו שלי.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest_hns:
	.string "מנחה: אוי! שלום!\n"
	.string "אנחנו באמצע תחרות!\p"
	.string "בבקשה להירשם בדלפק ההרשמה\n"
	.string "ולעלות לבמה, בסדר?$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals_hns:
	.string "שופט: אה, אילו הופעות מקסימות\n"
	.string "וחמודות!\p"
	.string "אלוהים אדירים! איזו הופעה מתוקה\n"
	.string "להפליא עם משחק מים!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted_hns:
	.string "אוי, לא… האזוריל המתוק שלי\n"
	.string "איבד ריכוז בגלל פוקימון אחר.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest_hns:
	.string "הפוקימון שלי אף פעם לא ניצח בקרב,\n"
	.string "אבל בתחרות? כדאי להיזהר ממנו!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel_hns:
	.string "המהלך מחול אביב של הפוקימון שלי\n"
	.string "הוא פלא של אלגנטיות.\p"
	.string "לא אתן לאף אחד להפריע\n"
	.string "להופעה שלו.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter_hns:
	.string "הפוקימונים של כולם חמודים מאוד.\p"
	.string "אבל אם הפוקימון שלי היה מציג\n"
	.string "הופעה חמודה…\p"
	.string "אני בטוחה שהוא היה הרבה\n"
	.string "יותר חמוד מהאחרים.$"

LilycoveCity_ContestHall_Text_MyChildIsInContest_hns:
	.string "הילד שלי משתתף בתחרות הזאת.$"

LilycoveCity_ContestHall_Text_ComeOnDear_hns:
	.string "קדימה, מותק! לך על זה!\n"
	.string "הפוקימון שלך הכי טוב!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest_hns:
	.string "נראה לי שהבחורה ההיא שם היא\n"
	.string "הכי חמודה מכולם.\p"
	.string "מה? שופטים את הפוקימונים לפי\n"
	.string "המראה שלהם?$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn_hns:
	.string "אוו, כשאני רואה את כל הפוקימונים\n"
	.string "החמודים האלה, בא לי פוקימון משלי!\p"
	.string "אני הולכת לתפוס כמה!$"

LilycoveCity_ContestHall_Text_BeautyContestStage_hns:
	.string "במת תחרות היופי\n"
	.string "התפתו לפוקימונים יפים!$"

LilycoveCity_ContestHall_Text_CuteContestStage_hns:
	.string "במת תחרות החמידות\n"
	.string "התאהבו בפוקימונים חמודים!$"

LilycoveCity_ContestHall_Text_SmartContestStage_hns:
	.string "במת תחרות החוכמה\n"
	.string "התרשמו מפוקימונים חכמים!$"

