CeladonCity_Apartments_RoofHouse_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_RoofHouse_EventScript_BlackBelt::
	lock 
	faceplayer
	goto_if_set FLAG_GOT_TM_SLEEP_TALK, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter
	msgbox CeladonMansionRoofHouse_Text_PharmacistIntro, MSGBOX_DEFAULT	
	goto_if_set FLAG_NIGHT_POKEMON, CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused
	msgbox CeladonMansionRoofHouse_Text_PharmacistStory, MSGBOX_NPC
	giveitem ITEM_TM_SLEEP_TALK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_SLEEP_TALK
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltRefused::
	msgbox CeladonMansionRoofHouse_Text_PharmacistNotNight, MSGBOX_NPC
	closemessage
	release
	end

CeladonCity_Apartments_RoofHouse_EventScript_BlackBeltAfter::
	msgbox CeladonMansionRoofHouse_Text_PharmacistCurse, MSGBOX_NPC
	release
	end

CeladonMansionRoofHouse_Text_PharmacistIntro:
	.string "אספר לך סיפור מצמרר…$"

CeladonMansionRoofHouse_Text_PharmacistNotNight:
	.string "מצד שני, זה לא כל כך מפחיד\n"
	.string "כשעדיין אור בחוץ.\p"
	.string "תחזור אחרי השקיעה, טוב?$"

CeladonMansionRoofHouse_Text_PharmacistStory:
	.string "היה היה פעם ילד קטן\n"
	.string "שקיבל אופניים חדשים…\p"
	.string "הוא רצה לנסות אותם מיד…\p"
	.string "היה לו כל כך כיף, שהוא\n"
	.string "לא שם לב שהשמש שקעה…\p"
	.string "כשרכב הביתה בלילה החשוך,\n"
	.string "האופניים פתאום האטו!\p"
	.string "הדוושות נעשו כבדות!\p"
	.string "כשהוא הפסיק לדווש, האופניים\n"
	.string "התחילו להחליק אחורה!\p"
	.string "כאילו האופניים היו מקוללים\n"
	.string "וניסו לגרור אותו אל התהום!\p"
	.string "…\p"
	.string "…\p"
	.string "אאאאאאאה!\p"
	.string "הילד בסך הכל רכב בעלייה\n"
	.string "בשביל האופניים!\p"
	.string "…\n"
	.string "בא-דום בא-דום!\p"
	.string "על זה שהקשבת בסבלנות כזו,\n"
	.string "קבל את זה - מ”מ 82!$"

CeladonMansionRoofHouse_Text_PharmacistCurse:
	.string "מ”מ 82 הוא דיבור שינה.\p"
	.string "הוא מאפשר לפוקימון שלך להשתמש\n"
	.string "במהלך אקראי בזמן שהוא ישן.\p"
	.string "אבל בהצלחה להירדם אחרי\n"
	.string "הסיפור המפחיד הזה!$"

