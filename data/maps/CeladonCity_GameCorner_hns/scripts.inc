CeladonCity_GameCorner_hns_MapScripts::
	.byte 0

CeladonGameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanM, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Teacher::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Teacher, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_FishingGuru::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_FishingGuru, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_Fisher1::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher1, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Fisher2::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher2, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_GymGuide::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_GymGuide, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Gramps::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Gramps, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_PokefanF::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonGameCorner_Text_PokefanM:
	.string "כל מכונות המזל כאן\n"
	.string "חדישות ביותר.$"

CeladonGameCorner_Text_Teacher:
	.string "אני רוצה דווקא את המכונה הזאת.\p"
	.string "אתמול היא רוששה אותי, אז היום\n"
	.string "היא אמורה לשלם.$"

CeladonGameCorner_Text_FishingGuru:
	.string "I think this slot machine will pay\n"
	.string "out…\p"
	.string "The odds vary among machines.$"

CeladonGameCorner_Text_Fisher1:
	.string "גאהאהאהא!\p"
	.string "המטבעות פשוט לא מפסיקים להגיע!\p"
	.string "המ? מה, ילד? אתה רוצה לשחק?\p"
	.string "אחלוק איתך את המזל שלי!$"

CeladonGameCorner_Text_Fisher2:
	.string "גאהאהאהא!\p"
	.string "זה עושה לי טוב לעשות דברים\n"
	.string "נחמדים בשביל אחרים!$"

CeladonGameCorner_Text_GymGuide:
	.string "היי! אלוף לעתיד!\p"
	.string "גם אתה משחק במכונות המזל?\p"
	.string "אני מנסה לאסוף מספיק מטבעות\n"
	.string "בשביל פוקימון פרס.\p"
	.string "אבל עוד אין לי מספיק מטבעות…$"

CeladonGameCorner_Text_PokefanF:
	.string "רולטה…\p"
	.string "אני מעדיף אותה על פני מכונות המזל,\n"
	.string "כי קל יותר לחשב את הסיכויים.\p"
	.string "אבל הזכייה נמוכה הרבה יותר.$"

CeladonGameCorner_Text_Gramps:
	.string "הממם… הסיכויים בטח טובים יותר\n"
	.string "אם אשים הכל על כחול, אבל… מה לעשות?$"

CeladonGameCorner_Text_Woman:
	.string "אני לא מפסיקה לנצח!$"
