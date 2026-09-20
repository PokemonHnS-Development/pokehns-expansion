extern const u8 EventScript_FollowerIsShivering[];
extern const u8 EventScript_FollowerNostalgia[];
extern const u8 EventScript_FollowerHopping[];
extern const u8 EventScript_FollowerJumpOnPlayer[];
extern const u8 EventScript_FollowerCuddling[];
extern const u8 EventScript_FollowerShiverCuddling[];
extern const u8 EventScript_FollowerGetCloser[];
extern const u8 EventScript_FollowerPokingPlayer[];
extern const u8 EventScript_FollowerLookAround[];
extern const u8 EventScript_FollowerLookAway[];
extern const u8 EventScript_FollowerLookAwayBark[];
extern const u8 EventScript_FollowerLookAwayPoke[];
extern const u8 EventScript_FollowerPokeGround[];
extern const u8 EventScript_FollowerStartled[];
extern const u8 EventScript_FollowerFastHopping[];
extern const u8 EventScript_FollowerDizzy[];
extern const u8 EventScript_FollowerLookAroundScared[];
extern const u8 EventScript_FollowerDance[];
extern const u8 EventScript_FollowerLookUp[];

// 'Generic', unconditional happy messages
static const u8 sHappyMsg00[] = _("{STR_VAR_1} empezó a picarte en el\nestómago.");
static const u8 sHappyMsg01[] = _("{STR_VAR_1} is happy but shy.");
static const u8 sHappyMsg02[] = _("{STR_VAR_1} is coming along happily.");
static const u8 sHappyMsg03[] = _("{STR_VAR_1} is composed.");
static const u8 sHappyMsg04[] = _("{STR_VAR_1} parece muy feliz\nde caminar contigo.");
static const u8 sHappyMsg05[] = _("{STR_VAR_1} rebosa de salud.");
static const u8 sHappyMsg06[] = _("{STR_VAR_1} looks very happy.");
static const u8 sHappyMsg07[] = _("{STR_VAR_1} put in extra effort.");
static const u8 sHappyMsg08[] = _("{STR_VAR_1} está oliendo los\naromas del aire.");
static const u8 sHappyMsg09[] = _("{STR_VAR_1} is jumping for joy!");
static const u8 sHappyMsg10[] = _("{STR_VAR_1} is still feeling great!");
static const u8 sHappyMsg11[] = _("Tu POKéMON sintió olor\na humo.");
static const u8 sHappyMsg12[] = _("{STR_VAR_1} te está picando la barriga.");
static const u8 sHappyMsg13[] = _("Tu POKéMON estiró su cuerpo\ny se está relajando.");
static const u8 sHappyMsg14[] = _("{STR_VAR_1} looks like it wants to\nlead!");
static const u8 sHappyMsg15[] = _("{STR_VAR_1} hace lo posible\npor seguirte el paso.");
static const u8 sHappyMsg16[] = _("{STR_VAR_1} se acurruca\nmuy feliz junto a ti.");
static const u8 sHappyMsg17[] = _("¡{STR_VAR_1} está lleno de vida!");
static const u8 sHappyMsg18[] = _("{STR_VAR_1} seems to be very happy!");
static const u8 sHappyMsg19[] = _("¡{STR_VAR_1} está tan feliz que\nno puede quedarse quieto!");
static const u8 sHappyMsg20[] = _("{STR_VAR_1} nodded slowly.");
static const u8 sHappyMsg21[] = _("{STR_VAR_1} is very eager!");
static const u8 sHappyMsg22[] = _("{STR_VAR_1} pasea por ahí\nescuchando los distintos sonidos.");
static const u8 sHappyMsg23[] = _("{STR_VAR_1} looks very interested.");
static const u8 sHappyMsg24[] = _("{STR_VAR_1} is somehow forcing\nitself to keep going.");
static const u8 sHappyMsg25[] = _("{STR_VAR_1} gave you a sunny look!");
static const u8 sHappyMsg26[] = _("{STR_VAR_1} gives you a happy look\nand a smile.");
static const u8 sHappyMsg27[] = _("Tu POKéMON está oliendo el aroma\n de las flores.");
static const u8 sHappyMsg28[] = _("{STR_VAR_1} seems very happy to see\nyou!");
static const u8 sHappyMsg29[] = _("{STR_VAR_1} se giró hacia aquí\ny sonrió.");
static const u8 sHappyMsg30[] = _("{STR_VAR_1} happily cuddled up to\nyou!");
// Conditional messages begin here, index 31
static const u8 sHappyMsg31[] = _("Tu POKéMON parece feliz por el\n buen clima.");
static const u8 sHappyMsg32[] = _("{STR_VAR_1} es muy sereno y\nseguro de sí mismo!");

const struct FollowerMsgInfo gFollowerHappyMessages[] = {
    {sHappyMsg00, EventScript_FollowerPokingPlayer},
    {sHappyMsg01}, {sHappyMsg02}, {sHappyMsg03}, {sHappyMsg04}, {sHappyMsg05}, {sHappyMsg06}, {sHappyMsg07},
    {sHappyMsg08, EventScript_FollowerLookAround},
    {sHappyMsg09, EventScript_FollowerHopping},
    {sHappyMsg10}, {sHappyMsg11},
    {sHappyMsg12, EventScript_FollowerPokingPlayer},
    {sHappyMsg13, EventScript_FollowerLookAround},
    {sHappyMsg14}, {sHappyMsg15},
    {sHappyMsg16, EventScript_FollowerCuddling},
    {sHappyMsg17}, {sHappyMsg18},
    {sHappyMsg19, EventScript_FollowerFastHopping},
    {sHappyMsg20}, {sHappyMsg21}, {sHappyMsg22}, {sHappyMsg23}, {sHappyMsg24}, {sHappyMsg25}, {sHappyMsg26}, {sHappyMsg27}, {sHappyMsg28}, {sHappyMsg29},
    {sHappyMsg30, EventScript_FollowerCuddling},
    {sHappyMsg31}, {sHappyMsg32},
};

// Unconditional neutral messages
static const u8 sNeutralMsg00[] = _("{STR_VAR_1} is steadily poking at\nthe ground.");
static const u8 sNeutralMsg01[] = _("{STR_VAR_1} is standing guard.");
static const u8 sNeutralMsg02[] = _("{STR_VAR_1} is staring patiently at\nnothing at all.");
static const u8 sNeutralMsg03[] = _("{STR_VAR_1} is wandering around.");
static const u8 sNeutralMsg04[] = _("Your POKéMON yawned loudly!");
static const u8 sNeutralMsg05[] = _("Tu POKéMON mira alrededor\n con inquietud.");
static const u8 sNeutralMsg06[] = _("{STR_VAR_1} mira hacia aquí y\nsonríe.");
static const u8 sNeutralMsg07[] = _("{STR_VAR_1} is gazing around\nrestlessly.");
static const u8 sNeutralMsg08[] = _("{STR_VAR_1} let out a battle cry.");
static const u8 sNeutralMsg09[] = _("{STR_VAR_1} danced a wonderful\ndance!");
static const u8 sNeutralMsg10[] = _("{STR_VAR_1} is very eager.");
static const u8 sNeutralMsg11[] = _("{STR_VAR_1} mira fijamente\na la distancia.");
static const u8 sNeutralMsg12[] = _("{STR_VAR_1} está al acecho!");
static const u8 sNeutralMsg13[] = _("{STR_VAR_1} miró a lo lejos\ny ladró!");

const struct FollowerMsgInfo gFollowerNeutralMessages[] = {
    {sNeutralMsg00, EventScript_FollowerPokeGround},
    {sNeutralMsg01},
    {sNeutralMsg02, EventScript_FollowerLookAway},
    {sNeutralMsg03, EventScript_FollowerLookAround},
    {sNeutralMsg04},
    {sNeutralMsg05, EventScript_FollowerLookAround},
    {sNeutralMsg06}, {sNeutralMsg07}, {sNeutralMsg08},
    {sNeutralMsg09, EventScript_FollowerDance},
    {sNeutralMsg10},
    {sNeutralMsg11, EventScript_FollowerLookAway},
    {sNeutralMsg12},
    {sNeutralMsg13, EventScript_FollowerLookAwayBark},
};

// Unconditional sad messages
static const u8 sSadMsg00[] = _("{STR_VAR_1} is dizzy.");
static const u8 sSadMsg01[] = _("¡{STR_VAR_1} te está pisando\nlos pies!");
static const u8 sSadMsg02[] = _("{STR_VAR_1} seems a little tired.");
// Conditional messages begin, index 3
static const u8 sSadMsg03[] = _("{STR_VAR_1} no está contento.");
static const u8 sSadMsg04[] = _("{STR_VAR_1} is going to fall down!\n");
static const u8 sSadMsg05[] = _("{STR_VAR_1} seems to be about to\nfall over!");
static const u8 sSadMsg06[] = _("{STR_VAR_1} se esfuerza mucho\npor seguirte…");
static const u8 sSadMsg07[] = _("{STR_VAR_1} is nervous.");

const struct FollowerMsgInfo gFollowerSadMessages[] = {
    {sSadMsg00, EventScript_FollowerDizzy},
    {sSadMsg01}, {sSadMsg02},
    {sSadMsg03}, {sSadMsg04}, {sSadMsg05}, {sSadMsg06}, {sSadMsg07},
};

// Unconditional upset messages
static const u8 sUpsetMsg00[] = _("{STR_VAR_1} seems unhappy somehow…");
static const u8 sUpsetMsg01[] = _("{STR_VAR_1} is making an unhappy\nface.");
static const u8 sUpsetMsg02[] = _("…Your POKéMON seems a little\ncold.");
// Conditional messages, index 3
static const u8 sUpsetMsg03[] = _("{STR_VAR_1} se refugia de la lluvia\nen la hierba.");

const struct FollowerMsgInfo gFollowerUpsetMessages[] = {
    {sUpsetMsg00}, {sUpsetMsg01},
    {sUpsetMsg02, EventScript_FollowerIsShivering},
    {sUpsetMsg03},
};

// Unconditional angry messages
static const u8 sAngryMsg00[] = _("{STR_VAR_1} let out a roar!");
static const u8 sAngryMsg01[] = _("{STR_VAR_1} is making a face like\nit's angry!");
static const u8 sAngryMsg02[] = _("{STR_VAR_1} seems to be angry for\nsome reason.");
static const u8 sAngryMsg03[] = _("Tu POKéMON se dio la vuelta\n con cara desafiante.");
static const u8 sAngryMsg04[] = _("{STR_VAR_1} cried out.");

const struct FollowerMsgInfo gFollowerAngryMessages[] = {
    {sAngryMsg00}, {sAngryMsg01}, {sAngryMsg02},
    {sAngryMsg03, EventScript_FollowerLookAway},
    {sAngryMsg04},
};

// Unconditional pensive messages
static const u8 sPensiveMsg00[] = _("{STR_VAR_1} is looking down\nsteadily.");
static const u8 sPensiveMsg01[] = _("{STR_VAR_1} está observando la zona.");
static const u8 sPensiveMsg02[] = _("{STR_VAR_1} is peering down.");
static const u8 sPensiveMsg03[] = _("{STR_VAR_1} is somehow fighting off\nsleep…");
static const u8 sPensiveMsg04[] = _("{STR_VAR_1} seems to be wandering\naround.");
static const u8 sPensiveMsg05[] = _("{STR_VAR_1} is looking around\nabsentmindedly.");
static const u8 sPensiveMsg06[] = _("{STR_VAR_1} yawned very loudly!");
static const u8 sPensiveMsg07[] = _("{STR_VAR_1} is relaxing comfortably.");
static const u8 sPensiveMsg08[] = _("{STR_VAR_1} te mira fijamente\na la cara.");
static const u8 sPensiveMsg09[] = _("{STR_VAR_1} is staring intently at\nyour face.");
static const u8 sPensiveMsg10[] = _("{STR_VAR_1} está centrando su\natención en ti.");
static const u8 sPensiveMsg11[] = _("{STR_VAR_1} mira fijamente\nlas profundidades.");
static const u8 sPensiveMsg12[] = _("{STR_VAR_1} está olfateando\nel suelo.");
static const u8 sPensiveMsg13[] = _("Tu POKéMON mira fijamente\nal vacío.");
static const u8 sPensiveMsg14[] = _("{STR_VAR_1} focused with a sharp\ngaze!");
static const u8 sPensiveMsg15[] = _("{STR_VAR_1} is concentrating.");
static const u8 sPensiveMsg16[] = _("{STR_VAR_1} se volteó hacia aquí y\nasintió.");
static const u8 sPensiveMsg17[] = _("{STR_VAR_1} seems a bit nervous…");
static const u8 sPensiveMsg18[] = _("{STR_VAR_1} está mirando tus\nhuellas.");
static const u8 sPensiveMsg19[] = _("{STR_VAR_1} te está mirando fijamente\na los ojos.");

const struct FollowerMsgInfo gFollowerPensiveMessages[] = {
    {sPensiveMsg00},
    {sPensiveMsg01, EventScript_FollowerLookAround},
    {sPensiveMsg02}, {sPensiveMsg03}, {sPensiveMsg04},
    {sPensiveMsg05, EventScript_FollowerLookAround},
    {sPensiveMsg06}, {sPensiveMsg07}, {sPensiveMsg08}, {sPensiveMsg09}, {sPensiveMsg10},
    {sPensiveMsg11, EventScript_FollowerLookAway},
    {sPensiveMsg12, EventScript_FollowerPokeGround},
    {sPensiveMsg13, EventScript_FollowerLookAway},
    {sPensiveMsg14}, {sPensiveMsg15}, {sPensiveMsg16}, {sPensiveMsg17}, {sPensiveMsg18}, {sPensiveMsg19},
};

// All 'love' messages are unconditional
static const u8 sLoveMsg00[] = _("{STR_VAR_1} suddenly started walking\ncloser!");
static const u8 sLoveMsg01[] = _("{STR_VAR_1} cheeks are becoming\nrosy!");
static const u8 sLoveMsg02[] = _("Woah! {STR_VAR_1} suddenly hugged\nyou!");
static const u8 sLoveMsg03[] = _("Woah! {STR_VAR_1} is suddenly\nplayful!");
static const u8 sLoveMsg04[] = _("{STR_VAR_1} se frota contra tus\npiernas!");
static const u8 sLoveMsg05[] = _("{STR_VAR_1} blushes.");
static const u8 sLoveMsg06[] = _("Ah! {STR_VAR_1} cuddles you!");
static const u8 sLoveMsg07[] = _("{STR_VAR_1} te mira con\nadoración!");
static const u8 sLoveMsg08[] = _("{STR_VAR_1} got closer to you.");
static const u8 sLoveMsg09[] = _("{STR_VAR_1} se mantiene cerca de\ntus pies.");

const struct FollowerMsgInfo gFollowerLoveMessages[] = {
    {sLoveMsg00, EventScript_FollowerGetCloser},
    {sLoveMsg01},
    {sLoveMsg02, EventScript_FollowerCuddling},
    {sLoveMsg03},
    {sLoveMsg04, EventScript_FollowerCuddling},
    {sLoveMsg05},
    {sLoveMsg06, EventScript_FollowerCuddling},
    {sLoveMsg07},
    {sLoveMsg08, EventScript_FollowerGetCloser},
    {sLoveMsg09},
};

// Unconditional surprised messages
static const u8 sSurpriseMsg00[] = _("{STR_VAR_1} está en peligro de\ncaerse!");
static const u8 sSurpriseMsg01[] = _("¡{STR_VAR_1} chocó contra ti!");
static const u8 sSurpriseMsg02[] = _("{STR_VAR_1} doesn't seem to be used\nto its own name yet.");
static const u8 sSurpriseMsg03[] = _("{STR_VAR_1} is peering down.");
static const u8 sSurpriseMsg04[] = _("¡Tu POKéMON tropezó y casi\nse cae!");
static const u8 sSurpriseMsg05[] = _("{STR_VAR_1} siente algo y\n¡está aullando!");
static const u8 sSurpriseMsg06[] = _("{STR_VAR_1} seems refreshed!");
static const u8 sSurpriseMsg07[] = _("{STR_VAR_1} suddenly turned around\nand started barking!");
static const u8 sSurpriseMsg08[] = _("{STR_VAR_1} suddenly turned around!");
static const u8 sSurpriseMsg09[] = _("¡Tu POKéMON se sorprendió cuando\n le hablaste de repente!");
static const u8 sSurpriseMsg10[] = _("Sniff sniff, something smells really\ngood!");
static const u8 sSurpriseMsg11[] = _("{STR_VAR_1} feels refreshed.");
static const u8 sSurpriseMsg12[] = _("{STR_VAR_1} se tambalea y parece\nque va a caerse.");
static const u8 sSurpriseMsg13[] = _("{STR_VAR_1} corre peligro de\ncaerse.");
static const u8 sSurpriseMsg14[] = _("{STR_VAR_1} is walking along\ncautiously.");
static const u8 sSurpriseMsg15[] = _("{STR_VAR_1} se pone tenso con\nenergía nerviosa.");
static const u8 sSurpriseMsg16[] = _("{STR_VAR_1} sensed something strange\nand was surprised!");
static const u8 sSurpriseMsg17[] = _("¡{STR_VAR_1} tiene miedo y se\nacurruca contra ti!");
static const u8 sSurpriseMsg18[] = _("{STR_VAR_1} is feeling an unusual\npresence…");
static const u8 sSurpriseMsg19[] = _("{STR_VAR_1} se pone tenso con\nenergía nerviosa.");
// Conditional messages, index 20
static const u8 sSurpriseMsg20[] = _("{STR_VAR_1} parece muy\nsorprendido de que llueva!");

const struct FollowerMsgInfo gFollowerSurpriseMessages[] = {
    {sSurpriseMsg00},
    {sSurpriseMsg01, EventScript_FollowerPokingPlayer},
    {sSurpriseMsg02}, {sSurpriseMsg03}, {sSurpriseMsg04}, {sSurpriseMsg05}, {sSurpriseMsg06},
    {sSurpriseMsg07, EventScript_FollowerLookAwayBark},
    {sSurpriseMsg08, EventScript_FollowerLookAway},
    {sSurpriseMsg09},
    {sSurpriseMsg10, EventScript_FollowerLookAround},
    {sSurpriseMsg11}, {sSurpriseMsg12}, {sSurpriseMsg13}, {sSurpriseMsg14}, {sSurpriseMsg15}, {sSurpriseMsg16},
    {sSurpriseMsg17, EventScript_FollowerCuddling},
    {sSurpriseMsg18},
    {sSurpriseMsg19, EventScript_FollowerLookAround},
    {sSurpriseMsg20},
};

// Unconditional curious messages
static const u8 sCuriousMsg00[] = _("Tu POKéMON busca algo\ninquieto a su alrededor.");
static const u8 sCuriousMsg01[] = _("Tu POKéMON no miraba por donde\niba y ¡se estrelló contra ti!");
static const u8 sCuriousMsg02[] = _("¡Snif, snif! ¿Hay algo\ncerca?");
static const u8 sCuriousMsg03[] = _("{STR_VAR_1} is rolling a pebble\naround playfully.");
static const u8 sCuriousMsg04[] = _("{STR_VAR_1} anda por ahí\ny busca algo.");
static const u8 sCuriousMsg05[] = _("{STR_VAR_1} te está oliendo.");
static const u8 sCuriousMsg06[] = _("{STR_VAR_1} seems to be a little\nhesitant…");

const struct FollowerMsgInfo gFollowerCuriousMessages[] = {
    {sCuriousMsg00, EventScript_FollowerLookAround},
    {sCuriousMsg01, EventScript_FollowerPokingPlayer},
    {sCuriousMsg02}, {sCuriousMsg03},
    {sCuriousMsg04, EventScript_FollowerLookAround},
    {sCuriousMsg05}, {sCuriousMsg06},
};

// Unconditional music messages
static const u8 sMusicMsg00[] = _("{STR_VAR_1} presume de su\nagilidad!");
static const u8 sMusicMsg01[] = _("{STR_VAR_1} is moving around\nhappily!");
static const u8 sMusicMsg02[] = _("Woah! {STR_VAR_1} suddenly started\ndancing in happiness!");
static const u8 sMusicMsg03[] = _("{STR_VAR_1} te sigue el\npaso sin parar!");
static const u8 sMusicMsg04[] = _("{STR_VAR_1} seems to want to play\nwith you.");
static const u8 sMusicMsg05[] = _("{STR_VAR_1} salta feliz.");
static const u8 sMusicMsg06[] = _("{STR_VAR_1} canta y tararea.");
static const u8 sMusicMsg07[] = _("{STR_VAR_1} te muerde los pies!");
static const u8 sMusicMsg08[] = _("{STR_VAR_1} se da la vuelta\ny te mira.");
static const u8 sMusicMsg09[] = _("{STR_VAR_1} se esfuerza por lucir\nsu enorme poder!");
static const u8 sMusicMsg10[] = _("Whoa! {STR_VAR_1} suddenly danced in\nhappiness!");
static const u8 sMusicMsg11[] = _("{STR_VAR_1} is cheerful!");
static const u8 sMusicMsg12[] = _("{STR_VAR_1} is jumping around in a\ncarefree way!");
static const u8 sMusicMsg13[] = _("Your POKéMON seems to be smelling a\nnostalgically familiar scent…");
// Conditional music messages, index 14
static const u8 sMusicMsg14[] = _("{STR_VAR_1} está feliz con la\nlluvia.");

const struct FollowerMsgInfo gFollowerMusicMessages[] = {
    {sMusicMsg00, EventScript_FollowerLookAround},
    {sMusicMsg01},
    {sMusicMsg02, EventScript_FollowerDance},
    {sMusicMsg03},
    {sMusicMsg04, EventScript_FollowerHopping},
    {sMusicMsg05, EventScript_FollowerHopping},
    {sMusicMsg06}, {sMusicMsg07}, {sMusicMsg08}, {sMusicMsg09},
    {sMusicMsg10, EventScript_FollowerDance},
    {sMusicMsg11},
    {sMusicMsg12, EventScript_FollowerHopping},
    {sMusicMsg13, EventScript_FollowerNostalgia},
    {sMusicMsg14}
};


static const u8 sPoisonedMsg00[] = _("{STR_VAR_1} tiembla por los\nefectos del veneno.");

const struct FollowerMsgInfo gFollowerPoisonedMessages[] = {
    {sPoisonedMsg00, EventScript_FollowerIsShivering},
};
