VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
	.string "אפשר לראות את הפוקימון שלך?\n"
	.string "אבדוק כמה הוא אוהב אותך.\p"
	.string "אה.\n"
	.string "הפוקימון שלך…$"

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
	.string "הוא מעריץ אותך. הוא לא יכול\n"
	.string "לאהוב אותך יותר מזה.\p"
	.string "אפילו אני שמחה לראות את זה.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
	.string "הוא נראה מאושר מאוד.\n"
	.string "ברור שהוא אוהב אותך מאוד מאוד.$"

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
	.string "הוא אוהב אותך די הרבה.\n"
	.string "נראה שהוא רוצה קצת פינוקים.$"

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
	.string "הוא מתחיל להתרגל אליך.\n"
	.string "נראה שהוא מאמין בך.$"

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
	.string "הוא עדיין לא ממש רגיל אליך.\n"
	.string "הוא לא אוהב אותך וגם לא שונא.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
	.string "הוא חשדן מאוד. יש בעיניים שלו\n"
	.string "אכזריות מפחידה.\p"
	.string "הוא בכלל לא אוהב אותך.$"

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
	.string "קצת קשה לי להגיד את זה…\p"
	.string "הפוקימון שלך פשוט מתעב אותך.\n"
	.string "זה לא מטריד אותך?$"

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
	.string "PIKACHU: Pika pika!$"

