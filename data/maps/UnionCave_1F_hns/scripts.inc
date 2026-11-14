UnionCave_1F_hns_MapScripts::
	.byte 0


UnionCave_1F_Trigger_Monview::
	special SpawnCameraObject
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkRight1
	waitmovement 0
	message Route29_Text_PressAorB
	waitbuttonpress
	closemessage
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_CAMERA, Common_Movement_WalkLeft1
	waitmovement 0
	special RemoveCameraObject
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	end


UnionCave_1F_EventScript_HikerRussell::
	trainerbattle_single TRAINER_RUSSELL_HNS, UnionCave_1F_Text_HikerRussellSeen, UnionCave_1F_Text_HikerRussellBeaten
	msgbox UnionCave_1F_Text_HikerRussellAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_PokemaniacLarry::
	trainerbattle_single TRAINER_LARRY_HNS, UnionCave_1F_Text_PokemaniacLarrySeen, UnionCave_1F_Text_PokemaniacLarryBeaten
	msgbox UnionCave_1F_Text_PokemaniacLarryAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_HikerDaniel::
	trainerbattle_single TRAINER_DANIEL_HNS, UnionCave_1F_Text_HikerDanielSeen, UnionCave_1F_Text_HikerDanielBeaten
	msgbox UnionCave_1F_Text_HikerDanielAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherBill::
	trainerbattle_single TRAINER_BILL_HNS, UnionCave_1F_Text_FirebreatherBillSeen, UnionCave_1F_Text_FirebreatherBillBeaten
	msgbox UnionCave_1F_Text_FirebreatherBillAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_1F_EventScript_FirebreatherRay::
	trainerbattle_single TRAINER_RAY_HNS, UnionCave_1F_Text_FirebreatherRaySeen, UnionCave_1F_Text_FirebreatherRayBeaten
	msgbox UnionCave_1F_Text_FirebreatherRayAfter, MSGBOX_AUTOCLOSE
	end	

UnionCave_1F_EventScript_Item_Potion::
	finditem ITEM_POTION
	end

UnionCave_1F_EventScript_Item_GreatBall::
	finditem ITEM_GREAT_BALL
	end

UnionCave_1F_EventScript_Item_Xattack::
	finditem ITEM_X_ATTACK
	end

UnionCave_1F_EventScript_Item_Awakening::
	finditem ITEM_AWAKENING
	end

UnionCave_1F_Text_HikerRussellSeen:
	.string "בדרך לאזייליה, הא?\p"
	.string "הפוקימונים שלי יבדקו אם יש לך\n"
	.string "מה שצריך בשביל קרב.$"

UnionCave_1F_Text_HikerRussellBeaten:
	.string "אוי, אוי, אוי!$"

UnionCave_1F_Text_HikerRussellAfter:
	.string "טוב, זהו! החלטתי.\p"
	.string "אני לא זז מפה עד\n"
	.string "שהפוקימונים שלי יתחשלו!$"

UnionCave_1F_Text_PokemaniacLarrySeen:
	.string "אני נודד למרחקים בחיפוש\n"
	.string "אחרי פוקימונים.\p"
	.string "גם אתה מחפש פוקימונים?\p"
	.string "אז אתה היריב שלי באיסוף!$"

UnionCave_1F_Text_PokemaniacLarryBeaten:
	.string "אוף. הפוקימונים המסכנים שלי…$"

UnionCave_1F_Text_PokemaniacLarryAfter:
	.string "לפעמים אפשר לשמוע שאגות של\n"
	.string "פוקימונים מעומק המערה.$"

UnionCave_1F_Text_HikerDanielSeen:
	.string "וואו! איזו הפתעה!\p"
	.string "לא ציפיתי לראות פה אף אחד!$"

UnionCave_1F_Text_HikerDanielBeaten:
	.string "וואו! הפסדתי בגדול!$"

UnionCave_1F_Text_HikerDanielAfter:
	.string "עבדו עליי ושכנעו אותי לקנות\n"
	.string "זנב סלופוק.\p"
	.string "אני מרחם על הפוקימון המסכן.$"

UnionCave_1F_Text_FirebreatherBillSeen:
	.string "מהלך העל-קולי של זובאט מבלבל\n"
	.string "שוב ושוב את הפוקימונים שלי.\p"
	.string "זה ממש מרגיז אותי!$"

UnionCave_1F_Text_FirebreatherBillBeaten:
	.string "הלהבה שלי כבתה!$"

UnionCave_1F_Text_FirebreatherBillAfter:
	.string "בסופי שבוע אפשר לשמוע שאגות\n"
	.string "מוזרות מעומק המערה.$"

UnionCave_1F_Text_FirebreatherRaySeen:
	.string "כשיש אור, מערה לא מפחידה.\p"
	.string "כשחזקים, פוקימונים לא מפחידים.$"

UnionCave_1F_Text_FirebreatherRayBeaten:
	.string "הבזק!$"

UnionCave_1F_Text_FirebreatherRayAfter:
	.string "האש של הפוקימון שלי היא שמאירה\n"
	.string "את המערה הזאת.$"
