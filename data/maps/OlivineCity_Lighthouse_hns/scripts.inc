OlivineCity_Lighthouse_hns_MapScripts::
	.byte 0

OlivineLighthouse_EventScript_Item_Ether::
    finditem ITEM_ETHER
    end

OlivineLighthouse_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

OlivineLighthouse_EventScript_Item_TMSwagger::
    finditem ITEM_TM_SWAGGER
    end

OlivineLighthouse_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end

OlivineLighthouse_EventScript_Item_Protein::
    finditem ITEM_PROTEIN
    end

OlivineLighthouse_EventScript_1FSailor::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_EventScript_1FPokefanF::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_1FSailor:
	.string "אנשים מתאמנים במגדלור הזה.\p"
	.string "לא קל לטפס כשכל המאמנים\n"
	.string "האלה מחכים בפנים.$"

OlivineLighthouse_Text_1FPokefanF:
	.string "פעם, פוקימונים היו מאירים בלילה\n"
	.string "את הים שסביב אוליבין.\p"
	.string "המגדלור נבנה לכבוד\n"
	.string "הפוקימונים האצילים האלה.$"

@2nd floor==============================================================================================================================

OlivineLighthouse_EventScript_Huey::
	trainerbattle_single TRAINER_HUEY_HNS, OlivineLighthouse_Text_SailorHueySeen, OlivineLighthouse_Text_SailorHueyBeaten, OlivineLighthouse_EventScript_RegisterHuey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, OlivineLighthouse_EventScript_RematchHuey
	msgbox OlivineLighthouse_Text_SailorHueyAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_RegisterHuey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox OlivineLighthouse_Text_HueyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_HUEY_HNS
	release
	end

OlivineLighthouse_EventScript_RematchHuey::
	trainerbattle_rematch TRAINER_HUEY_HNS, OlivineLighthouse_Text_HueyRematchIntro, OlivineLighthouse_Text_HueyRematchDefeat
	msgbox OlivineLighthouse_Text_HueyPostRematch, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_GentlemanAlfred::
    trainerbattle_single TRAINER_ALFRED_HNS, OlivineLighthouse_Text_GentlemanAlfredSeen, OlivineLighthouse_Text_GentlemanAlfredBeaten
    msgbox OlivineLighthouse_Text_GentlemanAlfredAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorHueySeen:
	.string "אנשי הים תמיד\n"
	.string "מחפשים קרב טוב!$"

OlivineLighthouse_Text_SailorHueyBeaten:
	.string "אוף!\n"
	.string "הפסדתי!$"

OlivineLighthouse_Text_SailorHueyAfter:
	.string "איזה כוח! מה דעתך\n"
	.string "להפליג איתי בימים?$"

OlivineLighthouse_Text_HueyRegister:
	.string "איזה כוח! מה דעתך\n"
	.string "להפליג איתי בימים?$"

OlivineLighthouse_Text_HueyRematchIntro:
	.string "אנשי הים תמיד\n"
	.string "מחפשים קרב טוב!$"

OlivineLighthouse_Text_HueyRematchDefeat:
	.string "אוף!\n"
	.string "הפסדתי!$"

OlivineLighthouse_Text_HueyPostRematch:
	.string "איזה כוח! מה דעתך\n"
	.string "להפליג איתי בימים?$"

OlivineLighthouse_Text_GentlemanAlfredSeen:
	.string "הממ? זה לא מקום\n"
	.string "למשחקים.$"

OlivineLighthouse_Text_GentlemanAlfredBeaten:
	.string "אה! אני רואה\n"
	.string "שאתה רציני.$"

OlivineLighthouse_Text_GentlemanAlfredAfter:
	.string "למעלה יש פוקימון שמאיר\n"
	.string "את המגדלור.\p"
	.string "אבל שמעתי שהוא חולה עכשיו,\n"
	.string "ושאי אפשר לרפא אותו בדרך רגילה.$"

@3rd floor==============================================================================================================================

OlivineLighthouse_EventScript_BirdKeeperTheo::
    trainerbattle_single TRAINER_THEO_HNS, OlivineLighthouse_Text_BirdKeeperTheoSeen, OlivineLighthouse_Text_BirdKeeperTheoBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperTheoAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_SailorTerrell::
    trainerbattle_single TRAINER_TERRELL_HNS, OlivineLighthouse_Text_SailorTerrellSeen, OlivineLighthouse_Text_SailorTerrellBeaten
    msgbox OlivineLighthouse_Text_SailorTerrellAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_GentlemanPreston::
    trainerbattle_single TRAINER_PRESTON_HNS, OlivineLighthouse_Text_GentlemanPrestonSeen, OlivineLighthouse_Text_GentlemanPrestonBeaten
    msgbox OlivineLighthouse_Text_GentlemanPrestonAfter, MSGBOX_AUTOCLOSE
    end


OlivineLighthouse_Text_BirdKeeperTheoSeen:
	.string "מה אתה עושה פה? באת רק\n"
	.string "לבהות? כדאי לך ללכת!$"

OlivineLighthouse_Text_BirdKeeperTheoBeaten:
	.string "אתה באמת דואג\n"
	.string "לפוקימון החולה…$"

OlivineLighthouse_Text_BirdKeeperTheoAfter:
	.string "איך לעזאזל עולים למעלה?\p"
	.string "אני רוצה לבקר את הפוקימון החולה,\n"
	.string "אבל אני לא מצליח לעלות לשם…$"

OlivineLighthouse_Text_SailorTerrellSeen:
	.string "מלחים הם גם טובי לב\n"
	.string "וגם חזקים. ומה איתך?$"

OlivineLighthouse_Text_SailorTerrellBeaten:
	.string "אתה גם טוב לב וגם חזק…$"

OlivineLighthouse_Text_SailorTerrellAfter:
	.string "בכל פעם שאני חוזר לאוליבין,\n"
	.string "אני מבקר במכון.\p"
	.string "סוג הפוקימונים של המנהיגה\n"
	.string "השתנה בלי ששמתי לב.$"

OlivineLighthouse_Text_GentlemanPrestonSeen:
	.string "אני מטייל בעולם כדי לאמן את\n"
	.string "הפוקימונים שלי. ברצוני להילחם בך.$"

OlivineLighthouse_Text_GentlemanPrestonBeaten:
	.string "…אנחה… עליי להתאמן עוד…$"

OlivineLighthouse_Text_GentlemanPrestonAfter:
	.string "ג'סמין השתמשה פעם בפוקימונים\n"
	.string "מסוג סלע, כמו אוניקס.$"

@4th floor==============================================================================================================================

OlivineLighthouse_EventScript_SailorKent::
    trainerbattle_single TRAINER_KENT_HNS, OlivineLighthouse_Text_SailorKentSeen, OlivineLighthouse_Text_SailorKentBeaten
    msgbox OlivineLighthouse_Text_SailorKentAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_LassConnie::
    trainerbattle_single TRAINER_CONNIE_HNS, OlivineLighthouse_Text_LassConnieSeen, OlivineLighthouse_Text_LassConnieBeaten
    msgbox OlivineLighthouse_Text_LassConnieAfter, MSGBOX_AUTOCLOSE
    end


OlivineLighthouse_Text_SailorKentSeen:
	.string "ג'סמין בטח מתה מדאגה\n"
	.string "לפוקימון שכאן.\p"
	.string "בימים אלה היא אפילו לא מחייכת.$"

OlivineLighthouse_Text_SailorKentBeaten:
	.string "גם אני לא מצליח לחייך…$"

OlivineLighthouse_Text_SailorKentAfter:
	.string "אם כבר מדברים על חולים, שמעתי\n"
	.string "שיש בית מרקחת טוב בסיאנווד.$"

OlivineLighthouse_Text_LassConnieSeen:
	.string "ג'סמין היא מנהיגת המכון\n"
	.string "של העיר הזאת.\p"
	.string "אני מתכוונת להחזיר אותה איתי.\p"
	.string "שאף אחד לא יעז לעמוד בדרכי!$"

OlivineLighthouse_Text_LassConnieBeaten:
	.string "איי! הפוקימונים שלי!$"

OlivineLighthouse_Text_LassConnieAfter:
	.string "נכון. כל אחד היה דואג אם\n"
	.string "הפוקימון שלו היה נפגע.\p"
	.string "אתפלל לשלום הפוקימון שכאן,\n"
	.string "כדי שג'סמין תוכל לחזור למכון.$"

@5th floor==============================================================================================================================

OlivineLighthouse_EventScript_SailorErnest::
    trainerbattle_single TRAINER_ERNEST_HNS, OlivineLighthouse_Text_SailorErnestSeen, OlivineLighthouse_Text_SailorErnestBeaten
    msgbox OlivineLighthouse_Text_SailorErnestAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_BirdKeeperDenis::
    trainerbattle_single TRAINER_DENIS_HNS, OlivineLighthouse_Text_BirdKeeperDenisSeen, OlivineLighthouse_Text_BirdKeeperDenisBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperDenisAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorErnestSeen:
	.string "רציתי להילחם בג'סמין, אבל\n"
	.string "היא לא במצב לזה עכשיו.\p"
	.string "אז מה איתך?$"

OlivineLighthouse_Text_SailorErnestBeaten:
	.string "וואו, וואו. אתה פשוט מוחץ!$"

OlivineLighthouse_Text_SailorErnestAfter:
	.string "להיות מנהיג זה לא רק\n"
	.string "להיות חזק.\p"
	.string "מנהיג צריך גם\n"
	.string "לגלות חמלה.$"

OlivineLighthouse_Text_BirdKeeperDenisSeen:
	.string "אנחנו די גבוה פה.\n"
	.string "פוקימוני הציפורים שלי בכושר שיא.$"

OlivineLighthouse_Text_BirdKeeperDenisBeaten:
	.string "אופס… הם התרסקו…$"

OlivineLighthouse_Text_BirdKeeperDenisAfter:
	.string "הפוקימונים שלי למדו בסיאנווד\n"
	.string "להשתמש בתעופה.\p"
	.string "טוב, אחרי הפסד כזה, אשתמש\n"
	.string "בתעופה ואעוף מעבר לים…$"

@6th floor==============================================================================================================================

OlivineLighthouse_EventScript_Jasmine::
	lock
	faceplayer
	goto_if_eq VAR_OLIVINE_CITY_STATE, 3, OlivineLighthouse_EventScript_JasmineGoGetPotion
	goto_if_eq VAR_OLIVINE_CITY_STATE, 4, OlivineLighthouse_EventScript_JasmineDeliverPotion
	msgbox OlivineLighthouse_Text_JasmineCianwoodPharmacy, MSGBOX_DEFAULT
	msgbox OlivineLighthouse_Text_JasmineGetMedicine, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLIVINE_CITY_STATE, 3
	release
	end
OlivineLighthouse_EventScript_JasmineGoGetPotion::
	msgbox OlivineLighthouse_Text_JasmineGetMedicine2, MSGBOX_DEFAULT
	release
	end


OlivineLighthouse_EventScript_Ampharos::
	lock
	faceplayer
	goto_if_lt VAR_OLIVINE_CITY_STATE, 5, OlivineLighthouse_EventScript_AmpharosSick
	fadescreen FADE_TO_WHITE
	playse SE_M_THUNDERBOLT2
	waitse
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	setflag FLAG_AMPHAROS_HEALED
	release
	end

OlivineLighthouse_EventScript_AmpharosSick::
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPalPaloo, MSGBOX_DEFAULT
	waitmoncry
	msgbox OlivineLighthouse_Text_AmphyBreathingLabored, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_JasmineCianwoodPharmacy:
	.string "ג'סמין: …הפוקימון הזה תמיד\n"
	.string "האיר את הים בלילה.\p"
	.string "…אבל פתאום הוא חלה… הוא\n"
	.string "מתנשם בכבדות…\p"
	.string "…שמעתי שיש בית מרקחת\n"
	.string "נפלא בסיאנווד…\p"
	.string "אבל הוא מעבר לים…\n"
	.string "ואני לא יכולה להשאיר את אמפי לבד…$"

OlivineLighthouse_Text_JasmineGetMedicine:
	.string "…אפשר לבקש ממך להביא\n"
	.string "לי תרופה? בבקשה?$"

OlivineLighthouse_Text_JasmineGetMedicine2:
	.string "יש בית מרקחת נפלא\n"
	.string "בסיאנווד…\p"
	.string "אבל הוא מעבר לים…\n"
	.string "ואני לא יכולה להשאיר את אמפי לבד…\p"
	.string "…אפשר לבקש ממך להביא\n"
	.string "לי תרופה? בבקשה?$"

OlivineLighthouse_Text_JasmineCureAmphy:
	.string "ג'סמין: …התרופה הזאת\n"
	.string "תרפא את אמפי?$"


OlivineLighthouse_EventScript_JasmineDeliverPotion::
	msgbox OlivineLighthouse_Text_JasmineCureAmphy, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineLighthouse_EventScript_JasmineRefuse
	playse SE_USE_ITEM
	removeitem ITEM_SECRET_POTION
	msgbox OlivineLighthouse_Text_PlayerHandedSecretpotion, MSGBOX_DEFAULT
	waitse
	msgbox OlivineLighthouse_Text_JasmineDontBeOffended, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_LIGHTHOUSE_JASMINE, DIR_NORTH
	delay 20
	turnobject LOCALID_LIGHTHOUSE_AMPHAROS, DIR_SOUTH
	playfanfare MUS_HEAL
	waitfanfare
	msgbox OlivineLighthouse_Text_JasmineAmphyHowFeeling, MSGBOX_DEFAULT
	fadescreen FADE_TO_WHITE
	playse SE_M_THUNDERBOLT2
	waitse
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_LIGHTHOUSE_AMPHAROS, OlivineLighthouse_Movement_Amphy
	waitmovement 0
	applymovement LOCALID_LIGHTHOUSE_JASMINE, OlivineLighthouse_Movement_Jasmine
	msgbox OlivineLighthouse_Text_JasmineThankYou, MSGBOX_DEFAULT
	closemessage

	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	removeobject LOCALID_LIGHTHOUSE_JASMINE
	waitse
	delay 50
	fadescreen FADE_FROM_BLACK
	setvar VAR_SAFARI_ZONE_GATE_STATE, 1
	setvar VAR_OLIVINE_CITY_STATE, 5
	setflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
	release
	end

OlivineLighthouse_Movement_Jasmine:
	face_player
	step_end

OlivineLighthouse_Movement_Amphy:
	walk_up
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	jump_in_place_up
	face_down
	step_end


OlivineLighthouse_EventScript_JasmineRefuse::
	msgbox OlivineLighthouse_Text_JasmineISee, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_PlayerHandedSecretpotion:
	.string "{PLAYER} מסר את השיקוי הסודי\n"
	.string "לג'סמין.$"

OlivineLighthouse_Text_JasmineDontBeOffended:
	.string "ג'סמין: …אממ, בבקשה\n"
	.string "אל תיעלב…\p"
	.string "…אמפי לא מקבל שום דבר\n"
	.string "מאף אחד חוץ ממני…$"

OlivineLighthouse_Text_JasmineAmphyHowFeeling:
	.string "ג'סמין: …\p"
	.string "אמפי, איך אתה מרגיש?$"

OlivineLighthouse_Text_JasmineThankYou:
	.string "ג'סמין: …הו, איזו הקלה…\p"
	.string "זה פשוט נפלא…\p"
	.string "תודה לך, תודה רבה רבה.\p"
	.string "…אני אחזור למכון…\p"
	.string "ואני גם מזהירה אותך: פוקימונים\n"
	.string "מסוג פלדה הם חזקים.$"

OlivineLighthouse_Text_JasmineISee:
	.string "ג'סמין: …אני מבינה…\n"
	.string "…אמפי, תחזיק מעמד!$"

OlivineLighthouse_Text_AmphyPalPaloo:
	.string "אמפי: …\n"
	.string "…פא… פאלו…$"

OlivineLighthouse_Text_AmphyBreathingLabored:
	.string "הנשימה שלו כבדה\n"
	.string "מאוד…$"

OlivineLighthouse_Text_AmphyPaluPalulu:
	.string "אמפי: פאלו! פאלולו!$"


