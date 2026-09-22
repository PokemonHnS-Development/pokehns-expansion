.set REWARD_TYPE, VAR_0x8004
.set REWARD_ITEM, VAR_0x8008

CeruleanCity_House4_Frlg_MapScripts::
	.byte 0

CeruleanCity_House4_EventScript_WonderNewsBerryMan::
	lock
	specialvar REWARD_TYPE, WonderNews_GetRewardInfo
	copyvar REWARD_ITEM, VAR_RESULT
	goto_if_eq REWARD_TYPE, NEWS_REWARD_NONE,       CeruleanCity_House4_EventScript_NoNews
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_SMALL, CeruleanCity_House4_EventScript_Reward_RecvSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_RECV_BIG,   CeruleanCity_House4_EventScript_Reward_RecvBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_WAITING,    CeruleanCity_House4_EventScript_Waiting
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_SMALL, CeruleanCity_House4_EventScript_Reward_SentSmall
	goto_if_eq REWARD_TYPE, NEWS_REWARD_SENT_BIG,   CeruleanCity_House4_EventScript_Reward_SentBig
	goto_if_eq REWARD_TYPE, NEWS_REWARD_AT_MAX,     CeruleanCity_House4_EventScript_AtMax
	end

@ Mystery Gift is not enabled, or the player has no saved Wonder News
CeruleanCity_House4_EventScript_NoNews::
	msgbox CeruleanCity_House4_Text_NothingEntertaining
	release
	end

@ Small reward for receiving Wonder News from friend
CeruleanCity_House4_EventScript_Reward_RecvSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_NewNewsInformativeHaveThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for receiving Wonder News from non-friend source
CeruleanCity_House4_EventScript_Reward_RecvBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_IncredibleNewsHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has not recently sent Wonder News
CeruleanCity_House4_EventScript_Waiting::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_WishCouldShareNewsWithOthers
	release
	end

@ Small reward for sending Wonder News every 1-3 times
CeruleanCity_House4_EventScript_Reward_SentSmall::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_ThanksForSpreadingNewsTakeThis
	giveitem REWARD_ITEM
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Big reward for sending Wonder News every 4th time
CeruleanCity_House4_EventScript_Reward_SentBig::
	call CeruleanCity_House4_EventScript_MovementReactionToNews
	msgbox CeruleanCity_House4_Text_MagnificentNewsSpreadHaveBerries
	giveitem REWARD_ITEM, 4
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House4_EventScript_NoRoomForBerries
	release
	end

@ Player has hit reward limit and must wait to receive new rewards
CeruleanCity_House4_EventScript_AtMax::
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox CeruleanCity_House4_Text_EnjoyingMyselfWithAllSortsOfNews
	release
	end

CeruleanCity_House4_EventScript_MovementReactionToNews::
	playse SE_PIN
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_WONDER_NEWS_BERRY_MAN, Common_Movement_Delay48
	waitmovement 0
	return

CeruleanCity_House4_EventScript_NoRoomForBerries::
	msgbox CeruleanCity_House4_Text_YourBerryPouchIsFull
	release
	end

CeruleanCity_House4_Text_NothingEntertaining::
	.string "Suspiro...\n"
	.string "Tanto tiempo, tan poco que hacer…\p"
	.string "¿No pasa nada interesante\n"
	.string "anywhere?$"

CeruleanCity_House4_Text_NewNewsInformativeHaveThis::
	.string "Ah!\n"
	.string "¡Un nuevo reportaje!\p"
	.string "Hmm…\p"
	.string "¡Ya veo!\n"
	.string "¡Qué informativo fue!\p"
	.string "Aplausos por tu interés\n"
	.string "en las noticias a tu corta edad.\p"
	.string "Como agradecimiento por compartir\n"
	.string "las noticias, quiero que tengas esto.$"

CeruleanCity_House4_Text_IncredibleNewsHaveBerries::
	.string "Oh, oh!\n"
	.string "¡E-esta noticia!\p"
	.string "Hmm…\p"
	.string "Amazing!\n"
	.string "¡Qué noticia tan increíble!\p"
	.string "No he visto una noticia tan\n"
	.string "increíble en mucho tiempo!\p"
	.string "Gracias por compartir esta\n"
	.string "fantástica noticia. ¡Toma BAYAS!$"

CeruleanCity_House4_Text_WishCouldShareNewsWithOthers::
	.string "Sería una lástima no compartir\n"
	.string "esta noticia con otras personas…\p"
	.string "Ojalá pudiera contárselo a alguien…\n"
	.string "Que otros se enteren de la noticia…$"

CeruleanCity_House4_Text_ThanksForSpreadingNewsTakeThis::
	.string "Ah, ¿esparciste la noticia por mí?\p"
	.string "Good news becomes worthwhile when\n"
	.string "toda clase de gente la comparte.\p"
	.string "Como agradecimiento por correr\n"
	.string "la voz, ¡toma esto!$"

CeruleanCity_House4_Text_MagnificentNewsSpreadHaveBerries::
	.string "¿Sigues corriendo la voz?\n"
	.string "Magnificent!\p"
	.string "Esa noticia debe estar\n"
	.string "encantada de circular tanto.\p"
	.string "¡Así es!\p"
	.string "Considera esto una muestra\n"
	.string "appreciation from me and the news.\p"
	.string "I'll give you more BERRIES than\n"
	.string "I usually do.$"

CeruleanCity_House4_Text_EnjoyingMyselfWithAllSortsOfNews::
	.string "Me la estoy pasando muy bien con\n"
	.string "todo tipo de noticias.\p"
	.string "¡Sí, estoy satisfecho!\n"
	.string "No me aburriré en un tiempo.$"

CeruleanCity_House4_Text_YourBerryPouchIsFull::
	.string "¿Eh? Tu BOLSA BERRYS está llena.\n"
	.string "Mi regalo sigue sin entregar.$"

