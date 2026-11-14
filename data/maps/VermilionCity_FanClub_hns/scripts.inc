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
	.string "אני יושב הראש של מועדון\n"
	.string "מעריצי הפוקימונים.\p"
	.string "גידלתי יותר מ-150 פוקימונים.\p"
	.string "אני מאוד בררן כשזה נוגע\n"
	.string "לפוקימונים.\p"
	.string "באת לבקר רק כדי לשמוע על\n"
	.string "הפוקימונים שלי?$"

PokemonFanClub_Text_Chairman_Rapidash:
	.string "יופי! אז תקשיב!\p"
	.string "אז… הרפידאש האהוב עליי…\p"
	.string "הוא… חמוד… מקסים… חכם…\n"
	.string "בצורה בלתי נסבלת… וגם… מדהים…\p"
	.string "אוי… גם אתה חושב ככה?… יותר מדי…\n"
	.string "פראי… יפהפה… אדיב… אוהב אותו!\p"
	.string "מחבק אותו… כש… ישן… חמים ורך…\n"
	.string "אה, ו… מרהיב… מהמם… פשוט אלוהי…\p"
	.string "אופס! איך הזמן עף!\n"
	.string "עיכבתי אותך יותר מדי!$"

PokemonFanClub_Text_Chairman_Gift:
	.string "תודה שהקשבת לי.\n"
	.string "אני רוצה שזה יהיה שלך!$"

PokemonFanClub_Text_Chairman_Candy:
	.string "זה ממתק נדיר שמחזק\n"
	.string "פוקימונים.\p"
	.string "אני מעדיף לחזק את הפוקימונים\n"
	.string "שלי בקרבות, אז הוא שלך.$"

PokemonFanClub_Text_Chairman_MoreTales:
	.string "שלום, {PLAYER}!\p"
	.string "באת שוב לשמוע על\n"
	.string "הפוקימונים שלי?\p"
	.string "לא? אוי… היו לי עוד סיפורים\n"
	.string "לספר…$"

PokemonFanClub_Text_Chairman_Disappointed:
	.string "כמה מאכזב…\p"
	.string "תחזור אם תרצה להקשיב.$"

PokemonFanClub_Text_Receptionist:
	.string "יושב הראש שלנו מדבר המון\n"
	.string "כשזה נוגע לפוקימונים…$"

@=Clefairy=Guy=========================================================================================================
PokemonFanClub_Text_ClefairyGuy_Adorable:
	.string "אני אוהב איך שקלפרי מנענע את האצבע\n"
	.string "שלו כשהוא מנסה להשתמש בפעמן.\p"
	.string "זה כל כך מקסים!$"

PokemonFanClub_Text_ClefairyGuy_MakingDo:
	.string "אני אוהב את קלפרי, אבל אף פעם\n"
	.string "לא הצלחתי לתפוס אחד.\p"
	.string "אז אני מסתפק בבובת פוקימון\n"
	.string "שמצאתי.$"

PokemonFanClub_Text_ClefairyGuy_ReturnDoll:
	.string "אה, עכשיו אני מבין. הילדה שאיבדה\n"
	.string "את בובת הפוקימון הזאת עצובה…\p"
	.string "בסדר. תוכל להחזיר את הבובה\n"
	.string "לילדה הקטנה והמסכנה ההיא?\p"
	.string "יום אחד אתיידד בעצמי עם\n"
	.string "קלפרי אמיתי. אל דאגה!$"

PokemonFanClub_Text_ClefairyGuy_GoingToGetOne:
	.string "רק תראה. אני עוד אשיג לי\n"
	.string "קלפרי אמיתי בתור חבר.$"

@============================================================================================================================

PokemonFanClub_Text_Teacher:
	.string "הנה הבייליף המתוק שלי!\p"
	.string "העלה על הראש שלו כל כך חמוד!$"

PokemonFanClub_Text_ClefairyDoll:
	.string "It's a CLEFAIRY! Huh?\p"
	.string "Oh, right. It's a CLEFAIRY POKé\n"
	.string "DOLL.$"

PokemonFanClub_Text_Bayleef:
	.string "בייליף: לי לייף!$"

PokemonFanClub_Text_Listen:
	.string "Let's all listen politely to\n"
	.string "other trainers.$"

PokemonFanClub_Text_Bragging:
	.string "If someone brags, brag right\n"
	.string "back!$"
