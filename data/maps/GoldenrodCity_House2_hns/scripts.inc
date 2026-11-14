GoldenrodCity_House2_hns_MapScripts::
	.byte 0

GoldenrodCity_House2_EventScript_Man::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Man, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_House2_EventScript_Woman::
	faceplayer
	lock
	msgbox GoldenrodPPSpeechHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodPPSpeechHouse_Text_Man:
    .string "פעם, באמצע קרב, הפוקימון שלי\n"
    .string "לא הצליח לבצע אף מהלך.\p"
    .string "כל נקודות הכוח, או נ”כ,\n"
    .string "של המהלכים שלו נגמרו.$"

GoldenrodPPSpeechHouse_Text_Lass:
    .string "לפעמים גם פוקימון בריא\n"
    .string "לא יכול להשתמש במהלכים שלו.\p"
    .string "אם זה קורה, אפשר לרפא אותו\n"
    .string "במרכז פוקימון או להשתמש בפריט.$"
