CherrygroveCity_House1_hns_MapScripts::
	.byte 0

CherrygroveCity_House1_EventScript_Baldingman::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_House1_EventScript_Kid::
	lock
	faceplayer
	msgbox CherrygroveCity_GymSpeechHouse_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GymSpeechHouse_Text_PokefanM:
	.string "אתה רוצה לבדוק כמה אתה טוב\n"
	.string "בתור מאמן פוקימונים?\p"
	.string "כדאי לך לבקר במכוני הפוקימון\n"
	.string "בכל רחבי ג'וטו ולאסוף תגים.$"

CherrygroveCity_GymSpeechHouse_Text_BugCatcher:
	.string "כשאהיה גדול, אני אהיה\n"
	.string "מנהיג מכון!\p"
	.string "אני נותן לפוקימונים שלי להילחם\n"
	.string "בפוקימונים של החבר שלי כדי שיתחשלו!$"
