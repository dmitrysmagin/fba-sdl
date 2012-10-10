#include "tiles_generic.h"
#include "burn_ym2610.h"
#include "tc0110pcr.h"
#include "tc0220ioc.h"
#include "tc0150rod.h"
#include "tc0140syt.h"
#include "tc0100scn.h"
#include "eeprom_93cxx.h"
#include "burn_gun.h"

static unsigned char TaitoZReset = 0;
static int TaitoZAnalogPort0 = 0;
static int TaitoZAnalogPort1 = 0;
static int TaitoZAnalogPort2 = 0;
static int TaitoZAnalogPort3 = 0;

static unsigned char *Mem                = NULL;
static unsigned char *MemEnd             = NULL;
static unsigned char *RamStart           = NULL;
static unsigned char *RamEnd             = NULL;
static unsigned char *TaitoZ68KRom1      = NULL;
static unsigned char *TaitoZ68KRom2      = NULL;
static unsigned char *TaitoZZ80Rom       = NULL;
static unsigned char *YM2610ADPCMAROM    = NULL;
static unsigned char *YM2610ADPCMBROM    = NULL;
static unsigned char *TaitoZ68KRam1      = NULL;
static unsigned char *TaitoZ68KRam2      = NULL;
static unsigned char *TaitoZSharedRam    = NULL;
static unsigned char *TaitoZZ80Ram       = NULL;
static unsigned char *TaitoZSpriteRam    = NULL;
static unsigned char *TaitoZPaletteRam   = NULL;
static unsigned char *TaitoZSpriteMapRom = NULL;
static unsigned char *TaitoZChars        = NULL;
static unsigned char *TaitoZSpritesA     = NULL;
static unsigned char *TaitoZSpritesB     = NULL;
static unsigned char *TaitoZTempRom      = NULL;
static unsigned int  *TaitoZPalette      = NULL;

static int TaitoZNumChars;
static int TaitoZNumSpritesA;
static int TaitoZNumSpritesB;
static int TaitoZCharXSize;
static int TaitoZCharYSize;
static int TaitoZSpriteAXSize;
static int TaitoZSpriteAYSize;
static int TaitoZSpriteBXSize;
static int TaitoZSpriteBYSize;
static int YM2610ADPCMASize;
static int YM2610ADPCMBSize;
static int TaitoZVBlankIRQ;
static int TaitoZFrameInterleave;
static int TaitoZHasZ80;
static int TaitoZHasEEPROM;
static int TaitoZHasTC0110PCR;
static int TaitoZHasTC0220IOC;
static int TaitoZHasTC0140SYT;
static int TaitoZHasTC0100SCN;
static int TaitoZHasTC0150ROD;
static int TaitoZFlipScreenX;

static int Sci;
int OldSteer; // Hack to centre the steering in SCI

static unsigned char TaitoZCpuACtrl;
static unsigned char TaitoZZ80Bank;
static int SciSpriteFrame;
static int TaitoZRoadPalBank;

static int nCyclesDone[3], nCyclesTotal[3];
static int nCyclesSegment;

typedef void (*Render)();
static Render DrawFunction;
static void AquajackDraw();
static void BsharkDraw();
static void ChasehqDraw();
static void ContcircDraw();
static void DblaxleDraw();
static void SciDraw();
static void SpacegunDraw();

typedef void (*MakeInputs)();
static MakeInputs MakeInputsFunction;

static bool bUseAsm68KCoreOldValue = false;

#define A(a, b, c, d) {a, b, (unsigned char*)(c), d}

static struct BurnInputInfo AquajackInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p2 coin"   },

	{"Up"                , BIT_DIGITAL   , TC0220IOCInputPort1 + 0, "p1 up"     },
	{"Down"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 down"   },
	{"Left"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 1, "p1 left"   },
	{"Right"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 2, "p1 right"  },
	{"Jump"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 5, "p1 fire 1" },
	{"Accelerate"        , BIT_DIGITAL   , TC0220IOCInputPort0 + 1, "p1 fire 2" },
	{"Vulcan"            , BIT_DIGITAL   , TC0220IOCInputPort1 + 6, "p1 fire 3" },
	{"Missile"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 4, "p1 fire 4" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Aquajack);

static struct BurnInputInfo BsharkInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 1, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort2 + 0, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 0, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL   , TC0220IOCInputPort2 + 1, "p2 start"  },

	A("Crosshair X"      , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "p1 x-axis" ),
	A("Crosshair Y"      , BIT_ANALOG_REL, &TaitoZAnalogPort1     , "p1 y-axis" ),
	{"Fire 1"            , BIT_DIGITAL   , TC0220IOCInputPort2 + 6, "p1 fire 1" },
	{"Fire 2"            , BIT_DIGITAL   , TC0220IOCInputPort2 + 7, "p1 fire 2" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Bshark);

static struct BurnInputInfo ChasehqInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p2 coin"   },

	A("Steering"         , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "p1 x-axis" ),
	{"Brake"             , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "p1 fire 1" },
	{"Accelerate"        , BIT_DIGITAL   , TC0220IOCInputPort1 + 5, "p1 fire 2" },
	{"Turbo"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 0, "p1 fire 3" },
	{"Gear"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 4, "p1 fire 4" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 1, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Chasehq);

static struct BurnInputInfo ContcircInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p2 coin"   },

	A("Steering"         , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "p1 x-axis" ),
	{"Brake"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 7, "p1 fire 1" },
	{"Accelerate"        , BIT_DIGITAL   , TC0220IOCInputPort0 + 7, "p1 fire 2" },
	{"Gear"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 4, "p1 fire 3" },
	{"Brake 2"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 5, "p1 fire 4" },
	{"Brake 3"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 6, "p1 fire 5" },
	{"Accelerate 2"      , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "p1 fire 6" },
	{"Accelerate 3"      , BIT_DIGITAL   , TC0220IOCInputPort0 + 6, "p1 fire 7" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 2, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Contcirc);

static struct BurnInputInfo EnforceInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p2 coin"   },

	{"Up"                , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "p1 up"     },
	{"Down"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 6, "p1 down"   },
	{"Left"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 7, "p1 left"   },
	{"Right"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 7, "p1 right"  },
	{"Laser"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 0, "p1 fire 1" },
	{"Bomb"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 1, "p1 fire 2" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 2, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Enforce);

static struct BurnInputInfo NightstrInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort2 + 0, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL   , TC0220IOCInputPort2 + 1, "p2 start"  },

	A("Stick X"          , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "p1 x-axis" ),
	A("Stick Y"          , BIT_ANALOG_REL, &TaitoZAnalogPort1     , "p1 y-axis" ),
	{"Fire 1"            , BIT_DIGITAL   , TC0220IOCInputPort2 + 6, "p1 fire 1" },
	{"Fire 2"            , BIT_DIGITAL   , TC0220IOCInputPort2 + 7, "p1 fire 2" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 6, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 7, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Nightstr);

static struct BurnInputInfo SciInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort1 + 3, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p2 coin"   },

	A("Steering"         , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "p1 x-axis" ),
	{"Brake"             , BIT_DIGITAL   , TC0220IOCInputPort0 + 5, "p1 fire 1" },
	{"Accelerate"        , BIT_DIGITAL   , TC0220IOCInputPort1 + 5, "p1 fire 2" },
	{"Fire"              , BIT_DIGITAL   , TC0220IOCInputPort0 + 1, "p1 fire 3" },
	{"Turbo"             , BIT_DIGITAL   , TC0220IOCInputPort1 + 0, "p1 fire 4" },
	{"Gear"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 4, "p1 fire 5" },
	{"Centre"            , BIT_DIGITAL   , TC0220IOCInputPort1 + 2, "p1 fire 6" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Tilt"              , BIT_DIGITAL   , TC0220IOCInputPort1 + 1, "tilt"      },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Sci);

static struct BurnInputInfo SpacegunInputList[] =
{
	{"Coin 1"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 3, "p1 coin"   },
	{"Start 1"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 6, "p1 start"  },
	{"Coin 2"            , BIT_DIGITAL   , TC0220IOCInputPort0 + 2, "p2 coin"   },
	{"Start 2"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 7, "p2 start"  },

	A("P1 Gun X"         , BIT_ANALOG_REL, &TaitoZAnalogPort0     , "mouse x-axis" ),
	A("P1 Gun Y"         , BIT_ANALOG_REL, &TaitoZAnalogPort1     , "mouse y-axis" ),
	{"P1 Fire 1"         , BIT_DIGITAL   , TC0220IOCInputPort2 + 0, "mouse button 1" },
	{"P1 Fire 2"         , BIT_DIGITAL   , TC0220IOCInputPort2 + 2, "mouse button 2" },
	{"P1 Fire 3"         , BIT_DIGITAL   , TC0220IOCInputPort0 + 0, "p1 fire 1" },
	
	A("P2 Gun X"         , BIT_ANALOG_REL, &TaitoZAnalogPort2     , "p2 x-axis" ),
	A("P2 Gun Y"         , BIT_ANALOG_REL, &TaitoZAnalogPort3     , "p2 y-axis" ),
	{"P2 Fire 1"         , BIT_DIGITAL   , TC0220IOCInputPort2 + 1, "p2 fire 1" },
	{"P2 Fire 2"         , BIT_DIGITAL   , TC0220IOCInputPort2 + 3, "p2 fire 2" },
	{"P2 Fire 3"         , BIT_DIGITAL   , TC0220IOCInputPort0 + 1, "p2 fire 3" },
	
	{"Reset"             , BIT_DIGITAL   , &TaitoZReset           , "reset"     },
	{"Service"           , BIT_DIGITAL   , TC0220IOCInputPort0 + 4, "service"   },
	{"Dip 1"             , BIT_DIPSWITCH , TC0220IOCDip + 0       , "dip"       },
	{"Dip 2"             , BIT_DIPSWITCH , TC0220IOCDip + 1       , "dip"       },
};

STDINPUTINFO(Spacegun);

#undef A

static void AquajackMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xff;
	TC0220IOCInput[1] = 0xff;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] -= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] -= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort1[0]) TC0220IOCInput[1] -= 0x01;
	if (TC0220IOCInputPort1[1]) TC0220IOCInput[1] -= 0x02;
	if (TC0220IOCInputPort1[2]) TC0220IOCInput[1] -= 0x04;
	if (TC0220IOCInputPort1[3]) TC0220IOCInput[1] -= 0x08;
	if (TC0220IOCInputPort1[4]) TC0220IOCInput[1] -= 0x10;
	if (TC0220IOCInputPort1[5]) TC0220IOCInput[1] -= 0x20;
	if (TC0220IOCInputPort1[6]) TC0220IOCInput[1] -= 0x40;
	if (TC0220IOCInputPort1[7]) TC0220IOCInput[1] -= 0x80;
}

static void BsharkMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xff;
	TC0220IOCInput[1] = 0xff;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] -= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] -= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort2[0]) TC0220IOCInput[2] -= 0x01;
	if (TC0220IOCInputPort2[1]) TC0220IOCInput[2] -= 0x02;
	if (TC0220IOCInputPort2[2]) TC0220IOCInput[2] -= 0x04;
	if (TC0220IOCInputPort2[3]) TC0220IOCInput[2] -= 0x08;
	if (TC0220IOCInputPort2[4]) TC0220IOCInput[2] -= 0x10;
	if (TC0220IOCInputPort2[5]) TC0220IOCInput[2] -= 0x20;
	if (TC0220IOCInputPort2[6]) TC0220IOCInput[2] -= 0x40;
	if (TC0220IOCInputPort2[7]) TC0220IOCInput[2] -= 0x80;
}

static void ChasehqMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xf3;
	TC0220IOCInput[1] = 0xef;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] |= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] |= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort1[0]) TC0220IOCInput[1] -= 0x01;
	if (TC0220IOCInputPort1[1]) TC0220IOCInput[1] -= 0x02;
	if (TC0220IOCInputPort1[2]) TC0220IOCInput[1] -= 0x04;
	if (TC0220IOCInputPort1[3]) TC0220IOCInput[1] -= 0x08;
	if (TC0220IOCInputPort1[4]) TC0220IOCInput[1] |= 0x10;
	if (TC0220IOCInputPort1[5]) TC0220IOCInput[1] -= 0x20;
	if (TC0220IOCInputPort1[6]) TC0220IOCInput[1] -= 0x40;
	if (TC0220IOCInputPort1[7]) TC0220IOCInput[1] -= 0x80;
}

static void ContcircMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0x13;
	TC0220IOCInput[1] = 0x0f;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] |= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] |= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] |= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] |= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] |= 0x80;
	
	if (TC0220IOCInputPort1[0]) TC0220IOCInput[1] -= 0x01;
	if (TC0220IOCInputPort1[1]) TC0220IOCInput[1] -= 0x02;
	if (TC0220IOCInputPort1[2]) TC0220IOCInput[1] -= 0x04;
	if (TC0220IOCInputPort1[3]) TC0220IOCInput[1] -= 0x08;
	if (TC0220IOCInputPort1[4]) TC0220IOCInput[1] |= 0x10;
	if (TC0220IOCInputPort1[5]) TC0220IOCInput[1] |= 0x20;
	if (TC0220IOCInputPort1[6]) TC0220IOCInput[1] |= 0x40;
	if (TC0220IOCInputPort1[7]) TC0220IOCInput[1] |= 0x80;
}

static void EnforceMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xf3;
	TC0220IOCInput[1] = 0xff;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] |= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] |= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort1[0]) TC0220IOCInput[1] -= 0x01;
	if (TC0220IOCInputPort1[1]) TC0220IOCInput[1] -= 0x02;
	if (TC0220IOCInputPort1[2]) TC0220IOCInput[1] -= 0x04;
	if (TC0220IOCInputPort1[3]) TC0220IOCInput[1] -= 0x08;
	if (TC0220IOCInputPort1[4]) TC0220IOCInput[1] -= 0x10;
	if (TC0220IOCInputPort1[5]) TC0220IOCInput[1] -= 0x20;
	if (TC0220IOCInputPort1[6]) TC0220IOCInput[1] -= 0x40;
	if (TC0220IOCInputPort1[7]) TC0220IOCInput[1] -= 0x80;
}

static void NightstrMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xff;
	TC0220IOCInput[1] = 0xff;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] -= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] -= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort2[0]) TC0220IOCInput[2] -= 0x01;
	if (TC0220IOCInputPort2[1]) TC0220IOCInput[2] -= 0x02;
	if (TC0220IOCInputPort2[2]) TC0220IOCInput[2] -= 0x04;
	if (TC0220IOCInputPort2[3]) TC0220IOCInput[2] -= 0x08;
	if (TC0220IOCInputPort2[4]) TC0220IOCInput[2] -= 0x10;
	if (TC0220IOCInputPort2[5]) TC0220IOCInput[2] -= 0x20;
	if (TC0220IOCInputPort2[6]) TC0220IOCInput[2] -= 0x40;
	if (TC0220IOCInputPort2[7]) TC0220IOCInput[2] -= 0x80;
}

static void SciMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xff;
	TC0220IOCInput[1] = 0xef;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] -= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] -= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort1[0]) TC0220IOCInput[1] -= 0x01;
	if (TC0220IOCInputPort1[1]) TC0220IOCInput[1] -= 0x02;
	if (TC0220IOCInputPort1[2]) TC0220IOCInput[1] -= 0x04;
	if (TC0220IOCInputPort1[3]) TC0220IOCInput[1] -= 0x08;
	if (TC0220IOCInputPort1[4]) TC0220IOCInput[1] |= 0x10;
	if (TC0220IOCInputPort1[5]) TC0220IOCInput[1] -= 0x20;
	if (TC0220IOCInputPort1[6]) TC0220IOCInput[1] -= 0x40;
	if (TC0220IOCInputPort1[7]) TC0220IOCInput[1] -= 0x80;
}

static void SpacegunMakeInputs()
{
	// Reset Inputs
	TC0220IOCInput[0] = 0xff;
	TC0220IOCInput[1] = 0xff;
	TC0220IOCInput[2] = 0xff;

	if (TC0220IOCInputPort0[0]) TC0220IOCInput[0] -= 0x01;
	if (TC0220IOCInputPort0[1]) TC0220IOCInput[0] -= 0x02;
	if (TC0220IOCInputPort0[2]) TC0220IOCInput[0] -= 0x04;
	if (TC0220IOCInputPort0[3]) TC0220IOCInput[0] -= 0x08;
	if (TC0220IOCInputPort0[4]) TC0220IOCInput[0] -= 0x10;
	if (TC0220IOCInputPort0[5]) TC0220IOCInput[0] -= 0x20;
	if (TC0220IOCInputPort0[6]) TC0220IOCInput[0] -= 0x40;
	if (TC0220IOCInputPort0[7]) TC0220IOCInput[0] -= 0x80;
	
	if (TC0220IOCInputPort2[0]) TC0220IOCInput[2] -= 0x01;
	if (TC0220IOCInputPort2[1]) TC0220IOCInput[2] -= 0x02;
	if (TC0220IOCInputPort2[2]) TC0220IOCInput[2] -= 0x04;
	if (TC0220IOCInputPort2[3]) TC0220IOCInput[2] -= 0x08;
	if (TC0220IOCInputPort2[4]) TC0220IOCInput[2] -= 0x10;
	if (TC0220IOCInputPort2[5]) TC0220IOCInput[2] -= 0x20;
	if (TC0220IOCInputPort2[6]) TC0220IOCInput[2] -= 0x40;
	if (TC0220IOCInputPort2[7]) TC0220IOCInput[2] -= 0x80;
	
	BurnGunMakeInputs(0, (short)TaitoZAnalogPort0, (short)TaitoZAnalogPort1);
	BurnGunMakeInputs(1, (short)TaitoZAnalogPort2, (short)TaitoZAnalogPort3);
}

static struct BurnDIPInfo AquajackDIPList[]=
{
	// Default Values
	{0x0e, 0xff, 0xff, 0x7f, NULL                             },
	{0x0f, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0e, 0x01, 0x80, 0x80, "Cockpit"                        },
	{0x0e, 0x01, 0x80, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0e, 0x01, 0x20, 0x20, "Off"                            },
	{0x0e, 0x01, 0x20, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0e, 0x01, 0x10, 0x00, "Off"                            },
	{0x0e, 0x01, 0x10, 0x10, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0e, 0x01, 0x0c, 0x00, "4 Coins 1 Credit"               },
	{0x0e, 0x01, 0x0c, 0x08, "3 Coins 1 Credit"               },
	{0x0e, 0x01, 0x0c, 0x04, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0x0c, 0x0c, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0e, 0x01, 0x03, 0x03, "1 Coin 2 Credits"               },
	{0x0e, 0x01, 0x03, 0x01, "1 Coin 3 Credits"               },
	{0x0e, 0x01, 0x03, 0x02, "1 Coin 4 Credits"               },
	{0x0e, 0x01, 0x03, 0x00, "1 Coin 6 Credits"               },	
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0f, 0x01, 0xc0, 0x40, "Easy"                           },
	{0x0f, 0x01, 0xc0, 0xc0, "Normal"                         },
	{0x0f, 0x01, 0xc0, 0x80, "Hard"                           },
	{0x0f, 0x01, 0xc0, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                     },
	{0x0f, 0x01, 0x30, 0x00, "30000"                          },
	{0x0f, 0x01, 0x30, 0x30, "50000"                          },
	{0x0f, 0x01, 0x30, 0x10, "80000"                          },
	{0x0f, 0x01, 0x30, 0x20, "100000"                         },
	
	{0   , 0xfe, 0   , 4   , "Lives"                          },
	{0x0f, 0x01, 0x0c, 0x08, "1"                              },
	{0x0f, 0x01, 0x0c, 0x04, "2"                              },
	{0x0f, 0x01, 0x0c, 0x0c, "3"                              },
	{0x0f, 0x01, 0x0c, 0x00, "5"                              },
};

STDDIPINFO(Aquajack);

static struct BurnDIPInfo AquajckjDIPList[]=
{
	// Default Values
	{0x0e, 0xff, 0xff, 0x7f, NULL                             },
	{0x0f, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0e, 0x01, 0x80, 0x80, "Cockpit"                        },
	{0x0e, 0x01, 0x80, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0e, 0x01, 0x20, 0x20, "Off"                            },
	{0x0e, 0x01, 0x20, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0e, 0x01, 0x10, 0x00, "Off"                            },
	{0x0e, 0x01, 0x10, 0x10, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0e, 0x01, 0x0c, 0x08, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0x0c, 0x0c, "1 Coin  1 Credit"               },
	{0x0e, 0x01, 0x0c, 0x00, "2 Coins 3 Credits"              },
	{0x0e, 0x01, 0x0c, 0x04, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0e, 0x01, 0x03, 0x02, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0x03, 0x03, "1 Coin  1 Credit"               },
	{0x0e, 0x01, 0x03, 0x00, "2 Coins 3 Credits"              },
	{0x0e, 0x01, 0x03, 0x01, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0f, 0x01, 0xc0, 0x40, "Easy"                           },
	{0x0f, 0x01, 0xc0, 0xc0, "Normal"                         },
	{0x0f, 0x01, 0xc0, 0x80, "Hard"                           },
	{0x0f, 0x01, 0xc0, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Bonus Life"                     },
	{0x0f, 0x01, 0x30, 0x00, "30000"                          },
	{0x0f, 0x01, 0x30, 0x30, "50000"                          },
	{0x0f, 0x01, 0x30, 0x10, "80000"                          },
	{0x0f, 0x01, 0x30, 0x20, "100000"                         },
	
	{0   , 0xfe, 0   , 4   , "Lives"                          },
	{0x0f, 0x01, 0x0c, 0x08, "1"                              },
	{0x0f, 0x01, 0x0c, 0x04, "2"                              },
	{0x0f, 0x01, 0x0c, 0x0c, "3"                              },
	{0x0f, 0x01, 0x0c, 0x00, "5"                              },
};

STDDIPINFO(Aquajckj);

static struct BurnDIPInfo BsharkDIPList[]=
{
	// Default Values
	{0x0b, 0xff, 0xff, 0xff, NULL                             },
	{0x0c, 0xff, 0xff, 0xf7, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Mirror Screen"                  },
	{0x0b, 0x01, 0x01, 0x01, "Off"                            },
	{0x0b, 0x01, 0x01, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0b, 0x01, 0x04, 0x04, "Off"                            },
	{0x0b, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0b, 0x01, 0x08, 0x00, "Off"                            },
	{0x0b, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coinage"                        },
	{0x0b, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Price to Continue"              },
	{0x0b, 0x01, 0xc0, 0x00, "3 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x80, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0xc0, 0xc0, "Same as Start"                  },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0c, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0c, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0c, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0c, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Speed of Sight"                 },
	{0x0c, 0x01, 0x0c, 0x0c, "Slow"                           },
	{0x0c, 0x01, 0x0c, 0x08, "Medium"                         },
	{0x0c, 0x01, 0x0c, 0x04, "Fast"                           },
	{0x0c, 0x01, 0x0c, 0x00, "Fastest"                        },
};

STDDIPINFO(Bshark);

static struct BurnDIPInfo BsharkjDIPList[]=
{
	// Default Values
	{0x0b, 0xff, 0xff, 0xff, NULL                             },
	{0x0c, 0xff, 0xff, 0xf7, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Mirror Screen"                  },
	{0x0b, 0x01, 0x01, 0x01, "Off"                            },
	{0x0b, 0x01, 0x01, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0b, 0x01, 0x04, 0x04, "Off"                            },
	{0x0b, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0b, 0x01, 0x08, 0x00, "Off"                            },
	{0x0b, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0b, 0x01, 0x30, 0x10, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0x30, 0x00, "2 Coins 3 Credits"              },
	{0x0b, 0x01, 0x30, 0x20, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0b, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0xc0, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x00, "2 Coins 3 Credits"              },
	{0x0b, 0x01, 0xc0, 0x80, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0c, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0c, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0c, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0c, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Speed of Sight"                 },
	{0x0c, 0x01, 0x0c, 0x0c, "Slow"                           },
	{0x0c, 0x01, 0x0c, 0x08, "Medium"                         },
	{0x0c, 0x01, 0x0c, 0x04, "Fast"                           },
	{0x0c, 0x01, 0x0c, 0x00, "Fastest"                        },
};

STDDIPINFO(Bsharkj);

static struct BurnDIPInfo ChasehqDIPList[]=
{
	// Default Values
	{0x0b, 0xff, 0xff, 0xff, NULL                             },
	{0x0c, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 4   , "Cabinet"                        },
	{0x0b, 0x01, 0x03, 0x03, "Upright / Steering Lock"        },
	{0x0b, 0x01, 0x03, 0x02, "Upright / No Steering Lock"     },
	{0x0b, 0x01, 0x03, 0x01, "Full Throttle Convert, Cockpit" },
	{0x0b, 0x01, 0x03, 0x00, "Full Throttle Convert, Deluxe"  },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0b, 0x01, 0x04, 0x04, "Off"                            },
	{0x0b, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0b, 0x01, 0x08, 0x00, "Off"                            },
	{0x0b, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0b, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0b, 0x01, 0xc0, 0xc0, "1 Coin 2 Credits"               },
	{0x0b, 0x01, 0xc0, 0x80, "1 Coin 3 Credits"               },
	{0x0b, 0x01, 0xc0, 0x40, "1 Coin 4 Credits"               },
	{0x0b, 0x01, 0xc0, 0x00, "1 Coin 6 Credits"               },	
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0c, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0c, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0c, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0c, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Timer Setting"                  },
	{0x0c, 0x01, 0x0c, 0x08, "70 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x04, "65 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x0c, "60 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x00, "55 Seconds"                     },
	
	{0   , 0xfe, 0   , 2   , "Turbos Stocked"                 },
	{0x0c, 0x01, 0x10, 0x10, "3"                              },
	{0x0c, 0x01, 0x10, 0x00, "5"                              },
	
	{0   , 0xfe, 0   , 2   , "Discounted Continue Play"       },
	{0x0c, 0x01, 0x20, 0x20, "Off"                            },
	{0x0c, 0x01, 0x20, 0x00, "On"                             },

	{0   , 0xfe, 0   , 2   , "Damage Cleared at Continue"     },
	{0x0c, 0x01, 0x40, 0x00, "Off"                            },
	{0x0c, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                 },
	{0x0c, 0x01, 0x80, 0x00, "Off"                            },
	{0x0c, 0x01, 0x80, 0x80, "On"                             },
};

STDDIPINFO(Chasehq);

static struct BurnDIPInfo ChasehqjDIPList[]=
{
	// Default Values
	{0x0b, 0xff, 0xff, 0xff, NULL                             },
	{0x0c, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 4   , "Cabinet"                        },
	{0x0b, 0x01, 0x03, 0x03, "Upright / Steering Lock"        },
	{0x0b, 0x01, 0x03, 0x02, "Upright / No Steering Lock"     },
	{0x0b, 0x01, 0x03, 0x01, "Full Throttle Convert, Cockpit" },
	{0x0b, 0x01, 0x03, 0x00, "Full Throttle Convert, Deluxe"  },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0b, 0x01, 0x04, 0x04, "Off"                            },
	{0x0b, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0b, 0x01, 0x08, 0x00, "Off"                            },
	{0x0b, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0b, 0x01, 0x30, 0x10, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0x30, 0x00, "2 Coins 3 Credits"              },
	{0x0b, 0x01, 0x30, 0x20, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0b, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0xc0, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x00, "2 Coins 3 Credits"              },
	{0x0b, 0x01, 0xc0, 0x80, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0c, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0c, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0c, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0c, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Timer Setting"                  },
	{0x0c, 0x01, 0x0c, 0x08, "70 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x04, "65 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x0c, "60 Seconds"                     },
	{0x0c, 0x01, 0x0c, 0x00, "55 Seconds"                     },
	
	{0   , 0xfe, 0   , 2   , "Turbos Stocked"                 },
	{0x0c, 0x01, 0x10, 0x10, "3"                              },
	{0x0c, 0x01, 0x10, 0x00, "5"                              },
	
	{0   , 0xfe, 0   , 2   , "Discounted Continue Play"       },
	{0x0c, 0x01, 0x20, 0x20, "Off"                            },
	{0x0c, 0x01, 0x20, 0x00, "On"                             },

	{0   , 0xfe, 0   , 2   , "Damage Cleared at Continue"     },
	{0x0c, 0x01, 0x40, 0x00, "Off"                            },
	{0x0c, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                 },
	{0x0c, 0x01, 0x80, 0x00, "Off"                            },
	{0x0c, 0x01, 0x80, 0x80, "On"                             },
};

STDDIPINFO(Chasehqj);

static struct BurnDIPInfo ContcircDIPList[]=
{
	// Default Values
	{0x0e, 0xff, 0xff, 0xff, NULL                             },
	{0x0f, 0xff, 0xff, 0xdf, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0e, 0x01, 0x01, 0x01, "Upright"                        },
	{0x0e, 0x01, 0x01, 0x00, "Cockpit"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0e, 0x01, 0x04, 0x04, "Off"                            },
	{0x0e, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0e, 0x01, 0x08, 0x00, "Off"                            },
	{0x0e, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0e, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0e, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0e, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0e, 0x01, 0xc0, 0xc0, "1 Coin 2 Credits"               },
	{0x0e, 0x01, 0xc0, 0x80, "1 Coin 3 Credits"               },
	{0x0e, 0x01, 0xc0, 0x40, "1 Coin 4 Credits"               },
	{0x0e, 0x01, 0xc0, 0x00, "1 Coin 6 Credits"               },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Time Difficulty"                },
	{0x0f, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0f, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0f, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0f, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Opponent Difficulty"            },
	{0x0f, 0x01, 0x0c, 0x08, "Easy"                           },
	{0x0f, 0x01, 0x0c, 0x0c, "Normal"                         },
	{0x0f, 0x01, 0x0c, 0x04, "Hard"                           },
	{0x0f, 0x01, 0x0c, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 2   , "Steering Wheel"                 },
	{0x0f, 0x01, 0x10, 0x10, "Free"                           },
	{0x0f, 0x01, 0x10, 0x00, "Locked"                         },
	
	{0   , 0xfe, 0   , 2   , "Enable 3D Alternate Frames"     },
	{0x0f, 0x01, 0x20, 0x00, "Off"                            },
	{0x0f, 0x01, 0x20, 0x20, "On"                             },
};

STDDIPINFO(Contcirc);

static struct BurnDIPInfo ContcrcuDIPList[]=
{
	// Default Values
	{0x0e, 0xff, 0xff, 0xff, NULL                             },
	{0x0f, 0xff, 0xff, 0xdf, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0e, 0x01, 0x01, 0x01, "Upright"                        },
	{0x0e, 0x01, 0x01, 0x00, "Cockpit"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0e, 0x01, 0x04, 0x04, "Off"                            },
	{0x0e, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0e, 0x01, 0x08, 0x00, "Off"                            },
	{0x0e, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0e, 0x01, 0x30, 0x10, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	{0x0e, 0x01, 0x30, 0x00, "2 Coins 3 Credits"              },
	{0x0e, 0x01, 0x30, 0x20, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0e, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0e, 0x01, 0xc0, 0xc0, "1 Coin  1 Credit"               },
	{0x0e, 0x01, 0xc0, 0x00, "2 Coins 3 Credits"              },
	{0x0e, 0x01, 0xc0, 0x80, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Time Difficulty"                },
	{0x0f, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0f, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0f, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0f, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Opponent Difficulty"            },
	{0x0f, 0x01, 0x0c, 0x08, "Easy"                           },
	{0x0f, 0x01, 0x0c, 0x0c, "Normal"                         },
	{0x0f, 0x01, 0x0c, 0x04, "Hard"                           },
	{0x0f, 0x01, 0x0c, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 2   , "Steering Wheel"                 },
	{0x0f, 0x01, 0x10, 0x10, "Free"                           },
	{0x0f, 0x01, 0x10, 0x00, "Locked"                         },
	
	{0   , 0xfe, 0   , 2   , "Enable 3D Alternate Frames"     },
	{0x0f, 0x01, 0x20, 0x00, "Off"                            },
	{0x0f, 0x01, 0x20, 0x20, "On"                             },
};

STDDIPINFO(Contcrcu);

static struct BurnDIPInfo EnforceDIPList[]=
{
	// Default Values
	{0x0c, 0xff, 0xff, 0xff, NULL                             },
	{0x0d, 0xff, 0xff, 0xef, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0c, 0x01, 0x04, 0x04, "Off"                            },
	{0x0c, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0c, 0x01, 0x08, 0x00, "Off"                            },
	{0x0c, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0c, 0x01, 0x30, 0x10, "2 Coins 1 Credit"               },
	{0x0c, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	{0x0c, 0x01, 0x30, 0x00, "2 Coins 3 Credits"              },
	{0x0c, 0x01, 0x30, 0x20, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0c, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0c, 0x01, 0xc0, 0xc0, "1 Coin  1 Credit"               },
	{0x0c, 0x01, 0xc0, 0x00, "2 Coins 3 Credits"              },
	{0x0c, 0x01, 0xc0, 0x80, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 2   , "Background Scenery"             },
	{0x0d, 0x01, 0x10, 0x10, "Crazy Scolling"                 },
	{0x0d, 0x01, 0x10, 0x00, "Normal"                         },
};

STDDIPINFO(Enforce);

static struct BurnDIPInfo NightstrDIPList[]=
{
	// Default Values
	{0x0b, 0xff, 0xff, 0xfe, NULL                             },
	{0x0c, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0b, 0x01, 0x01, 0x01, "Cockpit"                        },
	{0x0b, 0x01, 0x01, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0b, 0x01, 0x04, 0x04, "Off"                            },
	{0x0b, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0b, 0x01, 0x08, 0x00, "Off"                            },
	{0x0b, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coinage"                        },
	{0x0b, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Price to Continue"              },
	{0x0b, 0x01, 0xc0, 0x00, "3 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0b, 0x01, 0xc0, 0x80, "1 Coin  1 Credit"               },
	{0x0b, 0x01, 0xc0, 0xc0, "Same as Start"                  },	
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0c, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0c, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0c, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0c, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Bonus Shields"                  },
	{0x0c, 0x01, 0x0c, 0x08, "3"                              },
	{0x0c, 0x01, 0x0c, 0x04, "2"                              },
	{0x0c, 0x01, 0x0c, 0x0c, "1"                              },
	{0x0c, 0x01, 0x0c, 0x00, "None"                           },
	
	{0   , 0xfe, 0   , 4   , "Shields"                        },
	{0x0c, 0x01, 0x30, 0x00, "3"                              },
	{0x0c, 0x01, 0x30, 0x10, "4"                              },
	{0x0c, 0x01, 0x30, 0x30, "5"                              },
	{0x0c, 0x01, 0x30, 0x20, "6"                              },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                 },
	{0x0c, 0x01, 0x40, 0x00, "Off"                            },
	{0x0c, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Trigger Turbo"                  },
	{0x0c, 0x01, 0x80, 0x80, "7 shots / seconds"              },
	{0x0c, 0x01, 0x80, 0x00, "10 shots / seconds"             },
};

STDDIPINFO(Nightstr);

static struct BurnDIPInfo SciDIPList[]=
{
	// Default Values
	{0x0d, 0xff, 0xff, 0xfe, NULL                             },
	{0x0e, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0d, 0x01, 0x01, 0x01, "Cockpit"                        },
	{0x0d, 0x01, 0x01, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0d, 0x01, 0x04, 0x04, "Off"                            },
	{0x0d, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0d, 0x01, 0x08, 0x00, "Off"                            },
	{0x0d, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0d, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0d, 0x01, 0xc0, 0xc0, "1 Coin 2 Credits"               },
	{0x0d, 0x01, 0xc0, 0x80, "1 Coin 3 Credits"               },
	{0x0d, 0x01, 0xc0, 0x40, "1 Coin 4 Credits"               },
	{0x0d, 0x01, 0xc0, 0x00, "1 Coin 6 Credits"               },	
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0e, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0e, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0e, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0e, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Timer Setting"                  },
	{0x0e, 0x01, 0x0c, 0x08, "70 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x04, "65 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x0c, "60 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x00, "55 Seconds"                     },
	
	{0   , 0xfe, 0   , 2   , "Turbos Stocked"                 },
	{0x0e, 0x01, 0x10, 0x10, "3"                              },
	{0x0e, 0x01, 0x10, 0x00, "5"                              },
	
	{0   , 0xfe, 0   , 2   , "Steering Radius"                },
	{0x0e, 0x01, 0x20, 0x00, "270 Degree"                     },
	{0x0e, 0x01, 0x20, 0x20, "360 Degree"                     },

	{0   , 0xfe, 0   , 2   , "Damage Cleared at Continue"     },
	{0x0e, 0x01, 0x40, 0x00, "Off"                            },
	{0x0e, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Siren Volume"                   },
	{0x0e, 0x01, 0x80, 0x80, "Normal"                         },
	{0x0e, 0x01, 0x80, 0x00, "Low"                            },
};

STDDIPINFO(Sci);

static struct BurnDIPInfo ScijDIPList[]=
{
	// Default Values
	{0x0d, 0xff, 0xff, 0xfe, NULL                             },
	{0x0e, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0d, 0x01, 0x01, 0x01, "Cockpit"                        },
	{0x0d, 0x01, 0x01, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0d, 0x01, 0x04, 0x04, "Off"                            },
	{0x0d, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0d, 0x01, 0x08, 0x00, "Off"                            },
	{0x0d, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x0d, 0x01, 0x30, 0x10, "2 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	{0x0d, 0x01, 0x30, 0x00, "2 Coins 3 Credits"              },
	{0x0d, 0x01, 0x30, 0x20, "1 Coin  2 Credits"              },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x0d, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0d, 0x01, 0xc0, 0xc0, "1 Coin  1 Credit"               },
	{0x0d, 0x01, 0xc0, 0x00, "2 Coins 3 Credits"              },
	{0x0d, 0x01, 0xc0, 0x80, "1 Coin  2 Credits"              },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0e, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0e, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0e, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0e, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Timer Setting"                  },
	{0x0e, 0x01, 0x0c, 0x08, "70 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x04, "65 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x0c, "60 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x00, "55 Seconds"                     },
	
	{0   , 0xfe, 0   , 2   , "Turbos Stocked"                 },
	{0x0e, 0x01, 0x10, 0x10, "3"                              },
	{0x0e, 0x01, 0x10, 0x00, "5"                              },
	
	{0   , 0xfe, 0   , 2   , "Steering Radius"                },
	{0x0e, 0x01, 0x20, 0x00, "270 Degree"                     },
	{0x0e, 0x01, 0x20, 0x20, "360 Degree"                     },

	{0   , 0xfe, 0   , 2   , "Damage Cleared at Continue"     },
	{0x0e, 0x01, 0x40, 0x00, "Off"                            },
	{0x0e, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Siren Volume"                   },
	{0x0e, 0x01, 0x80, 0x80, "Normal"                         },
	{0x0e, 0x01, 0x80, 0x00, "Low"                            },
};

STDDIPINFO(Scij);

static struct BurnDIPInfo SciuDIPList[]=
{
	// Default Values
	{0x0d, 0xff, 0xff, 0xfe, NULL                             },
	{0x0e, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Cabinet"                        },
	{0x0d, 0x01, 0x01, 0x01, "Cockpit"                        },
	{0x0d, 0x01, 0x01, 0x00, "Upright"                        },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x0d, 0x01, 0x04, 0x04, "Off"                            },
	{0x0d, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x0d, 0x01, 0x08, 0x00, "Off"                            },
	{0x0d, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coinage"                        },
	{0x0d, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x0d, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Price to Continue"              },
	{0x0d, 0x01, 0xc0, 0x00, "3 Coins 1 Credit"               },
	{0x0d, 0x01, 0xc0, 0x40, "2 Coins 1 Credit"               },
	{0x0d, 0x01, 0xc0, 0x80, "1 Coin  1 Credit"               },
	{0x0d, 0x01, 0xc0, 0xc0, "Same as Start"                  },
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x0e, 0x01, 0x03, 0x02, "Easy"                           },
	{0x0e, 0x01, 0x03, 0x03, "Normal"                         },
	{0x0e, 0x01, 0x03, 0x01, "Hard"                           },
	{0x0e, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 4   , "Timer Setting"                  },
	{0x0e, 0x01, 0x0c, 0x08, "70 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x04, "65 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x0c, "60 Seconds"                     },
	{0x0e, 0x01, 0x0c, 0x00, "55 Seconds"                     },
	
	{0   , 0xfe, 0   , 2   , "Turbos Stocked"                 },
	{0x0e, 0x01, 0x10, 0x10, "3"                              },
	{0x0e, 0x01, 0x10, 0x00, "5"                              },
	
	{0   , 0xfe, 0   , 2   , "Steering Radius"                },
	{0x0e, 0x01, 0x20, 0x00, "270 Degree"                     },
	{0x0e, 0x01, 0x20, 0x20, "360 Degree"                     },

	{0   , 0xfe, 0   , 2   , "Damage Cleared at Continue"     },
	{0x0e, 0x01, 0x40, 0x00, "Off"                            },
	{0x0e, 0x01, 0x40, 0x40, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Siren Volume"                   },
	{0x0e, 0x01, 0x80, 0x80, "Normal"                         },
	{0x0e, 0x01, 0x80, 0x00, "Low"                            },
};

STDDIPINFO(Sciu);

static struct BurnDIPInfo SpacegunDIPList[]=
{
	// Default Values
	{0x10, 0xff, 0xff, 0xff, NULL                             },
	{0x11, 0xff, 0xff, 0xff, NULL                             },
	
	// Dip 1
	{0   , 0xfe, 0   , 2   , "Always have gunsight power up"  },
	{0x10, 0x01, 0x02, 0x02, "Off"                            },
	{0x10, 0x01, 0x02, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Service Mode"                   },
	{0x10, 0x01, 0x04, 0x04, "Off"                            },
	{0x10, 0x01, 0x04, 0x00, "On"                             },
	
	{0   , 0xfe, 0   , 2   , "Demo Sounds"                    },
	{0x10, 0x01, 0x08, 0x00, "Off"                            },
	{0x10, 0x01, 0x08, 0x08, "On"                             },
	
	{0   , 0xfe, 0   , 4   , "Coin A"                         },
	{0x10, 0x01, 0x30, 0x00, "4 Coins 1 Credit"               },
	{0x10, 0x01, 0x30, 0x10, "3 Coins 1 Credit"               },
	{0x10, 0x01, 0x30, 0x20, "2 Coins 1 Credit"               },
	{0x10, 0x01, 0x30, 0x30, "1 Coin  1 Credit"               },
	
	{0   , 0xfe, 0   , 4   , "Coin B"                         },
	{0x10, 0x01, 0xc0, 0xc0, "1 Coin 2 Credits"               },
	{0x10, 0x01, 0xc0, 0x80, "1 Coin 3 Credits"               },
	{0x10, 0x01, 0xc0, 0x40, "1 Coin 4 Credits"               },
	{0x10, 0x01, 0xc0, 0x00, "1 Coin 6 Credits"               },	
	
	// Dip 2
	{0   , 0xfe, 0   , 4   , "Difficulty"                     },
	{0x11, 0x01, 0x03, 0x02, "Easy"                           },
	{0x11, 0x01, 0x03, 0x03, "Normal"                         },
	{0x11, 0x01, 0x03, 0x01, "Hard"                           },
	{0x11, 0x01, 0x03, 0x00, "Hardest"                        },
	
	{0   , 0xfe, 0   , 2   , "Allow Continue"                 },
	{0x11, 0x01, 0x40, 0x00, "Off"                            },
	{0x11, 0x01, 0x40, 0x40, "On"                             },

	{0   , 0xfe, 0   , 2   , "Disable Pedal"                  },
	{0x11, 0x01, 0x80, 0x80, "Off"                            },
	{0x11, 0x01, 0x80, 0x00, "On"                             },	
};

STDDIPINFO(Spacegun);

static struct BurnRomInfo AquajackRomDesc[] = {
	{ "b77-22.rom",    0x20000, 0x67400dde, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "34.17",         0x20000, 0xcd4d0969, BRF_ESS | BRF_PRG },			//  1
	
	{ "b77-24.rom",    0x20000, 0x95e643ed, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "b77-23.rom",    0x20000, 0x395a7d1c, BRF_ESS | BRF_PRG },			//  3
	
	{ "b77-20.rom",    0x10000, 0x84ba54b7, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b77-05.rom",    0x80000, 0x7238f0ff, BRF_GRA },				//  5	Chars
	
	{ "b77-04.rom",    0x80000, 0xbed0be6c, BRF_GRA },				//  6	Sprites A
	{ "b77-03.rom",    0x80000, 0x9a3030a7, BRF_GRA },				//  7
	{ "b77-02.rom",    0x80000, 0xdaea0d2e, BRF_GRA },				//  8
	{ "b77-01.rom",    0x80000, 0xcdab000d, BRF_GRA },				//  9
	
	{ "b77-07.rom",    0x80000, 0x7db1fc5e, BRF_GRA },				//  10	Road Lines
	
	{ "b77-06.rom",    0x80000, 0xce2aed00, BRF_GRA },				//  11	Spritemap
	
	{ "b77-09.rom",    0x80000, 0x948e5ad9, BRF_SND },				//  12	ADPCM Samples
	
	{ "b77-08.rom",    0x80000, 0x119b9485, BRF_SND },				//  13	Delta-T Samples
	
	{ "b77-17.bin",    0x00100, 0xfbf81f30, BRF_OPT },				//  14	Unused ROMs
	{ "b77-18.bin",    0x00100, 0x7b7d8ff4, BRF_OPT },				//  15
};

STD_ROM_PICK(Aquajack);
STD_ROM_FN(Aquajack);

static struct BurnRomInfo AquajckjRomDesc[] = {
	{ "b77-22.rom",    0x20000, 0x67400dde, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b77-21.rom",    0x20000, 0x23436845, BRF_ESS | BRF_PRG },			//  1
	
	{ "b77-24.rom",    0x20000, 0x95e643ed, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "b77-23.rom",    0x20000, 0x395a7d1c, BRF_ESS | BRF_PRG },			//  3
	
	{ "b77-20.rom",    0x10000, 0x84ba54b7, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b77-05.rom",    0x80000, 0x7238f0ff, BRF_GRA },				//  5	Chars
	
	{ "b77-04.rom",    0x80000, 0xbed0be6c, BRF_GRA },				//  6	Sprites A
	{ "b77-03.rom",    0x80000, 0x9a3030a7, BRF_GRA },				//  7
	{ "b77-02.rom",    0x80000, 0xdaea0d2e, BRF_GRA },				//  8
	{ "b77-01.rom",    0x80000, 0xcdab000d, BRF_GRA },				//  9
	
	{ "b77-07.rom",    0x80000, 0x7db1fc5e, BRF_GRA },				//  10	Road Lines
	
	{ "b77-06.rom",    0x80000, 0xce2aed00, BRF_GRA },				//  11	Spritemap
	
	{ "b77-09.rom",    0x80000, 0x948e5ad9, BRF_SND },				//  12	ADPCM Samples
	
	{ "b77-08.rom",    0x80000, 0x119b9485, BRF_SND },				//  13	Delta-T Samples
	
	{ "b77-17.bin",    0x00100, 0xfbf81f30, BRF_OPT },				//  14	Unused ROMs
	{ "b77-18.bin",    0x00100, 0x7b7d8ff4, BRF_OPT },				//  15
};

STD_ROM_PICK(Aquajckj);
STD_ROM_FN(Aquajckj);

static struct BurnRomInfo BsharkRomDesc[] = {
	{ "c34_71.98",     0x20000, 0xdf1fa629, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c34_69.75",     0x20000, 0xa54c137a, BRF_ESS | BRF_PRG },			//  1
	{ "c34_70.97",     0x20000, 0xd77d81e2, BRF_ESS | BRF_PRG },			//  2
	{ "bshark67.bin",  0x20000, 0x39307c74, BRF_ESS | BRF_PRG },			//  3
	
	{ "c34_74.128",    0x20000, 0x6869fa99, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c34_72.112",    0x20000, 0xc09c0f91, BRF_ESS | BRF_PRG },			//  5
	{ "c34_75.129",    0x20000, 0x6ba65542, BRF_ESS | BRF_PRG },			//  6
	{ "c34_73.113",    0x20000, 0xf2fe62b5, BRF_ESS | BRF_PRG },			//  7
	
	{ "c34_05.3",      0x80000, 0x596b83da, BRF_GRA },				//  8	Chars
	
	{ "c34_04.17",     0x80000, 0x2446b0da, BRF_GRA },				//  9	Sprites A
	{ "c34_03.16",     0x80000, 0xa18eab78, BRF_GRA },				//  10
	{ "c34_02.15",     0x80000, 0x8488ba10, BRF_GRA },				//  11
	{ "c34_01.14",     0x80000, 0x3ebe8c63, BRF_GRA },				//  12
	
	{ "c34_07.42",     0x80000, 0xedb07808, BRF_GRA },				//  13	Road Lines
	
	{ "c34_06.12",     0x80000, 0xd200b6eb, BRF_GRA },				//  14	Spritemap
	
	{ "c34_08.127",    0x80000, 0x89a30450, BRF_SND },				//  15	ADPCM Samples
	
	{ "c34_09.126",    0x80000, 0x39d12b50, BRF_SND },				//  16	Delta_T Samples
	
	{ "c34_18.22",     0x10000, 0x7245a6f6, BRF_OPT },				//  17	Unused ROMs
	{ "c34_19.72",     0x00100, 0x2ee9c404, BRF_OPT },				//  18
	{ "c34_20.89",     0x00100, 0xfbf81f30, BRF_OPT },				//  19
	{ "c34_21.7",      0x00400, 0x10728853, BRF_OPT },				//  20
	{ "c34_22.8",      0x00400, 0x643e8bfc, BRF_OPT },				//  21
};

STD_ROM_PICK(Bshark);
STD_ROM_FN(Bshark);

static struct BurnRomInfo BsharkjRomDesc[] = {
	{ "c34_71.98",     0x20000, 0xdf1fa629, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c34_69.75",     0x20000, 0xa54c137a, BRF_ESS | BRF_PRG },			//  1
	{ "c34_70.97",     0x20000, 0xd77d81e2, BRF_ESS | BRF_PRG },			//  2
	{ "c34_66.74",     0x20000, 0xa0392dce, BRF_ESS | BRF_PRG },			//  3
	
	{ "c34_74.128",    0x20000, 0x6869fa99, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c34_72.112",    0x20000, 0xc09c0f91, BRF_ESS | BRF_PRG },			//  5
	{ "c34_75.129",    0x20000, 0x6ba65542, BRF_ESS | BRF_PRG },			//  6
	{ "c34_73.113",    0x20000, 0xf2fe62b5, BRF_ESS | BRF_PRG },			//  7
	
	{ "c34_05.3",      0x80000, 0x596b83da, BRF_GRA },				//  8	Chars
	
	{ "c34_04.17",     0x80000, 0x2446b0da, BRF_GRA },				//  9	Sprites A
	{ "c34_03.16",     0x80000, 0xa18eab78, BRF_GRA },				//  10
	{ "c34_02.15",     0x80000, 0x8488ba10, BRF_GRA },				//  11
	{ "c34_01.14",     0x80000, 0x3ebe8c63, BRF_GRA },				//  12
	
	{ "c34_07.42",     0x80000, 0xedb07808, BRF_GRA },				//  13	Road Lines
	
	{ "c34_06.12",     0x80000, 0xd200b6eb, BRF_GRA },				//  14	Spritemap
	
	{ "c34_08.127",    0x80000, 0x89a30450, BRF_SND },				//  15	ADPCM Samples
	
	{ "c34_09.126",    0x80000, 0x39d12b50, BRF_SND },				//  16	Delta_T Samples
	
	{ "c34_18.22",     0x10000, 0x7245a6f6, BRF_OPT },				//  17	Unused ROMs
	{ "c34_19.72",     0x00100, 0x2ee9c404, BRF_OPT },				//  18
	{ "c34_20.89",     0x00100, 0xfbf81f30, BRF_OPT },				//  19
	{ "c34_21.7",      0x00400, 0x10728853, BRF_OPT },				//  20
	{ "c34_22.8",      0x00400, 0x643e8bfc, BRF_OPT },				//  21
};

STD_ROM_PICK(Bsharkj);
STD_ROM_FN(Bsharkj);

static struct BurnRomInfo ChasehqRomDesc[] = {
	{ "b52-130.36",    0x20000, 0x4e7beb46, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b52-136.29",    0x20000, 0x2f414df0, BRF_ESS | BRF_PRG },			//  1
	{ "b52-131.37",    0x20000, 0xaa945d83, BRF_ESS | BRF_PRG },			//  2
	{ "b52-129.30",    0x20000, 0x0eaebc08, BRF_ESS | BRF_PRG },			//  3
	
	{ "b52-132.39",    0x10000, 0xa2f54789, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "b52-133.55",    0x10000, 0x12232f95, BRF_ESS | BRF_PRG },			//  5
	
	{ "b52-137.51",    0x10000, 0x37abb74a, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "b52-29.27",     0x80000, 0x8366d27c, BRF_GRA },				//  7	Chars
	
	{ "b52-34.5",      0x80000, 0x7d8dce36, BRF_GRA },				//  8	Sprites A
	{ "b52-35.7",      0x80000, 0x78eeec0d, BRF_GRA },				//  9
	{ "b52-36.9",      0x80000, 0x61e89e91, BRF_GRA },				//  10
	{ "b52-37.11",     0x80000, 0xf02e47b9, BRF_GRA },				//  11
	
	{ "b52-30.4",      0x80000, 0x1b8cc647, BRF_GRA },				//  12	Sprites B
	{ "b52-31.6",      0x80000, 0xf1998e20, BRF_GRA },				//  13
	{ "b52-32.8",      0x80000, 0x8620780c, BRF_GRA },				//  14
	{ "b52-33.10",     0x80000, 0xe6f4b8c4, BRF_GRA },				//  15
	
	{ "b52-28.4",      0x80000, 0x963bc82b, BRF_GRA },				//  16	Road Lines
	
	{ "b52-38.34",     0x80000, 0x5b5bf7f6, BRF_GRA },				//  17	Spritemap
	
	{ "b52-115.71",    0x80000, 0x4e117e93, BRF_SND },				//  18	ADPCM Samples
	{ "b52-114.72",    0x80000, 0x3a73d6b1, BRF_SND },				//  19
	{ "b52-113.73",    0x80000, 0x2c6a3a05, BRF_SND },				//  20
	
	{ "b52-116.70",    0x80000, 0xad46983c, BRF_SND },				//  21	Delta-T Samples
	
	{ "b52-01.7",      0x00100, 0x89719d17, BRF_OPT },				//  22	Unused ROMs
	{ "b52-03.135",    0x00400, 0xa3f8490d, BRF_OPT },				//  23
	{ "b52-06.24",     0x00100, 0xfbf81f30, BRF_OPT },				//  24
	{ "b52-18.93",     0x00100, 0x60bdaf1a, BRF_OPT },				//  25
	{ "b52-18a",       0x00100, 0x6271be0d, BRF_OPT },				//  26
	{ "b52-49.68",     0x02000, 0x60dd2ed1, BRF_OPT },				//  27
	{ "b52-50.66",     0x10000, 0xc189781c, BRF_OPT },				//  28
	{ "b52-51.65",     0x10000, 0x30cc1f79, BRF_OPT },				//  29
	{ "b52-126.136",   0x00400, 0xfa2f840e, BRF_OPT },				//  30
	{ "b52-127.156",   0x00400, 0x77682a4f, BRF_OPT },				//  31
	
	{ "pal20l8b-b52-17.ic18",   0x00144, 0x4851316d, BRF_OPT },			//  32 	PLDs
	{ "pal20l8b-b52-17.ic16",   0x00144, 0x4851316d, BRF_OPT },			//  33
	{ "pal20l8b-b52-17.ic53",   0x00144, 0x4851316d, BRF_OPT },			//  34
	{ "pal20l8b-b52-17.ic55",   0x00144, 0x4851316d, BRF_OPT },			//  35
	{ "pal16l8b-b52-19.ic33",   0x00104, 0x3ba292dc, BRF_OPT },			//  36
	{ "pal16l8b-b52-20.ic35",   0x00104, 0xbd39ad73, BRF_OPT },			//  37
	{ "pal16l8b-b52-21.ic51",   0x00104, 0x2fe76aa4, BRF_OPT },			//  38
	{ "pal20l8b-b52-25.ic123",  0x00144, 0x372b632d, BRF_OPT },			//  39
	{ "pal20l8b-b52-26.ic15",   0x00144, 0xd94f2bc2, BRF_OPT },			//  40
	{ "pal20l8b-b52-26.ic18",   0x00144, 0xd94f2bc2, BRF_OPT },			//  41
	{ "pal20l8b-b52-26.ic52",   0x00144, 0xd94f2bc2, BRF_OPT },			//  42
	{ "pal20l8b-b52-26.ic54",   0x00144, 0xd94f2bc2, BRF_OPT },			//  43
	{ "pal20l8b-b52-27.ic64",   0x00144, 0x61c2ab26, BRF_OPT },			//  44
	{ "pal20l8b-b52-118.ic20",  0x00144, 0x9c5fe4af, BRF_OPT },			//  45
	{ "pal20l8b-b52-119.ic21",  0x00144, 0x8b8e2106, BRF_OPT },			//  46
	{ "pal16l8b-b52-120.ic56",  0x00104, 0x3e7effa0, BRF_OPT },			//  47
	{ "pal20l8b-b52-121.ic57",  0x00144, 0x7056fd1d, BRF_OPT },			//  48
	{ "pal16l8b-b52-122.ic124", 0x00104, 0x04c0fb04, BRF_OPT },			//  49
	{ "pal16l8b-b52-123.ic125", 0x00104, 0x3865d1c8, BRF_OPT },			//  50
	{ "pal16l8b-b52-124.ic180", 0x00104, 0x00000000, BRF_OPT | BRF_NODUMP },	//  51
	{ "pal16l8b-b52-125.ic112", 0x00104, 0x7628c557, BRF_OPT },			//  52
};

STD_ROM_PICK(Chasehq);
STD_ROM_FN(Chasehq);

static struct BurnRomInfo ChasehqjRomDesc[] = {
	{ "b52-140.36",    0x20000, 0xc1298a4b, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b52-139.29",    0x20000, 0x997f732e, BRF_ESS | BRF_PRG },			//  1
	{ "b52-131.37",    0x20000, 0xaa945d83, BRF_ESS | BRF_PRG },			//  2
	{ "b52-129.30",    0x20000, 0x0eaebc08, BRF_ESS | BRF_PRG },			//  3
	
	{ "b52-132.39",    0x10000, 0xa2f54789, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "b52-133.55",    0x10000, 0x12232f95, BRF_ESS | BRF_PRG },			//  5
	
	{ "b52-134.51",    0x10000, 0x91faac7f, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "b52-29.27",     0x80000, 0x8366d27c, BRF_GRA },				//  7	Chars
	
	{ "b52-34.5",      0x80000, 0x7d8dce36, BRF_GRA },				//  8	Sprites A
	{ "b52-35.7",      0x80000, 0x78eeec0d, BRF_GRA },				//  9
	{ "b52-36.9",      0x80000, 0x61e89e91, BRF_GRA },				//  10
	{ "b52-37.11",     0x80000, 0xf02e47b9, BRF_GRA },				//  11
	
	{ "b52-30.4",      0x80000, 0x1b8cc647, BRF_GRA },				//  12	Sprites B
	{ "b52-31.6",      0x80000, 0xf1998e20, BRF_GRA },				//  13
	{ "b52-32.8",      0x80000, 0x8620780c, BRF_GRA },				//  14
	{ "b52-33.10",     0x80000, 0xe6f4b8c4, BRF_GRA },				//  15
	
	{ "b52-28.4",      0x80000, 0x963bc82b, BRF_GRA },				//  16	Road Lines
	
	{ "b52-38.34",     0x80000, 0x5b5bf7f6, BRF_GRA },				//  17	Spritemap
	
	{ "b52-41.71",     0x80000, 0x8204880c, BRF_SND },				//  18	ADPCM Samples
	{ "b52-40.72",     0x80000, 0xf0551055, BRF_SND },				//  19
	{ "b52-39.73",     0x80000, 0xac9cbbd3, BRF_SND },				//  20
	
	{ "b52-42.70",     0x80000, 0x6e617df1, BRF_SND },				//  21	Delta-T Samples
	
	{ "b52-01.7",      0x00100, 0x89719d17, BRF_OPT },				//  22	Unused ROMs
	{ "b52-03.135",    0x00400, 0xa3f8490d, BRF_OPT },				//  23
	{ "b52-06.24",     0x00100, 0xfbf81f30, BRF_OPT },				//  24
	{ "b52-18.93",     0x00100, 0x60bdaf1a, BRF_OPT },				//  25
	{ "b52-18a",       0x00100, 0x6271be0d, BRF_OPT },				//  26
	{ "b52-49.68",     0x02000, 0x60dd2ed1, BRF_OPT },				//  27
	{ "b52-50.66",     0x10000, 0xc189781c, BRF_OPT },				//  28
	{ "b52-51.65",     0x10000, 0x30cc1f79, BRF_OPT },				//  29
	{ "b52-126.136",   0x00400, 0xfa2f840e, BRF_OPT },				//  30
	{ "b52-127.156",   0x00400, 0x77682a4f, BRF_OPT },				//  31
	
	{ "pal20l8b-b52-17.ic18",   0x00144, 0x4851316d, BRF_OPT },			//  32 	PLDs
	{ "pal20l8b-b52-17.ic16",   0x00144, 0x4851316d, BRF_OPT },			//  33
	{ "pal20l8b-b52-17.ic53",   0x00144, 0x4851316d, BRF_OPT },			//  34
	{ "pal20l8b-b52-17.ic55",   0x00144, 0x4851316d, BRF_OPT },			//  35
	{ "pal16l8b-b52-19.ic33",   0x00104, 0x3ba292dc, BRF_OPT },			//  36
	{ "pal16l8b-b52-20.ic35",   0x00104, 0xbd39ad73, BRF_OPT },			//  37
	{ "pal16l8b-b52-21.ic51",   0x00104, 0x2fe76aa4, BRF_OPT },			//  38
	{ "pal20l8b-b52-25.ic123",  0x00144, 0x372b632d, BRF_OPT },			//  39
	{ "pal20l8b-b52-26.ic15",   0x00144, 0xd94f2bc2, BRF_OPT },			//  40
	{ "pal20l8b-b52-26.ic18",   0x00144, 0xd94f2bc2, BRF_OPT },			//  41
	{ "pal20l8b-b52-26.ic52",   0x00144, 0xd94f2bc2, BRF_OPT },			//  42
	{ "pal20l8b-b52-26.ic54",   0x00144, 0xd94f2bc2, BRF_OPT },			//  43
	{ "pal20l8b-b52-27.ic64",   0x00144, 0x61c2ab26, BRF_OPT },			//  44
	{ "pal20l8b-b52-118.ic20",  0x00144, 0x9c5fe4af, BRF_OPT },			//  45
	{ "pal20l8b-b52-119.ic21",  0x00144, 0x8b8e2106, BRF_OPT },			//  46
	{ "pal16l8b-b52-120.ic56",  0x00104, 0x3e7effa0, BRF_OPT },			//  47
	{ "pal20l8b-b52-121.ic57",  0x00144, 0x7056fd1d, BRF_OPT },			//  48
	{ "pal16l8b-b52-122.ic124", 0x00104, 0x04c0fb04, BRF_OPT },			//  49
	{ "pal16l8b-b52-123.ic125", 0x00104, 0x3865d1c8, BRF_OPT },			//  50
	{ "pal16l8b-b52-124.ic180", 0x00104, 0x00000000, BRF_OPT | BRF_NODUMP },	//  51
	{ "pal16l8b-b52-125.ic112", 0x00104, 0x7628c557, BRF_OPT },			//  52
};

STD_ROM_PICK(Chasehqj);
STD_ROM_FN(Chasehqj);

static struct BurnRomInfo ContcircRomDesc[] = {
	{ "ic25",          0x20000, 0xf5c92e42, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "ic26",          0x20000, 0xe7c1d1fa, BRF_ESS | BRF_PRG },			//  1
	
	{ "ic35",          0x20000, 0x16522f2d, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "cc_36.bin",     0x20000, 0xa1732ea5, BRF_ESS | BRF_PRG },			//  3
	
	{ "b33-30.11",     0x10000, 0xd8746234, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b33-02.57",     0x80000, 0xf6fb3ba2, BRF_GRA },				//  5	Chars
	
	{ "b33-06",        0x80000, 0x2cb40599, BRF_GRA },				//  6	Sprites A
	{ "b33-05",        0x80000, 0xbddf9eea, BRF_GRA },				//  7
	{ "b33-04",        0x80000, 0x8df866a2, BRF_GRA },				//  8
	{ "b33-03",        0x80000, 0x4f6c36d9, BRF_GRA },				//  9
	
	{ "b33-01.3",      0x80000, 0xf11f2be8, BRF_GRA },				//  10	Road Lines
	
	{ "b33-07.64",     0x80000, 0x151e1f52, BRF_GRA },				//  11	Spritemap
	
	{ "b33-09.18",     0x80000, 0x1e6724b5, BRF_SND },				//  12	ADPCM Samples
	{ "b33-10.17",     0x80000, 0xe9ce03ab, BRF_SND },				//  13
	
	{ "b33-08.19",     0x80000, 0xcaa1c4c8, BRF_SND },				//  14	Delta-T Samples
	
	{ "b14-30.97",     0x10000, 0xdccb0c7f, BRF_OPT },				//  15	Unused ROMs
	{ "b14-31.50",     0x02000, 0x5c6b013d, BRF_OPT },				//  16
	{ "b33-17.16",     0x00100, 0x7b7d8ff4, BRF_OPT },				//  17
	{ "b33-18.17",     0x00100, 0xfbf81f30, BRF_OPT },				//  18
};

STD_ROM_PICK(Contcirc);
STD_ROM_FN(Contcirc);

static struct BurnRomInfo ContcrcuRomDesc[] = {
	{ "ic25",          0x20000, 0xf5c92e42, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "ic26",          0x20000, 0xe7c1d1fa, BRF_ESS | BRF_PRG },			//  1
	
	{ "ic35",          0x20000, 0x16522f2d, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "ic36",          0x20000, 0xd6741e33, BRF_ESS | BRF_PRG },			//  3
	
	{ "b33-30.11",     0x10000, 0xd8746234, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b33-02.57",     0x80000, 0xf6fb3ba2, BRF_GRA },				//  5	Chars
	
	{ "b33-06",        0x80000, 0x2cb40599, BRF_GRA },				//  6	Sprites A
	{ "b33-05",        0x80000, 0xbddf9eea, BRF_GRA },				//  7
	{ "b33-04",        0x80000, 0x8df866a2, BRF_GRA },				//  8
	{ "b33-03",        0x80000, 0x4f6c36d9, BRF_GRA },				//  9
	
	{ "b33-01.3",      0x80000, 0xf11f2be8, BRF_GRA },				//  10	Road Lines
	
	{ "b33-07.64",     0x80000, 0x151e1f52, BRF_GRA },				//  11	Spritemap
	
	{ "b33-09.18",     0x80000, 0x1e6724b5, BRF_SND },				//  12	ADPCM Samples
	{ "b33-10.17",     0x80000, 0xe9ce03ab, BRF_SND },				//  13
	
	{ "b33-08.19",     0x80000, 0xcaa1c4c8, BRF_SND },				//  14	Delta-T Samples
	
	{ "b14-30.97",     0x10000, 0xdccb0c7f, BRF_OPT },				//  15	Unused ROMs
	{ "b14-31.50",     0x02000, 0x5c6b013d, BRF_OPT },				//  16
	{ "b33-17.16",     0x00100, 0x7b7d8ff4, BRF_OPT },				//  17
	{ "b33-18.17",     0x00100, 0xfbf81f30, BRF_OPT },				//  18
};

STD_ROM_PICK(Contcrcu);
STD_ROM_FN(Contcrcu);

static struct BurnRomInfo ContcruaRomDesc[] = {
	{ "b33-34.ic25",   0x20000, 0xe1e016c1, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b33-33.ic26",   0x20000, 0xf539d44b, BRF_ESS | BRF_PRG },			//  1
	
	{ "21-2.ic35",     0x20000, 0x2723f9e3, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "31-1.ic36",     0x20000, 0x438431f7, BRF_ESS | BRF_PRG },			//  3
	
	{ "b33-30.11",     0x10000, 0xd8746234, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b33-02.57",     0x80000, 0xf6fb3ba2, BRF_GRA },				//  5	Chars
	
	{ "b33-06",        0x80000, 0x2cb40599, BRF_GRA },				//  6	Sprites A
	{ "b33-05",        0x80000, 0xbddf9eea, BRF_GRA },				//  7
	{ "b33-04",        0x80000, 0x8df866a2, BRF_GRA },				//  8
	{ "b33-03",        0x80000, 0x4f6c36d9, BRF_GRA },				//  9
	
	{ "b33-01.3",      0x80000, 0xf11f2be8, BRF_GRA },				//  10	Road Lines
	
	{ "b33-07.64",     0x80000, 0x151e1f52, BRF_GRA },				//  11	Spritemap
	
	{ "b33-09.18",     0x80000, 0x1e6724b5, BRF_SND },				//  12	ADPCM Samples
	{ "b33-10.17",     0x80000, 0xe9ce03ab, BRF_SND },				//  13
	
	{ "b33-08.19",     0x80000, 0xcaa1c4c8, BRF_SND },				//  14	Delta-T Samples
	
	{ "b14-30.97",     0x10000, 0xdccb0c7f, BRF_OPT },				//  15	Unused ROMs
	{ "b14-31.50",     0x02000, 0x5c6b013d, BRF_OPT },				//  16
	{ "b33-17.16",     0x00100, 0x7b7d8ff4, BRF_OPT },				//  17
	{ "b33-18.17",     0x00100, 0xfbf81f30, BRF_OPT },				//  18
};

STD_ROM_PICK(Contcrua);
STD_ROM_FN(Contcrua);

static struct BurnRomInfo EnforceRomDesc[] = {
	{ "b58-27.27",     0x20000, 0xa1aa0191, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b58-19.19",     0x20000, 0x40f43da3, BRF_ESS | BRF_PRG },			//  1
	
	{ "b58-26.26",     0x20000, 0xe823c85c, BRF_ESS | BRF_PRG },			//  2	68000 #2 Program Code
	{ "b58-18.18",     0x20000, 0x65328a3e, BRF_ESS | BRF_PRG },			//  3
	
	{ "b58-32.41",     0x10000, 0xf3fd8eca, BRF_ESS | BRF_PRG },			//  4	Z80 Program
	
	{ "b58-09.13",     0x80000, 0x9ffd5b31, BRF_GRA },				//  5	Chars
	
	{ "b58-04.7",      0x80000, 0x9482f08d, BRF_GRA },				//  6	Sprites A
	{ "b58-03.6",      0x80000, 0x158bc440, BRF_GRA },				//  7
	{ "b58-02.2",      0x80000, 0x6a6e307c, BRF_GRA },				//  8
	{ "b58-01.1",      0x80000, 0x01e9f0a8, BRF_GRA },				//  9
	
	{ "b58-06.116",    0x80000, 0xb3495d70, BRF_GRA },				//  10	Road Lines
	
	{ "b58-05.71",     0x80000, 0xd1f4991b, BRF_GRA },				//  11	Spritemap
	
	{ "b58-07.11",     0x80000, 0xeeb5ba08, BRF_SND },				//  12	ADPCM Samples
	{ "b58-08.12",     0x80000, 0x049243cf, BRF_SND },				//  13
	
	{ "b58-10.14",     0x80000, 0xedce0cc1, BRF_SND },				//  14	Delta-T Samples
	
	{ "b58-26a.104",   0x10000, 0xdccb0c7f, BRF_OPT },				//  15	Unused ROMs
	{ "b58-27.56",     0x02000, 0x5c6b013d, BRF_OPT },				//  16
	{ "b58-23.52",     0x00100, 0x7b7d8ff4, BRF_OPT },				//  17
	{ "b58-24.51",     0x00100, 0xfbf81f30, BRF_OPT },				//  18
	{ "b58-25.75",     0x00100, 0xde547342, BRF_OPT },				//  19
};

STD_ROM_PICK(Enforce);
STD_ROM_FN(Enforce);

static struct BurnRomInfo NightstrRomDesc[] = {
	{ "b91-45.bin",    0x20000, 0x7ad63421, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "b91-44.bin",    0x20000, 0x4bc30adf, BRF_ESS | BRF_PRG },			//  1
	{ "b91-43.bin",    0x20000, 0x3e6f727a, BRF_ESS | BRF_PRG },			//  2
	{ "b91-46.bin",    0x20000, 0xe870be95, BRF_ESS | BRF_PRG },			//  3
	
	{ "b91-39.bin",    0x20000, 0x725b23ae, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "b91-40.bin",    0x20000, 0x81fb364d, BRF_ESS | BRF_PRG },			//  5
	
	{ "b91-41.bin",    0x20000, 0x2694bb42, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "b91-11.bin",    0x80000, 0xfff8ce31, BRF_GRA },				//  7	Chars
	
	{ "b91-04.bin",    0x80000, 0x8ca1970d, BRF_GRA },				//  8	Sprites A
	{ "b91-03.bin",    0x80000, 0xcd5fed39, BRF_GRA },				//  9
	{ "b91-02.bin",    0x80000, 0x457c64b8, BRF_GRA },				//  10
	{ "b91-01.bin",    0x80000, 0x3731d94f, BRF_GRA },				//  11
	
	{ "b91-08.bin",    0x80000, 0x66f35c34, BRF_GRA },				//  12	Sprites B
	{ "b91-07.bin",    0x80000, 0x4d8ec6cf, BRF_GRA },				//  13
	{ "b91-06.bin",    0x80000, 0xa34dc839, BRF_GRA },				//  14
	{ "b91-05.bin",    0x80000, 0x5e72ac90, BRF_GRA },				//  15
	
	{ "b91-10.bin",    0x80000, 0x1d8f05b4, BRF_GRA },				//  16	Road Lines
	
	{ "b91-09.bin",    0x80000, 0x5f247ca2, BRF_GRA },				//  17	Spritemap
	
	{ "b91-13.bin",    0x80000, 0x8c7bf0f5, BRF_SND },				//  18	ADPCM Samples
	{ "b91-12.bin",    0x80000, 0xda77c7af, BRF_SND },				//  19
	
	{ "b91-14.bin",    0x80000, 0x6bc314d3, BRF_SND },				//  20	Delta-T Samples
	
	{ "b91-26.bin",    0x00400, 0x77682a4f, BRF_OPT },				//  21	Unused ROMs
	{ "b91-27.bin",    0x00400, 0xa3f8490d, BRF_OPT },				//  22
	{ "b91-28.bin",    0x00400, 0xfa2f840e, BRF_OPT },				//  23
	{ "b91-29.bin",    0x02000, 0xad685be8, BRF_OPT },				//  24
	{ "b91-30.bin",    0x10000, 0x30cc1f79, BRF_OPT },				//  25
	{ "b91-31.bin",    0x10000, 0xc189781c, BRF_OPT },				//  26
	{ "b91-32.bin",    0x00100, 0xfbf81f30, BRF_OPT },				//  27
	{ "b91-33.bin",    0x00100, 0x89719d17, BRF_OPT },				//  28
};

STD_ROM_PICK(Nightstr);
STD_ROM_FN(Nightstr);

static struct BurnRomInfo SciRomDesc[] = {
	{ "c09-37.43",     0x20000, 0x0fecea17, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c09-38.40",     0x20000, 0xe46ebd9b, BRF_ESS | BRF_PRG },			//  1
	{ "c09-42.38",     0x20000, 0xf4404f87, BRF_ESS | BRF_PRG },			//  2
	{ "c09-39.41",     0x20000, 0xde87bcb9, BRF_ESS | BRF_PRG },			//  3
	
	{ "c09-33.6",      0x10000, 0xcf4e6c5b, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c09-32.5",      0x10000, 0xa4713719, BRF_ESS | BRF_PRG },			//  5
	
	{ "c09-34.31",     0x20000, 0xa21b3151, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "c09-05.16",     0x80000, 0x890b38f0, BRF_GRA },				//  7	Chars
	
	{ "c09-04.52",     0x80000, 0x2cbb3c9b, BRF_GRA },				//  8	Sprites A
	{ "c09-02.53",     0x80000, 0xa83a0389, BRF_GRA },				//  9
	{ "c09-03.54",     0x80000, 0xa31d0e80, BRF_GRA },				//  10
	{ "c09-01.55",     0x80000, 0x64bfea10, BRF_GRA },				//  11
	
	{ "c09-07.15",     0x80000, 0x963bc82b, BRF_GRA },				//  12	Road Lines
	
	{ "c09-06.37",     0x80000, 0x12df6d7b, BRF_GRA },				//  13	Spritemap
	
	{ "c09-14.42",     0x80000, 0xad78bf46, BRF_SND },				//  14	ADPCM Samples
	{ "c09-13.43",     0x80000, 0xd57c41d3, BRF_SND },				//  15
	{ "c09-12.44",     0x80000, 0x56c99fa5, BRF_SND },				//  16
	
	{ "c09-15.29",     0x80000, 0xe63b9095, BRF_SND },				//  17	Delta-T Samples
	
	{ "c09-16.17",     0x10000, 0x7245a6f6, BRF_OPT },				//  18	Unused ROMs
	{ "c09-20.71",     0x00100, 0xcd8ffd80, BRF_OPT },				//  19
	{ "c09-23.14",     0x00100, 0xfbf81f30, BRF_OPT },				//  20
};

STD_ROM_PICK(Sci);
STD_ROM_FN(Sci);

static struct BurnRomInfo SciaRomDesc[] = {
	{ "c09-28.43",     0x20000, 0x630dbaad, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c09-30.40",     0x20000, 0x68b1a97d, BRF_ESS | BRF_PRG },			//  1
	{ "c09-36.38",     0x20000, 0x59e47cba, BRF_ESS | BRF_PRG },			//  2
	{ "c09-31.41",     0x20000, 0x962b1fbf, BRF_ESS | BRF_PRG },			//  3
	
	{ "c09-33.6",      0x10000, 0xcf4e6c5b, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c09-32.5",      0x10000, 0xa4713719, BRF_ESS | BRF_PRG },			//  5
	
	{ "c09-34.31",     0x20000, 0xa21b3151, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "c09-05.16",     0x80000, 0x890b38f0, BRF_GRA },				//  7	Chars
	
	{ "c09-04.52",     0x80000, 0x2cbb3c9b, BRF_GRA },				//  8	Sprites A
	{ "c09-02.53",     0x80000, 0xa83a0389, BRF_GRA },				//  9
	{ "c09-03.54",     0x80000, 0xa31d0e80, BRF_GRA },				//  10
	{ "c09-01.55",     0x80000, 0x64bfea10, BRF_GRA },				//  11
	
	{ "c09-07.15",     0x80000, 0x963bc82b, BRF_GRA },				//  12	Road Lines
	
	{ "c09-06.37",     0x80000, 0x12df6d7b, BRF_GRA },				//  13	Spritemap
	
	{ "c09-14.42",     0x80000, 0xad78bf46, BRF_SND },				//  14	ADPCM Samples
	{ "c09-13.43",     0x80000, 0xd57c41d3, BRF_SND },				//  15
	{ "c09-12.44",     0x80000, 0x56c99fa5, BRF_SND },				//  16
	
	{ "c09-15.29",     0x80000, 0xe63b9095, BRF_SND },				//  17	Delta-T Samples
	
	{ "c09-16.17",     0x10000, 0x7245a6f6, BRF_OPT },				//  18	Unused ROMs
	{ "c09-20.71",     0x00100, 0xcd8ffd80, BRF_OPT },				//  19
	{ "c09-23.14",     0x00100, 0xfbf81f30, BRF_OPT },				//  20
};

STD_ROM_PICK(Scia);
STD_ROM_FN(Scia);

static struct BurnRomInfo ScijRomDesc[] = {
	{ "c09-37.43",     0x20000, 0x0fecea17, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c09-38.40",     0x20000, 0xe46ebd9b, BRF_ESS | BRF_PRG },			//  1
	{ "c09-40.38",     0x20000, 0x1a4e2eab, BRF_ESS | BRF_PRG },			//  2
	{ "c09-39.41",     0x20000, 0xde87bcb9, BRF_ESS | BRF_PRG },			//  3
	
	{ "c09-33.6",      0x10000, 0xcf4e6c5b, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c09-32.5",      0x10000, 0xa4713719, BRF_ESS | BRF_PRG },			//  5
	
	{ "c09-27.31",     0x20000, 0xcd161dca, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "c09-05.16",     0x80000, 0x890b38f0, BRF_GRA },				//  7	Chars
	
	{ "c09-04.52",     0x80000, 0x2cbb3c9b, BRF_GRA },				//  8	Sprites A
	{ "c09-02.53",     0x80000, 0xa83a0389, BRF_GRA },				//  9
	{ "c09-03.54",     0x80000, 0xa31d0e80, BRF_GRA },				//  10
	{ "c09-01.55",     0x80000, 0x64bfea10, BRF_GRA },				//  11
	
	{ "c09-07.15",     0x80000, 0x963bc82b, BRF_GRA },				//  12	Road Lines
	
	{ "c09-06.37",     0x80000, 0x12df6d7b, BRF_GRA },				//  13	Spritemap
	
	{ "c09-10.42",     0x80000, 0xad78bf46, BRF_SND },				//  14	ADPCM Samples
	{ "c09-09.43",     0x80000, 0x6a655c00, BRF_SND },				//  15
	{ "c09-08.44",     0x80000, 0x7ddfc316, BRF_SND },				//  16
	
	{ "c09-11.29",     0x80000, 0x6b1a11e1, BRF_SND },				//  17	Delta-T Samples
	
	{ "c09-16.17",     0x10000, 0x7245a6f6, BRF_OPT },				//  18	Unused ROMs
	{ "c09-20.71",     0x00100, 0xcd8ffd80, BRF_OPT },				//  19
	{ "c09-23.14",     0x00100, 0xfbf81f30, BRF_OPT },				//  20
};

STD_ROM_PICK(Scij);
STD_ROM_FN(Scij);

static struct BurnRomInfo SciuRomDesc[] = {
	{ "c09-43.43",     0x20000, 0x20a9343e, BRF_ESS | BRF_PRG },			//  0	68000 #1 Program Code
	{ "c09-44.40",     0x20000, 0x7524338a, BRF_ESS | BRF_PRG },			//  1
	{ "c09-41.38",     0x20000, 0x83477f11, BRF_ESS | BRF_PRG },			//  2
	{ "c09-39.41",     0x20000, 0xde87bcb9, BRF_ESS | BRF_PRG },			//  3
	
	{ "c09-33.6",      0x10000, 0xcf4e6c5b, BRF_ESS | BRF_PRG },			//  4	68000 #2 Program Code
	{ "c09-32.5",      0x10000, 0xa4713719, BRF_ESS | BRF_PRG },			//  5
	
	{ "c09-34.31",     0x20000, 0xa21b3151, BRF_ESS | BRF_PRG },			//  6	Z80 Program
	
	{ "c09-05.16",     0x80000, 0x890b38f0, BRF_GRA },				//  7	Chars
	
	{ "c09-04.52",     0x80000, 0x2cbb3c9b, BRF_GRA },				//  8	Sprites A
	{ "c09-02.53",     0x80000, 0xa83a0389, BRF_GRA },				//  9
	{ "c09-03.54",     0x80000, 0xa31d0e80, BRF_GRA },				//  10
	{ "c09-01.55",     0x80000, 0x64bfea10, BRF_GRA },				//  11
	
	{ "c09-07.15",     0x80000, 0x963bc82b, BRF_GRA },				//  12	Road Lines
	
	{ "c09-06.37",     0x80000, 0x12df6d7b, BRF_GRA },				//  13	Spritemap
	
	{ "c09-14.42",     0x80000, 0xad78bf46, BRF_SND },				//  14	ADPCM Samples
	{ "c09-13.43",     0x80000, 0xd57c41d3, BRF_SND },				//  15
	{ "c09-12.44",     0x80000, 0x56c99fa5, BRF_SND },				//  16
	
	{ "c09-15.29",     0x80000, 0xe63b9095, BRF_SND },				//  17	Delta-T Samples
	
	{ "c09-16.17",     0x10000, 0x7245a6f6, BRF_OPT },				//  18	Unused ROMs
	{ "c09-20.71",     0x00100, 0xcd8ffd80, BRF_OPT },				//  19
	{ "c09-23.14",     0x00100, 0xfbf81f30, BRF_OPT },				//  20
};

STD_ROM_PICK(Sciu);
STD_ROM_FN(Sciu);

static struct BurnRomInfo SpacegunRomDesc[] = {
	{ "c57-18.62",         0x020000, 0x19d7d52e, BRF_ESS | BRF_PRG },		//  0	68000 #1 Program Code
	{ "c57-20.74",         0x020000, 0x2e58253f, BRF_ESS | BRF_PRG },		//  1
	{ "c57-17.59",         0x020000, 0xe197edb8, BRF_ESS | BRF_PRG },		//  2
	{ "c57-22.73",         0x020000, 0x5855fde3, BRF_ESS | BRF_PRG },		//  3
	
	{ "c57-15.27",         0x020000, 0xb36eb8f1, BRF_ESS | BRF_PRG },		//  4	68000 #2 Program Code
	{ "c57-16.29",         0x020000, 0xbfb5d1e7, BRF_ESS | BRF_PRG },		//  5
	
	{ "c57-06.52",         0x080000, 0x4ebadd5b, BRF_GRA },				//  6	Chars
	
	{ "c57-01.25",         0x100000, 0xf901b04e, BRF_GRA },				//  7	Sprites A
	{ "c57-02.24",         0x100000, 0x21ee4633, BRF_GRA },				//  8
	{ "c57-03.12",         0x100000, 0xfafca86f, BRF_GRA },				//  9
	{ "c57-04.11",         0x100000, 0xa9787090, BRF_GRA },				//  10
	
	{ "c57-05.36",         0x080000, 0x6a70eb2e, BRF_GRA },				//  11	Spritemap
	
	{ "c57-07.76",         0x080000, 0xad653dc1, BRF_SND },				//  12	ADPCM Samples
	
	{ "c57-08.75",         0x080000, 0x22593550, BRF_SND },				//  13	Delta-T Samples
	
	{ "pal16l8-c57-09.9",  0x000104, 0xea93161e, BRF_OPT },				//  14	Unused ROMs
	{ "pal20l8-c57-10.47", 0x000144, 0x3ee56888, BRF_OPT },				//  15
	{ "pal16l8-c57-11.48", 0x000104, 0x6bb4372e, BRF_OPT },				//  16
	{ "pal20l8-c57-12.61", 0x000144, 0xdebddb13, BRF_OPT },				//  17
	{ "pal16l8-c57-13.72", 0x000104, 0x1369f23e, BRF_OPT },				//  18
	{ "pal16r4-c57-14.96", 0x000104, 0x75e1bf61, BRF_OPT },				//  19
	
};

STD_ROM_PICK(Spacegun);
STD_ROM_FN(Spacegun);

static int MemIndex()
{
	unsigned char *Next; Next = Mem;

	TaitoZ68KRom1                  = Next; Next += 0x80000;
	TaitoZ68KRom2                  = Next; Next += 0x80000;
	TaitoZZ80Rom                   = Next; Next += 0x20000;
	TaitoZSpriteMapRom             = Next; Next += 0x80000;
	YM2610ADPCMAROM                = Next; Next += YM2610ADPCMASize;
	YM2610ADPCMBROM                = Next; Next += YM2610ADPCMBSize;
	
	RamStart                       = Next;

	TaitoZ68KRam1                  = Next; Next += 0x10000;
	TaitoZ68KRam2                  = Next; Next += 0x08000;
	TaitoZSharedRam                = Next; Next += 0x10000;
	TaitoZZ80Ram                   = Next; Next += 0x02000;
	TaitoZSpriteRam                = Next; Next += 0x04000;
	TaitoZPaletteRam               = Next; Next += 0x02000;
	
	RamEnd                         = Next;

	TaitoZChars                    = Next; Next += TaitoZNumChars * TaitoZCharXSize * TaitoZCharYSize;
	TaitoZSpritesA                 = Next; Next += TaitoZNumSpritesA * TaitoZSpriteAXSize * TaitoZSpriteAYSize;
	TaitoZSpritesB                 = Next; Next += TaitoZNumSpritesB * TaitoZSpriteBXSize * TaitoZSpriteBYSize;
	TaitoZPalette                  = (unsigned int*)Next; Next += 0x01000 * sizeof(unsigned int);

	MemEnd                         = Next;

	return 0;
}

static int TaitoZDoReset()
{
	SekOpen(0);
	SekReset();
	SekClose();
	
	SekOpen(1);
	SekReset();
	SekClose();

	if (TaitoZHasZ80) {
		ZetOpen(0);
		ZetReset();
		ZetClose();
	}
	
	if (TaitoZHasEEPROM) EEPROMReset();
	
	BurnYM2610Reset();
	
	if (TaitoZHasTC0110PCR) TC0110PCRReset();
	if (TaitoZHasTC0220IOC) TC0220IOCReset();
	if (TaitoZHasTC0140SYT) TC0140SYTReset();
	if (TaitoZHasTC0100SCN) TC0100SCNReset();
	
	TaitoZZ80Bank = 0;
	TaitoZCpuACtrl = 0xff;
	SciSpriteFrame = 0;
	TaitoZRoadPalBank = 0;
	OldSteer = 0;
	
	return 0;
}

static void TaitoZCpuAReset(UINT16 d)
{
	TaitoZCpuACtrl = d;
	if (!(TaitoZCpuACtrl & 1)) {
		SekClose();
		SekOpen(1);
		SekReset();
		SekClose();
		SekOpen(0);
	}
}

void __fastcall Aquajack68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x200000: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x300000:
		case 0x300002: {
			TC0110PCRStep1WordWrite((a - 0x300000) >> 1, d);
			return;
		}
		
		case 0xa20000:
		case 0xa20002:
		case 0xa20004:
		case 0xa20006:
		case 0xa20008:
		case 0xa2000a:
		case 0xa2000c:
		case 0xa2000e: {
			TC0100SCNCtrlWordWrite((a - 0xa20000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned char __fastcall Aquajack68K2ReadByte(unsigned int a)
{
	if (a >= 0x200000 && a <= 0x20000f) {
		return TC0220IOCHalfWordRead((a - 0x200000) >> 1);
	}
	
	switch (a) {
		case 0x300003: {
			return TC0140SYTCommRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

unsigned short __fastcall Aquajack68K2ReadWord(unsigned int a)
{
	switch (a) {
		case 0x200000:
		case 0x200002:
		case 0x200004:
		case 0x200006:
		case 0x200008:
		case 0x20000a:
		case 0x20000c:
		case 0x20000e: {
			return TC0220IOCHalfWordRead((a - 0x200000) >> 1);
		}
		
		case 0x900000:
		case 0x900002:
		case 0x900004:
		case 0x900006: {
			// nop
			return 0;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Aquajack68K2WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x200000:
		case 0x200002:
		case 0x200004:
		case 0x200006:
		case 0x200008:
		case 0x20000a:
		case 0x20000c:
		case 0x20000e: {
			TC0220IOCHalfWordWrite((a - 0x200000) >> 1, d);
			return;
		}
		
		case 0x300000: {
			TC0140SYTPortWrite(d & 0xff);
			return;
		}
		
		case 0x300002: {
			TC0140SYTCommWrite(d & 0xff);
			return;
		}
		
		case 0x900000:
		case 0x900002:
		case 0x900004:
		case 0x900006: {
			// nop
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static UINT8 BsharkStickRead(int Offset)
{
	switch (Offset) {
		case 0x00: {
			int Temp = (TaitoZAnalogPort0 >> 4) & 0xfff;
			Temp = 0xfff - Temp;
			Temp += 1;
			if (Temp == 0x1000) Temp = 0;
			return Temp;
		}
		
		case 0x01: {
			return 0xff;
		}
		
		case 0x02: {
			return TaitoZAnalogPort1 >> 4;
		}
		
		case 0x03: {
			return 0xff;
		}
	}
}

unsigned char __fastcall Bshark68K1ReadByte(unsigned int a)
{
	if (a >= 0x400000 && a <= 0x40000f) {
		return TC0220IOCHalfWordRead((a - 0x400000) >> 1);
	}
	
	switch (a) {
		case 0x800001:
		case 0x800003:
		case 0x800005:
		case 0x800007: {
			return BsharkStickRead((a - 0x800000) >> 1);
		}
		
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Bshark68K1WriteByte(unsigned int a, unsigned char d)
{
	if (a >= 0x400000 && a <= 0x40000f) {
		TC0220IOCHalfWordWrite((a - 0x400000) >> 1, d);
		return;
	}
	
	switch (a) {
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

void __fastcall Bshark68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x400000:
		case 0x400002:
		case 0x400004:
		case 0x400006:
		case 0x400008:
		case 0x40000a:
		case 0x40000c:
		case 0x40000e: {
			TC0220IOCHalfWordWrite((a - 0x400000) >> 1, d);
			return;
		}
		
		case 0x600000: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x800000:
		case 0x800002:
		case 0x800004:
		case 0x800006: {
			nCyclesDone[0] += SekRun(10000);
			SekSetIRQLine(6, SEK_IRQSTATUS_AUTO);
			return;
		}
		
		case 0xd20000:
		case 0xd20002:
		case 0xd20004:
		case 0xd20006:
		case 0xd20008:
		case 0xd2000a:
		case 0xd2000c:
		case 0xd2000e: {
			TC0100SCNCtrlWordWrite((a - 0xd20000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned short __fastcall Bshark68K2ReadWord(unsigned int a)
{
	switch (a) {
		case 0x40000a: {
			// ???
			return 0;
		}
		
		case 0x600000: {
			return BurnYM2610Read(0);
		}
		
		case 0x600004: {
			return BurnYM2610Read(2);
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Bshark68K2WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x400000:
		case 0x400002:
		case 0x400004:
		case 0x400006:
		case 0x400008: {
			// nop
			return;
		}
		
		case 0x600000: {
			BurnYM2610Write(0, d & 0xff);
			return;
		}
		
		case 0x600002: {
			BurnYM2610Write(1, d & 0xff);
			return;
		}
		
		case 0x600004: {
			BurnYM2610Write(2, d & 0xff);
			return;
		}
		
		case 0x600006: {
			BurnYM2610Write(3, d & 0xff);
			return;
		}
		
		case 0x60000c:
		case 0x60000e: {
			// nop
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static UINT8 ChasehqInputBypassRead()
{
	UINT8 Port = TC0220IOCPortRead();
	
	int Steer = (TaitoZAnalogPort0 >> 4);
	
	switch (Port) {
		case 0x08:
		case 0x09:
		case 0x0a:
		case 0x0b: {
			return 0xff;
		}
		
		case 0x0c: {
			return Steer & 0xff;
		}
		
		case 0x0d: {
			return Steer >> 8;
		}
	
		default: {
			return TC0220IOCPortRegRead();
		}
	}
}

unsigned char __fastcall Chasehq68K1ReadByte(unsigned int a)
{
	switch (a) {
		case 0x400001: {
			return ChasehqInputBypassRead();
		}
		
		case 0x820003: {
			return TC0140SYTCommRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Chasehq68K1WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x400001: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		case 0x400003: {
			TC0220IOCHalfWordPortWrite(d);
			return;
		}
		
		case 0x800001: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x820001: {
			TC0140SYTPortWrite(d);
			return;
		}
		
		case 0x820003: {
			TC0140SYTCommWrite(d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

unsigned short __fastcall Chasehq68K1ReadWord(unsigned int a)
{
	switch (a) {
		case 0x400002: {
			return TC0220IOCHalfWordPortRead();
		}
		
		case 0xa00002: {
			return TC0110PCRWordRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Chasehq68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x400000: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		case 0x400002: {
			TC0220IOCHalfWordPortWrite(d);
			return;
		}
		
		case 0xa00000:
		case 0xa00002: {
			TC0110PCRStep1WordWrite((a - 0xa00000) >> 1, d);
			return;
		}
		
		case 0xc20000:
		case 0xc20002:
		case 0xc20004:
		case 0xc20006:
		case 0xc20008:
		case 0xc2000a:
		case 0xc2000c:
		case 0xc2000e: {
			TC0100SCNCtrlWordWrite((a - 0xc20000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static UINT8 ContcircInputBypassRead()
{
	UINT8 Port = TC0220IOCPortRead();
	
	int Steer = (TaitoZAnalogPort0 >> 4) & 0xfff;
	Steer = 0xfff - Steer;
	if (Steer == 0xfff) Steer = 0;
	if (Steer > 0x5f && Steer < 0x80) Steer = 0x5f;
	if (Steer > 0xf7f && Steer < 0xfa0) Steer = 0xfa0;
	if (Steer > 0xf7f) Steer |= 0xf000;
	
	switch (Port) {
		case 0x08: {
			return Steer & 0xff;
		}
		
		case 0x09: {
			return Steer >> 8;
		}
	
		default: {
			return TC0220IOCPortRegRead();
		}
	}
}

void __fastcall Contcirc68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x090000: {
			TaitoZRoadPalBank = (d & 0xc0) >> 6;
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x100000:
		case 0x100002: {
			TC0110PCRStep1RBSwapWordWrite((a - 0x100000) >> 1, d);
			return;
		}
		
		case 0x220000:
		case 0x220002:
		case 0x220004:
		case 0x220006:
		case 0x220008:
		case 0x22000a:
		case 0x22000c:
		case 0x22000e: {
			TC0100SCNCtrlWordWrite((a - 0x220000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned char __fastcall Contcirc68K2ReadByte(unsigned int a)
{
	switch (a) {
		case 0x100001: {
			return ContcircInputBypassRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Contcirc68K2WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x100001: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

unsigned short __fastcall Contcirc68K2ReadWord(unsigned int a)
{
	switch (a) {
		case 0x100000: {
			return ContcircInputBypassRead();
		}
		
		case 0x100002: {
			return TC0220IOCHalfWordPortRead();
		}
		
		case 0x200002: {
			return TC0140SYTCommRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Contcirc68K2WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x100000: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		case 0x100002: {
			TC0220IOCHalfWordPortWrite(d);
			return;
		}
		
		case 0x200000: {
			TC0140SYTPortWrite(d & 0xff);
			return;
		}
		
		case 0x200002: {
			TC0140SYTCommWrite(d & 0xff);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned short __fastcall Enforce68K1ReadWord(unsigned int a)
{
	switch (a) {
		case 0x500002: {
			return TC0110PCRWordRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Enforce68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x200000: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x500000:
		case 0x500002: {
			TC0110PCRStep1RBSwapWordWrite((a - 0x500000) >> 1, d);
			return;
		}
		
		case 0x620000:
		case 0x620002:
		case 0x620004:
		case 0x620006:
		case 0x620008:
		case 0x62000a:
		case 0x62000c:
		case 0x62000e: {
			TC0100SCNCtrlWordWrite((a - 0x620000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned char __fastcall Enforce68K2ReadByte(unsigned int a)
{
	switch (a) {
		case 0x300001: {
			return TC0220IOCPortRegRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Enforce68K2WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x300001: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

unsigned short __fastcall Enforce68K2ReadWord(unsigned int a)
{
	switch (a) {
		case 0x200002: {
			return TC0140SYTCommRead();
		}
		
		case 0x300000: {
			return TC0220IOCPortRegRead();
		}
		
		case 0x300002: {
			return TC0220IOCHalfWordPortRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Enforce68K2WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x200000: {
			TC0140SYTPortWrite(d & 0xff);
			return;
		}
		
		case 0x200002: {
			TC0140SYTCommWrite(d & 0xff);
			return;
		}
		
		case 0x300000: {
			TC0220IOCHalfWordPortRegWrite(d);
			return;
		}
		
		case 0x300002: {
			TC0220IOCHalfWordPortWrite(d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static const UINT8 nightstr_stick[128]=
{
	0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
	0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
	0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
	0xe8,0x00,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,
	0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,
	0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,
	0x46,0x47,0x48,0x49,0xb8
};

static UINT8 NightstrStickRead(int Offset)
{
	switch (Offset) {
		case 0x00: {
			unsigned char Temp = 0x7f + (TaitoZAnalogPort0 >> 4);
			if (Temp < 0x01) Temp = 0x01;
			if (Temp > 0xfe) Temp = 0xfe;
			return nightstr_stick[(Temp * 0x64) / 0x100];
		}
		
		case 0x01: {
			unsigned char Temp = 0x7f - (TaitoZAnalogPort1 >> 4);
			if (Temp < 0x01) Temp = 0x01;
			if (Temp > 0xfe) Temp = 0xfe;
			return nightstr_stick[(Temp * 0x64) / 0x100];
		}
		
		case 0x02: {
			return 0xff;
		}
		
		case 0x03: {
			return 0xff;
		}
	}
	
	return 0xff;
}

unsigned char __fastcall Nightstr68K1ReadByte(unsigned int a)
{
	if (a >= 0x400000 && a <= 0x40000f) {
		return TC0220IOCHalfWordRead((a - 0x400000) >> 1);
	}
	
	switch (a) {
		case 0xe40001:
		case 0xe40003:
		case 0xe40005:
		case 0xe40007: {
			return NightstrStickRead((a - 0xe40000) >> 1);
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Nightstr68K1WriteByte(unsigned int a, unsigned char d)
{
	if (a >= 0x400000 && a <= 0x40000f) {
		TC0220IOCHalfWordWrite((a - 0x400000) >> 1, d);
		return;
	}
	
	switch (a) {
		case 0xe00000:
		case 0xe00008:
		case 0xe00010: {
			// nop
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

unsigned short __fastcall Nightstr68K1ReadWord(unsigned int a)
{
	switch (a) {
		case 0x820002: {
			return TC0140SYTCommRead();
		}
		
		case 0xa00002: {
			return TC0110PCRWordRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Nightstr68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x400000:
		case 0x400002:
		case 0x400004:
		case 0x400006:
		case 0x400008:
		case 0x40000a:
		case 0x40000c:
		case 0x40000e: {
			TC0220IOCHalfWordWrite((a - 0x400000) >> 1, d);
			return;
		}
		
		case 0x800000: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x820000: {
			TC0140SYTPortWrite(d & 0xff);
			return;
		}
		
		case 0x820002: {
			TC0140SYTCommWrite(d & 0xff);
			return;
		}
		
		case 0xa00000:
		case 0xa00002: {
			TC0110PCRStep1WordWrite((a - 0xa00000) >> 1, d);
			return;
		}
		
		case 0xc20000:
		case 0xc20002:
		case 0xc20004:
		case 0xc20006:
		case 0xc20008:
		case 0xc2000a:
		case 0xc2000c:
		case 0xc2000e: {
			TC0100SCNCtrlWordWrite((a - 0xc20000) >> 1, d);
			return;
		}
		
		case 0xe00000:
		case 0xe00008:
		case 0xe00010: {
			// nop
			return;
		}
		
		case 0xe40000:
		case 0xe40002:
		case 0xe40004:
		case 0xe40006:
		case 0xe40008:
		case 0xe4000a:
		case 0xe4000c:
		case 0xe4000e: {
			nCyclesDone[0] += SekRun(10000);
			SekSetIRQLine(6, SEK_IRQSTATUS_AUTO);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static UINT8 SciSteerRead(int Offset)
{
	int Steer = TaitoZAnalogPort0 >> 4;
	if (Steer > 0x5f && Steer < 0x80) Steer = 0x5f;
	if (Steer > 0xf80 && Steer < 0xfa0) Steer = 0xfa0;
	if ((OldSteer < Steer) && (Steer > 0xfc0)) Steer = 0;
	OldSteer = Steer;
	
	switch (Offset) {
		case 0x04: {
			return Steer & 0xff;
		}
		
		case 0x05: {
			return (Steer & 0xff00) >> 8;
		}
	}
	
	return 0xff;
}

unsigned char __fastcall Sci68K1ReadByte(unsigned int a)
{
	if (a >= 0x200000 && a <= 0x20000f) {
		return TC0220IOCHalfWordRead((a - 0x200000) >> 1);
	}
	
	switch (a) {
		case 0x200019:
		case 0x20001b: {
			return SciSteerRead((a - 0x200010) >> 1);
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Sci68K1WriteByte(unsigned int a, unsigned char d)
{
	if (a >= 0x200000 && a <= 0x20000f) {
		TC0220IOCHalfWordWrite((a - 0x200000) >> 1, d);
		return;
	}
	
	switch (a) {
		case 0x400001: {
			TaitoZCpuAReset(d);
			return;
		}
		
		case 0x420001: {
			TC0140SYTPortWrite(d);
			return;
		}
		
		case 0x420003: {
			TC0140SYTCommWrite(d);
			return;
		}
		
		case 0xc08000: {
			SciSpriteFrame = d;
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

void __fastcall Sci68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0xa20000:
		case 0xa20002:
		case 0xa20004:
		case 0xa20006:
		case 0xa20008:
		case 0xa2000a:
		case 0xa2000c:
		case 0xa2000e: {
			TC0100SCNCtrlWordWrite((a - 0xa20000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

static UINT8 SpacegunDefaultEEPROM[128]=
{
	0x00,0x00,0xff,0x00,0x01,0x00,0x41,0x41,0x00,0x00,0xff,0x00,0x00,0x00,0xf0,0xf0,
	0x00,0x00,0xff,0x00,0x01,0x00,0x41,0x41,0x00,0x00,0xff,0x00,0x00,0x00,0xf0,0xf0,
	0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x01,0x00,0x00,0x40,0x00,0x00,0x00,0xf0,
	0x01,0x00,0x85,0x42,0x00,0x00,0xe3,0xf1,0x01,0x00,0x00,0x40,0x00,0x00,0x00,0xf0,
	0x01,0x00,0x85,0x42,0x00,0x00,0xe3,0xf1,0xcb,0xcc,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

static UINT8 SpacegunInputBypassRead(int Offset)
{
	switch (Offset) {
		case 0x03: {
			return (EEPROMRead() & 1)  << 7;
		}
	
		default: {
			return TC0220IOCRead(Offset);
		}
	}
	
	return 0;
}

static void SpacegunInputBypassWrite(int Offset, UINT16 Data)
{
	switch (Offset) {
		case 0x03: {
			EEPROMWrite(Data & 0x20, Data & 0x10, Data & 0x40);
			return;
		}
	
		default: {
			TC0220IOCWrite(Offset, Data & 0xff);
		}
	}
}

unsigned short __fastcall Spacegun68K1ReadWord(unsigned int a)
{
	switch (a) {
		case 0xb00002: {
			return TC0110PCRWordRead();
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Spacegun68K1WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x920000:
		case 0x920002:
		case 0x920004:
		case 0x920006:
		case 0x920008:
		case 0x92000a:
		case 0x92000c:
		case 0x92000e: {
			TC0100SCNCtrlWordWrite((a - 0x920000) >> 1, d);
			return;
		}
		
		case 0xb00000:
		case 0xb00002: {
			TC0110PCRStep1RBSwapWordWrite((a - 0xb00000) >> 1, d);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #1 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned char __fastcall Spacegun68K2ReadByte(unsigned int a)
{
	switch (a) {
		case 0xc0000d: {
			// nop
			return 0;
		}
		
		case 0xf00001: {
			return ~BurnGunReturnX(0);
		}
		
		case 0xf00003: {
			return BurnGunReturnY(0);
		}
		
		case 0xf00005: {
			return ~BurnGunReturnX(1);
		}
		
		case 0xf00007: {
			return BurnGunReturnY(1);
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read byte => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Spacegun68K2WriteByte(unsigned int a, unsigned char d)
{
	switch (a) {
		case 0x800008: {
			SpacegunInputBypassWrite((a - 0x800000) >> 1, d);
			return;
		}
		
		case 0xc0000d: {
			// nop
			return;
		}
		
		case 0xe00001: {
			// ???
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write byte => %06X, %02X\n"), a, d);
		}
	}
}

unsigned short __fastcall Spacegun68K2ReadWord(unsigned int a)
{
	switch (a) {
		case 0x800000:
		case 0x800002:
		case 0x800004:
		case 0x800006:
		case 0x800008:
		case 0x80000a:
		case 0x80000c:
		case 0x80000e: {
			return SpacegunInputBypassRead((a - 0x800000) >> 1);
		}
		
		case 0xc00000: {
			return BurnYM2610Read(0);
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Read word => %06X\n"), a);
		}
	}
	
	return 0;
}

void __fastcall Spacegun68K2WriteWord(unsigned int a, unsigned short d)
{
	switch (a) {
		case 0x800000:
		case 0x800002:
		case 0x800004:
		case 0x800006:
		case 0x800008:
		case 0x80000a:
		case 0x80000c:
		case 0x80000e: {
			SpacegunInputBypassWrite((a - 0x800000) >> 1, d);
			return;
		}
		
		case 0xc00000: {
			BurnYM2610Write(0, d & 0xff);
			return;
		}
		
		case 0xc00002: {
			BurnYM2610Write(1, d & 0xff);
			return;
		}
		
		case 0xc00004: {
			BurnYM2610Write(2, d & 0xff);
			return;
		}
		
		case 0xc00006: {
			BurnYM2610Write(3, d & 0xff);
			return;
		}
		
		case 0xc20000:
		case 0xc20002:
		case 0xc20004:
		case 0xc20006: {
			// ???
			return;
		}
		
		case 0xf00000:
		case 0xf00002:
		case 0xf00004:
		case 0xf00006: {
			nCyclesDone[1] += SekRun(10000);
			SekSetIRQLine(5, SEK_IRQSTATUS_AUTO);
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("68K #2 Write word => %06X, %04X\n"), a, d);
		}
	}
}

unsigned char __fastcall TaitoZZ80Read(unsigned short a)
{
	switch (a) {
		case 0xe000: {
			return BurnYM2610Read(0);
		}
		
		case 0xe001: {
			return BurnYM2610Read(1);
		}
		
		case 0xe002: {
			return BurnYM2610Read(2);
		}
		
		case 0xe200: {
			// NOP
			return 0;
		}
		
		case 0xe201: {
			return TC0140SYTSlaveCommRead();
		}
		
		case 0xea00: {
			// NOP
			return 0;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("Z80 Read => %04X\n"), a);
		}
	}

	return 0;
}

void __fastcall TaitoZZ80Write(unsigned short a, unsigned char d)
{
	switch (a) {
		case 0xe000: {
			BurnYM2610Write(0, d);
			return;
		}
		
		case 0xe001: {
			BurnYM2610Write(1, d);
			return;
		}
		
		case 0xe002: {
			BurnYM2610Write(2, d);
			return;
		}
		
		case 0xe003: {
			BurnYM2610Write(3, d);
			return;
		}
		
		case 0xe200: {
			TC0140SYTSlavePortWrite(d);
			return;
		}
		
		case 0xe201: {
			TC0140SYTSlaveCommWrite(d);
			return;
		}
		
		case 0xe400:
		case 0xe401:
		case 0xe402:
		case 0xe403: {
			return;
		}
		
		case 0xe600: {
			return;
		}
		
		case 0xee00: {
			return;
		}
		
		case 0xf000: {
			return;
		}
		
		case 0xf200: {
			TaitoZZ80Bank = (d - 1) & 7;
			ZetMapArea(0x4000, 0x7fff, 0, TaitoZZ80Rom + 0x4000 + (TaitoZZ80Bank * 0x4000));
			ZetMapArea(0x4000, 0x7fff, 2, TaitoZZ80Rom + 0x4000 + (TaitoZZ80Bank * 0x4000));
			return;
		}
		
		default: {
			bprintf(PRINT_NORMAL, _T("Z80 Write => %04X, %02X\n"), a, d);
		}
	}
}

static int CharPlaneOffsets[4]   = { 0, 1, 2, 3 };
static int CharXOffsets[8]       = { 8, 12, 0, 4, 24, 28, 16, 20 };
static int CharYOffsets[8]       = { 0, 32, 64, 96, 128, 160, 192, 224 };
static int SpritePlaneOffsets[4] = { 0, 8, 16, 24 };
static int SpriteXOffsets[16]    = { 32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7 };
static int SpriteYOffsets[16]    = { 0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960 };
static int Sprite16x8YOffsets[8] = { 0, 64, 128, 192, 256, 320, 384, 448 };

static void TaitoZFMIRQHandler(int, int nStatus)
{
	if (nStatus & 1) {
		ZetSetIRQLine(0xFF, ZET_IRQSTATUS_ACK);
	} else {
		ZetSetIRQLine(0,    ZET_IRQSTATUS_NONE);
	}
}

static int TaitoZSynchroniseStream(int nSoundRate)
{
	return (long long)ZetTotalCycles() * nSoundRate / (16000000 / 4);
}

static double TaitoZGetTime()
{
	return (double)ZetTotalCycles() / (16000000 / 4);
}

static int TaitoZ68KSynchroniseStream(int nSoundRate)
{
	return (long long)SekTotalCycles() * nSoundRate / (nCyclesTotal[1] * 60);
}

static double TaitoZ68KGetTime()
{
	return (double)SekTotalCycles() / (nCyclesTotal[1] * 60);
}

static void TaitoZZ80Init()
{
	// Setup the Z80 emulation
	ZetInit(1);
	ZetOpen(0);
	ZetSetReadHandler(TaitoZZ80Read);
	ZetSetWriteHandler(TaitoZZ80Write);
	ZetMapArea(0x0000, 0x3fff, 0, TaitoZZ80Rom                );
	ZetMapArea(0x0000, 0x3fff, 2, TaitoZZ80Rom                );
	ZetMapArea(0x4000, 0x7fff, 0, TaitoZZ80Rom + 0x4000       );
	ZetMapArea(0x4000, 0x7fff, 2, TaitoZZ80Rom + 0x4000       );
	ZetMapArea(0xc000, 0xdfff, 0, TaitoZZ80Ram                );
	ZetMapArea(0xc000, 0xdfff, 1, TaitoZZ80Ram                );
	ZetMapArea(0xc000, 0xdfff, 2, TaitoZZ80Ram                );
	ZetMemEnd();
	ZetClose();
	
	TaitoZHasZ80 = 1;
}

static int AquajackInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x8000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x080000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0110PCRInit(0x4000, 0x1000);
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 8, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  4, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  5, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  6, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  7, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  ,  9, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);
	
	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 10, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 11, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 12, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 13, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x104000, 0x107fff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x800000, 0x801fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0xa00000, 0xa0ffff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0xc40000, 0xc403ff, SM_RAM);
	SekSetWriteWordHandler(0, Aquajack68K1WriteWord);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x104000, 0x107fff, SM_RAM);
	SekSetReadWordHandler(0, Aquajack68K2ReadWord);
	SekSetWriteWordHandler(0, Aquajack68K2WriteWord);
	SekSetReadByteHandler(0, Aquajack68K2ReadByte);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = AquajackMakeInputs;
	DrawFunction = AquajackDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 500;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int BsharkInit()
{
	int nRet = 0, nLen;
	
	Sci = 1;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x8000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x080000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 0;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 0;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0150RODInit(0x80000, 0x2000, 1);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 8, 1);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);
	
	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  5, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x40001   ,  6, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x40000   ,  7, 2); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  8, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  9, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  , 10, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 11, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 12, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);

	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 13, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 14, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 15, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 16, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x10ffff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x110000, 0x113fff, SM_RAM);
	SekMapMemory(TaitoZPaletteRam        , 0xa00000, 0xa01fff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0xc00000, 0xc00fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0xd00000, 0xd0ffff, SM_RAM);
	SekSetWriteWordHandler(0, Bshark68K1WriteWord);
	SekSetReadByteHandler(0, Bshark68K1ReadByte);
	SekSetWriteByteHandler(0, Bshark68K1WriteByte);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x108000, 0x10bfff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x110000, 0x113fff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x800000, 0x801fff, SM_RAM);
	SekSetReadWordHandler(0, Bshark68K2ReadWord);
	SekSetWriteWordHandler(0, Bshark68K2WriteWord);
	SekClose();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, NULL, TaitoZ68KSynchroniseStream, TaitoZ68KGetTime, 0);
	BurnTimerAttachSek(12000000);
	
	MakeInputsFunction = BsharkMakeInputs;
	DrawFunction = BsharkDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 1;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int ChasehqInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x4000;
	TaitoZNumSpritesB = 0x4000;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 16;
	TaitoZSpriteBXSize = 16;
	TaitoZSpriteBYSize = 16;
	YM2610ADPCMASize = 0x180000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0110PCRInit(0x4000, 0x1000);
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 8, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  5, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  6, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  7, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  9, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 10, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 11, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, SpriteYOffsets, 0x400, TaitoZTempRom, TaitoZSpritesA);

	// Load and decode Sprites B
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  , 12, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  , 13, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 14, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 15, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesB, 4, TaitoZSpriteBXSize, TaitoZSpriteBYSize, SpritePlaneOffsets, SpriteXOffsets, SpriteYOffsets, 0x400, TaitoZTempRom, TaitoZSpritesB);
	
	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 16, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 17, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 18, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x080000, 19, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x100000, 20, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 21, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x107fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x108000, 0x10bfff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0xc00000, 0xc0ffff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0xd00000, 0xd007ff, SM_RAM);
	SekSetReadWordHandler(0, Chasehq68K1ReadWord);
	SekSetWriteWordHandler(0, Chasehq68K1WriteWord);
	SekSetReadByteHandler(0, Chasehq68K1ReadByte);
	SekSetWriteByteHandler(0, Chasehq68K1WriteByte);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x01ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x108000, 0x10bfff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x800000, 0x801fff, SM_RAM);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = ChasehqMakeInputs;
	DrawFunction = ChasehqDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int ContcircInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x8000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x100000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0110PCRInit(0x4000, 0x1000);
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 16, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  4, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  5, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  6, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  7, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  ,  9, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);
	
	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 10, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 11, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 12, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x080000, 13, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 14, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x080000, 0x083fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x084000, 0x087fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0x200000, 0x20ffff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x300000, 0x301fff, SM_RAM);	
	SekMapMemory(TaitoZSpriteRam         , 0x400000, 0x4006ff, SM_RAM);
	SekSetWriteWordHandler(0, Contcirc68K1WriteWord);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x080000, 0x083fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x084000, 0x087fff, SM_RAM);
	SekSetReadWordHandler(0, Contcirc68K2ReadWord);
	SekSetWriteWordHandler(0, Contcirc68K2WriteWord);
	SekSetReadByteHandler(0, Contcirc68K2ReadByte);
	SekSetWriteByteHandler(0, Contcirc68K2WriteByte);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = ContcircMakeInputs;
	DrawFunction = ContcircDraw;
	TaitoZVBlankIRQ = 6;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int EnforceInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x8000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x100000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;

	TC0110PCRInit(0x4000, 0x1000);
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 16, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  4, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  5, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  6, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  7, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  ,  9, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);
	
	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 10, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 11, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 12, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x080000, 13, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 14, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x104000, 0x107fff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0x300000, 0x3006ff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x400000, 0x401fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0x600000, 0x60ffff, SM_RAM);
	SekSetReadWordHandler(0, Enforce68K1ReadWord);
	SekSetWriteWordHandler(0, Enforce68K1WriteWord);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x104000, 0x107fff, SM_RAM);
	SekSetReadWordHandler(0, Enforce68K2ReadWord);
	SekSetWriteWordHandler(0, Enforce68K2WriteWord);
	SekSetReadByteHandler(0, Enforce68K2ReadByte);
	SekSetWriteByteHandler(0, Enforce68K2WriteByte);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = EnforceMakeInputs;
	DrawFunction = ContcircDraw;
	TaitoZVBlankIRQ = 6;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int NightstrInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x4000;
	TaitoZNumSpritesB = 0x4000;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 16;
	TaitoZSpriteBXSize = 16;
	TaitoZSpriteBYSize = 16;
	YM2610ADPCMASize = 0x100000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0110PCRInit(0x4000, 0x1000);
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 8, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  5, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  6, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  7, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  9, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 10, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 11, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, SpriteYOffsets, 0x400, TaitoZTempRom, TaitoZSpritesA);

	// Load and decode Sprites B
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  , 12, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  , 13, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 14, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 15, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesB, 4, TaitoZSpriteBXSize, TaitoZSpriteBYSize, SpritePlaneOffsets, SpriteXOffsets, SpriteYOffsets, 0x400, TaitoZTempRom, TaitoZSpritesB);
	
	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 16, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 17, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 18, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x080000, 19, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 20, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x10ffff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x110000, 0x113fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0xc00000, 0xc0ffff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0xd00000, 0xd007ff, SM_RAM);
	SekSetReadWordHandler(0, Nightstr68K1ReadWord);
	SekSetWriteWordHandler(0, Nightstr68K1WriteWord);
	SekSetReadByteHandler(0, Nightstr68K1ReadByte);
	SekSetWriteByteHandler(0, Nightstr68K1WriteByte);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x100000, 0x103fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x104000, 0x107fff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0x800000, 0x801fff, SM_RAM);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = NightstrMakeInputs;
	DrawFunction = ChasehqDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int SciInit()
{
	int nRet = 0, nLen;
	
	Sci = 1;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x8000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x180000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 0;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 1;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 1;
	
	TC0150RODInit(0x80000, 0x2000, 0);
	TC0100SCNInit(0x10000, TaitoZNumChars, 0, 8, 0);

	TaitoZTempRom = (unsigned char *)malloc(0x200000);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  5, 2); if (nRet != 0) return 1;
	
	// Load Z80 Program Roms
	nRet = BurnLoadRom(TaitoZZ80Rom              ,  6, 1); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  7, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x200000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  9, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  , 10, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 11, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);

	// Load Road Rom
	nRet = BurnLoadRom(TC0150RODRom              , 12, 1); if (nRet != 0) return 1;
	
	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 13, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 14, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x080000, 15, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x100000, 16, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 17, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x100000, 0x107fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x108000, 0x10bfff, SM_RAM);
	SekMapMemory(TaitoZPaletteRam        , 0x800000, 0x801fff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0xa00000, 0xa0ffff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0xc00000, 0xc03fff, SM_RAM);
	SekSetWriteWordHandler(0, Sci68K1WriteWord);
	SekSetReadByteHandler(0, Sci68K1ReadByte);
	SekSetWriteByteHandler(0, Sci68K1WriteByte);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x01ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x200000, 0x203fff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x208000, 0x20bfff, SM_RAM);
	SekMapMemory(TC0150RODRam            , 0xa00000, 0xa01fff, SM_RAM);
	SekClose();
	
	TaitoZZ80Init();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, &TaitoZFMIRQHandler, TaitoZSynchroniseStream, TaitoZGetTime, 0);
	BurnTimerAttachZet(16000000 / 4);
	
	MakeInputsFunction = SciMakeInputs;
	DrawFunction = SciDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 0;
	TaitoZHasEEPROM = 0;
	nCyclesTotal[0] = 12000000 / 60;
	nCyclesTotal[1] = 12000000 / 60;
	nCyclesTotal[2] = (16000000 / 4) / 60;
	
	GenericTilesInit();

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int SpacegunInit()
{
	int nRet = 0, nLen;
	
	TaitoZNumChars = 0x4000;
	TaitoZNumSpritesA = 0x10000;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 8;
	TaitoZCharYSize = 8;
	TaitoZSpriteAXSize = 16;
	TaitoZSpriteAYSize = 8;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0x080000;
	YM2610ADPCMBSize = 0x080000;

	// Allocate and Blank all required memory
	Mem = NULL;
	MemIndex();
	nLen = MemEnd - (unsigned char *)0;
	if ((Mem = (unsigned char *)malloc(nLen)) == NULL) return 1;
	memset(Mem, 0, nLen);
	MemIndex();
	
	TaitoZHasTC0110PCR = 1;
	TaitoZHasTC0220IOC = 1;
	TaitoZHasTC0140SYT = 0;
	TaitoZHasTC0100SCN = 1;
	TaitoZHasTC0150ROD = 0;
	
	TC0110PCRInit(0x4000, 0x1000);
	TC0100SCNInit(0x10000, TaitoZNumChars, 4, 8, 1);

	TaitoZTempRom = (unsigned char *)malloc(0x400000);
	
	// Make sure we use Musashi
	if (bBurnUseASMCPUEmulation) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching to Musashi 68000 core\n"));
#endif
		bUseAsm68KCoreOldValue = bBurnUseASMCPUEmulation;
		bBurnUseASMCPUEmulation = false;
	}

	// Load 68000 #1 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00001   ,  0, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x00000   ,  1, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40001   ,  2, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom1 + 0x40000   ,  3, 2); if (nRet != 0) return 1;
	
	// Load 68000 #2 Program Roms
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00001   ,  4, 2); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZ68KRom2 + 0x00000   ,  5, 2); if (nRet != 0) return 1;
	
	// Load and decode Chars
	memset(TaitoZTempRom, 0, 0x400000);
	nRet = BurnLoadRom(TaitoZTempRom             ,  6, 1); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumChars, 4, TaitoZCharXSize, TaitoZCharYSize, CharPlaneOffsets, CharXOffsets, CharYOffsets, 0x100, TaitoZTempRom, TaitoZChars);
	
	// Load and decode Sprites A
	memset(TaitoZTempRom, 0, 0x400000);
	nRet = BurnLoadRom(TaitoZTempRom + 0x000000  ,  7, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000001  ,  8, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000002  ,  9, 4); if (nRet != 0) return 1;
	nRet = BurnLoadRom(TaitoZTempRom + 0x000003  , 10, 4); if (nRet != 0) return 1;
	GfxDecode(TaitoZNumSpritesA, 4, TaitoZSpriteAXSize, TaitoZSpriteAYSize, SpritePlaneOffsets, SpriteXOffsets, Sprite16x8YOffsets, 0x200, TaitoZTempRom, TaitoZSpritesA);

	// Load SpriteMap Rom
	nRet = BurnLoadRom(TaitoZSpriteMapRom        , 11, 1); if (nRet != 0) return 1;
	
	// Load YM2610 Samples
	nRet = BurnLoadRom(YM2610ADPCMAROM + 0x000000, 12, 1); if (nRet != 0) return 1;
	nRet = BurnLoadRom(YM2610ADPCMBROM + 0x000000, 13, 1); if (nRet != 0) return 1;

	free(TaitoZTempRom);
	
	// Setup the 68000 emulation
	SekInit(0, 0x68000);
	SekOpen(0);
	SekMapMemory(TaitoZ68KRom1           , 0x000000, 0x07ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam1           , 0x30c000, 0x30ffff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x310000, 0x31ffff, SM_RAM);
	SekMapMemory(TaitoZSpriteRam         , 0x500000, 0x5005ff, SM_RAM);
	SekMapMemory(TC0100SCNRam            , 0x900000, 0x90ffff, SM_RAM);
	SekSetReadWordHandler(0, Spacegun68K1ReadWord);
	SekSetWriteWordHandler(0, Spacegun68K1WriteWord);
	SekClose();
	
	SekInit(1, 0x68000);
	SekOpen(1);
	SekMapMemory(TaitoZ68KRom2           , 0x000000, 0x03ffff, SM_ROM);
	SekMapMemory(TaitoZ68KRam2           , 0x20c000, 0x20ffff, SM_RAM);
	SekMapMemory(TaitoZSharedRam         , 0x210000, 0x21ffff, SM_RAM);
	SekSetReadWordHandler(0, Spacegun68K2ReadWord);
	SekSetWriteWordHandler(0, Spacegun68K2WriteWord);
	SekSetReadByteHandler(0, Spacegun68K2ReadByte);
	SekSetWriteByteHandler(0, Spacegun68K2WriteByte);
	SekClose();
	
	BurnYM2610Init(16000000 / 2, YM2610ADPCMAROM, &YM2610ADPCMASize, YM2610ADPCMBROM, &YM2610ADPCMBSize, NULL, TaitoZ68KSynchroniseStream, TaitoZ68KGetTime, 0);
	BurnTimerAttachSek(16000000);
	
	EEPROMInit(1024, 16);
	EEPROMFill((unsigned char*)SpacegunDefaultEEPROM, 0, 128);
	
	MakeInputsFunction = SpacegunMakeInputs;
	DrawFunction = SpacegunDraw;
	TaitoZVBlankIRQ = 4;
	TaitoZFrameInterleave = 100;
	TaitoZFlipScreenX = 1;
	TaitoZHasEEPROM = 1;
	nCyclesTotal[0] = 16000000 / 60;
	nCyclesTotal[1] = 16000000 / 60;
	
	GenericTilesInit();
	BurnGunInit(2, true);

	// Reset the driver
	TaitoZDoReset();

	return 0;
}

static int TaitoZExit()
{
	SekExit();
	ZetExit();
	
	BurnYM2610Exit();
	
	if (TaitoZHasEEPROM) EEPROMExit();
	
	TC0110PCRExit();
	TC0220IOCExit();
	TC0150RODExit();
	TC0140SYTExit();
	TC0100SCNExit();

	GenericTilesExit();
	BurnGunExit();
	
	TaitoZCpuACtrl = 0;
	TaitoZZ80Bank = 0;
	SciSpriteFrame = 0;
	TaitoZRoadPalBank = 0;
	OldSteer = 0;
	
	MakeInputsFunction = NULL;
	DrawFunction = NULL;
	
	TaitoZNumChars = 0;
	TaitoZNumSpritesA = 0;
	TaitoZNumSpritesB = 0;
	TaitoZCharXSize = 0;
	TaitoZCharYSize = 0;
	TaitoZSpriteAXSize = 0;
	TaitoZSpriteAYSize = 0;
	TaitoZSpriteBXSize = 0;
	TaitoZSpriteBYSize = 0;
	YM2610ADPCMASize = 0;
	YM2610ADPCMBSize = 0;
	TaitoZVBlankIRQ = 0;
	TaitoZFrameInterleave = 0;
	TaitoZHasZ80 = 0;
	TaitoZHasEEPROM = 0;
	TaitoZHasTC0110PCR = 0;
	TaitoZHasTC0220IOC = 0;
	TaitoZHasTC0140SYT = 0;
	TaitoZHasTC0100SCN = 0;
	TaitoZHasTC0150ROD = 0;

	TaitoZFlipScreenX = 0;
	
	Sci = 0;
	
	free(Mem);
	Mem = NULL;
	
	// Switch back CPU core if needed
	if (bUseAsm68KCoreOldValue) {
#if 1 && defined FBA_DEBUG
		bprintf(PRINT_NORMAL, _T("Switching back to A68K core\n"));
#endif
		bUseAsm68KCoreOldValue = false;
		bBurnUseASMCPUEmulation = true;
	}

	return 0;
}

static inline unsigned char pal5bit(unsigned char bits)
{
	bits &= 0x1f;
	return (bits << 3) | (bits >> 2);
}

inline static unsigned int CalcCol(unsigned short nColour)
{
	int r, g, b;

	r = pal5bit(nColour >>  0);
	g = pal5bit(nColour >>  5);
	b = pal5bit(nColour >> 10);

	return BurnHighCol(r, g, b, 0);
}

static void TaitoZCalcPalette()
{
	int i;
	unsigned short* ps;
	unsigned int* pd;

	for (i = 0, ps = (unsigned short*)TaitoZPaletteRam, pd = TaitoZPalette; i < 0x1000; i++, ps++, pd++) {
		*pd = CalcCol(*ps);
	}
}

static void RenderSpriteZoom(int Code, int sx, int sy, int Colour, int xFlip, int yFlip, int xScale, int yScale, unsigned char* pSource)
{
	// We can use sprite A for sizes, etc. as only Chase HQ uses sprite B and it has the same sizes and count
	
	UINT8 *SourceBase = pSource + ((Code % TaitoZNumSpritesA) * TaitoZSpriteAXSize * TaitoZSpriteAYSize);
	
	int SpriteScreenHeight = (yScale * TaitoZSpriteAYSize + 0x8000) >> 16;
	int SpriteScreenWidth = (xScale * TaitoZSpriteAXSize + 0x8000) >> 16;
	
	Colour = 0x10 * (Colour % 0x100);
	
	if (TaitoZFlipScreenX) {
		xFlip = !xFlip;
		sx = 320 - sx - (xScale >> 12);
	}	
		
	if (SpriteScreenWidth && SpriteScreenHeight) {
		int dx = (TaitoZSpriteAXSize << 16) / SpriteScreenWidth;
		int dy = (TaitoZSpriteAYSize << 16) / SpriteScreenHeight;
		
		int ex = sx + SpriteScreenWidth;
		int ey = sy + SpriteScreenHeight;
		
		int xIndexBase;
		int yIndex;
		
		if (xFlip) {
			xIndexBase = (SpriteScreenWidth - 1) * dx;
			dx = -dx;
		} else {
			xIndexBase = 0;
		}
		
		if (yFlip) {
			yIndex = (SpriteScreenHeight - 1) * dy;
			dy = -dy;
		} else {
			yIndex = 0;
		}
		
		if (sx < 0) {
			int Pixels = 0 - sx;
			sx += Pixels;
			xIndexBase += Pixels * dx;
		}
		
		if (sy < 0) {
			int Pixels = 0 - sy;
			sy += Pixels;
			yIndex += Pixels * dy;
		}
		
		if (ex > nScreenWidth) {
			int Pixels = ex - nScreenWidth;
			ex -= Pixels;
		}
		
		if (ey > nScreenHeight) {
			int Pixels = ey - nScreenHeight;
			ey -= Pixels;	
		}
		
		if (ex > sx) {
			int y;
			
			for (y = sy; y < ey; y++) {
				UINT8 *Source = SourceBase + ((yIndex >> 16) * TaitoZSpriteAXSize);
				unsigned short* pPixel = pTransDraw + (y * nScreenWidth);
				
				int x, xIndex = xIndexBase;
				for (x = sx; x < ex; x++) {
					int c = Source[xIndex >> 16];
					if (c != 0) {
						pPixel[x] = c | Colour;
					}
					xIndex += dx;
				}
				
				yIndex += dy;
			}
		}
	}
}

static void AquajackRenderSprites(int PriorityDraw)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	for (Offset = 0x200 - 4; Offset >= 0; Offset -= 4) {
		Data = SpriteRam[Offset + 1];
		Priority = (Data & 0x8000) >> 15;
		
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		xFlip = (Data & 0x4000) >> 14;
		x = Data & 0x1ff;

		Data = SpriteRam[Offset + 3];
		yFlip = (Data & 0x8000) >> 15;
		Tile = Data & 0x1fff;
		if (!Tile) continue;
		
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0x7e00) >> 9;
		y = Data & 0x1ff;
		
		Data = SpriteRam[Offset + 2];
		Colour = (Data & 0xff00) >> 8;
		xZoom = (Data & 0x3f);

		MapOffset = Tile << 5;

		xZoom += 1;
		yZoom += 1;

		y += 3;

		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		for (SpriteChunk = 0; SpriteChunk < 32; SpriteChunk++) {
			k = SpriteChunk % 4;
			j = SpriteChunk / 4;

			px = xFlip ? (3 - k) : k;
			py = yFlip ? (7 - j) : j;

			Code = SpriteMap[MapOffset + px + (py << 2)];
			Code &= (TaitoZNumSpritesA - 1);

			xCur = x + ((k * xZoom) / 4);
			yCur = y + ((j * yZoom) / 8);

			zx = x + (((k + 1) * xZoom) / 4) - xCur;
			zy = y + (((j + 1) * yZoom) / 8) - yCur;

			yCur -= 16;

			RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 13, TaitoZSpritesA);
		}


	}
}

static void BsharkRenderSprites(int PriorityDraw, int yOffset)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	for (Offset = 0; Offset < 0x800 - 4; Offset += 4) {
		Data = SpriteRam[Offset + 1];
		Priority = (Data & 0x8000) >> 15;
		
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		Colour = (Data & 0x7f80) >> 7;
		xZoom = (Data & 0x3f);
		
		Data = SpriteRam[Offset + 3];
		Tile = Data & 0x1fff;
		if (!Tile) continue;
				
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0x7e00) >> 9;
		y = Data & 0x1ff;

		Data = SpriteRam[Offset + 2];
		yFlip = (Data & 0x8000) >> 15;
		xFlip = (Data & 0x4000) >> 14;
		x = Data & 0x1ff;

		MapOffset = Tile << 5;

		xZoom += 1;
		yZoom += 1;

		y += yOffset;
		y += (64 - yZoom);

		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		for (SpriteChunk = 0; SpriteChunk < 32; SpriteChunk++) {
			k = SpriteChunk % 4;
			j = SpriteChunk / 4;
			
			px = xFlip ? (3 - k) : k;
			py = yFlip ? (7 - j) : j;

			Code = SpriteMap[MapOffset + px + (py << 2)];
			Code &= (TaitoZNumSpritesA - 1);
			
			xCur = x + ((k * xZoom) / 4);
			yCur = y + ((j * yZoom) / 8);
			
			zx = x + (((k + 1) * xZoom) / 4) - xCur;
			zy = y + (((j + 1) * yZoom) / 8) - yCur;

			yCur -= 16;

			RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 13, TaitoZSpritesA);
		}

	}
}

static void ChasehqRenderSprites(int PriorityDraw)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	for (Offset = 0; Offset < 0x400; Offset += 4) {
		Data = SpriteRam[Offset + 1];
		Priority = (Data & 0x8000) >> 15;
		
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		Colour = (Data & 0x7f80) >> 7;
		xZoom = (Data & 0x7f);
		
		Data = SpriteRam[Offset + 3];
		Tile = Data & 0x7ff;
		if (!Tile) continue;
		
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0xfe00) >> 9;
		y = Data & 0x1ff;
				
		Data = SpriteRam[Offset + 2];
		yFlip = (Data & 0x8000) >> 15;
		xFlip = (Data & 0x4000) >> 14;
		x = Data & 0x1ff;
		
		xZoom += 1;
		yZoom += 1;
		
		y += 7;
		y += (128 - yZoom);
		
		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		if ((xZoom - 1) & 0x40) {
			MapOffset = Tile << 6;
			
			for (SpriteChunk = 0; SpriteChunk < 64; SpriteChunk++) {
				j = SpriteChunk / 8;
				k = SpriteChunk % 8;
				
				px = xFlip ? (7 - k) : k;
				py = yFlip ? (7 - j) : j;
				
				Code = SpriteMap[MapOffset + px + (py << 3)];
				Code &= (TaitoZNumSpritesA - 1);
				
				xCur = x + ((k * xZoom) / 8);
				yCur = y + ((j * yZoom) / 8);
				
				zx = x + (((k + 1) * xZoom) / 8) - xCur;
				zy = y + (((j + 1) * yZoom) / 8) - yCur;
				
				yCur -= 16;
				
				RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 12, TaitoZSpritesA);
			}
		} else if ((xZoom - 1) & 0x20) {
			MapOffset = (Tile << 5) + 0x20000;
			
			for (SpriteChunk = 0; SpriteChunk < 32; SpriteChunk++) {
				j = SpriteChunk / 4;
				k = SpriteChunk % 4;
				
				px = xFlip ? (3 - k) : k;
				py = yFlip ? (7 - j) : j;
				
				Code = SpriteMap[MapOffset + px + (py << 2)];
				Code &= (TaitoZNumSpritesB - 1);
				
				xCur = x + ((k * xZoom) / 4);
				yCur = y + ((j * yZoom) / 8);
				
				zx = x + (((k + 1) * xZoom) / 4) - xCur;
				zy = y + (((j + 1) * yZoom) / 8) - yCur;
				
				yCur -= 16;
				
				RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 12, TaitoZSpritesB);
			}
		} else if (!((xZoom - 1) & 0x60)) {
			MapOffset = (Tile << 4) + 0x30000;
			
			for (SpriteChunk = 0; SpriteChunk < 16; SpriteChunk++) {
				j = SpriteChunk / 2;
				k = SpriteChunk % 2;
				
				px = xFlip ? (1 - k) : k;
				py = yFlip ? (7 - j) : j;
				
				Code = SpriteMap[MapOffset + px + (py << 1)];
				Code &= (TaitoZNumSpritesB - 1);
				
				xCur = x + ((k * xZoom) / 2);
				yCur = y + ((j * yZoom) / 8);
				
				zx = x + (((k + 1) * xZoom) / 2) - xCur;
				zy = y + (((j + 1) * yZoom) / 8) - yCur;
				
				yCur -= 16;
				
				RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 12, TaitoZSpritesB);
			}
		}
	}
}

static void ContcircRenderSprites(int PriorityDraw, int VisibleYOffset)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	for (Offset = 0x380 - 4; Offset >= 0; Offset -= 4) {
		Data = SpriteRam[Offset + 2];
		Priority = (Data & 0x8000) >> 15;
			
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		xFlip = (Data & 0x4000) >> 14;
		yFlip = (Data & 0x2000) >> 13;
		x = Data & 0x1ff;
		
		Data = SpriteRam[Offset + 1];
		Tile = Data & 0x7ff;
		if (!Tile) continue;
		
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0xfe00) >> 9;
		y = Data & 0x1ff;
		
		Data = SpriteRam[Offset + 3];
		Colour = (Data & 0xff00) >> 8;
		xZoom = (Data & 0x7f);		

		MapOffset = Tile << 7;

		xZoom += 1;
		yZoom += 1;

		y += 5;
		y += ( 128 - yZoom);

		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		for (SpriteChunk = 0; SpriteChunk < 128; SpriteChunk++)	{
			k = SpriteChunk % 8;
			j = SpriteChunk / 8;

			px = xFlip ? (7 - k) : k;
			py = yFlip ? (15 - j) : j;

			Code = SpriteMap[MapOffset + px + (py << 3)];
			Code &= (TaitoZNumSpritesA - 1);

			xCur = x + ((k * xZoom) / 8);
			yCur = y + ((j * yZoom) / 16);

			zx = x + (((k + 1) * xZoom) / 8) - xCur;
			zy = y + (((j + 1) * yZoom) / 16) - yCur;

			yCur -= VisibleYOffset;

			RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 13, TaitoZSpritesA);
		}
	}
}

static void SciRenderSprites(int PriorityDraw, int yOffs)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, StartOffs, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	StartOffs = (SciSpriteFrame & 1) ? 0x800 : 0;
	
	for (Offset = StartOffs; Offset < StartOffs + 0x800; Offset += 4) {
		Data = SpriteRam[Offset + 1];
		Priority = (Data & 0x8000) >> 15;
		
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		Colour = (Data & 0x7f80) >> 7;
		xZoom = (Data & 0x3f);
		
		Data = SpriteRam[Offset + 3];
		Tile = Data & 0x1fff;
		if (!Tile) continue;
		
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0x7e00) >> 9;
		y = Data & 0x1ff;

		Data = SpriteRam[Offset + 2];
		yFlip = (Data & 0x8000) >> 15;
		xFlip = (Data & 0x4000) >> 14;
		x = Data & 0x1ff;

		MapOffset = Tile << 5;

		xZoom += 1;
		yZoom += 1;

		y += yOffs;
		y += (64 - yZoom);

		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		for (SpriteChunk = 0; SpriteChunk < 32; SpriteChunk++) {
			k = SpriteChunk % 4;
			j = SpriteChunk / 4;

			px = xFlip ? (3-k) : k;
			py = yFlip ? (7-j) : j;

			Code = SpriteMap[MapOffset + px + (py << 2)];
			Code &= (TaitoZNumSpritesA - 1);

			xCur = x + ((k * xZoom) / 4);
			yCur = y + ((j * yZoom) / 8);

			zx = x + (((k + 1) * xZoom) / 4) - xCur;
			zy = y + (((j + 1) * yZoom) / 8) - yCur;
			
			yCur -= 16;

			RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 13, TaitoZSpritesA);
		}
	}
}

static void SpacegunRenderSprites(int PriorityDraw)
{
	UINT16 *SpriteMap = (UINT16*)TaitoZSpriteMapRom;
	UINT16 *SpriteRam = (UINT16*)TaitoZSpriteRam;
	int Offset, Data, Tile, Colour, xFlip, yFlip;
	int x, y, Priority, xCur, yCur;
	int xZoom, yZoom, zx, zy;
	int SpriteChunk, MapOffset, Code, j, k, px, py;
	
	for (Offset = 0x300 - 4; Offset >= 0; Offset -= 4) {
		Data = SpriteRam[Offset + 1];
		Priority = (Data & 0x8000) >> 15;
		
		if (Priority != 0 && Priority != 1) bprintf(PRINT_NORMAL, _T("Unused Priority %x\n"), Priority);
		if (Priority != PriorityDraw) continue;
		
		xFlip = (Data & 0x4000) >> 14;
		x = Data & 0x1ff;

		Data = SpriteRam[Offset + 3];
		yFlip = (Data & 0x8000) >> 15;
		Tile = Data & 0x1fff;
		if (!Tile) continue;
		
		Data = SpriteRam[Offset + 0];
		yZoom = (Data & 0xfe00) >> 9;
		y = Data & 0x1ff;
		
		Data = SpriteRam[Offset + 2];
		Colour = (Data & 0xff00) >> 8;
		xZoom = (Data & 0x7f);

		MapOffset = Tile << 5;

		xZoom += 1;
		yZoom += 1;

		y += 4;

		if (x > 0x140) x -= 0x200;
		if (y > 0x140) y -= 0x200;
		
		for (SpriteChunk = 0; SpriteChunk < 32; SpriteChunk++) {
			k = SpriteChunk % 4;
			j = SpriteChunk / 4;

			px = xFlip ? (3 - k) : k;
			py = yFlip ? (7 - j) : j;

			Code = SpriteMap[MapOffset + px + (py << 2)];
			Code &= (TaitoZNumSpritesA - 1);			

			xCur = x + ((k * xZoom) / 4);
			yCur = y + ((j * yZoom) / 8);

			zx = x + (((k + 1) * xZoom) / 4) - xCur;
			zy = y + (((j + 1) * yZoom) / 8) - yCur;
			
			yCur -= 16;

			RenderSpriteZoom(Code, xCur, yCur, Colour, xFlip, yFlip, zx << 12, zy << 13, TaitoZSpritesA);
		}

	}
}

static void AquajackDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(1, TaitoZChars);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(1, TaitoZChars);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	AquajackRenderSprites(1);
	
	TC0150RODDraw(-1, 0, 2, 1, 1, 2);
	
	AquajackRenderSprites(0);
	
	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	BurnTransferCopy(TC0110PCRPalette);
}

static void BsharkDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	TaitoZCalcPalette();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(1, TaitoZChars);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(1, TaitoZChars);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	BsharkRenderSprites(1, 8);
	
	TC0150RODDraw(-1, 0xc0, 0, 1, 1, 2);
	
	BsharkRenderSprites(0, 8);
	
	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	BurnTransferCopy(TaitoZPalette);
}

static void ChasehqDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(1, TaitoZChars);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(1, TaitoZChars);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	ChasehqRenderSprites(1);
	
	TC0150RODDraw(-1, 0xc0, 0, 0, 1, 2);
	
	ChasehqRenderSprites(0);
	
	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	BurnTransferCopy(TC0110PCRPalette);
}

static void ContcircDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	ContcircRenderSprites(1, 24);
	
	TC0150RODDraw(-3 + 8, TaitoZRoadPalBank << 6, 1, 0, 1, 2);
	
	ContcircRenderSprites(0, 24);
	
	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	BurnTransferCopy(TC0110PCRPalette);
}

static void DblaxleDraw()
{
	BurnTransferClear();
	TaitoZCalcPalette();
	
	BsharkRenderSprites(1, 7);
	
	TC0150RODDraw(-1, 0xc0, 0, 0, 1, 2);
	
	BsharkRenderSprites(0, 7);
	
	BurnTransferCopy(TaitoZPalette);
}

static void SciDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	TaitoZCalcPalette();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(1, TaitoZChars);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(1, TaitoZChars);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	SciRenderSprites(1, 6);

	TC0150RODDraw(-1, 0xc0, 0, 0, 1, 2);
	
	SciRenderSprites(0, 6);

	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	
	BurnTransferCopy(TaitoZPalette);
}

static void SpacegunDraw()
{
	int Disable = TC0100SCNCtrl[6] & 0xf7;
	
	BurnTransferClear();
	
	if (TC0100SCNBottomLayer()) {
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(1, TaitoZChars);
		SpacegunRenderSprites(1);
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(0, TaitoZChars);
	} else {
		if (!(Disable & 0x01)) TC0100SCNRenderBgLayer(1, TaitoZChars);
		SpacegunRenderSprites(1);
		if (!(Disable & 0x02)) TC0100SCNRenderFgLayer(0, TaitoZChars);
	}
	
	SpacegunRenderSprites(0);
	
	if (!(Disable & 0x04)) TC0100SCNRenderCharLayer();
	BurnTransferCopy(TC0110PCRPalette);
	
	for (int i = 0; i < nBurnGunNumPlayers; i++) {
		BurnGunDrawTarget(i, BurnGunX[i] >> 8, BurnGunY[i] >> 8);
	}
}

static int TaitoZFrame()
{
	int nInterleave = TaitoZFrameInterleave;

	if (TaitoZReset) TaitoZDoReset();

	MakeInputsFunction();
	
	nCyclesDone[0] = nCyclesDone[1] = nCyclesDone[2] = 0;

	SekNewFrame();
	if (TaitoZHasZ80) ZetNewFrame();
		
	for (int i = 0; i < nInterleave; i++) {
		int nCurrentCPU, nNext;

		// Run 68000 #1
		nCurrentCPU = 0;
		SekOpen(0);
		nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
		nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
		nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
		if (i == 10 && Sci && (GetCurrentFrame() & 1)) { SekSetIRQLine(6, SEK_IRQSTATUS_AUTO); nCyclesDone[0] += SekRun(200000 - 500); }
		if (i == (TaitoZFrameInterleave - 1)) SekSetIRQLine(TaitoZVBlankIRQ, SEK_IRQSTATUS_AUTO);
		SekClose();
		
		// Run 68000 #2
		if ((TaitoZCpuACtrl & 0x01) && TaitoZHasZ80) {
			nCurrentCPU = 1;
			SekOpen(1);
			nNext = (i + 1) * nCyclesTotal[nCurrentCPU] / nInterleave;
			nCyclesSegment = nNext - nCyclesDone[nCurrentCPU];
			nCyclesDone[nCurrentCPU] += SekRun(nCyclesSegment);
			if (i == (TaitoZFrameInterleave - 1)) SekSetIRQLine(TaitoZVBlankIRQ, SEK_IRQSTATUS_AUTO);
			SekClose();
		}
	}
	
	if (TaitoZHasZ80) {
		ZetOpen(0);
		BurnTimerEndFrame(nCyclesTotal[2]);
		BurnYM2610Update(pBurnSoundOut, nBurnSoundLen);
		ZetClose();
	} else {
		SekOpen(1);
		if (TaitoZCpuACtrl & 0x01) BurnTimerEndFrame(nCyclesTotal[1]);
		BurnYM2610Update(pBurnSoundOut, nBurnSoundLen);
		if (TaitoZCpuACtrl & 0x01) SekSetIRQLine(TaitoZVBlankIRQ, SEK_IRQSTATUS_AUTO);
		SekClose();
	}
	
	if (pBurnDraw) DrawFunction();

	return 0;
}

static int TaitoZScan(int nAction, int *pnMin)
{
	struct BurnArea ba;
	
	if (pnMin != NULL) {			// Return minimum compatible version
		*pnMin = 0x029674;
	}
	
	if (TaitoZHasEEPROM) EEPROMScan(nAction, pnMin);
	
	if (TaitoZHasTC0150ROD) TC0150RODScan(nAction);
	if (TaitoZHasTC0110PCR) TC0110PCRScan(nAction);
	if (TaitoZHasTC0220IOC) TC0220IOCScan(nAction);
	if (TaitoZHasTC0140SYT) TC0140SYTScan(nAction);
	if (TaitoZHasTC0100SCN) TC0100SCNScan(nAction);

	if (nAction & ACB_MEMORY_RAM) {
		memset(&ba, 0, sizeof(ba));
		ba.Data	  = RamStart;
		ba.nLen	  = RamEnd-RamStart;
		ba.szName = "All Ram";
		BurnAcb(&ba);
	}
	
	if (nAction & ACB_DRIVER_DATA) {
		SekScan(nAction);
		if (TaitoZHasZ80) ZetScan(nAction);

		BurnYM2610Scan(nAction, pnMin);
		
		BurnGunScan();
				
		SCAN_VAR(TaitoZAnalogPort0);
		SCAN_VAR(TaitoZAnalogPort1);
		SCAN_VAR(TaitoZAnalogPort2);
		SCAN_VAR(TaitoZAnalogPort3);
		SCAN_VAR(OldSteer);
		SCAN_VAR(TaitoZCpuACtrl);
		SCAN_VAR(TaitoZZ80Bank);
		SCAN_VAR(SciSpriteFrame);
		SCAN_VAR(TaitoZRoadPalBank);
		SCAN_VAR(nCyclesDone);
		SCAN_VAR(nCyclesSegment);
	}

	return 0;
}

struct BurnDriver BurnDrvAquajack = {
	"aquajack", NULL, NULL, "1990",
	"Aquajack (World)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, AquajackRomInfo, AquajackRomName, AquajackInputInfo, AquajackDIPInfo,
	AquajackInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvAquajckj = {
	"aquajckj", "aquajack", NULL, "1990",
	"Aquajack (Japan)\0", NULL, "Taito Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, AquajckjRomInfo, AquajckjRomName, AquajackInputInfo, AquajckjDIPInfo,
	AquajackInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvBshark = {
	"bshark", NULL, NULL, "1989",
	"Battle Shark (US)\0", NULL, "Taito America Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, BsharkRomInfo, BsharkRomName, BsharkInputInfo, BsharkDIPInfo,
	BsharkInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvBsharkj = {
	"bsharkj", "bshark", NULL, "1989",
	"Battle Shark (Japan)\0", NULL, "Taito Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, BsharkjRomInfo, BsharkjRomName, BsharkInputInfo, BsharkjDIPInfo,
	BsharkInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvChasehq = {
	"chasehq", NULL, NULL, "1988",
	"Chase H.Q. (World)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ChasehqRomInfo, ChasehqRomName, ChasehqInputInfo, ChasehqDIPInfo,
	ChasehqInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvChasehqj = {
	"chasehqj", "chasehq", NULL, "1988",
	"Chase H.Q. (Japan)\0", NULL, "Taito Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ChasehqjRomInfo, ChasehqjRomName, ChasehqInputInfo, ChasehqjDIPInfo,
	ChasehqInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvContcirc = {
	"contcirc", NULL, NULL, "1987",
	"Continental Circus (World)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ContcircRomInfo, ContcircRomName, ContcircInputInfo, ContcircDIPInfo,
	ContcircInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvContcrcu = {
	"contcrcu", "contcirc", NULL, "1987",
	"Continental Circus (US set 1)\0", NULL, "Taito America Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ContcrcuRomInfo, ContcrcuRomName, ContcircInputInfo, ContcrcuDIPInfo,
	ContcircInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvContcrua = {
	"contcrua", "contcirc", NULL, "1987",
	"Continental Circus (US set 2)\0", NULL, "Taito America Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ContcruaRomInfo, ContcruaRomName, ContcircInputInfo, ContcrcuDIPInfo,
	ContcircInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvEnforce = {
	"enforce", NULL, NULL, "1988",
	"Enforce (Japan)\0", NULL, "Taito Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, EnforceRomInfo, EnforceRomName, EnforceInputInfo, EnforceDIPInfo,
	EnforceInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 224, 4, 3
};

struct BurnDriver BurnDrvNightstr = {
	"nightstr", NULL, NULL, "1989",
	"Night Striker (US)\0", NULL, "Taito America Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, NightstrRomInfo, NightstrRomName, NightstrInputInfo, NightstrDIPInfo,
	NightstrInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvSci = {
	"sci", NULL, NULL, "1989",
	"Special Criminal Investigation (World set 1)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, SciRomInfo, SciRomName, SciInputInfo, SciDIPInfo,
	SciInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvScia = {
	"scia", "sci", NULL, "1989",
	"Special Criminal Investigation (World set 2)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, SciaRomInfo, SciaRomName, SciInputInfo, SciDIPInfo,
	SciInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvScij = {
	"scij", "sci", NULL, "1989",
	"Special Criminal Investigation (Japan)\0", NULL, "Taito Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, ScijRomInfo, ScijRomName, SciInputInfo, ScijDIPInfo,
	SciInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvSciu = {
	"sciu", "sci", NULL, "1989",
	"Special Criminal Investigation (US)\0", NULL, "Taito America Corporation", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_TAITO_TAITOZ,
	NULL, SciuRomInfo, SciuRomName, SciInputInfo, SciuDIPInfo,
	SciInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};

struct BurnDriver BurnDrvSpacegun = {
	"spacegun", NULL, NULL, "1990",
	"Space Gun (World)\0", NULL, "Taito Corporation Japan", "Taito-Z",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_TAITO_TAITOZ,
	NULL, SpacegunRomInfo, SpacegunRomName, SpacegunInputInfo, SpacegunDIPInfo,
	SpacegunInit, TaitoZExit, TaitoZFrame, NULL, TaitoZScan,
	NULL, 320, 240, 4, 3
};
