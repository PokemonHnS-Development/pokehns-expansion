DiglettsCave_EntranceNorth_hns_MapScripts::
	.byte 0


DiglettsCave_EntranceNorth_EventScript_Brock::
    lock
    faceplayer
    msgbox DiglettsCave_EntranceNorth_Text_Brock, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DIGLETT_BROCK
    removeobject LOCALID_DIGLETT_BROCK
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_BROCK
    release
    end

DiglettsCave_EntranceNorth_Text_Brock:
    .string "ברוק: מקומות קטנים מוקפי סלעים\n"
    .string "משרים תחושת שלווה, נכון?\p"
    .string "אם תרצה עוד קרב, אהיה\n"
    .string "בדוג'ו הלחימה.$"




