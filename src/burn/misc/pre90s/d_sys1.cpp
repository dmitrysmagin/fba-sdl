#include "tiles_generic.h"

static unsigned char System1InputPort0[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char System1InputPort1[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char System1InputPort2[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char System1InputPort3[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char System1Dip[2]           = {0, 0};
static unsigned char System1Input[4]         = {0x00, 0x00, 0x00, 0x00};
static unsigned char System1Reset            = 0;

static unsigned char *Mem                    = NULL;
static unsigned char *MemEnd                 = NULL;
static unsigned char *RamStart               = NULL;
static unsigned char *RamEnd                 = NULL;
static unsigned char *System1Rom1            = NULL;
static unsigned char *System1Rom2            = NULL;
static unsigned char *System1Ram1            = NULL;
static unsigned char *System1Ram2            = NULL;
static unsigned char *System1SpriteRam       = NULL;
static unsigned char *System1PaletteRam      = NULL;
static unsigned char *System1BgRam           = NULL;
static unsigned char *System1VideoRam        = NULL;
static unsigned char *System1BgCollisionRam  = NULL;
static unsigned char *System1SprCollisionRam = NULL;
static unsigned char *System1deRam           = NULL;
static unsigned char *System1efRam           = NULL;
static unsigned char *System1f4Ram           = NULL;
static unsigned char *System1fcRam           = NULL;
static unsigned int  *System1Palette         = NULL;
static unsigned char *System1Tiles           = NULL;
static unsigned char *System1Sprites         = NULL;
static unsigned char *System1TempGfx         = NULL;

static unsigned char *System1Fetch1          = NULL;
static unsigned char *System1FetchData1      = NULL;

static unsigned char  System1ScrollX[2] = {0, 0};
static unsigned char  System1ScrollY = 0;

static int System1SpriteRomSize;
static int System1NumTiles;
static int System1SpriteXOffset;
static UINT32 System1TilesPenUsage[0x800];

static unsigned char *SpriteOnScreenMap;
static int BgScrollX;
static int BgScrollY;
static int System1VideoMode;
static int System1FlipScreen;

static int System1SoundLatch;

static int nCyclesDone[2], nCyclesTotal[2];
static int nCyclesSegment;

/*==============================================================================================
Input Definitions
===============================================================================================*/

static struct BurnInputInfo FlickyInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System1InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System1InputPort2 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System1InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System1InputPort2 + 5, "p2 start"  },

	{"P1 Left"           , BIT_DIGITAL  , System1InputPort0 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System1InputPort0 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System1InputPort0 + 2, "p1 fire 1" },

	{"P2 Left"           , BIT_DIGITAL  , System1InputPort1 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System1InputPort1 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System1InputPort1 + 2, "p2 fire 1" },

	{"Reset"             , BIT_DIGITAL  , &System1Reset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , System1InputPort2 + 3, "service"   },
	{"Test"              , BIT_DIGITAL  , System1InputPort2 + 2, "diag"      },
	{"Dip 1"             , BIT_DIPSWITCH, System1Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System1Dip + 1       , "dip"       },
};

STDINPUTINFO(Flicky);

static struct BurnInputInfo MyheroInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System1InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System1InputPort2 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System1InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System1InputPort2 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System1InputPort0 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System1InputPort0 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System1InputPort0 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System1InputPort0 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System1InputPort0 + 1, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System1InputPort0 + 2, "p1 fire 2" },

	{"P2 Up"             , BIT_DIGITAL  , System1InputPort1 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System1InputPort1 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System1InputPort1 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System1InputPort1 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System1InputPort1 + 1, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System1InputPort1 + 2, "p2 fire 2" },

	{"Reset"             , BIT_DIGITAL  , &System1Reset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , System1InputPort2 + 3, "service"   },
	{"Test"              , BIT_DIGITAL  , System1InputPort2 + 2, "diag"      },
	{"Dip 1"             , BIT_DIPSWITCH, System1Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System1Dip + 1       , "dip"       },
};

STDINPUTINFO(Myhero);

static struct BurnInputInfo SeganinjInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System1InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System1InputPort2 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System1InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System1InputPort2 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System1InputPort0 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System1InputPort0 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System1InputPort0 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System1InputPort0 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System1InputPort0 + 0, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System1InputPort0 + 1, "p1 fire 2" },
	{"P1 Fire 3"         , BIT_DIGITAL  , System1InputPort0 + 2, "p1 fire 3" },

	{"P2 Up"             , BIT_DIGITAL  , System1InputPort1 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System1InputPort1 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System1InputPort1 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System1InputPort1 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System1InputPort1 + 0, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System1InputPort1 + 1, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL  , System1InputPort1 + 2, "p2 fire 3" },

	{"Reset"             , BIT_DIGITAL  , &System1Reset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , System1InputPort2 + 3, "service"   },
	{"Test"              , BIT_DIGITAL  , System1InputPort2 + 2, "diag"      },
	{"Dip 1"             , BIT_DIPSWITCH, System1Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System1Dip + 1       , "dip"       },
};

STDINPUTINFO(Seganinj);

static struct BurnInputInfo UpndownInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System1InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System1InputPort2 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System1InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System1InputPort2 + 5, "p2 start"  },

	{"P1 Up"             , BIT_DIGITAL  , System1InputPort0 + 5, "p1 up"     },
	{"P1 Down"           , BIT_DIGITAL  , System1InputPort0 + 4, "p1 down"   },
	{"P1 Left"           , BIT_DIGITAL  , System1InputPort0 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System1InputPort0 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System1InputPort0 + 2, "p1 fire 1" },

	{"P2 Up"             , BIT_DIGITAL  , System1InputPort1 + 5, "p2 up"     },
	{"P2 Down"           , BIT_DIGITAL  , System1InputPort1 + 4, "p2 down"   },
	{"P2 Left"           , BIT_DIGITAL  , System1InputPort1 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System1InputPort1 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System1InputPort1 + 2, "p2 fire 1" },

	{"Reset"             , BIT_DIGITAL  , &System1Reset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , System1InputPort2 + 3, "service"   },
	{"Test"              , BIT_DIGITAL  , System1InputPort2 + 2, "diag"      },
	{"Dip 1"             , BIT_DIPSWITCH, System1Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System1Dip + 1       , "dip"       },
};

STDINPUTINFO(Upndown);

static struct BurnInputInfo WboyInputList[] = {
	{"Coin 1"            , BIT_DIGITAL  , System1InputPort2 + 0, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL  , System1InputPort2 + 4, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL  , System1InputPort2 + 1, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL  , System1InputPort2 + 5, "p2 start"  },

	{"P1 Left"           , BIT_DIGITAL  , System1InputPort0 + 7, "p1 left"   },
	{"P1 Right"          , BIT_DIGITAL  , System1InputPort0 + 6, "p1 right"  },
	{"P1 Fire 1"         , BIT_DIGITAL  , System1InputPort0 + 1, "p1 fire 1" },
	{"P1 Fire 2"         , BIT_DIGITAL  , System1InputPort0 + 2, "p1 fire 2" },

	{"P2 Left"           , BIT_DIGITAL  , System1InputPort1 + 7, "p2 left"   },
	{"P2 Right"          , BIT_DIGITAL  , System1InputPort1 + 6, "p2 right"  },
	{"P2 Fire 1"         , BIT_DIGITAL  , System1InputPort1 + 1, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL  , System1InputPort1 + 2, "p2 fire 2" },

	{"Reset"             , BIT_DIGITAL  , &System1Reset        , "reset"     },
	{"Service"           , BIT_DIGITAL  , System1InputPort2 + 3, "service"   },
	{"Test"              , BIT_DIGITAL  , System1InputPort2 + 2, "diag"      },
	{"Dip 1"             , BIT_DIPSWITCH, System1Dip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH, System1Dip + 1       , "dip"       },
};

STDINPUTINFO(Wboy);

inline void System1ClearOpposites(unsigned char* nJoystickInputs)
{
	if ((*nJoystickInputs & 0x30) == 0x30) {
		*nJoystickInputs &= ~0x30;
	}
	if ((*nJoystickInputs & 0xc0) == 0xc0) {
		*nJoystickInputs &= ~0xc0;
	}
}

inline void System1MakeInputs()
{
	// Reset Inputs
	System1Input[0] = System1Input[1] = System1Input[2] = System1Input[3] = 0x00;

	// Compile Digital Inputs
	for (int i = 0; i < 8; i++) {
		System1Input[0] |= (System1InputPort0[i] & 1) << i;
		System1Input[1] |= (System1InputPort1[i] & 1) << i;
		System1Input[2] |= (System1InputPort2[i] & 1) << i;
		System1Input[3] |= (System1InputPort3[i] & 1) << i;
	}

	// Clear Opposites
	System1ClearOpposites(&System1Input[0]);
	System1ClearOpposites(&System1Input[1]);
}

/*==============================================================================================
ROM Descriptions
===============================================================================================*/

static struct BurnRomInfo FlickyRomDesc[] = {
	{ "epr5978a.116",      0x004000, 0x296f1492, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr5979a.109",      0x004000, 0x64b03ef9, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	
	{ "epr-5869.120",      0x002000, 0x6d220d4e, BRF_ESS | BRF_PRG }, //  2	Z80 #2 Program Code
	
	{ "epr-5868.62",       0x002000, 0x7402256b, BRF_GRA },		  //  3 Tiles
	{ "epr-5867.61",       0x002000, 0x2f5ce930, BRF_GRA },		  //  4 Tiles
	{ "epr-5866.64",       0x002000, 0x967f1d9a, BRF_GRA },		  //  5 Tiles
	{ "epr-5865.63",       0x002000, 0x03d9a34c, BRF_GRA },		  //  6 Tiles
	{ "epr-5864.66",       0x002000, 0xe659f358, BRF_GRA },		  //  7 Tiles
	{ "epr-5863.65",       0x002000, 0xa496ca15, BRF_GRA },		  //  8 Tiles
	
	{ "epr-5855.117",      0x004000, 0xb5f894a1, BRF_GRA },		  //  9 Sprites
	{ "epr-5856.110",      0x004000, 0x266af78f, BRF_GRA },		  //  10 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  11 Timing PROM
};


STD_ROM_PICK(Flicky);
STD_ROM_FN(Flicky);

static struct BurnRomInfo Flicks2RomDesc[] = {
	{ "epr-6621.bin",      0x004000, 0xb21ff546, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-6622.bin",      0x004000, 0x133a8bf1, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	
	{ "epr-5869.120",      0x002000, 0x6d220d4e, BRF_ESS | BRF_PRG }, //  2	Z80 #2 Program Code
	
	{ "epr-5868.62",       0x002000, 0x7402256b, BRF_GRA },		  //  3 Tiles
	{ "epr-5867.61",       0x002000, 0x2f5ce930, BRF_GRA },		  //  4 Tiles
	{ "epr-5866.64",       0x002000, 0x967f1d9a, BRF_GRA },		  //  5 Tiles
	{ "epr-5865.63",       0x002000, 0x03d9a34c, BRF_GRA },		  //  6 Tiles
	{ "epr-5864.66",       0x002000, 0xe659f358, BRF_GRA },		  //  7 Tiles
	{ "epr-5863.65",       0x002000, 0xa496ca15, BRF_GRA },		  //  8 Tiles
	
	{ "epr-5855.117",      0x004000, 0xb5f894a1, BRF_GRA },		  //  9 Sprites
	{ "epr-5856.110",      0x004000, 0x266af78f, BRF_GRA },		  //  10 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  11 Timing PROM
};


STD_ROM_PICK(Flicks2);
STD_ROM_FN(Flicks2);

static struct BurnRomInfo MyheroRomDesc[] = {
	{ "epr6963b.116",      0x004000, 0x4daf89d4, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr6964a.109",      0x004000, 0xc26188e5, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-6927.96",       0x004000, 0x3cbbaf64, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	
	{ "epr-69xx.120",      0x002000, 0x0039e1e9, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code
	
	{ "epr-6966.62",       0x002000, 0x157f0401, BRF_GRA },		  //  4 Tiles
	{ "epr-6961.61",       0x002000, 0xbe53ce47, BRF_GRA },		  //  5 Tiles
	{ "epr-6960.64",       0x002000, 0xbd381baa, BRF_GRA },		  //  6 Tiles
	{ "epr-6959.63",       0x002000, 0xbc04e79a, BRF_GRA },		  //  7 Tiles
	{ "epr-6958.66",       0x002000, 0x714f2c26, BRF_GRA },		  //  8 Tiles
	{ "epr-6957.65",       0x002000, 0x80920112, BRF_GRA },		  //  9 Tiles
	
	{ "epr-6921.117",      0x004000, 0xf19e05a1, BRF_GRA },		  //  10 Sprites
	{ "epr-6923.04",       0x004000, 0x7988adc3, BRF_GRA },		  //  11 Sprites
	{ "epr-6922.110",      0x004000, 0x37f77a78, BRF_GRA },		  //  12 Sprites
	{ "epr-6924.05",       0x004000, 0x42bdc8f6, BRF_GRA },		  //  13 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  14 Timing PROM
};

STD_ROM_PICK(Myhero);
STD_ROM_FN(Myhero);

static struct BurnRomInfo RegulusRomDesc[] = {
	{ "epr-5640a.129",     0x002000, 0xdafb1528, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-5641a.130",     0x002000, 0x0fcc850e, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-5642a.131",     0x002000, 0x4feffa17, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-5643a.132",     0x002000, 0xb8ac7eb4, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-5644.133",      0x002000, 0xffd05b7d, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-5645a.134",     0x002000, 0x6b4bf77c, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5652.3",        0x002000, 0x74edcb98, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5651.82",       0x002000, 0xf07f3e82, BRF_GRA },		  //  7 Tiles
	{ "epr-5650.65",       0x002000, 0x84c1baa2, BRF_GRA },		  //  8 Tiles
	{ "epr-5649.81",       0x002000, 0x6774c895, BRF_GRA },		  //  9 Tiles
	{ "epr-5648.64",       0x002000, 0x0c69e92a, BRF_GRA },		  //  10 Tiles
	{ "epr-5647.80",       0x002000, 0x9330f7b5, BRF_GRA },		  //  11 Tiles
	{ "epr-5646.63",       0x002000, 0x4dfacbbc, BRF_GRA },		  //  12 Tiles
	
	{ "epr-5638.86",       0x004000, 0x617363dd, BRF_GRA },		  //  13 Sprites
	{ "epr-5639.93",       0x004000, 0xa4ec5131, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};


STD_ROM_PICK(Regulus);
STD_ROM_FN(Regulus);

static struct BurnRomInfo RegulusuRomDesc[] = {
	{ "epr-5950.129",      0x002000, 0x3b047b67, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-5951.130",      0x002000, 0xd66453ab, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-5952.131",      0x002000, 0xf3d0158a, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-5953.132",      0x002000, 0xa9ad4f44, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-5644.133",      0x002000, 0xffd05b7d, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-5955.134",      0x002000, 0x65ddb2a3, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5652.3",        0x002000, 0x74edcb98, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5651.82",       0x002000, 0xf07f3e82, BRF_GRA },		  //  7 Tiles
	{ "epr-5650.65",       0x002000, 0x84c1baa2, BRF_GRA },		  //  8 Tiles
	{ "epr-5649.81",       0x002000, 0x6774c895, BRF_GRA },		  //  9 Tiles
	{ "epr-5648.64",       0x002000, 0x0c69e92a, BRF_GRA },		  //  10 Tiles
	{ "epr-5647.80",       0x002000, 0x9330f7b5, BRF_GRA },		  //  11 Tiles
	{ "epr-5646.63",       0x002000, 0x4dfacbbc, BRF_GRA },		  //  12 Tiles
	
	{ "epr-5638.86",       0x004000, 0x617363dd, BRF_GRA },		  //  13 Sprites
	{ "epr-5639.93",       0x004000, 0xa4ec5131, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};


STD_ROM_PICK(Regulusu);
STD_ROM_FN(Regulusu);

static struct BurnRomInfo SeganinjRomDesc[] = {
	{ "epr-.116",          0x004000, 0xa5d0c9d0, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-.109",          0x004000, 0xb9e6775c, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-6552.96",       0x004000, 0xf2eeb0d8, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	
	{ "epr-6559.120",      0x002000, 0x5a1570ee, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code
	
	{ "epr-6558.62",       0x002000, 0x2af9eaeb, BRF_GRA },		  //  4 Tiles
	{ "epr-6592.61",       0x002000, 0x7804db86, BRF_GRA },		  //  5 Tiles
	{ "epr-6556.64",       0x002000, 0x79fd26f7, BRF_GRA },		  //  6 Tiles
	{ "epr-6590.63",       0x002000, 0xbf858cad, BRF_GRA },		  //  7 Tiles
	{ "epr-6554.66",       0x002000, 0x5ac9d205, BRF_GRA },		  //  8 Tiles
	{ "epr-6588.65",       0x002000, 0xdc931dbb, BRF_GRA },		  //  9 Tiles
	
	{ "epr-6546.117",      0x004000, 0xa4785692, BRF_GRA },		  //  10 Sprites
	{ "epr-6548.04",       0x004000, 0xbdf278c1, BRF_GRA },		  //  11 Sprites
	{ "epr-6547.110",      0x004000, 0x34451b08, BRF_GRA },		  //  12 Sprites
	{ "epr-6549.05",       0x004000, 0xd2057668, BRF_GRA },		  //  13 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  14 Timing PROM
};


STD_ROM_PICK(Seganinj);
STD_ROM_FN(Seganinj);

static struct BurnRomInfo SeganinuRomDesc[] = {
	{ "epr-7149.116",      0x004000, 0xcd9fade7, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-7150.109",      0x004000, 0xc36351e2, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-6552.96",       0x004000, 0xf2eeb0d8, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	
	{ "epr-6559.120",      0x002000, 0x5a1570ee, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code
	
	{ "epr-6558.62",       0x002000, 0x2af9eaeb, BRF_GRA },		  //  4 Tiles
	{ "epr-6592.61",       0x002000, 0x7804db86, BRF_GRA },		  //  5 Tiles
	{ "epr-6556.64",       0x002000, 0x79fd26f7, BRF_GRA },		  //  6 Tiles
	{ "epr-6590.63",       0x002000, 0xbf858cad, BRF_GRA },		  //  7 Tiles
	{ "epr-6554.66",       0x002000, 0x5ac9d205, BRF_GRA },		  //  8 Tiles
	{ "epr-6588.65",       0x002000, 0xdc931dbb, BRF_GRA },		  //  9 Tiles
	
	{ "epr-6546.117",      0x004000, 0xa4785692, BRF_GRA },		  //  10 Sprites
	{ "epr-6548.04",       0x004000, 0xbdf278c1, BRF_GRA },		  //  11 Sprites
	{ "epr-6547.110",      0x004000, 0x34451b08, BRF_GRA },		  //  12 Sprites
	{ "epr-6549.05",       0x004000, 0xd2057668, BRF_GRA },		  //  13 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  14 Timing PROM
};


STD_ROM_PICK(Seganinu);
STD_ROM_FN(Seganinu);

static struct BurnRomInfo NprincsuRomDesc[] = {
	{ "epr-6573.129",      0x002000, 0xd2919c7d, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-6574.130",      0x002000, 0x5a132833, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-6575.131",      0x002000, 0xa94b0bd4, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-6576.132",      0x002000, 0x27d3bbdb, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-6577.133",      0x002000, 0x73616e03, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-6578.134",      0x002000, 0xab68499f, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-6559.120",      0x002000, 0x5a1570ee, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-6558.62",       0x002000, 0x2af9eaeb, BRF_GRA },		  //  7 Tiles
	{ "epr-6557.61",       0x002000, 0x6eb131d0, BRF_GRA },		  //  8 Tiles
	{ "epr-6556.64",       0x002000, 0x79fd26f7, BRF_GRA },		  //  9 Tiles
	{ "epr-6555.63",       0x002000, 0x7f669aac, BRF_GRA },		  //  10 Tiles
	{ "epr-6554.66",       0x002000, 0x5ac9d205, BRF_GRA },		  //  11 Tiles
	{ "epr-6553.65",       0x002000, 0xeb82a8fe, BRF_GRA },		  //  12 Tiles
	
	{ "epr-6546.117",      0x004000, 0xa4785692, BRF_GRA },		  //  13 Sprites
	{ "epr-6548.04",       0x004000, 0xbdf278c1, BRF_GRA },		  //  14 Sprites
	{ "epr-6547.110",      0x004000, 0x34451b08, BRF_GRA },		  //  15 Sprites
	{ "epr-6549.05",       0x004000, 0xd2057668, BRF_GRA },		  //  16 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  17 Timing PROM
};


STD_ROM_PICK(Nprincsu);
STD_ROM_FN(Nprincsu);

static struct BurnRomInfo StarjackRomDesc[] = {
	{ "epr5320b.129",      0x002000, 0x7ab72ecd, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr5321a.130",      0x002000, 0x38b99050, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr5322a.131",      0x002000, 0x103a595b, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-5323.132",      0x002000, 0x46af0d58, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-5324.133",      0x002000, 0x1e89efe2, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-5325.134",      0x002000, 0xd6e379a1, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5332.3",        0x002000, 0x7a72ab3d, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5331.82",       0x002000, 0x251d898f, BRF_GRA },		  //  7 Tiles
	{ "epr-5330.65",       0x002000, 0xeb048745, BRF_GRA },		  //  8 Tiles
	{ "epr-5329.81",       0x002000, 0x3e8bcaed, BRF_GRA },		  //  9 Tiles
	{ "epr-5328.64",       0x002000, 0x9ed7849f, BRF_GRA },		  //  10 Tiles
	{ "epr-5327.80",       0x002000, 0x79e92cb1, BRF_GRA },		  //  11 Tiles
	{ "epr-5326.63",       0x002000, 0xba7e2b47, BRF_GRA },		  //  12 Tiles
	
	{ "epr-5318.86",       0x004000, 0x6f2e1fd3, BRF_GRA },		  //  13 Sprites
	{ "epr-5319.93",       0x004000, 0xebee4999, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};


STD_ROM_PICK(Starjack);
STD_ROM_FN(Starjack);

static struct BurnRomInfo StarjacsRomDesc[] = {
	{ "a1_ic29.129",       0x002000, 0x59a22a1f, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "a1_ic30.130",       0x002000, 0x7f4597dc, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "a1_ic31.131",       0x002000, 0x6074c046, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "a1_ic32.132",       0x002000, 0x1c48a3fa, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "a1_ic33.133",       0x002000, 0x7598bd51, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "a1_ic34.134",       0x002000, 0xf66fa604, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5332.3",        0x002000, 0x7a72ab3d, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5331.82",       0x002000, 0x251d898f, BRF_GRA },		  //  7 Tiles
	{ "a1_ic65.65",        0x002000, 0x0ab1893c, BRF_GRA },		  //  8 Tiles
	{ "epr-5329.81",       0x002000, 0x3e8bcaed, BRF_GRA },		  //  9 Tiles
	{ "a1_ic64.64",        0x002000, 0x7f628ae6, BRF_GRA },		  //  10 Tiles
	{ "epr-5327.80",       0x002000, 0x79e92cb1, BRF_GRA },		  //  11 Tiles
	{ "a1_ic63.63",        0x002000, 0x5bcb253e, BRF_GRA },		  //  12 Tiles
	
	{ "a1_ic86.86",        0x004000, 0x6f2e1fd3, BRF_GRA },		  //  13 Sprites
	{ "a1_ic93.93",        0x004000, 0x07987244, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};


STD_ROM_PICK(Starjacs);
STD_ROM_FN(Starjacs);

static struct BurnRomInfo UpndownRomDesc[] = {
	{ "epr5516a.129",      0x002000, 0x038c82da, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr5517a.130",      0x002000, 0x6930e1de, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-5518.131",      0x002000, 0x2a370c99, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-5519.132",      0x002000, 0x9d664a58, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-5520.133",      0x002000, 0x208dfbdf, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-5521.134",      0x002000, 0xe7b8d87a, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5535.3",        0x002000, 0xcf4e4c45, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5527.82",       0x002000, 0xb2d616f1, BRF_GRA },		  //  7 Tiles
	{ "epr-5526.65",       0x002000, 0x8a8b33c2, BRF_GRA },		  //  8 Tiles
	{ "epr-5525.81",       0x002000, 0xe749c5ef, BRF_GRA },		  //  9 Tiles
	{ "epr-5524.64",       0x002000, 0x8b886952, BRF_GRA },		  //  10 Tiles
	{ "epr-5523.80",       0x002000, 0xdede35d9, BRF_GRA },		  //  11 Tiles
	{ "epr-5522.63",       0x002000, 0x5e6d9dff, BRF_GRA },		  //  12 Tiles
	
	{ "epr-5514.86",       0x004000, 0xfcc0a88b, BRF_GRA },		  //  13 Sprites
	{ "epr-5515.93",       0x004000, 0x60908838, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};

STD_ROM_PICK(Upndown);
STD_ROM_FN(Upndown);

static struct BurnRomInfo UpndownuRomDesc[] = {
	{ "epr-5679.129",      0x002000, 0xc4f2f9c2, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-5680.130",      0x002000, 0x837f021c, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-5681.131",      0x002000, 0xe1c7ff7e, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "epr-5682.132",      0x002000, 0x4a5edc1e, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-5520.133",      0x002000, 0x208dfbdf, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-5684.133",      0x002000, 0x32fa95da, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr-5528.3",        0x002000, 0x00cd44ab, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-5527.82",       0x002000, 0xb2d616f1, BRF_GRA },		  //  7 Tiles
	{ "epr-5526.65",       0x002000, 0x8a8b33c2, BRF_GRA },		  //  8 Tiles
	{ "epr-5525.81",       0x002000, 0xe749c5ef, BRF_GRA },		  //  9 Tiles
	{ "epr-5524.64",       0x002000, 0x8b886952, BRF_GRA },		  //  10 Tiles
	{ "epr-5523.80",       0x002000, 0xdede35d9, BRF_GRA },		  //  11 Tiles
	{ "epr-5522.63",       0x002000, 0x5e6d9dff, BRF_GRA },		  //  12 Tiles
	
	{ "epr-5514.86",       0x004000, 0xfcc0a88b, BRF_GRA },		  //  13 Sprites
	{ "epr-5515.93",       0x004000, 0x60908838, BRF_GRA },		  //  14 Sprites

	{ "pr-5317.106",       0x000100, 0x648350b8, BRF_OPT },		  //  15 Timing PROM
};


STD_ROM_PICK(Upndownu);
STD_ROM_FN(Upndownu);

static struct BurnRomInfo WboyRomDesc[] = {
	{ "epr-7489.116",      0x004000, 0x130f4b70, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "epr-7490.109",      0x004000, 0x9e656733, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "epr-7491.96",       0x004000, 0x1f7d0efe, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	
	{ "epr-7498.120",      0x002000, 0x78ae1e7b, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code
	
	{ "epr-7497.62",       0x002000, 0x08d609ca, BRF_GRA },		  //  4 Tiles
	{ "epr-7496.61",       0x002000, 0x6f61fdf1, BRF_GRA },		  //  5 Tiles
	{ "epr-7495.64",       0x002000, 0x6a0d2c2d, BRF_GRA },		  //  6 Tiles
	{ "epr-7494.63",       0x002000, 0xa8e281c7, BRF_GRA },		  //  7 Tiles
	{ "epr-7493.66",       0x002000, 0x89305df4, BRF_GRA },		  //  8 Tiles
	{ "epr-7492.65",       0x002000, 0x60f806b1, BRF_GRA },		  //  9 Tiles
	
	{ "epr-7485.117",      0x004000, 0xc2891722, BRF_GRA },		  //  10 Sprites
	{ "epr-7487.04",       0x004000, 0x2d3a421b, BRF_GRA },		  //  11 Sprites
	{ "epr-7486.110",      0x004000, 0x8d622c50, BRF_GRA },		  //  12 Sprites
	{ "epr-7488.05",       0x004000, 0x007c2f1b, BRF_GRA },		  //  13 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  14 Timing PROM
};


STD_ROM_PICK(Wboy);
STD_ROM_FN(Wboy);

static struct BurnRomInfo Wboy2uRomDesc[] = {
	{ "ic129_02.bin",      0x002000, 0x32c4b709, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "ic130_03.bin",      0x002000, 0x56463ede, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "ic131_04.bin",      0x002000, 0x775ed392, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "ic132_05.bin",      0x002000, 0x7b922708, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "epr-7591.133",      0x002000, 0x8379aa23, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "epr-7592.134",      0x002000, 0xc767a5d7, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr7498a.3",        0x002000, 0xc198205c, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-7497.62",       0x002000, 0x08d609ca, BRF_GRA },		  //  7 Tiles
	{ "epr-7496.61",       0x002000, 0x6f61fdf1, BRF_GRA },		  //  8 Tiles
	{ "epr-7495.64",       0x002000, 0x6a0d2c2d, BRF_GRA },		  //  9 Tiles
	{ "epr-7494.63",       0x002000, 0xa8e281c7, BRF_GRA },		  //  10 Tiles
	{ "epr-7493.66",       0x002000, 0x89305df4, BRF_GRA },		  //  11 Tiles
	{ "epr-7492.65",       0x002000, 0x60f806b1, BRF_GRA },		  //  12 Tiles
	
	{ "epr-7485.117",      0x004000, 0xc2891722, BRF_GRA },		  //  13 Sprites
	{ "epr-7487.04",       0x004000, 0x2d3a421b, BRF_GRA },		  //  14 Sprites
	{ "epr-7486.110",      0x004000, 0x8d622c50, BRF_GRA },		  //  15 Sprites
	{ "epr-7488.05",       0x004000, 0x007c2f1b, BRF_GRA },		  //  16 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  17 Timing PROM
};


STD_ROM_PICK(Wboy2u);
STD_ROM_FN(Wboy2u);

static struct BurnRomInfo WboyuRomDesc[] = {
	{ "ic116_89.bin",      0x004000, 0x73d8cef0, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "ic109_90.bin",      0x004000, 0x29546828, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "ic096_91.bin",      0x004000, 0xc7145c2a, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	
	{ "epr-7498.120",      0x002000, 0x78ae1e7b, BRF_ESS | BRF_PRG }, //  3	Z80 #2 Program Code
	
	{ "epr-7497.62",       0x002000, 0x08d609ca, BRF_GRA },		  //  4 Tiles
	{ "epr-7496.61",       0x002000, 0x6f61fdf1, BRF_GRA },		  //  5 Tiles
	{ "epr-7495.64",       0x002000, 0x6a0d2c2d, BRF_GRA },		  //  6 Tiles
	{ "epr-7494.63",       0x002000, 0xa8e281c7, BRF_GRA },		  //  7 Tiles
	{ "epr-7493.66",       0x002000, 0x89305df4, BRF_GRA },		  //  8 Tiles
	{ "epr-7492.65",       0x002000, 0x60f806b1, BRF_GRA },		  //  9 Tiles
	
	{ "ic117_85.bin",      0x004000, 0x1ee96ae8, BRF_GRA },		  //  10 Sprites
	{ "ic004_87.bin",      0x004000, 0x119735bb, BRF_GRA },		  //  11 Sprites
	{ "ic110_86.bin",      0x004000, 0x26d0fac4, BRF_GRA },		  //  12 Sprites
	{ "ic005_88.bin",      0x004000, 0x2602e519, BRF_GRA },		  //  13 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  14 Timing PROM
};


STD_ROM_PICK(Wboyu);
STD_ROM_FN(Wboyu);

static struct BurnRomInfo WbdeluxeRomDesc[] = {
	{ "wbd1.bin",          0x002000, 0xa1bedbd7, BRF_ESS | BRF_PRG }, //  0	Z80 #1 Program Code
	{ "ic130_03.bin",      0x002000, 0x56463ede, BRF_ESS | BRF_PRG }, //  1	Z80 #1 Program Code
	{ "wbd3.bin",          0x002000, 0x6fcdbd4c, BRF_ESS | BRF_PRG }, //  2	Z80 #1 Program Code
	{ "ic132_05.bin",      0x002000, 0x7b922708, BRF_ESS | BRF_PRG }, //  3	Z80 #1 Program Code
	{ "wbd5.bin",          0x002000, 0xf6b02902, BRF_ESS | BRF_PRG }, //  4	Z80 #1 Program Code
	{ "wbd6.bin",          0x002000, 0x43df21fe, BRF_ESS | BRF_PRG }, //  5	Z80 #1 Program Code
	
	{ "epr7498a.3",        0x002000, 0xc198205c, BRF_ESS | BRF_PRG }, //  6	Z80 #2 Program Code
	
	{ "epr-7497.62",       0x002000, 0x08d609ca, BRF_GRA },		  //  7 Tiles
	{ "epr-7496.61",       0x002000, 0x6f61fdf1, BRF_GRA },		  //  8 Tiles
	{ "epr-7495.64",       0x002000, 0x6a0d2c2d, BRF_GRA },		  //  9 Tiles
	{ "epr-7494.63",       0x002000, 0xa8e281c7, BRF_GRA },		  //  10 Tiles
	{ "epr-7493.66",       0x002000, 0x89305df4, BRF_GRA },		  //  11 Tiles
	{ "epr-7492.65",       0x002000, 0x60f806b1, BRF_GRA },		  //  12 Tiles
	
	{ "epr-7485.117",      0x004000, 0xc2891722, BRF_GRA },		  //  13 Sprites
	{ "epr-7487.04",       0x004000, 0x2d3a421b, BRF_GRA },		  //  14 Sprites
	{ "epr-7486.110",      0x004000, 0x8d622c50, BRF_GRA },		  //  15 Sprites
	{ "epr-7488.05",       0x004000, 0x007c2f1b, BRF_GRA },		  //  16 Sprites

	{ "pr-5317.76",        0x000100, 0x648350b8, BRF_OPT },		  //  17 Timing PROM
};


STD_ROM_PICK(Wbdeluxe);
STD_ROM_FN(Wbdeluxe);

/*==============================================================================================
Allocate Memory
===============================================================================================*/

static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	System1Rom1            = Next; Next += 0x010000;
	System1Fetch1          = Next; Next += 0x010000;
	System1FetchData1      = Next; Next += 0x010000;
	System1Rom2            = Next; Next += 0x008000;

	RamStart = Next;

	System1Ram1            = Next; Next += 0x0020fd;
	System1Ram2            = Next; Next += 0x000800;
	System1SpriteRam       = Next; Next += 0x000200;
	System1PaletteRam      = Next; Next += 0x000600;
	System1BgRam           = Next; Next += 0x000800;
	System1VideoRam        = Next; Next += 0x000700;
	System1BgCollisionRam  = Next; Next += 0x000400;
	System1SprCollisionRam = Next; Next += 0x000400;
	System1deRam           = Next; Next += 0x000200;
	System1efRam           = Next; Next += 0x000100;
	System1f4Ram           = Next; Next += 0x000400;
	System1fcRam           = Next; Next += 0x000400;
	
	RamEnd = Next;

	System1Sprites         = Next; Next += System1SpriteRomSize;
	System1Tiles           = Next; Next += (System1NumTiles * 8 * 8);
	System1Palette         = (unsigned int*)Next; Next += 0x000600 * sizeof(unsigned int);
	MemEnd = Next;

	return 0;
}

/*==============================================================================================
Reset Functions
===============================================================================================*/

static int System1DoReset()
{
	ZetOpen(0);
	ZetReset();
	ZetClose();
	
	ZetOpen(1);
	ZetReset();
	ZetClose();
	
	System1SoundLatch = 0;
	
	System1ScrollX[0] = System1ScrollX[1] = System1ScrollY = 0;
	BgScrollX = 0;
	BgScrollY = 0;
	System1VideoMode = 0;
	System1FlipScreen = 0;
	
	return 0;
}

/*==============================================================================================
Memory Handlers
===============================================================================================*/

unsigned char __fastcall System1Z80Read1(unsigned short a)
{
	switch (a) {
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #1 Read %04X\n"), a);

	return 0;
}

void __fastcall System1Z80Write1(unsigned short a, unsigned char d)
{
	if (a >= 0xf000 && a <= 0xf3ff) {
		System1BgCollisionRam[a - 0xf000] = 0x7e;
		return;
	}
	
	if (a >= 0xf800 && a <= 0xfbff) {
		System1SprCollisionRam[a - 0xf800] = 0x7e;
		return;
	}

	switch (a) {
		case 0xefbd: {
			System1ScrollY = d;
			break;
		}
		
		case 0xeffc: {
			System1ScrollX[0] = d;
			break;
		}
		
		case 0xeffd: {
			System1ScrollX[1] = d;
			break;
		}
	}
	
	if (a >= 0xef00 && a <= 0xefff) {
		System1efRam[a - 0xef00] = d;
		return;
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #1 Write %04X -> %02X\n"), a, d);
}

unsigned char __fastcall System1Z80PortRead1(unsigned short a)
{
	a &= 0xff;
	
	switch (a) {
		case 0x00: {
			return 0xff - System1Input[0];
		}
		
		case 0x04: {
			return 0xff - System1Input[1];
		}
		
		case 0x08: {
			return 0xff - System1Input[2];
		}
		
//		case 0x0c: {
//			return System1Dip[0];
//		}
		
		case 0x0d: {
			return System1Dip[1];
		}
		
		case 0x10: {
			return System1Dip[1];
		}
		
		case 0x15: {
			return System1VideoMode;
		}
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #1 Port Read %02X\n"), a);

	return 0;
}

void __fastcall System1Z80PortWrite1(unsigned short a, unsigned char d)
{
	a &= 0xff;
	
	switch (a) {
		case 0x14:
		case 0x18: {
			System1SoundLatch = d;
			bprintf(PRINT_NORMAL, _T("Sound Latch Sent %x\n"), d);
			ZetClose();
			ZetOpen(1);
			ZetNmi();
			nCyclesDone[1] += ZetRun(100);
			ZetClose();
			ZetOpen(0);
			return;
		}
		
		case 0x15:
		case 0x19: {
			System1VideoMode = d;
			System1FlipScreen = d & 0x80;
			return;
		}
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #1 Port Write %02X -> %02X\n"), a, d);
}

unsigned char __fastcall System1Z80Read2(unsigned short a)
{
	switch (a) {
		case 0xe000: {
			bprintf(PRINT_NORMAL, _T("Sound Latch Read %x\n"), System1SoundLatch);
			return System1SoundLatch;
		}
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #2 Read %04X\n"), a);

	return 0;
}

void __fastcall System1Z80Write2(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xa000:
		case 0xa001:
		case 0xa002:
		case 0xa003: {
			// SN76496_0_w
			return;
		}
		
		case 0xc000:
		case 0xc001:
		case 0xc002:
		case 0xc003: {
			// SN76496_1_w
			return;
		}
	}
		
	bprintf(PRINT_NORMAL, _T("Z80 #2 Write %04X -> %02X\n"), a, d);
}

unsigned char __fastcall System1Z80PortRead2(unsigned short a)
{
	a &= 0xff;
	
	switch (a) {
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #2 Port Read %02X\n"), a);

	return 0;
}

void __fastcall System1Z80PortWrite2(unsigned short a, unsigned char d)
{
	a &= 0xff;
	
	switch (a) {
	}
	
	bprintf(PRINT_NORMAL, _T("Z80 #2 Port Write %02X -> %02X\n"), a, d);
}

/*==============================================================================================
Driver Inits
===============================================================================================*/

static void sega_decode(const UINT8 convtable[32][4])
{
	int A;

	int length = 0x10000;
	int cryptlen = 0xc000;
	UINT8 *rom = System1FetchData1;
	UINT8 *decrypted = System1Fetch1;
	
	for (A = 0x0000;A < cryptlen;A++)
	{
		int xor1 = 0;

		UINT8 src = rom[A];

		/* pick the translation table from bits 0, 4, 8 and 12 of the address */
		int row = (A & 1) + (((A >> 4) & 1) << 1) + (((A >> 8) & 1) << 2) + (((A >> 12) & 1) << 3);

		/* pick the offset in the table from bits 3 and 5 of the source data */
		int col = ((src >> 3) & 1) + (((src >> 5) & 1) << 1);
		/* the bottom half of the translation table is the mirror image of the top */
		if (src & 0x80)
		{
			col = 3 - col;
			xor1 = 0xa8;
		}

		/* decode the opcodes */
		decrypted[A] = (src & ~0xa8) | (convtable[2*row][col] ^ xor1);

		/* decode the data */
		rom[A] = (src & ~0xa8) | (convtable[2*row+1][col] ^ xor1);

		if (convtable[2*row][col] == 0xff)	/* table incomplete! (for development) */
			decrypted[A] = 0x00;
		if (convtable[2*row+1][col] == 0xff)	/* table incomplete! (for development) */
			rom[A] = 0xee;
	}

	/* this is a kludge to catch anyone who has code that crosses the encrypted/ */
	/* decrypted boundary. ssanchan does it */
	if (length > 0x8000)
	{
		int bytes = 0x4000; //MIN(length - 0x8000, 0x4000);
		memcpy(&decrypted[0x8000], &rom[0x8000], bytes);
	}
}

void flicky_decode(void)
{
	static const UINT8 convtable[32][4] =
	{
		/*       opcode                   data                     address      */
		/*  A    B    C    D         A    B    C    D                           */
		{ 0x08,0x88,0x00,0x80 }, { 0xa0,0x80,0xa8,0x88 },	/* ...0...0...0...0 */
		{ 0x80,0x00,0xa0,0x20 }, { 0x88,0x80,0x08,0x00 },	/* ...0...0...0...1 */
		{ 0xa0,0x80,0xa8,0x88 }, { 0x28,0x08,0x20,0x00 },	/* ...0...0...1...0 */
		{ 0x28,0x08,0x20,0x00 }, { 0xa0,0x80,0xa8,0x88 },	/* ...0...0...1...1 */
		{ 0x08,0x88,0x00,0x80 }, { 0x80,0x00,0xa0,0x20 },	/* ...0...1...0...0 */
		{ 0x80,0x00,0xa0,0x20 }, { 0x88,0x80,0x08,0x00 },	/* ...0...1...0...1 */
		{ 0x28,0x08,0x20,0x00 }, { 0x28,0x08,0x20,0x00 },	/* ...0...1...1...0 */
		{ 0x28,0x08,0x20,0x00 }, { 0x88,0x80,0x08,0x00 },	/* ...0...1...1...1 */
		{ 0x08,0x88,0x00,0x80 }, { 0xa8,0x88,0x28,0x08 },	/* ...1...0...0...0 */
		{ 0xa8,0x88,0x28,0x08 }, { 0x80,0x00,0xa0,0x20 },	/* ...1...0...0...1 */
		{ 0x28,0x08,0x20,0x00 }, { 0x88,0x80,0x08,0x00 },	/* ...1...0...1...0 */
		{ 0xa8,0x88,0x28,0x08 }, { 0x88,0x80,0x08,0x00 },	/* ...1...0...1...1 */
		{ 0x08,0x88,0x00,0x80 }, { 0x80,0x00,0xa0,0x20 },	/* ...1...1...0...0 */
		{ 0xa8,0x88,0x28,0x08 }, { 0x80,0x00,0xa0,0x20 },	/* ...1...1...0...1 */
		{ 0x28,0x08,0x20,0x00 }, { 0x28,0x08,0x20,0x00 },	/* ...1...1...1...0 */
		{ 0x08,0x88,0x00,0x80 }, { 0x88,0x80,0x08,0x00 }	/* ...1...1...1...1 */
	};


	sega_decode(convtable);
}

void regulus_decode(void)
{
	static const UINT8 convtable[32][4] =
	{
		/*       opcode                   data                     address      */
		/*  A    B    C    D         A    B    C    D                           */
		{ 0x28,0x08,0xa8,0x88 }, { 0x88,0x80,0x08,0x00 },	/* ...0...0...0...0 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x28,0xa8,0x08,0x88 },	/* ...0...0...0...1 */
		{ 0x88,0x80,0x08,0x00 }, { 0x88,0x08,0x80,0x00 },	/* ...0...0...1...0 */
		{ 0x88,0x08,0x80,0x00 }, { 0x28,0xa8,0x08,0x88 },	/* ...0...0...1...1 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x88,0x80,0x08,0x00 },	/* ...0...1...0...0 */
		{ 0x88,0x80,0x08,0x00 }, { 0x88,0x80,0x08,0x00 },	/* ...0...1...0...1 */
		{ 0x88,0x08,0x80,0x00 }, { 0x88,0x08,0x80,0x00 },	/* ...0...1...1...0 */
		{ 0xa0,0x80,0xa8,0x88 }, { 0xa0,0x80,0xa8,0x88 },	/* ...0...1...1...1 */
		{ 0x80,0xa0,0x00,0x20 }, { 0x28,0x08,0xa8,0x88 },	/* ...1...0...0...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0x28,0x08,0xa8,0x88 },	/* ...1...0...0...1 */
		{ 0x80,0xa0,0x00,0x20 }, { 0x80,0xa0,0x00,0x20 },	/* ...1...0...1...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0x80,0xa0,0x00,0x20 },	/* ...1...0...1...1 */
		{ 0xa0,0x80,0xa8,0x88 }, { 0x28,0x08,0xa8,0x88 },	/* ...1...1...0...0 */
		{ 0x80,0xa0,0x00,0x20 }, { 0xa0,0x80,0xa8,0x88 },	/* ...1...1...0...1 */
		{ 0xa0,0x80,0xa8,0x88 }, { 0x80,0xa0,0x00,0x20 },	/* ...1...1...1...0 */
		{ 0xa0,0x80,0xa8,0x88 }, { 0xa0,0x80,0xa8,0x88 }	/* ...1...1...1...1 */
	};


	sega_decode(convtable);
}

void seganinj_decode(void)
{
	static const UINT8 convtable[32][4] =
	{
		/*       opcode                   data                     address      */
		/*  A    B    C    D         A    B    C    D                           */
		{ 0x88,0xa8,0x80,0xa0 }, { 0x88,0x08,0x80,0x00 },	/* ...0...0...0...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0xa0,0xa8,0x80,0x88 },	/* ...0...0...0...1 */
		{ 0xa8,0xa0,0x28,0x20 }, { 0xa8,0xa0,0x28,0x20 },	/* ...0...0...1...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0xa0,0xa8,0x80,0x88 },	/* ...0...0...1...1 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x28,0x08,0xa8,0x88 },	/* ...0...1...0...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0x88,0x08,0x80,0x00 },	/* ...0...1...0...1 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x28,0x08,0xa8,0x88 },	/* ...0...1...1...0 */
		{ 0x28,0xa8,0x08,0x88 }, { 0xa8,0xa0,0x28,0x20 },	/* ...0...1...1...1 */
		{ 0x88,0x08,0x80,0x00 }, { 0x88,0xa8,0x80,0xa0 },	/* ...1...0...0...0 */
		{ 0xa0,0xa8,0x80,0x88 }, { 0x28,0xa8,0x08,0x88 },	/* ...1...0...0...1 */
		{ 0xa8,0xa0,0x28,0x20 }, { 0x88,0xa8,0x80,0xa0 },	/* ...1...0...1...0 */
		{ 0xa8,0xa0,0x28,0x20 }, { 0x28,0xa8,0x08,0x88 },	/* ...1...0...1...1 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x88,0xa8,0x80,0xa0 },	/* ...1...1...0...0 */
		{ 0x28,0x08,0xa8,0x88 }, { 0x28,0x08,0xa8,0x88 },	/* ...1...1...0...1 */
		{ 0x88,0xa8,0x80,0xa0 }, { 0x88,0xa8,0x80,0xa0 },	/* ...1...1...1...0 */
		{ 0xa8,0xa0,0x28,0x20 }, { 0x28,0x08,0xa8,0x88 }	/* ...1...1...1...1 */
	};


	sega_decode(convtable);
}

static void CalcPenUsage()
{
	int i, x, y;
	UINT32 Usage;
	unsigned char *dp = NULL;
	
	for (i = 0; i < System1NumTiles; i++) {
		dp = System1Tiles + (i * 64);
		Usage = 0;
		for (y = 0; y < 8; y++) {
			for (x = 0; x < 8; x++) {
				Usage |= 1 << dp[x];					
			}
			
			dp += 8;
		}
		
		System1TilesPenUsage[i] = Usage;
	}
}

static int TilePlaneOffsets[3]  = { 0, 0x20000, 0x40000 };
static int TileXOffsets[8]      = { 0, 1, 2, 3, 4, 5, 6, 7 };
static int TileYOffsets[8]      = { 0, 8, 16, 24, 32, 40, 48, 56 };

static int System1Init(int nZ80Rom1Num, int nZ80Rom1Size, int nZ80Rom2Num, int nZ80Rom2Size, int nTileRomNum, int nTileRomSize, int nSpriteRomNum, int nSpriteRomSize)
{
	int nRet = 0, nLen, i, RomOffset;
	
	System1NumTiles = (nTileRomNum * nTileRomSize) / 24;
	System1SpriteRomSize = nSpriteRomNum * nSpriteRomSize;
	
	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();

	System1TempGfx = (unsigned char*)malloc(nTileRomNum * nTileRomSize);
		
	// Load Z80 #1 Program roms
	RomOffset = 0;
	for (i = 0; i < nZ80Rom1Num; i++) {
		nRet = BurnLoadRom(System1Rom1 + (i * nZ80Rom1Size), i + RomOffset, 1); if (nRet != 0) return 1;
	}
	
	//memcpy(System1FetchData1, System1Rom1, 0x8000);
	//flicky_decode();
	//regulus_decode();
	
	// Load Z80 #2 Program roms
	RomOffset += nZ80Rom1Num;
	for (i = 0; i < nZ80Rom2Num; i++) {
		nRet = BurnLoadRom(System1Rom2 + (i * nZ80Rom2Size), i + RomOffset, 1); if (nRet != 0) return 1;
	}
	
	// Load and decode tiles
	RomOffset += nZ80Rom2Num;
	for (i = 0; i < nTileRomNum; i++) {
		nRet = BurnLoadRom(System1TempGfx + (i * nTileRomSize), i + RomOffset, 1);
	}
	GfxDecode(System1NumTiles, 3, 8, 8, TilePlaneOffsets, TileXOffsets, TileYOffsets, 0x40, System1TempGfx, System1Tiles);
	CalcPenUsage();
	free(System1TempGfx);
	
	// Load Sprite roms
	RomOffset += nTileRomNum;
	for (i = 0; i < nSpriteRomNum; i++) {
		nRet = BurnLoadRom(System1Sprites + (i * nSpriteRomSize), i + RomOffset, 1);
	}
	
	// Setup the Z80 emulation
	ZetInit(2);
	ZetOpen(0);
	ZetMapArea(0x0000, 0x7fff, 0, System1Rom1            );
	ZetMapArea(0x0000, 0x7fff, 2, System1Rom1            );
//	ZetMapArea(0x0000, 0xbfff, 0, System1FetchData1          );
//	ZetMapArea(0x0000, 0xbfff, 2, System1Fetch1, System1FetchData1 );
	ZetMapArea(0x8000, 0xbfff, 0, System1Rom1 + 0x8000   );
	ZetMapArea(0x8000, 0xbfff, 2, System1Rom1 + 0x8000   );
	ZetMapArea(0xc000, 0xcfff, 0, System1Ram1            );
	ZetMapArea(0xc000, 0xcfff, 1, System1Ram1            );
	ZetMapArea(0xc000, 0xcfff, 2, System1Ram1            );
	ZetMapArea(0xd000, 0xd1ff, 0, System1SpriteRam       );
	ZetMapArea(0xd000, 0xd1ff, 1, System1SpriteRam       );
	ZetMapArea(0xd000, 0xd1ff, 2, System1SpriteRam       );
	ZetMapArea(0xd200, 0xd7ff, 0, System1Ram1 + 0x1000   );
	ZetMapArea(0xd200, 0xd7ff, 1, System1Ram1 + 0x1000   );
	ZetMapArea(0xd200, 0xd7ff, 2, System1Ram1 + 0x1000   );
	ZetMapArea(0xd800, 0xddff, 0, System1PaletteRam      );
	ZetMapArea(0xd800, 0xddff, 1, System1PaletteRam      );
	ZetMapArea(0xd800, 0xddff, 2, System1PaletteRam      );
	ZetMapArea(0xde00, 0xdfff, 0, System1deRam           );
	ZetMapArea(0xde00, 0xdfff, 1, System1deRam           );
	ZetMapArea(0xde00, 0xdfff, 2, System1deRam           );
	ZetMapArea(0xe000, 0xe7ff, 0, System1BgRam           );
	ZetMapArea(0xe000, 0xe7ff, 1, System1BgRam           );
	ZetMapArea(0xe000, 0xe7ff, 2, System1BgRam           );
	ZetMapArea(0xe800, 0xeeff, 0, System1VideoRam        );
	ZetMapArea(0xe800, 0xeeff, 1, System1VideoRam        );
	ZetMapArea(0xe800, 0xeeff, 2, System1VideoRam        );
	ZetMapArea(0xef00, 0xefff, 0, System1efRam           );
	ZetMapArea(0xf000, 0xf3ff, 0, System1BgCollisionRam  );
//	ZetMapArea(0xf000, 0xf3ff, 1, System1BgCollisionRam  );
//	ZetMapArea(0xf000, 0xf3ff, 2, System1BgCollisionRam  );
	ZetMapArea(0xf400, 0xf7ff, 0, System1f4Ram           );
	ZetMapArea(0xf400, 0xf7ff, 1, System1f4Ram           );
	ZetMapArea(0xf400, 0xf7ff, 2, System1f4Ram           );
	ZetMapArea(0xf800, 0xfbff, 0, System1SprCollisionRam );
//	ZetMapArea(0xf800, 0xfbff, 1, System1SprCollisionRam );
//	ZetMapArea(0xf800, 0xfbff, 2, System1SprCollisionRam );
	ZetMapArea(0xfc00, 0xffff, 0, System1fcRam           );
	ZetMapArea(0xfc00, 0xffff, 1, System1fcRam           );
	ZetMapArea(0xfc00, 0xffff, 2, System1fcRam           );
	ZetMemEnd();
	ZetSetReadHandler(System1Z80Read1);
	ZetSetWriteHandler(System1Z80Write1);
	ZetSetInHandler(System1Z80PortRead1);
	ZetSetOutHandler(System1Z80PortWrite1);
	ZetClose();
	
	ZetOpen(1);
	ZetMapArea(0x0000, 0x7fff, 0, System1Rom2            );
	ZetMapArea(0x0000, 0x7fff, 2, System1Rom2            );
	ZetMapArea(0x8000, 0x87ff, 0, System1Ram2            );
	ZetMapArea(0x8000, 0x87ff, 1, System1Ram2            );
	ZetMapArea(0x8000, 0x87ff, 2, System1Ram2            );
	ZetSetReadHandler(System1Z80Read2);
	ZetSetWriteHandler(System1Z80Write2);
	ZetSetInHandler(System1Z80PortRead2);
	ZetSetOutHandler(System1Z80PortWrite2);
	ZetMemEnd();
	ZetClose();
	
	SpriteOnScreenMap = (unsigned char*)malloc(256 * 256);
	memset(SpriteOnScreenMap, 255, 256 * 256);

	GenericTilesInit();
	
	// Reset the driver
	System1DoReset();
	
	return 0;
}

static int FlickyInit()
{
	return System1Init(2, 0x4000, 1, 0x2000, 6, 0x2000, 2, 0x4000);
}

static int MyheroInit()
{
	return System1Init(3, 0x4000, 1, 0x2000, 6, 0x2000, 4, 0x4000);
}

static int RegulusInit()
{
	return System1Init(6, 0x2000, 1, 0x2000, 6, 0x2000, 2, 0x4000);
}

static int SeganinjInit()
{
	return System1Init(3, 0x4000, 1, 0x2000, 6, 0x2000, 4, 0x4000);
}

static int NprincesInit()
{
	return System1Init(6, 0x2000, 1, 0x2000, 6, 0x2000, 4, 0x4000);
}

static int StarjackInit()
{
	return System1Init(6, 0x2000, 1, 0x2000, 6, 0x2000, 2, 0x4000);
}

static int UpndownInit()
{
	return System1Init(6, 0x2000, 1, 0x2000, 6, 0x2000, 2, 0x4000);
}

static int WboyInit()
{
	return System1Init(3, 0x4000, 1, 0x2000, 6, 0x2000, 4, 0x4000);
}

static int Wboy2uInit()
{
	return System1Init(6, 0x2000, 1, 0x2000, 6, 0x2000, 4, 0x4000);
}

static int System1Exit()
{
	ZetExit();

	GenericTilesExit();
	
	free(Mem);
	Mem = NULL;
	
	System1SoundLatch = 0;

	System1ScrollX[0] = System1ScrollX[1] = System1ScrollY = 0;
	System1SpriteXOffset = 0;
	BgScrollX = 0;
	BgScrollY = 0;
	System1VideoMode = 0;
	System1FlipScreen = 0;
	
	return 0;
}

/*==============================================================================================
Graphics Rendering
===============================================================================================*/

static void DrawPixel(int x, int y, int SpriteNum, int Colour)
{
	int xr, yr, SpriteOnScreen, dx, dy;
	
	dx = x;
	dy = y;
	if (nScreenWidth == 240) dx -= 8;
	
	if (x < 0 || x > 255  || y < 0 || y > 255) return;
	
	if (SpriteOnScreenMap[(y * 256) + x] != 255) {
		SpriteOnScreen = SpriteOnScreenMap[(y * 256) + x];
		System1SprCollisionRam[SpriteOnScreen + (32 * SpriteNum)] = 0xff;
	}
	
	SpriteOnScreenMap[(y * 256) + x] = SpriteNum;
	
	if (dx >= 0 && dx < nScreenWidth && dy >= 0 && dy < nScreenHeight) {
		unsigned short *pPixel = pTransDraw + (dy * nScreenWidth);
		pPixel[dx] = Colour;
	}
	
	xr = ((x - BgScrollX) & 0xff) / 8;
	yr = ((y - BgScrollY) & 0xff) / 8;
	
	if (System1BgRam[2 * (32 * yr + xr) + 1] & 0x10) {
		System1BgCollisionRam[0x20 + SpriteNum] = 0xff;
	}
}

static void DrawSprite(int Num)
{
	int Src, Bank, Height, sy, Row;
	INT16 Skip;
	unsigned char *SpriteBase;
	unsigned int *SpritePalette;
	
	SpriteBase = System1SpriteRam + (0x10 * Num);
	Src = (SpriteBase[7] << 8) | SpriteBase[6];
	Bank = 0x8000 * (((SpriteBase[3] & 0x80) >> 7) + ((SpriteBase[3] & 0x40) >> 5));
	Bank &= (System1SpriteRomSize - 1);
	Skip = (SpriteBase[5] << 8) | SpriteBase[4];
	
	Height = SpriteBase[1] - SpriteBase[0];
	SpritePalette = System1Palette + (0x10 * Num);
	
	sy = SpriteBase[0] + 1;
	
	for (Row = 0; Row < Height; Row++) {
		int x, y, Src2;
		
		Src = Src2 = Src + Skip;
		x = ((SpriteBase[3] & 0x01) << 8) + SpriteBase[2] + 1;
		y = sy + Row;
		
		x /= 2;
		
		while(1) {
			int Colour1, Colour2, Data;
			
			Data = System1Sprites[Bank + (Src2 & 0x7fff)];
			
			if (Src & 0x8000) {
				Src2--;
				Colour1 = Data & 0x0f;
				Colour2 = Data >> 4;
			} else {
				Src2++;
				Colour1 = Data >> 4;
				Colour2 = Data & 0x0f;
			}
			
			if (Colour1 == 0x0f) break;
			if (Colour1) DrawPixel(x, y, Num, Colour1 + (0x10 * Num));
			x++;
			
			if (Colour2 == 0x0f) break;
			if (Colour2) DrawPixel(x, y, Num, Colour2 + (0x10 * Num));
			x++;
		}
	}
}

static void System1DrawSprites()
{
	int i, SpriteBottomY, SpriteTopY;
	unsigned char *SpriteBase;
	
	memset(SpriteOnScreenMap, 255, 256 * 256);
	
	for (i = 0; i < 32; i++) {
		SpriteBase = System1SpriteRam + (0x10 * i);
		SpriteTopY = SpriteBase[0];
		SpriteBottomY = SpriteBase[1];
		if (SpriteBottomY && (SpriteBottomY - SpriteTopY > 0)) {
			DrawSprite(i);
		}
	}
}

static void System1DrawBgLayer(int PriorityDraw)
{
	int Offs, sx, sy;
	
	BgScrollX = ((System1ScrollX[0] >> 1) + ((System1ScrollX[1] & 1) << 7) + 14) & 0xff;
	BgScrollY = (-System1ScrollY & 0xff);
	
	if (PriorityDraw == -1) {
		for (Offs = 0; Offs < 0x800; Offs += 2) {
			int Code, Colour;
		
			Code = (System1BgRam[Offs + 1] << 8) | System1BgRam[Offs + 0];
			Code = ((Code >> 4) & 0x800) | (Code & 0x7ff);
			Colour = ((Code >> 5) & 0x3f);
			
			sx = (Offs >> 1) % 32;
			sy = (Offs >> 1) / 32;
			
			sx = 8 * sx + BgScrollX;
			sy = 8 * sy + BgScrollY;
			
			if (nScreenWidth == 240) sx -= 8;
			
			Code &= (System1NumTiles - 1);
			
			Render8x8Tile_Clip(pTransDraw, Code, sx      , sy      , Colour, 3, 512 * 2, System1Tiles);
			Render8x8Tile_Clip(pTransDraw, Code, sx - 256, sy      , Colour, 3, 512 * 2, System1Tiles);
			Render8x8Tile_Clip(pTransDraw, Code, sx      , sy - 256, Colour, 3, 512 * 2, System1Tiles);
			Render8x8Tile_Clip(pTransDraw, Code, sx - 256, sy - 256, Colour, 3, 512 * 2, System1Tiles);
		}
	} else {
		PriorityDraw <<= 3;
		
		for (Offs = 0; Offs < 0x800; Offs += 2) {
			if ((System1BgRam[Offs + 1] & 0x08) == PriorityDraw) {
				int Code, Colour;
			
				Code = (System1BgRam[Offs + 1] << 8) | System1BgRam[Offs + 0];
				Code = ((Code >> 4) & 0x800) | (Code & 0x7ff);
				Colour = ((Code >> 5) & 0x3f);
								
				int ColourOffs = 0x40;
				if (Colour >= 0x10 && Colour <= 0x1f) ColourOffs += 0x10;
				if (Colour >= 0x20 && Colour <= 0x2f) ColourOffs += 0x20;
				if (Colour >= 0x30 && Colour <= 0x3f) ColourOffs += 0x30;
		
				sx = (Offs >> 1) % 32;
				sy = (Offs >> 1) / 32;
			
				sx = 8 * sx + BgScrollX;
				sy = 8 * sy + BgScrollY;
				
				if (nScreenWidth == 240) sx -= 8;
				
				Code &= (System1NumTiles - 1);
				
				Render8x8Tile_Mask_Clip(pTransDraw, Code, sx      , sy      , Colour, 3, 0, 512 * 2, System1Tiles);
				Render8x8Tile_Mask_Clip(pTransDraw, Code, sx - 256, sy      , Colour, 3, 0, 512 * 2, System1Tiles);
				Render8x8Tile_Mask_Clip(pTransDraw, Code, sx      , sy - 256, Colour, 3, 0, 512 * 2, System1Tiles);
				Render8x8Tile_Mask_Clip(pTransDraw, Code, sx - 256, sy - 256, Colour, 3, 0, 512 * 2, System1Tiles);
			}
		}
	}
}

static void System1DrawFgLayer(int PriorityDraw)
{
	int Offs, sx, sy;
	
	PriorityDraw <<= 3;
	
	for (Offs = 0; Offs < 0x700; Offs += 2) {
		int Code, Colour;
		
		if ((System1VideoRam[Offs + 1] & 0x08) == PriorityDraw) {
			Code = (System1VideoRam[Offs + 1] << 8) | System1VideoRam[Offs + 0];
			Code = ((Code >> 4) & 0x800) | (Code & 0x7ff);
			Colour = (Code >> 5) & 0x3f;
		
			sx = (Offs >> 1) % 32;
			sy = (Offs >> 1) / 32;
			
			sx *= 8;
			sy *= 8;
			
			if (nScreenWidth == 240) sx -= 8;
		
			Code %= System1NumTiles;
			
			if (System1TilesPenUsage[Code] & ~1) {
				Render8x8Tile_Mask_Clip(pTransDraw, Code, sx, sy, Colour, 3, 0, 512, System1Tiles);
			}
		}
	}
}

static inline unsigned char pal2bit(unsigned char bits)
{
	bits &= 3;
	return (bits << 6) | (bits << 4) | (bits << 2) | bits;
}

static inline unsigned char pal3bit(unsigned char bits)
{
	bits &= 7;
	return (bits << 5) | (bits << 2) | (bits >> 1);
}

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = pal3bit(nColour >> 0);
	g = pal3bit(nColour >> 3);
	b = pal2bit(nColour >> 6);

	return BurnHighCol(r, g, b, 0);
}

static int System1CalcPalette()
{
	for (int i = 0; i < 0x600; i++) {
		System1Palette[i] = CalcCol(System1PaletteRam[i]);
	}

	return 0;
}

static void System1Render()
{
	BurnTransferClear();
	System1CalcPalette();
	System1DrawBgLayer(-1);
	System1DrawFgLayer(0);
	System1DrawBgLayer(0);
	System1DrawSprites();
	System1DrawBgLayer(1);
	System1DrawFgLayer(1);
	BurnTransferCopy(System1Palette);
}


/*==============================================================================================
Frame functions
===============================================================================================*/

int System1Frame()
{
	int nInterleave = 10;
		
	if (System1Reset) System1DoReset();

	System1MakeInputs();
	
	nCyclesTotal[0] = 4000000 / 60;
	nCyclesTotal[1] = 4000000 / 60;
	nCyclesDone[0] = nCyclesDone[1] = 0;
	
	ZetNewFrame();
	
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;
		
		// Run Z80 #1
		nCurrentCPU = 0;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;
		if (i == 9) ZetRaiseIrq(0);
		ZetClose();
		
		// Run Z80 #2
		nCurrentCPU = 1;
		ZetOpen(nCurrentCPU);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesSegment = ZetRun(nCyclesSegment);
		nCyclesDone[nCurrentCPU] += nCyclesSegment;
		if (i == 2 || i == 4 || i == 6 || i == 8) ZetRaiseIrq(0);
		ZetClose();
	}

	if (pBurnDraw) System1Render();

	
	return 0;
}

/*==============================================================================================
Scan Driver
===============================================================================================*/

static int System1Scan(int /*nAction*/,int *pnMin)
{
//	struct BurnArea ba;

	if (pnMin != NULL) {
		*pnMin = 0x029672;
	}
	
	return 0;
}

/*==============================================================================================
Driver defs
===============================================================================================*/

struct BurnDriverD BurnDrvFlicky = {
	"flicky", NULL, NULL, "1984",
	"Flicky (128k Version, System 2, 315-5051)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_MISC_PRE90S,
	NULL, FlickyRomInfo, FlickyRomName, FlickyInputInfo, NULL,
	FlickyInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvFlicks2 = {
	"flicks2", "flicky", NULL, "1984",
	"Flicky (128k Version, System 2, not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, Flicks2RomInfo, Flicks2RomName, FlickyInputInfo, NULL,
	FlickyInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvMyhero = {
	"myhero", NULL, NULL, "1985",
	"My Hero (US, not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_MISC_PRE90S,
	NULL, MyheroRomInfo, MyheroRomName, MyheroInputInfo, NULL,
	MyheroInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvRegulus = {
	"regulus", NULL, NULL, "1983",
	"Regulus (315-5033, New Ver.)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, RegulusRomInfo, RegulusRomName, MyheroInputInfo, NULL,
	RegulusInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 240, 3, 4
};

struct BurnDriverD BurnDrvRegulusu = {
	"regulusu", "regulus", NULL, "1983",
	"Regulus (not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, RegulusuRomInfo, RegulusuRomName, MyheroInputInfo, NULL,
	RegulusInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 240, 3, 4
};

struct BurnDriverD BurnDrvSeganinj = {
	"seganinj", NULL, NULL, "1985",
	"Sega Ninja (315-5102)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_MISC_PRE90S,
	NULL, SeganinjRomInfo, SeganinjRomName, SeganinjInputInfo, NULL,
	SeganinjInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvSeganinu = {
	"seganinu", "seganinj", NULL, "1985",
	"Sega Ninja (not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, SeganinuRomInfo, SeganinuRomName, SeganinjInputInfo, NULL,
	SeganinjInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvNprincsu = {
	"nprincsu", "seganinj", NULL, "1985",
	"Ninja Princess (64k Ver. not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, NprincsuRomInfo, NprincsuRomName, SeganinjInputInfo, NULL,
	NprincesInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvStarjack = {
	"starjack", NULL, NULL, "1983",
	"Star Jacker (Sega)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, StarjackRomInfo, StarjackRomName, MyheroInputInfo, NULL,
	StarjackInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 240, 3, 4
};

struct BurnDriverD BurnDrvStarjacs = {
	"starjacs", "starjack", NULL, "1983",
	"Star Jacker (Stern)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, StarjacsRomInfo, StarjacsRomName, MyheroInputInfo, NULL,
	StarjackInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 240, 3, 4
};

struct BurnDriverD BurnDrvUpndown = {
	"upndown", NULL, NULL, "1983",
	"Up'n Down (315-5030)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	0 | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, UpndownRomInfo, UpndownRomName, UpndownInputInfo, NULL,
	UpndownInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 256, 3, 4
};

struct BurnDriverD BurnDrvUpndownu = {
	"upndownu", "upndown", NULL, "1983",
	"Up'n Down (not encrypted)\0", NULL, "Sega", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE | BDF_ORIENTATION_VERTICAL, 2, HARDWARE_MISC_PRE90S,
	NULL, UpndownuRomInfo, UpndownuRomName, UpndownInputInfo, NULL,
	UpndownInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 224, 256, 3, 4
};

struct BurnDriverD BurnDrvWboy = {
	"wboy", NULL, NULL, "1986",
	"Wonder Boy (set 1, 315-5177)\0", NULL, "Sega (Escape License)", "System 1",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_MISC_PRE90S,
	NULL, WboyRomInfo, WboyRomName, WboyInputInfo, NULL,
	WboyInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvWboy2u = {
	"wboy2u", "wboy", NULL, "1986",
	"Wonder Boy (set 2, not encrypted)\0", NULL, "Sega (Escape License)", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, Wboy2uRomInfo, Wboy2uRomName, WboyInputInfo, NULL,
	Wboy2uInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvWboyu = {
	"wboyu", "wboy", NULL, "1986",
	"Wonder Boy (not encrypted)\0", NULL, "Sega (Escape License)", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, WboyuRomInfo, WboyuRomName, WboyInputInfo, NULL,
	WboyInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};

struct BurnDriverD BurnDrvWbdeluxe = {
	"wbdeluxe", "wboy", NULL, "1986",
	"Wonder Boy Deluxe\0", NULL, "Sega (Escape License)", "System 1",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_MISC_PRE90S,
	NULL, WbdeluxeRomInfo, WbdeluxeRomName, WboyInputInfo, NULL,
	Wboy2uInit, System1Exit, System1Frame, NULL, System1Scan,
	NULL, 256, 224, 4, 3
};
