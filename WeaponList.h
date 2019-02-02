#pragma once

#include "SDK.h"

/*===================================================================================
//Weapon ID Define List
//
//http://www.tf2items.com/allitems.php?d=1
//===================================================================================*/

enum scoutweapons
{
	//Primary
	WPN_Scattergun = 13,
	WPN_NewScattergun = 200,
	WPN_FAN = 45,
	WPN_Shortstop = 220,
	WPN_SodaPopper = 448,
	WPN_BabyFaceBlaster = 772,
	WPN_BotScattergunS = 799,
	WPN_BotScattergunG = 808,
	WPN_BotScattergunR = 888,
	WPN_BotScattergunB = 897,
	WPN_BotScattergunC = 906,
	WPN_BotScattergunD = 915,
	WPN_BotScattergunES = 964,
	WPN_BotScattergunEG = 973,
	WPN_FestiveFaN = 1078,
	WPN_BackScatter = 1103,
	//Secondary
	WPN_ScoutPistol = 23,
	WPN_NewPistol = 209,
	WPN_Bonk = 46,
	WPN_CritCola = 163,
	WPN_Lugermorph = 160,
	WPN_Milk = 222,
	WPN_Lugermorph2 = 294,
	WPN_Winger = 449,
	WPN_PocketPistol = 773,
	WPN_MutatedMilk = 1121,
	WPN_CAPPER = 30666,
	//Melee
	WPN_Bat = 0,
	WPN_NewBat = 190,
	WPN_Sandman = 44,
	WPN_Fish = 221,
	WPN_Cane = 317,
	WPN_BostonBasher = 325,
	WPN_SunStick = 349,
	WPN_FanOWar = 355,
	WPN_RuneBlade = 452,
	WPN_Saxxy = 423,
	WPN_Atomizer = 450,
	WPN_ConscientiousObjector = 474,
	WPN_UnarmedCombat = 572,
	WPN_WrapAssassin = 648,
	WPN_FestiveBat = 660,
	WPN_FestiveScattergun = 669,
	WPN_FlyingGuillotine1 = 812,
	WPN_FlyingGuillotine2 = 833,
	WPN_FreedomStaff = 880,
	WPN_BatOuttaHell = 939,
	WPN_MemoryMaker = 954,
	WPN_FestiveFish = 999,
	WPN_TheHamShank = 1013,
	WPN_CrossingGuard = 1127,
	WPN_NecroSmasher = 1123,
	WPN_Batsaber = 30667,
};
enum soldierweapons
{
	//Primary
	WPN_RocketLauncher = 18,
	WPN_NewRocketLauncher = 205,
	WPN_DirectHit = 127,
	WPN_BlackBox = 228,
	WPN_RocketJumper = 237,
	WPN_LibertyLauncher = 414,
	WPN_CowMangler = 441,
	WPN_Original = 513,
	WPN_FestiveRocketLauncher = 658,
	WPN_BeggersBazooka = 730,
	WPN_BotRocketlauncherS = 800,
	WPN_BotRocketlauncherG = 809,
	WPN_BotRocketlauncherR = 889,
	WPN_BotRocketlauncherB = 898,
	WPN_BotRocketlauncherC = 907,
	WPN_BotRocketlauncherD = 916,
	WPN_BotRocketlauncherES = 965,
	WPN_BotRocketlauncherEG = 974,
	WPN_FestiveBlackbox = 1085,
	WPN_Airstrike = 1104,
	//Secondary
	WPN_SoldierShotgun = 10,
	WPN_NewShotgun = 199,
	WPN_BuffBanner = 129,
	WPN_BattalionBackup = 226,
	WPN_Concheror = 354,
	WPN_ReserveShooter = 415,
	WPN_RighteousBison = 442,
	WPN_FestiveBuffBanner = 1001,
	WPN_PanicAttack = 1153,
	//Melee
	WPN_Shovel = 6,
	WPN_NewShovel = 196,
	WPN_Equalizer = 128,
	WPN_PainTrain = 154,
	WPN_Katana = 357,
	WPN_MarketGardener = 416,
	WPN_DisciplinaryAction = 447,
	WPN_EscapePlan = 775,
};
enum pyroweapons
{
	//Primary
	WPN_Flamethrower = 21,
	WPN_NewFlamethrower = 208,
	WPN_Backburner = 40,
	WPN_Degreaser = 215,
	WPN_FestiveFlamethrower = 659,
	WPN_Phlogistinator = 594,
	WPN_Rainblower = 741,
	WPN_NostromoNapalmer = 30474,
	WPN_BotFlamethrowerS = 798,
	WPN_BotFlamethrowerG = 807,
	WPN_BotFlamethrowerR = 887,
	WPN_BotFlamethrowerB = 896,
	WPN_BotFlamethrowerC = 905,
	WPN_BotFlamethrowerD = 914,
	WPN_BotFlamethrowerES = 963,
	WPN_BotFlamethrowerEG = 972,
	WPN_FestiveBackburner = 1146,
	//Secondary
	WPN_PyroShotgun = 12,
	WPN_Flaregun = 39,
	WPN_Detonator = 351,
	WPN_ManMelter = 595,
	WPN_ScorchShot = 740,
	WPN_FestiveFlaregun = 1081,
	//Melee
	WPN_Fireaxe = 2,
	WPN_NewAxe = 192,
	WPN_Axtingusher = 38,
	WPN_HomeWrecker = 153,
	WPN_PowerJack = 214,
	WPN_Backscratcher = 326,
	WPN_VolcanoFragment = 348,
	WPN_Maul = 466,
	WPN_Mailbox = 457,
	WPN_ThirdDegree = 593,
	WPN_Lollychop = 739,
	WPN_NeonAnnihilator1 = 813,
	WPN_NeonAnnihilator2 = 834,
	WPN_FestiveAxtingisher = 1000,
};
enum demomanweapons
{
	//Primary
	WPN_GrenadeLauncher = 19,
	WPN_NewGrenadeLauncher = 206,
	WPN_LochNLoad = 308,
	WPN_LoooseCannon = 996,
	WPN_FestiveGrenadeLauncher = 1007,
	WPN_IronBomber = 1151,
	//Secondary
	WPN_StickyLauncher = 20,
	WPN_NewStickyLauncher = 207,
	WPN_ScottishResistance = 130,
	WPN_StickyJumper = 265,
	WPN_FestiveStickyLauncher = 661,
	WPN_BotStickyS = 797,
	WPN_BotStickyG = 806,
	WPN_BotStickyR = 886,
	WPN_BotStickyB = 895,
	WPN_BotStickyC = 904,
	WPN_BotStickyD = 913,
	WPN_BotStickyES = 962,
	WPN_BotStickyEG = 971,
	WPN_QuickieBombLauncher = 1150,
	//Melee
	WPN_Bottle = 1,
	WPN_NewBottle = 191,
	WPN_Sword = 132,
	WPN_ScottsSkullctter = 172,
	WPN_Fryingpan = 264,
	WPN_Headless = 266,
	WPN_Ullapool = 307,
	WPN_Claidheamhmor = 327,
	WPN_PersainPersuader = 404,
	WPN_Golfclub = 482,
	WPN_ScottishHandshake = 609,
	WPN_GoldenFryingPan = 1071,
	WPN_FestiveEyelander = 1082,
};
enum heavyweapons
{
	//Primary
	WPN_Minigun = 15,
	WPN_NewMinigun = 202,
	WPN_Natascha = 41,
	WPN_IronCurtain = 298,
	WPN_BrassBeast = 312,
	WPN_Tomislav = 424,
	WPN_FestiveMinigun = 654,
	WPN_HuoLongHeatmaker1 = 811,
	WPN_HuoLongHeatmaker2 = 832,
	WPN_BotMinigunS = 793,
	WPN_BotMinigunG = 802,
	WPN_BotMinigunR = 882,
	WPN_BotMinigunB = 891,
	WPN_BotMinigunC = 900,
	WPN_BotMinigunD = 909,
	WPN_Deflector = 850,
	WPN_BotMinigunES = 958,
	WPN_BotMinigunEG = 967,
	//Secondary
	WPN_HeavyShotgun = 11,
	WPN_Sandvich = 42,
	WPN_CandyBar = 159,
	WPN_Steak = 311,
	WPN_Fishcake = 433,
	WPN_FamilyBuisness = 425, //GIVE 'EM THE BUISSNESS, TONY!
	WPN_RobotSandvich = 863,
	WPN_FestiveSandvich = 1002,
	//Melee
	WPN_Fists = 5,
	WPN_NewFists = 195,
	WPN_KGB = 43,
	WPN_GRU = 239,
	WPN_WarriorSpirit = 310,
	WPN_FistsOfSteel = 331,
	WPN_EvictionNotice = 426,
	WPN_ApocoFists = 587,
	WPN_HolidayPunch = 656,
	WPN_FestiveGRU = 1084,
	WPN_BreadBite = 1100,
};
enum engineerweapons
{
	//Primary
	WPN_EngineerShotgun = 9,
	WPN_FrontierJustice = 141,
	WPN_Widowmaker = 527,
	WPN_Pomson = 588,
	WPN_RescueRanger = 997,
	WPN_FestiveFrontierJustice = 1004,
	//Secondary
	WPN_EngineerPistol = 22,
	WPN_Wrangler = 140,
	WPN_ShortCircut = 528,
	WPN_FestiveWrangler = 1086,
	WPN_GeigerCounter = 30668,
	//Melee
	WPN_Wrench = 7,
	WPN_NewWrench = 197,
	WPN_Goldenwrench = 169,
	WPN_SouthernHospitality = 155,
	WPN_Gunslinger = 142,
	WPN_Jag = 329,
	WPN_FestiveWrench = 662,
	WPN_EurekaEffect = 589,
	WPN_BotWrenchS = 795,
	WPN_BotWrenchG = 804,
	WPN_BotWrenchR = 884,
	WPN_BotWrenchB = 893,
	WPN_BotWrenchC = 902,
	WPN_BotWrenchD = 911,
	WPN_BotWrenchES = 960,
	WPN_BotWrenchEG = 969,
	//Misc
	WPN_Builder = 25,
	WPN_Builder2 = 737,
	WPN_Destructor = 26,
	WPN_Toolbox = 28,
};
enum medicweapons
{
	//Primary
	WPN_SyringeGun = 17,
	WPN_NewSyringeGun = 204,
	WPN_Blutsauger = 36,
	WPN_Crossbow = 305,
	WPN_Overdose = 412,
	WPN_FestiveCrossbow = 1079,
	//Secondary
	WPN_Medigun = 29,
	WPN_NewMedigun = 211,
	WPN_Kritzkrieg = 35,
	WPN_QuickFix = 411,
	WPN_FestiveMedigun = 663,
	WPN_MedigunS = 796,
	WPN_MedigunG = 805,
	WPN_MedigunR = 885,
	WPN_MedigunB = 894,
	WPN_MedigunC = 903,
	WPN_MedigunD = 912,
	WPN_Vaccinator = 998,
	WPN_MedigunES = 961,
	WPN_MedigunEG = 970,
	//Melee
	WPN_Bonesaw = 8,
	WPN_NewBonesaw = 198,
	WPN_Ubersaw = 37,
	WPN_Vitasaw = 173,
	WPN_Amputator = 304,
	WPN_Solemnvow = 413,
	WPN_FestiveUbersaw = 1003,
};
enum sniperweapons
{
	//Primary
	WPN_SniperRifle = 14,
	WPN_NewSniperRifle = 201,
	WPN_Huntsman = 56,
	WPN_SydneySleeper = 230,
	WPN_Bazaarbargain = 402,
	WPN_Machina = 526,
	WPN_FestiveSniperRifle = 664,
	WPN_HitmanHeatmaker = 752,
	WPN_BotSniperRifleS = 792,
	WPN_BotSniperRifleG = 801,
	WPN_BotSniperRifleR = 881,
	WPN_BotSniperRifleB = 890,
	WPN_BotSniperRifleC = 899,
	WPN_BotSniperRifleD = 908,
	WPN_AWP = 851,
	WPN_BotSniperRifleES = 957,
	WPN_BotSniperRifleEG = 966,
	WPN_FestiveHuntsman = 1005,
	WPN_CompoundBow = 1092,
	WPN_ClassicSniperRifle = 1098,
	WPN_ShootingStar = 30665,
	//Secondary
	WPN_SMG = 16,
	WPN_NewSMG = 203,
	WPN_Jarate = 58,
	WPN_DarwinDangerShield = 231,
	WPN_CleanersCarbine = 751,
	WPN_FestiveJarate = 1083,
	WPN_SelfAwareBeautyMark = 1105,
	//Melee
	WPN_Kukri = 3,
	WPN_NewKukri = 193,
	WPN_TribalmansShiv = 171,
	WPN_Bushwacka = 232,
	WPN_Shahanshah = 401,
};
enum spyweapons
{
	//Primary
	WPN_Revolver = 24,
	WPN_NewRevolver = 210,
	WPN_Ambassador = 61,
	WPN_BigKill = 161,
	WPN_Letranger = 224,
	WPN_Enforcer = 460,
	WPN_Diamondback = 525,
	WPN_FestiveAmbassador = 1006,
	//Melee
	WPN_Knife = 4,
	WPN_NewKnife = 194,
	WPN_EternalReward = 225,
	WPN_DisguiseKit = 27,
	WPN_Kunai = 356,
	WPN_BigEarner = 461,
	WPN_WangaPrick = 574,
	WPN_SharpDresser = 638,
	WPN_Spycicle = 649,
	WPN_FestiveKnife = 665,
	WPN_BlackRose = 727,
	WPN_BotKnifeS = 794,
	WPN_BotKnifeG = 803,
	WPN_BotKnifeR = 883,
	WPN_BotKnifeB = 892,
	WPN_BotKnifeC = 901,
	WPN_BotKnifeD = 910,
	WPN_BotKnifeES = 959,
	WPN_BotKnifeEG = 968,
	//Watches
	WPN_InivisWatch = 30,
	WPN_DeadRinger = 59,
	WPN_CloakAndDagger = 60,
	WPN_TimePiece = 297,
	//Sapper
	WPN_Sapper = 735,
	WPN_Sapper2 = 736,
	WPN_RedTape1 = 810,
	WPN_RedTape2 = 831,
	WPN_ApSap = 933,
	WPN_FestiveSapper = 1080,
	WPN_SnackAttack = 1102,
};

enum class ent_id
{
	CTFWearableRazorback = 340,
	CTFWearableDemoShield = 337,
	CTFWearableLevelableItem = 339,
	CTFWearableCampaignItem = 336,
	CTFBaseRocket = 184,
	CTFWeaponBaseMerasmusGrenade = 324,
	CTFWeaponBaseMelee = 323,
	CTFWeaponBaseGun = 322,
	CTFWeaponBaseGrenadeProj = 321,
	CTFWeaponBase = 320,
	CTFWearableRobotArm = 341,
	CTFRobotArm = 286,
	CTFWrench = 343,
	CTFProjectile_ThrowableBreadMonster = 278,
	CTFProjectile_ThrowableBrick = 279,
	CTFProjectile_ThrowableRepel = 280,
	CTFProjectile_Throwable = 277,
	CTFThrowable = 318,
	CTFSyringeGun = 314,
	CTFKatana = 224,
	CTFSword = 313,
	CSniperDot = 117,
	CTFSniperRifleClassic = 307,
	CTFSniperRifleDecap = 308,
	CTFSniperRifle = 306,
	CTFChargedSMG = 196,
	CTFSMG = 305,
	CTFSlap = 304,
	CTFShovel = 303,
	CTFShotgunBuildingRescue = 302,
	CTFPEPBrawlerBlaster = 240,
	CTFSodaPopper = 309,
	CTFShotgun_Revenge = 300,
	CTFScatterGun = 296,
	CTFShotgun_Pyro = 299,
	CTFShotgun_HWG = 298,
	CTFShotgun_Soldier = 301,
	CTFShotgun = 297,
	CTFRocketPack = 295,
	CTFCrossbow = 200,
	CTFRocketLauncher_Mortar = 294,
	CTFRocketLauncher_AirStrike = 292,
	CTFRocketLauncher_DirectHit = 293,
	CTFRocketLauncher = 291,
	CTFRevolver = 285,
	CTFDRGPomson = 201,
	CTFRaygun = 283,
	CTFPistol_ScoutSecondary = 245,
	CTFPistol_ScoutPrimary = 244,
	CTFPistol_Scout = 243,
	CTFPistol = 242,
	CTFPipebombLauncher = 241,
	CTFWeaponPDA_Spy = 331,
	CTFWeaponPDA_Engineer_Destroy = 330,
	CTFWeaponPDA_Engineer_Build = 329,
	CTFWeaponPDAExpansion_Teleporter = 333,
	CTFWeaponPDAExpansion_Dispenser = 332,
	CTFWeaponPDA = 328,
	CTFParticleCannon = 238,
	CTFParachute_Secondary = 237,
	CTFParachute_Primary = 236,
	CTFParachute = 235,
	CTFMinigun = 233,
	CTFMedigunShield = 230,
	CWeaponMedigun = 351,
	CTFProjectile_MechanicalArmOrb = 262,
	CTFMechanicalArm = 229,
	CTFLunchBox_Drink = 228,
	CTFLunchBox = 227,
	CLaserDot = 78,
	CTFLaserPointer = 226,
	CTFKnife = 225,
	CTFGasManager = 211,
	CTFProjectile_JarGas = 260,
	CTFJarGas = 222,
	CTFProjectile_Cleaver = 253,
	CTFProjectile_JarMilk = 261,
	CTFProjectile_Jar = 259,
	CTFCleaver = 197,
	CTFJarMilk = 223,
	CTFJar = 221,
	CTFWeaponInvis = 327,
	CTFCannon = 195,
	CTFGrenadeLauncher = 215,
	CTFGrenadePipebombProjectile = 216,
	CTFGrapplingHook = 214,
	CTFFlareGun_Revenge = 209,
	CTFFlareGun = 208,
	CTFFlameRocket = 206,
	CTFFlameThrower = 207,
	CTFFists = 204,
	CTFFireAxe = 203,
	CTFWeaponFlameBall = 326,
	CTFCompoundBow = 199,
	CTFClub = 198,
	CTFBuffItem = 194,
	CTFStickBomb = 311,
	CTFBreakableSign = 193,
	CTFBottle = 191,
	CTFBreakableMelee = 192,
	CTFBonesaw = 189,
	CTFBall_Ornament = 181,
	CTFStunBall = 312,
	CTFBat_Giftwrap = 187,
	CTFBat_Wood = 188,
	CTFBat_Fish = 186,
	CTFBat = 185,
	CTFProjectile_EnergyRing = 255,
	CTFDroppedWeapon = 202,
	CTFWeaponSapper = 334,
	CTFWeaponBuilder = 325,
	C_TFWeaponBuilder = 0,
	CTFProjectile_Rocket = 263,
	CTFProjectile_Flare = 256,
	CTFProjectile_EnergyBall = 254,
	CTFProjectile_GrapplingHook = 257,
	CTFProjectile_HealingBolt = 258,
	CTFProjectile_Arrow = 251,
	CMannVsMachineStats = 80,
	CTFTankBoss = 315,
	CTFBaseBoss = 182,
	CBossAlpha = 0,
	NextBotCombatCharacter = 356,
	CTFProjectile_SpellKartBats = 267,
	CTFProjectile_SpellKartOrb = 268,
	CTFHellZap = 219,
	CTFProjectile_SpellLightningOrb = 269,
	CTFProjectile_SpellTransposeTeleport = 276,
	CTFProjectile_SpellMeteorShower = 270,
	CTFProjectile_SpellSpawnBoss = 273,
	CTFProjectile_SpellMirv = 271,
	CTFProjectile_SpellPumpkin = 272,
	CTFProjectile_SpellSpawnHorde = 274,
	CTFProjectile_SpellSpawnZombie = 275,
	CTFProjectile_SpellBats = 265,
	CTFProjectile_SpellFireball = 266,
	CTFSpellBook = 310,
	CHightower_TeleportVortex = 74,
	CTeleportVortex = 159,
	CZombie = 353,
	CMerasmusDancer = 83,
	CMerasmus = 82,
	CHeadlessHatman = 73,
	CEyeballBoss = 48,
	CTFBotHintEngineerNest = 190,
	CBotNPCMinion = 0,
	CBotNPC = 0,
	CPasstimeGun = 94,
	CTFViewModel = 319,
	CRobotDispenser = 111,
	CTFRobotDestruction_Robot = 287,
	CTFReviveMarker = 284,
	CTFPumpkinBomb = 281,
	CTFProjectile_BallOfFire = 252,
	CTFBaseProjectile = 183,
	CTFPointManager = 249,
	CBaseObjectUpgrade = 11,
	CTFRobotDestructionLogic = 290,
	CTFRobotDestruction_RobotGroup = 288,
	CTFRobotDestruction_RobotSpawn = 289,
	CTFPlayerDestructionLogic = 247,
	CPlayerDestructionDispenser = 101,
	CTFMinigameLogic = 232,
	CTFHalloweenMinigame_FallingPlatforms = 218,
	CTFHalloweenMinigame = 217,
	CTFMiniGame = 231,
	CTFPowerupBottle = 250,
	CTFItem = 220,
	CHalloweenSoulPack = 71,
	CTFGenericBomb = 212,
	CBonusRoundLogic = 23,
	CTFGameRulesProxy = 210,
	CTETFParticleEffect = 178,
	CTETFExplosion = 177,
	CTETFBlood = 176,
	CTFFlameManager = 205,
	CHalloweenGiftPickup = 69,
	CBonusDuckPickup = 21,
	CHalloweenPickup = 70,
	CCaptureFlagReturnIcon = 27,
	CCaptureFlag = 26,
	CBonusPack = 22,
	CTFTeam = 317,
	CTFTauntProp = 316,
	CTFPlayerResource = 248,
	CTFPlayer = 246,
	CTFRagdoll = 282,
	CTEPlayerAnimEvent = 164,
	CTFPasstimeLogic = 239,
	CPasstimeBall = 93,
	CTFObjectiveResource = 234,
	CTFGlow = 213,
	CTEFireBullets = 151,
	CTFBuffBanner = 0,
	CTFAmmoPack = 180,
	CObjectTeleporter = 89,
	CObjectSentrygun = 88,
	CTFProjectile_SentryRocket = 264,
	CObjectSapper = 87,
	CObjectCartDispenser = 85,
	CObjectDispenser = 86,
	CMonsterResource = 84,
	CFuncRespawnRoomVisualizer = 64,
	CFuncRespawnRoom = 63,
	CFuncPasstimeGoal = 61,
	CFuncForceField = 57,
	CCaptureZone = 28,
	CCurrencyPack = 31,
	CBaseObject = 10,
	CTestTraceline = 175,
	CTEWorldDecal = 179,
	CTESpriteSpray = 173,
	CTESprite = 172,
	CTESparks = 171,
	CTESmoke = 170,
	CTEShowLine = 168,
	CTEProjectedDecal = 166,
	CTEPlayerDecal = 165,
	CTEPhysicsProp = 163,
	CTEParticleSystem = 162,
	CTEMuzzleFlash = 161,
	CTELargeFunnel = 158,
	CTEKillPlayerAttachments = 157,
	CTEImpact = 156,
	CTEGlowSprite = 155,
	CTEShatterSurface = 167,
	CTEFootprintDecal = 153,
	CTEFizz = 152,
	CTEExplosion = 150,
	CTEEnergySplash = 149,
	CTEEffectDispatch = 148,
	CTEDynamicLight = 147,
	CTEDecal = 145,
	CTEClientProjectile = 144,
	CTEBubbleTrail = 143,
	CTEBubbles = 142,
	CTEBSPDecal = 141,
	CTEBreakModel = 140,
	CTEBloodStream = 139,
	CTEBloodSprite = 138,
	CTEBeamSpline = 137,
	CTEBeamRingPoint = 136,
	CTEBeamRing = 135,
	CTEBeamPoints = 134,
	CTEBeamLaser = 133,
	CTEBeamFollow = 132,
	CTEBeamEnts = 131,
	CTEBeamEntPoint = 130,
	CTEBaseBeam = 129,
	CTEArmorRicochet = 128,
	CTEMetalSparks = 160,
	CSteamJet = 122,
	CSmokeStack = 116,
	DustTrail = 354,
	CFireTrail = 50,
	SporeTrail = 361,
	SporeExplosion = 360,
	RocketTrail = 358,
	SmokeTrail = 359,
	CPropVehicleDriveable = 107,
	ParticleSmokeGrenade = 357,
	CParticleFire = 90,
	MovieExplosion = 355,
	CTEGaussExplosion = 154,
	CEnvQuadraticBeam = 43,
	CEmbers = 36,
	CEnvWind = 47,
	CPrecipitation = 106,
	CBaseTempEntity = 17,
	CWeaponIFMSteadyCam = 350,
	CWeaponIFMBaseCamera = 349,
	CWeaponIFMBase = 348,
	CTFWearableVM = 342,
	CTFWearable = 335,
	CTFWearableItem = 338,
	CEconWearable = 35,
	CBaseAttributableItem = 3,
	CEconEntity = 34,
	CHandleTest = 72,
	CTeamplayRoundBasedRulesProxy = 125,
	CTeamRoundTimer = 126,
	CSpriteTrail = 121,
	CSpriteOriented = 120,
	CSprite = 119,
	CRagdollPropAttached = 110,
	CRagdollProp = 109,
	CPoseController = 105,
	CGameRulesProxy = 68,
	CInfoLadderDismount = 75,
	CFuncLadder = 58,
	CEnvDetailController = 40,
	CWorld = 352,
	CWaterLODControl = 347,
	CWaterBullet = 346,
	CVoteController = 345,
	CVGuiScreen = 344,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 174,
	CTesla = 169,
	CTeamTrainWatcher = 127,
	CBaseTeamObjectiveResource = 16,
	CTeam = 124,
	CSun = 123,
	CParticlePerformanceMonitor = 91,
	CSpotlightEnd = 118,
	CSlideshowDisplay = 115,
	CShadowControl = 114,
	CSceneEntity = 113,
	CRopeKeyframe = 112,
	CRagdollManager = 108,
	CPhysicsPropMultiplayer = 98,
	CPhysBoxMultiplayer = 96,
	CBasePropDoor = 15,
	CDynamicProp = 33,
	CPointCommentaryNode = 104,
	CPointCamera = 103,
	CPlayerResource = 102,
	CPlasma = 100,
	CPhysMagnet = 99,
	CPhysicsProp = 97,
	CPhysBox = 95,
	CParticleSystem = 92,
	CMaterialModifyControl = 81,
	CLightGlow = 79,
	CInfoOverlayAccessor = 77,
	CFuncTrackTrain = 67,
	CFuncSmokeVolume = 66,
	CFuncRotating = 65,
	CFuncReflectiveGlass = 62,
	CFuncOccluder = 60,
	CFuncMonitor = 59,
	CFunc_LOD = 54,
	CTEDust = 146,
	CFunc_Dust = 53,
	CFuncConveyor = 56,
	CBreakableSurface = 25,
	CFuncAreaPortalWindow = 55,
	CFish = 51,
	CEntityFlame = 38,
	CFireSmoke = 49,
	CEnvTonemapController = 46,
	CEnvScreenEffect = 44,
	CEnvScreenOverlay = 45,
	CEnvProjectedTexture = 42,
	CEnvParticleScript = 41,
	CFogController = 52,
	CEntityParticleTrail = 39,
	CEntityDissolve = 37,
	CDynamicLight = 32,
	CColorCorrectionVolume = 30,
	CColorCorrection = 29,
	CBreakableProp = 24,
	CBasePlayer = 13,
	CBaseFlex = 8,
	CBaseEntity = 7,
	CBaseDoor = 6,
	CBaseCombatCharacter = 4,
	CBaseAnimatingOverlay = 2,
	CBoneFollower = 20,
	CBaseAnimating = 1,
	CInfoLightingRelative = 76,
	CAI_BaseNPC = 0,
	CBeam = 19,
	CBaseViewModel = 18,
	CBaseProjectile = 14,
	CBaseParticleEntity = 12,
	CBaseGrenade = 9,
	CBaseCombatWeapon = 5,
};