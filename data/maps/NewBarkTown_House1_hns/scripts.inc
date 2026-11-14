NewBarkTown_House1_hns_MapScripts::
	.byte 0

NewBarkTown_House1_EventScript_Mother::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_Neighbor, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_EventScript_Daughter::
	lock
	faceplayer
	msgbox NewBarkTown_House1_Text_NeighborsDaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House1_Text_NeighborsDaughter:
	.string "פיקאצ'ו הוא פוקימון שעבר התפתחות.\p"
	.string "התגליות של פרופ' אלם\n"
	.string "ממש הדהימו אותי.\p"
	.string "הוא כל כך מפורסם בזכות\n"
	.string "המחקר שלו על התפתחות פוקימונים.\p"
	.string "…אנחה…\p"
	.string "הלוואי שיכולתי להיות חוקרת\n"
	.string "כמוהו…$"


NewBarkTown_House1_Text_Neighbor:
	.string "הבת שלי נחושה בדעתה\n"
	.string "להיות העוזרת של פרופ' אלם.\p"
	.string "היא ממש אוהבת פוקימונים!\p"
	.string "אבל בעצם, גם אני!$"

