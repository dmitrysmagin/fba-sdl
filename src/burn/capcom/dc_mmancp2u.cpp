// Mega Man - the power battle

#include "cps.h"

static struct BurnInputInfo DrvInputList[] =
{
  {"P1 Coin"       , BIT_DIGITAL, CpsInp020+4, "p1 coin"},
  {"P1 Start"      , BIT_DIGITAL, CpsInp020+0, "p1 start"},
  {"P1 Up"         , BIT_DIGITAL, CpsInp001+3, "p1 up"},
  {"P1 Down"       , BIT_DIGITAL, CpsInp001+2, "p1 down"},
  {"P1 Left"       , BIT_DIGITAL, CpsInp001+1, "p1 left"},
  {"P1 Right"      , BIT_DIGITAL, CpsInp001+0, "p1 right"},
  {"P1 Punch"      , BIT_DIGITAL, CpsInp001+4, "p1 fire 1"},
  {"P1 Kick"       , BIT_DIGITAL, CpsInp001+5, "p1 fire 2"},
  {"P1 Special"    , BIT_DIGITAL, CpsInp001+6, "p1 fire 3"},

  {"P2 Coin"       , BIT_DIGITAL, CpsInp020+5, "p2 coin"},
  {"P2 Start"      , BIT_DIGITAL, CpsInp020+1, "p2 start"},
  {"P2 Up"         , BIT_DIGITAL, CpsInp000+3, "p2 up"},
  {"P2 Down"       , BIT_DIGITAL, CpsInp000+2, "p2 down"},
  {"P2 Left"       , BIT_DIGITAL, CpsInp000+1, "p2 left"},
  {"P2 Right"      , BIT_DIGITAL, CpsInp000+0, "p2 right"},
  {"P2 Punch"      , BIT_DIGITAL, CpsInp000+4, "p2 fire 1"},
  {"P2 Kick"       , BIT_DIGITAL, CpsInp000+5, "p2 fire 2"},
  {"P2 Special"    , BIT_DIGITAL, CpsInp000+6, "p2 fire 3"},

  {"Reset"         , BIT_DIGITAL, &CpsReset   , "reset"},
  {"Diagnostic"    , BIT_DIGITAL, CpsInp021+1, "diag"},
  {"Service"       , BIT_DIGITAL, CpsInp021+2, "service"},
};

STDINPUTINFO(Drv);

static struct BurnRomInfo Mmancp2uRomDesc[] = {
	{ "rcmu.03b",     0x080000, 0xc39f037f, 1 | BRF_ESS | BRF_PRG },
	{ "rcmu.04b",     0x080000, 0xcd6f5e99, 1 | BRF_ESS | BRF_PRG },
	{ "rcm.05b",      0x080000, 0x4376ea95, 1 | BRF_ESS | BRF_PRG },

	{ "rcm.73",       0x080000, 0x774c6e04, 3 | BRF_GRA },
	{ "rcm.63",       0x080000, 0xacad7c62, 3 | BRF_GRA },
	{ "rcm.83",       0x080000, 0x6af30499, 3 | BRF_GRA },
	{ "rcm.93",       0x080000, 0x7a5a5166, 3 | BRF_GRA },
	{ "rcm.74",       0x080000, 0x004ec725, 3 | BRF_GRA },
	{ "rcm.64",       0x080000, 0x65c0464e, 3 | BRF_GRA },
	{ "rcm.84",       0x080000, 0xfb3097cc, 3 | BRF_GRA },
	{ "rcm.94",       0x080000, 0x2e16557a, 3 | BRF_GRA },
	{ "rcm.75",       0x080000, 0x70a73f99, 3 | BRF_GRA },
	{ "rcm.65",       0x080000, 0xecedad3d, 3 | BRF_GRA },
	{ "rcm.85",       0x080000, 0x3d6186d8, 3 | BRF_GRA },
	{ "rcm.95",       0x080000, 0x8c7700f1, 3 | BRF_GRA },
	{ "rcm.76",       0x080000, 0x89a889ad, 3 | BRF_GRA },
	{ "rcm.66",       0x080000, 0x1300eb7b, 3 | BRF_GRA },
	{ "rcm.86",       0x080000, 0x6d974ebd, 3 | BRF_GRA },
	{ "rcm.96",       0x080000, 0x7da4cd24, 3 | BRF_GRA },

	{ "rcm.01",       0x020000, 0xd60cf8a3, 4 | BRF_ESS | BRF_PRG },

	{ "rcm.51",       0x080000, 0xb6d07080, 5 | BRF_SND },
	{ "rcm.52",       0x080000, 0xdfddc493, 5 | BRF_SND },
	{ "rcm.53",       0x080000, 0x6062ae3a, 5 | BRF_SND },
	{ "rcm.54",       0x080000, 0x08c6f3bf, 5 | BRF_SND },
	{ "rcm.55",       0x080000, 0xf97dfccc, 5 | BRF_SND },
	{ "rcm.56",       0x080000, 0xade475bc, 5 | BRF_SND },
	{ "rcm.57",       0x080000, 0x075effb3, 5 | BRF_SND },
	{ "rcm.58",       0x080000, 0xf6c1f87b, 5 | BRF_SND },
};


STD_ROM_PICK(Mmancp2u) STD_ROM_FN(Mmancp2u)

static struct BurnRomInfo Rmancp2jRomDesc[] = {
	{ "rcmj.03a",     0x080000, 0x30559f60, 1 | BRF_ESS | BRF_PRG },
	{ "rcmj.04a",     0x080000, 0x5efc9366, 1 | BRF_ESS | BRF_PRG },
	{ "rcm.05a",      0x080000, 0x517ccde2, 1 | BRF_ESS | BRF_PRG },

	{ "rcm.73",       0x080000, 0x774c6e04, 3 | BRF_GRA },
	{ "rcm.63",       0x080000, 0xacad7c62, 3 | BRF_GRA },
	{ "rcm.83",       0x080000, 0x6af30499, 3 | BRF_GRA },
	{ "rcm.93",       0x080000, 0x7a5a5166, 3 | BRF_GRA },
	{ "rcm.74",       0x080000, 0x004ec725, 3 | BRF_GRA },
	{ "rcm.64",       0x080000, 0x65c0464e, 3 | BRF_GRA },
	{ "rcm.84",       0x080000, 0xfb3097cc, 3 | BRF_GRA },
	{ "rcm.94",       0x080000, 0x2e16557a, 3 | BRF_GRA },
	{ "rcm.75",       0x080000, 0x70a73f99, 3 | BRF_GRA },
	{ "rcm.65",       0x080000, 0xecedad3d, 3 | BRF_GRA },
	{ "rcm.85",       0x080000, 0x3d6186d8, 3 | BRF_GRA },
	{ "rcm.95",       0x080000, 0x8c7700f1, 3 | BRF_GRA },
	{ "rcm.76",       0x080000, 0x89a889ad, 3 | BRF_GRA },
	{ "rcm.66",       0x080000, 0x1300eb7b, 3 | BRF_GRA },
	{ "rcm.86",       0x080000, 0x6d974ebd, 3 | BRF_GRA },
	{ "rcm.96",       0x080000, 0x7da4cd24, 3 | BRF_GRA },

	{ "rcm.01",       0x020000, 0xd60cf8a3, 4 | BRF_ESS | BRF_PRG },

	{ "rcm.51",       0x080000, 0xb6d07080, 5 | BRF_SND },
	{ "rcm.52",       0x080000, 0xdfddc493, 5 | BRF_SND },
	{ "rcm.53",       0x080000, 0x6062ae3a, 5 | BRF_SND },
	{ "rcm.54",       0x080000, 0x08c6f3bf, 5 | BRF_SND },
	{ "rcm.55",       0x080000, 0xf97dfccc, 5 | BRF_SND },
	{ "rcm.56",       0x080000, 0xade475bc, 5 | BRF_SND },
	{ "rcm.57",       0x080000, 0x075effb3, 5 | BRF_SND },
	{ "rcm.58",       0x080000, 0xf6c1f87b, 5 | BRF_SND },
};


STD_ROM_PICK(Rmancp2j) STD_ROM_FN(Rmancp2j)

struct BurnDriver BurnDrvCpsMmancp2u = {
	"mmancp2u", "megaman", NULL, "1999",
	"Mega Man - The Power Battle (951006 USA, SAMPLE Version)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Mmancp2uRomInfo, Mmancp2uRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};

struct BurnDriver BurnDrvCpsRmancp2j = {
	"rmancp2j", "mmancp2u", NULL, "1999",
	"Rockman: The Power Battle (950922 Japan)\0", NULL, "Capcom", "CPS2",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_CAPCOM_CPS2,
	NULL, Rmancp2jRomInfo, Rmancp2jRomName, DrvInputInfo, NULL,
	Cps2Init, CpsExit,Cps2Frame,CpsRedraw,CpsAreaScan,
	&CpsRecalcPal,384,224,4,3
};
