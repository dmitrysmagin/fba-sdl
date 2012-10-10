#include "megadrive.h"
#include "burnint.h"

static struct BurnInputInfo MegadriveInputList[] = {
	{"P1 Start",	  BIT_DIGITAL,   MegadriveJoy1 +  7, "p1 start"  },
	{"P1 Up",	  BIT_DIGITAL,   MegadriveJoy1 +  0, "p1 up"     },
	{"P1 Down",	  BIT_DIGITAL,   MegadriveJoy1 +  1, "p1 down"   },
	{"P1 Left",	  BIT_DIGITAL,   MegadriveJoy1 +  2, "p1 left"   },
	{"P1 Right",	  BIT_DIGITAL,   MegadriveJoy1 +  3, "p1 right"  },
	{"P1 Button A",	  BIT_DIGITAL,   MegadriveJoy1 +  6, "p1 fire 1" },
	{"P1 Button B",	  BIT_DIGITAL,   MegadriveJoy1 +  4, "p1 fire 2" },
	{"P1 Button C",	  BIT_DIGITAL,   MegadriveJoy1 +  5, "p1 fire 3" },
	{"P1 Button X",	  BIT_DIGITAL,   MegadriveJoy1 + 10, "p1 fire 4" },
	{"P1 Button Y",	  BIT_DIGITAL,   MegadriveJoy1 +  9, "p1 fire 5" },
	{"P1 Button Z",	  BIT_DIGITAL,   MegadriveJoy1 +  8, "p1 fire 6" },
	{"P1 Mode",	  BIT_DIGITAL,   MegadriveJoy1 + 11, "p1 select" },

	{"P2 Start",	  BIT_DIGITAL,   MegadriveJoy2 +  7, "p2 start"  },
	{"P2 Up",	  BIT_DIGITAL,   MegadriveJoy2 +  0, "p2 up"     },
	{"P2 Down",	  BIT_DIGITAL,   MegadriveJoy2 +  1, "p2 down"   },
	{"P2 Left",	  BIT_DIGITAL,   MegadriveJoy2 +  2, "p2 left"   },
	{"P2 Right",	  BIT_DIGITAL,   MegadriveJoy2 +  3, "p2 right"  },
	{"P2 Button A",	  BIT_DIGITAL,   MegadriveJoy2 +  6, "p2 fire 1" },
	{"P2 Button B",	  BIT_DIGITAL,   MegadriveJoy2 +  4, "p2 fire 2" },
	{"P2 Button C",	  BIT_DIGITAL,   MegadriveJoy2 +  5, "p2 fire 3" },
	{"P2 Button X",	  BIT_DIGITAL,   MegadriveJoy2 + 10, "p2 fire 4" },
	{"P2 Button Y",	  BIT_DIGITAL,   MegadriveJoy2 +  9, "p2 fire 5" },
	{"P2 Button Z",	  BIT_DIGITAL,   MegadriveJoy2 +  8, "p2 fire 6" },
	{"P2 Mode",	  BIT_DIGITAL,   MegadriveJoy2 + 11, "p2 select" },
	
	{"Reset",	  BIT_DIGITAL,   &MegadriveReset,     "reset"    },
	{"Dip A",	  BIT_DIPSWITCH, MegadriveDIP  + 0,   "dip"      },
	{"Dip B",	  BIT_DIPSWITCH, MegadriveDIP  + 1,   "dip"      },
};

STDINPUTINFO(Megadrive);

static struct BurnDIPInfo MegadriveDIPList[] = {

	{0x19,	0xFF, 0xFF, 0x21,  NULL               },	// Default Auto-Detect and No-CDROM
	{0x1a,	0xFF, 0xFF, 0x01,  NULL               },

	{0,	0xFE, 0,       5, "Hardware"          },
	{0x19,	0x01, 0xC1, 0x01, "Auto Detect"       },
	{0x19,	0x01, 0xC1, 0x00, "Japan NTSC"        },
	{0x19,	0x01, 0xC1, 0x40, "Japan PAL"         },
	{0x19,	0x01, 0xC1, 0x80, "USA"               },
	{0x19,	0x01, 0xC1, 0xC0, "Europe"            },

	{0,	0xFE, 0,       2, "CD-ROM"            },
	{0x19,	0x01, 0x20, 0x20, "No"                },
	{0x19,	0x01, 0x20, 0x00, "Yes"               },

	{0,	0xFE, 0,       3, "32-Col Mode Draw"  },
	{0x1a,	0x01, 0x03, 0x00, "No Change"         },
	{0x1a,	0x01, 0x03, 0x01, "Center"            },
	{0x1a,	0x01, 0x03, 0x02, "Inner Zoom"        },
};

STDDIPINFO(Megadrive);

// NHL 94 (UE) [!]

static struct BurnRomInfo nh94RomDesc[]={
	{ "nhl94 hl9402", 0x100000, 0xACECD225, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh94);
STD_ROM_FN(nh94);

struct BurnDriverD BurnDrvMDnh94 = {
	"g_nh94", NULL, NULL, "1900",
	"NHL 94 (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh94RomInfo, nh94RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveNoByteswapInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Pond II - Codename RoboCod (UE) [!]

static struct BurnRomInfo jp2RomDesc[]={
	{ "pond ii robocod rob02", 0x080000, 0xC32B5D66, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jp2);
STD_ROM_FN(jp2);

struct BurnDriver BurnDrvMDjp2 = {
	"g_jp2", NULL, NULL, "1991",
	"James Pond II - Codename RoboCod (UE) [!]\0", NULL, "Electronic Arts / Millenium", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jp2RomInfo, jp2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveNoByteswapInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Block Out (W) (REV01) [!]

static struct BurnRomInfo blocRomDesc[]={
	{ "g_bloc.bin", 0x020000, 0x5E2966F1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bloc);
STD_ROM_FN(bloc);

struct BurnDriver BurnDrvMDbloc = {
	"g_bloc", NULL, NULL, "1994",
	"Block Out (W) (REV01) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blocRomInfo, blocRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Columns (W) (REV01) [!]

static struct BurnRomInfo colRomDesc[]={
	{ "g_col.bin", 0x020000, 0xD783C244, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(col);
STD_ROM_FN(col);

struct BurnDriverD BurnDrvMDcol = {
	"g_col", NULL, NULL, "1994",
	"Columns (W) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, colRomInfo, colRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pac-Attack (U) [!]

static struct BurnRomInfo pacaRomDesc[]={
	{ "g_paca.bin", 0x040000, 0x5DF382F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(paca);
STD_ROM_FN(paca);

struct BurnDriverD BurnDrvMDpaca = {
	"g_paca", NULL, NULL, "1900",
	"Pac-Attack (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pacaRomInfo, pacaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lemmings (JU) (REV01) [!]

static struct BurnRomInfo lemRomDesc[]={
	{ "g_lem.bin", 0x100000, 0x68C70362, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lem);
STD_ROM_FN(lem);

struct BurnDriverD BurnDrvMDlem = {
	"g_lem", NULL, NULL, "1992",
	"Lemmings (JU) (REV01) [!]\0", NULL, "Psygnosis / Sunsoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lemRomInfo, lemRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gunstar Heroes (U) [!]

static struct BurnRomInfo gshRomDesc[]={
	{ "g_gsh.bin", 0x100000, 0xB813CF0D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gsh);
STD_ROM_FN(gsh);

struct BurnDriverD BurnDrvMDgsh = {
	"g_gsh", NULL, NULL, "1993",
	"Gunstar Heroes (U) [!]\0", NULL, "Sega / Treasure", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gshRomInfo, gshRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Force IV (J) [!]

static struct BurnRomInfo tf4RomDesc[]={
	{ "g_tf4.bin", 0x100000, 0x8D606480, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tf4);
STD_ROM_FN(tf4);

struct BurnDriverD BurnDrvMDtf4 = {
	"g_tf4", NULL, NULL, "1992",
	"Thunder Force IV (J) [!]\0", NULL, "Tecnosoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tf4RomInfo, tf4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World of Illusion Starring Mickey Mouse & Donald Duck (U) [!]

static struct BurnRomInfo willRomDesc[]={
	{ "g_will.bin", 0x100000, 0x921EBD1C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(will);
STD_ROM_FN(will);

struct BurnDriverD BurnDrvMDwill = {
	"g_will", NULL, NULL, "1992",
	"World of Illusion Starring Mickey Mouse & Donald Duck (U) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, willRomInfo, willRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl (U) (REV00) [!]

static struct BurnRomInfo tjeRomDesc[]={
	{ "g_tje.bin", 0x100000, 0x7A588F4B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje);
STD_ROM_FN(tje);

struct BurnDriver BurnDrvMDtje = {
	"g_tje", "g_tje00", NULL, "1991",
	"Toejam & Earl (U) (REV00) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tjeRomInfo, tjeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Rash (UE) [c][!]

static struct BurnRomInfo rrshRomDesc[]={
	{ "g_rrsh.bin", 0x0C0000, 0xDEA53D19, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrsh);
STD_ROM_FN(rrsh);

struct BurnDriverD BurnDrvMDrrsh = {
	"g_rrsh", NULL, NULL, "1991",
	"Road Rash (UE) [c][!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrshRomInfo, rrshRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Doki Doki Penguin Land MD (SN) (J) [!]

static struct BurnRomInfo ddplRomDesc[]={
	{ "g_ddpl.bin", 0x040000, 0x0053BFD6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddpl);
STD_ROM_FN(ddpl);

struct BurnDriverD BurnDrvMDddpl = {
	"g_ddpl", NULL, NULL, "1994",
	"Doki Doki Penguin Land MD (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddplRomInfo, ddplRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog (W) (REV01) [!]

static struct BurnRomInfo soniRomDesc[]={
	{ "g_soni.bin", 0x080000, 0xAFE05EEE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soni);
STD_ROM_FN(soni);

struct BurnDriver BurnDrvMDsoni = {
	"g_soni", NULL, NULL, "1991",
	"Sonic The Hedgehog (W) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soniRomInfo, soniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 2 (W) (REV01) [!]

static struct BurnRomInfo son2RomDesc[]={
	{ "g_son2.bin", 0x100000, 0x7B905383, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son2);
STD_ROM_FN(son2);

struct BurnDriver BurnDrvMDson2 = {
	"g_son2", NULL, NULL, "1992",
	"Sonic The Hedgehog 2 (W) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son2RomInfo, son2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 2 (W) (REVSC02)

static struct BurnRomInfo son2aRomDesc[]={
	{ "g_son2a.bin", 0x100000, 0xF23AD4B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son2a);
STD_ROM_FN(son2a);

struct BurnDriver BurnDrvMDson2a = {
	"g_son2a", "g_son2", NULL, "1992",
	"Sonic The Hedgehog 2 (W) (REVSC02)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son2aRomInfo, son2aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 3 (U) [!]

static struct BurnRomInfo son3RomDesc[]={
	{ "g_son3.bin", 0x200000, 0x9BC192CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son3);
STD_ROM_FN(son3);

struct BurnDriver BurnDrvMDson3 = {
	"g_son3", NULL, NULL, "1994",
	"Sonic The Hedgehog 3 (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son3RomInfo, son3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Spinball (U) [!]

static struct BurnRomInfo sonsRomDesc[]={
	{ "g_sons.bin", 0x100000, 0x677206CB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sons);
STD_ROM_FN(sons);

struct BurnDriverD BurnDrvMDsons = {
	"g_sons", NULL, NULL, "1993",
	"Sonic Spinball (U) [!]\0", "No sound in-game", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sonsRomInfo, sonsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wani Wani World (J) [c][!]

static struct BurnRomInfo waniRomDesc[]={
	{ "g_wani.bin", 0x080000, 0x56F0DBB2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wani);
STD_ROM_FN(wani);

struct BurnDriverD BurnDrvMDwani = {
	"g_wani", NULL, NULL, "1992",
	"Wani Wani World (J) [c][!]\0", NULL, "Kaneko", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, waniRomInfo, waniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wild Snake (U) (Prototype) [!]

static struct BurnRomInfo wildRomDesc[]={
	{ "g_wild.bin", 0x080000, 0x0C1A49E5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wild);
STD_ROM_FN(wild);

struct BurnDriverD BurnDrvMDwild = {
	"g_wild", NULL, NULL, "1994",
	"Wild Snake (U) (Prototype) [!]\0", NULL, "Bullet-Proof Software", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wildRomInfo, wildRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Castle of Illusion Starring Mickey Mouse (UE) [!]

static struct BurnRomInfo cillRomDesc[]={
	{ "g_cill.bin", 0x080000, 0xBA4E9FD0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cill);
STD_ROM_FN(cill);

struct BurnDriverD BurnDrvMDcill = {
	"g_cill", NULL, NULL, "1990",
	"Castle of Illusion Starring Mickey Mouse (UE) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cillRomInfo, cillRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Pond 3 - Operation Starfish (UE) [!]

static struct BurnRomInfo jp3RomDesc[]={
	{ "g_jp3.bin", 0x200000, 0x26F64B2A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jp3);
STD_ROM_FN(jp3);

struct BurnDriver BurnDrvMDjp3 = {
	"g_jp3", NULL, NULL, "1993",
	"James Pond 3 - Operation Starfish (UE) [!]\0", NULL, "Electronic Arts / Vectordean / Millenium", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jp3RomInfo, jp3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Adventures of Batman and Robi

static struct BurnRomInfo abatRomDesc[]={
	{ "g_abat.bin", 0x200000, 0x0CAAA4AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abat);
STD_ROM_FN(abat);

struct BurnDriverD BurnDrvMDabat = {
	"g_abat", NULL, NULL, "1995",
	"Adventures of Batman and Robi\0", "No sound", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abatRomInfo, abatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Earthworm Jim 2 (U) [!]

static struct BurnRomInfo jim2RomDesc[]={
	{ "g_jim2.bin", 0x300000, 0xD57F8BA7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jim2);
STD_ROM_FN(jim2);

struct BurnDriverD BurnDrvMDjim2 = {
	"g_jim2", NULL, NULL, "1900",
	"Earthworm Jim 2 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jim2RomInfo, jim2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Animaniacs (U) [!]

static struct BurnRomInfo animRomDesc[]={
	{ "g_anim.bin", 0x100000, 0x86224D86, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(anim);
STD_ROM_FN(anim);

struct BurnDriverD BurnDrvMDanim = {
	"g_anim", NULL, NULL, "1900",
	"Animaniacs (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, animRomInfo, animRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gley Lancer (J)

static struct BurnRomInfo gleyRomDesc[]={
	{ "g_gley.bin", 0x100000, 0x42CF9B5B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gley);
STD_ROM_FN(gley);

struct BurnDriverD BurnDrvMDgley = {
	"g_gley", NULL, NULL, "1900",
	"Gley Lancer (J)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gleyRomInfo, gleyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ristar (UE) [!]

static struct BurnRomInfo ristRomDesc[]={
	{ "g_rist.bin", 0x200000, 0x6511AA61, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rist);
STD_ROM_FN(rist);

struct BurnDriverD BurnDrvMDrist = {
	"g_rist", NULL, NULL, "1900",
	"Ristar (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ristRomInfo, ristRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rocket Knight Adventures (U) [!]

static struct BurnRomInfo rkniRomDesc[]={
	{ "g_rkni.bin", 0x100000, 0xA6EFEC47, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rkni);
STD_ROM_FN(rkni);

struct BurnDriverD BurnDrvMDrkni = {
	"g_rkni", NULL, NULL, "1900",
	"Rocket Knight Adventures (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rkniRomInfo, rkniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Snake Rattle 'n' Roll (E) [c][!]

static struct BurnRomInfo srrRomDesc[]={
	{ "g_srr.bin", 0x080000, 0x543BED30, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(srr);
STD_ROM_FN(srr);

struct BurnDriverD BurnDrvMDsrr = {
	"g_srr", NULL, NULL, "1900",
	"Snake Rattle 'n' Roll (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, srrRomInfo, srrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Taz-Mania (W) [!]

static struct BurnRomInfo tazmRomDesc[]={
	{ "g_tazm.bin", 0x080000, 0x0E901F45, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tazm);
STD_ROM_FN(tazm);

struct BurnDriver BurnDrvMDtazm = {
	"g_tazm", NULL, NULL, "1900",
	"Taz-Mania (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tazmRomInfo, tazmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse 3 (U) [c][!]

static struct BurnRomInfo spl3RomDesc[]={
	{ "g_spl3.bin", 0x200000, 0x00F05D07, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spl3);
STD_ROM_FN(spl3);

struct BurnDriverD BurnDrvMDspl3 = {
	"g_spl3", NULL, NULL, "1900",
	"Splatterhouse 3 (U) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spl3RomInfo, spl3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mortal Kombat (UE) (REV01) [c][!]

static struct BurnRomInfo mkRomDesc[]={
	{ "g_mk.bin", 0x200000, 0x33F19AB6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mk);
STD_ROM_FN(mk);

struct BurnDriverD BurnDrvMDmk = {
	"g_mk", NULL, NULL, "1900",
	"Mortal Kombat (UE) (REV01) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mkRomInfo, mkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Comix Zone (U) [!]

static struct BurnRomInfo comxRomDesc[]={
	{ "g_comx.bin", 0x200000, 0x17DA0354, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comx);
STD_ROM_FN(comx);

struct BurnDriverD BurnDrvMDcomx = {
	"g_comx", NULL, NULL, "1995",
	"Comix Zone (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comxRomInfo, comxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cosmic Spacehead (E) (M4) [c][!]

static struct BurnRomInfo cossRomDesc[]={
	{ "g_coss.bin", 0x100000, 0xC593D31C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(coss);
STD_ROM_FN(coss);

struct BurnDriverD BurnDrvMDcoss = {
	"g_coss", NULL, NULL, "1900",
	"Cosmic Spacehead (E) (M4) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cossRomInfo, cossRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dino Dini's Soccer (E)

static struct BurnRomInfo dinoRomDesc[]={
	{ "g_dino.bin", 0x100000, 0x4608F53A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dino);
STD_ROM_FN(dino);

struct BurnDriverD BurnDrvMDdino = {
	"g_dino", NULL, NULL, "1994",
	"Dino Dini's Soccer (E)\0", NULL, "Dino Dini / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dinoRomInfo, dinoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jungle Boo

static struct BurnRomInfo jbokRomDesc[]={
	{ "g_jbok.bin", 0x200000, 0x3FB6D92E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jbok);
STD_ROM_FN(jbok);

struct BurnDriverD BurnDrvMDjbok = {
	"g_jbok", NULL, NULL, "1900",
	"Jungle Boo\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jbokRomInfo, jbokRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fantasia (JU) (REV01) [!]

static struct BurnRomInfo fantRomDesc[]={
	{ "g_fant.bin", 0x080000, 0xFC43DF2D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fant);
STD_ROM_FN(fant);

struct BurnDriverD BurnDrvMDfant = {
	"g_fant", NULL, NULL, "1900",
	"Fantasia (JU) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fantRomInfo, fantRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Decap Attack (UE) [!]

static struct BurnRomInfo dcapRomDesc[]={
	{ "g_dcap.bin", 0x080000, 0x73DC0DD8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dcap);
STD_ROM_FN(dcap);

struct BurnDriverD BurnDrvMDdcap = {
	"g_dcap", NULL, NULL, "1900",
	"Decap Attack (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dcapRomInfo, dcapRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pirates! Gold (U) [!]

static struct BurnRomInfo pirgRomDesc[]={
	{ "g_pirg.bin", 0x100000, 0xED50E75C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pirg);
STD_ROM_FN(pirg);

struct BurnDriverD BurnDrvMDpirg = {
	"g_pirg", NULL, NULL, "1900",
	"Pirates! Gold (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pirgRomInfo, pirgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gauntlet 4 (UE) (Aug 1993) [!]

static struct BurnRomInfo gau4RomDesc[]={
	{ "g_gau4.bin", 0x100000, 0x3BF46DCE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gau4);
STD_ROM_FN(gau4);

struct BurnDriverD BurnDrvMDgau4 = {
	"g_gau4", NULL, NULL, "1994",
	"Gauntlet 4 (UE) (Aug 1993) [!]\0", NULL, "Tengen / Atari", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gau4RomInfo, gau4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hard Drivin' (W) [!]

static struct BurnRomInfo hardRomDesc[]={
	{ "g_hard.bin", 0x040000, 0x3225BAAF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hard);
STD_ROM_FN(hard);

struct BurnDriverD BurnDrvMDhard = {
	"g_hard", NULL, NULL, "1990",
	"Hard Drivin' (W) [!]\0", NULL, "Tengen / Atari", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hardRomInfo, hardRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kawasaki Superbike Challenge (UE) [!]

static struct BurnRomInfo kawaRomDesc[]={
	{ "g_kawa.bin", 0x100000, 0x631CC8E9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kawa);
STD_ROM_FN(kawa);

struct BurnDriverD BurnDrvMDkawa = {
	"g_kawa", NULL, NULL, "1900",
	"Kawasaki Superbike Challenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kawaRomInfo, kawaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park 2 - The Lost World (U) [!]

static struct BurnRomInfo jpa2RomDesc[]={
	{ "g_jpa2.bin", 0x400000, 0x140A284C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jpa2);
STD_ROM_FN(jpa2);

struct BurnDriverD BurnDrvMDjpa2 = {
	"g_jpa2", NULL, NULL, "1998",
	"Jurassic Park 2 - The Lost World (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jpa2RomInfo, jpa2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toy Story (U) [!]

static struct BurnRomInfo toyRomDesc[]={
	{ "g_toy.bin", 0x400000, 0x829FE313, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toy);
STD_ROM_FN(toy);

struct BurnDriverD BurnDrvMDtoy = {
	"g_toy", NULL, NULL, "1900",
	"Toy Story (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toyRomInfo, toyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Quack Shot Starring Donald Duck (W) (REV01) [!]

static struct BurnRomInfo quacRomDesc[]={
	{ "g_quac.bin", 0x140000, 0x1801098B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(quac);
STD_ROM_FN(quac);

struct BurnDriverD BurnDrvMDquac = {
	"g_quac", NULL, NULL, "1991",
	"Quack Shot Starring Donald Duck (W) (REV01) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, quacRomInfo, quacRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jim Power - The Arcade Game (Beta)

static struct BurnRomInfo jimpRomDesc[]={
	{ "g_jimp.bin", 0x100000, 0x1CF3238B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jimp);
STD_ROM_FN(jimp);

struct BurnDriverD BurnDrvMDjimp = {
	"g_jimp", NULL, NULL, "1900",
	"Jim Power - The Arcade Game (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jimpRomInfo, jimpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vectorman 2 (U) [!]

static struct BurnRomInfo vec2RomDesc[]={
	{ "g_vec2.bin", 0x300000, 0xC1A24088, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vec2);
STD_ROM_FN(vec2);

struct BurnDriverD BurnDrvMDvec2 = {
	"g_vec2", NULL, NULL, "1996",
	"Vectorman 2 (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vec2RomInfo, vec2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Charles' Window Bug Example

static struct BurnRomInfo wbugRomDesc[]={
	{ "g_wbug.bin", 0x004000, 0x75582DDB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wbug);
STD_ROM_FN(wbug);

struct BurnDriverD BurnDrvMDwbug = {
	"g_wbug", NULL, NULL, "1900",
	"Charles' Window Bug Example\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wbugRomInfo, wbugRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Raiden Trad (JU) [!]

static struct BurnRomInfo raidRomDesc[]={
	{ "g_raid.bin", 0x100000, 0xF839A811, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(raid);
STD_ROM_FN(raid);

struct BurnDriverD BurnDrvMDraid = {
	"g_raid", NULL, NULL, "1900",
	"Raiden Trad (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, raidRomInfo, raidRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Journey From Darkness - Strider Returns (U) [c][!]

static struct BurnRomInfo str2RomDesc[]={
	{ "g_str2.bin", 0x100000, 0x42589B79, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(str2);
STD_ROM_FN(str2);

struct BurnDriverD BurnDrvMDstr2 = {
	"g_str2", NULL, NULL, "1994",
	"Journey From Darkness - Strider Returns (U) [c][!]\0", NULL, "Tiertex / Capcom / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, str2RomInfo, str2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Galaxy Force II (W) (REV01) [!]

static struct BurnRomInfo gf2RomDesc[]={
	{ "g_gf2.bin", 0x100000, 0xD15F5C3C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gf2);
STD_ROM_FN(gf2);

struct BurnDriverD BurnDrvMDgf2 = {
	"g_gf2", NULL, NULL, "1900",
	"Galaxy Force II (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gf2RomInfo, gf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines (UE) [c][!]

static struct BurnRomInfo micRomDesc[]={
	{ "g_mic.bin", 0x080000, 0x7FFBD1AD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mic);
STD_ROM_FN(mic);

struct BurnDriver BurnDrvMDmic = {
	"g_mic", NULL, NULL, "1990",
	"Micro Machines (UE) [c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micRomInfo, micRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines (UE) [a1][c][!]

static struct BurnRomInfo micaRomDesc[]={
	{ "g_mica.bin", 0x080000, 0xE5CF560D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mica);
STD_ROM_FN(mica);

struct BurnDriver BurnDrvMDmica = {
	"g_mica", "g_mic", NULL, "1993",
	"Micro Machines (UE) [a1][c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micaRomInfo, micaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines 2 - Turbo Tournament (E) [c][!]

static struct BurnRomInfo mic2RomDesc[]={
	{ "g_mic2.bin", 0x100000, 0x01C22A5D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mic2);
STD_ROM_FN(mic2);

struct BurnDriverD BurnDrvMDmic2 = {
	"g_mic2", NULL, NULL, "1994",
	"Micro Machines 2 - Turbo Tournament (E) [c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mic2RomInfo, mic2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines - Turbo Tournament '96 (V1.1) (E) (J-Cart) [c][!]

static struct BurnRomInfo mic9RomDesc[]={
	{ "g_mic9.bin", 0x100000, 0x23319D0D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mic9);
STD_ROM_FN(mic9);

struct BurnDriverD BurnDrvMDmic9 = {
	"g_mic9", NULL, NULL, "1995",
	"Micro Machines - Turbo Tournament '96 (V1.1) (E) (J-Cart) [c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mic9RomInfo, mic9RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mick & Mack as the Global Gladiators (E) [!]

static struct BurnRomInfo micmRomDesc[]={
	{ "g_micm.bin", 0x100000, 0xB3ABB15E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micm);
STD_ROM_FN(micm);

struct BurnDriverD BurnDrvMDmicm = {
	"g_micm", NULL, NULL, "1994",
	"Mick & Mack as the Global Gladiators (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micmRomInfo, micmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines Military - It's a Blast! (E) [x]

static struct BurnRomInfo mimmxRomDesc[]={
	{ "g_mimmx.bin", 0x100000, 0xA1AD9F97, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mimmx);
STD_ROM_FN(mimmx);

struct BurnDriverD BurnDrvMDmimmx = {
	"g_mimmx", NULL, NULL, "1996",
	"Micro Machines Military - It's a Blast! (E) [x]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mimmxRomInfo, mimmxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Adventures of Mighty Ma

static struct BurnRomInfo mmaxRomDesc[]={
	{ "g_mmax.bin", 0x100000, 0x55F13A00, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmax);
STD_ROM_FN(mmax);

struct BurnDriverD BurnDrvMDmmax = {
	"g_mmax", NULL, NULL, "1900",
	"Adventures of Mighty Ma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmaxRomInfo, mmaxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Castlevania - Bloodlines (U) [!]

static struct BurnRomInfo casvRomDesc[]={
	{ "g_casv.bin", 0x100000, 0xFB1EA6DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(casv);
STD_ROM_FN(casv);

struct BurnDriverD BurnDrvMDcasv = {
	"g_casv", NULL, NULL, "1994",
	"Castlevania - Bloodlines (U) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, casvRomInfo, casvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alien Soldier (J) [!]

static struct BurnRomInfo asolRomDesc[]={
	{ "g_asol.bin", 0x200000, 0x90FA1539, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(asol);
STD_ROM_FN(asol);

struct BurnDriver BurnDrvMDasol = {
	"g_asol", NULL, NULL, "1900",
	"Alien Soldier (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, asolRomInfo, asolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dynamite Headdy (UE) [c][!]

static struct BurnRomInfo dhedRomDesc[]={
	{ "g_dhed.bin", 0x200000, 0x3DFEEB77, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dhed);
STD_ROM_FN(dhed);

struct BurnDriverD BurnDrvMDdhed = {
	"g_dhed", NULL, NULL, "1900",
	"Dynamite Headdy (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dhedRomInfo, dhedRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA Soccer 98 - Road to the World Cup (E) (M5) [!]

static struct BurnRomInfo f98RomDesc[]={
	{ "g_f98.bin", 0x200000, 0x96947F57, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f98);
STD_ROM_FN(f98);

struct BurnDriverD BurnDrvMDf98 = {
	"g_f98", NULL, NULL, "1900",
	"FIFA Soccer 98 - Road to the World Cup (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f98RomInfo, f98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Contra - Hard Corps (U) [!]

static struct BurnRomInfo contRomDesc[]={
	{ "g_cont.bin", 0x200000, 0xC579F45E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cont);
STD_ROM_FN(cont);

struct BurnDriverD BurnDrvMDcont = {
	"g_cont", NULL, NULL, "1994",
	"Contra - Hard Corps (U) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, contRomInfo, contRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dashin' Desperadoes (U) [!]

static struct BurnRomInfo dashRomDesc[]={
	{ "g_dash.bin", 0x100000, 0xDCB76FB7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dash);
STD_ROM_FN(dash);

struct BurnDriverD BurnDrvMDdash = {
	"g_dash", NULL, NULL, "1900",
	"Dashin' Desperadoes (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dashRomInfo, dashRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Donald in Maui Mallard (E) [!]

static struct BurnRomInfo mauiRomDesc[]={
	{ "g_maui.bin", 0x300000, 0xB2DD857F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(maui);
STD_ROM_FN(maui);

struct BurnDriverD BurnDrvMDmaui = {
	"g_maui", NULL, NULL, "1900",
	"Donald in Maui Mallard (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mauiRomInfo, mauiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Great Circus Myster

static struct BurnRomInfo gcmRomDesc[]={
	{ "g_gcm.bin", 0x200000, 0x14744883, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gcm);
STD_ROM_FN(gcm);

struct BurnDriverD BurnDrvMDgcm = {
	"g_gcm", NULL, NULL, "1994",
	"Great Circus Myster\0", NULL, "Disney / Capcom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gcmRomInfo, gcmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// International Superstar Soccer Deluxe (E) [!]

static struct BurnRomInfo issRomDesc[]={
	{ "g_iss.bin", 0x200000, 0x9BB3B180, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(iss);
STD_ROM_FN(iss);

struct BurnDriverD BurnDrvMDiss = {
	"g_iss", NULL, NULL, "1996",
	"International Superstar Soccer Deluxe (E) [!]\0", NULL, "Konami / Factor 5", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, issRomInfo, issRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Boogerman (U) [!]

static struct BurnRomInfo boogRomDesc[]={
	{ "g_boog.bin", 0x300000, 0x1A7A2BEC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(boog);
STD_ROM_FN(boog);

struct BurnDriver BurnDrvMDboog = {
	"g_boog", NULL, NULL, "1900",
	"Boogerman (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, boogRomInfo, boogRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage (W) (REV01) [!]

static struct BurnRomInfo sorRomDesc[]={
	{ "g_sor.bin", 0x080000, 0x4052E845, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor);
STD_ROM_FN(sor);

struct BurnDriver BurnDrvMDsor = {
	"g_sor", NULL, NULL, "1991",
	"Streets of Rage (W) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sorRomInfo, sorRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage 2 (U) [!]

static struct BurnRomInfo sor2RomDesc[]={
	{ "g_sor2.bin", 0x200000, 0xE01FA526, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor2);
STD_ROM_FN(sor2);

struct BurnDriver BurnDrvMDsor2 = {
	"g_sor2", NULL, NULL, "1992",
	"Streets of Rage 2 (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor2RomInfo, sor2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage 3 (U) [!]

static struct BurnRomInfo sor3RomDesc[]={
	{ "g_sor3.bin", 0x300000, 0xD5BB15D9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor3);
STD_ROM_FN(sor3);

struct BurnDriver BurnDrvMDsor3 = {
	"g_sor3", NULL, NULL, "1994",
	"Streets of Rage 3 (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor3RomInfo, sor3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ayrton Senna's Super Monaco GP II (U) [!]

static struct BurnRomInfo sgp2RomDesc[]={
	{ "g_sgp2.bin", 0x100000, 0xEAC8DED6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sgp2);
STD_ROM_FN(sgp2);

struct BurnDriverD BurnDrvMDsgp2 = {
	"g_sgp2", NULL, NULL, "1900",
	"Ayrton Senna's Super Monaco GP II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sgp2RomInfo, sgp2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman Forever (W) [!]

static struct BurnRomInfo batfRomDesc[]={
	{ "g_batf.bin", 0x300000, 0x8B723D01, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(batf);
STD_ROM_FN(batf);

struct BurnDriverD BurnDrvMDbatf = {
	"g_batf", NULL, NULL, "1900",
	"Batman Forever (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batfRomInfo, batfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beyond Oasis (U) [!]

static struct BurnRomInfo boasRomDesc[]={
	{ "g_boas.bin", 0x300000, 0xC4728225, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(boas);
STD_ROM_FN(boas);

struct BurnDriver BurnDrvMDboas = {
	"g_boas", NULL, NULL, "1995",
	"Beyond Oasis (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, boasRomInfo, boasRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck II - Son of Chuck (U) [!]

static struct BurnRomInfo chk2RomDesc[]={
	{ "g_chk2.bin", 0x100000, 0x408B1CDB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chk2);
STD_ROM_FN(chk2);

struct BurnDriverD BurnDrvMDchk2 = {
	"g_chk2", NULL, NULL, "1900",
	"Chuck II - Son of Chuck (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chk2RomInfo, chk2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Disney's Aladdin (U) [!]

static struct BurnRomInfo aladRomDesc[]={
	{ "g_alad.bin", 0x200000, 0xED427EA9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alad);
STD_ROM_FN(alad);

struct BurnDriverD BurnDrvMDalad = {
	"g_alad", NULL, NULL, "1993",
	"Disney's Aladdin (U) [!]\0", "No sound", "Disney / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aladRomInfo, aladRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dr. Robotnik's Mean Bean Machine (U) [!]

static struct BurnRomInfo beanRomDesc[]={
	{ "g_bean.bin", 0x100000, 0xC7CA517F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bean);
STD_ROM_FN(bean);

struct BurnDriverD BurnDrvMDbean = {
	"g_bean", NULL, NULL, "1900",
	"Dr. Robotnik's Mean Bean Machine (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beanRomInfo, beanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon - The Bruce Lee Story (U) [!]

static struct BurnRomInfo bleeRomDesc[]={
	{ "g_blee.bin", 0x200000, 0xEFE850E5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blee);
STD_ROM_FN(blee);

struct BurnDriverD BurnDrvMDblee = {
	"g_blee", NULL, NULL, "1900",
	"Dragon - The Bruce Lee Story (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bleeRomInfo, bleeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO - The Tides of Time (U) [!]

static struct BurnRomInfo eco2RomDesc[]={
	{ "g_eco2.bin", 0x200000, 0xCCB21F98, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eco2);
STD_ROM_FN(eco2);

struct BurnDriverD BurnDrvMDeco2 = {
	"g_eco2", NULL, NULL, "1994",
	"ECCO - The Tides of Time (U) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eco2RomInfo, eco2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Exo-Squad (U) [!]

static struct BurnRomInfo exosRomDesc[]={
	{ "g_exos.bin", 0x100000, 0x10EC03F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exos);
STD_ROM_FN(exos);

struct BurnDriverD BurnDrvMDexos = {
	"g_exos", NULL, NULL, "1900",
	"Exo-Squad (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exosRomInfo, exosRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatal Rewind (UE) [!]

static struct BurnRomInfo fatrRomDesc[]={
	{ "g_fatr.bin", 0x080000, 0xE91AED05, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fatr);
STD_ROM_FN(fatr);

struct BurnDriverD BurnDrvMDfatr = {
	"g_fatr", NULL, NULL, "1991",
	"Fatal Rewind (UE) [!]\0", NULL, "Psygnosis", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fatrRomInfo, fatrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Killing Game Sho

static struct BurnRomInfo kgsRomDesc[]={
	{ "g_kgs.bin", 0x080000, 0x21DBB69D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kgs);
STD_ROM_FN(kgs);

struct BurnDriverD BurnDrvMDkgs = {
	"g_kgs", NULL, NULL, "1991",
	"Killing Game Sho\0", NULL, "Psygnosis", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kgsRomInfo, kgsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Killing Game Sho

static struct BurnRomInfo kgsrRomDesc[]={
	{ "g_kgsr.bin", 0x100000, 0xB8E7668A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kgsr);
STD_ROM_FN(kgsr);

struct BurnDriverD BurnDrvMDkgsr = {
	"g_kgsr", NULL, NULL, "1993",
	"Killing Game Sho\0", NULL, "Psygnosis", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kgsrRomInfo, kgsrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gadget Twin

static struct BurnRomInfo gtwiRomDesc[]={
	{ "g_gtwi.bin", 0x100000, 0x7AE5E248, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gtwi);
STD_ROM_FN(gtwi);

struct BurnDriverD BurnDrvMDgtwi = {
	"g_gtwi", NULL, NULL, "1900",
	"Gadget Twin\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gtwiRomInfo, gtwiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gargoyles (U) [!]

static struct BurnRomInfo gargRomDesc[]={
	{ "g_garg.bin", 0x300000, 0x2D965364, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(garg);
STD_ROM_FN(garg);

struct BurnDriverD BurnDrvMDgarg = {
	"g_garg", NULL, NULL, "1995",
	"Gargoyles (U) [!]\0", NULL, "Buena Vista Interactive", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gargRomInfo, gargRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ghouls 'N Ghosts (UE) (REV02) [!]

static struct BurnRomInfo gngRomDesc[]={
	{ "g_gng.bin", 0x0A0000, 0x4F2561D5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gng);
STD_ROM_FN(gng);

struct BurnDriverD BurnDrvMDgng = {
	"g_gng", NULL, NULL, "1989",
	"Ghouls 'N Ghosts (UE) (REV02) [!]\0", NULL, "Capcom / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gngRomInfo, gngRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dai Makaimura (J) [!]

static struct BurnRomInfo daimRomDesc[]={
	{ "g_daim.bin", 0x0A0000, 0x5659F379, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daim);
STD_ROM_FN(daim);

struct BurnDriverD BurnDrvMDdaim = {
	"g_daim", NULL, NULL, "1989",
	"Dai Makaimura (J) [!]\0", NULL, "Capcom / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daimRomInfo, daimRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// High Seas Havoc (U) [!]

static struct BurnRomInfo hshRomDesc[]={
	{ "g_hsh.bin", 0x100000, 0x17BE551C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hsh);
STD_ROM_FN(hsh);

struct BurnDriverD BurnDrvMDhsh = {
	"g_hsh", NULL, NULL, "1993",
	"High Seas Havoc (U) [!]\0", NULL, "Data East", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hshRomInfo, hshRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Legend of Galaha

static struct BurnRomInfo lgalRomDesc[]={
	{ "g_lgal.bin", 0x100000, 0x679557BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lgal);
STD_ROM_FN(lgal);

struct BurnDriverD BurnDrvMDlgal = {
	"g_lgal", NULL, NULL, "1900",
	"Legend of Galaha\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lgalRomInfo, lgalRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lion Kin

static struct BurnRomInfo lionRomDesc[]={
	{ "g_lion.bin", 0x300000, 0x5696A5BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lion);
STD_ROM_FN(lion);

struct BurnDriverD BurnDrvMDlion = {
	"g_lion", NULL, NULL, "1900",
	"Lion Kin\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lionRomInfo, lionRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mazin Saga (U) [!]

static struct BurnRomInfo maziRomDesc[]={
	{ "g_mazi.bin", 0x100000, 0x1BD9FEF1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mazi);
STD_ROM_FN(mazi);

struct BurnDriverD BurnDrvMDmazi = {
	"g_mazi", NULL, NULL, "1993",
	"Mazin Saga (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, maziRomInfo, maziRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// I Love Mickey Mouse - Fushigi no Oshiro Dai Bouken (J) [!]

static struct BurnRomInfo mickRomDesc[]={
	{ "g_mick.bin", 0x100000, 0x40F17BB3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mick);
STD_ROM_FN(mick);

struct BurnDriverD BurnDrvMDmick = {
	"g_mick", NULL, NULL, "1990",
	"I Love Mickey Mouse - Fushigi no Oshiro Dai Bouken (J) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mickRomInfo, mickRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey Mania - Timeless Adventures of Mickey Mouse (U) [!]

static struct BurnRomInfo mmanRomDesc[]={
	{ "g_mman.bin", 0x200000, 0x629E5963, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mman);
STD_ROM_FN(mman);

struct BurnDriverD BurnDrvMDmman = {
	"g_mman", NULL, NULL, "1994",
	"Mickey Mania - Timeless Adventures of Mickey Mouse (U) [!]\0", NULL, "Disney / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmanRomInfo, mmanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Panorama Cotton (J) [c][!]

static struct BurnRomInfo panoRomDesc[]={
	{ "g_pano.bin", 0x280000, 0x9E57D92E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pano);
STD_ROM_FN(pano);

struct BurnDriverD BurnDrvMDpano = {
	"g_pano", NULL, NULL, "1900",
	"Panorama Cotton (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, panoRomInfo, panoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pocahontas (U) [!]

static struct BurnRomInfo pocaRomDesc[]={
	{ "g_poca.bin", 0x400000, 0x6DDD1C6D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(poca);
STD_ROM_FN(poca);

struct BurnDriverD BurnDrvMDpoca = {
	"g_poca", NULL, NULL, "1900",
	"Pocahontas (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pocaRomInfo, pocaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Power Monger (UE) [!]

static struct BurnRomInfo pmonRomDesc[]={
	{ "g_pmon.bin", 0x100000, 0xFB599B86, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pmon);
STD_ROM_FN(pmon);

struct BurnDriverD BurnDrvMDpmon = {
	"g_pmon", NULL, NULL, "1900",
	"Power Monger (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pmonRomInfo, pmonRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pulseman (J) [c][!]

static struct BurnRomInfo pulsRomDesc[]={
	{ "g_puls.bin", 0x200000, 0x138A104E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puls);
STD_ROM_FN(puls);

struct BurnDriverD BurnDrvMDpuls = {
	"g_puls", NULL, NULL, "1900",
	"Pulseman (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pulsRomInfo, pulsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Red Zone (UE) [!]

static struct BurnRomInfo redzRomDesc[]={
	{ "g_redz.bin", 0x200000, 0x56512EE5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(redz);
STD_ROM_FN(redz);

struct BurnDriverD BurnDrvMDredz = {
	"g_redz", NULL, NULL, "1900",
	"Red Zone (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, redzRomInfo, redzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Socket (U) [!]

static struct BurnRomInfo sockRomDesc[]={
	{ "g_sock.bin", 0x100000, 0x3C14E15A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sock);
STD_ROM_FN(sock);

struct BurnDriverD BurnDrvMDsock = {
	"g_sock", NULL, NULL, "1993",
	"Socket (U) [!]\0", NULL, "Vic Tokai", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sockRomInfo, sockRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Skitchin' (UE) [!]

static struct BurnRomInfo skitRomDesc[]={
	{ "g_skit.bin", 0x200000, 0xF785F9D7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(skit);
STD_ROM_FN(skit);

struct BurnDriverD BurnDrvMDskit = {
	"g_skit", NULL, NULL, "1900",
	"Skitchin' (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, skitRomInfo, skitRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic 3D Blast (UE) [!]

static struct BurnRomInfo s3dRomDesc[]={
	{ "g_s3d.bin", 0x400000, 0x44A2CA44, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s3d);
STD_ROM_FN(s3d);

struct BurnDriver BurnDrvMDs3d = {
	"g_s3d", NULL, NULL, "1996",
	"Sonic 3D Blast (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s3dRomInfo, s3dRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spot Goes to Hollywood (U) (REV01) [!]

static struct BurnRomInfo spo2RomDesc[]={
	{ "g_spo2.bin", 0x300000, 0xBDAD1CBC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spo2);
STD_ROM_FN(spo2);

struct BurnDriverD BurnDrvMDspo2 = {
	"g_spo2", NULL, NULL, "199?",
	"Spot Goes to Hollywood (U) (REV01) [!]\0", NULL, "Virgin / Acclaim / Eurocom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spo2RomInfo, spo2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sub-Terrania (U) [!]

static struct BurnRomInfo subtRomDesc[]={
	{ "g_subt.bin", 0x200000, 0xDC3C6C45, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(subt);
STD_ROM_FN(subt);

struct BurnDriverD BurnDrvMDsubt = {
	"g_subt", NULL, NULL, "1993",
	"Sub-Terrania (U) [!]\0", NULL, "Zyrinx", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, subtRomInfo, subtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Fantasy Zone (E) [!]

static struct BurnRomInfo sfzRomDesc[]={
	{ "g_sfz.bin", 0x100000, 0x767780D7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sfz);
STD_ROM_FN(sfz);

struct BurnDriverD BurnDrvMDsfz = {
	"g_sfz", NULL, NULL, "1900",
	"Super Fantasy Zone (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sfzRomInfo, sfzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse 2 (E) [c][!]

static struct BurnRomInfo shoRomDesc[]={
	{ "g_sho.bin", 0x080000, 0x3877D107, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sho);
STD_ROM_FN(sho);

struct BurnDriverD BurnDrvMDsho = {
	"g_sho", NULL, NULL, "1900",
	"Splatterhouse 2 (E) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shoRomInfo, shoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Monaco Grand Prix (W) (M2) (REV02) [!]

static struct BurnRomInfo smgpRomDesc[]={
	{ "g_smgp.bin", 0x080000, 0xBE91B28A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smgp);
STD_ROM_FN(smgp);

struct BurnDriverD BurnDrvMDsmgp = {
	"g_smgp", NULL, NULL, "1990",
	"Super Monaco Grand Prix (W) (M2) (REV02) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smgpRomInfo, smgpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Thunder Blade (W) (REV01) [!]

static struct BurnRomInfo stbRomDesc[]={
	{ "g_stb.bin", 0x080000, 0xB13087EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stb);
STD_ROM_FN(stb);

struct BurnDriverD BurnDrvMDstb = {
	"g_stb", NULL, NULL, "1900",
	"Super Thunder Blade (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stbRomInfo, stbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tiny Toon Adventures - Buster's Hidden Treasure (U) [!]

static struct BurnRomInfo ttaRomDesc[]={
	{ "g_tta.bin", 0x080000, 0xA26D3AE0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tta);
STD_ROM_FN(tta);

struct BurnDriverD BurnDrvMDtta = {
	"g_tta", NULL, NULL, "1900",
	"Tiny Toon Adventures - Buster's Hidden Treasure (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ttaRomInfo, ttaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tyrants - Fight Through Time (U) [!]

static struct BurnRomInfo tyraRomDesc[]={
	{ "g_tyra.bin", 0x100000, 0xA744921E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tyra);
STD_ROM_FN(tyra);

struct BurnDriverD BurnDrvMDtyra = {
	"g_tyra", NULL, NULL, "1994",
	"Tyrants - Fight Through Time (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tyraRomInfo, tyraRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtua Fighter 2 (UE) [!]

static struct BurnRomInfo vf2RomDesc[]={
	{ "g_vf2.bin", 0x400000, 0x937380F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vf2);
STD_ROM_FN(vf2);

struct BurnDriverD BurnDrvMDvf2 = {
	"g_vf2", NULL, NULL, "1900",
	"Virtua Fighter 2 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vf2RomInfo, vf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wiz 'n' Liz - The Frantic Wabbit Wescue (U) [!]

static struct BurnRomInfo wizlRomDesc[]={
	{ "g_wizl.bin", 0x100000, 0xDF036B62, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wizl);
STD_ROM_FN(wizl);

struct BurnDriverD BurnDrvMDwizl = {
	"g_wizl", NULL, NULL, "1900",
	"Wiz 'n' Liz - The Frantic Wabbit Wescue (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wizlRomInfo, wizlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zero the Kamikaze Squirrel (U) [!]

static struct BurnRomInfo ztksRomDesc[]={
	{ "g_ztks.bin", 0x200000, 0x423968DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ztks);
STD_ROM_FN(ztks);

struct BurnDriverD BurnDrvMDztks = {
	"g_ztks", NULL, NULL, "1900",
	"Zero the Kamikaze Squirrel (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ztksRomInfo, ztksRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Populous (U) [!]

static struct BurnRomInfo popuRomDesc[]={
	{ "g_popu.bin", 0x080000, 0xBD74B31E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(popu);
STD_ROM_FN(popu);

struct BurnDriverD BurnDrvMDpopu = {
	"g_popu", NULL, NULL, "1900",
	"Populous (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, popuRomInfo, popuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pinocchio (U) [!]

static struct BurnRomInfo pinoRomDesc[]={
	{ "g_pino.bin", 0x300000, 0xCD4128D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pino);
STD_ROM_FN(pino);

struct BurnDriverD BurnDrvMDpino = {
	"g_pino", NULL, NULL, "1900",
	"Pinocchio (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pinoRomInfo, pinoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puyo Puyo (J) [!]

static struct BurnRomInfo puyoRomDesc[]={
	{ "g_puyo.bin", 0x080000, 0x7F26614E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puyo);
STD_ROM_FN(puyo);

struct BurnDriverD BurnDrvMDpuyo = {
	"g_puyo", NULL, NULL, "1900",
	"Puyo Puyo (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puyoRomInfo, puyoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Revenge of Shinob

static struct BurnRomInfo revsRomDesc[]={
	{ "g_revs.bin", 0x080000, 0x4D35EBE4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(revs);
STD_ROM_FN(revs);

struct BurnDriverD BurnDrvMDrevs = {
	"g_revs", NULL, NULL, "1990",
	"Revenge of Shinob\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, revsRomInfo, revsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// SeaQuest DSV (U) [!]

static struct BurnRomInfo seaqRomDesc[]={
	{ "g_seaq.bin", 0x200000, 0x25B05480, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(seaq);
STD_ROM_FN(seaq);

struct BurnDriverD BurnDrvMDseaq = {
	"g_seaq", NULL, NULL, "1900",
	"SeaQuest DSV (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, seaqRomInfo, seaqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tale Spin (UE) [!]

static struct BurnRomInfo taleRomDesc[]={
	{ "g_tale.bin", 0x080000, 0xF5C0C8D0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tale);
STD_ROM_FN(tale);

struct BurnDriverD BurnDrvMDtale = {
	"g_tale", NULL, NULL, "1900",
	"Tale Spin (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taleRomInfo, taleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zool (U) [!]

static struct BurnRomInfo zoolRomDesc[]={
	{ "g_zool.bin", 0x100000, 0xCB2939F1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zool);
STD_ROM_FN(zool);

struct BurnDriverD BurnDrvMDzool = {
	"g_zool", NULL, NULL, "1900",
	"Zool (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zoolRomInfo, zoolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Andre Agassi Tennis (U) (REV00) [!]

static struct BurnRomInfo aateRomDesc[]={
	{ "g_aate.bin", 0x080000, 0xE755DD51, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aate);
STD_ROM_FN(aate);

struct BurnDriverD BurnDrvMDaate = {
	"g_aate", NULL, NULL, "1900",
	"Andre Agassi Tennis (U) (REV00) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aateRomInfo, aateRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ballz (UE) [!]

static struct BurnRomInfo balzRomDesc[]={
	{ "g_balz.bin", 0x200000, 0xB362B705, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(balz);
STD_ROM_FN(balz);

struct BurnDriverD BurnDrvMDbalz = {
	"g_balz", NULL, NULL, "1900",
	"Ballz (UE) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, balzRomInfo, balzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blood Shot (E) (M4) [!]

static struct BurnRomInfo bshtRomDesc[]={
	{ "g_bsht.bin", 0x200000, 0xF9F2BCEB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bsht);
STD_ROM_FN(bsht);

struct BurnDriverD BurnDrvMDbsht = {
	"g_bsht", NULL, NULL, "1994",
	"Blood Shot (E) (M4) [!]\0", "No sound in-game", "Domark / Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bshtRomInfo, bshtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bonkers (UE) [!]

static struct BurnRomInfo bonkRomDesc[]={
	{ "g_bonk.bin", 0x100000, 0xD1E66017, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bonk);
STD_ROM_FN(bonk);

struct BurnDriverD BurnDrvMDbonk = {
	"g_bonk", NULL, NULL, "1900",
	"Bonkers (UE) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bonkRomInfo, bonkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marsupilami (U) (M5) [!]

static struct BurnRomInfo marsRomDesc[]={
	{ "g_mars.bin", 0x200000, 0xC76558DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mars);
STD_ROM_FN(mars);

struct BurnDriverD BurnDrvMDmars = {
	"g_mars", NULL, NULL, "1900",
	"Marsupilami (U) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, marsRomInfo, marsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flavio's DMA Test (PD)

static struct BurnRomInfo fdmaRomDesc[]={
	{ "g_fdma.bin", 0x004000, 0x549CEBF4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fdma);
STD_ROM_FN(fdma);

struct BurnDriverD BurnDrvMDfdma = {
	"g_fdma", NULL, NULL, "1900",
	"Flavio's DMA Test (PD)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fdmaRomInfo, fdmaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// 3 Ninjas Kick Back (U) [!]

static struct BurnRomInfo g_3ninRomDesc[]={
	{ "g_3nin.bin", 0x200000, 0xE5A24999, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_3nin);
STD_ROM_FN(g_3nin);

struct BurnDriver BurnDrvMDg_3nin = {
	"g_3nin", NULL, NULL, "1900",
	"3 Ninjas Kick Back (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_3ninRomInfo, g_3ninRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aero the Acro-Bat (U) [c][!]

static struct BurnRomInfo acroRomDesc[]={
	{ "g_acro.bin", 0x100000, 0xA3A7A8B5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(acro);
STD_ROM_FN(acro);

struct BurnDriverD BurnDrvMDacro = {
	"g_acro", NULL, NULL, "1993",
	"Aero the Acro-Bat (U) [c][!]\0", "No sound", "Sunsoft / Iguana", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, acroRomInfo, acroRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aero the Acro-Bat 2 (U) [!]

static struct BurnRomInfo acr2RomDesc[]={
	{ "g_acr2.bin", 0x200000, 0x39EB74EB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(acr2);
STD_ROM_FN(acr2);

struct BurnDriverD BurnDrvMDacr2 = {
	"g_acr2", NULL, NULL, "1994",
	"Aero the Acro-Bat 2 (U) [!]\0", "No sound", "Sunsoft / Iguana", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, acr2RomInfo, acr2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Haunting Starring Polterguy (UE) [!]

static struct BurnRomInfo haunRomDesc[]={
	{ "g_haun.bin", 0x200000, 0xC9FC876D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(haun);
STD_ROM_FN(haun);

struct BurnDriverD BurnDrvMDhaun = {
	"g_haun", NULL, NULL, "1900",
	"Haunting Starring Polterguy (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, haunRomInfo, haunRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puggsy (U) [!]

static struct BurnRomInfo puggRomDesc[]={
	{ "g_pugg.bin", 0x100000, 0x70132168, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pugg);
STD_ROM_FN(pugg);

struct BurnDriverD BurnDrvMDpugg = {
	"g_pugg", NULL, NULL, "1900",
	"Puggsy (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puggRomInfo, puggRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Samurai Shodown (U) [!]

static struct BurnRomInfo samsRomDesc[]={
	{ "g_sams.bin", 0x300000, 0x5BB8B2D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sams);
STD_ROM_FN(sams);

struct BurnDriverD BurnDrvMDsams = {
	"g_sams", NULL, NULL, "1994",
	"Samurai Shodown (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, samsRomInfo, samsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marko's Magic Football (U) [!]

static struct BurnRomInfo mmfRomDesc[]={
	{ "g_mmf.bin", 0x200000, 0x2B8C8CCE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmf);
STD_ROM_FN(mmf);

struct BurnDriverD BurnDrvMDmmf = {
	"g_mmf", NULL, NULL, "1900",
	"Marko's Magic Football (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmfRomInfo, mmfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Misadventures of Flin

static struct BurnRomInfo mfliRomDesc[]={
	{ "g_mfli.bin", 0x100000, 0xBEF9A4F4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mfli);
STD_ROM_FN(mfli);

struct BurnDriverD BurnDrvMDmfli = {
	"g_mfli", NULL, NULL, "1900",
	"Misadventures of Flin\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mfliRomInfo, mfliRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Skidmarks (E) (J-Cart) [!]

static struct BurnRomInfo skidRomDesc[]={
	{ "g_skid.bin", 0x200000, 0x4A9C62F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(skid);
STD_ROM_FN(skid);

struct BurnDriverD BurnDrvMDskid = {
	"g_skid", NULL, NULL, "1995",
	"Super Skidmarks (E) (J-Cart) [!]\0", NULL, "Codemasters / Acid", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, skidRomInfo, skidRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRun 2019 (U) [!]

static struct BurnRomInfo or20RomDesc[]={
	{ "g_or20.bin", 0x100000, 0xE32E17E2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(or20);
STD_ROM_FN(or20);

struct BurnDriverD BurnDrvMDor20 = {
	"g_or20", NULL, NULL, "1993",
	"OutRun 2019 (U) [!]\0", NULL, "Sims", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, or20RomInfo, or20RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Risky Woods (UE) [!]

static struct BurnRomInfo rwooRomDesc[]={
	{ "g_rwoo.bin", 0x100000, 0xD975E93C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rwoo);
STD_ROM_FN(rwoo);

struct BurnDriverD BurnDrvMDrwoo = {
	"g_rwoo", NULL, NULL, "1900",
	"Risky Woods (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rwooRomInfo, rwooRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rolo to the Rescue (UE) [!]

static struct BurnRomInfo roloRomDesc[]={
	{ "g_rolo.bin", 0x080000, 0x306861A2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rolo);
STD_ROM_FN(rolo);

struct BurnDriverD BurnDrvMDrolo = {
	"g_rolo", NULL, NULL, "1992",
	"Rolo to the Rescue (UE) [!]\0", NULL, "Electronic Arts / Vectordean", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, roloRomInfo, roloRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lotus Turbo Challenge (UE) [!]

static struct BurnRomInfo lotRomDesc[]={
	{ "g_lot.bin", 0x100000, 0xA3CF6E9C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lot);
STD_ROM_FN(lot);

struct BurnDriverD BurnDrvMDlot = {
	"g_lot", NULL, NULL, "1900",
	"Lotus Turbo Challenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lotRomInfo, lotRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lotus II RECS (UE) [!]

static struct BurnRomInfo lot2RomDesc[]={
	{ "g_lot2.bin", 0x100000, 0x1D8EE010, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lot2);
STD_ROM_FN(lot2);

struct BurnDriverD BurnDrvMDlot2 = {
	"g_lot2", NULL, NULL, "1900",
	"Lotus II RECS (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lot2RomInfo, lot2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Racer (E) [c][!]

static struct BurnRomInfo straRomDesc[]={
	{ "g_stra.bin", 0x100000, 0x1A58D5FE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stra);
STD_ROM_FN(stra);

struct BurnDriverD BurnDrvMDstra = {
	"g_stra", NULL, NULL, "1900",
	"Street Racer (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, straRomInfo, straRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tinhead (U) [!]

static struct BurnRomInfo tinhRomDesc[]={
	{ "g_tinh.bin", 0x100000, 0xD6724B84, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tinh);
STD_ROM_FN(tinh);

struct BurnDriverD BurnDrvMDtinh = {
	"g_tinh", NULL, NULL, "1900",
	"Tinhead (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tinhRomInfo, tinhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Top Gear 2 (U) [!]

static struct BurnRomInfo tg2RomDesc[]={
	{ "g_tg2.bin", 0x100000, 0xBD3074D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tg2);
STD_ROM_FN(tg2);

struct BurnDriverD BurnDrvMDtg2 = {
	"g_tg2", NULL, NULL, "1900",
	"Top Gear 2 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tg2RomInfo, tg2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Greendog - The Beached Surfer Dude (UE) [!]

static struct BurnRomInfo gdogRomDesc[]={
	{ "g_gdog.bin", 0x080000, 0xC4820A03, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gdog);
STD_ROM_FN(gdog);

struct BurnDriverD BurnDrvMDgdog = {
	"g_gdog", NULL, NULL, "1900",
	"Greendog - The Beached Surfer Dude (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gdogRomInfo, gdogRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gaiares (JU) [!]

static struct BurnRomInfo gaiaRomDesc[]={
	{ "g_gaia.bin", 0x100000, 0x5D8BF68B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gaia);
STD_ROM_FN(gaia);

struct BurnDriverD BurnDrvMDgaia = {
	"g_gaia", NULL, NULL, "1900",
	"Gaiares (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gaiaRomInfo, gaiaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gods (U) [!]

static struct BurnRomInfo godsRomDesc[]={
	{ "g_gods.bin", 0x100000, 0xFD234CCD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gods);
STD_ROM_FN(gods);

struct BurnDriverD BurnDrvMDgods = {
	"g_gods", NULL, NULL, "1900",
	"Gods (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, godsRomInfo, godsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gynoug (E) [!]

static struct BurnRomInfo gynoRomDesc[]={
	{ "g_gyno.bin", 0x080000, 0x1B69241F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gyno);
STD_ROM_FN(gyno);

struct BurnDriverD BurnDrvMDgyno = {
	"g_gyno", NULL, NULL, "1991",
	"Gynoug (E) [!]\0", NULL, "NCS", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gynoRomInfo, gynoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Elemental Master (U) [!]

static struct BurnRomInfo elemRomDesc[]={
	{ "g_elem.bin", 0x080000, 0x390918C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(elem);
STD_ROM_FN(elem);

struct BurnDriverD BurnDrvMDelem = {
	"g_elem", NULL, NULL, "1900",
	"Elemental Master (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, elemRomInfo, elemRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Man Overboard! - S.S. Lucifer (E) [c][!]

static struct BurnRomInfo manoRomDesc[]={
	{ "g_mano.bin", 0x100000, 0xCAE0E3A6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mano);
STD_ROM_FN(mano);

struct BurnDriverD BurnDrvMDmano = {
	"g_mano", NULL, NULL, "1900",
	"Man Overboard! - S.S. Lucifer (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, manoRomInfo, manoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daze Before Christma

static struct BurnRomInfo dazeRomDesc[]={
	{ "g_daze.bin", 0x200000, 0xB95E25C9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daze);
STD_ROM_FN(daze);

struct BurnDriverD BurnDrvMDdaze = {
	"g_daze", NULL, NULL, "1900",
	"Daze Before Christma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dazeRomInfo, dazeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jimmy White's Whirlwind Snooker (E) [c][!]

static struct BurnRomInfo jwwsRomDesc[]={
	{ "g_jwws.bin", 0x080000, 0x0AEF5B1F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jwws);
STD_ROM_FN(jwws);

struct BurnDriverD BurnDrvMDjwws = {
	"g_jwws", NULL, NULL, "1900",
	"Jimmy White's Whirlwind Snooker (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jwwsRomInfo, jwwsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ex-Mutants (U) [!]

static struct BurnRomInfo exmuRomDesc[]={
	{ "g_exmu.bin", 0x100000, 0x33B1979F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exmu);
STD_ROM_FN(exmu);

struct BurnDriverD BurnDrvMDexmu = {
	"g_exmu", NULL, NULL, "1992",
	"Ex-Mutants (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exmuRomInfo, exmuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubble and Squeak (U) [!]

static struct BurnRomInfo busqRomDesc[]={
	{ "g_busq.bin", 0x080000, 0x28C4A006, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(busq);
STD_ROM_FN(busq);

struct BurnDriver BurnDrvMDbusq = {
	"g_busq", NULL, NULL, "1900",
	"Bubble and Squeak (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, busqRomInfo, busqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Outlander (U) [!]

static struct BurnRomInfo olanRomDesc[]={
	{ "g_olan.bin", 0x100000, 0xFE6F2350, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olan);
STD_ROM_FN(olan);

struct BurnDriverD BurnDrvMDolan = {
	"g_olan", NULL, NULL, "1900",
	"Outlander (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olanRomInfo, olanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Space Harrier II (UE) [!]

static struct BurnRomInfo sharRomDesc[]={
	{ "g_shar.bin", 0x080000, 0xE5C9CBB0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shar);
STD_ROM_FN(shar);

struct BurnDriverD BurnDrvMDshar = {
	"g_shar", NULL, NULL, "1900",
	"Space Harrier II (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sharRomInfo, sharRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pirates of Dark Wate

static struct BurnRomInfo pidwRomDesc[]={
	{ "g_pidw.bin", 0x200000, 0x0C45B9F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pidw);
STD_ROM_FN(pidw);

struct BurnDriverD BurnDrvMDpidw = {
	"g_pidw", NULL, NULL, "1900",
	"Pirates of Dark Wate\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pidwRomInfo, pidwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beauty and the Beast - Roar of the Beast (U) [!]

static struct BurnRomInfo bbrbRomDesc[]={
	{ "g_bbrb.bin", 0x100000, 0x13E7B519, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bbrb);
STD_ROM_FN(bbrb);

struct BurnDriverD BurnDrvMDbbrb = {
	"g_bbrb", NULL, NULL, "1900",
	"Beauty and the Beast - Roar of the Beast (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bbrbRomInfo, bbrbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beauty and the Beast - Belle's Quest (U) [!]

static struct BurnRomInfo bbbqRomDesc[]={
	{ "g_bbbq.bin", 0x100000, 0xBEFB6FAE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bbbq);
STD_ROM_FN(bbbq);

struct BurnDriverD BurnDrvMDbbbq = {
	"g_bbbq", NULL, NULL, "1900",
	"Beauty and the Beast - Belle's Quest (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bbbqRomInfo, bbbqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toki - Going Ape Spit (UE) [c][!]

static struct BurnRomInfo tokiRomDesc[]={
	{ "g_toki.bin", 0x080000, 0x7362C3F4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toki);
STD_ROM_FN(toki);

struct BurnDriverD BurnDrvMDtoki = {
	"g_toki", NULL, NULL, "1900",
	"Toki - Going Ape Spit (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tokiRomInfo, tokiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Turrican (U) [!]

static struct BurnRomInfo mturRomDesc[]={
	{ "g_mtur.bin", 0x100000, 0xFE898CC9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mtur);
STD_ROM_FN(mtur);

struct BurnDriverD BurnDrvMDmtur = {
	"g_mtur", NULL, NULL, "1994",
	"Mega Turrican (U) [!]\0", NULL, "Data East / Factor 5", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mturRomInfo, mturRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tanto R (J) [!]

static struct BurnRomInfo tanrRomDesc[]={
	{ "g_tanr.bin", 0x200000, 0xD2D2D437, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tanr);
STD_ROM_FN(tanr);

struct BurnDriverD BurnDrvMDtanr = {
	"g_tanr", NULL, NULL, "1900",
	"Tanto R (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tanrRomInfo, tanrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rings of Power (UE) [!]

static struct BurnRomInfo ropRomDesc[]={
	{ "g_rop.bin", 0x100000, 0x41FCC497, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rop);
STD_ROM_FN(rop);

struct BurnDriverD BurnDrvMDrop = {
	"g_rop", NULL, NULL, "1900",
	"Rings of Power (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ropRomInfo, ropRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sensible Soccer - International Edition (E) (M4) [!]

static struct BurnRomInfo seniRomDesc[]={
	{ "g_seni.bin", 0x080000, 0x04E3BCCA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(seni);
STD_ROM_FN(seni);

struct BurnDriver BurnDrvMDseni = {
	"g_seni", NULL, NULL, "1994",
	"Sensible Soccer - International Edition (E) (M4) [!]\0", NULL, "Sensible Software", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, seniRomInfo, seniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pete Sampras Tennis 96 (E) [c][!]

static struct BurnRomInfo ps96RomDesc[]={
	{ "g_ps96.bin", 0x200000, 0x14E3FB7B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ps96);
STD_ROM_FN(ps96);

struct BurnDriverD BurnDrvMDps96 = {
	"g_ps96", NULL, NULL, "1900",
	"Pete Sampras Tennis 96 (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ps96RomInfo, ps96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toughman Contest (UE) [!]

static struct BurnRomInfo tougRomDesc[]={
	{ "g_toug.bin", 0x400000, 0xE19FBC93, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toug);
STD_ROM_FN(toug);

struct BurnDriverD BurnDrvMDtoug = {
	"g_toug", NULL, NULL, "1900",
	"Toughman Contest (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tougRomInfo, tougRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spirou (E) [!]

static struct BurnRomInfo spirRomDesc[]={
	{ "g_spir.bin", 0x100000, 0x6634B130, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spir);
STD_ROM_FN(spir);

struct BurnDriverD BurnDrvMDspir = {
	"g_spir", NULL, NULL, "1900",
	"Spirou (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spirRomInfo, spirRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Striker (E) (M5) [!]

static struct BurnRomInfo strkRomDesc[]={
	{ "g_strk.bin", 0x200000, 0xCC5D7AB2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(strk);
STD_ROM_FN(strk);

struct BurnDriverD BurnDrvMDstrk = {
	"g_strk", NULL, NULL, "1900",
	"Striker (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, strkRomInfo, strkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Championship Soccer II (U) [!]

static struct BurnRomInfo wcs2RomDesc[]={
	{ "g_wcs2.bin", 0x100000, 0xC1DD1C8E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcs2);
STD_ROM_FN(wcs2);

struct BurnDriverD BurnDrvMDwcs2 = {
	"g_wcs2", NULL, NULL, "1900",
	"World Championship Soccer II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wcs2RomInfo, wcs2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Rash II (UE) (REV00) [!]

static struct BurnRomInfo rrs2RomDesc[]={
	{ "g_rrs2.bin", 0x100000, 0x7B29C209, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrs2);
STD_ROM_FN(rrs2);

struct BurnDriverD BurnDrvMDrrs2 = {
	"g_rrs2", NULL, NULL, "1992",
	"Road Rash II (UE) (REV00) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrs2RomInfo, rrs2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Rash 3 (UE) [!]

static struct BurnRomInfo rrs3RomDesc[]={
	{ "g_rrs3.bin", 0x200000, 0x15785956, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrs3);
STD_ROM_FN(rrs3);

struct BurnDriverD BurnDrvMDrrs3 = {
	"g_rrs3", NULL, NULL, "1995",
	"Road Rash 3 (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrs3RomInfo, rrs3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zombies Ate My Neighbors (U) [c][!]

static struct BurnRomInfo zombRomDesc[]={
	{ "g_zomb.bin", 0x100000, 0x2BF3626F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zomb);
STD_ROM_FN(zomb);

struct BurnDriverD BurnDrvMDzomb = {
	"g_zomb", NULL, NULL, "1900",
	"Zombies Ate My Neighbors (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zombRomInfo, zombRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Yuu Yuu Hakusho - Makyou Toitsusen (J) [!]

static struct BurnRomInfo yuyuRomDesc[]={
	{ "g_yuyu.bin", 0x300000, 0x71CEAC6F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yuyu);
STD_ROM_FN(yuyu);

struct BurnDriverD BurnDrvMDyuyu = {
	"g_yuyu", NULL, NULL, "1900",
	"Yuu Yuu Hakusho - Makyou Toitsusen (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yuyuRomInfo, yuyuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Devilish - The Next Possession (U) [c][!]

static struct BurnRomInfo deviRomDesc[]={
	{ "g_devi.bin", 0x080000, 0xD3F300AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(devi);
STD_ROM_FN(devi);

struct BurnDriverD BurnDrvMDdevi = {
	"g_devi", NULL, NULL, "1992",
	"Devilish - The Next Possession (U) [c][!]\0", "No sound", "Sage's Creation", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, deviRomInfo, deviRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alisia Dragoon (U) [!]

static struct BurnRomInfo alisRomDesc[]={
	{ "g_alis.bin", 0x100000, 0xD28D5C40, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alis);
STD_ROM_FN(alis);

struct BurnDriverD BurnDrvMDalis = {
	"g_alis", NULL, NULL, "1900",
	"Alisia Dragoon (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alisRomInfo, alisRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Atomic Runner (U) [!]

static struct BurnRomInfo arunRomDesc[]={
	{ "g_arun.bin", 0x100000, 0x0677C210, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arun);
STD_ROM_FN(arun);

struct BurnDriver BurnDrvMDarun = {
	"g_arun", NULL, NULL, "1992",
	"Atomic Runner (U) [!]\0", NULL, "Data East", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arunRomInfo, arunRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRunners (U) [!]

static struct BurnRomInfo orurRomDesc[]={
	{ "g_orur.bin", 0x200000, 0xEDE636B9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(orur);
STD_ROM_FN(orur);

struct BurnDriverD BurnDrvMDorur = {
	"g_orur", NULL, NULL, "199?",
	"OutRunners (U) [!]\0", NULL, "Sega / Data East", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, orurRomInfo, orurRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRunners (J) [!]

static struct BurnRomInfo orunRomDesc[]={
	{ "g_orun.bin", 0x100000, 0xFDD9A8D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(orun);
STD_ROM_FN(orun);

struct BurnDriverD BurnDrvMDorun = {
	"g_orun", NULL, NULL, "199?",
	"OutRunners (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, orunRomInfo, orunRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cheese Cat-Astrophe Starring Speedy Gonzales (E) (M4) [!]

static struct BurnRomInfo cheeRomDesc[]={
	{ "g_chee.bin", 0x200000, 0xFF634B28, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chee);
STD_ROM_FN(chee);

struct BurnDriverD BurnDrvMDchee = {
	"g_chee", NULL, NULL, "1900",
	"Cheese Cat-Astrophe Starring Speedy Gonzales (E) (M4) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cheeRomInfo, cheeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Hang Time (U) [!]

static struct BurnRomInfo nbahRomDesc[]={
	{ "g_nbah.bin", 0x300000, 0x176B0338, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbah);
STD_ROM_FN(nbah);

struct BurnDriverD BurnDrvMDnbah = {
	"g_nbah", NULL, NULL, "1900",
	"NBA Hang Time (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbahRomInfo, nbahRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bio-Hazard Battle (UE) [!]

static struct BurnRomInfo bhbRomDesc[]={
	{ "g_bhb.bin", 0x100000, 0x95B0EA2B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bhb);
STD_ROM_FN(bhb);

struct BurnDriver BurnDrvMDbhb = {
	"g_bhb", NULL, NULL, "1900",
	"Bio-Hazard Battle (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bhbRomInfo, bhbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vectorman (UE) [!]

static struct BurnRomInfo vectRomDesc[]={
	{ "g_vect.bin", 0x200000, 0xD38B3354, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vect);
STD_ROM_FN(vect);

struct BurnDriverD BurnDrvMDvect = {
	"g_vect", NULL, NULL, "1995",
	"Vectorman (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vectRomInfo, vectRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Stormlord (U) [!]

static struct BurnRomInfo stolRomDesc[]={
	{ "g_stol.bin", 0x080000, 0x39AB50A5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stol);
STD_ROM_FN(stol);

struct BurnDriverD BurnDrvMDstol = {
	"g_stol", NULL, NULL, "1900",
	"Stormlord (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stolRomInfo, stolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Test Drive II - The Duel (U) [!]

static struct BurnRomInfo td2RomDesc[]={
	{ "g_td2.bin", 0x100000, 0xF9BDF8C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(td2);
STD_ROM_FN(td2);

struct BurnDriverD BurnDrvMDtd2 = {
	"g_td2", NULL, NULL, "1900",
	"Test Drive II - The Duel (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, td2RomInfo, td2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Turbo Outrun (JE) [c][!]

static struct BurnRomInfo toutRomDesc[]={
	{ "g_tout.bin", 0x080000, 0x0C661369, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tout);
STD_ROM_FN(tout);

struct BurnDriverD BurnDrvMDtout = {
	"g_tout", NULL, NULL, "1900",
	"Turbo Outrun (JE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toutRomInfo, toutRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sparkster (U) [!]

static struct BurnRomInfo sprkRomDesc[]={
	{ "g_sprk.bin", 0x100000, 0x6BDB14ED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sprk);
STD_ROM_FN(sprk);

struct BurnDriverD BurnDrvMDsprk = {
	"g_sprk", NULL, NULL, "1900",
	"Sparkster (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sprkRomInfo, sprkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Garfield - Caught in the Act (UE) [!]

static struct BurnRomInfo garfRomDesc[]={
	{ "g_garf.bin", 0x200000, 0xF0FF078E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(garf);
STD_ROM_FN(garf);

struct BurnDriverD BurnDrvMDgarf = {
	"g_garf", NULL, NULL, "1900",
	"Garfield - Caught in the Act (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, garfRomInfo, garfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon's Fury (UE) [!]

static struct BurnRomInfo dfryRomDesc[]={
	{ "g_dfry.bin", 0x080000, 0x58037BC6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dfry);
STD_ROM_FN(dfry);

struct BurnDriverD BurnDrvMDdfry = {
	"g_dfry", NULL, NULL, "1992",
	"Dragon's Fury (UE) [!]\0", NULL, "Technosoft / Tengen", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dfryRomInfo, dfryRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon's Revenge (UE) [!]

static struct BurnRomInfo drevRomDesc[]={
	{ "g_drev.bin", 0x100000, 0x841EDBC0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drev);
STD_ROM_FN(drev);

struct BurnDriverD BurnDrvMDdrev = {
	"g_drev", NULL, NULL, "1900",
	"Dragon's Revenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, drevRomInfo, drevRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Addams Family, The (UE) [!]

static struct BurnRomInfo afamRomDesc[]={
	{ "g_afam.bin", 0x100000, 0x71F58614, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(afam);
STD_ROM_FN(afam);

struct BurnDriver BurnDrvMDafam = {
	"g_afam", NULL, NULL, "1900",
	"Addams Family, The (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, afamRomInfo, afamRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Addams Family Values (E) (M3) [!]

static struct BurnRomInfo afavRomDesc[]={
	{ "g_afav.bin", 0x200000, 0xB906B992, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(afav);
STD_ROM_FN(afav);

struct BurnDriver BurnDrvMDafav = {
	"g_afav", NULL, NULL, "1900",
	"Addams Family Values (E) (M3) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, afavRomInfo, afavRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Air Buster (U) [c][!]

static struct BurnRomInfo abusRomDesc[]={
	{ "g_abus.bin", 0x080000, 0xF3D65BAA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abus);
STD_ROM_FN(abus);

struct BurnDriver BurnDrvMDabus = {
	"g_abus", NULL, NULL, "1900",
	"Air Buster (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abusRomInfo, abusRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alien 3 (UE) (REV01) [!]

static struct BurnRomInfo ali3RomDesc[]={
	{ "g_ali3.bin", 0x080000, 0xB327FD1B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ali3);
STD_ROM_FN(ali3);

struct BurnDriver BurnDrvMDali3 = {
	"g_ali3", NULL, NULL, "1900",
	"Alien 3 (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ali3RomInfo, ali3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arcus Odyssey (U) [!]

static struct BurnRomInfo arcuRomDesc[]={
	{ "g_arcu.bin", 0x100000, 0xBC4D9B20, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arcu);
STD_ROM_FN(arcu);

struct BurnDriver BurnDrvMDarcu = {
	"g_arcu", NULL, NULL, "1900",
	"Arcus Odyssey (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arcuRomInfo, arcuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ariel - The Little Mermaid (UE) [!]

static struct BurnRomInfo arieRomDesc[]={
	{ "g_arie.bin", 0x080000, 0x58E297DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arie);
STD_ROM_FN(arie);

struct BurnDriver BurnDrvMDarie = {
	"g_arie", NULL, NULL, "1900",
	"Ariel - The Little Mermaid (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arieRomInfo, arieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arrow Flash (UE) [!]

static struct BurnRomInfo arroRomDesc[]={
	{ "g_arro.bin", 0x080000, 0x4D89E66B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arro);
STD_ROM_FN(arro);

struct BurnDriverD BurnDrvMDarro = {
	"g_arro", NULL, NULL, "1900",
	"Arrow Flash (UE) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arroRomInfo, arroRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Asterix and the Great Rescue (E) (M5) [c][!]

static struct BurnRomInfo asgrRomDesc[]={
	{ "g_asgr.bin", 0x200000, 0x4735FEE6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(asgr);
STD_ROM_FN(asgr);

struct BurnDriverD BurnDrvMDasgr = {
	"g_asgr", NULL, NULL, "1900",
	"Asterix and the Great Rescue (E) (M5) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, asgrRomInfo, asgrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Asterix and the Power of The Gods (E) (M4) [!]

static struct BurnRomInfo aspgRomDesc[]={
	{ "g_aspg.bin", 0x200000, 0x4FF1D83F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aspg);
STD_ROM_FN(aspg);

struct BurnDriverD BurnDrvMDaspg = {
	"g_aspg", NULL, NULL, "1900",
	"Asterix and the Power of The Gods (E) (M4) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aspgRomInfo, aspgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Awesome Possum Kicks Dr. Machino's Butt! (U) [!]

static struct BurnRomInfo awepRomDesc[]={
	{ "g_awep.bin", 0x200000, 0x1F07577F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(awep);
STD_ROM_FN(awep);

struct BurnDriverD BurnDrvMDawep = {
	"g_awep", NULL, NULL, "1900",
	"Awesome Possum Kicks Dr. Machino's Butt! (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, awepRomInfo, awepRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// B.O.B (UE) (REV01) [!]

static struct BurnRomInfo bobRomDesc[]={
	{ "g_bob.bin", 0x100000, 0xEAA2ACB7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bob);
STD_ROM_FN(bob);

struct BurnDriverD BurnDrvMDbob = {
	"g_bob", NULL, NULL, "1994",
	"B.O.B (UE) (REV01) [!]\0", "No sound in-game", "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bobRomInfo, bobRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blaster Master 2 (U) [c][!]

static struct BurnRomInfo blmaRomDesc[]={
	{ "g_blma.bin", 0x100000, 0xC11E4BA1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blma);
STD_ROM_FN(blma);

struct BurnDriverD BurnDrvMDblma = {
	"g_blma", NULL, NULL, "1900",
	"Blaster Master 2 (U) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blmaRomInfo, blmaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Body Count (E) (M5) [!]

static struct BurnRomInfo bodyRomDesc[]={
	{ "g_body.bin", 0x100000, 0x3575A030, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(body);
STD_ROM_FN(body);

struct BurnDriverD BurnDrvMDbody = {
	"g_body", NULL, NULL, "1900",
	"Body Count (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bodyRomInfo, bodyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bram Stoker's Dracula (U) [!]

static struct BurnRomInfo dracRomDesc[]={
	{ "g_drac.bin", 0x100000, 0x077084A6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drac);
STD_ROM_FN(drac);

struct BurnDriverD BurnDrvMDdrac = {
	"g_drac", NULL, NULL, "1994",
	"Bram Stoker's Dracula (U) [!]\0", NULL, "Psygnosis / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dracRomInfo, dracRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brutal - Paws of Fury (U) [!]

static struct BurnRomInfo brpwRomDesc[]={
	{ "g_brpw.bin", 0x200000, 0x98D502CD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(brpw);
STD_ROM_FN(brpw);

struct BurnDriverD BurnDrvMDbrpw = {
	"g_brpw", NULL, NULL, "1900",
	"Brutal - Paws of Fury (U) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, brpwRomInfo, brpwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubba N Stix (U) [!]

static struct BurnRomInfo bubaRomDesc[]={
	{ "g_buba.bin", 0x100000, 0xD45CB46F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(buba);
STD_ROM_FN(buba);

struct BurnDriverD BurnDrvMDbuba = {
	"g_buba", NULL, NULL, "1900",
	"Bubba N Stix (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bubaRomInfo, bubaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubsy in Claws Encounters of the Furred Kind (UE) [!]

static struct BurnRomInfo bubsRomDesc[]={
	{ "g_bubs.bin", 0x200000, 0x3E30D365, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bubs);
STD_ROM_FN(bubs);

struct BurnDriver BurnDrvMDbubs = {
	"g_bubs", NULL, NULL, "1900",
	"Bubsy in Claws Encounters of the Furred Kind (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bubsRomInfo, bubsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubsy II (UE) [!]

static struct BurnRomInfo bub2RomDesc[]={
	{ "g_bub2.bin", 0x200000, 0xF8BEFF56, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bub2);
STD_ROM_FN(bub2);

struct BurnDriver BurnDrvMDbub2 = {
	"g_bub2", NULL, NULL, "1900",
	"Bubsy II (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bub2RomInfo, bub2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bugs Bunny in Double Trouble (U) [!]

static struct BurnRomInfo bbnyRomDesc[]={
	{ "g_bbny.bin", 0x200000, 0x365305A2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bbny);
STD_ROM_FN(bbny);

struct BurnDriver BurnDrvMDbbny = {
	"g_bbny", NULL, NULL, "1900",
	"Bugs Bunny in Double Trouble (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bbnyRomInfo, bbnyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cannon Fodder (E) [!]

static struct BurnRomInfo canoRomDesc[]={
	{ "g_cano.bin", 0x180000, 0xAD217654, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cano);
STD_ROM_FN(cano);

struct BurnDriverD BurnDrvMDcano = {
	"g_cano", NULL, NULL, "1900",
	"Cannon Fodder (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, canoRomInfo, canoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Championship Pool (U) [!]

static struct BurnRomInfo cpooRomDesc[]={
	{ "g_cpoo.bin", 0x100000, 0x253512CF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cpoo);
STD_ROM_FN(cpoo);

struct BurnDriverD BurnDrvMDcpoo = {
	"g_cpoo", NULL, NULL, "1900",
	"Championship Pool (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cpooRomInfo, cpooRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chaos Engin

static struct BurnRomInfo chaoRomDesc[]={
	{ "g_chao.bin", 0x180000, 0xBD9EECF4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chao);
STD_ROM_FN(chao);

struct BurnDriverD BurnDrvMDchao = {
	"g_chao", NULL, NULL, "1900",
	"Chaos Engin\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chaoRomInfo, chaoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chase HQ II (U) [!]

static struct BurnRomInfo chq2RomDesc[]={
	{ "g_chq2.bin", 0x080000, 0xF39E4BF2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chq2);
STD_ROM_FN(chq2);

struct BurnDriverD BurnDrvMDchq2 = {
	"g_chq2", NULL, NULL, "1900",
	"Chase HQ II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chq2RomInfo, chq2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cool Spot (U) [!]

static struct BurnRomInfo coolRomDesc[]={
	{ "g_cool.bin", 0x100000, 0xF024C1A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cool);
STD_ROM_FN(cool);

struct BurnDriverD BurnDrvMDcool = {
	"g_cool", NULL, NULL, "1900",
	"Cool Spot (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, coolRomInfo, coolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cyborg Justice (W) [!]

static struct BurnRomInfo cyboRomDesc[]={
	{ "g_cybo.bin", 0x080000, 0xAB0D1269, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cybo);
STD_ROM_FN(cybo);

struct BurnDriverD BurnDrvMDcybo = {
	"g_cybo", NULL, NULL, "1993",
	"Cyborg Justice (W) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cyboRomInfo, cyboRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dick Vitale's Awesome Baby! College Hoops (U) [!]

static struct BurnRomInfo dicvRomDesc[]={
	{ "g_dicv.bin", 0x200000, 0x1312CF22, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dicv);
STD_ROM_FN(dicv);

struct BurnDriverD BurnDrvMDdicv = {
	"g_dicv", NULL, NULL, "1900",
	"Dick Vitale's Awesome Baby! College Hoops (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dicvRomInfo, dicvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Earthworm Jim (U) [!]

static struct BurnRomInfo ejimRomDesc[]={
	{ "g_ejim.bin", 0x300000, 0xDF3ACF59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ejim);
STD_ROM_FN(ejim);

struct BurnDriverD BurnDrvMDejim = {
	"g_ejim", NULL, NULL, "1900",
	"Earthworm Jim (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ejimRomInfo, ejimRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Escape From Mars Starring Taz (U) [!]

static struct BurnRomInfo taz2RomDesc[]={
	{ "g_taz2.bin", 0x200000, 0x62009F8C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(taz2);
STD_ROM_FN(taz2);

struct BurnDriverD BurnDrvMDtaz2 = {
	"g_taz2", NULL, NULL, "1900",
	"Escape From Mars Starring Taz (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taz2RomInfo, taz2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fantastic Dizzy (UE) (M5) [c][!]

static struct BurnRomInfo fandRomDesc[]={
	{ "g_fand.bin", 0x080000, 0x46447E7A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fand);
STD_ROM_FN(fand);

struct BurnDriverD BurnDrvMDfand = {
	"g_fand", NULL, NULL, "1900",
	"Fantastic Dizzy (UE) (M5) [c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fandRomInfo, fandRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fantastic Dizzy (UE) (M5) [a1]

static struct BurnRomInfo fandaRomDesc[]={
	{ "g_fanda.bin", 0x080000, 0x86B2A235, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fanda);
STD_ROM_FN(fanda);

struct BurnDriverD BurnDrvMDfanda = {
	"g_fanda", NULL, NULL, "1900",
	"Fantastic Dizzy (UE) (M5) [a1]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fandaRomInfo, fandaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flashback - The Quest for Identity (U) [!]

static struct BurnRomInfo fbakRomDesc[]={
	{ "g_fbak.bin", 0x180000, 0x23A9616D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fbak);
STD_ROM_FN(fbak);

struct BurnDriver BurnDrvMDfbak = {
	"g_fbak", NULL, NULL, "1993",
	"Flashback - The Quest for Identity (U) [!]\0", NULL, "Delphine / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fbakRomInfo, fbakRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Heavy Unit (J) [!]

static struct BurnRomInfo huniRomDesc[]={
	{ "g_huni.bin", 0x080000, 0x1ACBE608, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(huni);
STD_ROM_FN(huni);

struct BurnDriverD BurnDrvMDhuni = {
	"g_huni", NULL, NULL, "1900",
	"Heavy Unit (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, huniRomInfo, huniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hellfire (U) [!]

static struct BurnRomInfo hellRomDesc[]={
	{ "g_hell.bin", 0x080000, 0x184018F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hell);
STD_ROM_FN(hell);

struct BurnDriverD BurnDrvMDhell = {
	"g_hell", NULL, NULL, "1900",
	"Hellfire (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hellRomInfo, hellRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hook (U) [c][!]

static struct BurnRomInfo hookRomDesc[]={
	{ "g_hook.bin", 0x100000, 0x2C48E712, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hook);
STD_ROM_FN(hook);

struct BurnDriverD BurnDrvMDhook = {
	"g_hook", NULL, NULL, "1900",
	"Hook (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hookRomInfo, hookRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Human

static struct BurnRomInfo humaRomDesc[]={
	{ "g_huma.bin", 0x100000, 0xA0CF4366, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(huma);
STD_ROM_FN(huma);

struct BurnDriverD BurnDrvMDhuma = {
	"g_huma", NULL, NULL, "1900",
	"Human\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, humaRomInfo, humaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park - Rampage Edition (UE) [!]

static struct BurnRomInfo jpraRomDesc[]={
	{ "g_jpra.bin", 0x200000, 0x98B4AA1B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jpra);
STD_ROM_FN(jpra);

struct BurnDriverD BurnDrvMDjpra = {
	"g_jpra", NULL, NULL, "1900",
	"Jurassic Park - Rampage Edition (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jpraRomInfo, jpraRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Krusty's Super Funhouse (UE) (REV01) [!]

static struct BurnRomInfo ksfhRomDesc[]={
	{ "g_ksfh.bin", 0x080000, 0x56976261, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ksfh);
STD_ROM_FN(ksfh);

struct BurnDriverD BurnDrvMDksfh = {
	"g_ksfh", NULL, NULL, "1900",
	"Krusty's Super Funhouse (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ksfhRomInfo, ksfhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - The Treasures of King Nole (U) [!]

static struct BurnRomInfo landRomDesc[]={
	{ "g_land.bin", 0x200000, 0xFBBB5B97, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(land);
STD_ROM_FN(land);

struct BurnDriverD BurnDrvMDland = {
	"g_land", NULL, NULL, "1994",
	"Landstalker - The Treasures of King Nole (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landRomInfo, landRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Magical Hat no Buttobi Turbo! Daibouken (J) [!]

static struct BurnRomInfo mhatRomDesc[]={
	{ "g_mhat.bin", 0x080000, 0xE43E853D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mhat);
STD_ROM_FN(mhat);

struct BurnDriverD BurnDrvMDmhat = {
	"g_mhat", NULL, NULL, "1900",
	"Magical Hat no Buttobi Turbo! Daibouken (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mhatRomInfo, mhatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// McDonald's Treasure Land Adventure (U) [!]

static struct BurnRomInfo mtlaRomDesc[]={
	{ "g_mtla.bin", 0x100000, 0x04EF4899, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mtla);
STD_ROM_FN(mtla);

struct BurnDriverD BurnDrvMDmtla = {
	"g_mtla", NULL, NULL, "1993",
	"McDonald's Treasure Land Adventure (U) [!]\0", NULL, "Sega / Treasure / McDonalds", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mtlaRomInfo, mtlaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mr. Nutz (E) [!]

static struct BurnRomInfo nutzRomDesc[]={
	{ "g_nutz.bin", 0x100000, 0x0786EA0B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nutz);
STD_ROM_FN(nutz);

struct BurnDriverD BurnDrvMDnutz = {
	"g_nutz", NULL, NULL, "1900",
	"Mr. Nutz (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nutzRomInfo, nutzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ooz

static struct BurnRomInfo oozeRomDesc[]={
	{ "g_ooze.bin", 0x100000, 0x1C0DD42F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ooze);
STD_ROM_FN(ooze);

struct BurnDriverD BurnDrvMDooze = {
	"g_ooze", NULL, NULL, "1900",
	"Ooz\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, oozeRomInfo, oozeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Out of this World (U) [!]

static struct BurnRomInfo ootwRomDesc[]={
	{ "g_ootw.bin", 0x100000, 0x2DA36E01, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ootw);
STD_ROM_FN(ootw);

struct BurnDriver BurnDrvMDootw = {
	"g_ootw", NULL, NULL, "1992",
	"Out of this World (U) [!]\0", NULL, "Delphine / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ootwRomInfo, ootwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pagemaste

static struct BurnRomInfo pageRomDesc[]={
	{ "g_page.bin", 0x200000, 0x75A96D4E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(page);
STD_ROM_FN(page);

struct BurnDriverD BurnDrvMDpage = {
	"g_page", NULL, NULL, "1994",
	"Pagemaste\0", NULL, "Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pageRomInfo, pageRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantom 2040 (U) [!]

static struct BurnRomInfo g_2040RomDesc[]={
	{ "g_2040.bin", 0x200000, 0xFB36E1F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2040);
STD_ROM_FN(g_2040);

struct BurnDriverD BurnDrvMDg_2040 = {
	"g_2040", NULL, NULL, "1900",
	"Phantom 2040 (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2040RomInfo, g_2040RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Psycho Pinball (E) (Oct 1994) (M5) [c][!]

static struct BurnRomInfo ppinRomDesc[]={
	{ "g_ppin.bin", 0x180000, 0xD704784B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ppin);
STD_ROM_FN(ppin);

struct BurnDriverD BurnDrvMDppin = {
	"g_ppin", NULL, NULL, "1900",
	"Psycho Pinball (E) (Oct 1994) (M5) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ppinRomInfo, ppinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ranger-X (U) [!]

static struct BurnRomInfo ranxRomDesc[]={
	{ "g_ranx.bin", 0x100000, 0x55915915, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ranx);
STD_ROM_FN(ranx);

struct BurnDriverD BurnDrvMDranx = {
	"g_ranx", NULL, NULL, "1993",
	"Ranger-X (U) [!]\0", NULL, "Sega / Gau", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ranxRomInfo, ranxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shinobi III - Return of the Ninja Master (U) [!]

static struct BurnRomInfo shi3RomDesc[]={
	{ "g_shi3.bin", 0x100000, 0x5381506F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shi3);
STD_ROM_FN(shi3);

struct BurnDriverD BurnDrvMDshi3 = {
	"g_shi3", NULL, NULL, "1993",
	"Shinobi III - Return of the Ninja Master (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shi3RomInfo, shi3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Skeleton Krew (U) [!]

static struct BurnRomInfo krewRomDesc[]={
	{ "g_krew.bin", 0x200000, 0xC2E05ACB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(krew);
STD_ROM_FN(krew);

struct BurnDriverD BurnDrvMDkrew = {
	"g_krew", NULL, NULL, "1900",
	"Skeleton Krew (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, krewRomInfo, krewRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic and Knuckles & Sonic 3 (W) [!]

static struct BurnRomInfo sks3RomDesc[]={
	{ "g_sks3.bin", 0x400000, 0x63522553, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sks3);
STD_ROM_FN(sks3);

struct BurnDriver BurnDrvMDsks3 = {
	"g_sks3", "g_snkn", NULL, "1994",
	"Sonic and Knuckles & Sonic 3 (W) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sks3RomInfo, sks3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Kick Off (E) [c][!]

static struct BurnRomInfo skikRomDesc[]={
	{ "g_skik.bin", 0x080000, 0xF43793FF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(skik);
STD_ROM_FN(skik);

struct BurnDriverD BurnDrvMDskik = {
	"g_skik", NULL, NULL, "1900",
	"Super Kick Off (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, skikRomInfo, skikRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sylvester & Tweety in Cagey Capers (UE) [!]

static struct BurnRomInfo sylvRomDesc[]={
	{ "g_sylv.bin", 0x200000, 0x89FC54CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sylv);
STD_ROM_FN(sylv);

struct BurnDriverD BurnDrvMDsylv = {
	"g_sylv", NULL, NULL, "1900",
	"Sylvester & Tweety in Cagey Capers (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sylvRomInfo, sylvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Terminato

static struct BurnRomInfo termRomDesc[]={
	{ "g_term.bin", 0x100000, 0x31A629BE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(term);
STD_ROM_FN(term);

struct BurnDriverD BurnDrvMDterm = {
	"g_term", NULL, NULL, "1900",
	"Terminato\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, termRomInfo, termRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl in Panic on Funkotron (U) [!]

static struct BurnRomInfo tje2RomDesc[]={
	{ "g_tje2.bin", 0x200000, 0xAA021BDD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje2);
STD_ROM_FN(tje2);

struct BurnDriverD BurnDrvMDtje2 = {
	"g_tje2", NULL, NULL, "1993",
	"Toejam & Earl in Panic on Funkotron (U) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tje2RomInfo, tje2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wolverine Adamantium Rage (UE) [!]

static struct BurnRomInfo wolvRomDesc[]={
	{ "g_wolv.bin", 0x200000, 0xD2437BB7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wolv);
STD_ROM_FN(wolv);

struct BurnDriverD BurnDrvMDwolv = {
	"g_wolv", NULL, NULL, "1900",
	"Wolverine Adamantium Rage (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wolvRomInfo, wolvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ultimate Qix (U) [!]

static struct BurnRomInfo uqixRomDesc[]={
	{ "g_uqix.bin", 0x040000, 0xD83369D9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uqix);
STD_ROM_FN(uqix);

struct BurnDriverD BurnDrvMDuqix = {
	"g_uqix", NULL, NULL, "1900",
	"Ultimate Qix (U) [!]\0", NULL, "Taito", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, uqixRomInfo, uqixRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// AAAHH!!! Real Monsters (UE) [!]

static struct BurnRomInfo realRomDesc[]={
	{ "g_real.bin", 0x200000, 0xFDC80BFC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(real);
STD_ROM_FN(real);

struct BurnDriverD BurnDrvMDreal = {
	"g_real", NULL, NULL, "1900",
	"AAAHH!!! Real Monsters (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, realRomInfo, realRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aerobiz Supersonic (U) [!]

static struct BurnRomInfo abz2RomDesc[]={
	{ "g_abz2.bin", 0x100000, 0x9377F1B5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abz2);
STD_ROM_FN(abz2);

struct BurnDriver BurnDrvMDabz2 = {
	"g_abz2", NULL, NULL, "1994",
	"Aerobiz Supersonic (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abz2RomInfo, abz2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// After Burner II (UE) [!]

static struct BurnRomInfo abu2RomDesc[]={
	{ "g_abu2.bin", 0x080000, 0xCCAFE00E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abu2);
STD_ROM_FN(abu2);

struct BurnDriverD BurnDrvMDabu2 = {
	"g_abu2", NULL, NULL, "1900",
	"After Burner II (UE) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abu2RomInfo, abu2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aquatic Games - Starring James Pond, The (UE) [!]

static struct BurnRomInfo aquaRomDesc[]={
	{ "g_aqua.bin", 0x080000, 0x400F4BA7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aqua);
STD_ROM_FN(aqua);

struct BurnDriver BurnDrvMDaqua = {
	"g_aqua", NULL, NULL, "1992",
	"Aquatic Games - Starring James Pond, The (UE) [!]\0", NULL, "Electronic Arts / Vectordean / Millenium", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aquaRomInfo, aquaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Barkley Shut Up and Jam! 2 (U) [!]

static struct BurnRomInfo suj2RomDesc[]={
	{ "g_suj2.bin", 0x200000, 0x321BB6BD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(suj2);
STD_ROM_FN(suj2);

struct BurnDriverD BurnDrvMDsuj2 = {
	"g_suj2", NULL, NULL, "1900",
	"Barkley Shut Up and Jam! 2 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, suj2RomInfo, suj2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman Returns (W) [!]

static struct BurnRomInfo batrRomDesc[]={
	{ "g_batr.bin", 0x100000, 0x4A3225C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(batr);
STD_ROM_FN(batr);

struct BurnDriverD BurnDrvMDbatr = {
	"g_batr", NULL, NULL, "1900",
	"Batman Returns (W) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batrRomInfo, batrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battletoads (W) [!]

static struct BurnRomInfo btoaRomDesc[]={
	{ "g_btoa.bin", 0x080000, 0xD10E103A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btoa);
STD_ROM_FN(btoa);

struct BurnDriverD BurnDrvMDbtoa = {
	"g_btoa", NULL, NULL, "1900",
	"Battletoads (W) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btoaRomInfo, btoaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chester Cheetah 2 - Wild Wild Quest (U) [!]

static struct BurnRomInfo che2RomDesc[]={
	{ "g_che2.bin", 0x100000, 0xB97B735D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(che2);
STD_ROM_FN(che2);

struct BurnDriverD BurnDrvMDche2 = {
	"g_che2", NULL, NULL, "1900",
	"Chester Cheetah 2 - Wild Wild Quest (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, che2RomInfo, che2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chester Cheetah (U) [c][!]

static struct BurnRomInfo cheRomDesc[]={
	{ "g_che.bin", 0x100000, 0x250E3EC3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(che);
STD_ROM_FN(che);

struct BurnDriverD BurnDrvMDche = {
	"g_che", NULL, NULL, "1900",
	"Chester Cheetah (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cheRomInfo, cheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck Rock (U) [c][!]

static struct BurnRomInfo chukRomDesc[]={
	{ "g_chuk.bin", 0x100000, 0xF8AC454A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chuk);
STD_ROM_FN(chuk);

struct BurnDriverD BurnDrvMDchuk = {
	"g_chuk", NULL, NULL, "1900",
	"Chuck Rock (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chukRomInfo, chukRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Clay Fighter (U) [!]

static struct BurnRomInfo clayRomDesc[]={
	{ "g_clay.bin", 0x200000, 0xB12C1BC1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clay);
STD_ROM_FN(clay);

struct BurnDriverD BurnDrvMDclay = {
	"g_clay", NULL, NULL, "1900",
	"Clay Fighter (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clayRomInfo, clayRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crue Ball (UE) [!]

static struct BurnRomInfo crueRomDesc[]={
	{ "g_crue.bin", 0x080000, 0x4B195FC0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crue);
STD_ROM_FN(crue);

struct BurnDriverD BurnDrvMDcrue = {
	"g_crue", NULL, NULL, "1992",
	"Crue Ball (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crueRomInfo, crueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daffy Duck in Hollywood (E) (M5) [!]

static struct BurnRomInfo daffRomDesc[]={
	{ "g_daff.bin", 0x200000, 0x1FDC66B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daff);
STD_ROM_FN(daff);

struct BurnDriverD BurnDrvMDdaff = {
	"g_daff", NULL, NULL, "1900",
	"Daffy Duck in Hollywood (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daffRomInfo, daffRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Davis Cup World Tour Tennis (UE) [!]

static struct BurnRomInfo daviRomDesc[]={
	{ "g_davi.bin", 0x100000, 0x894686F0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(davi);
STD_ROM_FN(davi);

struct BurnDriverD BurnDrvMDdavi = {
	"g_davi", NULL, NULL, "1900",
	"Davis Cup World Tour Tennis (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daviRomInfo, daviRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Desert Demolition (UE) [!]

static struct BurnRomInfo desdRomDesc[]={
	{ "g_desd.bin", 0x100000, 0xC287343D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(desd);
STD_ROM_FN(desd);

struct BurnDriverD BurnDrvMDdesd = {
	"g_desd", NULL, NULL, "1900",
	"Desert Demolition (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, desdRomInfo, desdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Desert Strike - Return to the Gulf (UE) [!]

static struct BurnRomInfo dstrRomDesc[]={
	{ "g_dstr.bin", 0x100000, 0x67A9860B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dstr);
STD_ROM_FN(dstr);

struct BurnDriver BurnDrvMDdstr = {
	"g_dstr", NULL, NULL, "1900",
	"Desert Strike - Return to the Gulf (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dstrRomInfo, dstrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// DJ Boy (U) [!]

static struct BurnRomInfo djbyRomDesc[]={
	{ "g_djby.bin", 0x080000, 0xDC9F02DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(djby);
STD_ROM_FN(djby);

struct BurnDriverD BurnDrvMDdjby = {
	"g_djby", NULL, NULL, "1900",
	"DJ Boy (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, djbyRomInfo, djbyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Doom Troopers - The Mutant Chronicles (U) [c][!]

static struct BurnRomInfo dtroRomDesc[]={
	{ "g_dtro.bin", 0x200000, 0x11194414, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dtro);
STD_ROM_FN(dtro);

struct BurnDriverD BurnDrvMDdtro = {
	"g_dtro", NULL, NULL, "1900",
	"Doom Troopers - The Mutant Chronicles (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dtroRomInfo, dtroRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO The Dolphin (UE) [!]

static struct BurnRomInfo eccoRomDesc[]={
	{ "g_ecco.bin", 0x100000, 0x45547390, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecco);
STD_ROM_FN(ecco);

struct BurnDriverD BurnDrvMDecco = {
	"g_ecco", NULL, NULL, "199?",
	"ECCO The Dolphin (UE) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eccoRomInfo, eccoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESPN SpeedWorld (U) [c][!]

static struct BurnRomInfo e_swRomDesc[]={
	{ "g_e-sw.bin", 0x200000, 0xF50BE478, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(e_sw);
STD_ROM_FN(e_sw);

struct BurnDriverD BurnDrvMDe_sw = {
	"g_e_sw", NULL, NULL, "1900",
	"ESPN SpeedWorld (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, e_swRomInfo, e_swRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Eternal Champions (U) [!]

static struct BurnRomInfo etchRomDesc[]={
	{ "g_etch.bin", 0x300000, 0x48F1A42E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(etch);
STD_ROM_FN(etch);

struct BurnDriverD BurnDrvMDetch = {
	"g_etch", NULL, NULL, "1900",
	"Eternal Champions (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, etchRomInfo, etchRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 World Championship Edition (E) [!]

static struct BurnRomInfo f1ceRomDesc[]={
	{ "g_f1ce.bin", 0x200000, 0x74CEE0A7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1ce);
STD_ROM_FN(f1ce);

struct BurnDriverD BurnDrvMDf1ce = {
	"g_f1ce", NULL, NULL, "1900",
	"F1 World Championship Edition (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1ceRomInfo, f1ceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flicky (UE) [!]

static struct BurnRomInfo flicRomDesc[]={
	{ "g_flic.bin", 0x020000, 0x4291C8AB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(flic);
STD_ROM_FN(flic);

struct BurnDriverD BurnDrvMDflic = {
	"g_flic", NULL, NULL, "1900",
	"Flicky (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, flicRomInfo, flicRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Golden Axe III (J) [!]

static struct BurnRomInfo gax3RomDesc[]={
	{ "g_gax3.bin", 0x100000, 0xC7862EA3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gax3);
STD_ROM_FN(gax3);

struct BurnDriverD BurnDrvMDgax3 = {
	"g_gax3", NULL, NULL, "1900",
	"Golden Axe III (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gax3RomInfo, gax3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Granada (JU) (REV01) [!]

static struct BurnRomInfo granRomDesc[]={
	{ "g_gran.bin", 0x080000, 0xE89D1E66, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gran);
STD_ROM_FN(gran);

struct BurnDriverD BurnDrvMDgran = {
	"g_gran", NULL, NULL, "1900",
	"Granada (JU) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, granRomInfo, granRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hurricanes (E) [!]

static struct BurnRomInfo hurrRomDesc[]={
	{ "g_hurr.bin", 0x200000, 0xDECCC874, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hurr);
STD_ROM_FN(hurr);

struct BurnDriverD BurnDrvMDhurr = {
	"g_hurr", NULL, NULL, "1900",
	"Hurricanes (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hurrRomInfo, hurrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Izzy's Quest for the Olympic Rings (UE) [!]

static struct BurnRomInfo izzyRomDesc[]={
	{ "g_izzy.bin", 0x200000, 0x77B416E4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(izzy);
STD_ROM_FN(izzy);

struct BurnDriverD BurnDrvMDizzy = {
	"g_izzy", NULL, NULL, "1900",
	"Izzy's Quest for the Olympic Rings (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, izzyRomInfo, izzyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Bond 007 - The Duel (UE) [!]

static struct BurnRomInfo bondRomDesc[]={
	{ "g_bond.bin", 0x080000, 0x291A3E4B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bond);
STD_ROM_FN(bond);

struct BurnDriver BurnDrvMDbond = {
	"g_bond", NULL, NULL, "1993",
	"James Bond 007 - The Duel (UE) [!]\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bondRomInfo, bondRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jungle Strike (UE) [!]

static struct BurnRomInfo jstrRomDesc[]={
	{ "g_jstr.bin", 0x200000, 0xA5D29735, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jstr);
STD_ROM_FN(jstr);

struct BurnDriverD BurnDrvMDjstr = {
	"g_jstr", NULL, NULL, "1900",
	"Jungle Strike (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jstrRomInfo, jstrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kid Chameleon (UE) [!]

static struct BurnRomInfo kidcRomDesc[]={
	{ "g_kidc.bin", 0x100000, 0xCE36E6CC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kidc);
STD_ROM_FN(kidc);

struct BurnDriverD BurnDrvMDkidc = {
	"g_kidc", NULL, NULL, "1994",
	"Kid Chameleon (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kidcRomInfo, kidcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lawnmower Ma

static struct BurnRomInfo lawnRomDesc[]={
	{ "g_lawn.bin", 0x100000, 0xA7CACD59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lawn);
STD_ROM_FN(lawn);

struct BurnDriverD BurnDrvMDlawn = {
	"g_lawn", NULL, NULL, "1900",
	"Lawnmower Ma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lawnRomInfo, lawnRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lemmings 2 - The Tribes (U) [!]

static struct BurnRomInfo lem2RomDesc[]={
	{ "g_lem2.bin", 0x200000, 0xDE59A3A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lem2);
STD_ROM_FN(lem2);

struct BurnDriverD BurnDrvMDlem2 = {
	"g_lem2", NULL, NULL, "1900",
	"Lemmings 2 - The Tribes (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lem2RomInfo, lem2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lost Viking

static struct BurnRomInfo lostRomDesc[]={
	{ "g_lost.bin", 0x100000, 0x7BA49EDB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lost);
STD_ROM_FN(lost);

struct BurnDriverD BurnDrvMDlost = {
	"g_lost", NULL, NULL, "1900",
	"Lost Viking\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lostRomInfo, lostRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marvel Land (U) [!]

static struct BurnRomInfo marvRomDesc[]={
	{ "g_marv.bin", 0x100000, 0xCD7EEEB7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(marv);
STD_ROM_FN(marv);

struct BurnDriverD BurnDrvMDmarv = {
	"g_marv", NULL, NULL, "1900",
	"Marvel Land (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, marvRomInfo, marvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Megapanel (J) [c][!]

static struct BurnRomInfo megpRomDesc[]={
	{ "g_megp.bin", 0x040000, 0x6240F579, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(megp);
STD_ROM_FN(megp);

struct BurnDriverD BurnDrvMDmegp = {
	"g_megp", NULL, NULL, "1900",
	"Megapanel (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, megpRomInfo, megpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mighty Morphin Power Rangers - The Movie (U) [!]

static struct BurnRomInfo mmpmRomDesc[]={
	{ "g_mmpm.bin", 0x200000, 0xAA941CBC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmpm);
STD_ROM_FN(mmpm);

struct BurnDriverD BurnDrvMDmmpm = {
	"g_mmpm", NULL, NULL, "1900",
	"Mighty Morphin Power Rangers - The Movie (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmpmRomInfo, mmpmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mortal Kombat II (W) [!]

static struct BurnRomInfo mk2RomDesc[]={
	{ "g_mk2.bin", 0x300000, 0xA9E013D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mk2);
STD_ROM_FN(mk2);

struct BurnDriverD BurnDrvMDmk2 = {
	"g_mk2", NULL, NULL, "1900",
	"Mortal Kombat II (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mk2RomInfo, mk2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mortal Kombat 3 (U) [!]

static struct BurnRomInfo mk3RomDesc[]={
	{ "g_mk3.bin", 0x400000, 0xDD638AF6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mk3);
STD_ROM_FN(mk3);

struct BurnDriverD BurnDrvMDmk3 = {
	"g_mk3", NULL, NULL, "1900",
	"Mortal Kombat 3 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mk3RomInfo, mk3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 98 (U) [c][!]

static struct BurnRomInfo nh98RomDesc[]={
	{ "g_nh98.bin", 0x200000, 0x7B64CD98, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh98);
STD_ROM_FN(nh98);

struct BurnDriverD BurnDrvMDnh98 = {
	"g_nh98", NULL, NULL, "1900",
	"NHL 98 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh98RomInfo, nh98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ottifant

static struct BurnRomInfo ottiRomDesc[]={
	{ "g_otti.bin", 0x100000, 0x41AC8003, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(otti);
STD_ROM_FN(otti);

struct BurnDriverD BurnDrvMDotti = {
	"g_otti", NULL, NULL, "1900",
	"Ottifant\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ottiRomInfo, ottiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star III - Generations of Doom (UE) [!]

static struct BurnRomInfo pst3RomDesc[]={
	{ "g_pst3.bin", 0x0C0000, 0xC6B42B0F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pst3);
STD_ROM_FN(pst3);

struct BurnDriverD BurnDrvMDpst3 = {
	"g_pst3", NULL, NULL, "1991",
	"Phantasy Star III - Generations of Doom (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pst3RomInfo, pst3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pink Goes to Hollywood (U) [!]

static struct BurnRomInfo pinkRomDesc[]={
	{ "g_pink.bin", 0x100000, 0xB5804771, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pink);
STD_ROM_FN(pink);

struct BurnDriverD BurnDrvMDpink = {
	"g_pink", NULL, NULL, "1900",
	"Pink Goes to Hollywood (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pinkRomInfo, pinkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pitfall - The Mayan Adventure (U) [!]

static struct BurnRomInfo pitfRomDesc[]={
	{ "g_pitf.bin", 0x200000, 0xF917E34F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pitf);
STD_ROM_FN(pitf);

struct BurnDriverD BurnDrvMDpitf = {
	"g_pitf", NULL, NULL, "1900",
	"Pitfall - The Mayan Adventure (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pitfRomInfo, pitfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Prince of Persia (U) [!]

static struct BurnRomInfo prinRomDesc[]={
	{ "g_prin.bin", 0x100000, 0x13C181A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(prin);
STD_ROM_FN(prin);

struct BurnDriverD BurnDrvMDprin = {
	"g_prin", NULL, NULL, "1993",
	"Prince of Persia (U) [!]\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, prinRomInfo, prinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Radical Rex (U) [!]

static struct BurnRomInfo radrRomDesc[]={
	{ "g_radr.bin", 0x100000, 0x2E6EEC7E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(radr);
STD_ROM_FN(radr);

struct BurnDriverD BurnDrvMDradr = {
	"g_radr", NULL, NULL, "1900",
	"Radical Rex (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, radrRomInfo, radrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic and Knuckles & Sonic 2 (W) [!]

static struct BurnRomInfo sks2RomDesc[]={
	{ "g_sks2.bin", 0x340000, 0x2AC1E7C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sks2);
STD_ROM_FN(sks2);

struct BurnDriver BurnDrvMDsks2 = {
	"g_sks2", "g_snkn", NULL, "1994",
	"Sonic and Knuckles & Sonic 2 (W) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sks2RomInfo, sks2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man and Venom - Separation Anxiety (U) [!]

static struct BurnRomInfo s_saRomDesc[]={
	{ "g_s-sa.bin", 0x300000, 0x512ADE32, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_sa);
STD_ROM_FN(s_sa);

struct BurnDriverD BurnDrvMDs_sa = {
	"g_s_sa", NULL, NULL, "1900",
	"Spider-Man and Venom - Separation Anxiety (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_saRomInfo, s_saRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse 2 (U) [c][!]

static struct BurnRomInfo spl2RomDesc[]={
	{ "g_spl2.bin", 0x100000, 0x2D1766E9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spl2);
STD_ROM_FN(spl2);

struct BurnDriverD BurnDrvMDspl2 = {
	"g_spl2", NULL, NULL, "1900",
	"Splatterhouse 2 (U) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spl2RomInfo, spl2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Strider II (E) [c][!]

static struct BurnRomInfo striRomDesc[]={
	{ "g_stri.bin", 0x100000, 0xB9D099A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stri);
STD_ROM_FN(stri);

struct BurnDriverD BurnDrvMDstri = {
	"g_stri", NULL, NULL, "1994",
	"Strider II (E) [c][!]\0", NULL, "Tiertex / Capcom / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, striRomInfo, striRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Ninja Turtles - The Hyperstone Heist (U) [!]

static struct BurnRomInfo turtRomDesc[]={
	{ "g_turt.bin", 0x100000, 0x679C41DE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(turt);
STD_ROM_FN(turt);

struct BurnDriverD BurnDrvMDturt = {
	"g_turt", NULL, NULL, "1900",
	"Teenage Mutant Ninja Turtles - The Hyperstone Heist (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, turtRomInfo, turtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tic

static struct BurnRomInfo tickRomDesc[]={
	{ "g_tick.bin", 0x200000, 0x425132F0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tick);
STD_ROM_FN(tick);

struct BurnDriverD BurnDrvMDtick = {
	"g_tick", NULL, NULL, "1900",
	"Tic\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tickRomInfo, tickRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tom and Jerry - Frantic Antics (U) (1994) [!]

static struct BurnRomInfo tomjRomDesc[]={
	{ "g_tomj.bin", 0x100000, 0x3044460C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tomj);
STD_ROM_FN(tomj);

struct BurnDriverD BurnDrvMDtomj = {
	"g_tomj", NULL, NULL, "1900",
	"Tom and Jerry - Frantic Antics (U) (1994) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tomjRomInfo, tomjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ultimate Mortal Kombat 3 (U) [!]

static struct BurnRomInfo umk3RomDesc[]={
	{ "g_umk3.bin", 0x400000, 0x7290770D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(umk3);
STD_ROM_FN(umk3);

struct BurnDriverD BurnDrvMDumk3 = {
	"g_umk3", NULL, NULL, "1900",
	"Ultimate Mortal Kombat 3 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, umk3RomInfo, umk3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Undead Line (J) [!]

static struct BurnRomInfo udedRomDesc[]={
	{ "g_uded.bin", 0x100000, 0xFB3CA1E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uded);
STD_ROM_FN(uded);

struct BurnDriverD BurnDrvMDuded = {
	"g_uded", NULL, NULL, "1900",
	"Undead Line (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, udedRomInfo, udedRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Urban Strike (UE) [!]

static struct BurnRomInfo ustrRomDesc[]={
	{ "g_ustr.bin", 0x200000, 0xCF690A75, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ustr);
STD_ROM_FN(ustr);

struct BurnDriverD BurnDrvMDustr = {
	"g_ustr", NULL, NULL, "1900",
	"Urban Strike (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ustrRomInfo, ustrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mutant League Hockey (UE) [!]

static struct BurnRomInfo muthRomDesc[]={
	{ "g_muth.bin", 0x200000, 0x3529180F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(muth);
STD_ROM_FN(muth);

struct BurnDriverD BurnDrvMDmuth = {
	"g_muth", NULL, NULL, "1900",
	"Mutant League Hockey (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, muthRomInfo, muthRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadow of the Beast (UE) [!]

static struct BurnRomInfo sbeaRomDesc[]={
	{ "g_sbea.bin", 0x100000, 0xBD385C27, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbea);
STD_ROM_FN(sbea);

struct BurnDriverD BurnDrvMDsbea = {
	"g_sbea", NULL, NULL, "1900",
	"Shadow of the Beast (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sbeaRomInfo, sbeaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alex Kidd in the Enchanted Castle (U) [!]

static struct BurnRomInfo alexRomDesc[]={
	{ "g_alex.bin", 0x040000, 0x47DBA0AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alex);
STD_ROM_FN(alex);

struct BurnDriverD BurnDrvMDalex = {
	"g_alex", NULL, NULL, "1989",
	"Alex Kidd in the Enchanted Castle (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alexRomInfo, alexRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battletoads and Double Dragon (U) [c][!]

static struct BurnRomInfo btddRomDesc[]={
	{ "g_btdd.bin", 0x100000, 0x8239DD17, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btdd);
STD_ROM_FN(btdd);

struct BurnDriver BurnDrvMDbtdd = {
	"g_btdd", NULL, NULL, "1900",
	"Battletoads and Double Dragon (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btddRomInfo, btddRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chakan - The Forever Man (UE) [!]

static struct BurnRomInfo chakRomDesc[]={
	{ "g_chak.bin", 0x100000, 0x046A48DE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chak);
STD_ROM_FN(chak);

struct BurnDriverD BurnDrvMDchak = {
	"g_chak", NULL, NULL, "1900",
	"Chakan - The Forever Man (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chakRomInfo, chakRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blades of Vengeance (UE) [!]

static struct BurnRomInfo blavRomDesc[]={
	{ "g_blav.bin", 0x100000, 0x74C65A49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blav);
STD_ROM_FN(blav);

struct BurnDriverD BurnDrvMDblav = {
	"g_blav", NULL, NULL, "1900",
	"Blades of Vengeance (UE) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blavRomInfo, blavRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Budokan - The Martial Spirit (U) [c][!]

static struct BurnRomInfo budoRomDesc[]={
	{ "g_budo.bin", 0x080000, 0xACD9F5FC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(budo);
STD_ROM_FN(budo);

struct BurnDriver BurnDrvMDbudo = {
	"g_budo", NULL, NULL, "1900",
	"Budokan - The Martial Spirit (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, budoRomInfo, budoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cliffhanger (U) [c][!]

static struct BurnRomInfo clifRomDesc[]={
	{ "g_clif.bin", 0x100000, 0x9CBF44D3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clif);
STD_ROM_FN(clif);

struct BurnDriverD BurnDrvMDclif = {
	"g_clif", NULL, NULL, "1900",
	"Cliffhanger (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clifRomInfo, clifRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Columns III - Revenge of Columns (U) [!]

static struct BurnRomInfo col3RomDesc[]={
	{ "g_col3.bin", 0x080000, 0xDC678F6D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(col3);
STD_ROM_FN(col3);

struct BurnDriverD BurnDrvMDcol3 = {
	"g_col3", NULL, NULL, "1994",
	"Columns III - Revenge of Columns (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, col3RomInfo, col3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cutthroat Island (UE) [!]

static struct BurnRomInfo cuttRomDesc[]={
	{ "g_cutt.bin", 0x200000, 0xEBABBC70, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cutt);
STD_ROM_FN(cutt);

struct BurnDriverD BurnDrvMDcutt = {
	"g_cutt", NULL, NULL, "1900",
	"Cutthroat Island (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cuttRomInfo, cuttRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dangerous Seed (J) [!]

static struct BurnRomInfo dangRomDesc[]={
	{ "g_dang.bin", 0x080000, 0xA2990031, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dang);
STD_ROM_FN(dang);

struct BurnDriverD BurnDrvMDdang = {
	"g_dang", NULL, NULL, "1900",
	"Dangerous Seed (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dangRomInfo, dangRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Darius II (J) [c][!]

static struct BurnRomInfo dar2RomDesc[]={
	{ "g_dar2.bin", 0x100000, 0x25DFE62A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dar2);
STD_ROM_FN(dar2);

struct BurnDriverD BurnDrvMDdar2 = {
	"g_dar2", NULL, NULL, "1900",
	"Darius II (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dar2RomInfo, dar2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Death Duel (U) [!]

static struct BurnRomInfo duelRomDesc[]={
	{ "g_duel.bin", 0x100000, 0xA9804DCC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(duel);
STD_ROM_FN(duel);

struct BurnDriverD BurnDrvMDduel = {
	"g_duel", NULL, NULL, "1900",
	"Death Duel (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, duelRomInfo, duelRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Demolition Man (UE) [!]

static struct BurnRomInfo demoRomDesc[]={
	{ "g_demo.bin", 0x200000, 0x5FF71877, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(demo);
STD_ROM_FN(demo);

struct BurnDriverD BurnDrvMDdemo = {
	"g_demo", NULL, NULL, "1900",
	"Demolition Man (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, demoRomInfo, demoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dick Tracy (W) [c][!]

static struct BurnRomInfo dickRomDesc[]={
	{ "g_dick.bin", 0x080000, 0xEF887533, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dick);
STD_ROM_FN(dick);

struct BurnDriverD BurnDrvMDdick = {
	"g_dick", NULL, NULL, "1900",
	"Dick Tracy (W) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dickRomInfo, dickRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Doraemon - Yume Dorobouto 7 Nin No Gozansu (J) [!]

static struct BurnRomInfo doraRomDesc[]={
	{ "g_dora.bin", 0x080000, 0xEEED1130, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dora);
STD_ROM_FN(dora);

struct BurnDriverD BurnDrvMDdora = {
	"g_dora", NULL, NULL, "1900",
	"Doraemon - Yume Dorobouto 7 Nin No Gozansu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, doraRomInfo, doraRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Duke Nukem 3D (B) [!]

static struct BurnRomInfo dn3dRomDesc[]={
	{ "g_dn3d.bin", 0x400000, 0x6BD2ACCB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dn3d);
STD_ROM_FN(dn3d);

struct BurnDriverD BurnDrvMDdn3d = {
	"g_dn3d", NULL, NULL, "1900",
	"Duke Nukem 3D (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dn3dRomInfo, dn3dRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// El Viento (U) [!]

static struct BurnRomInfo elviRomDesc[]={
	{ "g_elvi.bin", 0x100000, 0x070A1CEB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(elvi);
STD_ROM_FN(elvi);

struct BurnDriverD BurnDrvMDelvi = {
	"g_elvi", NULL, NULL, "1900",
	"El Viento (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, elviRomInfo, elviRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatal Fury 2 (U) [c][!]

static struct BurnRomInfo faf2RomDesc[]={
	{ "g_faf2.bin", 0x300000, 0x1B1754CB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(faf2);
STD_ROM_FN(faf2);

struct BurnDriverD BurnDrvMDfaf2 = {
	"g_faf2", NULL, NULL, "1994",
	"Fatal Fury 2 (U) [c][!]\0", NULL, "SNK / Takara", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, faf2RomInfo, faf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatal Fury (U) [!]

static struct BurnRomInfo fafRomDesc[]={
	{ "g_faf.bin", 0x180000, 0x98D49170, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(faf);
STD_ROM_FN(faf);

struct BurnDriverD BurnDrvMDfaf = {
	"g_faf", NULL, NULL, "1993",
	"Fatal Fury (U) [!]\0", NULL, "SNK / Takara", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fafRomInfo, fafRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Final Zone (JU) [!]

static struct BurnRomInfo fzonRomDesc[]={
	{ "g_fzon.bin", 0x080000, 0x731FA4A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fzon);
STD_ROM_FN(fzon);

struct BurnDriverD BurnDrvMDfzon = {
	"g_fzon", NULL, NULL, "1900",
	"Final Zone (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fzonRomInfo, fzonRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flintstone

static struct BurnRomInfo flinRomDesc[]={
	{ "g_flin.bin", 0x080000, 0x7C982C59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(flin);
STD_ROM_FN(flin);

struct BurnDriverD BurnDrvMDflin = {
	"g_flin", NULL, NULL, "1900",
	"Flintstone\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, flinRomInfo, flinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// General Chaos (UE) [!]

static struct BurnRomInfo gencRomDesc[]={
	{ "g_genc.bin", 0x100000, 0xF1ECC4DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(genc);
STD_ROM_FN(genc);

struct BurnDriverD BurnDrvMDgenc = {
	"g_genc", NULL, NULL, "1900",
	"General Chaos (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gencRomInfo, gencRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Generations Lost (UE) [!]

static struct BurnRomInfo glosRomDesc[]={
	{ "g_glos.bin", 0x100000, 0x131F36A6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(glos);
STD_ROM_FN(glos);

struct BurnDriverD BurnDrvMDglos = {
	"g_glos", NULL, NULL, "1900",
	"Generations Lost (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, glosRomInfo, glosRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ghostbusters (W) (REV01) [!]

static struct BurnRomInfo gbusRomDesc[]={
	{ "g_gbus.bin", 0x080000, 0x792DF93B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gbus);
STD_ROM_FN(gbus);

struct BurnDriverD BurnDrvMDgbus = {
	"g_gbus", NULL, NULL, "1900",
	"Ghostbusters (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gbusRomInfo, gbusRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Head-On Soccer (U) (M5) [!]

static struct BurnRomInfo hosoRomDesc[]={
	{ "g_hoso.bin", 0x200000, 0xDCFFA327, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hoso);
STD_ROM_FN(hoso);

struct BurnDriverD BurnDrvMDhoso = {
	"g_hoso", NULL, NULL, "1900",
	"Head-On Soccer (U) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hosoRomInfo, hosoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Home Alone (U) [!]

static struct BurnRomInfo homeRomDesc[]={
	{ "g_home.bin", 0x080000, 0xAA0D4387, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(home);
STD_ROM_FN(home);

struct BurnDriverD BurnDrvMDhome = {
	"g_home", NULL, NULL, "1900",
	"Home Alone (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, homeRomInfo, homeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Home Alone 2 - Lost in New York (U) [!]

static struct BurnRomInfo hom2RomDesc[]={
	{ "g_hom2.bin", 0x080000, 0xCBF87C14, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hom2);
STD_ROM_FN(hom2);

struct BurnDriverD BurnDrvMDhom2 = {
	"g_hom2", NULL, NULL, "1900",
	"Home Alone 2 - Lost in New York (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hom2RomInfo, hom2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Immorta

static struct BurnRomInfo immoRomDesc[]={
	{ "g_immo.bin", 0x100000, 0xF653C508, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(immo);
STD_ROM_FN(immo);

struct BurnDriverD BurnDrvMDimmo = {
	"g_immo", NULL, NULL, "1900",
	"Immorta\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, immoRomInfo, immoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Incredible Crash Dummie

static struct BurnRomInfo icdRomDesc[]={
	{ "g_icd.bin", 0x100000, 0x1F6E574A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(icd);
STD_ROM_FN(icd);

struct BurnDriverD BurnDrvMDicd = {
	"g_icd", NULL, NULL, "1900",
	"Incredible Crash Dummie\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, icdRomInfo, icdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Incredible Hul

static struct BurnRomInfo hulkRomDesc[]={
	{ "g_hulk.bin", 0x200000, 0x84A5A2DC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hulk);
STD_ROM_FN(hulk);

struct BurnDriverD BurnDrvMDhulk = {
	"g_hulk", NULL, NULL, "1900",
	"Incredible Hul\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hulkRomInfo, hulkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Junction (JU) [!]

static struct BurnRomInfo juncRomDesc[]={
	{ "g_junc.bin", 0x080000, 0x94CDCE8D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(junc);
STD_ROM_FN(junc);

struct BurnDriverD BurnDrvMDjunc = {
	"g_junc", NULL, NULL, "1900",
	"Junction (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, juncRomInfo, juncRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park (U) [!]

static struct BurnRomInfo jparRomDesc[]={
	{ "g_jpar.bin", 0x200000, 0x7B31DEEF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jpar);
STD_ROM_FN(jpar);

struct BurnDriverD BurnDrvMDjpar = {
	"g_jpar", NULL, NULL, "1900",
	"Jurassic Park (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jparRomInfo, jparRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lightening Force - Quest for the Darkstar (U) [c][!]

static struct BurnRomInfo lighRomDesc[]={
	{ "g_ligh.bin", 0x200000, 0xBEB715DC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ligh);
STD_ROM_FN(ligh);

struct BurnDriverD BurnDrvMDligh = {
	"g_ligh", NULL, NULL, "1992",
	"Lightening Force - Quest for the Darkstar (U) [c][!]\0", NULL, "Tecnosoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lighRomInfo, lighRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mary Shelley's Frankenstein (U) [!]

static struct BurnRomInfo franRomDesc[]={
	{ "g_fran.bin", 0x200000, 0x48993DC3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fran);
STD_ROM_FN(fran);

struct BurnDriverD BurnDrvMDfran = {
	"g_fran", NULL, NULL, "1900",
	"Mary Shelley's Frankenstein (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, franRomInfo, franRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Minnesota Fats Pool Legend (U) [!]

static struct BurnRomInfo mfplRomDesc[]={
	{ "g_mfpl.bin", 0x100000, 0x38174F40, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mfpl);
STD_ROM_FN(mfpl);

struct BurnDriverD BurnDrvMDmfpl = {
	"g_mfpl", NULL, NULL, "1900",
	"Minnesota Fats Pool Legend (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mfplRomInfo, mfplRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Onslaught (U) [c][!]

static struct BurnRomInfo onslRomDesc[]={
	{ "g_onsl.bin", 0x080000, 0x9F19D6DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(onsl);
STD_ROM_FN(onsl);

struct BurnDriverD BurnDrvMDonsl = {
	"g_onsl", NULL, NULL, "1900",
	"Onslaught (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, onslRomInfo, onslRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pengo (J) [!]

static struct BurnRomInfo pengRomDesc[]={
	{ "g_peng.bin", 0x100000, 0xD1E2324B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(peng);
STD_ROM_FN(peng);

struct BurnDriverD BurnDrvMDpeng = {
	"g_peng", NULL, NULL, "1900",
	"Pengo (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pengRomInfo, pengRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rainbow Islands - The Story of Bubble Bobble 2 (J) [c][!]

static struct BurnRomInfo rainRomDesc[]={
	{ "g_rain.bin", 0x080000, 0xC74DCB35, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rain);
STD_ROM_FN(rain);

struct BurnDriverD BurnDrvMDrain = {
	"g_rain", NULL, NULL, "1900",
	"Rainbow Islands - The Story of Bubble Bobble 2 (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rainRomInfo, rainRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ren and Stimpy Sho

static struct BurnRomInfo rensRomDesc[]={
	{ "g_rens.bin", 0x100000, 0xD9503BA5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rens);
STD_ROM_FN(rens);

struct BurnDriverD BurnDrvMDrens = {
	"g_rens", NULL, NULL, "1900",
	"Ren and Stimpy Sho\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rensRomInfo, rensRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robocop Versus The Terminator (U) [!]

static struct BurnRomInfo robtRomDesc[]={
	{ "g_robt.bin", 0x200000, 0xBBAD77A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robt);
STD_ROM_FN(robt);

struct BurnDriverD BurnDrvMDrobt = {
	"g_robt", NULL, NULL, "1993",
	"Robocop Versus The Terminator (U) [!]\0", NULL, "Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robtRomInfo, robtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining in the Darkness (UE) [!]

static struct BurnRomInfo sitdRomDesc[]={
	{ "g_sitd.bin", 0x100000, 0x4D2785BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sitd);
STD_ROM_FN(sitd);

struct BurnDriverD BurnDrvMDsitd = {
	"g_sitd", NULL, NULL, "1991",
	"Shining in the Darkness (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sitdRomInfo, sitdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Simpsons, The - Bart's Nightmare (UE) (REV02) [!]

static struct BurnRomInfo btnmRomDesc[]={
	{ "g_btnm.bin", 0x100000, 0x24D7507C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btnm);
STD_ROM_FN(btnm);

struct BurnDriverD BurnDrvMDbtnm = {
	"g_btnm", NULL, NULL, "1900",
	"Simpsons, The - Bart's Nightmare (UE) (REV02) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btnmRomInfo, btnmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Smurf

static struct BurnRomInfo smfRomDesc[]={
	{ "g_smf.bin", 0x100000, 0x88B30EFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smf);
STD_ROM_FN(smf);

struct BurnDriverD BurnDrvMDsmf = {
	"g_smf", NULL, NULL, "1900",
	"Smurf\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smfRomInfo, smfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Smurfs 

static struct BurnRomInfo smf2RomDesc[]={
	{ "g_smf2.bin", 0x100000, 0xB28BDD69, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smf2);
STD_ROM_FN(smf2);

struct BurnDriverD BurnDrvMDsmf2 = {
	"g_smf2", NULL, NULL, "1900",
	"Smurfs \0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smf2RomInfo, smf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic and Knuckles (W) [!]

static struct BurnRomInfo snknRomDesc[]={
	{ "g_snkn.bin", 0x200000, 0x0658F691, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(snkn);
STD_ROM_FN(snkn);

struct BurnDriver BurnDrvMDsnkn = {
	"g_snkn", NULL, NULL, "1994",
	"Sonic and Knuckles (W) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, snknRomInfo, snknRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man and Venom - Maximum Carnage (W) [!]

static struct BurnRomInfo s_mcRomDesc[]={
	{ "g_s_mc.bin", 0x200000, 0x8FA0B6E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_mc);
STD_ROM_FN(s_mc);

struct BurnDriverD BurnDrvMDs_mc = {
	"g_s_mc", NULL, NULL, "1900",
	"Spider-Man and Venom - Maximum Carnage (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_mcRomInfo, s_mcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Stargate (UE) [!]

static struct BurnRomInfo sgatRomDesc[]={
	{ "g_sgat.bin", 0x200000, 0xE587069E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sgat);
STD_ROM_FN(sgat);

struct BurnDriverD BurnDrvMDsgat = {
	"g_sgat", NULL, NULL, "1900",
	"Stargate (UE) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sgatRomInfo, sgatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Task Force Harrier EX (U) [!]

static struct BurnRomInfo tfhRomDesc[]={
	{ "g_tfh.bin", 0x100000, 0xC8BB0257, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tfh);
STD_ROM_FN(tfh);

struct BurnDriverD BurnDrvMDtfh = {
	"g_tfh", NULL, NULL, "1900",
	"Task Force Harrier EX (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tfhRomInfo, tfhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Ninja Turtles - Tournament Fighters (U) [c][!]

static struct BurnRomInfo tutfRomDesc[]={
	{ "g_tutf.bin", 0x200000, 0x95B5484D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tutf);
STD_ROM_FN(tutf);

struct BurnDriverD BurnDrvMDtutf = {
	"g_tutf", NULL, NULL, "1900",
	"Teenage Mutant Ninja Turtles - Tournament Fighters (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tutfRomInfo, tutfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Force III (JU) [!]

static struct BurnRomInfo tf3RomDesc[]={
	{ "g_tf3.bin", 0x080000, 0x1B3F399A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tf3);
STD_ROM_FN(tf3);

struct BurnDriverD BurnDrvMDtf3 = {
	"g_tf3", NULL, NULL, "1900",
	"Thunder Force III (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tf3RomInfo, tf3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tiny Toon Adventures - Acme All-Stars (U) [!]

static struct BurnRomInfo ttaaRomDesc[]={
	{ "g_ttaa.bin", 0x100000, 0x2F9FAA1D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ttaa);
STD_ROM_FN(ttaa);

struct BurnDriverD BurnDrvMDttaa = {
	"g_ttaa", NULL, NULL, "1900",
	"Tiny Toon Adventures - Acme All-Stars (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ttaaRomInfo, ttaaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Trampoline Terror! (U) [!]

static struct BurnRomInfo tterRomDesc[]={
	{ "g_tter.bin", 0x040000, 0xAABB349F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tter);
STD_ROM_FN(tter);

struct BurnDriverD BurnDrvMDtter = {
	"g_tter", NULL, NULL, "1900",
	"Trampoline Terror! (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tterRomInfo, tterRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Universal Soldier (U) [!]

static struct BurnRomInfo unisRomDesc[]={
	{ "g_unis.bin", 0x100000, 0x352EBD49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(unis);
STD_ROM_FN(unis);

struct BurnDriverD BurnDrvMDunis = {
	"g_unis", NULL, NULL, "1900",
	"Universal Soldier (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, unisRomInfo, unisRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// VR Troopers (UE) [!]

static struct BurnRomInfo vrtrRomDesc[]={
	{ "g_vrtr.bin", 0x200000, 0x2F35516E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vrtr);
STD_ROM_FN(vrtr);

struct BurnDriverD BurnDrvMDvrtr = {
	"g_vrtr", NULL, NULL, "1900",
	"VR Troopers (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vrtrRomInfo, vrtrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wayne's World (U) [c][!]

static struct BurnRomInfo waynRomDesc[]={
	{ "g_wayn.bin", 0x100000, 0xD2CF6EBE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wayn);
STD_ROM_FN(wayn);

struct BurnDriverD BurnDrvMDwayn = {
	"g_wayn", NULL, NULL, "1900",
	"Wayne's World (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, waynRomInfo, waynRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Weaponlord (U) [!]

static struct BurnRomInfo weapRomDesc[]={
	{ "g_weap.bin", 0x300000, 0xB9895365, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(weap);
STD_ROM_FN(weap);

struct BurnDriverD BurnDrvMDweap = {
	"g_weap", NULL, NULL, "1900",
	"Weaponlord (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, weapRomInfo, weapRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// WWF Wrestlemania Arcade (U) [!]

static struct BurnRomInfo wmarRomDesc[]={
	{ "g_wmar.bin", 0x400000, 0xA5D023F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wmar);
STD_ROM_FN(wmar);

struct BurnDriverD BurnDrvMDwmar = {
	"g_wmar", NULL, NULL, "1900",
	"WWF Wrestlemania Arcade (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wmarRomInfo, wmarRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// X-Men 2 - Clone Wars (UE) [!]

static struct BurnRomInfo xme2RomDesc[]={
	{ "g_xme2.bin", 0x200000, 0x710BC628, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xme2);
STD_ROM_FN(xme2);

struct BurnDriverD BurnDrvMDxme2 = {
	"g_xme2", NULL, NULL, "1900",
	"X-Men 2 - Clone Wars (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xme2RomInfo, xme2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Yogi Bear's Cartoon Capers (E) [!]

static struct BurnRomInfo yogiRomDesc[]={
	{ "g_yogi.bin", 0x100000, 0x204F97D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yogi);
STD_ROM_FN(yogi);

struct BurnDriverD BurnDrvMDyogi = {
	"g_yogi", NULL, NULL, "1900",
	"Yogi Bear's Cartoon Capers (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yogiRomInfo, yogiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Off Road (U) [!]

static struct BurnRomInfo soffRomDesc[]={
	{ "g_soff.bin", 0x080000, 0x8F2FDADA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soff);
STD_ROM_FN(soff);

struct BurnDriverD BurnDrvMDsoff = {
	"g_soff", NULL, NULL, "1900",
	"Super Off Road (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soffRomInfo, soffRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Dragon (U) [!]

static struct BurnRomInfo ddrRomDesc[]={
	{ "g_ddr.bin", 0x080000, 0x054F5D53, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddr);
STD_ROM_FN(ddr);

struct BurnDriverD BurnDrvMDddr = {
	"g_ddr", NULL, NULL, "1900",
	"Double Dragon (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddrRomInfo, ddrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Dragon 2 - The Revenge (J) [!]

static struct BurnRomInfo ddr2RomDesc[]={
	{ "g_ddr2.bin", 0x080000, 0xA8BFDBD6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddr2);
STD_ROM_FN(ddr2);

struct BurnDriverD BurnDrvMDddr2 = {
	"g_ddr2", NULL, NULL, "1900",
	"Double Dragon 2 - The Revenge (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddr2RomInfo, ddr2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Dragon 3 - The Rosetta Stone (UE) [!]

static struct BurnRomInfo ddr3RomDesc[]={
	{ "g_ddr3.bin", 0x100000, 0xB36AB75C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddr3);
STD_ROM_FN(ddr3);

struct BurnDriverD BurnDrvMDddr3 = {
	"g_ddr3", NULL, NULL, "1900",
	"Double Dragon 3 - The Rosetta Stone (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddr3RomInfo, ddr3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Dragon V - The Shadow Falls (U) [!]

static struct BurnRomInfo ddrvRomDesc[]={
	{ "g_ddrv.bin", 0x300000, 0x27E59E35, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddrv);
STD_ROM_FN(ddrv);

struct BurnDriverD BurnDrvMDddrv = {
	"g_ddrv", NULL, NULL, "1900",
	"Double Dragon V - The Shadow Falls (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddrvRomInfo, ddrvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Bomberman - 8 Player Demo (Unl)

static struct BurnRomInfo mb8pRomDesc[]={
	{ "g_mb8p.bin", 0x100000, 0xD41C0D81, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mb8p);
STD_ROM_FN(mb8p);

struct BurnDriverD BurnDrvMDmb8p = {
	"g_mb8p", NULL, NULL, "1900",
	"Mega Bomberman - 8 Player Demo (Unl)\0", NULL, "Factor 5", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mb8pRomInfo, mb8pRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fido Dido (Prototype)

static struct BurnRomInfo fidoRomDesc[]={
	{ "g_fido.bin", 0x100000, 0xC6D4A240, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fido);
STD_ROM_FN(fido);

struct BurnDriverD BurnDrvMDfido = {
	"g_fido", NULL, NULL, "1900",
	"Fido Dido (Prototype)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fidoRomInfo, fidoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// TNN Bass Tournament of Champions (U) (REV01) [!]

static struct BurnRomInfo tnnbRomDesc[]={
	{ "g_tnnb.bin", 0x100000, 0xC83FFA1B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tnnb);
STD_ROM_FN(tnnb);

struct BurnDriverD BurnDrvMDtnnb = {
	"g_tnnb", NULL, NULL, "1900",
	"TNN Bass Tournament of Champions (U) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tnnbRomInfo, tnnbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// TNN Outdoors Bass Tournament '96 (U) [!]

static struct BurnRomInfo tnnoRomDesc[]={
	{ "g_tnno.bin", 0x200000, 0x5C523C0B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tnno);
STD_ROM_FN(tnno);

struct BurnDriverD BurnDrvMDtnno = {
	"g_tnno", NULL, NULL, "1900",
	"TNN Outdoors Bass Tournament '96 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tnnoRomInfo, tnnoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sesame Street Counting Cafe (U) [!]

static struct BurnRomInfo ssccRomDesc[]={
	{ "g_sscc.bin", 0x100000, 0x0A4F48C3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sscc);
STD_ROM_FN(sscc);

struct BurnDriverD BurnDrvMDsscc = {
	"g_sscc", NULL, NULL, "1900",
	"Sesame Street Counting Cafe (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ssccRomInfo, ssccRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// X-perts (U) [!]

static struct BurnRomInfo xperRomDesc[]={
	{ "g_xper.bin", 0x400000, 0x57E8ABFD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xper);
STD_ROM_FN(xper);

struct BurnDriverD BurnDrvMDxper = {
	"g_xper", NULL, NULL, "1996",
	"X-perts (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xperRomInfo, xperRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman - Revenge of the Joker (U) [!]

static struct BurnRomInfo batjRomDesc[]={
	{ "g_batj.bin", 0x100000, 0xCAA044A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(batj);
STD_ROM_FN(batj);

struct BurnDriverD BurnDrvMDbatj = {
	"g_batj", NULL, NULL, "1900",
	"Batman - Revenge of the Joker (U) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batjRomInfo, batjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman Forever (W) [!]

static struct BurnRomInfo batRomDesc[]={
	{ "g_bat.bin", 0x080000, 0x017410AE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bat);
STD_ROM_FN(bat);

struct BurnDriver BurnDrvMDbat = {
	"g_bat", NULL, NULL, "1900",
	"Batman (U)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batRomInfo, batRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battle Squadron (UE) [!]

static struct BurnRomInfo bsquRomDesc[]={
	{ "g_bsqu.bin", 0x080000, 0x0FEAA8BF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bsqu);
STD_ROM_FN(bsqu);

struct BurnDriver BurnDrvMDbsqu = {
	"g_bsqu", NULL, NULL, "1900",
	"Battle Squadron (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bsquRomInfo, bsquRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crack Down (U) [!]

static struct BurnRomInfo crkdRomDesc[]={
	{ "g_crkd.bin", 0x080000, 0xB9CE9051, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crkd);
STD_ROM_FN(crkd);

struct BurnDriverD BurnDrvMDcrkd = {
	"g_crkd", NULL, NULL, "1900",
	"Crack Down (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crkdRomInfo, crkdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dune - The Battle for Arrakis (U) [!]

static struct BurnRomInfo duneRomDesc[]={
	{ "g_dune.bin", 0x100000, 0x4DEA40BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dune);
STD_ROM_FN(dune);

struct BurnDriverD BurnDrvMDdune = {
	"g_dune", NULL, NULL, "1900",
	"Dune - The Battle for Arrakis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, duneRomInfo, duneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Earnest Evans (U) [!]

static struct BurnRomInfo earnRomDesc[]={
	{ "g_earn.bin", 0x100000, 0xA243816D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(earn);
STD_ROM_FN(earn);

struct BurnDriverD BurnDrvMDearn = {
	"g_earn", NULL, NULL, "1900",
	"Earnest Evans (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, earnRomInfo, earnRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-117 Night Storm (UE) [!]

static struct BurnRomInfo f117RomDesc[]={
	{ "g_f117.bin", 0x200000, 0x1BF67A07, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f117);
STD_ROM_FN(f117);

struct BurnDriverD BurnDrvMDf117 = {
	"g_f117", NULL, NULL, "1900",
	"F-117 Night Storm (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f117RomInfo, f117RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Frogger (U) [!]

static struct BurnRomInfo frogRomDesc[]={
	{ "g_frog.bin", 0x080000, 0xEA2E48C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(frog);
STD_ROM_FN(frog);

struct BurnDriverD BurnDrvMDfrog = {
	"g_frog", NULL, NULL, "1900",
	"Frogger (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, frogRomInfo, frogRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// G-LOC Air Battle (W) [c][!]

static struct BurnRomInfo glocRomDesc[]={
	{ "g_gloc.bin", 0x100000, 0xF2AF886E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gloc);
STD_ROM_FN(gloc);

struct BurnDriverD BurnDrvMDgloc = {
	"g_gloc", NULL, NULL, "1900",
	"G-LOC Air Battle (W) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, glocRomInfo, glocRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Golden Axe II (W) [!]

static struct BurnRomInfo gax2RomDesc[]={
	{ "g_gax2.bin", 0x080000, 0x725E0A18, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gax2);
STD_ROM_FN(gax2);

struct BurnDriverD BurnDrvMDgax2 = {
	"g_gax2", NULL, NULL, "1900",
	"Golden Axe II (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gax2RomInfo, gax2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gunship (E) [c][!]

static struct BurnRomInfo gshiRomDesc[]={
	{ "g_gshi.bin", 0x100000, 0xDA1440C9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gshi);
STD_ROM_FN(gshi);

struct BurnDriverD BurnDrvMDgshi = {
	"g_gshi", NULL, NULL, "1900",
	"Gunship (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gshiRomInfo, gshiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Herzog Zwei (UE) [!]

static struct BurnRomInfo herzRomDesc[]={
	{ "g_herz.bin", 0x080000, 0xA605B65B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(herz);
STD_ROM_FN(herz);

struct BurnDriverD BurnDrvMDherz = {
	"g_herz", NULL, NULL, "1900",
	"Herzog Zwei (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, herzRomInfo, herzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Last Action Hero (U) [!]

static struct BurnRomInfo lastRomDesc[]={
	{ "g_last.bin", 0x100000, 0x15357DDE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(last);
STD_ROM_FN(last);

struct BurnDriverD BurnDrvMDlast = {
	"g_last", NULL, NULL, "1900",
	"Last Action Hero (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lastRomInfo, lastRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// M.U.S.H.A (U) [!]

static struct BurnRomInfo mushRomDesc[]={
	{ "g_mush.bin", 0x080000, 0x58A7F7B4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mush);
STD_ROM_FN(mush);

struct BurnDriverD BurnDrvMDmush = {
	"g_mush", NULL, NULL, "1900",
	"M.U.S.H.A (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mushRomInfo, mushRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Michael Jackson's Moonwalker (W) (REV01) [!]

static struct BurnRomInfo mjmwRomDesc[]={
	{ "g_mjmw.bin", 0x080000, 0x11CE1F9E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mjmw);
STD_ROM_FN(mjmw);

struct BurnDriver BurnDrvMDmjmw = {
	"g_mjmw", NULL, NULL, "1900",
	"Michael Jackson's Moonwalker (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mjmwRomInfo, mjmwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mighty Morphin Power Rangers (U) [!]

static struct BurnRomInfo mmprRomDesc[]={
	{ "g_mmpr.bin", 0x200000, 0x715158A9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmpr);
STD_ROM_FN(mmpr);

struct BurnDriverD BurnDrvMDmmpr = {
	"g_mmpr", NULL, NULL, "1900",
	"Mighty Morphin Power Rangers (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmprRomInfo, mmprRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ms. Pac-Man (U) [!]

static struct BurnRomInfo mpacRomDesc[]={
	{ "g_mpac.bin", 0x020000, 0xAF041BE6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mpac);
STD_ROM_FN(mpac);

struct BurnDriverD BurnDrvMDmpac = {
	"g_mpac", NULL, NULL, "1900",
	"Ms. Pac-Man (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mpacRomInfo, mpacRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nightmare Circus (B) [!]

static struct BurnRomInfo ncirRomDesc[]={
	{ "g_ncir.bin", 0x200000, 0x06DA3217, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ncir);
STD_ROM_FN(ncir);

struct BurnDriverD BurnDrvMDncir = {
	"g_ncir", NULL, NULL, "1900",
	"Nightmare Circus (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ncirRomInfo, ncirRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Gold - Barcelona 92 (U) (M8) [c][!]

static struct BurnRomInfo ogolRomDesc[]={
	{ "g_ogol.bin", 0x080000, 0x339594B4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ogol);
STD_ROM_FN(ogol);

struct BurnDriverD BurnDrvMDogol = {
	"g_ogol", NULL, NULL, "1900",
	"Olympic Gold - Barcelona 92 (U) (M8) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ogolRomInfo, ogolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pac-Mania (U) [!]

static struct BurnRomInfo pacmRomDesc[]={
	{ "g_pacm.bin", 0x040000, 0x74BBA09B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pacm);
STD_ROM_FN(pacm);

struct BurnDriverD BurnDrvMDpacm = {
	"g_pacm", NULL, NULL, "1900",
	"Pac-Mania (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pacmRomInfo, pacmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Power Drive (E) (M5) [!]

static struct BurnRomInfo pdriRomDesc[]={
	{ "g_pdri.bin", 0x100000, 0x8C00AD61, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pdri);
STD_ROM_FN(pdri);

struct BurnDriverD BurnDrvMDpdri = {
	"g_pdri", NULL, NULL, "1900",
	"Power Drive (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pdriRomInfo, pdriRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Race Drivin' (U) [!]

static struct BurnRomInfo raceRomDesc[]={
	{ "g_race.bin", 0x080000, 0xD737CF3D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(race);
STD_ROM_FN(race);

struct BurnDriverD BurnDrvMDrace = {
	"g_race", NULL, NULL, "1993",
	"Race Drivin' (U) [!]\0", NULL, "Tengen / Atari", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, raceRomInfo, raceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadow of the Beast 2 (UE) [!]

static struct BurnRomInfo sbe2RomDesc[]={
	{ "g_sbe2.bin", 0x100000, 0x2DEDE3DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbe2);
STD_ROM_FN(sbe2);

struct BurnDriverD BurnDrvMDsbe2 = {
	"g_sbe2", NULL, NULL, "1900",
	"Shadow of the Beast 2 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sbe2RomInfo, sbe2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shaq Fu (UE) [!]

static struct BurnRomInfo shaqRomDesc[]={
	{ "g_shaq.bin", 0x300000, 0x499955F2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shaq);
STD_ROM_FN(shaq);

struct BurnDriverD BurnDrvMDshaq = {
	"g_shaq", NULL, NULL, "1900",
	"Shaq Fu (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shaqRomInfo, shaqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Simpsons, The - Bart vs The Space Mutants (UE) (REV01) [!]

static struct BurnRomInfo bartRomDesc[]={
	{ "g_bart.bin", 0x080000, 0xDB70E8CA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bart);
STD_ROM_FN(bart);

struct BurnDriver BurnDrvMDbart = {
	"g_bart", NULL, NULL, "1900",
	"Simpsons, The - Bart vs The Space Mutants (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bartRomInfo, bartRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soldiers of Fortune (U) [c][!]

static struct BurnRomInfo soldRomDesc[]={
	{ "g_sold.bin", 0x100000, 0xA77E4E9F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sold);
STD_ROM_FN(sold);

struct BurnDriverD BurnDrvMDsold = {
	"g_sold", NULL, NULL, "1900",
	"Soldiers of Fortune (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soldRomInfo, soldRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Space Invaders 91 (U) [c][!]

static struct BurnRomInfo si91RomDesc[]={
	{ "g_si91.bin", 0x040000, 0xBB83B528, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(si91);
STD_ROM_FN(si91);

struct BurnDriverD BurnDrvMDsi91 = {
	"g_si91", NULL, NULL, "1900",
	"Space Invaders 91 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, si91RomInfo, si91RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man and X-Men - Arcade's Revenge (UE) [!]

static struct BurnRomInfo s_arRomDesc[]={
	{ "g_s_ar.bin", 0x100000, 0x4A4414EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_ar);
STD_ROM_FN(s_ar);

struct BurnDriverD BurnDrvMDs_ar = {
	"g_s_ar", NULL, NULL, "1900",
	"Spider-Man and X-Men - Arcade's Revenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_arRomInfo, s_arRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sunset Riders (U) [!]

static struct BurnRomInfo ssriRomDesc[]={
	{ "g_ssri.bin", 0x080000, 0xAC30C297, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ssri);
STD_ROM_FN(ssri);

struct BurnDriverD BurnDrvMDssri = {
	"g_ssri", NULL, NULL, "1900",
	"Sunset Riders (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ssriRomInfo, ssriRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Smash TV (UE) [!]

static struct BurnRomInfo sstvRomDesc[]={
	{ "g_sstv.bin", 0x080000, 0xF22412B6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sstv);
STD_ROM_FN(sstv);

struct BurnDriverD BurnDrvMDsstv = {
	"g_sstv", NULL, NULL, "1900",
	"Super Smash TV (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sstvRomInfo, sstvRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Target Earth (U) [!]

static struct BurnRomInfo targRomDesc[]={
	{ "g_targ.bin", 0x080000, 0xCDDF62D3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(targ);
STD_ROM_FN(targ);

struct BurnDriverD BurnDrvMDtarg = {
	"g_targ", NULL, NULL, "1900",
	"Target Earth (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, targRomInfo, targRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Terminator 2 - Judgment Day (UE) [!]

static struct BurnRomInfo ter2RomDesc[]={
	{ "g_ter2.bin", 0x100000, 0x2F75E896, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ter2);
STD_ROM_FN(ter2);

struct BurnDriverD BurnDrvMDter2 = {
	"g_ter2", NULL, NULL, "1900",
	"Terminator 2 - Judgment Day (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ter2RomInfo, ter2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Force II (U) [!]

static struct BurnRomInfo tf2RomDesc[]={
	{ "g_tf2.bin", 0x080000, 0x9B1561B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tf2);
STD_ROM_FN(tf2);

struct BurnDriverD BurnDrvMDtf2 = {
	"g_tf2", NULL, NULL, "1900",
	"Thunder Force II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tf2RomInfo, tf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toy Story (E) [!]

static struct BurnRomInfo toysRomDesc[]={
	{ "g_toys.bin", 0x100000, 0xCBC9951B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toys);
STD_ROM_FN(toys);

struct BurnDriverD BurnDrvMDtoys = {
	"g_toys", NULL, NULL, "1900",
	"Toy Story (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toysRomInfo, toysRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// True Lies (W) [!]

static struct BurnRomInfo trueRomDesc[]={
	{ "g_true.bin", 0x200000, 0x18C09468, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(true);
STD_ROM_FN(true);

struct BurnDriverD BurnDrvMDtrue = {
	"g_true", NULL, NULL, "1900",
	"True Lies (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, trueRomInfo, trueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Uncharted Waters - New Horizons (U) [!]

static struct BurnRomInfo uwnhRomDesc[]={
	{ "g_uwnh.bin", 0x200000, 0xEAD69824, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uwnh);
STD_ROM_FN(uwnh);

struct BurnDriverD BurnDrvMDuwnh = {
	"g_uwnh", NULL, NULL, "1900",
	"Uncharted Waters - New Horizons (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, uwnhRomInfo, uwnhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Viewpoint (U) [!]

static struct BurnRomInfo viewRomDesc[]={
	{ "g_view.bin", 0x200000, 0x59C71866, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(view);
STD_ROM_FN(view);

struct BurnDriverD BurnDrvMDview = {
	"g_view", NULL, NULL, "1900",
	"Viewpoint (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, viewRomInfo, viewRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Williams Arcade's Greatest Hits (U) [!]

static struct BurnRomInfo waghRomDesc[]={
	{ "g_wagh.bin", 0x080000, 0xD68E9C00, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wagh);
STD_ROM_FN(wagh);

struct BurnDriverD BurnDrvMDwagh = {
	"g_wagh", NULL, NULL, "1900",
	"Williams Arcade's Greatest Hits (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, waghRomInfo, waghRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Worms (E) [!]

static struct BurnRomInfo wormRomDesc[]={
	{ "g_worm.bin", 0x200000, 0xB9A8B299, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(worm);
STD_ROM_FN(worm);

struct BurnDriverD BurnDrvMDworm = {
	"g_worm", NULL, NULL, "1900",
	"Worms (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wormRomInfo, wormRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Xenon 2 - Megablast (E) [c][!]

static struct BurnRomInfo xen2RomDesc[]={
	{ "g_xen2.bin", 0x080000, 0x59ABE7F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xen2);
STD_ROM_FN(xen2);

struct BurnDriverD BurnDrvMDxen2 = {
	"g_xen2", NULL, NULL, "1900",
	"Xenon 2 - Megablast (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xen2RomInfo, xen2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zany Golf (UE) (REV00) [c][!]

static struct BurnRomInfo zanyRomDesc[]={
	{ "g_zany.bin", 0x080000, 0xED5D12EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zany);
STD_ROM_FN(zany);

struct BurnDriverD BurnDrvMDzany = {
	"g_zany", NULL, NULL, "1900",
	"Zany Golf (UE) (REV00) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zanyRomInfo, zanyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zoop (U) [!]

static struct BurnRomInfo zoopRomDesc[]={
	{ "g_zoop.bin", 0x080000, 0xA899BEFA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zoop);
STD_ROM_FN(zoop);

struct BurnDriverD BurnDrvMDzoop = {
	"g_zoop", NULL, NULL, "1900",
	"Zoop (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zoopRomInfo, zoopRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Art Alive! (W) [!]

static struct BurnRomInfo artaRomDesc[]={
	{ "g_arta.bin", 0x020000, 0xF1B72CDD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arta);
STD_ROM_FN(arta);

struct BurnDriver BurnDrvMDarta = {
	"g_arta", NULL, NULL, "1900",
	"Art Alive! (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, artaRomInfo, artaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Assault Suits Leynos (J) [!]

static struct BurnRomInfo aslRomDesc[]={
	{ "g_asl.bin", 0x080000, 0x81A2C800, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(asl);
STD_ROM_FN(asl);

struct BurnDriverD BurnDrvMDasl = {
	"g_asl", "g_targ", NULL, "1900",
	"Assault Suits Leynos (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aslRomInfo, aslRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arcade Classics (U) [!]

static struct BurnRomInfo arcaRomDesc[]={
	{ "g_arca.bin", 0x080000, 0x8AED2090, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arca);
STD_ROM_FN(arca);

struct BurnDriverD BurnDrvMDarca = {
	"g_arca", NULL, NULL, "1900",
	"Arcade Classics (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arcaRomInfo, arcaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aah! Harimanada (J) [!]

static struct BurnRomInfo aahhRomDesc[]={
	{ "g_aahh.bin", 0x200000, 0x065F6021, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aahh);
STD_ROM_FN(aahh);

struct BurnDriver BurnDrvMDaahh = {
	"g_aahh", NULL, NULL, "1900",
	"Aah! Harimanada (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aahhRomInfo, aahhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aerobiz (U) [!]

static struct BurnRomInfo aeroRomDesc[]={
	{ "g_aero.bin", 0x100000, 0xCFAA9BCE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aero);
STD_ROM_FN(aero);

struct BurnDriver BurnDrvMDaero = {
	"g_aero", NULL, NULL, "199?",
	"Aerobiz (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aeroRomInfo, aeroRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// AWS Pro Moves Soccer (U) [!]

static struct BurnRomInfo awspRomDesc[]={
	{ "g_awsp.bin", 0x080000, 0x707017E5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(awsp);
STD_ROM_FN(awsp);

struct BurnDriver BurnDrvMDawsp = {
	"g_awsp", NULL, NULL, "1900",
	"AWS Pro Moves Soccer (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, awspRomInfo, awspRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Back to the Future Part III (U) [!]

static struct BurnRomInfo bttfRomDesc[]={
	{ "g_bttf.bin", 0x080000, 0x66A388C3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bttf);
STD_ROM_FN(bttf);

struct BurnDriverD BurnDrvMDbttf = {
	"g_bttf", NULL, NULL, "1900",
	"Back to the Future Part III (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bttfRomInfo, bttfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bare Knuckle III (J) [!]

static struct BurnRomInfo bar3RomDesc[]={
	{ "g_bar3.bin", 0x300000, 0x5D09236F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bar3);
STD_ROM_FN(bar3);

struct BurnDriver BurnDrvMDbar3 = {
	"g_bar3", "g_sor3", NULL, "1994",
	"Bare Knuckle III (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bar3RomInfo, bar3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Barkley Shut Up and Jam! 2 (U) [!]

static struct BurnRomInfo sujRomDesc[]={
	{ "g_suj.bin", 0x100000, 0x63FBF497, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(suj);
STD_ROM_FN(suj);

struct BurnDriverD BurnDrvMDsuj = {
	"g_suj", NULL, NULL, "1900",
	"Barkley Shut Up and Jam! 2 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sujRomInfo, sujRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beavis and Butt-head (U) [!]

static struct BurnRomInfo beavRomDesc[]={
	{ "g_beav.bin", 0x200000, 0xF5D7B948, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beav);
STD_ROM_FN(beav);

struct BurnDriver BurnDrvMDbeav = {
	"g_beav", NULL, NULL, "1900",
	"Beavis and Butt-head (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beavRomInfo, beavRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Best of the Best - Championship Karate (U) [c][!]

static struct BurnRomInfo botbRomDesc[]={
	{ "g_botb.bin", 0x100000, 0xC3D6A5D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(botb);
STD_ROM_FN(botb);

struct BurnDriver BurnDrvMDbotb = {
	"g_botb", NULL, NULL, "1900",
	"Best of the Best - Championship Karate (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, botbRomInfo, botbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bishoujo Senshi Sailor Moon (J) [!]

static struct BurnRomInfo sailRomDesc[]={
	{ "g_sail.bin", 0x200000, 0x5E246938, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sail);
STD_ROM_FN(sail);

struct BurnDriverD BurnDrvMDsail = {
	"g_sail", NULL, NULL, "1900",
	"Bishoujo Senshi Sailor Moon (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sailRomInfo, sailRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brian Lara Cricket 96 (E) [c][!]

static struct BurnRomInfo bl96RomDesc[]={
	{ "g_bl96.bin", 0x100000, 0xFA3024AF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bl96);
STD_ROM_FN(bl96);

struct BurnDriverD BurnDrvMDbl96 = {
	"g_bl96", NULL, NULL, "1900",
	"Brian Lara Cricket 96 (E) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bl96RomInfo, bl96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Buck Rogers - Countdown to Doomsday (UE) [!]

static struct BurnRomInfo buckRomDesc[]={
	{ "g_buck.bin", 0x100000, 0x44E3BFFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(buck);
STD_ROM_FN(buck);

struct BurnDriverD BurnDrvMDbuck = {
	"g_buck", NULL, NULL, "1900",
	"Buck Rogers - Countdown to Doomsday (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, buckRomInfo, buckRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Curse (J) [!]

static struct BurnRomInfo cursRomDesc[]={
	{ "g_curs.bin", 0x080000, 0xA4FBF9A9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(curs);
STD_ROM_FN(curs);

struct BurnDriverD BurnDrvMDcurs = {
	"g_curs", NULL, NULL, "1900",
	"Curse (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cursRomInfo, cursRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// HardBall '95 (U) [!]

static struct BurnRomInfo hb95RomDesc[]={
	{ "g_hb95.bin", 0x300000, 0xED10BC9E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hb95);
STD_ROM_FN(hb95);

struct BurnDriverD BurnDrvMDhb95 = {
	"g_hb95", NULL, NULL, "1900",
	"HardBall '95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hb95RomInfo, hb95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Series Baseball '98 (U) [!]

static struct BurnRomInfo ws98RomDesc[]={
	{ "g_ws98.bin", 0x300000, 0x05B1AB53, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ws98);
STD_ROM_FN(ws98);

struct BurnDriverD BurnDrvMDws98 = {
	"g_ws98", NULL, NULL, "1900",
	"World Series Baseball '98 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ws98RomInfo, ws98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dark Castle (UE) [!]

static struct BurnRomInfo darkRomDesc[]={
	{ "g_dark.bin", 0x080000, 0x0464ACA4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dark);
STD_ROM_FN(dark);

struct BurnDriverD BurnDrvMDdark = {
	"g_dark", NULL, NULL, "1900",
	"Dark Castle (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, darkRomInfo, darkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Darwin 4081 (J) [!]

static struct BurnRomInfo g_4081RomDesc[]={
	{ "g_4081.bin", 0x080000, 0x7A33B0CB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_4081);
STD_ROM_FN(g_4081);

struct BurnDriver BurnDrvMDg_4081 = {
	"g_4081", NULL, NULL, "1900",
	"Darwin 4081 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_4081RomInfo, g_4081RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Deadly Moves (U) [!]

static struct BurnRomInfo dmovRomDesc[]={
	{ "g_dmov.bin", 0x100000, 0x35CBD237, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dmov);
STD_ROM_FN(dmov);

struct BurnDriverD BurnDrvMDdmov = {
	"g_dmov", NULL, NULL, "1900",
	"Deadly Moves (U) [!]\0", NULL, "Kaneko", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dmovRomInfo, dmovRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Death and Return of Superma

static struct BurnRomInfo drsRomDesc[]={
	{ "g_drs.bin", 0x200000, 0x982242D3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drs);
STD_ROM_FN(drs);

struct BurnDriverD BurnDrvMDdrs = {
	"g_drs", NULL, NULL, "1900",
	"Death and Return of Superma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, drsRomInfo, drsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dinosaurs for Hire (U) [!]

static struct BurnRomInfo hireRomDesc[]={
	{ "g_hire.bin", 0x100000, 0x39351146, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hire);
STD_ROM_FN(hire);

struct BurnDriverD BurnDrvMDhire = {
	"g_hire", NULL, NULL, "1900",
	"Dinosaurs for Hire (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hireRomInfo, hireRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Clutch (E) [c][!]

static struct BurnRomInfo dblcRomDesc[]={
	{ "g_dblc.bin", 0x040000, 0xD98C623C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dblc);
STD_ROM_FN(dblc);

struct BurnDriverD BurnDrvMDdblc = {
	"g_dblc", NULL, NULL, "1900",
	"Double Clutch (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dblcRomInfo, dblcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Eliminate Down (J) [!]

static struct BurnRomInfo elimRomDesc[]={
	{ "g_elim.bin", 0x100000, 0x48467542, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(elim);
STD_ROM_FN(elim);

struct BurnDriverD BurnDrvMDelim = {
	"g_elim", NULL, NULL, "1900",
	"Eliminate Down (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, elimRomInfo, elimRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESWAT Cyber Police - City Under Siege (U) [!]

static struct BurnRomInfo eswaRomDesc[]={
	{ "g_eswa.bin", 0x080000, 0xE72F8A36, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eswa);
STD_ROM_FN(eswa);

struct BurnDriverD BurnDrvMDeswa = {
	"g_eswa", NULL, NULL, "1900",
	"ESWAT Cyber Police - City Under Siege (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eswaRomInfo, eswaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// European Club Soccer (E) [!]

static struct BurnRomInfo ecsRomDesc[]={
	{ "g_ecs.bin", 0x080000, 0x6A5CF104, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecs);
STD_ROM_FN(ecs);

struct BurnDriver BurnDrvMDecs = {
	"g_ecs", "g_wts", NULL, "1900",
	"European Club Soccer (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecsRomInfo, ecsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fire Mustang (J) [c][!]

static struct BurnRomInfo mustRomDesc[]={
	{ "g_must.bin", 0x080000, 0xEB7E36C3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(must);
STD_ROM_FN(must);

struct BurnDriverD BurnDrvMDmust = {
	"g_must", NULL, NULL, "1900",
	"Fire Mustang (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mustRomInfo, mustRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Golden Axe (W) (REV01) [!]

static struct BurnRomInfo gaxRomDesc[]={
	{ "g_gax.bin", 0x080000, 0x665D7DF9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gax);
STD_ROM_FN(gax);

struct BurnDriver BurnDrvMDgax = {
	"g_gax", NULL, NULL, "1900",
	"Golden Axe (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gaxRomInfo, gaxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Goofy's Hysterical History Tour (U) [!]

static struct BurnRomInfo goofRomDesc[]={
	{ "g_goof.bin", 0x100000, 0x4E1CC833, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(goof);
STD_ROM_FN(goof);

struct BurnDriverD BurnDrvMDgoof = {
	"g_goof", NULL, NULL, "1900",
	"Goofy's Hysterical History Tour (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, goofRomInfo, goofRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// GRIND Stormer (U) [!]

static struct BurnRomInfo grinRomDesc[]={
	{ "g_grin.bin", 0x100000, 0x7E6BEF15, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(grin);
STD_ROM_FN(grin);

struct BurnDriverD BurnDrvMDgrin = {
	"g_grin", NULL, NULL, "1900",
	"GRIND Stormer (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, grinRomInfo, grinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Honoo no Toukyuuji Dodge Danpei (J) [!]

static struct BurnRomInfo dodgRomDesc[]={
	{ "g_dodg.bin", 0x080000, 0x630F07C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dodg);
STD_ROM_FN(dodg);

struct BurnDriverD BurnDrvMDdodg = {
	"g_dodg", NULL, NULL, "1900",
	"Honoo no Toukyuuji Dodge Danpei (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dodgRomInfo, dodgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Indiana Jones and the Last Crusade (U) [c][!]

static struct BurnRomInfo indlRomDesc[]={
	{ "g_indl.bin", 0x100000, 0x3599A3FD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(indl);
STD_ROM_FN(indl);

struct BurnDriverD BurnDrvMDindl = {
	"g_indl", NULL, NULL, "1900",
	"Indiana Jones and the Last Crusade (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, indlRomInfo, indlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jennifer Capriati Tennis (U) [!]

static struct BurnRomInfo jcteRomDesc[]={
	{ "g_jcte.bin", 0x080000, 0xAB2ABC8E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jcte);
STD_ROM_FN(jcte);

struct BurnDriverD BurnDrvMDjcte = {
	"g_jcte", NULL, NULL, "1900",
	"Jennifer Capriati Tennis (U) [!]\0", NULL, "Sega / System Sacom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jcteRomInfo, jcteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Judge Dredd - The Movie (W) [!]

static struct BurnRomInfo jdreRomDesc[]={
	{ "g_jdre.bin", 0x200000, 0xEA342ED8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jdre);
STD_ROM_FN(jdre);

struct BurnDriverD BurnDrvMDjdre = {
	"g_jdre", NULL, NULL, "1995",
	"Judge Dredd - The Movie (W) [!]\0", NULL, "Acclaim / Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jdreRomInfo, jdreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Justice League Task Force (W) [!]

static struct BurnRomInfo jltfRomDesc[]={
	{ "g_jltf.bin", 0x300000, 0x2A60EBE9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jltf);
STD_ROM_FN(jltf);

struct BurnDriverD BurnDrvMDjltf = {
	"g_jltf", NULL, NULL, "1900",
	"Justice League Task Force (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jltfRomInfo, jltfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Magical Taruruuto-Kun (J) [!]

static struct BurnRomInfo taruRomDesc[]={
	{ "g_taru.bin", 0x080000, 0xF11060A5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(taru);
STD_ROM_FN(taru);

struct BurnDriverD BurnDrvMDtaru = {
	"g_taru", NULL, NULL, "1900",
	"Magical Taruruuto-Kun (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taruRomInfo, taruRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Osomatsu-kun - Hachamecha Gekijou (J) [c][!]

static struct BurnRomInfo osomRomDesc[]={
	{ "g_osom.bin", 0x040000, 0x2453350C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(osom);
STD_ROM_FN(osom);

struct BurnDriverD BurnDrvMDosom = {
	"g_osom", NULL, NULL, "1900",
	"Osomatsu-kun - Hachamecha Gekijou (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, osomRomInfo, osomRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puyo Puyo Tsu (J) (REV01) [!]

static struct BurnRomInfo puy2RomDesc[]={
	{ "g_puy2.bin", 0x200000, 0x25B7B2AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puy2);
STD_ROM_FN(puy2);

struct BurnDriverD BurnDrvMDpuy2 = {
	"g_puy2", NULL, NULL, "1900",
	"Puyo Puyo Tsu (J) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puy2RomInfo, puy2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Scooby Doo Mystery (U) [!]

static struct BurnRomInfo scobRomDesc[]={
	{ "g_scob.bin", 0x200000, 0x7BB9DD9B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(scob);
STD_ROM_FN(scob);

struct BurnDriverD BurnDrvMDscob = {
	"g_scob", NULL, NULL, "1900",
	"Scooby Doo Mystery (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, scobRomInfo, scobRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadowrun (U) [!]

static struct BurnRomInfo srunRomDesc[]={
	{ "g_srun.bin", 0x200000, 0xFBB92909, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(srun);
STD_ROM_FN(srun);

struct BurnDriverD BurnDrvMDsrun = {
	"g_srun", NULL, NULL, "1900",
	"Shadowrun (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, srunRomInfo, srunRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Snow Bros. - Nick & Tom (J) [c][!]

static struct BurnRomInfo snowRomDesc[]={
	{ "g_snow.bin", 0x100000, 0x11B56228, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(snow);
STD_ROM_FN(snow);

struct BurnDriverD BurnDrvMDsnow = {
	"g_snow", NULL, NULL, "1900",
	"Snow Bros. - Nick & Tom (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, snowRomInfo, snowRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Speed Ball 2 - Brutal Deluxe (U) [c][!]

static struct BurnRomInfo spb2RomDesc[]={
	{ "g_spb2.bin", 0x080000, 0x9FC340A7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spb2);
STD_ROM_FN(spb2);

struct BurnDriverD BurnDrvMDspb2 = {
	"g_spb2", NULL, NULL, "1900",
	"Speed Ball 2 - Brutal Deluxe (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spb2RomInfo, spb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man - The Animated Series (W) [!]

static struct BurnRomInfo s_asRomDesc[]={
	{ "g_s_as.bin", 0x200000, 0x11B5B590, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_as);
STD_ROM_FN(s_as);

struct BurnDriverD BurnDrvMDs_as = {
	"g_s_as", NULL, NULL, "1995",
	"Spider-Man - The Animated Series (W) [!]\0", NULL, "Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_asRomInfo, s_asRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man vs The Kingpin (W) [!]

static struct BurnRomInfo s_kpRomDesc[]={
	{ "g_s_kp.bin", 0x080000, 0x70AB775F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_kp);
STD_ROM_FN(s_kp);

struct BurnDriverD BurnDrvMDs_kp = {
	"g_s_kp", NULL, NULL, "1900",
	"Spider-Man vs The Kingpin (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_kpRomInfo, s_kpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Steel Empir

static struct BurnRomInfo sempRomDesc[]={
	{ "g_semp.bin", 0x100000, 0xD0E7A0B6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(semp);
STD_ROM_FN(semp);

struct BurnDriverD BurnDrvMDsemp = {
	"g_semp", NULL, NULL, "1994",
	"Steel Empir\0", NULL, "Hot B / Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sempRomInfo, sempRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Koutetsu Teikoku (J) [!]

static struct BurnRomInfo koutRomDesc[]={
	{ "g_kout.bin", 0x100000, 0x755D0B8A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kout);
STD_ROM_FN(kout);

struct BurnDriverD BurnDrvMDkout = {
	"g_kout", NULL, NULL, "1994",
	"Koutetsu Teikoku (J) [!]\0", NULL, "Hot B", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, koutRomInfo, koutRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Airwolf (J) [!]

static struct BurnRomInfo sairRomDesc[]={
	{ "g_sair.bin", 0x080000, 0xFA451982, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sair);
STD_ROM_FN(sair);

struct BurnDriverD BurnDrvMDsair = {
	"g_sair", NULL, NULL, "1991",
	"Super Airwolf (J) [!]\0", NULL, "Kyugo", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sairRomInfo, sairRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Battleship (U) [!]

static struct BurnRomInfo sbatRomDesc[]={
	{ "g_sbat.bin", 0x080000, 0x99CA1BFB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbat);
STD_ROM_FN(sbat);

struct BurnDriverD BurnDrvMDsbat = {
	"g_sbat", NULL, NULL, "1900",
	"Super Battleship (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sbatRomInfo, sbatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Theme Park (UE) [!]

static struct BurnRomInfo tprkRomDesc[]={
	{ "g_tprk.bin", 0x200000, 0x289DA2C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tprk);
STD_ROM_FN(tprk);

struct BurnDriverD BurnDrvMDtprk = {
	"g_tprk", NULL, NULL, "1900",
	"Theme Park (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tprkRomInfo, tprkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tintin Au Tibet (E) (M6) [!]

static struct BurnRomInfo tintRomDesc[]={
	{ "g_tint.bin", 0x200000, 0x4243CAF3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tint);
STD_ROM_FN(tint);

struct BurnDriverD BurnDrvMDtint = {
	"g_tint", NULL, NULL, "1900",
	"Tintin Au Tibet (E) (M6) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tintRomInfo, tintRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Trouble Shooter (U) [!]

static struct BurnRomInfo tshtRomDesc[]={
	{ "g_tsht.bin", 0x080000, 0xBECFC39B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsht);
STD_ROM_FN(tsht);

struct BurnDriver BurnDrvMDtsht = {
	"g_tsht", NULL, NULL, "1900",
	"Trouble Shooter (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tshtRomInfo, tshtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Uchu Senkan Gomora (J) [c][!]

static struct BurnRomInfo gomoRomDesc[]={
	{ "g_gomo.bin", 0x100000, 0xC511E8D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gomo);
STD_ROM_FN(gomo);

struct BurnDriverD BurnDrvMDgomo = {
	"g_gomo", NULL, NULL, "1900",
	"Uchu Senkan Gomora (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gomoRomInfo, gomoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ultimate Soccer (E) [!]

static struct BurnRomInfo usocRomDesc[]={
	{ "g_usoc.bin", 0x100000, 0x83DB6E58, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(usoc);
STD_ROM_FN(usoc);

struct BurnDriverD BurnDrvMDusoc = {
	"g_usoc", NULL, NULL, "1900",
	"Ultimate Soccer (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, usocRomInfo, usocRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// WWF Royal Rumble (W) [!]

static struct BurnRomInfo wfrrRomDesc[]={
	{ "g_wfrr.bin", 0x200000, 0xB69DC53E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wfrr);
STD_ROM_FN(wfrr);

struct BurnDriverD BurnDrvMDwfrr = {
	"g_wfrr", NULL, NULL, "1900",
	"WWF Royal Rumble (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wfrrRomInfo, wfrrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// WWF RAW (W) [!]

static struct BurnRomInfo wfraRomDesc[]={
	{ "g_wfra.bin", 0x300000, 0x4EF5D411, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wfra);
STD_ROM_FN(wfra);

struct BurnDriverD BurnDrvMDwfra = {
	"g_wfra", NULL, NULL, "1900",
	"WWF RAW (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wfraRomInfo, wfraRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wolf Child (U) [c][!]

static struct BurnRomInfo wolfRomDesc[]={
	{ "g_wolf.bin", 0x100000, 0xEB5B1CBF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wolf);
STD_ROM_FN(wolf);

struct BurnDriverD BurnDrvMDwolf = {
	"g_wolf", NULL, NULL, "1900",
	"Wolf Child (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wolfRomInfo, wolfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zoom! (JU) [!]

static struct BurnRomInfo zoomRomDesc[]={
	{ "g_zoom.bin", 0x040000, 0x724D6965, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zoom);
STD_ROM_FN(zoom);

struct BurnDriverD BurnDrvMDzoom = {
	"g_zoom", NULL, NULL, "1900",
	"Zoom! (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zoomRomInfo, zoomRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Resq (Beta)

static struct BurnRomInfo resqRomDesc[]={
	{ "g_resq.bin", 0x100000, 0x558E35E0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(resq);
STD_ROM_FN(resq);

struct BurnDriverD BurnDrvMDresq = {
	"g_resq", NULL, NULL, "1900",
	"Resq (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, resqRomInfo, resqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jelly Boy (Beta)

static struct BurnRomInfo jelyRomDesc[]={
	{ "g_jely.bin", 0x100000, 0x7CFADC16, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jely);
STD_ROM_FN(jely);

struct BurnDriverD BurnDrvMDjely = {
	"g_jely", NULL, NULL, "1900",
	"Jelly Boy (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jelyRomInfo, jelyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Itchy and Scratchy Gam

static struct BurnRomInfo itchRomDesc[]={
	{ "g_itch.bin", 0x100000, 0x81B7725D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(itch);
STD_ROM_FN(itch);

struct BurnDriverD BurnDrvMDitch = {
	"g_itch", NULL, NULL, "1900",
	"Itchy and Scratchy Gam\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, itchRomInfo, itchRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Second Samurai, The (E).

static struct BurnRomInfo g_2samRomDesc[]={
	{ "g_2sam.bin", 0x100000, 0x78E92143, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2sam);
STD_ROM_FN(g_2sam);

struct BurnDriver BurnDrvMDg_2sam = {
	"g_2sam", NULL, NULL, "1900",
	"Second Samurai, The (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2samRomInfo, g_2samRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fun Car Rally (Unl)

static struct BurnRomInfo fcrRomDesc[]={
	{ "g_fcr.bin", 0x100000, 0x42E27845, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fcr);
STD_ROM_FN(fcr);

struct BurnDriverD BurnDrvMDfcr = {
	"g_fcr", NULL, NULL, "1900",
	"Fun Car Rally (Unl)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fcrRomInfo, fcrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Predator 2 (UE) [!]

static struct BurnRomInfo pre2RomDesc[]={
	{ "g_pre2.bin", 0x100000, 0xBDBA113E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pre2);
STD_ROM_FN(pre2);

struct BurnDriverD BurnDrvMDpre2 = {
	"g_pre2", NULL, NULL, "1900",
	"Predator 2 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pre2RomInfo, pre2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II (UE) (REV02) [!]

static struct BurnRomInfo pst2RomDesc[]={
	{ "g_pst2.bin", 0x0C0000, 0x904FA047, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pst2);
STD_ROM_FN(pst2);

struct BurnDriverD BurnDrvMDpst2 = {
	"g_pst2", NULL, NULL, "1989",
	"Phantasy Star II (UE) (REV02) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pst2RomInfo, pst2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star - The End of the Millenium (U) [!]

static struct BurnRomInfo pst4RomDesc[]={
	{ "g_pst4.bin", 0x300000, 0xFE236442, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pst4);
STD_ROM_FN(pst4);

struct BurnDriverD BurnDrvMDpst4 = {
	"g_pst4", NULL, NULL, "1994",
	"Phantasy Star - The End of the Millenium (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pst4RomInfo, pst4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf III (UE) [!]

static struct BurnRomInfo pga3RomDesc[]={
	{ "g_pga3.bin", 0x200000, 0xAEB3F65F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pga3);
STD_ROM_FN(pga3);

struct BurnDriverD BurnDrvMDpga3 = {
	"g_pga3", NULL, NULL, "1900",
	"PGA Tour Golf III (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pga3RomInfo, pga3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf II (UE) (REV01) [!]

static struct BurnRomInfo pga2RomDesc[]={
	{ "g_pga2.bin", 0x100000, 0xE82B8606, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pga2);
STD_ROM_FN(pga2);

struct BurnDriverD BurnDrvMDpga2 = {
	"g_pga2", NULL, NULL, "1900",
	"PGA Tour Golf II (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pga2RomInfo, pga2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf (UE) (REV02) [!]

static struct BurnRomInfo pgaRomDesc[]={
	{ "g_pga.bin", 0x080000, 0xC1F0B4E1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pga);
STD_ROM_FN(pga);

struct BurnDriverD BurnDrvMDpga = {
	"g_pga", NULL, NULL, "1900",
	"PGA Tour Golf (UE) (REV02) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pgaRomInfo, pgaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour 96 (UE) [!]

static struct BurnRomInfo pg96RomDesc[]={
	{ "g_pg96.bin", 0x200000, 0x9698BBDE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pg96);
STD_ROM_FN(pg96);

struct BurnDriverD BurnDrvMDpg96 = {
	"g_pg96", NULL, NULL, "1900",
	"PGA Tour 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pg96RomInfo, pg96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Premier Manager 97 (E) [!]

static struct BurnRomInfo pm97RomDesc[]={
	{ "g_pm97.bin", 0x100000, 0xFCCBF69B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pm97);
STD_ROM_FN(pm97);

struct BurnDriverD BurnDrvMDpm97 = {
	"g_pm97", NULL, NULL, "1900",
	"Premier Manager 97 (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pm97RomInfo, pm97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Premier Manager (E) [!]

static struct BurnRomInfo pmanRomDesc[]={
	{ "g_pman.bin", 0x100000, 0x303B889F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pman);
STD_ROM_FN(pman);

struct BurnDriverD BurnDrvMDpman = {
	"g_pman", NULL, NULL, "1900",
	"Premier Manager (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pmanRomInfo, pmanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Primal Rage (UE) [!]

static struct BurnRomInfo primRomDesc[]={
	{ "g_prim.bin", 0x300000, 0x2884C6D1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(prim);
STD_ROM_FN(prim);

struct BurnDriverD BurnDrvMDprim = {
	"g_prim", NULL, NULL, "1900",
	"Primal Rage (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, primRomInfo, primRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Powerball (U) [c][!]

static struct BurnRomInfo pwblRomDesc[]={
	{ "g_pwbl.bin", 0x080000, 0x7ADF232F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pwbl);
STD_ROM_FN(pwbl);

struct BurnDriverD BurnDrvMDpwbl = {
	"g_pwbl", NULL, NULL, "1900",
	"Powerball (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pwblRomInfo, pwblRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Punishe

static struct BurnRomInfo puniRomDesc[]={
	{ "g_puni.bin", 0x200000, 0x695CD8B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puni);
STD_ROM_FN(puni);

struct BurnDriverD BurnDrvMDpuni = {
	"g_puni", NULL, NULL, "1900",
	"Punishe\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puniRomInfo, puniRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rambo III (W) (REV01) [!]

static struct BurnRomInfo ram3RomDesc[]={
	{ "g_ram3.bin", 0x040000, 0x4D47A647, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ram3);
STD_ROM_FN(ram3);

struct BurnDriverD BurnDrvMDram3 = {
	"g_ram3", NULL, NULL, "1900",
	"Rambo III (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ram3RomInfo, ram3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Revolution X (UE) [!]

static struct BurnRomInfo revxRomDesc[]={
	{ "g_revx.bin", 0x400000, 0x5FB0C5D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(revx);
STD_ROM_FN(revx);

struct BurnDriverD BurnDrvMDrevx = {
	"g_revx", NULL, NULL, "1900",
	"Revolution X (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, revxRomInfo, revxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Blasters (U) [!]

static struct BurnRomInfo rblsRomDesc[]={
	{ "g_rbls.bin", 0x080000, 0xEC6CD5F0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rbls);
STD_ROM_FN(rbls);

struct BurnDriverD BurnDrvMDrbls = {
	"g_rbls", NULL, NULL, "1900",
	"Road Blasters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rblsRomInfo, rblsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rock n' Roll Racing (U) [!]

static struct BurnRomInfo rrrRomDesc[]={
	{ "g_rrr.bin", 0x100000, 0x6ABAB577, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrr);
STD_ROM_FN(rrr);

struct BurnDriverD BurnDrvMDrrr = {
	"g_rrr", NULL, NULL, "1900",
	"Rock n' Roll Racing (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrrRomInfo, rrrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rolling Thunder 2 (U) [c][!]

static struct BurnRomInfo rth2RomDesc[]={
	{ "g_rth2.bin", 0x100000, 0x3ACE429B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rth2);
STD_ROM_FN(rth2);

struct BurnDriverD BurnDrvMDrth2 = {
	"g_rth2", NULL, NULL, "1900",
	"Rolling Thunder 2 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rth2RomInfo, rth2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rolling Thunder 3 (U) [c][!]

static struct BurnRomInfo rth3RomDesc[]={
	{ "g_rth3.bin", 0x180000, 0x64FB13AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rth3);
STD_ROM_FN(rth3);

struct BurnDriverD BurnDrvMDrth3 = {
	"g_rth3", NULL, NULL, "1900",
	"Rolling Thunder 3 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rth3RomInfo, rth3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Saturday Night Slam Masters (U) [!]

static struct BurnRomInfo snsmRomDesc[]={
	{ "g_snsm.bin", 0x400000, 0x2FB4EABA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(snsm);
STD_ROM_FN(snsm);

struct BurnDriverD BurnDrvMDsnsm = {
	"g_snsm", NULL, NULL, "1900",
	"Saturday Night Slam Masters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, snsmRomInfo, snsmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadow Dancer - The Secret of Shinobi (W) [c][!]

static struct BurnRomInfo sdanRomDesc[]={
	{ "g_sdan.bin", 0x080000, 0xEBE9AD10, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sdan);
STD_ROM_FN(sdan);

struct BurnDriverD BurnDrvMDsdan = {
	"g_sdan", NULL, NULL, "1900",
	"Shadow Dancer - The Secret of Shinobi (W) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sdanRomInfo, sdanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shanghai 2 - Dragon's Eye (U) [!]

static struct BurnRomInfo s2deRomDesc[]={
	{ "g_s2de.bin", 0x100000, 0xEBE9E840, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s2de);
STD_ROM_FN(s2de);

struct BurnDriverD BurnDrvMDs2de = {
	"g_s2de", NULL, NULL, "1900",
	"Shanghai 2 - Dragon's Eye (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s2deRomInfo, s2deRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force (U) [!]

static struct BurnRomInfo shf1RomDesc[]={
	{ "g_shf1.bin", 0x180000, 0xE0594ABE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shf1);
STD_ROM_FN(shf1);

struct BurnDriverD BurnDrvMDshf1 = {
	"g_shf1", NULL, NULL, "1993",
	"Shining Force (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shf1RomInfo, shf1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force II (U) [!]

static struct BurnRomInfo shf2RomDesc[]={
	{ "g_shf2.bin", 0x200000, 0x4815E075, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shf2);
STD_ROM_FN(shf2);

struct BurnDriverD BurnDrvMDshf2 = {
	"g_shf2", NULL, NULL, "1994",
	"Shining Force II (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shf2RomInfo, shf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soleil (E) [!]

static struct BurnRomInfo soleRomDesc[]={
	{ "g_sole.bin", 0x200000, 0xA30EBDB1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sole);
STD_ROM_FN(sole);

struct BurnDriverD BurnDrvMDsole = {
	"g_sole", NULL, NULL, "1994",
	"Soleil (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soleRomInfo, soleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Spinball (U) (alt music) [!]

static struct BurnRomInfo sspaRomDesc[]={
	{ "g_sspa.bin", 0x100000, 0xE9960371, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sspa);
STD_ROM_FN(sspa);

struct BurnDriverD BurnDrvMDsspa = {
	"g_sspa", "g_sons", NULL, "1993",
	"Sonic Spinball (U) (alt music) [!]\0", "No sound in-game", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sspaRomInfo, sspaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Fighter II' - Special Champion Edition (U) [!]

static struct BurnRomInfo sf2cRomDesc[]={
	{ "g_sf2c.bin", 0x300000, 0x13FE08A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sf2c);
STD_ROM_FN(sf2c);

struct BurnDriverD BurnDrvMDsf2c = {
	"g_sf2c", NULL, NULL, "1900",
	"Street Fighter II' - Special Champion Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sf2cRomInfo, sf2cRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Battle Tank - War in the Gulf (U) [!]

static struct BurnRomInfo sbtRomDesc[]={
	{ "g_sbt.bin", 0x080000, 0xB0B5E3C9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbt);
STD_ROM_FN(sbt);

struct BurnDriverD BurnDrvMDsbt = {
	"g_sbt", NULL, NULL, "1900",
	"Super Battle Tank - War in the Gulf (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sbtRomInfo, sbtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Baseball 2020 (UE) [!]

static struct BurnRomInfo g_2020RomDesc[]={
	{ "g_2020.bin", 0x200000, 0xC17ACEE5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2020);
STD_ROM_FN(g_2020);

struct BurnDriverD BurnDrvMDg_2020 = {
	"g_2020", NULL, NULL, "1900",
	"Super Baseball 2020 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2020RomInfo, g_2020RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-22 Interceptor (U) (Jun 1992) [c][!]

static struct BurnRomInfo f22iRomDesc[]={
	{ "g_f22i.bin", 0x0C0000, 0xDD19B2B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f22i);
STD_ROM_FN(f22i);

struct BurnDriverD BurnDrvMDf22i = {
	"g_f22i", NULL, NULL, "1991",
	"F-22 Interceptor (U) (Jun 1992) [c][!]\0", NULL, "Electronic Arts / Edward Lemer", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f22iRomInfo, f22iRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Faery Tale Adventur

static struct BurnRomInfo faerRomDesc[]={
	{ "g_faer.bin", 0x080000, 0x963F4969, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(faer);
STD_ROM_FN(faer);

struct BurnDriverD BurnDrvMDfaer = {
	"g_faer", NULL, NULL, "1900",
	"Faery Tale Adventur\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, faerRomInfo, faerRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gain Ground (UE) [c][!]

static struct BurnRomInfo gainRomDesc[]={
	{ "g_gain.bin", 0x080000, 0x83E7B8AE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gain);
STD_ROM_FN(gain);

struct BurnDriverD BurnDrvMDgain = {
	"g_gain", NULL, NULL, "1900",
	"Gain Ground (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gainRomInfo, gainRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zero Tolerance (UE) [!]

static struct BurnRomInfo g_0tolRomDesc[]={
	{ "g_0tol.bin", 0x200000, 0x23F603F5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_0tol);
STD_ROM_FN(g_0tol);

struct BurnDriverD BurnDrvMDg_0tol = {
	"g_0tol", NULL, NULL, "1900",
	"Zero Tolerance (UE) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_0tolRomInfo, g_0tolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zero Wing (E) [c][!]

static struct BurnRomInfo zwinRomDesc[]={
	{ "g_zwin.bin", 0x100000, 0x89B744A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zwin);
STD_ROM_FN(zwin);

struct BurnDriverD BurnDrvMDzwin = {
	"g_zwin", NULL, NULL, "1900",
	"Zero Wing (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zwinRomInfo, zwinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Young Indiana Jones - Instrument of Chaos (U) [!]

static struct BurnRomInfo yidyRomDesc[]={
	{ "g_yidy.bin", 0x100000, 0x4E384EF0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yidy);
STD_ROM_FN(yidy);

struct BurnDriverD BurnDrvMDyidy = {
	"g_yidy", NULL, NULL, "1900",
	"Young Indiana Jones - Instrument of Chaos (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yidyRomInfo, yidyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Heroes (U) [!]

static struct BurnRomInfo wherRomDesc[]={
	{ "g_wher.bin", 0x200000, 0x0F4D22EC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wher);
STD_ROM_FN(wher);

struct BurnDriverD BurnDrvMDwher = {
	"g_wher", NULL, NULL, "1900",
	"World Heroes (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wherRomInfo, wherRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Whip Rush 2222 AD (U) [!]

static struct BurnRomInfo whipRomDesc[]={
	{ "g_whip.bin", 0x080000, 0x7EB6B86B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(whip);
STD_ROM_FN(whip);

struct BurnDriverD BurnDrvMDwhip = {
	"g_whip", NULL, NULL, "1900",
	"Whip Rush 2222 AD (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, whipRomInfo, whipRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wardner (U) [!]

static struct BurnRomInfo wardRomDesc[]={
	{ "g_ward.bin", 0x080000, 0x1E369AE2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ward);
STD_ROM_FN(ward);

struct BurnDriverD BurnDrvMDward = {
	"g_ward", NULL, NULL, "1900",
	"Wardner (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wardRomInfo, wardRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtual Bart (W) [!]

static struct BurnRomInfo vbarRomDesc[]={
	{ "g_vbar.bin", 0x200000, 0x8DB9F378, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vbar);
STD_ROM_FN(vbar);

struct BurnDriverD BurnDrvMDvbar = {
	"g_vbar", NULL, NULL, "1900",
	"Virtual Bart (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vbarRomInfo, vbarRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Two Crude Dudes (U) [!]

static struct BurnRomInfo g_2cdRomDesc[]={
	{ "g_2cd.bin", 0x100000, 0x721B5744, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2cd);
STD_ROM_FN(g_2cd);

struct BurnDriverD BurnDrvMDg_2cd = {
	"g_2cd", NULL, NULL, "1900",
	"Two Crude Dudes (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2cdRomInfo, g_2cdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Twin Hawk (JE) [!]

static struct BurnRomInfo twihRomDesc[]={
	{ "g_twih.bin", 0x080000, 0xA2EC8C67, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(twih);
STD_ROM_FN(twih);

struct BurnDriverD BurnDrvMDtwih = {
	"g_twih", NULL, NULL, "1900",
	"Twin Hawk (JE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, twihRomInfo, twihRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Twin Cobra (U) [!]

static struct BurnRomInfo twicRomDesc[]={
	{ "g_twic.bin", 0x0A0000, 0x2C708248, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(twic);
STD_ROM_FN(twic);

struct BurnDriverD BurnDrvMDtwic = {
	"g_twic", NULL, NULL, "1900",
	"Twin Cobra (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, twicRomInfo, twicRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Turrican (U) [c][!]

static struct BurnRomInfo turrRomDesc[]={
	{ "g_turr.bin", 0x080000, 0x634D67A6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(turr);
STD_ROM_FN(turr);

struct BurnDriverD BurnDrvMDturr = {
	"g_turr", NULL, NULL, "1900",
	"Turrican (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, turrRomInfo, turrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Truxton (W) [!]

static struct BurnRomInfo truxRomDesc[]={
	{ "g_trux.bin", 0x080000, 0x5BD0882D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(trux);
STD_ROM_FN(trux);

struct BurnDriverD BurnDrvMDtrux = {
	"g_trux", NULL, NULL, "1900",
	"Truxton (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, truxRomInfo, truxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Triple Play '96 (U) [c][!]

static struct BurnRomInfo tp96RomDesc[]={
	{ "g_tp96.bin", 0x400000, 0xF1748E91, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tp96);
STD_ROM_FN(tp96);

struct BurnDriverD BurnDrvMDtp96 = {
	"g_tp96", NULL, NULL, "1900",
	"Triple Play '96 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tp96RomInfo, tp96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Triple Play Gold (U) [c][!]

static struct BurnRomInfo tpgoRomDesc[]={
	{ "g_tpgo.bin", 0x400000, 0xBBE69017, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tpgo);
STD_ROM_FN(tpgo);

struct BurnDriverD BurnDrvMDtpgo = {
	"g_tpgo", NULL, NULL, "1900",
	"Triple Play Gold (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tpgoRomInfo, tpgoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Todd's Adventures in Slime World (U) [!]

static struct BurnRomInfo toddRomDesc[]={
	{ "g_todd.bin", 0x080000, 0x652E8B7D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(todd);
STD_ROM_FN(todd);

struct BurnDriverD BurnDrvMDtodd = {
	"g_todd", NULL, NULL, "1900",
	"Todd's Adventures in Slime World (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toddRomInfo, toddRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Time Killers (U) [!]

static struct BurnRomInfo tkilRomDesc[]={
	{ "g_tkil.bin", 0x200000, 0x4B5F52AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tkil);
STD_ROM_FN(tkil);

struct BurnDriverD BurnDrvMDtkil = {
	"g_tkil", NULL, NULL, "1900",
	"Time Killers (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tkilRomInfo, tkilRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Fox (U) [c][!]

static struct BurnRomInfo tfoxRomDesc[]={
	{ "g_tfox.bin", 0x100000, 0x5463F50F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tfox);
STD_ROM_FN(tfox);

struct BurnDriverD BurnDrvMDtfox = {
	"g_tfox", NULL, NULL, "1900",
	"Thunder Fox (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tfoxRomInfo, tfoxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tetris (J) [!]

static struct BurnRomInfo tetrRomDesc[]={
	{ "g_tetr.bin", 0x040000, 0x4CE90DB0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tetr);
STD_ROM_FN(tetr);

struct BurnDriverD BurnDrvMDtetr = {
	"g_tetr", NULL, NULL, "1900",
	"Tetris (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tetrRomInfo, tetrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Syndicate (UE) [!]

static struct BurnRomInfo syndRomDesc[]={
	{ "g_synd.bin", 0x200000, 0x95BBF87B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(synd);
STD_ROM_FN(synd);

struct BurnDriverD BurnDrvMDsynd = {
	"g_synd", NULL, NULL, "1900",
	"Syndicate (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, syndRomInfo, syndRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Power Instinct (J) [!]

static struct BurnRomInfo pinsRomDesc[]={
	{ "g_pins.bin", 0x300000, 0xABE9C415, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pins);
STD_ROM_FN(pins);

struct BurnDriverD BurnDrvMDpins = {
	"g_pins", NULL, NULL, "1900",
	"Power Instinct (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pinsRomInfo, pinsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pit Fighter (W) (Oct 1991) [!]

static struct BurnRomInfo pifgRomDesc[]={
	{ "g_pifg.bin", 0x100000, 0xD48A8B02, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pifg);
STD_ROM_FN(pifg);

struct BurnDriverD BurnDrvMDpifg = {
	"g_pifg", NULL, NULL, "1900",
	"Pit Fighter (W) (Oct 1991) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pifgRomInfo, pifgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pac-Man 2 - The New Adventures (U) [!]

static struct BurnRomInfo pac2RomDesc[]={
	{ "g_pac2.bin", 0x200000, 0xFE7A7ED1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pac2);
STD_ROM_FN(pac2);

struct BurnDriverD BurnDrvMDpac2 = {
	"g_pac2", NULL, NULL, "1900",
	"Pac-Man 2 - The New Adventures (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pac2RomInfo, pac2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ninja Burai Densetsu (J) [!]

static struct BurnRomInfo nbdRomDesc[]={
	{ "g_nbd.bin", 0x100000, 0xA8D828A0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbd);
STD_ROM_FN(nbd);

struct BurnDriverD BurnDrvMDnbd = {
	"g_nbd", NULL, NULL, "1900",
	"Ninja Burai Densetsu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbdRomInfo, nbdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kick Off 3 - European Challenge (E) [!]

static struct BurnRomInfo ko3RomDesc[]={
	{ "g_ko3.bin", 0x100000, 0xBC37401A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ko3);
STD_ROM_FN(ko3);

struct BurnDriverD BurnDrvMDko3 = {
	"g_ko3", NULL, NULL, "1900",
	"Kick Off 3 - European Challenge (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ko3RomInfo, ko3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ka-Ge-Ki - Fists of Steel (U) [!]

static struct BurnRomInfo kgkRomDesc[]={
	{ "g_kgk.bin", 0x100000, 0xEFFC0FA6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kgk);
STD_ROM_FN(kgk);

struct BurnDriverD BurnDrvMDkgk = {
	"g_kgk", NULL, NULL, "1900",
	"Ka-Ge-Ki - Fists of Steel (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kgkRomInfo, kgkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King Salmon - The Big Catch (U) [c][!]

static struct BurnRomInfo ksalRomDesc[]={
	{ "g_ksal.bin", 0x080000, 0xF516E7D9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ksal);
STD_ROM_FN(ksal);

struct BurnDriverD BurnDrvMDksal = {
	"g_ksal", NULL, NULL, "1900",
	"King Salmon - The Big Catch (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ksalRomInfo, ksalRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lakers vs Celtics and the NBA Playoffs (UE) [!]

static struct BurnRomInfo lvscRomDesc[]={
	{ "g_lvsc.bin", 0x080000, 0x0E33FC75, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lvsc);
STD_ROM_FN(lvsc);

struct BurnDriverD BurnDrvMDlvsc = {
	"g_lvsc", NULL, NULL, "1990",
	"Lakers vs Celtics and the NBA Playoffs (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lvscRomInfo, lvscRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// We're Back! - A Dinosaur's Tale (U) [!]

static struct BurnRomInfo wbdtRomDesc[]={
	{ "g_wbdt.bin", 0x100000, 0x70155B5B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wbdt);
STD_ROM_FN(wbdt);

struct BurnDriverD BurnDrvMDwbdt = {
	"g_wbdt", NULL, NULL, "1900",
	"We're Back! - A Dinosaur's Tale (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wbdtRomInfo, wbdtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Combat Cars (UE) [!]

static struct BurnRomInfo comcRomDesc[]={
	{ "g_comc.bin", 0x100000, 0xE439B101, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comc);
STD_ROM_FN(comc);

struct BurnDriverD BurnDrvMDcomc = {
	"g_comc", NULL, NULL, "1900",
	"Combat Cars (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comcRomInfo, comcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// 688 Attack Sub (UE) [!]

static struct BurnRomInfo g_688aRomDesc[]={
	{ "g_688a.bin", 0x100000, 0xF2C58BF7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_688a);
STD_ROM_FN(g_688a);

struct BurnDriver BurnDrvMDg_688a = {
	"g_688a", NULL, NULL, "1900",
	"688 Attack Sub (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_688aRomInfo, g_688aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Air Diver (U) [!]

static struct BurnRomInfo adivRomDesc[]={
	{ "g_adiv.bin", 0x080000, 0x2041885E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(adiv);
STD_ROM_FN(adiv);

struct BurnDriver BurnDrvMDadiv = {
	"g_adiv", NULL, NULL, "1900",
	"Air Diver (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, adivRomInfo, adivRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alien Storm (W) [!]

static struct BurnRomInfo astoRomDesc[]={
	{ "g_asto.bin", 0x080000, 0xF5AC8DE5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(asto);
STD_ROM_FN(asto);

struct BurnDriverD BurnDrvMDasto = {
	"g_asto", NULL, NULL, "1900",
	"Alien Storm (W) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, astoRomInfo, astoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Altered Beast (UE) (REV02) [!]

static struct BurnRomInfo abeaRomDesc[]={
	{ "g_abea.bin", 0x080000, 0x154D59BB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abea);
STD_ROM_FN(abea);

struct BurnDriverD BurnDrvMDabea = {
	"g_abea", NULL, NULL, "1988",
	"Altered Beast (UE) (REV02) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abeaRomInfo, abeaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// American Gladiators (U) [!]

static struct BurnRomInfo aglaRomDesc[]={
	{ "g_agla.bin", 0x100000, 0x9952FA85, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(agla);
STD_ROM_FN(agla);

struct BurnDriverD BurnDrvMDagla = {
	"g_agla", NULL, NULL, "1900",
	"American Gladiators (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aglaRomInfo, aglaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arch Rivals (UE) [!]

static struct BurnRomInfo archRomDesc[]={
	{ "g_arch.bin", 0x080000, 0xE389D7E7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arch);
STD_ROM_FN(arch);

struct BurnDriver BurnDrvMDarch = {
	"g_arch", NULL, NULL, "1900",
	"Arch Rivals (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, archRomInfo, archRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arnold Palmer Tournament Golf (UE) [!]

static struct BurnRomInfo aptgRomDesc[]={
	{ "g_aptg.bin", 0x080000, 0x35B995EF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aptg);
STD_ROM_FN(aptg);

struct BurnDriverD BurnDrvMDaptg = {
	"g_aptg", NULL, NULL, "1900",
	"Arnold Palmer Tournament Golf (UE) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aptgRomInfo, aptgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Art of Fighting (U) [!]

static struct BurnRomInfo aofRomDesc[]={
	{ "g_aof.bin", 0x200000, 0xC9A57E07, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aof);
STD_ROM_FN(aof);

struct BurnDriver BurnDrvMDaof = {
	"g_aof", NULL, NULL, "1994",
	"Art of Fighting (U) [!]\0", NULL, "SNK / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aofRomInfo, aofRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Atomic Robo-Kid (U) [c][!]

static struct BurnRomInfo akidRomDesc[]={
	{ "g_akid.bin", 0x080000, 0x7CD8169E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(akid);
STD_ROM_FN(akid);

struct BurnDriver BurnDrvMDakid = {
	"g_akid", NULL, NULL, "1900",
	"Atomic Robo-Kid (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, akidRomInfo, akidRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ATP Tour Championship Tennis (U) [!]

static struct BurnRomInfo atptRomDesc[]={
	{ "g_atpt.bin", 0x200000, 0x8C822884, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(atpt);
STD_ROM_FN(atpt);

struct BurnDriver BurnDrvMDatpt = {
	"g_atpt", NULL, NULL, "1900",
	"ATP Tour Championship Tennis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, atptRomInfo, atptRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Australian Rugby League (E) [!]

static struct BurnRomInfo arugRomDesc[]={
	{ "g_arug.bin", 0x200000, 0xAC5BC26A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arug);
STD_ROM_FN(arug);

struct BurnDriver BurnDrvMDarug = {
	"g_arug", NULL, NULL, "1900",
	"Australian Rugby League (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arugRomInfo, arugRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ball Jacks (JE) [c][!]

static struct BurnRomInfo bjakRomDesc[]={
	{ "g_bjak.bin", 0x040000, 0xF5C3C54F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bjak);
STD_ROM_FN(bjak);

struct BurnDriver BurnDrvMDbjak = {
	"g_bjak", NULL, NULL, "1900",
	"Ball Jacks (JE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bjakRomInfo, bjakRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Barbie Super Model (U) [!]

static struct BurnRomInfo barbRomDesc[]={
	{ "g_barb.bin", 0x100000, 0x81C9662B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(barb);
STD_ROM_FN(barb);

struct BurnDriver BurnDrvMDbarb = {
	"g_barb", NULL, NULL, "1900",
	"Barbie Super Model (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, barbRomInfo, barbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bass Masters Classics (U) [!]

static struct BurnRomInfo bassRomDesc[]={
	{ "g_bass.bin", 0x200000, 0xCF1FF00A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bass);
STD_ROM_FN(bass);

struct BurnDriver BurnDrvMDbass = {
	"g_bass", NULL, NULL, "1900",
	"Bass Masters Classics (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bassRomInfo, bassRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bass Masters Classic Pro Edition (U) [!]

static struct BurnRomInfo baspRomDesc[]={
	{ "g_basp.bin", 0x200000, 0x9EDDEB3D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(basp);
STD_ROM_FN(basp);

struct BurnDriver BurnDrvMDbasp = {
	"g_basp", NULL, NULL, "1900",
	"Bass Masters Classic Pro Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, baspRomInfo, baspRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Barney's Hide & Seek Game (U) [!]

static struct BurnRomInfo barnRomDesc[]={
	{ "g_barn.bin", 0x100000, 0x1EFA9D53, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(barn);
STD_ROM_FN(barn);

struct BurnDriverD BurnDrvMDbarn = {
	"g_barn", NULL, NULL, "1900",
	"Barney's Hide & Seek Game (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, barnRomInfo, barnRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battle Mania - Dai Gin Jou (J) [c][!]

static struct BurnRomInfo btl2RomDesc[]={
	{ "g_btl2.bin", 0x100000, 0x312FA0F2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btl2);
STD_ROM_FN(btl2);

struct BurnDriver BurnDrvMDbtl2 = {
	"g_btl2", NULL, NULL, "1900",
	"Battle Mania - Dai Gin Jou (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btl2RomInfo, btl2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battle Mania (J) [!]

static struct BurnRomInfo btlmRomDesc[]={
	{ "g_btlm.bin", 0x080000, 0xA76C4A29, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btlm);
STD_ROM_FN(btlm);

struct BurnDriver BurnDrvMDbtlm = {
	"g_btlm", "g_tsht", NULL, "1900",
	"Battle Mania (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btlmRomInfo, btlmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battlemaster (U) [c][!]

static struct BurnRomInfo btmsRomDesc[]={
	{ "g_btms.bin", 0x080000, 0xFD2B35E3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btms);
STD_ROM_FN(btms);

struct BurnDriver BurnDrvMDbtms = {
	"g_btms", NULL, NULL, "1900",
	"Battlemaster (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btmsRomInfo, btmsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battletech (U) [!]

static struct BurnRomInfo btecRomDesc[]={
	{ "g_btec.bin", 0x200000, 0x409E5D14, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(btec);
STD_ROM_FN(btec);

struct BurnDriverD BurnDrvMDbtec = {
	"g_btec", NULL, NULL, "1900",
	"Battletech (U) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, btecRomInfo, btecRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beast Wrestler (U) [!]

static struct BurnRomInfo bwreRomDesc[]={
	{ "g_bwre.bin", 0x100000, 0x0CA5BB64, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bwre);
STD_ROM_FN(bwre);

struct BurnDriverD BurnDrvMDbwre = {
	"g_bwre", NULL, NULL, "1900",
	"Beast Wrestler (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bwreRomInfo, bwreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Berenstain Bears', The - Camping Adventure (U) [!]

static struct BurnRomInfo bearRomDesc[]={
	{ "g_bear.bin", 0x100000, 0x1F86237B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bear);
STD_ROM_FN(bear);

struct BurnDriver BurnDrvMDbear = {
	"g_bear", NULL, NULL, "1900",
	"Berenstain Bears', The - Camping Adventure (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bearRomInfo, bearRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bill Walsh College Football '95 (U) [!]

static struct BurnRomInfo bw95RomDesc[]={
	{ "g_bw95.bin", 0x200000, 0xA582F45A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bw95);
STD_ROM_FN(bw95);

struct BurnDriver BurnDrvMDbw95 = {
	"g_bw95", NULL, NULL, "1900",
	"Bill Walsh College Football '95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bw95RomInfo, bw95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bill Walsh College Football (UE) [c][!]

static struct BurnRomInfo bwcfRomDesc[]={
	{ "g_bwcf.bin", 0x100000, 0x3ED83362, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bwcf);
STD_ROM_FN(bwcf);

struct BurnDriver BurnDrvMDbwcf = {
	"g_bwcf", NULL, NULL, "1900",
	"Bill Walsh College Football (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bwcfRomInfo, bwcfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bimini Run (U) (REV02) [!]

static struct BurnRomInfo bimiRomDesc[]={
	{ "g_bimi.bin", 0x080000, 0xD4DC5188, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bimi);
STD_ROM_FN(bimi);

struct BurnDriver BurnDrvMDbimi = {
	"g_bimi", NULL, NULL, "1900",
	"Bimini Run (U) (REV02) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bimiRomInfo, bimiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bonanza Bros. (U) [!]

static struct BurnRomInfo bnzaRomDesc[]={
	{ "g_bnza.bin", 0x080000, 0x20D1AD4C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bnza);
STD_ROM_FN(bnza);

struct BurnDriverD BurnDrvMDbnza = {
	"g_bnza", NULL, NULL, "1900",
	"Bonanza Bros. (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bnzaRomInfo, bnzaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Boogie Woogie Bowling (J) [!]

static struct BurnRomInfo bwbwRomDesc[]={
	{ "g_bwbw.bin", 0x080000, 0xCCF52828, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bwbw);
STD_ROM_FN(bwbw);

struct BurnDriverD BurnDrvMDbwbw = {
	"g_bwbw", "g_cbwl", NULL, "1900",
	"Boogie Woogie Bowling (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bwbwRomInfo, bwbwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Boxing Legends of the Ring (U) [!]

static struct BurnRomInfo boxlRomDesc[]={
	{ "g_boxl.bin", 0x100000, 0x00F225AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(boxl);
STD_ROM_FN(boxl);

struct BurnDriverD BurnDrvMDboxl = {
	"g_boxl", NULL, NULL, "1900",
	"Boxing Legends of the Ring (U) [!]\0", "Bad Sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, boxlRomInfo, boxlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brett Hull Hockey '95 (U) [!]

static struct BurnRomInfo bh95RomDesc[]={
	{ "g_bh95.bin", 0x200000, 0xF7775A09, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bh95);
STD_ROM_FN(bh95);

struct BurnDriverD BurnDrvMDbh95 = {
	"g_bh95", NULL, NULL, "1900",
	"Brett Hull Hockey '95 (U) [!]\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bh95RomInfo, bh95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brian Lara Cricket (E) [c][!]

static struct BurnRomInfo blcrRomDesc[]={
	{ "g_blcr.bin", 0x100000, 0x408CF5C3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blcr);
STD_ROM_FN(blcr);

struct BurnDriverD BurnDrvMDblcr = {
	"g_blcr", NULL, NULL, "1900",
	"Brian Lara Cricket (E) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blcrRomInfo, blcrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bulls vs Blazers and the NBA Playoffs (UE) [!]

static struct BurnRomInfo bvsbRomDesc[]={
	{ "g_bvsb.bin", 0x100000, 0xD4E4B4E8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bvsb);
STD_ROM_FN(bvsb);

struct BurnDriver BurnDrvMDbvsb = {
	"g_bvsb", NULL, NULL, "1993",
	"Bulls vs Blazers and the NBA Playoffs (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bvsbRomInfo, bvsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bulls vs Lakers and the NBA Playoffs (UE) [!]

static struct BurnRomInfo bvslRomDesc[]={
	{ "g_bvsl.bin", 0x100000, 0xE56023A0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bvsl);
STD_ROM_FN(bvsl);

struct BurnDriver BurnDrvMDbvsl = {
	"g_bvsl", NULL, NULL, "1991",
	"Bulls vs Lakers and the NBA Playoffs (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bvslRomInfo, bvslRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Burning Force (U) [!]

static struct BurnRomInfo burfRomDesc[]={
	{ "g_burf.bin", 0x080000, 0xBDC8F02C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(burf);
STD_ROM_FN(burf);

struct BurnDriverD BurnDrvMDburf = {
	"g_burf", NULL, NULL, "1900",
	"Burning Force (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, burfRomInfo, burfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cadash (JU) [c][!]

static struct BurnRomInfo cadaRomDesc[]={
	{ "g_cada.bin", 0x080000, 0x13BDF374, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cada);
STD_ROM_FN(cada);

struct BurnDriverD BurnDrvMDcada = {
	"g_cada", NULL, NULL, "1900",
	"Cadash (JU) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cadaRomInfo, cadaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Caesars Palace (U) [!]

static struct BurnRomInfo caesRomDesc[]={
	{ "g_caes.bin", 0x080000, 0x8FDAA9BB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(caes);
STD_ROM_FN(caes);

struct BurnDriverD BurnDrvMDcaes = {
	"g_caes", NULL, NULL, "1900",
	"Caesars Palace (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, caesRomInfo, caesRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cal Ripken Jr. Baseball (U) [c][!]

static struct BurnRomInfo crjbRomDesc[]={
	{ "g_crjb.bin", 0x100000, 0x9B1C96C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crjb);
STD_ROM_FN(crjb);

struct BurnDriverD BurnDrvMDcrjb = {
	"g_crjb", NULL, NULL, "1900",
	"Cal Ripken Jr. Baseball (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crjbRomInfo, crjbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Caliber Fifty (U) [!]

static struct BurnRomInfo c50RomDesc[]={
	{ "g_c50.bin", 0x100000, 0x44F4FA05, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(c50);
STD_ROM_FN(c50);

struct BurnDriverD BurnDrvMDc50 = {
	"g_c50", NULL, NULL, "1900",
	"Caliber Fifty (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, c50RomInfo, c50RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// California Games (UE) [!]

static struct BurnRomInfo cgamRomDesc[]={
	{ "g_cgam.bin", 0x080000, 0x43B1B672, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cgam);
STD_ROM_FN(cgam);

struct BurnDriver BurnDrvMDcgam = {
	"g_cgam", NULL, NULL, "1900",
	"California Games (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cgamRomInfo, cgamRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Captain America and the Avengers (U) [!]

static struct BurnRomInfo capaRomDesc[]={
	{ "g_capa.bin", 0x100000, 0xE0639CA2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(capa);
STD_ROM_FN(capa);

struct BurnDriverD BurnDrvMDcapa = {
	"g_capa", NULL, NULL, "1900",
	"Captain America and the Avengers (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, capaRomInfo, capaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Captain Planet and the Planeteers (E) [!]

static struct BurnRomInfo cappRomDesc[]={
	{ "g_capp.bin", 0x080000, 0x7672EFA5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(capp);
STD_ROM_FN(capp);

struct BurnDriverD BurnDrvMDcapp = {
	"g_capp", NULL, NULL, "1900",
	"Captain Planet and the Planeteers (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cappRomInfo, cappRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chiki Chiki Boys (UE) [!]

static struct BurnRomInfo chikRomDesc[]={
	{ "g_chik.bin", 0x100000, 0x813A7D62, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chik);
STD_ROM_FN(chik);

struct BurnDriverD BurnDrvMDchik = {
	"g_chik", NULL, NULL, "1900",
	"Chiki Chiki Boys (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chikRomInfo, chikRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Clue (U) [!]

static struct BurnRomInfo clueRomDesc[]={
	{ "g_clue.bin", 0x080000, 0x7753A296, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clue);
STD_ROM_FN(clue);

struct BurnDriverD BurnDrvMDclue = {
	"g_clue", NULL, NULL, "1900",
	"Clue (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clueRomInfo, clueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Corporation (E) [c][!]

static struct BurnRomInfo corpRomDesc[]={
	{ "g_corp.bin", 0x100000, 0xA80D18AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(corp);
STD_ROM_FN(corp);

struct BurnDriverD BurnDrvMDcorp = {
	"g_corp", NULL, NULL, "1994",
	"Corporation (E) [c][!]\0", NULL, "Core / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, corpRomInfo, corpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cuty Suzuki no Ringside Angel (J) [!]

static struct BurnRomInfo cutyRomDesc[]={
	{ "g_cuty.bin", 0x080000, 0x13795DCA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cuty);
STD_ROM_FN(cuty);

struct BurnDriverD BurnDrvMDcuty = {
	"g_cuty", NULL, NULL, "1900",
	"Cuty Suzuki no Ringside Angel (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cutyRomInfo, cutyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// D&D - Warriors of the Eternal Sun (UE) [!]

static struct BurnRomInfo ddweRomDesc[]={
	{ "g_ddwe.bin", 0x100000, 0xAF4A9CD7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddwe);
STD_ROM_FN(ddwe);

struct BurnDriverD BurnDrvMDddwe = {
	"g_ddwe", NULL, NULL, "1900",
	"D&D - Warriors of the Eternal Sun (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddweRomInfo, ddweRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dino Land (U) [!]

static struct BurnRomInfo dlndRomDesc[]={
	{ "g_dlnd.bin", 0x080000, 0x5FE351B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dlnd);
STD_ROM_FN(dlnd);

struct BurnDriverD BurnDrvMDdlnd = {
	"g_dlnd", NULL, NULL, "1900",
	"Dino Land (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dlndRomInfo, dlndRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dynamite Duke (W) [!]

static struct BurnRomInfo ddukRomDesc[]={
	{ "g_dduk.bin", 0x080000, 0x39D01C8C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dduk);
STD_ROM_FN(dduk);

struct BurnDriverD BurnDrvMDdduk = {
	"g_dduk", NULL, NULL, "1900",
	"Dynamite Duke (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddukRomInfo, ddukRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO Jr. (U) (REV00) [!]

static struct BurnRomInfo ecjrRomDesc[]={
	{ "g_ecjr.bin", 0x100000, 0x6C6F4B89, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecjr);
STD_ROM_FN(ecjr);

struct BurnDriverD BurnDrvMDecjr = {
	"g_ecjr", NULL, NULL, "1995",
	"ECCO Jr. (U) (REV00) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecjrRomInfo, ecjrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESPN Baseball Tonight (U) [!]

static struct BurnRomInfo e_btRomDesc[]={
	{ "g_e_bt.bin", 0x200000, 0x96D8440C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(e_bt);
STD_ROM_FN(e_bt);

struct BurnDriverD BurnDrvMDe_bt = {
	"g_e_bt", NULL, NULL, "1900",
	"ESPN Baseball Tonight (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, e_btRomInfo, e_btRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESPN National Hockey Night (U) [c][!]

static struct BurnRomInfo e_hnRomDesc[]={
	{ "g_e_hn.bin", 0x200000, 0x1D08828C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(e_hn);
STD_ROM_FN(e_hn);

struct BurnDriverD BurnDrvMDe_hn = {
	"g_e_hn", NULL, NULL, "1900",
	"ESPN National Hockey Night (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, e_hnRomInfo, e_hnRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESPN Sunday Night NFL (U) [!]

static struct BurnRomInfo e_snRomDesc[]={
	{ "g_e_sn.bin", 0x200000, 0x61E9C309, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(e_sn);
STD_ROM_FN(e_sn);

struct BurnDriverD BurnDrvMDe_sn = {
	"g_e_sn", NULL, NULL, "1900",
	"ESPN Sunday Night NFL (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, e_snRomInfo, e_snRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Evander Holyfield's Real Deal Boxing (JU) [!]

static struct BurnRomInfo ehrdRomDesc[]={
	{ "g_ehrd.bin", 0x080000, 0x4FEF37C8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ehrd);
STD_ROM_FN(ehrd);

struct BurnDriverD BurnDrvMDehrd = {
	"g_ehrd", NULL, NULL, "1900",
	"Evander Holyfield's Real Deal Boxing (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ehrdRomInfo, ehrdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-15 Strike Eagle II (U) [!]

static struct BurnRomInfo f15sRomDesc[]={
	{ "g_f15s.bin", 0x100000, 0x412C4D60, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f15s);
STD_ROM_FN(f15s);

struct BurnDriverD BurnDrvMDf15s = {
	"g_f15s", NULL, NULL, "1900",
	"F-15 Strike Eagle II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f15sRomInfo, f15sRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Family Feud (U) [!]

static struct BurnRomInfo feudRomDesc[]={
	{ "g_feud.bin", 0x080000, 0x1AA628B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(feud);
STD_ROM_FN(feud);

struct BurnDriverD BurnDrvMDfeud = {
	"g_feud", NULL, NULL, "1900",
	"Family Feud (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, feudRomInfo, feudRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatal Labyrinth (JU) [!]

static struct BurnRomInfo fatlRomDesc[]={
	{ "g_fatl.bin", 0x020000, 0x5F0BD984, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fatl);
STD_ROM_FN(fatl);

struct BurnDriverD BurnDrvMDfatl = {
	"g_fatl", NULL, NULL, "1900",
	"Fatal Labyrinth (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fatlRomInfo, fatlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ferrari Grand Prix Challenge (U) [!]

static struct BurnRomInfo frgpRomDesc[]={
	{ "g_frgp.bin", 0x100000, 0xF73F6BEC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(frgp);
STD_ROM_FN(frgp);

struct BurnDriverD BurnDrvMDfrgp = {
	"g_frgp", NULL, NULL, "1900",
	"Ferrari Grand Prix Challenge (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, frgpRomInfo, frgpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA International Soccer (UE) (M4) [!]

static struct BurnRomInfo fifaRomDesc[]={
	{ "g_fifa.bin", 0x200000, 0xBDDBB763, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fifa);
STD_ROM_FN(fifa);

struct BurnDriver BurnDrvMDfifa = {
	"g_fifa", NULL, NULL, "1993",
	"FIFA International Soccer (UE) (M4) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fifaRomInfo, fifaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA Soccer 95 (UE) [!]

static struct BurnRomInfo fi95RomDesc[]={
	{ "g_fi95.bin", 0x200000, 0xB389D036, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fi95);
STD_ROM_FN(fi95);

struct BurnDriver BurnDrvMDfi95 = {
	"g_fi95", NULL, NULL, "1900",
	"FIFA Soccer 95 (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fi95RomInfo, fi95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA Soccer 96 (UE) (M6) [!]

static struct BurnRomInfo fi96RomDesc[]={
	{ "g_fi96.bin", 0x200000, 0xBAD30FFA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fi96);
STD_ROM_FN(fi96);

struct BurnDriver BurnDrvMDfi96 = {
	"g_fi96", NULL, NULL, "1900",
	"FIFA Soccer 96 (UE) (M6) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fi96RomInfo, fi96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA Soccer 97 Gold Edition (UE) (M6) [!]

static struct BurnRomInfo fi97RomDesc[]={
	{ "g_fi97.bin", 0x200000, 0xA33D5803, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fi97);
STD_ROM_FN(fi97);

struct BurnDriverD BurnDrvMDfi97 = {
	"g_fi97", NULL, NULL, "1996",
	"FIFA Soccer 97 Gold Edition (UE) (M6) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fi97RomInfo, fi97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// George Foreman's KO Boxing (U) [!]

static struct BurnRomInfo gfkoRomDesc[]={
	{ "g_gfko.bin", 0x100000, 0xE1FDC787, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gfko);
STD_ROM_FN(gfko);

struct BurnDriverD BurnDrvMDgfko = {
	"g_gfko", NULL, NULL, "1900",
	"George Foreman's KO Boxing (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gfkoRomInfo, gfkoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Grand Slam Tennis (E) [!]

static struct BurnRomInfo gsteRomDesc[]={
	{ "g_gste.bin", 0x080000, 0x8C2670DE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gste);
STD_ROM_FN(gste);

struct BurnDriverD BurnDrvMDgste = {
	"g_gste", NULL, NULL, "1900",
	"Grand Slam Tennis (E) [!]\0", NULL, "Sega / System Sacom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gsteRomInfo, gsteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Growl (U) [!]

static struct BurnRomInfo grwlRomDesc[]={
	{ "g_grwl.bin", 0x080000, 0xF60EF143, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(grwl);
STD_ROM_FN(grwl);

struct BurnDriverD BurnDrvMDgrwl = {
	"g_grwl", NULL, NULL, "1900",
	"Growl (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, grwlRomInfo, grwlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Heavy Nova (U) [!]

static struct BurnRomInfo hnovRomDesc[]={
	{ "g_hnov.bin", 0x100000, 0xF6B6A9D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hnov);
STD_ROM_FN(hnov);

struct BurnDriverD BurnDrvMDhnov = {
	"g_hnov", NULL, NULL, "1900",
	"Heavy Nova (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hnovRomInfo, hnovRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hit The Ice (U) [c][!]

static struct BurnRomInfo hiceRomDesc[]={
	{ "g_hice.bin", 0x080000, 0x85B23606, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hice);
STD_ROM_FN(hice);

struct BurnDriverD BurnDrvMDhice = {
	"g_hice", NULL, NULL, "1900",
	"Hit The Ice (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hiceRomInfo, hiceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jack Nicklaus' Power Challenge Golf (UE) [!]

static struct BurnRomInfo jnpgRomDesc[]={
	{ "g_jnpg.bin", 0x100000, 0x5545E909, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jnpg);
STD_ROM_FN(jnpg);

struct BurnDriverD BurnDrvMDjnpg = {
	"g_jnpg", NULL, NULL, "1900",
	"Jack Nicklaus' Power Challenge Golf (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jnpgRomInfo, jnpgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King of the Monsters 2 (U) [!]

static struct BurnRomInfo ktm2RomDesc[]={
	{ "g_ktm2.bin", 0x200000, 0xEE1638AC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ktm2);
STD_ROM_FN(ktm2);

struct BurnDriverD BurnDrvMDktm2 = {
	"g_ktm2", NULL, NULL, "1900",
	"King of the Monsters 2 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ktm2RomInfo, ktm2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King of the Monsters (U) [!]

static struct BurnRomInfo ktmRomDesc[]={
	{ "g_ktm.bin", 0x100000, 0xF390D406, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ktm);
STD_ROM_FN(ktm);

struct BurnDriverD BurnDrvMDktm = {
	"g_ktm", NULL, NULL, "1900",
	"King of the Monsters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ktmRomInfo, ktmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Klax (UE) [!]

static struct BurnRomInfo klaxRomDesc[]={
	{ "g_klax.bin", 0x040000, 0x248CD09E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(klax);
STD_ROM_FN(klax);

struct BurnDriverD BurnDrvMDklax = {
	"g_klax", NULL, NULL, "1900",
	"Klax (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, klaxRomInfo, klaxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lethal Enforcers (U) [!]

static struct BurnRomInfo lenRomDesc[]={
	{ "g_len.bin", 0x200000, 0x51D9A84A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(len);
STD_ROM_FN(len);

struct BurnDriverD BurnDrvMDlen = {
	"g_len", NULL, NULL, "1900",
	"Lethal Enforcers (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lenRomInfo, lenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lethal Enforcers II - Gun Fighters (U) [!]

static struct BurnRomInfo len2RomDesc[]={
	{ "g_len2.bin", 0x200000, 0xE5FDD28B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(len2);
STD_ROM_FN(len2);

struct BurnDriverD BurnDrvMDlen2 = {
	"g_len2", NULL, NULL, "1900",
	"Lethal Enforcers II - Gun Fighters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, len2RomInfo, len2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mario Andretti Racing (UE) [!]

static struct BurnRomInfo mamrRomDesc[]={
	{ "g_mamr.bin", 0x200000, 0x7F1DC0AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mamr);
STD_ROM_FN(mamr);

struct BurnDriverD BurnDrvMDmamr = {
	"g_mamr", NULL, NULL, "1900",
	"Mario Andretti Racing (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mamrRomInfo, mamrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Master of Monsters (U) [!]

static struct BurnRomInfo mamoRomDesc[]={
	{ "g_mamo.bin", 0x080000, 0x91354820, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mamo);
STD_ROM_FN(mamo);

struct BurnDriverD BurnDrvMDmamo = {
	"g_mamo", NULL, NULL, "1900",
	"Master of Monsters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mamoRomInfo, mamoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Bomberman (UE) [!]

static struct BurnRomInfo mbmbRomDesc[]={
	{ "g_mbmb.bin", 0x100000, 0x4BD6667D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mbmb);
STD_ROM_FN(mbmb);

struct BurnDriverD BurnDrvMDmbmb = {
	"g_mbmb", NULL, NULL, "1900",
	"Mega Bomberman (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mbmbRomInfo, mbmbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Jam Tournament Edition (W) (REV01) [!]

static struct BurnRomInfo njteRomDesc[]={
	{ "g_njte.bin", 0x300000, 0x6E25EBF0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(njte);
STD_ROM_FN(njte);

struct BurnDriverD BurnDrvMDnjte = {
	"g_njte", NULL, NULL, "1900",
	"NBA Jam Tournament Edition (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, njteRomInfo, njteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Live 98 (U) [!]

static struct BurnRomInfo nl98RomDesc[]={
	{ "g_nl98.bin", 0x200000, 0x23473A8A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nl98);
STD_ROM_FN(nl98);

struct BurnDriverD BurnDrvMDnl98 = {
	"g_nl98", NULL, NULL, "1900",
	"NBA Live 98 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nl98RomInfo, nl98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// New Zealand Stor

static struct BurnRomInfo tnzsRomDesc[]={
	{ "g_tnzs.bin", 0x080000, 0x1C77AD21, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tnzs);
STD_ROM_FN(tnzs);

struct BurnDriverD BurnDrvMDtnzs = {
	"g_tnzs", NULL, NULL, "1900",
	"New Zealand Stor\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tnzsRomInfo, tnzsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// No Escape (U) [!]

static struct BurnRomInfo noesRomDesc[]={
	{ "g_noes.bin", 0x200000, 0x44EE5F20, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(noes);
STD_ROM_FN(noes);

struct BurnDriverD BurnDrvMDnoes = {
	"g_noes", NULL, NULL, "1900",
	"No Escape (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, noesRomInfo, noesRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Normy's Beach Babe-O-Rama (UE) [!]

static struct BurnRomInfo normRomDesc[]={
	{ "g_norm.bin", 0x100000, 0xB56A8220, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(norm);
STD_ROM_FN(norm);

struct BurnDriverD BurnDrvMDnorm = {
	"g_norm", NULL, NULL, "1900",
	"Normy's Beach Babe-O-Rama (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, normRomInfo, normRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Paperboy (UE) [!]

static struct BurnRomInfo papbRomDesc[]={
	{ "g_papb.bin", 0x080000, 0x0A44819B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(papb);
STD_ROM_FN(papb);

struct BurnDriverD BurnDrvMDpapb = {
	"g_papb", NULL, NULL, "1900",
	"Paperboy (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, papbRomInfo, papbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Paperboy II (U) [!]

static struct BurnRomInfo pap2RomDesc[]={
	{ "g_pap2.bin", 0x100000, 0x1DE28BB1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pap2);
STD_ROM_FN(pap2);

struct BurnDriverD BurnDrvMDpap2 = {
	"g_pap2", NULL, NULL, "1900",
	"Paperboy II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pap2RomInfo, pap2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Populous II - Two Tribes (E) [!]

static struct BurnRomInfo pop2RomDesc[]={
	{ "g_pop2.bin", 0x100000, 0xEE988BD9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pop2);
STD_ROM_FN(pop2);

struct BurnDriverD BurnDrvMDpop2 = {
	"g_pop2", NULL, NULL, "1900",
	"Populous II - Two Tribes (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pop2RomInfo, pop2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Quad Challenge (U) [c][!]

static struct BurnRomInfo quadRomDesc[]={
	{ "g_quad.bin", 0x080000, 0x74736A80, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(quad);
STD_ROM_FN(quad);

struct BurnDriverD BurnDrvMDquad = {
	"g_quad", NULL, NULL, "1900",
	"Quad Challenge (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, quadRomInfo, quadRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Risk (U) [!]

static struct BurnRomInfo riskRomDesc[]={
	{ "g_risk.bin", 0x080000, 0x80416D0D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(risk);
STD_ROM_FN(risk);

struct BurnDriverD BurnDrvMDrisk = {
	"g_risk", NULL, NULL, "1900",
	"Risk (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, riskRomInfo, riskRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rise of the Robots (E) [!]

static struct BurnRomInfo riseRomDesc[]={
	{ "g_rise.bin", 0x300000, 0x5650780B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rise);
STD_ROM_FN(rise);

struct BurnDriverD BurnDrvMDrise = {
	"g_rise", NULL, NULL, "1900",
	"Rise of the Robots (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, riseRomInfo, riseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shove It! - The Warehouse Game (U) [!]

static struct BurnRomInfo shovRomDesc[]={
	{ "g_shov.bin", 0x020000, 0xC51F40CB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shov);
STD_ROM_FN(shov);

struct BurnDriverD BurnDrvMDshov = {
	"g_shov", NULL, NULL, "1900",
	"Shove It! - The Warehouse Game (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shovRomInfo, shovRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Side Pocket (JU) [!]

static struct BurnRomInfo sideRomDesc[]={
	{ "g_side.bin", 0x100000, 0xAF9F275D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(side);
STD_ROM_FN(side);

struct BurnDriverD BurnDrvMDside = {
	"g_side", NULL, NULL, "1900",
	"Side Pocket (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sideRomInfo, sideRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Trek - Deep Space 9 - Crossroads of Time (U) [!]

static struct BurnRomInfo std9RomDesc[]={
	{ "g_std9.bin", 0x100000, 0xA771E1A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(std9);
STD_ROM_FN(std9);

struct BurnDriverD BurnDrvMDstd9 = {
	"g_std9", NULL, NULL, "1900",
	"Star Trek - Deep Space 9 - Crossroads of Time (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, std9RomInfo, std9RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Trek - The Next Generation (U) (REV01) [!]

static struct BurnRomInfo stngRomDesc[]={
	{ "g_stng.bin", 0x200000, 0xEF840EF2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stng);
STD_ROM_FN(stng);

struct BurnDriverD BurnDrvMDstng = {
	"g_stng", NULL, NULL, "1900",
	"Star Trek - The Next Generation (U) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stngRomInfo, stngRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// T2 - The Arcade Game (UE) (REV01) [!]

static struct BurnRomInfo t2arRomDesc[]={
	{ "g_t2ar.bin", 0x100000, 0xA1264F17, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(t2ar);
STD_ROM_FN(t2ar);

struct BurnDriverD BurnDrvMDt2ar = {
	"g_t2ar", NULL, NULL, "1900",
	"T2 - The Arcade Game (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, t2arRomInfo, t2arRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Valis (U) [!]

static struct BurnRomInfo valiRomDesc[]={
	{ "g_vali.bin", 0x100000, 0x13BC5B72, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vali);
STD_ROM_FN(vali);

struct BurnDriverD BurnDrvMDvali = {
	"g_vali", NULL, NULL, "1900",
	"Valis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, valiRomInfo, valiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Valis III (U) [!]

static struct BurnRomInfo val3RomDesc[]={
	{ "g_val3.bin", 0x100000, 0x59A2A368, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(val3);
STD_ROM_FN(val3);

struct BurnDriverD BurnDrvMDval3 = {
	"g_val3", NULL, NULL, "1900",
	"Valis III (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, val3RomInfo, val3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtual Pinball (UE) [!]

static struct BurnRomInfo vpinRomDesc[]={
	{ "g_vpin.bin", 0x100000, 0xD63473AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vpin);
STD_ROM_FN(vpin);

struct BurnDriverD BurnDrvMDvpin = {
	"g_vpin", NULL, NULL, "1900",
	"Virtual Pinball (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vpinRomInfo, vpinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wimbledon Championship Tennis (U) [!]

static struct BurnRomInfo wimbRomDesc[]={
	{ "g_wimb.bin", 0x100000, 0xF9142AEE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wimb);
STD_ROM_FN(wimb);

struct BurnDriverD BurnDrvMDwimb = {
	"g_wimb", NULL, NULL, "1900",
	"Wimbledon Championship Tennis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wimbRomInfo, wimbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Live 97 (UE) [!]

static struct BurnRomInfo nl97RomDesc[]={
	{ "g_nl97.bin", 0x200000, 0x7024843A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nl97);
STD_ROM_FN(nl97);

struct BurnDriverD BurnDrvMDnl97 = {
	"g_nl97", NULL, NULL, "1900",
	"NBA Live 97 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nl97RomInfo, nl97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Live 96 (UE) [!]

static struct BurnRomInfo nl96RomDesc[]={
	{ "g_nl96.bin", 0x200000, 0x49DE0062, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nl96);
STD_ROM_FN(nl96);

struct BurnDriverD BurnDrvMDnl96 = {
	"g_nl96", NULL, NULL, "1900",
	"NBA Live 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nl96RomInfo, nl96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Live 95 (UE) [!]

static struct BurnRomInfo nl95RomDesc[]={
	{ "g_nl95.bin", 0x200000, 0x66018ABC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nl95);
STD_ROM_FN(nl95);

struct BurnDriverD BurnDrvMDnl95 = {
	"g_nl95", NULL, NULL, "1900",
	"NBA Live 95 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nl95RomInfo, nl95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Jam (UE) (REV01) [!]

static struct BurnRomInfo njamRomDesc[]={
	{ "g_njam.bin", 0x200000, 0xEB8360E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(njam);
STD_ROM_FN(njam);

struct BurnDriverD BurnDrvMDnjam = {
	"g_njam", NULL, NULL, "1900",
	"NBA Jam (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, njamRomInfo, njamRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA All-Star Challenge (UE) [!]

static struct BurnRomInfo nascRomDesc[]={
	{ "g_nasc.bin", 0x100000, 0xC4674ADF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nasc);
STD_ROM_FN(nasc);

struct BurnDriverD BurnDrvMDnasc = {
	"g_nasc", NULL, NULL, "1900",
	"NBA All-Star Challenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nascRomInfo, nascRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Action (U) [!]

static struct BurnRomInfo nactRomDesc[]={
	{ "g_nact.bin", 0x200000, 0x99C348BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nact);
STD_ROM_FN(nact);

struct BurnDriverD BurnDrvMDnact = {
	"g_nact", NULL, NULL, "1994",
	"NBA Action (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nactRomInfo, nactRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Action '95 (UE) [!]

static struct BurnRomInfo na95RomDesc[]={
	{ "g_na95.bin", 0x200000, 0xAA7006D6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(na95);
STD_ROM_FN(na95);

struct BurnDriverD BurnDrvMDna95 = {
	"g_na95", NULL, NULL, "1900",
	"NBA Action '95 (UE) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, na95RomInfo, na95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Playoff - Bulls vs Blazers (J) [!]

static struct BurnRomInfo npbbRomDesc[]={
	{ "g_npbb.bin", 0x100000, 0x4565CE1F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(npbb);
STD_ROM_FN(npbb);

struct BurnDriverD BurnDrvMDnpbb = {
	"g_npbb", NULL, NULL, "1993",
	"NBA Playoff - Bulls vs Blazers (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, npbbRomInfo, npbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Showdown 94 (Beta)

static struct BurnRomInfo nba9RomDesc[]={
	{ "g_nba9.bin", 0x200000, 0xEEA19BCE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nba9);
STD_ROM_FN(nba9);

struct BurnDriverD BurnDrvMDnba9 = {
	"g_nba9", NULL, NULL, "1900",
	"NBA Showdown 94 (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nba9RomInfo, nba9RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Pro Basketball - Bulls vs Lakers (J) [!]

static struct BurnRomInfo npblRomDesc[]={
	{ "g_npbl.bin", 0x100000, 0x4416CE39, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(npbl);
STD_ROM_FN(npbl);

struct BurnDriverD BurnDrvMDnpbl = {
	"g_npbl", NULL, NULL, "1993",
	"NBA Pro Basketball - Bulls vs Lakers (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, npblRomInfo, npblRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Showdown 94 (UE) [!]

static struct BurnRomInfo nbs9RomDesc[]={
	{ "g_nbs9.bin", 0x200000, 0x160B7090, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbs9);
STD_ROM_FN(nbs9);

struct BurnDriverD BurnDrvMDnbs9 = {
	"g_nbs9", NULL, NULL, "1900",
	"NBA Showdown 94 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbs9RomInfo, nbs9RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NCAA College Football (U) [!]

static struct BurnRomInfo nccfRomDesc[]={
	{ "g_nccf.bin", 0x100000, 0x081012F0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nccf);
STD_ROM_FN(nccf);

struct BurnDriverD BurnDrvMDnccf = {
	"g_nccf", NULL, NULL, "1900",
	"NCAA College Football (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nccfRomInfo, nccfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NCAA Final Four College Basketball (U) [!]

static struct BurnRomInfo ncffRomDesc[]={
	{ "g_ncff.bin", 0x180000, 0xED0C1303, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ncff);
STD_ROM_FN(ncff);

struct BurnDriverD BurnDrvMDncff = {
	"g_ncff", NULL, NULL, "1900",
	"NCAA Final Four College Basketball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ncffRomInfo, ncffRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL 98 (U) [!]

static struct BurnRomInfo nfl8RomDesc[]={
	{ "g_nfl8.bin", 0x200000, 0xF73EC54C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nfl8);
STD_ROM_FN(nfl8);

struct BurnDriverD BurnDrvMDnfl8 = {
	"g_nfl8", NULL, NULL, "1997",
	"NFL 98 (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nfl8RomInfo, nfl8RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL '95 (U) [!]

static struct BurnRomInfo nfl5RomDesc[]={
	{ "g_nfl5.bin", 0x200000, 0xB58E4A81, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nfl5);
STD_ROM_FN(nfl5);

struct BurnDriverD BurnDrvMDnfl5 = {
	"g_nfl5", NULL, NULL, "1994",
	"NFL '95 (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nfl5RomInfo, nfl5RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL Football '94 Starring Joe Montana (U) [!]

static struct BurnRomInfo nfl4RomDesc[]={
	{ "g_nfl4.bin", 0x200000, 0x0D486ED5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nfl4);
STD_ROM_FN(nfl4);

struct BurnDriverD BurnDrvMDnfl4 = {
	"g_nfl4", NULL, NULL, "1900",
	"NFL Football '94 Starring Joe Montana (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nfl4RomInfo, nfl4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL Prime Time (U) [!]

static struct BurnRomInfo nfptRomDesc[]={
	{ "g_nfpt.bin", 0x200000, 0x5AA53CBC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nfpt);
STD_ROM_FN(nfpt);

struct BurnDriverD BurnDrvMDnfpt = {
	"g_nfpt", NULL, NULL, "1995",
	"NFL Prime Time (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nfptRomInfo, nfptRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL Quarterback Club 96 (UE) [!]

static struct BurnRomInfo nqc6RomDesc[]={
	{ "g_nqc6.bin", 0x400000, 0xD5A37CAB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nqc6);
STD_ROM_FN(nqc6);

struct BurnDriverD BurnDrvMDnqc6 = {
	"g_nqc6", NULL, NULL, "1900",
	"NFL Quarterback Club 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nqc6RomInfo, nqc6RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL Quarterback Club 96 (UE) [!]

static struct BurnRomInfo nqcRomDesc[]={
	{ "g_nqc.bin", 0x300000, 0x94542EAF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nqc);
STD_ROM_FN(nqc);

struct BurnDriverD BurnDrvMDnqc = {
	"g_nqc", NULL, NULL, "1900",
	"NFL Quarterback Club 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nqcRomInfo, nqcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 95 (UE) [!]

static struct BurnRomInfo nh95RomDesc[]={
	{ "g_nh95.bin", 0x200000, 0xE8EE917E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh95);
STD_ROM_FN(nh95);

struct BurnDriverD BurnDrvMDnh95 = {
	"g_nh95", NULL, NULL, "1900",
	"NHL 95 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh95RomInfo, nh95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 95 Elitserien (E) [c][!]

static struct BurnRomInfo nh9eRomDesc[]={
	{ "g_nh9e.bin", 0x200000, 0xE10A25C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh9e);
STD_ROM_FN(nh9e);

struct BurnDriverD BurnDrvMDnh9e = {
	"g_nh9e", NULL, NULL, "1900",
	"NHL 95 Elitserien (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh9eRomInfo, nh9eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 96 (UE) [!]

static struct BurnRomInfo nh96RomDesc[]={
	{ "g_nh96.bin", 0x200000, 0x8135702C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh96);
STD_ROM_FN(nh96);

struct BurnDriverD BurnDrvMDnh96 = {
	"g_nh96", NULL, NULL, "1900",
	"NHL 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh96RomInfo, nh96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 97 (UE) [!]

static struct BurnRomInfo nh97RomDesc[]={
	{ "g_nh97.bin", 0x200000, 0xF067C103, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nh97);
STD_ROM_FN(nh97);

struct BurnDriverD BurnDrvMDnh97 = {
	"g_nh97", NULL, NULL, "1900",
	"NHL 97 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nh97RomInfo, nh97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL All-Star Hockey '95 (U) [!]

static struct BurnRomInfo nashRomDesc[]={
	{ "g_nash.bin", 0x200000, 0xE6C0218B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nash);
STD_ROM_FN(nash);

struct BurnDriverD BurnDrvMDnash = {
	"g_nash", NULL, NULL, "1900",
	"NHL All-Star Hockey '95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nashRomInfo, nashRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL Hockey (U) [!]

static struct BurnRomInfo nhlhRomDesc[]={
	{ "g_nhlh.bin", 0x080000, 0x2641653F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nhlh);
STD_ROM_FN(nhlh);

struct BurnDriver BurnDrvMDnhlh = {
	"g_nhlh", NULL, NULL, "1900",
	"NHL Hockey (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nhlhRomInfo, nhlhRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHLPA Hockey '93 (UE) (REV01) [!]

static struct BurnRomInfo nhlpRomDesc[]={
	{ "g_nhlp.bin", 0x080000, 0xF361D0BF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nhlp);
STD_ROM_FN(nhlp);

struct BurnDriverD BurnDrvMDnhlp = {
	"g_nhlp", NULL, NULL, "1900",
	"NHLPA Hockey '93 (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nhlpRomInfo, nhlpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Summer Games Atlanta 96 (UE) [!]

static struct BurnRomInfo olsgRomDesc[]={
	{ "g_olsg.bin", 0x200000, 0x9E470FB9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olsg);
STD_ROM_FN(olsg);

struct BurnDriverD BurnDrvMDolsg = {
	"g_olsg", NULL, NULL, "1900",
	"Olympic Summer Games Atlanta 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olsgRomInfo, olsgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Winter Games - Lillehammer 94 (U) [c][!]

static struct BurnRomInfo olwgRomDesc[]={
	{ "g_olwg.bin", 0x200000, 0xC5834437, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olwg);
STD_ROM_FN(olwg);

struct BurnDriverD BurnDrvMDolwg = {
	"g_olwg", NULL, NULL, "1900",
	"Olympic Winter Games - Lillehammer 94 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olwgRomInfo, olwgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pat Riley Basketball (U) [!]

static struct BurnRomInfo patbRomDesc[]={
	{ "g_patb.bin", 0x080000, 0x3D9318A7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(patb);
STD_ROM_FN(patb);

struct BurnDriverD BurnDrvMDpatb = {
	"g_patb", NULL, NULL, "1990",
	"Pat Riley Basketball (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, patbRomInfo, patbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pele! (UE) [!]

static struct BurnRomInfo peleRomDesc[]={
	{ "g_pele.bin", 0x100000, 0x5A8ABE51, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pele);
STD_ROM_FN(pele);

struct BurnDriverD BurnDrvMDpele = {
	"g_pele", NULL, NULL, "1900",
	"Pele! (UE) [!]\0", NULL, "Accolate", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, peleRomInfo, peleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pele's World Tournament Soccer (UE) [!]

static struct BurnRomInfo pelwRomDesc[]={
	{ "g_pelw.bin", 0x200000, 0x05A486E9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pelw);
STD_ROM_FN(pelw);

struct BurnDriverD BurnDrvMDpelw = {
	"g_pelw", NULL, NULL, "1900",
	"Pele's World Tournament Soccer (UE) [!]\0", NULL, "Sport Accolate", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pelwRomInfo, pelwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II (UE) (REV02) [!]

static struct BurnRomInfo pstRomDesc[]={
	{ "g_pst.bin", 0x100000, 0x9EF5BBD1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pst);
STD_ROM_FN(pst);

struct BurnDriverD BurnDrvMDpst = {
	"g_pst", NULL, NULL, "1989",
	"Phantasy Star II (UE) (REV02) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pstRomInfo, pstRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA European Tour (UE) [!]

static struct BurnRomInfo pgaeRomDesc[]={
	{ "g_pgae.bin", 0x100000, 0x8CA45ACD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pgae);
STD_ROM_FN(pgae);

struct BurnDriverD BurnDrvMDpgae = {
	"g_pgae", NULL, NULL, "1900",
	"PGA European Tour (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pgaeRomInfo, pgaeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// RBI Baseball 3 (U) [c][!]

static struct BurnRomInfo rb3RomDesc[]={
	{ "g_rb3.bin", 0x080000, 0x4840348C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rb3);
STD_ROM_FN(rb3);

struct BurnDriverD BurnDrvMDrb3 = {
	"g_rb3", NULL, NULL, "1900",
	"RBI Baseball 3 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rb3RomInfo, rb3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// RBI Baseball 4 (U) [!]

static struct BurnRomInfo rb4RomDesc[]={
	{ "g_rb4.bin", 0x100000, 0xFECF9B94, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rb4);
STD_ROM_FN(rb4);

struct BurnDriverD BurnDrvMDrb4 = {
	"g_rb4", NULL, NULL, "1900",
	"RBI Baseball 4 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rb4RomInfo, rb4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// RBI Baseball 93 (U) [!]

static struct BurnRomInfo rb93RomDesc[]={
	{ "g_rb93.bin", 0x100000, 0xBEAFCE84, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rb93);
STD_ROM_FN(rb93);

struct BurnDriverD BurnDrvMDrb93 = {
	"g_rb93", NULL, NULL, "1900",
	"RBI Baseball 93 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rb93RomInfo, rb93RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// RBI Baseball 94 (UE) [!]

static struct BurnRomInfo rb94RomDesc[]={
	{ "g_rb94.bin", 0x200000, 0x4EB4D5E4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rb94);
STD_ROM_FN(rb94);

struct BurnDriverD BurnDrvMDrb94 = {
	"g_rb94", NULL, NULL, "1900",
	"RBI Baseball 94 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rb94RomInfo, rb94RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Roger Clemens' MVP Baseball (U) [!]

static struct BurnRomInfo rcvmRomDesc[]={
	{ "g_rcvm.bin", 0x100000, 0x83699E34, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rcvm);
STD_ROM_FN(rcvm);

struct BurnDriverD BurnDrvMDrcvm = {
	"g_rcvm", NULL, NULL, "1900",
	"Roger Clemens' MVP Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rcvmRomInfo, rcvmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rugby World Cup 1995 (UE) (M3) [!]

static struct BurnRomInfo rw93RomDesc[]={
	{ "g_rw93.bin", 0x200000, 0x61F90A8A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rw93);
STD_ROM_FN(rw93);

struct BurnDriverD BurnDrvMDrw93 = {
	"g_rw93", NULL, NULL, "1900",
	"Rugby World Cup 1995 (UE) (M3) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rw93RomInfo, rw93RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shane Warne Cricket (E) [c][!]

static struct BurnRomInfo swcrRomDesc[]={
	{ "g_swcr.bin", 0x100000, 0x68865F6F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(swcr);
STD_ROM_FN(swcr);

struct BurnDriverD BurnDrvMDswcr = {
	"g_swcr", NULL, NULL, "1900",
	"Shane Warne Cricket (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, swcrRomInfo, swcrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shin Changsegi - Ragnacenty (K) [!]

static struct BurnRomInfo shiRomDesc[]={
	{ "g_shi.bin", 0x100000, 0xB870C2F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shi);
STD_ROM_FN(shi);

struct BurnDriverD BurnDrvMDshi = {
	"g_shi", NULL, NULL, "1994",
	"Shin Changsegi - Ragnacenty (K) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shiRomInfo, shiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Real Basketball (E) [c][!]

static struct BurnRomInfo srbaRomDesc[]={
	{ "g_srba.bin", 0x080000, 0xF04765BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(srba);
STD_ROM_FN(srba);

struct BurnDriverD BurnDrvMDsrba = {
	"g_srba", NULL, NULL, "1900",
	"Super Real Basketball (E) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, srbaRomInfo, srbaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Volleyball (U) [c][!]

static struct BurnRomInfo svolRomDesc[]={
	{ "g_svol.bin", 0x040000, 0xA88FEE44, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(svol);
STD_ROM_FN(svol);

struct BurnDriverD BurnDrvMDsvol = {
	"g_svol", NULL, NULL, "1900",
	"Super Volleyball (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, svolRomInfo, svolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtua Racing (U) [!]

static struct BurnRomInfo virrRomDesc[]={
	{ "g_virr.bin", 0x200000, 0x7E1A324A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(virr);
STD_ROM_FN(virr);

struct BurnDriverD BurnDrvMDvirr = {
	"g_virr", NULL, NULL, "199?",
	"Virtua Racing (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, virrRomInfo, virrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Series Baseball '96 (U) [!]

static struct BurnRomInfo ws96RomDesc[]={
	{ "g_ws96.bin", 0x300000, 0x04EE8272, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ws96);
STD_ROM_FN(ws96);

struct BurnDriverD BurnDrvMDws96 = {
	"g_ws96", NULL, NULL, "1900",
	"World Series Baseball '96 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ws96RomInfo, ws96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Series Baseball '95 (U) [!]

static struct BurnRomInfo ws95RomDesc[]={
	{ "g_ws95.bin", 0x300000, 0x25130077, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ws95);
STD_ROM_FN(ws95);

struct BurnDriverD BurnDrvMDws95 = {
	"g_ws95", NULL, NULL, "1900",
	"World Series Baseball '95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ws95RomInfo, ws95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Series Baseball (U) [!]

static struct BurnRomInfo wsbRomDesc[]={
	{ "g_wsb.bin", 0x200000, 0x57C1D5EC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wsb);
STD_ROM_FN(wsb);

struct BurnDriverD BurnDrvMDwsb = {
	"g_wsb", NULL, NULL, "1900",
	"World Series Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wsbRomInfo, wsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Trophy Soccer (U) [!]

static struct BurnRomInfo wtsRomDesc[]={
	{ "g_wts.bin", 0x080000, 0x6E3EDC7C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wts);
STD_ROM_FN(wts);

struct BurnDriver BurnDrvMDwts = {
	"g_wts", NULL, NULL, "1900",
	"World Trophy Soccer (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wtsRomInfo, wtsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// WWF Super Wrestlemania (UE) [!]

static struct BurnRomInfo wfswRomDesc[]={
	{ "g_wfsw.bin", 0x100000, 0xB929D6C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wfsw);
STD_ROM_FN(wfsw);

struct BurnDriverD BurnDrvMDwfsw = {
	"g_wfsw", NULL, NULL, "1900",
	"WWF Super Wrestlemania (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wfswRomInfo, wfswRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ys III - Wanderers from Ys (U) [!]

static struct BurnRomInfo ys3RomDesc[]={
	{ "g_ys3.bin", 0x100000, 0xEA27976E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ys3);
STD_ROM_FN(ys3);

struct BurnDriverD BurnDrvMDys3 = {
	"g_ys3", NULL, NULL, "1900",
	"Ys III - Wanderers from Ys (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ys3RomInfo, ys3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Madden NFL 95 (UE) [!]

static struct BurnRomInfo ma95RomDesc[]={
	{ "g_ma95.bin", 0x200000, 0xDB0BE0C2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma95);
STD_ROM_FN(ma95);

struct BurnDriverD BurnDrvMDma95 = {
	"g_ma95", NULL, NULL, "1900",
	"Madden NFL 95 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma95RomInfo, ma95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Madden NFL 96 (UE) [!]

static struct BurnRomInfo ma96RomDesc[]={
	{ "g_ma96.bin", 0x200000, 0xF126918B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma96);
STD_ROM_FN(ma96);

struct BurnDriverD BurnDrvMDma96 = {
	"g_ma96", NULL, NULL, "1900",
	"Madden NFL 96 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma96RomInfo, ma96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Madden NFL 97 (UE) [!]

static struct BurnRomInfo ma97RomDesc[]={
	{ "g_ma97.bin", 0x200000, 0xC4B4E112, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma97);
STD_ROM_FN(ma97);

struct BurnDriverD BurnDrvMDma97 = {
	"g_ma97", NULL, NULL, "1900",
	"Madden NFL 97 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma97RomInfo, ma97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Madden NFL 98 (U) [c][!]

static struct BurnRomInfo ma98RomDesc[]={
	{ "g_ma98.bin", 0x200000, 0xE051EA62, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma98);
STD_ROM_FN(ma98);

struct BurnDriverD BurnDrvMDma98 = {
	"g_ma98", NULL, NULL, "1900",
	"Madden NFL 98 (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma98RomInfo, ma98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden NFL 94 (UE) [c][!]

static struct BurnRomInfo ma94RomDesc[]={
	{ "g_ma94.bin", 0x200000, 0xD14B811B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma94);
STD_ROM_FN(ma94);

struct BurnDriverD BurnDrvMDma94 = {
	"g_ma94", NULL, NULL, "1900",
	"John Madden NFL 94 (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma94RomInfo, ma94RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden Football '93 (UE) [c][!]

static struct BurnRomInfo ma93RomDesc[]={
	{ "g_ma93.bin", 0x100000, 0xCA323B3E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma93);
STD_ROM_FN(ma93);

struct BurnDriverD BurnDrvMDma93 = {
	"g_ma93", NULL, NULL, "1900",
	"John Madden Football '93 (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma93RomInfo, ma93RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden Football '92 (UE) [!]

static struct BurnRomInfo ma92RomDesc[]={
	{ "g_ma92.bin", 0x080000, 0x046E3945, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma92);
STD_ROM_FN(ma92);

struct BurnDriver BurnDrvMDma92 = {
	"g_ma92", NULL, NULL, "1900",
	"John Madden Football '92 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma92RomInfo, ma92RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden Football '93 - Championship Edition (U) [!]

static struct BurnRomInfo ma3cRomDesc[]={
	{ "g_ma3c.bin", 0x100000, 0xCA534B1A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma3c);
STD_ROM_FN(ma3c);

struct BurnDriverD BurnDrvMDma3c = {
	"g_ma3c", NULL, NULL, "1900",
	"John Madden Football '93 - Championship Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ma3cRomInfo, ma3cRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden Football (UE) [!]

static struct BurnRomInfo maRomDesc[]={
	{ "g_ma.bin", 0x080000, 0x90FB8818, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ma);
STD_ROM_FN(ma);

struct BurnDriver BurnDrvMDma = {
	"g_ma", NULL, NULL, "1900",
	"John Madden Football (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, maRomInfo, maRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Joe Montana Football (JU) [!]

static struct BurnRomInfo jmofRomDesc[]={
	{ "g_jmof.bin", 0x080000, 0x8AA6A1DD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jmof);
STD_ROM_FN(jmof);

struct BurnDriverD BurnDrvMDjmof = {
	"g_jmof", NULL, NULL, "1900",
	"Joe Montana Football (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jmofRomInfo, jmofRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Joe Montana Sports Talk Football 2 (W) (REV01) [!]

static struct BurnRomInfo jms2RomDesc[]={
	{ "g_jms2.bin", 0x100000, 0xA45DA893, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jms2);
STD_ROM_FN(jms2);

struct BurnDriver BurnDrvMDjms2 = {
	"g_jms2", NULL, NULL, "1900",
	"Joe Montana Sports Talk Football 2 (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jms2RomInfo, jms2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Joe Montana Sports Talk Football 2 (W) (REV01) [!]

static struct BurnRomInfo jmsRomDesc[]={
	{ "g_jms.bin", 0x180000, 0xCE0B1FE1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jms);
STD_ROM_FN(jms);

struct BurnDriverD BurnDrvMDjms = {
	"g_jms", NULL, NULL, "1900",
	"Joe Montana Sports Talk Football 2 (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jmsRomInfo, jmsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// HardBall '94 (UE) [!]

static struct BurnRomInfo hb94RomDesc[]={
	{ "g_hb94.bin", 0x200000, 0xEA9C4878, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hb94);
STD_ROM_FN(hb94);

struct BurnDriverD BurnDrvMDhb94 = {
	"g_hb94", NULL, NULL, "1900",
	"HardBall '94 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hb94RomInfo, hb94RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// HardBall III (U) [!]

static struct BurnRomInfo hb3RomDesc[]={
	{ "g_hb3.bin", 0x200000, 0xA4F2F011, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hb3);
STD_ROM_FN(hb3);

struct BurnDriverD BurnDrvMDhb3 = {
	"g_hb3", NULL, NULL, "1900",
	"HardBall III (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hb3RomInfo, hb3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// HardBall '95 (U) [!]

static struct BurnRomInfo hbRomDesc[]={
	{ "g_hb.bin", 0x100000, 0xBD1B9A04, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hb);
STD_ROM_FN(hb);

struct BurnDriverD BurnDrvMDhb = {
	"g_hb", NULL, NULL, "1900",
	"HardBall '95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hbRomInfo, hbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Coach K College Basketball (U) [!]

static struct BurnRomInfo coakRomDesc[]={
	{ "g_coak.bin", 0x200000, 0x67C309C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(coak);
STD_ROM_FN(coak);

struct BurnDriverD BurnDrvMDcoak = {
	"g_coak", NULL, NULL, "1900",
	"Coach K College Basketball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, coakRomInfo, coakRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// College Football USA 96 (U) [!]

static struct BurnRomInfo cf96RomDesc[]={
	{ "g_cf96.bin", 0x200000, 0xB9075385, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cf96);
STD_ROM_FN(cf96);

struct BurnDriverD BurnDrvMDcf96 = {
	"g_cf96", NULL, NULL, "1900",
	"College Football USA 96 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cf96RomInfo, cf96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// College Football USA 97 - The Road to New Orleans (U) [!]

static struct BurnRomInfo cf97RomDesc[]={
	{ "g_cf97.bin", 0x200000, 0x2EBB90A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cf97);
STD_ROM_FN(cf97);

struct BurnDriverD BurnDrvMDcf97 = {
	"g_cf97", NULL, NULL, "1900",
	"College Football USA 97 - The Road to New Orleans (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cf97RomInfo, cf97RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// College Football's National Championship (U) [!]

static struct BurnRomInfo cfnRomDesc[]={
	{ "g_cfn.bin", 0x200000, 0x172C5DBB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cfn);
STD_ROM_FN(cfn);

struct BurnDriverD BurnDrvMDcfn = {
	"g_cfn", NULL, NULL, "1994",
	"College Football's National Championship (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cfnRomInfo, cfnRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// College Football's National Championship II (U) [!]

static struct BurnRomInfo cfn2RomDesc[]={
	{ "g_cfn2.bin", 0x200000, 0x65B64413, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cfn2);
STD_ROM_FN(cfn2);

struct BurnDriverD BurnDrvMDcfn2 = {
	"g_cfn2", NULL, NULL, "1995",
	"College Football's National Championship II (U) [!]\0", NULL, "Sega Sports", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cfn2RomInfo, cfn2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// College Slam (U) [!]

static struct BurnRomInfo cslaRomDesc[]={
	{ "g_csla.bin", 0x400000, 0x96A42431, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(csla);
STD_ROM_FN(csla);

struct BurnDriverD BurnDrvMDcsla = {
	"g_csla", NULL, NULL, "1900",
	"College Slam (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cslaRomInfo, cslaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// CrossFire (U) [c][!]

static struct BurnRomInfo cfirRomDesc[]={
	{ "g_cfir.bin", 0x080000, 0xCC73F3A9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cfir);
STD_ROM_FN(cfir);

struct BurnDriverD BurnDrvMDcfir = {
	"g_cfir", NULL, NULL, "1991",
	"CrossFire (U) [c][!]\0", NULL, "Kyugo", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cfirRomInfo, cfirRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crusader of Centy (U) [!]

static struct BurnRomInfo ccRomDesc[]={
	{ "g_cc.bin", 0x200000, 0x41858F6F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cc);
STD_ROM_FN(cc);

struct BurnDriverD BurnDrvMDcc = {
	"g_cc", NULL, NULL, "1994",
	"Crusader of Centy (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ccRomInfo, ccRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crystal's Pony Tale (U) [!]

static struct BurnRomInfo crysRomDesc[]={
	{ "g_crys.bin", 0x100000, 0x6CF7A4DF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crys);
STD_ROM_FN(crys);

struct BurnDriverD BurnDrvMDcrys = {
	"g_crys", NULL, NULL, "1900",
	"Crystal's Pony Tale (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crysRomInfo, crysRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// CyberBall (W) [!]

static struct BurnRomInfo cybbRomDesc[]={
	{ "g_cybb.bin", 0x080000, 0x76120E96, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cybb);
STD_ROM_FN(cybb);

struct BurnDriverD BurnDrvMDcybb = {
	"g_cybb", NULL, NULL, "1900",
	"CyberBall (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cybbRomInfo, cybbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cyber-Cop (U) [c][!]

static struct BurnRomInfo ccopRomDesc[]={
	{ "g_ccop.bin", 0x100000, 0x01E719C8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ccop);
STD_ROM_FN(ccop);

struct BurnDriverD BurnDrvMDccop = {
	"g_ccop", NULL, NULL, "1994",
	"Cyber-Cop (U) [c][!]\0", NULL, "Core / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ccopRomInfo, ccopRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// David Crane's Amazing Tennis (U) [!]

static struct BurnRomInfo dcatRomDesc[]={
	{ "g_dcat.bin", 0x100000, 0x9177088C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dcat);
STD_ROM_FN(dcat);

struct BurnDriverD BurnDrvMDdcat = {
	"g_dcat", NULL, NULL, "1900",
	"David Crane's Amazing Tennis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dcatRomInfo, dcatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// David Robinson Basketball (J) [!]

static struct BurnRomInfo drbbRomDesc[]={
	{ "g_drbb.bin", 0x080000, 0x56164B00, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drbb);
STD_ROM_FN(drbb);

struct BurnDriverD BurnDrvMDdrbb = {
	"g_drbb", NULL, NULL, "1900",
	"David Robinson Basketball (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, drbbRomInfo, drbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// David Robinson's Supreme Court (U) [!]

static struct BurnRomInfo drscRomDesc[]={
	{ "g_drsc.bin", 0x080000, 0x512B7599, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drsc);
STD_ROM_FN(drsc);

struct BurnDriverD BurnDrvMDdrsc = {
	"g_drsc", NULL, NULL, "1900",
	"David Robinson's Supreme Court (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, drscRomInfo, drscRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Devil Crash MD (J) [!]

static struct BurnRomInfo dcmdRomDesc[]={
	{ "g_dcmd.bin", 0x080000, 0x4C4CAAD8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dcmd);
STD_ROM_FN(dcmd);

struct BurnDriverD BurnDrvMDdcmd = {
	"g_dcmd", NULL, NULL, "1992",
	"Devil Crash MD (J) [!]\0", NULL, "Technosoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dcmdRomInfo, dcmdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Devil's Course 3-D Golf (J) [!]

static struct BurnRomInfo dc3dRomDesc[]={
	{ "g_dc3d.bin", 0x180000, 0xBD090C67, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dc3d);
STD_ROM_FN(dc3d);

struct BurnDriverD BurnDrvMDdc3d = {
	"g_dc3d", NULL, NULL, "1900",
	"Devil's Course 3-D Golf (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dc3dRomInfo, dc3dRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Double Dribble - The Playoff Edition (U) [!]

static struct BurnRomInfo dribRomDesc[]={
	{ "g_drib.bin", 0x200000, 0x8352B1D0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drib);
STD_ROM_FN(drib);

struct BurnDriverD BurnDrvMDdrib = {
	"g_drib", NULL, NULL, "1900",
	"Double Dribble - The Playoff Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dribRomInfo, dribRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon Ball Z - Buyuu Retsuden (J) [!]

static struct BurnRomInfo dbzjRomDesc[]={
	{ "g_dbzj.bin", 0x200000, 0xAF8F3371, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dbzj);
STD_ROM_FN(dbzj);

struct BurnDriverD BurnDrvMDdbzj = {
	"g_dbzj", NULL, NULL, "1900",
	"Dragon Ball Z - Buyuu Retsuden (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dbzjRomInfo, dbzjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon Ball Z - L'Appel du Destin (F) [!]

static struct BurnRomInfo dbzfRomDesc[]={
	{ "g_dbzf.bin", 0x200000, 0xF035C737, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dbzf);
STD_ROM_FN(dbzf);

struct BurnDriverD BurnDrvMDdbzf = {
	"g_dbzf", NULL, NULL, "1900",
	"Dragon Ball Z - L'Appel du Destin (F) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dbzfRomInfo, dbzfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon's Eye - Shanghai 3 (J) [!]

static struct BurnRomInfo deyeRomDesc[]={
	{ "g_deye.bin", 0x040000, 0x81F0C3CF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(deye);
STD_ROM_FN(deye);

struct BurnDriverD BurnDrvMDdeye = {
	"g_deye", NULL, NULL, "1900",
	"Dragon's Eye - Shanghai 3 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, deyeRomInfo, deyeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// EA Hockey (E) [!]

static struct BurnRomInfo eahoRomDesc[]={
	{ "g_eaho.bin", 0x080000, 0x9BFC279C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eaho);
STD_ROM_FN(eaho);

struct BurnDriver BurnDrvMDeaho = {
	"g_eaho", "g_nhlh", NULL, "1900",
	"EA Hockey (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eahoRomInfo, eahoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Exile (U) [!]

static struct BurnRomInfo exilRomDesc[]={
	{ "g_exil.bin", 0x100000, 0x1B569DC2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exil);
STD_ROM_FN(exil);

struct BurnDriverD BurnDrvMDexil = {
	"g_exil", NULL, NULL, "1900",
	"Exile (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exilRomInfo, exilRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 World Championship Edition (E) [!]

static struct BurnRomInfo f1cRomDesc[]={
	{ "g_f1c.bin", 0x080000, 0x5D30BEFB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1c);
STD_ROM_FN(f1c);

struct BurnDriverD BurnDrvMDf1c = {
	"g_f1c", NULL, NULL, "1900",
	"F1 World Championship Edition (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1cRomInfo, f1cRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 Grand Prix - Nakajima Satoru (J) [!]

static struct BurnRomInfo f1gpRomDesc[]={
	{ "g_f1gp.bin", 0x100000, 0x93BE47CF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1gp);
STD_ROM_FN(f1gp);

struct BurnDriverD BurnDrvMDf1gp = {
	"g_f1gp", NULL, NULL, "1900",
	"F1 Grand Prix - Nakajima Satoru (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1gpRomInfo, f1gpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 Hero MD (J) [c][!]

static struct BurnRomInfo f1hRomDesc[]={
	{ "g_f1h.bin", 0x100000, 0x24F87987, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1h);
STD_ROM_FN(f1h);

struct BurnDriverD BurnDrvMDf1h = {
	"g_f1h", NULL, NULL, "1900",
	"F1 Hero MD (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1hRomInfo, f1hRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 Super License - Nakajima Satoru (J) [!]

static struct BurnRomInfo f1slRomDesc[]={
	{ "g_f1sl.bin", 0x100000, 0x8774BC79, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1sl);
STD_ROM_FN(f1sl);

struct BurnDriverD BurnDrvMDf1sl = {
	"g_f1sl", NULL, NULL, "1900",
	"F1 Super License - Nakajima Satoru (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1slRomInfo, f1slRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 World Championship Edition (Beta)

static struct BurnRomInfo f1wcRomDesc[]={
	{ "g_f1wc.bin", 0x100000, 0xCCD73738, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1wc);
STD_ROM_FN(f1wc);

struct BurnDriverD BurnDrvMDf1wc = {
	"g_f1wc", NULL, NULL, "1900",
	"F1 World Championship Edition (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1wcRomInfo, f1wcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fastest 1 (J) [!]

static struct BurnRomInfo fas1RomDesc[]={
	{ "g_fas1.bin", 0x080000, 0xBB43F0DE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fas1);
STD_ROM_FN(fas1);

struct BurnDriverD BurnDrvMDfas1 = {
	"g_fas1", NULL, NULL, "1900",
	"Fastest 1 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fas1RomInfo, fas1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatman (J) [c][!]

static struct BurnRomInfo fatmRomDesc[]={
	{ "g_fatm.bin", 0x0A0000, 0x7867DA3A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fatm);
STD_ROM_FN(fatm);

struct BurnDriverD BurnDrvMDfatm = {
	"g_fatm", NULL, NULL, "1900",
	"Fatman (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fatmRomInfo, fatmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fighting Masters (U) [!]

static struct BurnRomInfo fmasRomDesc[]={
	{ "g_fmas.bin", 0x080000, 0x5F51983B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fmas);
STD_ROM_FN(fmas);

struct BurnDriverD BurnDrvMDfmas = {
	"g_fmas", NULL, NULL, "1900",
	"Fighting Masters (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fmasRomInfo, fmasRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Final Blow (J) [c][!]

static struct BurnRomInfo fbloRomDesc[]={
	{ "g_fblo.bin", 0x080000, 0x48AD505D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fblo);
STD_ROM_FN(fblo);

struct BurnDriverD BurnDrvMDfblo = {
	"g_fblo", NULL, NULL, "1900",
	"Final Blow (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fbloRomInfo, fbloRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fire Pro Wrestling Gaiden (J) [c][!]

static struct BurnRomInfo fproRomDesc[]={
	{ "g_fpro.bin", 0x080000, 0x24408C73, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fpro);
STD_ROM_FN(fpro);

struct BurnDriverD BurnDrvMDfpro = {
	"g_fpro", NULL, NULL, "1900",
	"Fire Pro Wrestling Gaiden (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fproRomInfo, fproRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fire Shark (U) [!]

static struct BurnRomInfo fshkRomDesc[]={
	{ "g_fshk.bin", 0x080000, 0x9C175146, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fshk);
STD_ROM_FN(fshk);

struct BurnDriverD BurnDrvMDfshk = {
	"g_fshk", NULL, NULL, "1900",
	"Fire Shark (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fshkRomInfo, fshkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Foreman For Real (W) [!]

static struct BurnRomInfo foreRomDesc[]={
	{ "g_fore.bin", 0x300000, 0x36248F90, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fore);
STD_ROM_FN(fore);

struct BurnDriverD BurnDrvMDfore = {
	"g_fore", NULL, NULL, "1900",
	"Foreman For Real (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, foreRomInfo, foreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Forgotten Worlds (W) (REV01) [!]

static struct BurnRomInfo fwRomDesc[]={
	{ "g_fw.bin", 0x080000, 0x95513985, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fw);
STD_ROM_FN(fw);

struct BurnDriverD BurnDrvMDfw = {
	"g_fw", NULL, NULL, "1900",
	"Forgotten Worlds (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fwRomInfo, fwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fun-N-Games (U) [c][!]

static struct BurnRomInfo fungRomDesc[]={
	{ "g_fung.bin", 0x100000, 0xB5AE351D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fung);
STD_ROM_FN(fung);

struct BurnDriverD BurnDrvMDfung = {
	"g_fung", NULL, NULL, "1900",
	"Fun-N-Games (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fungRomInfo, fungRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Genghis Khan II - Clan of the Gray Wolf (U) [!]

static struct BurnRomInfo gengRomDesc[]={
	{ "g_geng.bin", 0x100000, 0x87A281AE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(geng);
STD_ROM_FN(geng);

struct BurnDriverD BurnDrvMDgeng = {
	"g_geng", NULL, NULL, "1900",
	"Genghis Khan II - Clan of the Gray Wolf (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gengRomInfo, gengRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Great Waldo Searc

static struct BurnRomInfo gwsRomDesc[]={
	{ "g_gws.bin", 0x100000, 0x8C5C93B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gws);
STD_ROM_FN(gws);

struct BurnDriverD BurnDrvMDgws = {
	"g_gws", NULL, NULL, "1900",
	"Great Waldo Searc\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gwsRomInfo, gwsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hyper Dunk - The Playoff Edition (E) [!]

static struct BurnRomInfo hyduRomDesc[]={
	{ "g_hydu.bin", 0x200000, 0xF27C576A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hydu);
STD_ROM_FN(hydu);

struct BurnDriverD BurnDrvMDhydu = {
	"g_hydu", NULL, NULL, "1900",
	"Hyper Dunk - The Playoff Edition (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hyduRomInfo, hyduRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// IMG International Tour Tennis (UE) [!]

static struct BurnRomInfo imgiRomDesc[]={
	{ "g_imgi.bin", 0x200000, 0xE04FFC2B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(imgi);
STD_ROM_FN(imgi);

struct BurnDriverD BurnDrvMDimgi = {
	"g_imgi", NULL, NULL, "1900",
	"IMG International Tour Tennis (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, imgiRomInfo, imgiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Insector X (U) [!]

static struct BurnRomInfo insxRomDesc[]={
	{ "g_insx.bin", 0x080000, 0x70626304, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(insx);
STD_ROM_FN(insx);

struct BurnDriverD BurnDrvMDinsx = {
	"g_insx", NULL, NULL, "1900",
	"Insector X (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, insxRomInfo, insxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// International Rugby (E) [c][!]

static struct BurnRomInfo intrRomDesc[]={
	{ "g_intr.bin", 0x080000, 0xD97D1699, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(intr);
STD_ROM_FN(intr);

struct BurnDriverD BurnDrvMDintr = {
	"g_intr", NULL, NULL, "1900",
	"International Rugby (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, intrRomInfo, intrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ishido - The Way of the Stones (U) [c][!]

static struct BurnRomInfo ishiRomDesc[]={
	{ "g_ishi.bin", 0x020000, 0xB1DE7D5E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ishi);
STD_ROM_FN(ishi);

struct BurnDriverD BurnDrvMDishi = {
	"g_ishi", NULL, NULL, "1900",
	"Ishido - The Way of the Stones (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ishiRomInfo, ishiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Champion Soccer (J) [!]

static struct BurnRomInfo jlcsRomDesc[]={
	{ "g_jlcs.bin", 0x080000, 0x453C405E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlcs);
STD_ROM_FN(jlcs);

struct BurnDriverD BurnDrvMDjlcs = {
	"g_jlcs", "G_wts", NULL, "1900",
	"J. League Champion Soccer (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlcsRomInfo, jlcsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Pro Striker 2 (J) [!]

static struct BurnRomInfo jlp2RomDesc[]={
	{ "g_jlp2.bin", 0x200000, 0x9FE71002, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlp2);
STD_ROM_FN(jlp2);

struct BurnDriverD BurnDrvMDjlp2 = {
	"g_jlp2", NULL, NULL, "1900",
	"J. League Pro Striker 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlp2RomInfo, jlp2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Pro Striker - Perfect Edition (J) [c][!]

static struct BurnRomInfo jlppRomDesc[]={
	{ "g_jlpp.bin", 0x100000, 0x0ABED379, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlpp);
STD_ROM_FN(jlpp);

struct BurnDriverD BurnDrvMDjlpp = {
	"g_jlpp", NULL, NULL, "1900",
	"J. League Pro Striker - Perfect Edition (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlppRomInfo, jlppRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Pro Striker 2 (J) [!]

static struct BurnRomInfo jlpRomDesc[]={
	{ "g_jlp.bin", 0x100000, 0x2D5B7A11, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlp);
STD_ROM_FN(jlp);

struct BurnDriverD BurnDrvMDjlp = {
	"g_jlp", NULL, NULL, "1900",
	"J. League Pro Striker 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlpRomInfo, jlpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Pro Striker Final Stage (J) [c][!]

static struct BurnRomInfo jlpfRomDesc[]={
	{ "g_jlpf.bin", 0x200000, 0xE35E25FB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlpf);
STD_ROM_FN(jlpf);

struct BurnDriverD BurnDrvMDjlpf = {
	"g_jlpf", NULL, NULL, "1900",
	"J. League Pro Striker Final Stage (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlpfRomInfo, jlpfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Buster Douglas Knock Out Boxing (UE) [c][!]

static struct BurnRomInfo jbdbRomDesc[]={
	{ "g_jbdb.bin", 0x080000, 0x87BBCF2A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jbdb);
STD_ROM_FN(jbdb);

struct BurnDriverD BurnDrvMDjbdb = {
	"g_jbdb", NULL, NULL, "1900",
	"James Buster Douglas Knock Out Boxing (UE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jbdbRomInfo, jbdbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jammit (U) [!]

static struct BurnRomInfo jammRomDesc[]={
	{ "g_jamm.bin", 0x200000, 0xD91B52B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jamm);
STD_ROM_FN(jamm);

struct BurnDriverD BurnDrvMDjamm = {
	"g_jamm", NULL, NULL, "1900",
	"Jammit (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jammRomInfo, jammRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Janou Touryumon (J) [!]

static struct BurnRomInfo janoRomDesc[]={
	{ "g_jano.bin", 0x100000, 0x7011E8EB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jano);
STD_ROM_FN(jano);

struct BurnDriverD BurnDrvMDjano = {
	"g_jano", NULL, NULL, "1900",
	"Janou Touryumon (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, janoRomInfo, janoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jantei Monogatari (J) [!]

static struct BurnRomInfo jantRomDesc[]={
	{ "g_jant.bin", 0x100000, 0x8A1B19AD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jant);
STD_ROM_FN(jant);

struct BurnDriverD BurnDrvMDjant = {
	"g_jant", NULL, NULL, "1900",
	"Jantei Monogatari (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jantRomInfo, jantRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jeopardy! (U) [c][!]

static struct BurnRomInfo jeopRomDesc[]={
	{ "g_jeop.bin", 0x080000, 0x56CFF3F1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jeop);
STD_ROM_FN(jeop);

struct BurnDriverD BurnDrvMDjeop = {
	"g_jeop", NULL, NULL, "1900",
	"Jeopardy! (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jeopRomInfo, jeopRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jeopardy! Deluxe (U) [c][!]

static struct BurnRomInfo jeodRomDesc[]={
	{ "g_jeod.bin", 0x080000, 0x25E2F9D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jeod);
STD_ROM_FN(jeod);

struct BurnDriverD BurnDrvMDjeod = {
	"g_jeod", NULL, NULL, "1900",
	"Jeopardy! Deluxe (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jeodRomInfo, jeodRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jeopardy! Sports Edition (U) [!]

static struct BurnRomInfo jeosRomDesc[]={
	{ "g_jeos.bin", 0x080000, 0x13F924D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jeos);
STD_ROM_FN(jeos);

struct BurnDriverD BurnDrvMDjeos = {
	"g_jeos", NULL, NULL, "1900",
	"Jeopardy! Sports Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jeosRomInfo, jeosRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jerry Glanville's Pigskin Footbrawl (U) [!]

static struct BurnRomInfo jgpfRomDesc[]={
	{ "g_jgpf.bin", 0x100000, 0xE7F48D30, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jgpf);
STD_ROM_FN(jgpf);

struct BurnDriverD BurnDrvMDjgpf = {
	"g_jgpf", NULL, NULL, "1900",
	"Jerry Glanville's Pigskin Footbrawl (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jgpfRomInfo, jgpfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jewel Master (UE) [!]

static struct BurnRomInfo jewlRomDesc[]={
	{ "g_jewl.bin", 0x080000, 0xCEE98813, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jewl);
STD_ROM_FN(jewl);

struct BurnDriverD BurnDrvMDjewl = {
	"g_jewl", NULL, NULL, "1900",
	"Jewel Master (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jewlRomInfo, jewlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Joe & Mac Caveman Ninja (U) [!]

static struct BurnRomInfo jmacRomDesc[]={
	{ "g_jmac.bin", 0x100000, 0x85BCC1C7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jmac);
STD_ROM_FN(jmac);

struct BurnDriverD BurnDrvMDjmac = {
	"g_jmac", NULL, NULL, "1900",
	"Joe & Mac Caveman Ninja (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jmacRomInfo, jmacRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jordan vs Bird - Super One-on-One (UE) (REV01) [!]

static struct BurnRomInfo jb11RomDesc[]={
	{ "g_jb11.bin", 0x080000, 0x4D3DDD7C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jb11);
STD_ROM_FN(jb11);

struct BurnDriverD BurnDrvMDjb11 = {
	"g_jb11", NULL, NULL, "1900",
	"Jordan vs Bird - Super One-on-One (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jb11RomInfo, jb11RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kick Boxing, The (J) [!]

static struct BurnRomInfo kboxRomDesc[]={
	{ "g_kbox.bin", 0x100000, 0x9BDC230C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kbox);
STD_ROM_FN(kbox);

struct BurnDriver BurnDrvMDkbox = {
	"g_kbox", "g_botb", NULL, "1900",
	"Kick Boxing, The (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kboxRomInfo, kboxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King's Bounty (UE) [!]

static struct BurnRomInfo kbouRomDesc[]={
	{ "g_kbou.bin", 0x080000, 0xAA68A92E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kbou);
STD_ROM_FN(kbou);

struct BurnDriverD BurnDrvMDkbou = {
	"g_kbou", NULL, NULL, "1900",
	"King's Bounty (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kbouRomInfo, kbouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Last Battle (UE) [!]

static struct BurnRomInfo lbatRomDesc[]={
	{ "g_lbat.bin", 0x080000, 0xBBFAAD77, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lbat);
STD_ROM_FN(lbat);

struct BurnDriverD BurnDrvMDlbat = {
	"g_lbat", NULL, NULL, "1900",
	"Last Battle (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lbatRomInfo, lbatRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// LHX Attack Chopper (UE) [!]

static struct BurnRomInfo lhxRomDesc[]={
	{ "g_lhx.bin", 0x100000, 0x70C3428D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lhx);
STD_ROM_FN(lhx);

struct BurnDriverD BurnDrvMDlhx = {
	"g_lhx", NULL, NULL, "1900",
	"LHX Attack Chopper (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lhxRomInfo, lhxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Magic School Bu

static struct BurnRomInfo msbuRomDesc[]={
	{ "g_msbu.bin", 0x100000, 0x1A5D4412, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(msbu);
STD_ROM_FN(msbu);

struct BurnDriverD BurnDrvMDmsbu = {
	"g_msbu", NULL, NULL, "1900",
	"Magic School Bu\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, msbuRomInfo, msbuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mamono Hunter Yohko - Makai Kara no Tenkosei (J) [!]

static struct BurnRomInfo mhyRomDesc[]={
	{ "g_mhy.bin", 0x080000, 0x10BB359B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mhy);
STD_ROM_FN(mhy);

struct BurnDriverD BurnDrvMDmhy = {
	"g_mhy", NULL, NULL, "1900",
	"Mamono Hunter Yohko - Makai Kara no Tenkosei (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mhyRomInfo, mhyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marble Madness (UE) [!]

static struct BurnRomInfo mmadRomDesc[]={
	{ "g_mmad.bin", 0x080000, 0x79EBA28A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmad);
STD_ROM_FN(mmad);

struct BurnDriverD BurnDrvMDmmad = {
	"g_mmad", NULL, NULL, "1900",
	"Marble Madness (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmadRomInfo, mmadRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mario Lemieux Hockey (UE) [!]

static struct BurnRomInfo mlemRomDesc[]={
	{ "g_mlem.bin", 0x080000, 0xF664EB6C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlem);
STD_ROM_FN(mlem);

struct BurnDriverD BurnDrvMDmlem = {
	"g_mlem", NULL, NULL, "1900",
	"Mario Lemieux Hockey (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlemRomInfo, mlemRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Master of Weapon (J) [!]

static struct BurnRomInfo moweRomDesc[]={
	{ "g_mowe.bin", 0x080000, 0x12AD6178, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mowe);
STD_ROM_FN(mowe);

struct BurnDriverD BurnDrvMDmowe = {
	"g_mowe", NULL, NULL, "1900",
	"Master of Weapon (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, moweRomInfo, moweRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Math Blaster - Episode 1 (U) [!]

static struct BurnRomInfo mathRomDesc[]={
	{ "g_math.bin", 0x100000, 0xD055A462, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(math);
STD_ROM_FN(math);

struct BurnDriverD BurnDrvMDmath = {
	"g_math", NULL, NULL, "1900",
	"Math Blaster - Episode 1 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mathRomInfo, mathRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Lo Mania (E) (REV00) [c][!]

static struct BurnRomInfo mloRomDesc[]={
	{ "g_mlo.bin", 0x100000, 0x2148D56D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlo);
STD_ROM_FN(mlo);

struct BurnDriverD BurnDrvMDmlo = {
	"g_mlo", NULL, NULL, "1994",
	"Mega Lo Mania (E) (REV00) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mloRomInfo, mloRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Lo Mania (J) [!]

static struct BurnRomInfo mlojRomDesc[]={
	{ "g_mloj.bin", 0x100000, 0xA60D8619, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mloj);
STD_ROM_FN(mloj);

struct BurnDriverD BurnDrvMDmloj = {
	"g_mloj", NULL, NULL, "1994",
	"Mega Lo Mania (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlojRomInfo, mlojRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega SWIV (E)

static struct BurnRomInfo mswiRomDesc[]={
	{ "g_mswi.bin", 0x100000, 0x1EC66BF7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mswi);
STD_ROM_FN(mswi);

struct BurnDriverD BurnDrvMDmswi = {
	"g_mswi", NULL, NULL, "1900",
	"Mega SWIV (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mswiRomInfo, mswiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// MegaTraX (J) [c][!]

static struct BurnRomInfo mtrxRomDesc[]={
	{ "g_mtrx.bin", 0x080000, 0xA0837741, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mtrx);
STD_ROM_FN(mtrx);

struct BurnDriverD BurnDrvMDmtrx = {
	"g_mtrx", NULL, NULL, "1900",
	"MegaTraX (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mtrxRomInfo, mtrxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mercs (W) [!]

static struct BurnRomInfo mercRomDesc[]={
	{ "g_merc.bin", 0x100000, 0x16113A72, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(merc);
STD_ROM_FN(merc);

struct BurnDriverD BurnDrvMDmerc = {
	"g_merc", NULL, NULL, "1900",
	"Mercs (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mercRomInfo, mercRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey's Ultimate Challenge (U) [!]

static struct BurnRomInfo multRomDesc[]={
	{ "g_mult.bin", 0x100000, 0x30B512EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mult);
STD_ROM_FN(mult);

struct BurnDriverD BurnDrvMDmult = {
	"g_mult", NULL, NULL, "1900",
	"Mickey's Ultimate Challenge (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, multRomInfo, multRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Midnight Resistance (U) [!]

static struct BurnRomInfo midrRomDesc[]={
	{ "g_midr.bin", 0x100000, 0x187C6AF6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(midr);
STD_ROM_FN(midr);

struct BurnDriverD BurnDrvMDmidr = {
	"g_midr", NULL, NULL, "1900",
	"Midnight Resistance (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, midrRomInfo, midrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mig-29 Fighter Pilot (U) [!]

static struct BurnRomInfo m29RomDesc[]={
	{ "g_m29.bin", 0x100000, 0x59CCABB2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(m29);
STD_ROM_FN(m29);

struct BurnDriverD BurnDrvMDm29 = {
	"g_m29", NULL, NULL, "1900",
	"Mig-29 Fighter Pilot (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, m29RomInfo, m29RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Might and Magic - Gates to Another World (UE) (REV01) [!]

static struct BurnRomInfo mmgRomDesc[]={
	{ "g_mmg.bin", 0x0C0000, 0xF509145F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmg);
STD_ROM_FN(mmg);

struct BurnDriverD BurnDrvMDmmg = {
	"g_mmg", NULL, NULL, "1900",
	"Might and Magic - Gates to Another World (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmgRomInfo, mmgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mike Ditka Power Football (U) [!]

static struct BurnRomInfo mikeRomDesc[]={
	{ "g_mike.bin", 0x100000, 0x6078B310, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mike);
STD_ROM_FN(mike);

struct BurnDriverD BurnDrvMDmike = {
	"g_mike", NULL, NULL, "1900",
	"Mike Ditka Power Football (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mikeRomInfo, mikeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// MLBPA Baseball (U) [!]

static struct BurnRomInfo mlbbRomDesc[]={
	{ "g_mlbb.bin", 0x200000, 0x14A8064D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlbb);
STD_ROM_FN(mlbb);

struct BurnDriverD BurnDrvMDmlbb = {
	"g_mlbb", NULL, NULL, "1900",
	"MLBPA Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlbbRomInfo, mlbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// MLBPA Sports Talk Baseball (U) [!]

static struct BurnRomInfo mlbsRomDesc[]={
	{ "g_mlbs.bin", 0x100000, 0x0DEB79C2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlbs);
STD_ROM_FN(mlbs);

struct BurnDriverD BurnDrvMDmlbs = {
	"g_mlbs", NULL, NULL, "1900",
	"MLBPA Sports Talk Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlbsRomInfo, mlbsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Monopoly (U) [c][!]

static struct BurnRomInfo monoRomDesc[]={
	{ "g_mono.bin", 0x080000, 0xC10268DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mono);
STD_ROM_FN(mono);

struct BurnDriverD BurnDrvMDmono = {
	"g_mono", NULL, NULL, "1900",
	"Monopoly (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, monoRomInfo, monoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Muhammad Ali Heavyweight Boxing (U) [c][!]

static struct BurnRomInfo mahbRomDesc[]={
	{ "g_mahb.bin", 0x100000, 0xB638B6A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mahb);
STD_ROM_FN(mahb);

struct BurnDriverD BurnDrvMDmahb = {
	"g_mahb", NULL, NULL, "1900",
	"Muhammad Ali Heavyweight Boxing (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mahbRomInfo, mahbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mystic Defender (W) (REV01) [!]

static struct BurnRomInfo mysdRomDesc[]={
	{ "g_mysd.bin", 0x080000, 0x50FD5D93, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mysd);
STD_ROM_FN(mysd);

struct BurnDriverD BurnDrvMDmysd = {
	"g_mysd", NULL, NULL, "1900",
	"Mystic Defender (W) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mysdRomInfo, mysdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mystical Fighter (U) [c][!]

static struct BurnRomInfo mysfRomDesc[]={
	{ "g_mysf.bin", 0x080000, 0xB2F2A69B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mysf);
STD_ROM_FN(mysf);

struct BurnDriverD BurnDrvMDmysf = {
	"g_mysf", NULL, NULL, "1900",
	"Mystical Fighter (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mysfRomInfo, mysfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Newman-Haas IndyCar Racing (W) [!]

static struct BurnRomInfo nhirRomDesc[]={
	{ "g_nhir.bin", 0x200000, 0x1233A229, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nhir);
STD_ROM_FN(nhir);

struct BurnDriverD BurnDrvMDnhir = {
	"g_nhir", NULL, NULL, "1900",
	"Newman-Haas IndyCar Racing (W) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nhirRomInfo, nhirRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nobunaga's Ambition (U) [!]

static struct BurnRomInfo nobuRomDesc[]={
	{ "g_nobu.bin", 0x080000, 0xB9BC07BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nobu);
STD_ROM_FN(nobu);

struct BurnDriverD BurnDrvMDnobu = {
	"g_nobu", NULL, NULL, "1900",
	"Nobunaga's Ambition (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nobuRomInfo, nobuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Operation Europe - Path to Victory 1939-1945 (U) [!]

static struct BurnRomInfo opeuRomDesc[]={
	{ "g_opeu.bin", 0x100000, 0xE7CBA1D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(opeu);
STD_ROM_FN(opeu);

struct BurnDriverD BurnDrvMDopeu = {
	"g_opeu", NULL, NULL, "1900",
	"Operation Europe - Path to Victory 1939-1945 (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, opeuRomInfo, opeuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// P.T.O. Pacific Theater of Operations (U) [!]

static struct BurnRomInfo ptoRomDesc[]={
	{ "g_pto.bin", 0x100000, 0xD9D4C6E2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pto);
STD_ROM_FN(pto);

struct BurnDriverD BurnDrvMDpto = {
	"g_pto", NULL, NULL, "1900",
	"P.T.O. Pacific Theater of Operations (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ptoRomInfo, ptoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pebble Beach Golf Links (U) [!]

static struct BurnRomInfo pbglRomDesc[]={
	{ "g_pbgl.bin", 0x200000, 0x95823C43, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pbgl);
STD_ROM_FN(pbgl);

struct BurnDriverD BurnDrvMDpbgl = {
	"g_pbgl", NULL, NULL, "1900",
	"Pebble Beach Golf Links (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pbglRomInfo, pbglRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phelios (U) [c][!]

static struct BurnRomInfo phelRomDesc[]={
	{ "g_phel.bin", 0x080000, 0x11C79320, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(phel);
STD_ROM_FN(phel);

struct BurnDriverD BurnDrvMDphel = {
	"g_phel", NULL, NULL, "1900",
	"Phelios (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, phelRomInfo, phelRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Power Athlete (J) [!]

static struct BurnRomInfo pathRomDesc[]={
	{ "g_path.bin", 0x100000, 0xB41B77CF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(path);
STD_ROM_FN(path);

struct BurnDriverD BurnDrvMDpath = {
	"g_path", NULL, NULL, "1900",
	"Power Athlete (J) [!]\0", NULL, "Kaneko", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pathRomInfo, pathRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pro Hockey (J) [!]

static struct BurnRomInfo prhoRomDesc[]={
	{ "g_prho.bin", 0x080000, 0x9DCDC894, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(prho);
STD_ROM_FN(prho);

struct BurnDriver BurnDrvMDprho = {
	"g_prho", "g_nhlh", NULL, "1900",
	"Pro Hockey (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, prhoRomInfo, prhoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pro Quarterback (U) [c][!]

static struct BurnRomInfo prquRomDesc[]={
	{ "g_prqu.bin", 0x100000, 0xCC8B2B69, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(prqu);
STD_ROM_FN(prqu);

struct BurnDriverD BurnDrvMDprqu = {
	"g_prqu", NULL, NULL, "1900",
	"Pro Quarterback (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, prquRomInfo, prquRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rampart (U) [!]

static struct BurnRomInfo rampRomDesc[]={
	{ "g_ramp.bin", 0x080000, 0x9C4DD057, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ramp);
STD_ROM_FN(ramp);

struct BurnDriverD BurnDrvMDramp = {
	"g_ramp", NULL, NULL, "1900",
	"Rampart (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rampRomInfo, rampRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rastan Saga II (U) [!]

static struct BurnRomInfo rastRomDesc[]={
	{ "g_rast.bin", 0x080000, 0xC7EE8965, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rast);
STD_ROM_FN(rast);

struct BurnDriverD BurnDrvMDrast = {
	"g_rast", NULL, NULL, "1900",
	"Rastan Saga II (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rastRomInfo, rastRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Richard Scarry's Busytown (U) [!]

static struct BurnRomInfo rsbtRomDesc[]={
	{ "g_rsbt.bin", 0x200000, 0x7BB60C3F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rsbt);
STD_ROM_FN(rsbt);

struct BurnDriverD BurnDrvMDrsbt = {
	"g_rsbt", NULL, NULL, "1900",
	"Richard Scarry's Busytown (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rsbtRomInfo, rsbtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rockman Megaworld (J) [!]

static struct BurnRomInfo rmmwRomDesc[]={
	{ "g_rmmw.bin", 0x200000, 0x85C956EF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rmmw);
STD_ROM_FN(rmmw);

struct BurnDriverD BurnDrvMDrmmw = {
	"g_rmmw", NULL, NULL, "1900",
	"Rockman Megaworld (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rmmwRomInfo, rmmwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robot Wreckage (Beta)

static struct BurnRomInfo robwRomDesc[]={
	{ "g_robw.bin", 0x100000, 0xEF02D57B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robw);
STD_ROM_FN(robw);

struct BurnDriverD BurnDrvMDrobw = {
	"g_robw", NULL, NULL, "1993",
	"Robot Wreckage (Beta)\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robwRomInfo, robwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Romance of the Three Kingdoms II (U) [!]

static struct BurnRomInfo r3k2RomDesc[]={
	{ "g_r3k2.bin", 0x100000, 0x3D842478, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(r3k2);
STD_ROM_FN(r3k2);

struct BurnDriverD BurnDrvMDr3k2 = {
	"g_r3k2", NULL, NULL, "1900",
	"Romance of the Three Kingdoms II (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, r3k2RomInfo, r3k2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Romance of the Three Kingdoms III (U) [!]

static struct BurnRomInfo r3k3RomDesc[]={
	{ "g_r3k3.bin", 0x140000, 0x7E41C8FE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(r3k3);
STD_ROM_FN(r3k3);

struct BurnDriverD BurnDrvMDr3k3 = {
	"g_r3k3", NULL, NULL, "1900",
	"Romance of the Three Kingdoms III (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, r3k3RomInfo, r3k3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Saint Sword (U) [c][!]

static struct BurnRomInfo sswoRomDesc[]={
	{ "g_sswo.bin", 0x080000, 0x44F66BFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sswo);
STD_ROM_FN(sswo);

struct BurnDriverD BurnDrvMDsswo = {
	"g_sswo", NULL, NULL, "1900",
	"Saint Sword (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sswoRomInfo, sswoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sensible Soccer (E) (M4) [!]

static struct BurnRomInfo senRomDesc[]={
	{ "g_sen.bin", 0x080000, 0xF9B396B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sen);
STD_ROM_FN(sen);

struct BurnDriver BurnDrvMDsen = {
	"g_sen", "g_seni", NULL, "1993",
	"Sensible Soccer (E) (M4) [!]\0", NULL, "Sensible Software", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, senRomInfo, senRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadow Blasters (U) [c][!]

static struct BurnRomInfo sblsRomDesc[]={
	{ "g_sbls.bin", 0x080000, 0x713D377B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbls);
STD_ROM_FN(sbls);

struct BurnDriverD BurnDrvMDsbls = {
	"g_sbls", NULL, NULL, "1900",
	"Shadow Blasters (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sblsRomInfo, sblsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Slam Dunk - Shikyou Gekitotsu! (J) [!]

static struct BurnRomInfo sdnkRomDesc[]={
	{ "g_sdnk.bin", 0x200000, 0xCDF5678F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sdnk);
STD_ROM_FN(sdnk);

struct BurnDriverD BurnDrvMDsdnk = {
	"g_sdnk", NULL, NULL, "1900",
	"Slam Dunk - Shikyou Gekitotsu! (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sdnkRomInfo, sdnkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Slaughter Sport (U) [c][!]

static struct BurnRomInfo sspoRomDesc[]={
	{ "g_sspo.bin", 0x0A0000, 0xAF9F9D9C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sspo);
STD_ROM_FN(sspo);

struct BurnDriverD BurnDrvMDsspo = {
	"g_sspo", NULL, NULL, "1900",
	"Slaughter Sport (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sspoRomInfo, sspoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic and Knuckles & Sonic 1 (W) [!]

static struct BurnRomInfo sks1RomDesc[]={
	{ "g_sks1.bin", 0x280000, 0xE01F6ED5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sks1);
STD_ROM_FN(sks1);

struct BurnDriver BurnDrvMDsks1 = {
	"g_sks1", "g_snkn", NULL, "1994",
	"Sonic and Knuckles & Sonic 1 (W) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sks1RomInfo, sks1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Control (U) [c][!]

static struct BurnRomInfo sconRomDesc[]={
	{ "g_scon.bin", 0x180000, 0x8E2BCEAF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(scon);
STD_ROM_FN(scon);

struct BurnDriverD BurnDrvMDscon = {
	"g_scon", NULL, NULL, "1900",
	"Star Control (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sconRomInfo, sconRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Starflight (UE) (REV01) [!]

static struct BurnRomInfo sfliRomDesc[]={
	{ "g_sfli.bin", 0x100000, 0x1217DBEA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sfli);
STD_ROM_FN(sfli);

struct BurnDriverD BurnDrvMDsfli = {
	"g_sfli", NULL, NULL, "1900",
	"Starflight (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sfliRomInfo, sfliRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Smart (JU) [!]

static struct BurnRomInfo ssmaRomDesc[]={
	{ "g_ssma.bin", 0x080000, 0xB1DEDFAD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ssma);
STD_ROM_FN(ssma);

struct BurnDriverD BurnDrvMDssma = {
	"g_ssma", NULL, NULL, "1900",
	"Street Smart (JU) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ssmaRomInfo, ssmaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Summer Challenge (U) [!]

static struct BurnRomInfo sumcRomDesc[]={
	{ "g_sumc.bin", 0x200000, 0xD7D53DC1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sumc);
STD_ROM_FN(sumc);

struct BurnDriverD BurnDrvMDsumc = {
	"g_sumc", NULL, NULL, "1900",
	"Summer Challenge (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sumcRomInfo, sumcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Hydlide (U) [!]

static struct BurnRomInfo shydRomDesc[]={
	{ "g_shyd.bin", 0x080000, 0x1335DDAA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shyd);
STD_ROM_FN(shyd);

struct BurnDriverD BurnDrvMDshyd = {
	"g_shyd", NULL, NULL, "1900",
	"Super Hydlide (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shydRomInfo, shydRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super League (E)

static struct BurnRomInfo slRomDesc[]={
	{ "g_sl.bin", 0x080000, 0xEA13CB1D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sl);
STD_ROM_FN(sl);

struct BurnDriverD BurnDrvMDsl = {
	"g_sl", NULL, NULL, "1900",
	"Super League (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, slRomInfo, slRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super League 91 (J) [!]

static struct BurnRomInfo sl91RomDesc[]={
	{ "g_sl91.bin", 0x080000, 0xA948AB7E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sl91);
STD_ROM_FN(sl91);

struct BurnDriverD BurnDrvMDsl91 = {
	"g_sl91", NULL, NULL, "1900",
	"Super League 91 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sl91RomInfo, sl91RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Masters Golf (J) [!]

static struct BurnRomInfo smasRomDesc[]={
	{ "g_smas.bin", 0x080000, 0x088BA825, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smas);
STD_ROM_FN(smas);

struct BurnDriverD BurnDrvMDsmas = {
	"g_smas", NULL, NULL, "1900",
	"Super Masters Golf (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smasRomInfo, smasRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Superman (U) [!]

static struct BurnRomInfo supmRomDesc[]={
	{ "g_supm.bin", 0x100000, 0x543A5869, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(supm);
STD_ROM_FN(supm);

struct BurnDriverD BurnDrvMDsupm = {
	"g_supm", NULL, NULL, "1900",
	"Superman (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, supmRomInfo, supmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sword of Sodan (UE) [!]

static struct BurnRomInfo swsoRomDesc[]={
	{ "g_swso.bin", 0x080000, 0x9CB8468F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(swso);
STD_ROM_FN(swso);

struct BurnDriverD BurnDrvMDswso = {
	"g_swso", NULL, NULL, "1900",
	"Sword of Sodan (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, swsoRomInfo, swsoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sword of Vermilion (UE) [!]

static struct BurnRomInfo swveRomDesc[]={
	{ "g_swve.bin", 0x0A0000, 0xEA1BC9AB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(swve);
STD_ROM_FN(swve);

struct BurnDriverD BurnDrvMDswve = {
	"g_swve", NULL, NULL, "1900",
	"Sword of Vermilion (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, swveRomInfo, swveRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Team USA Basketball (UE) [c][!]

static struct BurnRomInfo tusaRomDesc[]={
	{ "g_tusa.bin", 0x100000, 0xA0CAF97E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tusa);
STD_ROM_FN(tusa);

struct BurnDriverD BurnDrvMDtusa = {
	"g_tusa", NULL, NULL, "1900",
	"Team USA Basketball (UE) [c][!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tusaRomInfo, tusaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Techno Clash (UE) [!]

static struct BurnRomInfo tclsRomDesc[]={
	{ "g_tcls.bin", 0x100000, 0x4E65E483, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tcls);
STD_ROM_FN(tcls);

struct BurnDriverD BurnDrvMDtcls = {
	"g_tcls", NULL, NULL, "1900",
	"Techno Clash (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tclsRomInfo, tclsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Technocop (U) [!]

static struct BurnRomInfo tcopRomDesc[]={
	{ "g_tcop.bin", 0x080000, 0x7459AD06, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tcop);
STD_ROM_FN(tcop);

struct BurnDriverD BurnDrvMDtcop = {
	"g_tcop", NULL, NULL, "1900",
	"Technocop (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tcopRomInfo, tcopRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Techno Clash (UE) [!]

static struct BurnRomInfo tcRomDesc[]={
	{ "g_tc.bin", 0x080000, 0xE889E218, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tc);
STD_ROM_FN(tc);

struct BurnDriverD BurnDrvMDtc = {
	"g_tc", NULL, NULL, "1900",
	"Techno Clash (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tcRomInfo, tcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Baseball (U) [!]

static struct BurnRomInfo tsbRomDesc[]={
	{ "g_tsb.bin", 0x100000, 0x227A1178, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsb);
STD_ROM_FN(tsb);

struct BurnDriverD BurnDrvMDtsb = {
	"g_tsb", NULL, NULL, "1900",
	"Tecmo Super Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsbRomInfo, tsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl (U) (Oct 1993) [!]

static struct BurnRomInfo tsbwRomDesc[]={
	{ "g_tsbw.bin", 0x100000, 0x21F27D34, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsbw);
STD_ROM_FN(tsbw);

struct BurnDriverD BurnDrvMDtsbw = {
	"g_tsbw", NULL, NULL, "1900",
	"Tecmo Super Bowl (U) (Oct 1993) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsbwRomInfo, tsbwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl II SE (U) [!]

static struct BurnRomInfo tbw2RomDesc[]={
	{ "g_tbw2.bin", 0x200000, 0x0A0E67D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tbw2);
STD_ROM_FN(tbw2);

struct BurnDriverD BurnDrvMDtbw2 = {
	"g_tbw2", NULL, NULL, "1900",
	"Tecmo Super Bowl II SE (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tbw2RomInfo, tbw2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl III Final Edition (U) [!]

static struct BurnRomInfo tbw3RomDesc[]={
	{ "g_tbw3.bin", 0x200000, 0xAAE4089F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tbw3);
STD_ROM_FN(tbw3);

struct BurnDriverD BurnDrvMDtbw3 = {
	"g_tbw3", NULL, NULL, "1900",
	"Tecmo Super Bowl III Final Edition (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tbw3RomInfo, tbw3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Trouble Shooter (U) [!]

static struct BurnRomInfo tshRomDesc[]={
	{ "g_tsh.bin", 0x100000, 0x5F86DDC9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsh);
STD_ROM_FN(tsh);

struct BurnDriverD BurnDrvMDtsh = {
	"g_tsh", NULL, NULL, "1900",
	"Trouble Shooter (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tshRomInfo, tshRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super NBA Basketball (U) [!]

static struct BurnRomInfo tsnbRomDesc[]={
	{ "g_tsnb.bin", 0x100000, 0x53913991, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsnb);
STD_ROM_FN(tsnb);

struct BurnDriverD BurnDrvMDtsnb = {
	"g_tsnb", NULL, NULL, "1900",
	"Tecmo Super NBA Basketball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsnbRomInfo, tsnbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo World Cup '92 (J) [!]

static struct BurnRomInfo tw92RomDesc[]={
	{ "g_tw92.bin", 0x040000, 0x5E93C8B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tw92);
STD_ROM_FN(tw92);

struct BurnDriverD BurnDrvMDtw92 = {
	"g_tw92", NULL, NULL, "1900",
	"Tecmo World Cup '92 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tw92RomInfo, tw92RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo World Cup '93 (U) [!]

static struct BurnRomInfo tw93RomDesc[]={
	{ "g_tw93.bin", 0x040000, 0xCAF8EB2C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tw93);
STD_ROM_FN(tw93);

struct BurnDriverD BurnDrvMDtw93 = {
	"g_tw93", NULL, NULL, "1900",
	"Tecmo World Cup '93 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tw93RomInfo, tw93RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thomas the Tank Engine & Friends (U) [c][!]

static struct BurnRomInfo ttnkRomDesc[]={
	{ "g_ttnk.bin", 0x100000, 0x1A406299, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ttnk);
STD_ROM_FN(ttnk);

struct BurnDriverD BurnDrvMDttnk = {
	"g_ttnk", NULL, NULL, "1900",
	"Thomas the Tank Engine & Friends (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ttnkRomInfo, ttnkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tommy Lasorda Baseball (U) [!]

static struct BurnRomInfo tlbbRomDesc[]={
	{ "g_tlbb.bin", 0x080000, 0x4FB50304, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tlbb);
STD_ROM_FN(tlbb);

struct BurnDriverD BurnDrvMDtlbb = {
	"g_tlbb", NULL, NULL, "1900",
	"Tommy Lasorda Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tlbbRomInfo, tlbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tony La Russa Baseball 95 (U) [!]

static struct BurnRomInfo tr95RomDesc[]={
	{ "g_tr95.bin", 0x200000, 0x3F848A92, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tr95);
STD_ROM_FN(tr95);

struct BurnDriverD BurnDrvMDtr95 = {
	"g_tr95", NULL, NULL, "1900",
	"Tony La Russa Baseball 95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tr95RomInfo, tr95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tony La Russa Baseball (U) [!]

static struct BurnRomInfo trbbRomDesc[]={
	{ "g_trbb.bin", 0x100000, 0x24629C78, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(trbb);
STD_ROM_FN(trbb);

struct BurnDriverD BurnDrvMDtrbb = {
	"g_trbb", NULL, NULL, "1900",
	"Tony La Russa Baseball (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, trbbRomInfo, trbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Total Football (E) [!]

static struct BurnRomInfo totfRomDesc[]={
	{ "g_totf.bin", 0x200000, 0x8360B66A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(totf);
STD_ROM_FN(totf);

struct BurnDriverD BurnDrvMDtotf = {
	"g_totf", NULL, NULL, "1900",
	"Total Football (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, totfRomInfo, totfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toxic Crusaders (U) [!]

static struct BurnRomInfo toxiRomDesc[]={
	{ "g_toxi.bin", 0x080000, 0x11FD46CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toxi);
STD_ROM_FN(toxi);

struct BurnDriverD BurnDrvMDtoxi = {
	"g_toxi", NULL, NULL, "1900",
	"Toxic Crusaders (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toxiRomInfo, toxiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Troy Aikman NFL Football (U) [!]

static struct BurnRomInfo tanfRomDesc[]={
	{ "g_tanf.bin", 0x200000, 0x015F2713, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tanf);
STD_ROM_FN(tanf);

struct BurnDriverD BurnDrvMDtanf = {
	"g_tanf", NULL, NULL, "1900",
	"Troy Aikman NFL Football (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tanfRomInfo, tanfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ultraman (J) [!]

static struct BurnRomInfo umanRomDesc[]={
	{ "g_uman.bin", 0x080000, 0x83B4D5FB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uman);
STD_ROM_FN(uman);

struct BurnDriverD BurnDrvMDuman = {
	"g_uman", NULL, NULL, "1900",
	"Ultraman (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, umanRomInfo, umanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Unnecessary Roughness 95 (U) [!]

static struct BurnRomInfo ur95RomDesc[]={
	{ "g_ur95.bin", 0x200000, 0x9920E7B7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ur95);
STD_ROM_FN(ur95);

struct BurnDriverD BurnDrvMDur95 = {
	"g_ur95", NULL, NULL, "1900",
	"Unnecessary Roughness 95 (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ur95RomInfo, ur95RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vapor Trail (U) [!]

static struct BurnRomInfo vaptRomDesc[]={
	{ "g_vapt.bin", 0x100000, 0xC49E3A0A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vapt);
STD_ROM_FN(vapt);

struct BurnDriverD BurnDrvMDvapt = {
	"g_vapt", NULL, NULL, "1900",
	"Vapor Trail (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vaptRomInfo, vaptRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// V-Five (J) [!]

static struct BurnRomInfo v5RomDesc[]={
	{ "g_v5.bin", 0x100000, 0xAD9D0EC0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(v5);
STD_ROM_FN(v5);

struct BurnDriverD BurnDrvMDv5 = {
	"g_v5", NULL, NULL, "1900",
	"V-Five (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, v5RomInfo, v5RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Volfied (J) [!]

static struct BurnRomInfo volfRomDesc[]={
	{ "g_volf.bin", 0x040000, 0xB0C5E3F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(volf);
STD_ROM_FN(volf);

struct BurnDriverD BurnDrvMDvolf = {
	"g_volf", NULL, NULL, "1900",
	"Volfied (J) [!]\0", NULL, "Taito", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, volfRomInfo, volfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wacky Worlds (U) [!]

static struct BurnRomInfo wackRomDesc[]={
	{ "g_wack.bin", 0x100000, 0x8AF4552D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wack);
STD_ROM_FN(wack);

struct BurnDriverD BurnDrvMDwack = {
	"g_wack", NULL, NULL, "1900",
	"Wacky Worlds (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wackRomInfo, wackRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warlock (UE) [!]

static struct BurnRomInfo wlocRomDesc[]={
	{ "g_wloc.bin", 0x200000, 0x0A46539B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wloc);
STD_ROM_FN(wloc);

struct BurnDriverD BurnDrvMDwloc = {
	"g_wloc", NULL, NULL, "1994",
	"Warlock (UE) [!]\0", NULL, "Trimark / Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wlocRomInfo, wlocRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warrior of Rome (U) [!]

static struct BurnRomInfo wromRomDesc[]={
	{ "g_wrom.bin", 0x100000, 0x5BE10C6A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wrom);
STD_ROM_FN(wrom);

struct BurnDriverD BurnDrvMDwrom = {
	"g_wrom", NULL, NULL, "1991",
	"Warrior of Rome (U) [!]\0", NULL, "Micronet", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wromRomInfo, wromRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warsong (U) [!]

static struct BurnRomInfo warsRomDesc[]={
	{ "g_wars.bin", 0x080000, 0x4B680285, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wars);
STD_ROM_FN(wars);

struct BurnDriverD BurnDrvMDwars = {
	"g_wars", NULL, NULL, "1900",
	"Warsong (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, warsRomInfo, warsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wayne Gretzsky NHLPA All-Stars (UE) [!]

static struct BurnRomInfo wgasRomDesc[]={
	{ "g_wgas.bin", 0x200000, 0xC2C13B81, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wgas);
STD_ROM_FN(wgas);

struct BurnDriverD BurnDrvMDwgas = {
	"g_wgas", NULL, NULL, "1900",
	"Wayne Gretzsky NHLPA All-Stars (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wgasRomInfo, wgasRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wheel of Fortune (U) [!]

static struct BurnRomInfo wforRomDesc[]={
	{ "g_wfor.bin", 0x080000, 0xC8D8EFC3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wfor);
STD_ROM_FN(wfor);

struct BurnDriverD BurnDrvMDwfor = {
	"g_wfor", NULL, NULL, "1900",
	"Wheel of Fortune (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wforRomInfo, wforRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Winter Challenge (UE) [!]

static struct BurnRomInfo wincRomDesc[]={
	{ "g_winc.bin", 0x100000, 0xF57C7068, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(winc);
STD_ROM_FN(winc);

struct BurnDriverD BurnDrvMDwinc = {
	"g_winc", NULL, NULL, "1900",
	"Winter Challenge (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wincRomInfo, wincRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wonder Boy III - Monster Lair (JE) [c][!]

static struct BurnRomInfo wb3RomDesc[]={
	{ "g_wb3.bin", 0x080000, 0xC24BC5E4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wb3);
STD_ROM_FN(wb3);

struct BurnDriverD BurnDrvMDwb3 = {
	"g_wb3", NULL, NULL, "1900",
	"Wonder Boy III - Monster Lair (JE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wb3RomInfo, wb3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wonder Boy in Monster World (UE) [!]

static struct BurnRomInfo wbmwRomDesc[]={
	{ "g_wbmw.bin", 0x0C0000, 0x1592F5B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wbmw);
STD_ROM_FN(wbmw);

struct BurnDriverD BurnDrvMDwbmw = {
	"g_wbmw", NULL, NULL, "1900",
	"Wonder Boy in Monster World (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wbmwRomInfo, wbmwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Class Leaderboard Golf (U) [c][!]

static struct BurnRomInfo wclRomDesc[]={
	{ "g_wcl.bin", 0x080000, 0x53434BAB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcl);
STD_ROM_FN(wcl);

struct BurnDriverD BurnDrvMDwcl = {
	"g_wcl", NULL, NULL, "1900",
	"World Class Leaderboard Golf (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wclRomInfo, wclRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Championship Soccer (JU) (REV03) [!]

static struct BurnRomInfo wcsRomDesc[]={
	{ "g_wcs.bin", 0x040000, 0xBF272BCB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcs);
STD_ROM_FN(wcs);

struct BurnDriverD BurnDrvMDwcs = {
	"g_wcs", NULL, NULL, "1994",
	"World Championship Soccer (JU) (REV03) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wcsRomInfo, wcsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Cup Italia 90 (E) [!]

static struct BurnRomInfo wc90RomDesc[]={
	{ "g_wc90.bin", 0x040000, 0xDD95F829, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wc90);
STD_ROM_FN(wc90);

struct BurnDriverD BurnDrvMDwc90 = {
	"g_wc90", NULL, NULL, "1994",
	"World Cup Italia 90 (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wc90RomInfo, wc90RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Cup USA 94 (UE) [!]

static struct BurnRomInfo wc94RomDesc[]={
	{ "g_wc94.bin", 0x100000, 0x0171B47F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wc94);
STD_ROM_FN(wc94);

struct BurnDriverD BurnDrvMDwc94 = {
	"g_wc94", NULL, NULL, "1900",
	"World Cup USA 94 (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wc94RomInfo, wc94RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wrestle War (JE) [c][!]

static struct BurnRomInfo wwarRomDesc[]={
	{ "g_wwar.bin", 0x080000, 0x2D162A85, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wwar);
STD_ROM_FN(wwar);

struct BurnDriverD BurnDrvMDwwar = {
	"g_wwar", NULL, NULL, "1900",
	"Wrestle War (JE) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wwarRomInfo, wwarRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Champions World Class Soccer (W) (M4) [!]

static struct BurnRomInfo cwcsRomDesc[]={
	{ "g_cwcs.bin", 0x100000, 0x883E33DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cwcs);
STD_ROM_FN(cwcs);

struct BurnDriverD BurnDrvMDcwcs = {
	"g_cwcs", NULL, NULL, "1900",
	"Champions World Class Soccer (W) (M4) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cwcsRomInfo, cwcsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Championship Bowling (U) [!]

static struct BurnRomInfo cbwlRomDesc[]={
	{ "g_cbwl.bin", 0x080000, 0x1BF92520, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cbwl);
STD_ROM_FN(cbwl);

struct BurnDriverD BurnDrvMDcbwl = {
	"g_cbwl", NULL, NULL, "1900",
	"Championship Bowling (U) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cbwlRomInfo, cbwlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Championship Pro-Am (U) [c][!]

static struct BurnRomInfo cpamRomDesc[]={
	{ "g_cpam.bin", 0x040000, 0xB496DE28, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cpam);
STD_ROM_FN(cpam);

struct BurnDriverD BurnDrvMDcpam = {
	"g_cpam", NULL, NULL, "1900",
	"Championship Pro-Am (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cpamRomInfo, cpamRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Centurion - Defender of Rome (UE) [!]

static struct BurnRomInfo cdorRomDesc[]={
	{ "g_cdor.bin", 0x0C0000, 0x21283B14, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cdor);
STD_ROM_FN(cdor);

struct BurnDriverD BurnDrvMDcdor = {
	"g_cdor", NULL, NULL, "1900",
	"Centurion - Defender of Rome (UE) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cdorRomInfo, cdorRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chameleon Kid (J) [!]

static struct BurnRomInfo ckidRomDesc[]={
	{ "g_ckid.bin", 0x100000, 0x50217C80, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ckid);
STD_ROM_FN(ckid);

struct BurnDriverD BurnDrvMDckid = {
	"g_ckid", NULL, NULL, "1994",
	"Chameleon Kid (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ckidRomInfo, ckidRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chiki Chiki Boys (UE) [!]

static struct BurnRomInfo chiRomDesc[]={
	{ "g_chi.bin", 0x100000, 0x9C3973A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chi);
STD_ROM_FN(chi);

struct BurnDriverD BurnDrvMDchi = {
	"g_chi", NULL, NULL, "1900",
	"Chiki Chiki Boys (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chiRomInfo, chiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Battle Golfer Yui (J) [c][!]

static struct BurnRomInfo bglfRomDesc[]={
	{ "g_bglf.bin", 0x080000, 0x4AA03E4E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bglf);
STD_ROM_FN(bglf);

struct BurnDriverD BurnDrvMDbglf = {
	"g_bglf", NULL, NULL, "1900",
	"Battle Golfer Yui (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bglfRomInfo, bglfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bahamut Senki (J) [c][!]

static struct BurnRomInfo bahaRomDesc[]={
	{ "g_baha.bin", 0x080000, 0xB1E268DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(baha);
STD_ROM_FN(baha);

struct BurnDriverD BurnDrvMDbaha = {
	"g_baha", NULL, NULL, "1900",
	"Bahamut Senki (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bahaRomInfo, bahaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Another World (E) [!]

static struct BurnRomInfo awldRomDesc[]={
	{ "g_awld.bin", 0x100000, 0xE9742041, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(awld);
STD_ROM_FN(awld);

struct BurnDriver BurnDrvMDawld = {
	"g_awld", "g_ootw", NULL, "1992",
	"Another World (E) [!]\0", NULL, "Delphine / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, awldRomInfo, awldRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Air Management - Oozora ni Kakeru (J) [c][!]

static struct BurnRomInfo airmRomDesc[]={
	{ "g_airm.bin", 0x100000, 0xB3DB0C71, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(airm);
STD_ROM_FN(airm);

struct BurnDriver BurnDrvMDairm = {
	"g_airm", "g_aero", NULL, "199?",
	"Air Management - Oozora ni Kakeru (J) [c][!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, airmRomInfo, airmRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Air Management II - Kouku Ou wo Mezase (J) [!]

static struct BurnRomInfo airm2RomDesc[]={
	{ "g_airm2.bin", 0x100000, 0x4582817B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(airm2);
STD_ROM_FN(airm2);

struct BurnDriver BurnDrvMDairm2 = {
	"g_airm2", "g_abz2", NULL, "1994",
	"Air Management II - Kouku Ou wo Mezase (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, airm2RomInfo, airm2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aoki Ookami to Shiroki Meshika - Genchou Hishi (J) [!]

static struct BurnRomInfo aokiRomDesc[]={
	{ "g_aoki.bin", 0x140000, 0x10BE1D93, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aoki);
STD_ROM_FN(aoki);

struct BurnDriverD BurnDrvMDaoki = {
	"g_aoki", NULL, NULL, "1900",
	"Aoki Ookami to Shiroki Meshika - Genchou Hishi (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aokiRomInfo, aokiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Advanced Daisenryaku (J) (REV01) [!]

static struct BurnRomInfo advdaiRomDesc[]={
	{ "g_advdai.bin", 0x100000, 0xE0D5E18A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(advdai);
STD_ROM_FN(advdai);

struct BurnDriverD BurnDrvMDadvdai = {
	"g_advdai", NULL, NULL, "1900",
	"Advanced Daisenryaku (J) (REV01) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, advdaiRomInfo, advdaiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blue Almanac (J) [!]

static struct BurnRomInfo bluealRomDesc[]={
	{ "g_blueal.bin", 0x100000, 0x7222EBB3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blueal);
STD_ROM_FN(blueal);

struct BurnDriverD BurnDrvMDblueal = {
	"g_blueal", NULL, NULL, "1900",
	"Blue Almanac (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bluealRomInfo, bluealRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chavez II (U) [!]

static struct BurnRomInfo chav2RomDesc[]={
	{ "g_chav2.bin", 0x100000, 0x5BC0DBB8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chav2);
STD_ROM_FN(chav2);

struct BurnDriverD BurnDrvMDchav2 = {
	"g_chav2", "g_boxl", NULL, "1900",
	"Chavez II (U) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chav2RomInfo, chav2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chibi Maruko-Chan - Wakuwaku Shopping (J) [c][!]

static struct BurnRomInfo chibiRomDesc[]={
	{ "g_chibi.bin", 0x080000, 0x91A144B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chibi);
STD_ROM_FN(chibi);

struct BurnDriverD BurnDrvMDchibi = {
	"g_chibi", NULL, NULL, "1900",
	"Chibi Maruko-Chan - Wakuwaku Shopping (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chibiRomInfo, chibiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crayon Shin-Chan - Arashi o Yobu Sono Ko (J) [!]

static struct BurnRomInfo crayonRomDesc[]={
	{ "g_crayon.bin", 0x200000, 0x97FC42D2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crayon);
STD_ROM_FN(crayon);

struct BurnDriverD BurnDrvMDcrayon = {
	"g_crayon", NULL, NULL, "1900",
	"Crayon Shin-Chan - Arashi o Yobu Sono Ko (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crayonRomInfo, crayonRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dai Konsen (J) [!]

static struct BurnRomInfo konsenRomDesc[]={
	{ "g_konsen.bin", 0x100000, 0x05CC7369, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(konsen);
STD_ROM_FN(konsen);

struct BurnDriverD BurnDrvMDkonsen = {
	"g_konsen", NULL, NULL, "1900",
	"Dai Konsen (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, konsenRomInfo, konsenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dahna - Megami Tanjou (J) [!]

static struct BurnRomInfo dahnaRomDesc[]={
	{ "g_dahna.bin", 0x100000, 0x4602584F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dahna);
STD_ROM_FN(dahna);

struct BurnDriverD BurnDrvMDdahna = {
	"g_dahna", NULL, NULL, "1991",
	"Dahna - Megami Tanjou (J) [!]\0", NULL, "IGS", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dahnaRomInfo, dahnaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daikoukai Jidai (J) [c][!]

static struct BurnRomInfo daikouRomDesc[]={
	{ "g_daikou.bin", 0x100000, 0x5A652458, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daikou);
STD_ROM_FN(daikou);

struct BurnDriverD BurnDrvMDdaikou = {
	"g_daikou", NULL, NULL, "1900",
	"Daikoukai Jidai (J) [c][!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daikouRomInfo, daikouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Disney Collection - Castle of Illusion & Quack Shot (E) [!]

static struct BurnRomInfo discolRomDesc[]={
	{ "g_discol.bin", 0x100000, 0xADFDE883, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(discol);
STD_ROM_FN(discol);

struct BurnDriverD BurnDrvMDdiscol = {
	"g_discol", NULL, NULL, "1991",
	"Disney Collection - Castle of Illusion & Quack Shot (E) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, discolRomInfo, discolRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon Slayer - The Legend of Heroes (J) [!]

static struct BurnRomInfo dslayRomDesc[]={
	{ "g_dslay.bin", 0x200000, 0x01BC1604, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dslay);
STD_ROM_FN(dslay);

struct BurnDriverD BurnDrvMDdslay = {
	"g_dslay", NULL, NULL, "1994",
	"Dragon Slayer - The Legend of Heroes (J) [!]\0", NULL, "Sega / Falcom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dslayRomInfo, dslayRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon Slayer II - The Legend of Heroes (J) [!]

static struct BurnRomInfo dslay2RomDesc[]={
	{ "g_dslay2.bin", 0x200000, 0x46924DC3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dslay2);
STD_ROM_FN(dslay2);

struct BurnDriverD BurnDrvMDdslay2 = {
	"g_dslay2", NULL, NULL, "1994",
	"Dragon Slayer II - The Legend of Heroes (J) [!]\0", NULL, "Sega / Falcom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dslay2RomInfo, dslay2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Draxos (J) [!]

static struct BurnRomInfo draxosRomDesc[]={
	{ "g_draxos.bin", 0x100000, 0x1EA07AF2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(draxos);
STD_ROM_FN(draxos);

struct BurnDriverD BurnDrvMDdraxos = {
	"g_draxos", NULL, NULL, "1900",
	"Draxos (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, draxosRomInfo, draxosRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// EA Sports Double Header (E) [!]

static struct BurnRomInfo eadoubRomDesc[]={
	{ "g_eadoub.bin", 0x100000, 0xA0B54CBC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eadoub);
STD_ROM_FN(eadoub);

struct BurnDriverD BurnDrvMDeadoub = {
	"g_eadoub", NULL, NULL, "1900",
	"EA Sports Double Header (E) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eadoubRomInfo, eadoubRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Europa Sensen (J) [!]

static struct BurnRomInfo europaRomDesc[]={
	{ "g_europa.bin", 0x100000, 0xB0416C60, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(europa);
STD_ROM_FN(europa);

struct BurnDriverD BurnDrvMDeuropa = {
	"g_europa", NULL, NULL, "1900",
	"Europa Sensen (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, europaRomInfo, europaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ex-Ranza (J) [!]

static struct BurnRomInfo exranzRomDesc[]={
	{ "g_exranz.bin", 0x100000, 0x349BB68D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exranz);
STD_ROM_FN(exranz);

struct BurnDriverD BurnDrvMDexranz = {
	"g_exranz", NULL, NULL, "1993",
	"Ex-Ranza (J) [!]\0", NULL, "Sega / Gau", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exranzRomInfo, exranzRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fushigi no Umi no Nadia (J) [c][!]

static struct BurnRomInfo fushigRomDesc[]={
	{ "g_fushig.bin", 0x100000, 0x4762062A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fushig);
STD_ROM_FN(fushig);

struct BurnDriverD BurnDrvMDfushig = {
	"g_fushig", NULL, NULL, "1900",
	"Fushigi no Umi no Nadia (J) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fushigRomInfo, fushigRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Frank Thomas Big Hurt Baseball (UE) [!]

static struct BurnRomInfo ftbhbRomDesc[]={
	{ "g_ftbhb.bin", 0x400000, 0x863E0950, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ftbhb);
STD_ROM_FN(ftbhb);

struct BurnDriverD BurnDrvMDftbhb = {
	"g_ftbhb", NULL, NULL, "1900",
	"Frank Thomas Big Hurt Baseball (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ftbhbRomInfo, ftbhbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Game no Kanzume Otokuyou (J) [!]

static struct BurnRomInfo gamenoRomDesc[]={
	{ "g_gameno.bin", 0x300000, 0xCDAD7E6B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gameno);
STD_ROM_FN(gameno);

struct BurnDriverD BurnDrvMDgameno = {
	"g_gameno", NULL, NULL, "1994",
	"Game no Kanzume Otokuyou (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gamenoRomInfo, gamenoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// GemFire (U) [!]

static struct BurnRomInfo gemfiRomDesc[]={
	{ "g_gemfi.bin", 0x100000, 0x3D36135B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gemfi);
STD_ROM_FN(gemfi);

struct BurnDriverD BurnDrvMDgemfi = {
	"g_gemfi", NULL, NULL, "1900",
	"GemFire (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gemfiRomInfo, gemfiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gauntlet (J) [!]

static struct BurnRomInfo gauntRomDesc[]={
	{ "g_gaunt.bin", 0x100000, 0xF9872055, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gaunt);
STD_ROM_FN(gaunt);

struct BurnDriverD BurnDrvMDgaunt = {
	"g_gaunt", NULL, NULL, "1994",
	"Gauntlet (J) [!]\0", NULL, "Tengen / Atari", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gauntRomInfo, gauntRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Greatest Heavyweights of the Ring (U) [!]

static struct BurnRomInfo ghworRomDesc[]={
	{ "g_ghwor.bin", 0x200000, 0x6E3621D5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ghwor);
STD_ROM_FN(ghwor);

struct BurnDriverD BurnDrvMDghwor = {
	"g_ghwor", NULL, NULL, "1900",
	"Greatest Heavyweights of the Ring (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ghworRomInfo, ghworRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// High School Soccer - Kunio Kun (J) [!]

static struct BurnRomInfo hssocRomDesc[]={
	{ "g_hssoc.bin", 0x080000, 0xF49C3A86, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hssoc);
STD_ROM_FN(hssoc);

struct BurnDriverD BurnDrvMDhssoc = {
	"g_hssoc", NULL, NULL, "1900",
	"High School Soccer - Kunio Kun (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hssocRomInfo, hssocRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hokuto no Ken (J) [!]

static struct BurnRomInfo hokutoRomDesc[]={
	{ "g_hokuto.bin", 0x080000, 0x1B6585E7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hokuto);
STD_ROM_FN(hokuto);

struct BurnDriverD BurnDrvMDhokuto = {
	"g_hokuto", NULL, NULL, "1900",
	"Hokuto no Ken (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hokutoRomInfo, hokutoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hybrid Fron

static struct BurnRomInfo hybridRomDesc[]={
	{ "g_hybrid.bin", 0x200000, 0xA1F1CFE7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hybrid);
STD_ROM_FN(hybrid);

struct BurnDriverD BurnDrvMDhybrid = {
	"g_hybrid", NULL, NULL, "1900",
	"Hybrid Fron\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hybridRomInfo, hybridRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ichidant R (J) [!]

static struct BurnRomInfo ichirRomDesc[]={
	{ "g_ichir.bin", 0x200000, 0x7BDEC762, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ichir);
STD_ROM_FN(ichir);

struct BurnDriverD BurnDrvMDichir = {
	"g_ichir", NULL, NULL, "1900",
	"Ichidant R (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ichirRomInfo, ichirRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hyokkori Hyoutanjima (J) [c][!]

static struct BurnRomInfo hyokkRomDesc[]={
	{ "g_hyokk.bin", 0x080000, 0x72253BDB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hyokk);
STD_ROM_FN(hyokk);

struct BurnDriverD BurnDrvMDhyokk = {
	"g_hyokk", NULL, NULL, "1900",
	"Hyokkori Hyoutanjima (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hyokkRomInfo, hyokkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Janou Touryumon (J) [a1][!]

static struct BurnRomInfo janoutRomDesc[]={
	{ "g_janout.bin", 0x100000, 0xB5EF97C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(janout);
STD_ROM_FN(janout);

struct BurnDriverD BurnDrvMDjanout = {
	"g_janout", NULL, NULL, "1900",
	"Janou Touryumon (J) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, janoutRomInfo, janoutRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// JuJu Densetsu (J) [!]

static struct BurnRomInfo jujuRomDesc[]={
	{ "g_juju.bin", 0x080000, 0xD09B1EF1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(juju);
STD_ROM_FN(juju);

struct BurnDriverD BurnDrvMDjuju = {
	"g_juju", NULL, NULL, "1900",
	"JuJu Densetsu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jujuRomInfo, jujuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Juu-Ou-Ki (J) (REV00) [c][!]

static struct BurnRomInfo juuo00RomDesc[]={
	{ "g_juuo00.bin", 0x080000, 0x1B7C96C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(juuo00);
STD_ROM_FN(juuo00);

struct BurnDriverD BurnDrvMDjuuo00 = {
	"g_juuo00", "g_abea", NULL, "1988",
	"Juu-Ou-Ki (J) (REV00) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, juuo00RomInfo, juuo00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Juu-Ou-Ki (J) (REV01) [!]

static struct BurnRomInfo juuo01RomDesc[]={
	{ "g_juuo01.bin", 0x080000, 0xB2233E87, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(juuo01);
STD_ROM_FN(juuo01);

struct BurnDriverD BurnDrvMDjuuo01 = {
	"g_juuo01", "g_abea", NULL, "1988",
	"Juu-Ou-Ki (J) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, juuo01RomInfo, juuo01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kishi Densetsu (J) [!]

static struct BurnRomInfo kishiRomDesc[]={
	{ "g_kishi.bin", 0x180000, 0x22E1F04A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kishi);
STD_ROM_FN(kishi);

struct BurnDriverD BurnDrvMDkishi = {
	"g_kishi", NULL, NULL, "1900",
	"Kishi Densetsu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kishiRomInfo, kishiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kyuukyou Tiger (J) [!]

static struct BurnRomInfo kyuukRomDesc[]={
	{ "g_kyuuk.bin", 0x080000, 0xDE48DCE3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kyuuk);
STD_ROM_FN(kyuuk);

struct BurnDriverD BurnDrvMDkyuuk = {
	"g_kyuuk", NULL, NULL, "1900",
	"Kyuukyou Tiger (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kyuukRomInfo, kyuukRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Langrisser (J) [!]

static struct BurnRomInfo langrRomDesc[]={
	{ "g_langr.bin", 0x080000, 0xB6EA5016, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(langr);
STD_ROM_FN(langr);

struct BurnDriverD BurnDrvMDlangr = {
	"g_langr", NULL, NULL, "1900",
	"Langrisser (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, langrRomInfo, langrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Langrisser II (J) (REV00) [!]

static struct BurnRomInfo lngr2aRomDesc[]={
	{ "g_lngr2a.bin", 0x200000, 0x7F891DFC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lngr2a);
STD_ROM_FN(lngr2a);

struct BurnDriverD BurnDrvMDlngr2a = {
	"g_lngr2a", NULL, NULL, "1900",
	"Langrisser II (J) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lngr2aRomInfo, lngr2aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Langrisser II (J) (REV02) [!]

static struct BurnRomInfo lngr2cRomDesc[]={
	{ "g_lngr2c.bin", 0x200000, 0x4967C9F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lngr2c);
STD_ROM_FN(lngr2c);

struct BurnDriverD BurnDrvMDlngr2c = {
	"g_lngr2c", NULL, NULL, "1900",
	"Langrisser II (J) (REV02) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lngr2cRomInfo, lngr2cRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Liberty or Death (U) [!]

static struct BurnRomInfo librtyRomDesc[]={
	{ "g_librty.bin", 0x200000, 0x2ADB0364, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(librty);
STD_ROM_FN(librty);

struct BurnDriverD BurnDrvMDlibrty = {
	"g_librty", NULL, NULL, "1993",
	"Liberty or Death (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, librtyRomInfo, librtyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// M-1 Abrams Battle Tank (UE) (REV01) [!]

static struct BurnRomInfo m1tankRomDesc[]={
	{ "g_m1tank.bin", 0x080000, 0x1E2F74CF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(m1tank);
STD_ROM_FN(m1tank);

struct BurnDriverD BurnDrvMDm1tank = {
	"g_m1tank", NULL, NULL, "1900",
	"M-1 Abrams Battle Tank (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, m1tankRomInfo, m1tankRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Madou Monogatari I (J) [!]

static struct BurnRomInfo madouRomDesc[]={
	{ "g_madou.bin", 0x200000, 0xDD82C401, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(madou);
STD_ROM_FN(madou);

struct BurnDriverD BurnDrvMDmadou = {
	"g_madou", NULL, NULL, "1900",
	"Madou Monogatari I (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, madouRomInfo, madouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mahjong Cop Ryuu - Shiro Ookami no Yabou (J) [!]

static struct BurnRomInfo mahcopRomDesc[]={
	{ "g_mahcop.bin", 0x040000, 0x1CCBC782, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mahcop);
STD_ROM_FN(mahcop);

struct BurnDriverD BurnDrvMDmahcop = {
	"g_mahcop", NULL, NULL, "1900",
	"Mahjong Cop Ryuu - Shiro Ookami no Yabou (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mahcopRomInfo, mahcopRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Maou Renjishi (J) [c][!]

static struct BurnRomInfo maoureRomDesc[]={
	{ "g_maoure.bin", 0x080000, 0x24A7F28C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(maoure);
STD_ROM_FN(maoure);

struct BurnDriverD BurnDrvMDmaoure = {
	"g_maoure", NULL, NULL, "1900",
	"Maou Renjishi (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, maoureRomInfo, maoureRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Maten no Soumetsu / Maten Densetsu (J) [!]

static struct BurnRomInfo matenRomDesc[]={
	{ "g_maten.bin", 0x100000, 0xB804A105, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(maten);
STD_ROM_FN(maten);

struct BurnDriverD BurnDrvMDmaten = {
	"g_maten", NULL, NULL, "1900",
	"Maten no Soumetsu / Maten Densetsu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, matenRomInfo, matenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Anser (J) (REV01) [!]

static struct BurnRomInfo manserRomDesc[]={
	{ "g_manser.bin", 0x080000, 0x08ECE367, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(manser);
STD_ROM_FN(manser);

struct BurnDriverD BurnDrvMDmanser = {
	"g_manser", NULL, NULL, "1900",
	"Mega Anser (J) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, manserRomInfo, manserRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Q - The Party Quiz Game (J) [!]

static struct BurnRomInfo megaqRomDesc[]={
	{ "g_megaq.bin", 0x100000, 0x9D4B447A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(megaq);
STD_ROM_FN(megaq);

struct BurnDriverD BurnDrvMDmegaq = {
	"g_megaq", NULL, NULL, "1900",
	"Mega Q - The Party Quiz Game (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, megaqRomInfo, megaqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Metal Fangs (J) [c][!]

static struct BurnRomInfo mfangRomDesc[]={
	{ "g_mfang.bin", 0x080000, 0xA8DF1C4C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mfang);
STD_ROM_FN(mfang);

struct BurnDriverD BurnDrvMDmfang = {
	"g_mfang", NULL, NULL, "1900",
	"Metal Fangs (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mfangRomInfo, mfangRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey Mouse - Minnie's Magical Adventure 2 (J) [!]

static struct BurnRomInfo minnieRomDesc[]={
	{ "g_minnie.bin", 0x200000, 0x5AA0F3A0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(minnie);
STD_ROM_FN(minnie);

struct BurnDriverD BurnDrvMDminnie = {
	"g_minnie", NULL, NULL, "1994",
	"Mickey Mouse - Minnie's Magical Adventure 2 (J) [!]\0", NULL, "Disney / Capcom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, minnieRomInfo, minnieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Minato no Toreijia (J) [!]

static struct BurnRomInfo minatoRomDesc[]={
	{ "g_minato.bin", 0x100000, 0xBD89FD09, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(minato);
STD_ROM_FN(minato);

struct BurnDriverD BurnDrvMDminato = {
	"g_minato", NULL, NULL, "1900",
	"Minato no Toreijia (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, minatoRomInfo, minatoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Miracle Piano Teaching System (U) [!]

static struct BurnRomInfo mpianoRomDesc[]={
	{ "g_mpiano.bin", 0x080000, 0xA719542E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mpiano);
STD_ROM_FN(mpiano);

struct BurnDriverD BurnDrvMDmpiano = {
	"g_mpiano", NULL, NULL, "1900",
	"Miracle Piano Teaching System (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mpianoRomInfo, mpianoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Monster World IV (J) [!]

static struct BurnRomInfo monwr4RomDesc[]={
	{ "g_monwr4.bin", 0x200000, 0x36A3AAA4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(monwr4);
STD_ROM_FN(monwr4);

struct BurnDriverD BurnDrvMDmonwr4 = {
	"g_monwr4", NULL, NULL, "1900",
	"Monster World IV (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, monwr4RomInfo, monwr4RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mutant League Football (UE) [!]

static struct BurnRomInfo mlfootRomDesc[]={
	{ "g_mlfoot.bin", 0x100000, 0xDCE29C9D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlfoot);
STD_ROM_FN(mlfoot);

struct BurnDriverD BurnDrvMDmlfoot = {
	"g_mlfoot", NULL, NULL, "1900",
	"Mutant League Football (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlfootRomInfo, mlfootRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// New 3D Golf Simulation Harukanaru Augusta (J) [!]

static struct BurnRomInfo new3dgRomDesc[]={
	{ "g_new3dg.bin", 0x180000, 0xD2A9BF92, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(new3dg);
STD_ROM_FN(new3dg);

struct BurnDriverD BurnDrvMDnew3dg = {
	"g_new3dg", NULL, NULL, "1900",
	"New 3D Golf Simulation Harukanaru Augusta (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, new3dgRomInfo, new3dgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nikkan Sports Pro Yakyuu Van (J) [!]

static struct BurnRomInfo nikkanRomDesc[]={
	{ "g_nikkan.bin", 0x080000, 0xC3655A59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nikkan);
STD_ROM_FN(nikkan);

struct BurnDriverD BurnDrvMDnikkan = {
	"g_nikkan", NULL, NULL, "1900",
	"Nikkan Sports Pro Yakyuu Van (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nikkanRomInfo, nikkanRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nobunaga no Yabou - Bushou Fuuunsoku (J) [!]

static struct BurnRomInfo nobbusRomDesc[]={
	{ "g_nobbus.bin", 0x100000, 0x30BF8637, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nobbus);
STD_ROM_FN(nobbus);

struct BurnDriverD BurnDrvMDnobbus = {
	"g_nobbus", NULL, NULL, "1900",
	"Nobunaga no Yabou - Bushou Fuuunsoku (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nobbusRomInfo, nobbusRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nobunaga no Yabou - Zenkokuban (J) [!]

static struct BurnRomInfo nobzenRomDesc[]={
	{ "g_nobzen.bin", 0x080000, 0x1381B313, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nobzen);
STD_ROM_FN(nobzen);

struct BurnDriverD BurnDrvMDnobzen = {
	"g_nobzen", NULL, NULL, "1900",
	"Nobunaga no Yabou - Zenkokuban (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nobzenRomInfo, nobzenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nobunaga no Yabou Haouden - Lord of Darkness (J) [!]

static struct BurnRomInfo noblorRomDesc[]={
	{ "g_noblor.bin", 0x200000, 0x96C01FC6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(noblor);
STD_ROM_FN(noblor);

struct BurnDriverD BurnDrvMDnoblor = {
	"g_noblor", NULL, NULL, "1900",
	"Nobunaga no Yabou Haouden - Lord of Darkness (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, noblorRomInfo, noblorRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Patlabor (J) [c][!]

static struct BurnRomInfo patlabRomDesc[]={
	{ "g_patlab.bin", 0x080000, 0x21A0E749, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(patlab);
STD_ROM_FN(patlab);

struct BurnDriverD BurnDrvMDpatlab = {
	"g_patlab", NULL, NULL, "1900",
	"Patlabor (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, patlabRomInfo, patlabRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Psy-O-Blade Moving Adventure (J) [!]

static struct BurnRomInfo psyoblRomDesc[]={
	{ "g_psyobl.bin", 0x0A0000, 0x8BA7E6C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(psyobl);
STD_ROM_FN(psyobl);

struct BurnDriverD BurnDrvMDpsyobl = {
	"g_psyobl", NULL, NULL, "1900",
	"Psy-O-Blade Moving Adventure (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, psyoblRomInfo, psyoblRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ragnacenty (J) [!]

static struct BurnRomInfo ragnaRomDesc[]={
	{ "g_ragna.bin", 0x200000, 0x6A3F5AE2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ragna);
STD_ROM_FN(ragna);

struct BurnDriverD BurnDrvMDragna = {
	"g_ragna", NULL, NULL, "1994",
	"Ragnacenty (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ragnaRomInfo, ragnaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ransei no Hasha (J) [!]

static struct BurnRomInfo ranseiRomDesc[]={
	{ "g_ransei.bin", 0x100000, 0xA9A0083D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ransei);
STD_ROM_FN(ransei);

struct BurnDriverD BurnDrvMDransei = {
	"g_ransei", NULL, NULL, "1900",
	"Ransei no Hasha (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ranseiRomInfo, ranseiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rent A Hero (J) [!]

static struct BurnRomInfo rentheRomDesc[]={
	{ "g_renthe.bin", 0x100000, 0x2E515F82, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(renthe);
STD_ROM_FN(renthe);

struct BurnDriverD BurnDrvMDrenthe = {
	"g_renthe", NULL, NULL, "1900",
	"Rent A Hero (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rentheRomInfo, rentheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robocop 3 (UE) [!]

static struct BurnRomInfo robo3RomDesc[]={
	{ "g_robo3.bin", 0x080000, 0x34FB7B27, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robo3);
STD_ROM_FN(robo3);

struct BurnDriverD BurnDrvMDrobo3 = {
	"g_robo3", NULL, NULL, "1993",
	"Robocop 3 (UE) [!]\0", NULL, "Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robo3RomInfo, robo3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Royal Blood (J) [!]

static struct BurnRomInfo roybldRomDesc[]={
	{ "g_roybld.bin", 0x100000, 0x0E0107F1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(roybld);
STD_ROM_FN(roybld);

struct BurnDriverD BurnDrvMDroybld = {
	"g_roybld", NULL, NULL, "1900",
	"Royal Blood (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, roybldRomInfo, roybldRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sagaia (U) [c][!]

static struct BurnRomInfo sagiaRomDesc[]={
	{ "g_sagia.bin", 0x100000, 0xF1E22F43, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sagia);
STD_ROM_FN(sagia);

struct BurnDriverD BurnDrvMDsagia = {
	"g_sagia", NULL, NULL, "1900",
	"Sagaia (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sagiaRomInfo, sagiaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sangokushi II (J) [!]

static struct BurnRomInfo sango2RomDesc[]={
	{ "g_sango2.bin", 0x100000, 0x437BA326, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sango2);
STD_ROM_FN(sango2);

struct BurnDriverD BurnDrvMDsango2 = {
	"g_sango2", NULL, NULL, "1900",
	"Sangokushi II (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sango2RomInfo, sango2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sangokushi III (J) [!]

static struct BurnRomInfo sango3RomDesc[]={
	{ "g_sango3.bin", 0x180000, 0xA8DE6AEA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sango3);
STD_ROM_FN(sango3);

struct BurnDriverD BurnDrvMDsango3 = {
	"g_sango3", NULL, NULL, "1900",
	"Sangokushi III (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sango3RomInfo, sango3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sangokushi Retsuden - Ransei no Eiyuu Tachi (J) [!]

static struct BurnRomInfo sangorRomDesc[]={
	{ "g_sangor.bin", 0x100000, 0x0F56785A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sangor);
STD_ROM_FN(sangor);

struct BurnDriverD BurnDrvMDsangor = {
	"g_sangor", NULL, NULL, "1900",
	"Sangokushi Retsuden - Ransei no Eiyuu Tachi (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sangorRomInfo, sangorRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shi Kin Joh (J) [!]

static struct BurnRomInfo shikinRomDesc[]={
	{ "g_shikin.bin", 0x080000, 0x5EA0C97D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shikin);
STD_ROM_FN(shikin);

struct BurnDriverD BurnDrvMDshikin = {
	"g_shikin", NULL, NULL, "1900",
	"Shi Kin Joh (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shikinRomInfo, shikinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shiten Myooh (J) [c][!]

static struct BurnRomInfo shitenRomDesc[]={
	{ "g_shiten.bin", 0x080000, 0x7E729693, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shiten);
STD_ROM_FN(shiten);

struct BurnDriverD BurnDrvMDshiten = {
	"g_shiten", NULL, NULL, "1900",
	"Shiten Myooh (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shitenRomInfo, shitenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shogi no Hoshi (J) [!]

static struct BurnRomInfo shogiRomDesc[]={
	{ "g_shogi.bin", 0x040000, 0x4148F816, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shogi);
STD_ROM_FN(shogi);

struct BurnDriverD BurnDrvMDshogi = {
	"g_shogi", NULL, NULL, "1900",
	"Shogi no Hoshi (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shogiRomInfo, shogiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shura no Mon (J) [!]

static struct BurnRomInfo shuraRomDesc[]={
	{ "g_shura.bin", 0x100000, 0xE19DA6E5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shura);
STD_ROM_FN(shura);

struct BurnDriverD BurnDrvMDshura = {
	"g_shura", NULL, NULL, "1900",
	"Shura no Mon (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shuraRomInfo, shuraRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Slap Fight (J) [c][!]

static struct BurnRomInfo slapfRomDesc[]={
	{ "g_slapf.bin", 0x100000, 0xD6695695, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(slapf);
STD_ROM_FN(slapf);

struct BurnDriverD BurnDrvMDslapf = {
	"g_slapf", NULL, NULL, "1900",
	"Slap Fight (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, slapfRomInfo, slapfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soldiers of Fortune (U) [c][!]

static struct BurnRomInfo soldfRomDesc[]={
	{ "g_soldf.bin", 0x180000, 0xA84D28A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soldf);
STD_ROM_FN(soldf);

struct BurnDriverD BurnDrvMDsoldf = {
	"g_soldf", NULL, NULL, "1900",
	"Soldiers of Fortune (U) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soldfRomInfo, soldfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sorcerer's Kingdom (U) (REV01) [!]

static struct BurnRomInfo sorckdRomDesc[]={
	{ "g_sorckd.bin", 0x100000, 0xBB1FC9CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sorckd);
STD_ROM_FN(sorckd);

struct BurnDriverD BurnDrvMDsorckd = {
	"g_sorckd", NULL, NULL, "1900",
	"Sorcerer's Kingdom (U) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sorckdRomInfo, sorckdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Steel Talons (UE) [!]

static struct BurnRomInfo stalonRomDesc[]={
	{ "g_stalon.bin", 0x080000, 0x10E4EC63, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stalon);
STD_ROM_FN(stalon);

struct BurnDriverD BurnDrvMDstalon = {
	"g_stalon", NULL, NULL, "1900",
	"Steel Talons (UE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stalonRomInfo, stalonRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (E) [!]

static struct BurnRomInfo sthorRomDesc[]={
	{ "g_sthor.bin", 0x300000, 0x1110B0DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthor);
STD_ROM_FN(sthor);

struct BurnDriver BurnDrvMDsthor = {
	"g_sthor", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorRomInfo, sthorRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (J) [!]

static struct BurnRomInfo sthorjRomDesc[]={
	{ "g_sthorj.bin", 0x300000, 0x4F39783C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthorj);
STD_ROM_FN(sthorj);

struct BurnDriver BurnDrvMDsthorj = {
	"g_sthorj", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorjRomInfo, sthorjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Daisenryaku (J) (REV00) [!]

static struct BurnRomInfo supdaiRomDesc[]={
	{ "g_supdai.bin", 0x080000, 0xD50A166F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(supdai);
STD_ROM_FN(supdai);

struct BurnDriverD BurnDrvMDsupdai = {
	"g_supdai", NULL, NULL, "1900",
	"Super Daisenryaku (J) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, supdaiRomInfo, supdaiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Surging Aura (J) [!]

static struct BurnRomInfo surginRomDesc[]={
	{ "g_surgin.bin", 0x200000, 0x65AC1D2B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(surgin);
STD_ROM_FN(surgin);

struct BurnDriverD BurnDrvMDsurgin = {
	"g_surgin", NULL, NULL, "1900",
	"Surging Aura (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, surginRomInfo, surginRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Syd of Valis (U) [!]

static struct BurnRomInfo sydvalRomDesc[]={
	{ "g_sydval.bin", 0x080000, 0x37DC0108, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sydval);
STD_ROM_FN(sydval);

struct BurnDriverD BurnDrvMDsydval = {
	"g_sydval", NULL, NULL, "1900",
	"Syd of Valis (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sydvalRomInfo, sydvalRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Taiga Drama Taiheiki (J) [!]

static struct BurnRomInfo taigaRomDesc[]={
	{ "g_taiga.bin", 0x100000, 0x09FBB30E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(taiga);
STD_ROM_FN(taiga);

struct BurnDriverD BurnDrvMDtaiga = {
	"g_taiga", NULL, NULL, "1900",
	"Taiga Drama Taiheiki (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taigaRomInfo, taigaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Taikou Risshiden (J) [!]

static struct BurnRomInfo taikouRomDesc[]={
	{ "g_taikou.bin", 0x140000, 0xF96FE15B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(taikou);
STD_ROM_FN(taikou);

struct BurnDriverD BurnDrvMDtaikou = {
	"g_taikou", NULL, NULL, "1900",
	"Taikou Risshiden (J) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taikouRomInfo, taikouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teitoku no Ketsudan (J) [c][!]

static struct BurnRomInfo teitokRomDesc[]={
	{ "g_teitok.bin", 0x100000, 0x9B08E4E4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(teitok);
STD_ROM_FN(teitok);

struct BurnDriverD BurnDrvMDteitok = {
	"g_teitok", NULL, NULL, "1900",
	"Teitoku no Ketsudan (J) [c][!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, teitokRomInfo, teitokRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tel Tel Mahjong (J) [c][!]

static struct BurnRomInfo telmjRomDesc[]={
	{ "g_telmj.bin", 0x040000, 0x44817E92, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(telmj);
STD_ROM_FN(telmj);

struct BurnDriverD BurnDrvMDtelmj = {
	"g_telmj", NULL, NULL, "1900",
	"Tel Tel Mahjong (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, telmjRomInfo, telmjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tel Tel Stadium (J) [!]

static struct BurnRomInfo telstdRomDesc[]={
	{ "g_telstd.bin", 0x080000, 0x54CF8C29, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(telstd);
STD_ROM_FN(telstd);

struct BurnDriverD BurnDrvMDtelstd = {
	"g_telstd", NULL, NULL, "1900",
	"Tel Tel Stadium (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, telstdRomInfo, telstdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Top Pro Golf 2 (J) [!]

static struct BurnRomInfo tpglf2RomDesc[]={
	{ "g_tpglf2.bin", 0x100000, 0xB8CE98B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tpglf2);
STD_ROM_FN(tpglf2);

struct BurnDriverD BurnDrvMDtpglf2 = {
	"g_tpglf2", NULL, NULL, "1900",
	"Top Pro Golf 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tpglf2RomInfo, tpglf2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Top Pro Golf 2 (J) [!]

static struct BurnRomInfo tpglfRomDesc[]={
	{ "g_tpglf.bin", 0x100000, 0x62BAD606, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tpglf);
STD_ROM_FN(tpglf);

struct BurnDriverD BurnDrvMDtpglf = {
	"g_tpglf", NULL, NULL, "1900",
	"Top Pro Golf 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tpglfRomInfo, tpglfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Traysia (U) [!]

static struct BurnRomInfo traysiRomDesc[]={
	{ "g_traysi.bin", 0x100000, 0x96184F4F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(traysi);
STD_ROM_FN(traysi);

struct BurnDriverD BurnDrvMDtraysi = {
	"g_traysi", NULL, NULL, "1900",
	"Traysia (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, traysiRomInfo, traysiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Twinkle Tale (J) [!]

static struct BurnRomInfo twintlRomDesc[]={
	{ "g_twintl.bin", 0x100000, 0xD757F924, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(twintl);
STD_ROM_FN(twintl);

struct BurnDriverD BurnDrvMDtwintl = {
	"g_twintl", NULL, NULL, "1900",
	"Twinkle Tale (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, twintlRomInfo, twintlRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Uncharted Waters (U) [!]

static struct BurnRomInfo uwRomDesc[]={
	{ "g_uw.bin", 0x100000, 0x4EDAEC59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uw);
STD_ROM_FN(uw);

struct BurnDriverD BurnDrvMDuw = {
	"g_uw", NULL, NULL, "199?",
	"Uncharted Waters (U) [!]\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, uwRomInfo, uwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Verytex (J) [c][!]

static struct BurnRomInfo verytxRomDesc[]={
	{ "g_verytx.bin", 0x080000, 0xBAFC375F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(verytx);
STD_ROM_FN(verytx);

struct BurnDriverD BurnDrvMDverytx = {
	"g_verytx", NULL, NULL, "1900",
	"Verytex (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, verytxRomInfo, verytxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vixen 357 (J) [!]

static struct BurnRomInfo vix357RomDesc[]={
	{ "g_vix357.bin", 0x100000, 0x3AFA2D7B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vix357);
STD_ROM_FN(vix357);

struct BurnDriverD BurnDrvMDvix357 = {
	"g_vix357", NULL, NULL, "1900",
	"Vixen 357 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vix357RomInfo, vix357RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Waialae no Kiseki (J) [!]

static struct BurnRomInfo waialaRomDesc[]={
	{ "g_waiala.bin", 0x180000, 0xCBE2C1F6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(waiala);
STD_ROM_FN(waiala);

struct BurnDriverD BurnDrvMDwaiala = {
	"g_waiala", NULL, NULL, "1900",
	"Waialae no Kiseki (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, waialaRomInfo, waialaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warpspeed (U) [!]

static struct BurnRomInfo warpsRomDesc[]={
	{ "g_warps.bin", 0x200000, 0x143697ED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(warps);
STD_ROM_FN(warps);

struct BurnDriverD BurnDrvMDwarps = {
	"g_warps", NULL, NULL, "1900",
	"Warpspeed (U) [!]\0", NULL, "Accolade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, warpsRomInfo, warpsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warrior of Rome II (U) [c][!]

static struct BurnRomInfo wrom2RomDesc[]={
	{ "g_wrom2.bin", 0x100000, 0xCD8C472A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wrom2);
STD_ROM_FN(wrom2);

struct BurnDriverD BurnDrvMDwrom2 = {
	"g_wrom2", NULL, NULL, "1992",
	"Warrior of Rome II (U) [c][!]\0", NULL, "Micronet", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wrom2RomInfo, wrom2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wonder Boy V - Monster World III (J) [!]

static struct BurnRomInfo wboy5RomDesc[]={
	{ "g_wboy5.bin", 0x0A0000, 0x45A50F96, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wboy5);
STD_ROM_FN(wboy5);

struct BurnDriverD BurnDrvMDwboy5 = {
	"g_wboy5", NULL, NULL, "1900",
	"Wonder Boy V - Monster World III (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wboy5RomInfo, wboy5RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wonder Library (J) [!]

static struct BurnRomInfo wonlibRomDesc[]={
	{ "g_wonlib.bin", 0x080000, 0x9350E754, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wonlib);
STD_ROM_FN(wonlib);

struct BurnDriverD BurnDrvMDwonlib = {
	"g_wonlib", NULL, NULL, "1900",
	"Wonder Library (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wonlibRomInfo, wonlibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wrestleball (J) [c][!]

static struct BurnRomInfo wresblRomDesc[]={
	{ "g_wresbl.bin", 0x080000, 0xD563E07F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wresbl);
STD_ROM_FN(wresbl);

struct BurnDriverD BurnDrvMDwresbl = {
	"g_wresbl", NULL, NULL, "1900",
	"Wrestleball (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wresblRomInfo, wresblRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// X Dazedly Ray (J) [!]

static struct BurnRomInfo xdazeRomDesc[]={
	{ "g_xdaze.bin", 0x080000, 0xAB22D002, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xdaze);
STD_ROM_FN(xdaze);

struct BurnDriverD BurnDrvMDxdaze = {
	"g_xdaze", NULL, NULL, "1900",
	"X Dazedly Ray (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xdazeRomInfo, xdazeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// X-Men (U) [!]

static struct BurnRomInfo xmenRomDesc[]={
	{ "g_xmen.bin", 0x100000, 0xF71B21B4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xmen);
STD_ROM_FN(xmen);

struct BurnDriverD BurnDrvMDxmen = {
	"g_xmen", NULL, NULL, "1900",
	"X-Men (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xmenRomInfo, xmenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Yuu Yuu Hakusho Gaiden (J) [!]

static struct BurnRomInfo yuyugaRomDesc[]={
	{ "g_yuyuga.bin", 0x200000, 0x7DC98176, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yuyuga);
STD_ROM_FN(yuyuga);

struct BurnDriverD BurnDrvMDyuyuga = {
	"g_yuyuga", NULL, NULL, "1900",
	"Yuu Yuu Hakusho Gaiden (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yuyugaRomInfo, yuyugaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zan - Yasha Enbukyoku / Zan Yasha Enbuden (J) [!]

static struct BurnRomInfo zanyaRomDesc[]={
	{ "g_zanya.bin", 0x080000, 0x637FE8F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zanya);
STD_ROM_FN(zanya);

struct BurnDriverD BurnDrvMDzanya = {
	"g_zanya", NULL, NULL, "1991",
	"Zan - Yasha Enbukyoku / Zan Yasha Enbuden (J) [!]\0", NULL, "Wolfteam", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zanyaRomInfo, zanyaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// A Ressha de Gyoukou MD (J) [!]

static struct BurnRomInfo areshaRomDesc[]={
	{ "g_aresha.bin", 0x080000, 0x3D45DE4F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aresha);
STD_ROM_FN(aresha);

struct BurnDriver BurnDrvMDaresha = {
	"g_aresha", NULL, NULL, "1900",
	"A Ressha de Gyoukou MD (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, areshaRomInfo, areshaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alien Soldier (E) [!]

static struct BurnRomInfo asoldeRomDesc[]={
	{ "g_asolde.bin", 0x200000, 0x0496E06C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(asolde);
STD_ROM_FN(asolde);

struct BurnDriverD BurnDrvMDasolde = {
	"g_asolde", "g_asol", NULL, "1900",
	"Alien Soldier (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, asoldeRomInfo, asoldeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alisia Dragoon (E) [!]

static struct BurnRomInfo alisieRomDesc[]={
	{ "g_alisie.bin", 0x100000, 0x28165BD1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alisie);
STD_ROM_FN(alisie);

struct BurnDriverD BurnDrvMDalisie = {
	"g_alisie", "g_alis", NULL, "1900",
	"Alisia Dragoon (E) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alisieRomInfo, alisieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alisia Dragoon (J) [!]

static struct BurnRomInfo alisijRomDesc[]={
	{ "g_alisij.bin", 0x100000, 0x4D476722, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alisij);
STD_ROM_FN(alisij);

struct BurnDriverD BurnDrvMDalisij = {
	"g_alisij", "g_alis", NULL, "1900",
	"Alisia Dragoon (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alisijRomInfo, alisijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Air Diver (J) [!]

static struct BurnRomInfo adivejRomDesc[]={
	{ "g_adivej.bin", 0x080000, 0x9E2D5B91, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(adivej);
STD_ROM_FN(adivej);

struct BurnDriverD BurnDrvMDadivej = {
	"g_adivej", "g_adiv", NULL, "1900",
	"Air Diver (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, adivejRomInfo, adivejRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bad Omen (J) [c][!]

static struct BurnRomInfo bdomenRomDesc[]={
	{ "g_bdomen.bin", 0x080000, 0x975693CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bdomen);
STD_ROM_FN(bdomen);

struct BurnDriverD BurnDrvMDbdomen = {
	"g_bdomen", "g_devi", NULL, "1992",
	"Bad Omen (J) [c][!]\0", "No sound", "Hot B", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bdomenRomInfo, bdomenRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Art of Fighting (E) [!]

static struct BurnRomInfo aofeRomDesc[]={
	{ "g_aofe.bin", 0x200000, 0x9970C422, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aofe);
STD_ROM_FN(aofe);

struct BurnDriver BurnDrvMDaofe = {
	"g_aofe", "g_aof", NULL, "1994",
	"Art of Fighting (E) [!]\0", NULL, "SNK / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aofeRomInfo, aofeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bonanza Bros. (JE) (REV00) [!]

static struct BurnRomInfo bnza00RomDesc[]={
	{ "g_bnza00.bin", 0x080000, 0xADF6476C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bnza00);
STD_ROM_FN(bnza00);

struct BurnDriverD BurnDrvMDbnza00 = {
	"g_bnza00", "g_bnza", NULL, "1900",
	"Bonanza Bros. (JE) (REV00) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bnza00RomInfo, bnza00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bonanza Bros. (JE) (REV01) [!]

static struct BurnRomInfo bnza01RomDesc[]={
	{ "g_bnza01.bin", 0x080000, 0xC6AAC589, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bnza01);
STD_ROM_FN(bnza01);

struct BurnDriverD BurnDrvMDbnza01 = {
	"g_bnza01", "g_bnza", NULL, "1900",
	"Bonanza Bros. (JE) (REV01) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bnza01RomInfo, bnza01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Asterix and the Great Rescue (U) [!]

static struct BurnRomInfo astgruRomDesc[]={
	{ "g_astgru.bin", 0x200000, 0x7F112CD8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(astgru);
STD_ROM_FN(astgru);

struct BurnDriverD BurnDrvMDastgru = {
	"g_astgru", "g_asgr", NULL, "1900",
	"Asterix and the Great Rescue (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, astgruRomInfo, astgruRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Boogerman (E) [!]

static struct BurnRomInfo boogeRomDesc[]={
	{ "g_booge.bin", 0x300000, 0xDBC4340C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(booge);
STD_ROM_FN(booge);

struct BurnDriverD BurnDrvMDbooge = {
	"g_booge", "g_boog", NULL, "1900",
	"Boogerman (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, boogeRomInfo, boogeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Castlevania - The New Generation (E) [!]

static struct BurnRomInfo cvaneRomDesc[]={
	{ "g_cvane.bin", 0x100000, 0x4DD4E4A5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cvane);
STD_ROM_FN(cvane);

struct BurnDriverD BurnDrvMDcvane = {
	"g_cvane", NULL, NULL, "1994",
	"Castlevania - The New Generation (E) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cvaneRomInfo, cvaneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Capt'n Havoc (E) [!]

static struct BurnRomInfo capthaRomDesc[]={
	{ "g_captha.bin", 0x100000, 0x76E6D20D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(captha);
STD_ROM_FN(captha);

struct BurnDriverD BurnDrvMDcaptha = {
	"g_captha", NULL, NULL, "1994",
	"Capt'n Havoc (E) [!]\0", NULL, "Data East / Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, capthaRomInfo, capthaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chou Yakyuu Miracle Nine (J) [!]

static struct BurnRomInfo chouyaRomDesc[]={
	{ "g_chouya.bin", 0x200000, 0x6D8C2206, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chouya);
STD_ROM_FN(chouya);

struct BurnDriverD BurnDrvMDchouya = {
	"g_chouya", NULL, NULL, "1900",
	"Chou Yakyuu Miracle Nine (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chouyaRomInfo, chouyaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chiki Chiki Boys (J) [!]

static struct BurnRomInfo chikijRomDesc[]={
	{ "g_chikij.bin", 0x100000, 0x06918C17, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chikij);
STD_ROM_FN(chikij);

struct BurnDriverD BurnDrvMDchikij = {
	"g_chikij", NULL, NULL, "1900",
	"Chiki Chiki Boys (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chikijRomInfo, chikijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Comix Zone (E) (M4) [!]

static struct BurnRomInfo comixeRomDesc[]={
	{ "g_comixe.bin", 0x200000, 0x1318E923, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comixe);
STD_ROM_FN(comixe);

struct BurnDriverD BurnDrvMDcomixe = {
	"g_comixe", NULL, NULL, "1995",
	"Comix Zone (E) (M4) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comixeRomInfo, comixeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Comix Zone (J) [!]

static struct BurnRomInfo comixjRomDesc[]={
	{ "g_comixj.bin", 0x200000, 0x7A6027B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comixj);
STD_ROM_FN(comixj);

struct BurnDriverD BurnDrvMDcomixj = {
	"g_comixj", NULL, NULL, "1995",
	"Comix Zone (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comixjRomInfo, comixjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Contra - The Hard Corps (J) [!]

static struct BurnRomInfo contrjRomDesc[]={
	{ "g_contrj.bin", 0x200000, 0x2AB26380, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(contrj);
STD_ROM_FN(contrj);

struct BurnDriverD BurnDrvMDcontrj = {
	"g_contrj", NULL, NULL, "1994",
	"Contra - The Hard Corps (J) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, contrjRomInfo, contrjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cool Spot (E) [!]

static struct BurnRomInfo cooleRomDesc[]={
	{ "g_coole.bin", 0x100000, 0x5F09FA41, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(coole);
STD_ROM_FN(coole);

struct BurnDriverD BurnDrvMDcoole = {
	"g_coole", NULL, NULL, "1900",
	"Cool Spot (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cooleRomInfo, cooleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crying - Asia Seimei Sensou (J) [!]

static struct BurnRomInfo cryingRomDesc[]={
	{ "g_crying.bin", 0x100000, 0x4ABA1D6A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crying);
STD_ROM_FN(crying);

struct BurnDriver BurnDrvMDcrying = {
	"g_crying", "g_bhb", NULL, "1900",
	"Crying - Asia Seimei Sensou (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cryingRomInfo, cryingRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Disney's Aladdin (E) [!]

static struct BurnRomInfo aladeRomDesc[]={
	{ "g_alade.bin", 0x200000, 0xD1845E8F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alade);
STD_ROM_FN(alade);

struct BurnDriverD BurnDrvMDalade = {
	"g_alade", "g_alad", NULL, "1993",
	"Disney's Aladdin (E) [!]\0", "No sound", "Disney / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aladeRomInfo, aladeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Disney's Aladdin (J) [!]

static struct BurnRomInfo aladjRomDesc[]={
	{ "g_aladj.bin", 0x200000, 0xFB5AACF0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aladj);
STD_ROM_FN(aladj);

struct BurnDriverD BurnDrvMDaladj = {
	"g_aladj", "g_alad", NULL, "1993",
	"Disney's Aladdin (J) [!]\0", "No sound", "Disney / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aladjRomInfo, aladjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Earthworm Jim 2 (E) [!]

static struct BurnRomInfo ejim2eRomDesc[]={
	{ "g_ejim2e.bin", 0x300000, 0xAF235FDF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ejim2e);
STD_ROM_FN(ejim2e);

struct BurnDriverD BurnDrvMDejim2e = {
	"g_ejim2e", NULL, NULL, "1900",
	"Earthworm Jim 2 (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ejim2eRomInfo, ejim2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Earthworm Jim (E) [!]

static struct BurnRomInfo ejimeRomDesc[]={
	{ "g_ejime.bin", 0x300000, 0x1C07B337, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ejime);
STD_ROM_FN(ejime);

struct BurnDriverD BurnDrvMDejime = {
	"g_ejime", NULL, NULL, "1900",
	"Earthworm Jim (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ejimeRomInfo, ejimeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dream Team USA (J) [!]

static struct BurnRomInfo dtusaRomDesc[]={
	{ "g_dtusa.bin", 0x100000, 0xE2E21B72, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dtusa);
STD_ROM_FN(dtusa);

struct BurnDriverD BurnDrvMDdtusa = {
	"g_dtusa", NULL, NULL, "1900",
	"Dream Team USA (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dtusaRomInfo, dtusaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dr. Robotnik's Mean Bean Machine (E) [!]

static struct BurnRomInfo beaneRomDesc[]={
	{ "g_beane.bin", 0x100000, 0x70680706, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beane);
STD_ROM_FN(beane);

struct BurnDriverD BurnDrvMDbeane = {
	"g_beane", "g_bean", NULL, "1900",
	"Dr. Robotnik's Mean Bean Machine (E) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beaneRomInfo, beaneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dyna Brothers 2 (J) [!]

static struct BurnRomInfo dynab2RomDesc[]={
	{ "g_dynab2.bin", 0x200000, 0x47E0A64E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dynab2);
STD_ROM_FN(dynab2);

struct BurnDriverD BurnDrvMDdynab2 = {
	"g_dynab2", NULL, NULL, "1900",
	"Dyna Brothers 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dynab2RomInfo, dynab2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dynamite Headdy (J) [c][!]

static struct BurnRomInfo dheadjRomDesc[]={
	{ "g_dheadj.bin", 0x200000, 0xD03CDB53, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dheadj);
STD_ROM_FN(dheadj);

struct BurnDriverD BurnDrvMDdheadj = {
	"g_dheadj", NULL, NULL, "1900",
	"Dynamite Headdy (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dheadjRomInfo, dheadjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Escape From Mars Starring Taz (E) [!]

static struct BurnRomInfo taz2eRomDesc[]={
	{ "g_taz2e.bin", 0x200000, 0x62100099, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(taz2e);
STD_ROM_FN(taz2e);

struct BurnDriverD BurnDrvMDtaz2e = {
	"g_taz2e", NULL, NULL, "1900",
	"Escape From Mars Starring Taz (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, taz2eRomInfo, taz2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-15 Strike Eagle II (E) [!]

static struct BurnRomInfo f15eRomDesc[]={
	{ "g_f15e.bin", 0x100000, 0xE98EE370, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f15e);
STD_ROM_FN(f15e);

struct BurnDriverD BurnDrvMDf15e = {
	"g_f15e", NULL, NULL, "1900",
	"F-15 Strike Eagle II (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f15eRomInfo, f15eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-22 Interceptor - Advanced Tactical Fighter (J) [!]

static struct BurnRomInfo f22jRomDesc[]={
	{ "g_f22j.bin", 0x0C0000, 0xFB55C785, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f22j);
STD_ROM_FN(f22j);

struct BurnDriverD BurnDrvMDf22j = {
	"g_f22j", NULL, NULL, "1991",
	"F-22 Interceptor - Advanced Tactical Fighter (J) [!]\0", NULL, "Electronic Arts / Edward Lemer", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f22jRomInfo, f22jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-22 Interceptor (U) (Sep 1991) [a1][c][!]

static struct BurnRomInfo f22uaRomDesc[]={
	{ "g_f22ua.bin", 0x0C0000, 0x31E9D1A5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f22ua);
STD_ROM_FN(f22ua);

struct BurnDriverD BurnDrvMDf22ua = {
	"g_f22ua", NULL, NULL, "1991",
	"F-22 Interceptor (U) (Sep 1991) [a1][c][!]\0", NULL, "Electronic Arts / Edward Lemer", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f22uaRomInfo, f22uaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-22 Interceptor (U) (Sep 1991) [c][!]

static struct BurnRomInfo f22uRomDesc[]={
	{ "g_f22u.bin", 0x0C0000, 0x9CF552C2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f22u);
STD_ROM_FN(f22u);

struct BurnDriverD BurnDrvMDf22u = {
	"g_f22u", NULL, NULL, "1991",
	"F-22 Interceptor (U) (Sep 1991) [c][!]\0", NULL, "Electronic Arts / Edward Lemer", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f22uRomInfo, f22uRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fever Pitch Soccer (E) (M5) [!]

static struct BurnRomInfo feverRomDesc[]={
	{ "g_fever.bin", 0x200000, 0xFAC29677, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fever);
STD_ROM_FN(fever);

struct BurnDriverD BurnDrvMDfever = {
	"g_fever", NULL, NULL, "1900",
	"Fever Pitch Soccer (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, feverRomInfo, feverRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flashback - The Quest for Identity (U) [a1][!]

static struct BurnRomInfo fbckuaRomDesc[]={
	{ "g_fbckua.bin", 0x180000, 0x33CD2B65, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fbckua);
STD_ROM_FN(fbckua);

struct BurnDriver BurnDrvMDfbckua = {
	"g_fbckua", "g_fbak", NULL, "1993",
	"Flashback - The Quest for Identity (U) [a1][!]\0", NULL, "Delphine / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fbckuaRomInfo, fbckuaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flashback - The Quest for Identity (J) [!]

static struct BurnRomInfo fbckjRomDesc[]={
	{ "g_fbckj.bin", 0x180000, 0xB790E3B4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fbckj);
STD_ROM_FN(fbckj);

struct BurnDriver BurnDrvMDfbckj = {
	"g_fbckj", "g_fbak", NULL, "1993",
	"Flashback - The Quest for Identity (J) [!]\0", NULL, "Delphine / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fbckjRomInfo, fbckjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flashback - The Quest for Identity (E) [!]

static struct BurnRomInfo fbckeRomDesc[]={
	{ "g_fbcke.bin", 0x180000, 0x6F311C83, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fbcke);
STD_ROM_FN(fbcke);

struct BurnDriver BurnDrvMDfbcke = {
	"g_fbcke", "g_fbak", NULL, "1993",
	"Flashback - The Quest for Identity (E) [!]\0", NULL, "Delphine / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fbckeRomInfo, fbckeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gambler Jiko Chuushinha - Katayama Masayuki no Mahjong Doujou (J) [!]

static struct BurnRomInfo gamblrRomDesc[]={
	{ "g_gamblr.bin", 0x080000, 0x05650B7A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gamblr);
STD_ROM_FN(gamblr);

struct BurnDriverD BurnDrvMDgamblr = {
	"g_gamblr", NULL, NULL, "1900",
	"Gambler Jiko Chuushinha - Katayama Masayuki no Mahjong Doujou (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gamblrRomInfo, gamblrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Garou Densetsu - Shukumei no Tatakai (J) [!]

static struct BurnRomInfo garouRomDesc[]={
	{ "g_garou.bin", 0x180000, 0xBF3E3FA4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(garou);
STD_ROM_FN(garou);

struct BurnDriverD BurnDrvMDgarou = {
	"g_garou", NULL, NULL, "1993",
	"Garou Densetsu - Shukumei no Tatakai (J) [!]\0", NULL, "SNK / Takara", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, garouRomInfo, garouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Garou Densetsu 2 - Arata-naru Tatakai (J) [c][!]

static struct BurnRomInfo garou2RomDesc[]={
	{ "g_garou2.bin", 0x300000, 0x2AF4427F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(garou2);
STD_ROM_FN(garou2);

struct BurnDriverD BurnDrvMDgarou2 = {
	"g_garou2", NULL, NULL, "1994",
	"Garou Densetsu 2 - Arata-naru Tatakai (J) [c][!]\0", NULL, "SNK / Takara", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, garou2RomInfo, garou2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gods (E) [!]

static struct BurnRomInfo godseRomDesc[]={
	{ "g_godse.bin", 0x100000, 0x6C415016, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(godse);
STD_ROM_FN(godse);

struct BurnDriverD BurnDrvMDgodse = {
	"g_godse", NULL, NULL, "1900",
	"Gods (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, godseRomInfo, godseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gods (J) [!]

static struct BurnRomInfo godsjRomDesc[]={
	{ "g_godsj.bin", 0x100000, 0xE4F50206, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(godsj);
STD_ROM_FN(godsj);

struct BurnDriverD BurnDrvMDgodsj = {
	"g_godsj", NULL, NULL, "1900",
	"Gods (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, godsjRomInfo, godsjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Grand Slam Tennis (J) [!]

static struct BurnRomInfo gstenjRomDesc[]={
	{ "g_gstenj.bin", 0x080000, 0x30CF37D0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gstenj);
STD_ROM_FN(gstenj);

struct BurnDriverD BurnDrvMDgstenj = {
	"g_gstenj", NULL, NULL, "1900",
	"Grand Slam Tennis (J) [!]\0", NULL, "Sega / System Sacom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gstenjRomInfo, gstenjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gunstar Heroes (E) [!]

static struct BurnRomInfo gsheRomDesc[]={
	{ "g_gshe.bin", 0x100000, 0x866ED9D0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gshe);
STD_ROM_FN(gshe);

struct BurnDriverD BurnDrvMDgshe = {
	"g_gshe", NULL, NULL, "1993",
	"Gunstar Heroes (E) [!]\0", NULL, "Sega / Treasure", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gsheRomInfo, gsheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gunstar Heroes (J) [!]]

static struct BurnRomInfo gshjRomDesc[]={
	{ "g_gshj.bin", 0x100000, 0x1CFD0383, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gshj);
STD_ROM_FN(gshj);

struct BurnDriverD BurnDrvMDgshj = {
	"g_gshj", NULL, NULL, "1993",
	"Gunstar Heroes (J) [!]]\0", NULL, "Sega / Treasure", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gshjRomInfo, gshjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// I Love Mickey Mouse - Fushigi no Oshiro Dai Bouken (J) [!]

static struct BurnRomInfo mickeyRomDesc[]={
	{ "g_mickey.bin", 0x080000, 0xCE8333C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mickey);
STD_ROM_FN(mickey);

struct BurnDriverD BurnDrvMDmickey = {
	"g_mickey", NULL, NULL, "1990",
	"I Love Mickey Mouse - Fushigi no Oshiro Dai Bouken (J) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mickeyRomInfo, mickeyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Immorta

static struct BurnRomInfo immorjRomDesc[]={
	{ "g_immorj.bin", 0x200000, 0xC99FAD92, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(immorj);
STD_ROM_FN(immorj);

struct BurnDriverD BurnDrvMDimmorj = {
	"g_immorj", NULL, NULL, "1900",
	"Immorta\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, immorjRomInfo, immorjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Joe Montana Sports Talk Football 2 (W) (REV00) [!]

static struct BurnRomInfo jmons2RomDesc[]={
	{ "g_jmons2.bin", 0x100000, 0xF2363A4A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jmons2);
STD_ROM_FN(jmons2);

struct BurnDriver BurnDrvMDjmons2 = {
	"g_jmons2", "g_jms2", NULL, "1900",
	"Joe Montana Sports Talk Football 2 (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jmons2RomInfo, jmons2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// John Madden Football (J) [!]

static struct BurnRomInfo madjRomDesc[]={
	{ "g_madj.bin", 0x080000, 0x0460611C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(madj);
STD_ROM_FN(madj);

struct BurnDriver BurnDrvMDmadj = {
	"g_madj", "g_ma", NULL, "1900",
	"John Madden Football (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, madjRomInfo, madjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jungle Boo

static struct BurnRomInfo jbookeRomDesc[]={
	{ "g_jbooke.bin", 0x200000, 0xB9709A99, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jbooke);
STD_ROM_FN(jbooke);

struct BurnDriverD BurnDrvMDjbooke = {
	"g_jbooke", NULL, NULL, "1900",
	"Jungle Boo\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jbookeRomInfo, jbookeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jungle Strike (J) [!]

static struct BurnRomInfo jstrjRomDesc[]={
	{ "g_jstrj.bin", 0x200000, 0xBA7A870B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jstrj);
STD_ROM_FN(jstrj);

struct BurnDriverD BurnDrvMDjstrj = {
	"g_jstrj", NULL, NULL, "1900",
	"Jungle Strike (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jstrjRomInfo, jstrjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King Colossus (J) [!]

static struct BurnRomInfo kingcjRomDesc[]={
	{ "g_kingcj.bin", 0x100000, 0xFFE7B3C7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kingcj);
STD_ROM_FN(kingcj);

struct BurnDriverD BurnDrvMDkingcj = {
	"g_kingcj", NULL, NULL, "1900",
	"King Colossus (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kingcjRomInfo, kingcjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Klax (J) [c][!]

static struct BurnRomInfo klaxjRomDesc[]={
	{ "g_klaxj.bin", 0x040000, 0x1AFCC1DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(klaxj);
STD_ROM_FN(klaxj);

struct BurnDriverD BurnDrvMDklaxj = {
	"g_klaxj", NULL, NULL, "1900",
	"Klax (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, klaxjRomInfo, klaxjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kujaku Ou 2 (J) [!]

static struct BurnRomInfo kujakuRomDesc[]={
	{ "g_kujaku.bin", 0x060000, 0xAFFD56BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kujaku);
STD_ROM_FN(kujaku);

struct BurnDriverD BurnDrvMDkujaku = {
	"g_kujaku", NULL, NULL, "1900",
	"Kujaku Ou 2 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kujakuRomInfo, kujakuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Krusty's Super Funhouse (UE) (REV00) [!]

static struct BurnRomInfo ksfh00RomDesc[]={
	{ "g_ksfh00.bin", 0x080000, 0xF764005E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ksfh00);
STD_ROM_FN(ksfh00);

struct BurnDriverD BurnDrvMDksfh00 = {
	"g_ksfh00", NULL, NULL, "1900",
	"Krusty's Super Funhouse (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ksfh00RomInfo, ksfh00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kuuga - Operation Vapor Trail (J) [!]

static struct BurnRomInfo kuugaRomDesc[]={
	{ "g_kuuga.bin", 0x100000, 0x83B6B6BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kuuga);
STD_ROM_FN(kuuga);

struct BurnDriverD BurnDrvMDkuuga = {
	"g_kuuga", NULL, NULL, "1900",
	"Kuuga - Operation Vapor Trail (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kuugaRomInfo, kuugaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kyuukyou Tiger (J) [!]

static struct BurnRomInfo kyuukyRomDesc[]={
	{ "g_kyuuky.bin", 0x0A0000, 0x61276D21, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kyuuky);
STD_ROM_FN(kyuuky);

struct BurnDriverD BurnDrvMDkyuuky = {
	"g_kyuuky", NULL, NULL, "1900",
	"Kyuukyou Tiger (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kyuukyRomInfo, kyuukyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - Koutei no Zaihou (J) [!]

static struct BurnRomInfo landsjRomDesc[]={
	{ "g_landsj.bin", 0x200000, 0x60D4CEDB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(landsj);
STD_ROM_FN(landsj);

struct BurnDriverD BurnDrvMDlandsj = {
	"g_landsj", NULL, NULL, "1994",
	"Landstalker - Koutei no Zaihou (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landsjRomInfo, landsjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - The Treasures of King Nole (E) [!]

static struct BurnRomInfo landseRomDesc[]={
	{ "g_landse.bin", 0x200000, 0xE3C65277, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(landse);
STD_ROM_FN(landse);

struct BurnDriverD BurnDrvMDlandse = {
	"g_landse", NULL, NULL, "1994",
	"Landstalker - The Treasures of King Nole (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landseRomInfo, landseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - The Treasures of King Nole (G) [!]

static struct BurnRomInfo landsgRomDesc[]={
	{ "g_landsg.bin", 0x200000, 0x10FEDB8F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(landsg);
STD_ROM_FN(landsg);

struct BurnDriverD BurnDrvMDlandsg = {
	"g_landsg", NULL, NULL, "1994",
	"Landstalker - The Treasures of King Nole (G) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landsgRomInfo, landsgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lemmings 2 - The Tribes (E) [!]

static struct BurnRomInfo lem2eRomDesc[]={
	{ "g_lem2e.bin", 0x200000, 0x741EB624, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lem2e);
STD_ROM_FN(lem2e);

struct BurnDriverD BurnDrvMDlem2e = {
	"g_lem2e", NULL, NULL, "1900",
	"Lemmings 2 - The Tribes (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lem2eRomInfo, lem2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lemmings (E) [!]

static struct BurnRomInfo lemeRomDesc[]={
	{ "g_leme.bin", 0x100000, 0x6A1A4579, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(leme);
STD_ROM_FN(leme);

struct BurnDriverD BurnDrvMDleme = {
	"g_leme", NULL, NULL, "1992",
	"Lemmings (E) [!]\0", NULL, "Psygnosis / Sunsoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lemeRomInfo, lemeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lemmings (JU) (REV00) [!]

static struct BurnRomInfo lem00RomDesc[]={
	{ "g_lem00.bin", 0x100000, 0xF015C2AD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lem00);
STD_ROM_FN(lem00);

struct BurnDriverD BurnDrvMDlem00 = {
	"g_lem00", NULL, NULL, "1992",
	"Lemmings (JU) (REV00) [!]\0", NULL, "Psygnosis / Sunsoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lem00RomInfo, lem00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lethal Enforcers (E) [!]

static struct BurnRomInfo lenfeRomDesc[]={
	{ "g_lenfe.bin", 0x200000, 0xCA2BF99D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lenfe);
STD_ROM_FN(lenfe);

struct BurnDriverD BurnDrvMDlenfe = {
	"g_lenfe", NULL, NULL, "1900",
	"Lethal Enforcers (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lenfeRomInfo, lenfeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lethal Enforcers (J) [!]

static struct BurnRomInfo lenfjRomDesc[]={
	{ "g_lenfj.bin", 0x200000, 0xF25F1E49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lenfj);
STD_ROM_FN(lenfj);

struct BurnDriverD BurnDrvMDlenfj = {
	"g_lenfj", NULL, NULL, "1900",
	"Lethal Enforcers (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lenfjRomInfo, lenfjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lightening Force - Quest for the Darkstar (U) [c][!]

static struct BurnRomInfo lighfrRomDesc[]={
	{ "g_lighfr.bin", 0x100000, 0xC8F8C0E0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lighfr);
STD_ROM_FN(lighfr);

struct BurnDriverD BurnDrvMDlighfr = {
	"g_lighfr", NULL, NULL, "1992",
	"Lightening Force - Quest for the Darkstar (U) [c][!]\0", NULL, "Tecnosoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lighfrRomInfo, lighfrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lord Monarch (J) [!]

static struct BurnRomInfo lordmoRomDesc[]={
	{ "g_lordmo.bin", 0x200000, 0x238BF5DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lordmo);
STD_ROM_FN(lordmo);

struct BurnDriverD BurnDrvMDlordmo = {
	"g_lordmo", NULL, NULL, "1900",
	"Lord Monarch (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lordmoRomInfo, lordmoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marko's Magic Football (E) (M4) [!]

static struct BurnRomInfo mmftbeRomDesc[]={
	{ "g_mmftbe.bin", 0x200000, 0x2307B905, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmftbe);
STD_ROM_FN(mmftbe);

struct BurnDriverD BurnDrvMDmmftbe = {
	"g_mmftbe", NULL, NULL, "1900",
	"Marko's Magic Football (E) (M4) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmftbeRomInfo, mmftbeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marsupilami (E) (M5) [!]

static struct BurnRomInfo marsueRomDesc[]={
	{ "g_marsue.bin", 0x200000, 0xE09BBD70, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(marsue);
STD_ROM_FN(marsue);

struct BurnDriverD BurnDrvMDmarsue = {
	"g_marsue", NULL, NULL, "1900",
	"Marsupilami (E) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, marsueRomInfo, marsueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mazin Saga (J) [!]

static struct BurnRomInfo mazijRomDesc[]={
	{ "g_mazij.bin", 0x100000, 0x45B3A34B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mazij);
STD_ROM_FN(mazij);

struct BurnDriverD BurnDrvMDmazij = {
	"g_mazij", NULL, NULL, "1993",
	"Mazin Saga (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mazijRomInfo, mazijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Bomberman (UE) [a1][!]

static struct BurnRomInfo mbmbaRomDesc[]={
	{ "g_mbmba.bin", 0x100000, 0x54AB3BEB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mbmba);
STD_ROM_FN(mbmba);

struct BurnDriverD BurnDrvMDmbmba = {
	"g_mbmba", NULL, NULL, "1900",
	"Mega Bomberman (UE) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mbmbaRomInfo, mbmbaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Turrican (E) [!]

static struct BurnRomInfo mturreRomDesc[]={
	{ "g_mturre.bin", 0x100000, 0xB1D15D0F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mturre);
STD_ROM_FN(mturre);

struct BurnDriverD BurnDrvMDmturre = {
	"g_mturre", NULL, NULL, "1994",
	"Mega Turrican (E) [!]\0", NULL, "Data East / Factor 5", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mturreRomInfo, mturreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Michael Jackson's Moonwalker (W) (REV00) [!]

static struct BurnRomInfo mwlk00RomDesc[]={
	{ "g_mwlk00.bin", 0x080000, 0x6A70791B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mwlk00);
STD_ROM_FN(mwlk00);

struct BurnDriver BurnDrvMDmwlk00 = {
	"g_mwlk00", "g_mjmw", NULL, "1900",
	"Michael Jackson's Moonwalker (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mwlk00RomInfo, mwlk00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mighty Morphin Power Rangers - The Movie (E) [!]

static struct BurnRomInfo mmprmeRomDesc[]={
	{ "g_mmprme.bin", 0x200000, 0x254A4972, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmprme);
STD_ROM_FN(mmprme);

struct BurnDriverD BurnDrvMDmmprme = {
	"g_mmprme", NULL, NULL, "1900",
	"Mighty Morphin Power Rangers - The Movie (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmprmeRomInfo, mmprmeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mighty Morphin Power Rangers (E) [!]

static struct BurnRomInfo mmpreRomDesc[]={
	{ "g_mmpre.bin", 0x200000, 0x7F96E663, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmpre);
STD_ROM_FN(mmpre);

struct BurnDriverD BurnDrvMDmmpre = {
	"g_mmpre", NULL, NULL, "1900",
	"Mighty Morphin Power Rangers (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmpreRomInfo, mmpreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mortal Kombat 3 (E) [!]

static struct BurnRomInfo mk3eRomDesc[]={
	{ "g_mk3e.bin", 0x400000, 0xAF6DE3E8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mk3e);
STD_ROM_FN(mk3e);

struct BurnDriverD BurnDrvMDmk3e = {
	"g_mk3e", NULL, NULL, "1900",
	"Mortal Kombat 3 (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mk3eRomInfo, mk3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mortal Kombat (W) (REV00) [!]

static struct BurnRomInfo mk00RomDesc[]={
	{ "g_mk00.bin", 0x200000, 0x1AA3A207, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mk00);
STD_ROM_FN(mk00);

struct BurnDriverD BurnDrvMDmk00 = {
	"g_mk00", NULL, NULL, "1900",
	"Mortal Kombat (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mk00RomInfo, mk00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Musha Aleste - Full Metal Fighter Ellinor (J) [!]

static struct BurnRomInfo mushajRomDesc[]={
	{ "g_mushaj.bin", 0x080000, 0x8FDE18AB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mushaj);
STD_ROM_FN(mushaj);

struct BurnDriverD BurnDrvMDmushaj = {
	"g_mushaj", NULL, NULL, "1900",
	"Musha Aleste - Full Metal Fighter Ellinor (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mushajRomInfo, mushajRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Hang Time (E) [!]

static struct BurnRomInfo nbahteRomDesc[]={
	{ "g_nbahte.bin", 0x300000, 0xEDB4D4AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbahte);
STD_ROM_FN(nbahte);

struct BurnDriverD BurnDrvMDnbahte = {
	"g_nbahte", NULL, NULL, "1900",
	"NBA Hang Time (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbahteRomInfo, nbahteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Jam (J) [!]

static struct BurnRomInfo nbajjRomDesc[]={
	{ "g_nbajj.bin", 0x200000, 0xA6C6305A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbajj);
STD_ROM_FN(nbajj);

struct BurnDriverD BurnDrvMDnbajj = {
	"g_nbajj", NULL, NULL, "1900",
	"NBA Jam (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbajjRomInfo, nbajjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Jam (UE) (REV00) [!]

static struct BurnRomInfo nbaj00RomDesc[]={
	{ "g_nbaj00.bin", 0x200000, 0x10FA248F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbaj00);
STD_ROM_FN(nbaj00);

struct BurnDriverD BurnDrvMDnbaj00 = {
	"g_nbaj00", NULL, NULL, "1900",
	"NBA Jam (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbaj00RomInfo, nbaj00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Jam Tournament Edition (W) (REV00) [!]

static struct BurnRomInfo nbajt0RomDesc[]={
	{ "g_nbajt0.bin", 0x300000, 0xE9FFCB37, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nbajt0);
STD_ROM_FN(nbajt0);

struct BurnDriverD BurnDrvMDnbajt0 = {
	"g_nbajt0", NULL, NULL, "1900",
	"NBA Jam Tournament Edition (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nbajt0RomInfo, nbajt0RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nigel Mansell's World Championship (U) [!]

static struct BurnRomInfo nigelRomDesc[]={
	{ "g_nigel.bin", 0x100000, 0x6BC57B2C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nigel);
STD_ROM_FN(nigel);

struct BurnDriverD BurnDrvMDnigel = {
	"g_nigel", NULL, NULL, "1900",
	"Nigel Mansell's World Championship (U) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nigelRomInfo, nigelRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ooz

static struct BurnRomInfo oozeeRomDesc[]={
	{ "g_oozee.bin", 0x100000, 0xE16B102C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(oozee);
STD_ROM_FN(oozee);

struct BurnDriverD BurnDrvMDoozee = {
	"g_oozee", NULL, NULL, "1900",
	"Ooz\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, oozeeRomInfo, oozeeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRun 2019 (E) [!]

static struct BurnRomInfo g_2019eRomDesc[]={
	{ "g_2019e.bin", 0x100000, 0x5CB3536A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2019e);
STD_ROM_FN(g_2019e);

struct BurnDriverD BurnDrvMDg_2019e = {
	"g_2019e", "g_or20", NULL, "1993",
	"OutRun 2019 (E) [!]\0", NULL, "Sims", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2019eRomInfo, g_2019eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRun 2019 (J) [!]

static struct BurnRomInfo g_2019jRomDesc[]={
	{ "g_2019j.bin", 0x100000, 0x0EAC7440, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2019j);
STD_ROM_FN(g_2019j);

struct BurnDriverD BurnDrvMDg_2019j = {
	"g_2019j", "g_or20", NULL, "1993",
	"OutRun 2019 (J) [!]\0", NULL, "Sims", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2019jRomInfo, g_2019jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRun (J) [!]

static struct BurnRomInfo orunjRomDesc[]={
	{ "g_orunj.bin", 0x100000, 0xEE7D9F4A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(orunj);
STD_ROM_FN(orunj);

struct BurnDriverD BurnDrvMDorunj = {
	"g_orunj", NULL, NULL, "1900",
	"OutRun (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, orunjRomInfo, orunjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRunners (J) [!]

static struct BurnRomInfo orunrjRomDesc[]={
	{ "g_orunrj.bin", 0x200000, 0xE164A09F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(orunrj);
STD_ROM_FN(orunrj);

struct BurnDriverD BurnDrvMDorunrj = {
	"g_orunrj", NULL, NULL, "199?",
	"OutRunners (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, orunrjRomInfo, orunrjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star - The End of the Millenium (J) [!]

static struct BurnRomInfo pstr4jRomDesc[]={
	{ "g_pstr4j.bin", 0x300000, 0xF0BFAD42, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pstr4j);
STD_ROM_FN(pstr4j);

struct BurnDriverD BurnDrvMDpstr4j = {
	"g_pstr4j", NULL, NULL, "1994",
	"Phantasy Star - The End of the Millenium (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pstr4jRomInfo, pstr4jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II (J) [!]

static struct BurnRomInfo pstr2jRomDesc[]={
	{ "g_pstr2j.bin", 0x0C0000, 0xBEC8EB5A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pstr2j);
STD_ROM_FN(pstr2j);

struct BurnDriverD BurnDrvMDpstr2j = {
	"g_pstr2j", NULL, NULL, "1989",
	"Phantasy Star II (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pstr2jRomInfo, pstr2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star III - Toki no Keishousha (J) [!]

static struct BurnRomInfo pstr3jRomDesc[]={
	{ "g_pstr3j.bin", 0x0C0000, 0x6C48C06F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pstr3j);
STD_ROM_FN(pstr3j);

struct BurnDriverD BurnDrvMDpstr3j = {
	"g_pstr3j", NULL, NULL, "1991",
	"Phantasy Star III - Toki no Keishousha (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pstr3jRomInfo, pstr3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantom 2040 (E) [!]

static struct BurnRomInfo g_2040eRomDesc[]={
	{ "g_2040e.bin", 0x200000, 0xB024882E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2040e);
STD_ROM_FN(g_2040e);

struct BurnDriverD BurnDrvMDg_2040e = {
	"g_2040e", "g_2040", NULL, "1900",
	"Phantom 2040 (E) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2040eRomInfo, g_2040eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pitfall - The Mayan Adventure (E) [!]

static struct BurnRomInfo pitfeRomDesc[]={
	{ "g_pitfe.bin", 0x200000, 0xC9198E19, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pitfe);
STD_ROM_FN(pitfe);

struct BurnDriverD BurnDrvMDpitfe = {
	"g_pitfe", NULL, NULL, "1900",
	"Pitfall - The Mayan Adventure (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pitfeRomInfo, pitfeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pit Fighter (UE) (Jun 1991) [!]

static struct BurnRomInfo pifiaRomDesc[]={
	{ "g_pifia.bin", 0x100000, 0x1E0E0831, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pifia);
STD_ROM_FN(pifia);

struct BurnDriverD BurnDrvMDpifia = {
	"g_pifia", NULL, NULL, "1900",
	"Pit Fighter (UE) (Jun 1991) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pifiaRomInfo, pifiaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pocahontas (E) [!]

static struct BurnRomInfo pocaeRomDesc[]={
	{ "g_pocae.bin", 0x400000, 0x165E7987, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pocae);
STD_ROM_FN(pocae);

struct BurnDriverD BurnDrvMDpocae = {
	"g_pocae", NULL, NULL, "1900",
	"Pocahontas (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pocaeRomInfo, pocaeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Populous (E) [!]

static struct BurnRomInfo popueRomDesc[]={
	{ "g_popue.bin", 0x080000, 0x83D56F64, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(popue);
STD_ROM_FN(popue);

struct BurnDriverD BurnDrvMDpopue = {
	"g_popue", NULL, NULL, "1900",
	"Populous (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, popueRomInfo, popueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Populous (J) [!]

static struct BurnRomInfo popujRomDesc[]={
	{ "g_popuj.bin", 0x080000, 0x97C26818, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(popuj);
STD_ROM_FN(popuj);

struct BurnDriverD BurnDrvMDpopuj = {
	"g_popuj", NULL, NULL, "1900",
	"Populous (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, popujRomInfo, popujRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Power Monger (J) [!]

static struct BurnRomInfo pmonjRomDesc[]={
	{ "g_pmonj.bin", 0x100000, 0x553289B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pmonj);
STD_ROM_FN(pmonj);

struct BurnDriverD BurnDrvMDpmonj = {
	"g_pmonj", NULL, NULL, "1900",
	"Power Monger (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pmonjRomInfo, pmonjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Probotector (E) [!]

static struct BurnRomInfo probotRomDesc[]={
	{ "g_probot.bin", 0x200000, 0xBC597D48, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(probot);
STD_ROM_FN(probot);

struct BurnDriverD BurnDrvMDprobot = {
	"g_probot", NULL, NULL, "1994",
	"Probotector (E) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, probotRomInfo, probotRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Psycho Pinball (E) (Sep 1994) (M5) [c][!]

static struct BurnRomInfo ppinaRomDesc[]={
	{ "g_ppina.bin", 0x180000, 0x11E9C3F2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ppina);
STD_ROM_FN(ppina);

struct BurnDriverD BurnDrvMDppina = {
	"g_ppina", NULL, NULL, "1900",
	"Psycho Pinball (E) (Sep 1994) (M5) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ppinaRomInfo, ppinaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puyo Puyo Tsu (J) (REV00) [!]

static struct BurnRomInfo puy200RomDesc[]={
	{ "g_puy200.bin", 0x200000, 0x51AD7797, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puy200);
STD_ROM_FN(puy200);

struct BurnDriverD BurnDrvMDpuy200 = {
	"g_puy200", NULL, NULL, "1900",
	"Puyo Puyo Tsu (J) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puy200RomInfo, puy200RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ren and Stimpy Sho

static struct BurnRomInfo rensteRomDesc[]={
	{ "g_renste.bin", 0x100000, 0xC276C220, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(renste);
STD_ROM_FN(renste);

struct BurnDriverD BurnDrvMDrenste = {
	"g_renste", NULL, NULL, "1900",
	"Ren and Stimpy Sho\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rensteRomInfo, rensteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Rash II (J) [!]

static struct BurnRomInfo rrsh2jRomDesc[]={
	{ "g_rrsh2j.bin", 0x100000, 0x9A5723B6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrsh2j);
STD_ROM_FN(rrsh2j);

struct BurnDriverD BurnDrvMDrrsh2j = {
	"g_rrsh2j", NULL, NULL, "1992",
	"Road Rash II (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrsh2jRomInfo, rrsh2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Rash II (UE) (REV02) [c][!]

static struct BurnRomInfo rrsh22RomDesc[]={
	{ "g_rrsh22.bin", 0x100000, 0x0876E992, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrsh22);
STD_ROM_FN(rrsh22);

struct BurnDriverD BurnDrvMDrrsh22 = {
	"g_rrsh22", NULL, NULL, "1992",
	"Road Rash II (UE) (REV02) [c][!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrsh22RomInfo, rrsh22RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Runark (J) [!]

static struct BurnRomInfo runarkRomDesc[]={
	{ "g_runark.bin", 0x080000, 0x0894D8FB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(runark);
STD_ROM_FN(runark);

struct BurnDriverD BurnDrvMDrunark = {
	"g_runark", NULL, NULL, "1900",
	"Runark (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, runarkRomInfo, runarkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ryuuko no Ken (J) [!]

static struct BurnRomInfo ryuukoRomDesc[]={
	{ "g_ryuuko.bin", 0x200000, 0x054CF5F6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ryuuko);
STD_ROM_FN(ryuuko);

struct BurnDriver BurnDrvMDryuuko = {
	"g_ryuuko", "g_aof", NULL, "1994",
	"Ryuuko no Ken (J) [!]\0", NULL, "SNK / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ryuukoRomInfo, ryuukoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Samurai Shodown (E) [c][!]

static struct BurnRomInfo samsheRomDesc[]={
	{ "g_samshe.bin", 0x300000, 0xC972014F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(samshe);
STD_ROM_FN(samshe);

struct BurnDriverD BurnDrvMDsamshe = {
	"g_samshe", NULL, NULL, "1994",
	"Samurai Shodown (E) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, samsheRomInfo, samsheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Samurai Spirits (J) [!]

static struct BurnRomInfo samspiRomDesc[]={
	{ "g_samspi.bin", 0x300000, 0x0EA2AE36, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(samspi);
STD_ROM_FN(samspi);

struct BurnDriverD BurnDrvMDsamspi = {
	"g_samspi", NULL, NULL, "1994",
	"Samurai Spirits (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, samspiRomInfo, samspiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shinobi III - Return of the Ninja Master (E) [c][!]

static struct BurnRomInfo shin3eRomDesc[]={
	{ "g_shin3e.bin", 0x100000, 0x0B6D3EB5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shin3e);
STD_ROM_FN(shin3e);

struct BurnDriverD BurnDrvMDshin3e = {
	"g_shin3e", NULL, NULL, "1993",
	"Shinobi III - Return of the Ninja Master (E) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shin3eRomInfo, shin3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Side Pocket (E) [!]

static struct BurnRomInfo sidepeRomDesc[]={
	{ "g_sidepe.bin", 0x100000, 0x36E08145, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sidepe);
STD_ROM_FN(sidepe);

struct BurnDriverD BurnDrvMDsidepe = {
	"g_sidepe", NULL, NULL, "1900",
	"Side Pocket (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sidepeRomInfo, sidepeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Simpsons, The - Bart vs The Space Mutants (UE) (REV00) [!]

static struct BurnRomInfo bart00RomDesc[]={
	{ "g_bart00.bin", 0x080000, 0xC8620574, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bart00);
STD_ROM_FN(bart00);

struct BurnDriver BurnDrvMDbart00 = {
	"g_bart00", "g_bart", NULL, "1900",
	"Simpsons, The - Bart vs The Space Mutants (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bart00RomInfo, bart00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soleil (F) [!]

static struct BurnRomInfo soleifRomDesc[]={
	{ "g_soleif.bin", 0x200000, 0x08DC1EAD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soleif);
STD_ROM_FN(soleif);

struct BurnDriverD BurnDrvMDsoleif = {
	"g_soleif", NULL, NULL, "1994",
	"Soleil (F) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soleifRomInfo, soleifRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soleil (G) [!]

static struct BurnRomInfo soleigRomDesc[]={
	{ "g_soleig.bin", 0x200000, 0x332B9ECD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soleig);
STD_ROM_FN(soleig);

struct BurnDriverD BurnDrvMDsoleig = {
	"g_soleig", NULL, NULL, "1994",
	"Soleil (G) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soleigRomInfo, soleigRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Spinball (E) [!]

static struct BurnRomInfo sonseRomDesc[]={
	{ "g_sonse.bin", 0x100000, 0xAEA0786D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sonse);
STD_ROM_FN(sonse);

struct BurnDriverD BurnDrvMDsonse = {
	"g_sonse", "g_sons", NULL, "1993",
	"Sonic Spinball (E) [!]\0", "No sound in-game", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sonseRomInfo, sonseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Spinball (J) [!]

static struct BurnRomInfo sonsjRomDesc[]={
	{ "g_sonsj.bin", 0x100000, 0xACD08CE8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sonsj);
STD_ROM_FN(sonsj);

struct BurnDriverD BurnDrvMDsonsj = {
	"g_sonsj", "g_sons", NULL, "1993",
	"Sonic Spinball (J) [!]\0", "No sound in-game", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sonsjRomInfo, sonsjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 2 (W) (REV00) [!]

static struct BurnRomInfo son200RomDesc[]={
	{ "g_son200.bin", 0x100000, 0x24AB4C3A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son200);
STD_ROM_FN(son200);

struct BurnDriver BurnDrvMDson200 = {
	"g_son200", "g_son2", NULL, "1992",
	"Sonic The Hedgehog 2 (W) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son200RomInfo, son200RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 3 (E) [!]

static struct BurnRomInfo son3eRomDesc[]={
	{ "g_son3e.bin", 0x200000, 0x6A632503, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son3e);
STD_ROM_FN(son3e);

struct BurnDriver BurnDrvMDson3e = {
	"g_son3e", "g_son3", NULL, "1994",
	"Sonic The Hedgehog 3 (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son3eRomInfo, son3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 3 (J) [!]

static struct BurnRomInfo son3jRomDesc[]={
	{ "g_son3j.bin", 0x200000, 0xF4951D1F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(son3j);
STD_ROM_FN(son3j);

struct BurnDriver BurnDrvMDson3j = {
	"g_son3j", "g_son3", NULL, "1994",
	"Sonic The Hedgehog 3 (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, son3jRomInfo, son3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog (W) (REV00) [!]

static struct BurnRomInfo soni00RomDesc[]={
	{ "g_soni00.bin", 0x080000, 0xF9394E97, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soni00);
STD_ROM_FN(soni00);

struct BurnDriver BurnDrvMDsoni00 = {
	"g_soni00", "g_soni", NULL, "1991",
	"Sonic The Hedgehog (W) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soni00RomInfo, soni00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sorcerian (J) [!]

static struct BurnRomInfo sorcerRomDesc[]={
	{ "g_sorcer.bin", 0x080000, 0xA143A8C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sorcer);
STD_ROM_FN(sorcer);

struct BurnDriverD BurnDrvMDsorcer = {
	"g_sorcer", NULL, NULL, "1900",
	"Sorcerian (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sorcerRomInfo, sorcerRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Space Funky B.O.B. (J) [!]

static struct BurnRomInfo sfbobRomDesc[]={
	{ "g_sfbob.bin", 0x100000, 0xE9310D3B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sfbob);
STD_ROM_FN(sfbob);

struct BurnDriverD BurnDrvMDsfbob = {
	"g_sfbob", "g_bob", NULL, "1994",
	"Space Funky B.O.B. (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sfbobRomInfo, sfbobRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Space Invaders 90 (J) [c][!]

static struct BurnRomInfo si90RomDesc[]={
	{ "g_si90.bin", 0x040000, 0x22ADBD66, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(si90);
STD_ROM_FN(si90);

struct BurnDriverD BurnDrvMDsi90 = {
	"g_si90", NULL, NULL, "1900",
	"Space Invaders 90 (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, si90RomInfo, si90RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Fighter II' - Special Champion Edition (E) [!]

static struct BurnRomInfo sf2eRomDesc[]={
	{ "g_sf2e.bin", 0x300000, 0x56D41136, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sf2e);
STD_ROM_FN(sf2e);

struct BurnDriverD BurnDrvMDsf2e = {
	"g_sf2e", NULL, NULL, "1900",
	"Street Fighter II' - Special Champion Edition (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sf2eRomInfo, sf2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Fighter II' Plus - Champion Edition (J) [!]

static struct BurnRomInfo sf2jRomDesc[]={
	{ "g_sf2j.bin", 0x300000, 0x2E487EE3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sf2j);
STD_ROM_FN(sf2j);

struct BurnDriverD BurnDrvMDsf2j = {
	"g_sf2j", NULL, NULL, "1900",
	"Street Fighter II' Plus - Champion Edition (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sf2jRomInfo, sf2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage 2 (JE) [!]

static struct BurnRomInfo sor2jeRomDesc[]={
	{ "g_sor2je.bin", 0x200000, 0x42E3EFDC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor2je);
STD_ROM_FN(sor2je);

struct BurnDriver BurnDrvMDsor2je = {
	"g_sor2je", "g_sor2", NULL, "1992",
	"Streets of Rage 2 (JE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor2jeRomInfo, sor2jeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage 3 (E) (Apr 1994) [!]

static struct BurnRomInfo sor3eRomDesc[]={
	{ "g_sor3e.bin", 0x300000, 0x3B78135F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor3e);
STD_ROM_FN(sor3e);

struct BurnDriver BurnDrvMDsor3e = {
	"g_sor3e", "g_sor3", NULL, "1994",
	"Streets of Rage 3 (E) (Apr 1994) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor3eRomInfo, sor3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage 3 (E) (May 1994) [!]

static struct BurnRomInfo sor3eaRomDesc[]={
	{ "g_sor3ea.bin", 0x300000, 0x90EF991E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor3ea);
STD_ROM_FN(sor3ea);

struct BurnDriver BurnDrvMDsor3ea = {
	"g_sor3ea", "g_sor3", NULL, "1994",
	"Streets of Rage 3 (E) (May 1994) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor3eaRomInfo, sor3eaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Streets of Rage (W) (REV00) [!]

static struct BurnRomInfo sor00RomDesc[]={
	{ "g_sor00.bin", 0x080000, 0xBFF227C6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sor00);
STD_ROM_FN(sor00);

struct BurnDriver BurnDrvMDsor00 = {
	"g_sor00", "g_sor", NULL, "1991",
	"Streets of Rage (W) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sor00RomInfo, sor00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Strider II (E) [c][!]

static struct BurnRomInfo strid2RomDesc[]={
	{ "g_strid2.bin", 0x100000, 0xE85E5270, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(strid2);
STD_ROM_FN(strid2);

struct BurnDriverD BurnDrvMDstrid2 = {
	"g_strid2", NULL, NULL, "1994",
	"Strider II (E) [c][!]\0", NULL, "Tiertex / Capcom / US Gold", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, strid2RomInfo, strid2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super HQ (J) [!]

static struct BurnRomInfo suphqRomDesc[]={
	{ "g_suphq.bin", 0x080000, 0xAB2C52B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(suphq);
STD_ROM_FN(suphq);

struct BurnDriverD BurnDrvMDsuphq = {
	"g_suphq", NULL, NULL, "1900",
	"Super HQ (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, suphqRomInfo, suphqRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Talmit's Adventure (E) [!]

static struct BurnRomInfo talmitRomDesc[]={
	{ "g_talmit.bin", 0x100000, 0x05DC3FFC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(talmit);
STD_ROM_FN(talmit);

struct BurnDriverD BurnDrvMDtalmit = {
	"g_talmit", NULL, NULL, "1900",
	"Talmit's Adventure (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, talmitRomInfo, talmitRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Terminato

static struct BurnRomInfo termeRomDesc[]={
	{ "g_terme.bin", 0x100000, 0x15F4D302, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(terme);
STD_ROM_FN(terme);

struct BurnDriverD BurnDrvMDterme = {
	"g_terme", NULL, NULL, "1900",
	"Terminato\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, termeRomInfo, termeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Force II MD (J) [!]

static struct BurnRomInfo tf2mdRomDesc[]={
	{ "g_tf2md.bin", 0x080000, 0xE75EC3E0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tf2md);
STD_ROM_FN(tf2md);

struct BurnDriverD BurnDrvMDtf2md = {
	"g_tf2md", NULL, NULL, "1900",
	"Thunder Force II MD (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tf2mdRomInfo, tf2mdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Force IV (E) [c][!]

static struct BurnRomInfo tf4eRomDesc[]={
	{ "g_tf4e.bin", 0x100000, 0xE7E3C05B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tf4e);
STD_ROM_FN(tf4e);

struct BurnDriverD BurnDrvMDtf4e = {
	"g_tf4e", NULL, NULL, "1992",
	"Thunder Force IV (E) [c][!]\0", NULL, "Tecnosoft", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tf4eRomInfo, tf4eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl (U) (REV00) [!]

static struct BurnRomInfo tje00RomDesc[]={
	{ "g_tje00.bin", 0x100000, 0xD1B36786, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje00);
STD_ROM_FN(tje00);

struct BurnDriver BurnDrvMDtje00 = {
	"g_tje00", NULL, NULL, "1991",
	"Toejam & Earl (U) (REV00) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tje00RomInfo, tje00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl in Panic on Funkotron (E) [!]

static struct BurnRomInfo tje2eRomDesc[]={
	{ "g_tje2e.bin", 0x200000, 0x47B0A871, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje2e);
STD_ROM_FN(tje2e);

struct BurnDriverD BurnDrvMDtje2e = {
	"g_tje2e", NULL, NULL, "1993",
	"Toejam & Earl in Panic on Funkotron (E) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tje2eRomInfo, tje2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl in Panic on Funkotron (G) [!]

static struct BurnRomInfo tje2gRomDesc[]={
	{ "g_tje2g.bin", 0x200000, 0x4081B9F2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje2g);
STD_ROM_FN(tje2g);

struct BurnDriverD BurnDrvMDtje2g = {
	"g_tje2g", NULL, NULL, "1993",
	"Toejam & Earl in Panic on Funkotron (G) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tje2gRomInfo, tje2gRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toejam & Earl in Panic on Funkotron (J) [!]

static struct BurnRomInfo tje2jRomDesc[]={
	{ "g_tje2j.bin", 0x200000, 0xE1B36850, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tje2j);
STD_ROM_FN(tje2j);

struct BurnDriverD BurnDrvMDtje2j = {
	"g_tje2j", NULL, NULL, "1993",
	"Toejam & Earl in Panic on Funkotron (J) [!]\0", NULL, "Sega / JVP", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tje2jRomInfo, tje2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Toy Story (E) [!]

static struct BurnRomInfo toysteRomDesc[]={
	{ "g_toyste.bin", 0x400000, 0x8E89A9F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toyste);
STD_ROM_FN(toyste);

struct BurnDriverD BurnDrvMDtoyste = {
	"g_toyste", NULL, NULL, "1900",
	"Toy Story (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toysteRomInfo, toysteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ultimate Mortal Kombat 3 (E) [!]

static struct BurnRomInfo umk3eRomDesc[]={
	{ "g_umk3e.bin", 0x400000, 0xECFB5CB4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(umk3e);
STD_ROM_FN(umk3e);

struct BurnDriverD BurnDrvMDumk3e = {
	"g_umk3e", NULL, NULL, "1900",
	"Ultimate Mortal Kombat 3 (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, umk3eRomInfo, umk3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vampire Killer (J) [!]

static struct BurnRomInfo vamkilRomDesc[]={
	{ "g_vamkil.bin", 0x100000, 0x91B57D2B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vamkil);
STD_ROM_FN(vamkil);

struct BurnDriverD BurnDrvMDvamkil = {
	"g_vamkil", NULL, NULL, "1994",
	"Vampire Killer (J) [!]\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vamkilRomInfo, vamkilRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wardner no Mori Special (J) [!]

static struct BurnRomInfo wardjRomDesc[]={
	{ "g_wardj.bin", 0x080000, 0x80F1035C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wardj);
STD_ROM_FN(wardj);

struct BurnDriverD BurnDrvMDwardj = {
	"g_wardj", NULL, NULL, "1900",
	"Wardner no Mori Special (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wardjRomInfo, wardjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Where in the World is Carmen Sandiego (B) (M2) [!]

static struct BurnRomInfo wwicsRomDesc[]={
	{ "g_wwics.bin", 0x100000, 0x7D4450AD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wwics);
STD_ROM_FN(wwics);

struct BurnDriverD BurnDrvMDwwics = {
	"g_wwics", NULL, NULL, "1900",
	"Where in the World is Carmen Sandiego (B) (M2) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wwicsRomInfo, wwicsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Where in Time is Carmen Sandiego (B) [!]

static struct BurnRomInfo wticsRomDesc[]={
	{ "g_wtics.bin", 0x100000, 0xD523B552, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wtics);
STD_ROM_FN(wtics);

struct BurnDriverD BurnDrvMDwtics = {
	"g_wtics", NULL, NULL, "1900",
	"Where in Time is Carmen Sandiego (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wticsRomInfo, wticsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Where in Time is Carmen Sandiego (UE) (M5) [!]

static struct BurnRomInfo wticsaRomDesc[]={
	{ "g_wticsa.bin", 0x100000, 0xEA19D4A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wticsa);
STD_ROM_FN(wticsa);

struct BurnDriverD BurnDrvMDwticsa = {
	"g_wticsa", NULL, NULL, "1900",
	"Where in Time is Carmen Sandiego (UE) (M5) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wticsaRomInfo, wticsaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Whip Rush 2222 AD (J) [!]

static struct BurnRomInfo whipjRomDesc[]={
	{ "g_whipj.bin", 0x080000, 0x8084B4D1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(whipj);
STD_ROM_FN(whipj);

struct BurnDriverD BurnDrvMDwhipj = {
	"g_whipj", NULL, NULL, "1900",
	"Whip Rush 2222 AD (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, whipjRomInfo, whipjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wings of Wor (U) [!]

static struct BurnRomInfo winworRomDesc[]={
	{ "g_winwor.bin", 0x080000, 0x210A2FCD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(winwor);
STD_ROM_FN(winwor);

struct BurnDriverD BurnDrvMDwinwor = {
	"g_winwor", NULL, NULL, "1991",
	"Wings of Wor (U) [!]\0", NULL, "NCS / Dreamworks", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, winworRomInfo, winworRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wiz 'n' Liz - The Frantic Wabbit Wescue (E) [!]

static struct BurnRomInfo wizlieRomDesc[]={
	{ "g_wizlie.bin", 0x100000, 0xF09353B4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wizlie);
STD_ROM_FN(wizlie);

struct BurnDriverD BurnDrvMDwizlie = {
	"g_wizlie", NULL, NULL, "1900",
	"Wiz 'n' Liz - The Frantic Wabbit Wescue (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wizlieRomInfo, wizlieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zombies (E) [!]

static struct BurnRomInfo zombeRomDesc[]={
	{ "g_zombe.bin", 0x100000, 0x179A1AA2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zombe);
STD_ROM_FN(zombe);

struct BurnDriverD BurnDrvMDzombe = {
	"g_zombe", NULL, NULL, "1900",
	"Zombies (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zombeRomInfo, zombeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zool (E) [!]

static struct BurnRomInfo zooleRomDesc[]={
	{ "g_zoole.bin", 0x100000, 0x1EE58B03, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zoole);
STD_ROM_FN(zoole);

struct BurnDriverD BurnDrvMDzoole = {
	"g_zoole", NULL, NULL, "1900",
	"Zool (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zooleRomInfo, zooleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zoop (E) [!]

static struct BurnRomInfo zoopeRomDesc[]={
	{ "g_zoope.bin", 0x080000, 0x2FDAC6AB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zoope);
STD_ROM_FN(zoope);

struct BurnDriverD BurnDrvMDzoope = {
	"g_zoope", NULL, NULL, "1900",
	"Zoop (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zoopeRomInfo, zoopeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zou! Zou! Zou! Rescue Daisenryaku (J) [!]

static struct BurnRomInfo zouzouRomDesc[]={
	{ "g_zouzou.bin", 0x080000, 0x1A761E67, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zouzou);
STD_ROM_FN(zouzou);

struct BurnDriverD BurnDrvMDzouzou = {
	"g_zouzou", NULL, NULL, "1992",
	"Zou! Zou! Zou! Rescue Daisenryaku (J) [!]\0", NULL, "Electronic Arts / Vectordean", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zouzouRomInfo, zouzouRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zero the Kamikaze Squirrel (E) [!]

static struct BurnRomInfo ztkseRomDesc[]={
	{ "g_ztkse.bin", 0x200000, 0x45FF0B4B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ztkse);
STD_ROM_FN(ztkse);

struct BurnDriverD BurnDrvMDztkse = {
	"g_ztkse", NULL, NULL, "1900",
	"Zero the Kamikaze Squirrel (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ztkseRomInfo, ztkseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// 007 Shitou (J) [!]

static struct BurnRomInfo g_007RomDesc[]={
	{ "g_007.bin", 0x080000, 0xAEB4B262, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_007);
STD_ROM_FN(g_007);

struct BurnDriver BurnDrvMDg_007 = {
	"g_007", "g_bond", NULL, "1993",
	"007 Shitou (J) [!]\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_007RomInfo, g_007RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Adventures of Batman and Robi

static struct BurnRomInfo abateRomDesc[]={
	{ "g_abate.bin", 0x200000, 0x355E8C39, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abate);
STD_ROM_FN(abate);

struct BurnDriverD BurnDrvMDabate = {
	"g_abate", "g_abat", NULL, "1995",
	"Adventures of Batman and Robi\0", "No Sound", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abateRomInfo, abateRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aero Blasters (J) [!]

static struct BurnRomInfo aeroblRomDesc[]={
	{ "g_aerobl.bin", 0x080000, 0xA00DA987, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aerobl);
STD_ROM_FN(aerobl);

struct BurnDriver BurnDrvMDaerobl = {
	"g_aerobl", "g_abus", NULL, "1900",
	"Aero Blasters (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aeroblRomInfo, aeroblRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aero the Acro-Bat 2 (E) [!]

static struct BurnRomInfo acro2eRomDesc[]={
	{ "g_acro2e.bin", 0x200000, 0xA451F9A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(acro2e);
STD_ROM_FN(acro2e);

struct BurnDriverD BurnDrvMDacro2e = {
	"g_acro2e", "g_acr2", NULL, "1994",
	"Aero the Acro-Bat 2 (E) [!]\0", "Bad sound", "Sunsoft / Iguana", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, acro2eRomInfo, acro2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// After Burner II (J) [!]

static struct BurnRomInfo abrn2jRomDesc[]={
	{ "g_abrn2j.bin", 0x080000, 0x4FF37E66, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(abrn2j);
STD_ROM_FN(abrn2j);

struct BurnDriverD BurnDrvMDabrn2j = {
	"g_abrn2j", "g_abu2", NULL, "1900",
	"After Burner II (J) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, abrn2jRomInfo, abrn2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alex Kidd - Cheongongmaseong (K) [!]

static struct BurnRomInfo alexkkRomDesc[]={
	{ "g_alexkk.bin", 0x040000, 0x5B0678FB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alexkk);
STD_ROM_FN(alexkk);

struct BurnDriverD BurnDrvMDalexkk = {
	"g_alexkk", "g_alex", NULL, "1989",
	"Alex Kidd - Cheongongmaseong (K) [!]\0", "No sound", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alexkkRomInfo, alexkkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alex Kidd in the Enchanted Castle (E) (MD Bundle) [!]

static struct BurnRomInfo alxkebRomDesc[]={
	{ "g_alxkeb.bin", 0x040000, 0x778A0F00, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alxkeb);
STD_ROM_FN(alxkeb);

struct BurnDriverD BurnDrvMDalxkeb = {
	"g_alxkeb", "g_alex", NULL, "1989",
	"Alex Kidd in the Enchanted Castle (E) (MD Bundle) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alxkebRomInfo, alxkebRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alex Kidd in the Enchanted Castle (E) [!]

static struct BurnRomInfo alexkeRomDesc[]={
	{ "g_alexke.bin", 0x040000, 0xC3A52529, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alexke);
STD_ROM_FN(alexke);

struct BurnDriverD BurnDrvMDalexke = {
	"g_alexke", "g_alex", NULL, "1989",
	"Alex Kidd in the Enchanted Castle (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alexkeRomInfo, alexkeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alex Kidd in the Enchanted Castle (J) [!]

static struct BurnRomInfo alexkjRomDesc[]={
	{ "g_alexkj.bin", 0x040000, 0x8A5ED856, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(alexkj);
STD_ROM_FN(alexkj);

struct BurnDriverD BurnDrvMDalexkj = {
	"g_alexkj", "g_alex", NULL, "1989",
	"Alex Kidd in the Enchanted Castle (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, alexkjRomInfo, alexkjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Alien 3 (UE) (REV00) [!]

static struct BurnRomInfo ali300RomDesc[]={
	{ "g_ali300.bin", 0x080000, 0xA3B00D6E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ali300);
STD_ROM_FN(ali300);

struct BurnDriver BurnDrvMDali300 = {
	"g_ali300", "g_ali3", NULL, "1900",
	"Alien 3 (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ali300RomInfo, ali300RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Andre Agassi Tennis (E) (REV01) [c][!]

static struct BurnRomInfo aateeRomDesc[]={
	{ "g_aatee.bin", 0x080000, 0x224256C7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aatee);
STD_ROM_FN(aatee);

struct BurnDriverD BurnDrvMDaatee = {
	"g_aatee", "g_aate", NULL, "1900",
	"Andre Agassi Tennis (E) (REV01) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aateeRomInfo, aateeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Animaniacs (E) [!]

static struct BurnRomInfo animeRomDesc[]={
	{ "g_anime.bin", 0x100000, 0x92B6F255, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(anime);
STD_ROM_FN(anime);

struct BurnDriverD BurnDrvMDanime = {
	"g_anime", "g_anim", NULL, "1900",
	"Animaniacs (E) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, animeRomInfo, animeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arcus Odyssey (J) [!]

static struct BurnRomInfo arcusjRomDesc[]={
	{ "g_arcusj.bin", 0x100000, 0x41C5FB4F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arcusj);
STD_ROM_FN(arcusj);

struct BurnDriver BurnDrvMDarcusj = {
	"g_arcusj", "g_arcu", NULL, "1900",
	"Arcus Odyssey (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arcusjRomInfo, arcusjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Arrow Flash (J) [!]

static struct BurnRomInfo arrowjRomDesc[]={
	{ "g_arrowj.bin", 0x080000, 0xD49F8444, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arrowj);
STD_ROM_FN(arrowj);

struct BurnDriverD BurnDrvMDarrowj = {
	"g_arrowj", "g_arro", NULL, "1900",
	"Arrow Flash (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arrowjRomInfo, arrowjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Atomic Robo-Kid (J) [c][!]

static struct BurnRomInfo robokjRomDesc[]={
	{ "g_robokj.bin", 0x080000, 0xE833067E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robokj);
STD_ROM_FN(robokj);

struct BurnDriver BurnDrvMDrobokj = {
	"g_robokj", "g_akid", NULL, "1900",
	"Atomic Robo-Kid (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robokjRomInfo, robokjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Atomic Runner (E) [!]

static struct BurnRomInfo arunreRomDesc[]={
	{ "g_arunre.bin", 0x100000, 0xB3C05418, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(arunre);
STD_ROM_FN(arunre);

struct BurnDriver BurnDrvMDarunre = {
	"g_arunre", "g_arun", NULL, "1992",
	"Atomic Runner (E) [!]\0", NULL, "Data East", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, arunreRomInfo, arunreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ayrton Senna's Super Monaco GP II (JE) [!]

static struct BurnRomInfo smgp2aRomDesc[]={
	{ "g_smgp2a.bin", 0x100000, 0x60AF0F76, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smgp2a);
STD_ROM_FN(smgp2a);

struct BurnDriverD BurnDrvMDsmgp2a = {
	"g_smgp2a", NULL, NULL, "1900",
	"Ayrton Senna's Super Monaco GP II (JE) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smgp2aRomInfo, smgp2aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Back to the Future Part III (E) [!]

static struct BurnRomInfo bttfeRomDesc[]={
	{ "g_bttfe.bin", 0x080000, 0x2737F92E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bttfe);
STD_ROM_FN(bttfe);

struct BurnDriverD BurnDrvMDbttfe = {
	"g_bttfe", "g_bttf", NULL, "1900",
	"Back to the Future Part III (E) [!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bttfeRomInfo, bttfeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman (J) [!]

static struct BurnRomInfo batmnjRomDesc[]={
	{ "g_batmnj.bin", 0x080000, 0xD7B4FEBF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(batmnj);
STD_ROM_FN(batmnj);

struct BurnDriver BurnDrvMDbatmnj = {
	"g_batmnj", "g_bat", NULL, "1900",
	"Batman (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batmnjRomInfo, batmnjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beast Warriors (J) [!]

static struct BurnRomInfo beaswrRomDesc[]={
	{ "g_beaswr.bin", 0x100000, 0x4646C694, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beaswr);
STD_ROM_FN(beaswr);

struct BurnDriverD BurnDrvMDbeaswr = {
	"g_beaswr", "g_bwre", NULL, "1900",
	"Beast Warriors (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beaswrRomInfo, beaswrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beavis and Butt-head (E) [!]

static struct BurnRomInfo beaveRomDesc[]={
	{ "g_beave.bin", 0x200000, 0xC7B6435E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beave);
STD_ROM_FN(beave);

struct BurnDriver BurnDrvMDbeave = {
	"g_beave", "g_beav", NULL, "1900",
	"Beavis and Butt-head (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beaveRomInfo, beaveRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bram Stoker's Dracula (E) [!]

static struct BurnRomInfo draceRomDesc[]={
	{ "g_drace.bin", 0x100000, 0x9BA5A063, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drace);
STD_ROM_FN(drace);

struct BurnDriverD BurnDrvMDdrace = {
	"g_drace", NULL, NULL, "1994",
	"Bram Stoker's Dracula (E) [!]\0", NULL, "Psygnosis / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, draceRomInfo, draceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubba N Stix (E) [c][!]

static struct BurnRomInfo bubbaeRomDesc[]={
	{ "g_bubbae.bin", 0x100000, 0xB467432E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bubbae);
STD_ROM_FN(bubbae);

struct BurnDriverD BurnDrvMDbubbae = {
	"g_bubbae", "g_buba", NULL, "1900",
	"Bubba N Stix (E) [c][!]\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bubbaeRomInfo, bubbaeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Budokan - The Martial Spirit (E) [!]

static struct BurnRomInfo budoeRomDesc[]={
	{ "g_budoe.bin", 0x080000, 0x97ADD5BD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(budoe);
STD_ROM_FN(budoe);

struct BurnDriver BurnDrvMDbudoe = {
	"g_budoe", "g_budo", NULL, "1900",
	"Budokan - The Martial Spirit (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, budoeRomInfo, budoeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Burning Force (J) [!]

static struct BurnRomInfo burnfjRomDesc[]={
	{ "g_burnfj.bin", 0x080000, 0x0C1DEB47, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(burnfj);
STD_ROM_FN(burnfj);

struct BurnDriverD BurnDrvMDburnfj = {
	"g_burnfj", "g_burf", NULL, "1900",
	"Burning Force (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, burnfjRomInfo, burnfjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chelnov (J) [!]

static struct BurnRomInfo chelnoRomDesc[]={
	{ "g_chelno.bin", 0x100000, 0xB2FE74D8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chelno);
STD_ROM_FN(chelno);

struct BurnDriver BurnDrvMDchelno = {
	"g_chelno", "g_arun", NULL, "1992",
	"Chelnov (J) [!]\0", NULL, "Data East", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chelnoRomInfo, chelnoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck II - Son of Chuck (E) [c][!]

static struct BurnRomInfo chk2eRomDesc[]={
	{ "g_chk2e.bin", 0x100000, 0x1ADE9488, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chk2e);
STD_ROM_FN(chk2e);

struct BurnDriverD BurnDrvMDchk2e = {
	"g_chk2e", NULL, NULL, "1900",
	"Chuck II - Son of Chuck (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chk2eRomInfo, chk2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck II - Son of Chuck (J) [!]

static struct BurnRomInfo chk2jRomDesc[]={
	{ "g_chk2j.bin", 0x100000, 0xBFD24BE8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chk2j);
STD_ROM_FN(chk2j);

struct BurnDriverD BurnDrvMDchk2j = {
	"g_chk2j", NULL, NULL, "1900",
	"Chuck II - Son of Chuck (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chk2jRomInfo, chk2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck Rock (E) [c][!]

static struct BurnRomInfo chkrkeRomDesc[]={
	{ "g_chkrke.bin", 0x100000, 0x7CD40BEA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chkrke);
STD_ROM_FN(chkrke);

struct BurnDriverD BurnDrvMDchkrke = {
	"g_chkrke", NULL, NULL, "1900",
	"Chuck Rock (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chkrkeRomInfo, chkrkeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Columns (W) (REV00) [!]

static struct BurnRomInfo col00RomDesc[]={
	{ "g_col00.bin", 0x020000, 0x03163D7A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(col00);
STD_ROM_FN(col00);

struct BurnDriverD BurnDrvMDcol00 = {
	"g_col00", NULL, NULL, "1994",
	"Columns (W) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, col00RomInfo, col00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Columns III - Taiketsu! Columns World (J) [!]

static struct BurnRomInfo col3jRomDesc[]={
	{ "g_col3j.bin", 0x080000, 0xCD07462F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(col3j);
STD_ROM_FN(col3j);

struct BurnDriverD BurnDrvMDcol3j = {
	"g_col3j", NULL, NULL, "1994",
	"Columns III - Taiketsu! Columns World (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, col3jRomInfo, col3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crack Down (E) [!]

static struct BurnRomInfo crkdeRomDesc[]={
	{ "g_crkde.bin", 0x080000, 0xD012A47A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crkde);
STD_ROM_FN(crkde);

struct BurnDriverD BurnDrvMDcrkde = {
	"g_crkde", NULL, NULL, "1900",
	"Crack Down (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crkdeRomInfo, crkdeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crack Down (J) [!]

static struct BurnRomInfo crkdjRomDesc[]={
	{ "g_crkdj.bin", 0x080000, 0x538AAA5D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crkdj);
STD_ROM_FN(crkdj);

struct BurnDriverD BurnDrvMDcrkdj = {
	"g_crkdj", NULL, NULL, "1900",
	"Crack Down (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crkdjRomInfo, crkdjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crude Buster (J) [!]

static struct BurnRomInfo crudebRomDesc[]={
	{ "g_crudeb.bin", 0x100000, 0xAFFB4B00, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crudeb);
STD_ROM_FN(crudeb);

struct BurnDriverD BurnDrvMDcrudeb = {
	"g_crudeb", "g_2cd", NULL, "1900",
	"Crude Buster (J) [!]\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crudebRomInfo, crudebRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Crue Ball (J) [!]

static struct BurnRomInfo cruejRomDesc[]={
	{ "g_cruej.bin", 0x080000, 0x514C53E2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cruej);
STD_ROM_FN(cruej);

struct BurnDriverD BurnDrvMDcruej = {
	"g_cruej", NULL, NULL, "1992",
	"Crue Ball (J) [!]\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cruejRomInfo, cruejRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dino Land (J) [!]

static struct BurnRomInfo dinoljRomDesc[]={
	{ "g_dinolj.bin", 0x080000, 0x81F939DE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dinolj);
STD_ROM_FN(dinolj);

struct BurnDriverD BurnDrvMDdinolj = {
	"g_dinolj", NULL, NULL, "1900",
	"Dino Land (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dinoljRomInfo, dinoljRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Disney's Aladdin (Beta) [!]

static struct BurnRomInfo aladbRomDesc[]={
	{ "g_aladb.bin", 0x200000, 0x8C60EF73, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aladb);
STD_ROM_FN(aladb);

struct BurnDriverD BurnDrvMDaladb = {
	"g_aladb", "g_alad", NULL, "1993",
	"Disney's Aladdin (Beta) [!]\0", "No sound", "Disney / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aladbRomInfo, aladbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// DJ Boy (E) [!]

static struct BurnRomInfo djboyeRomDesc[]={
	{ "g_djboye.bin", 0x080000, 0x860E749A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(djboye);
STD_ROM_FN(djboye);

struct BurnDriverD BurnDrvMDdjboye = {
	"g_djboye", NULL, NULL, "1900",
	"DJ Boy (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, djboyeRomInfo, djboyeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// DJ Boy (J) [!]

static struct BurnRomInfo djboyjRomDesc[]={
	{ "g_djboyj.bin", 0x080000, 0x202ABAA8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(djboyj);
STD_ROM_FN(djboyj);

struct BurnDriverD BurnDrvMDdjboyj = {
	"g_djboyj", NULL, NULL, "1900",
	"DJ Boy (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, djboyjRomInfo, djboyjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dynamite Duke (W) [a1][!]

static struct BurnRomInfo ddukeaRomDesc[]={
	{ "g_ddukea.bin", 0x080000, 0x246F0BDA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ddukea);
STD_ROM_FN(ddukea);

struct BurnDriverD BurnDrvMDddukea = {
	"g_ddukea", NULL, NULL, "1900",
	"Dynamite Duke (W) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ddukeaRomInfo, ddukeaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO - The Tides of Time (E) [!]

static struct BurnRomInfo ecco2eRomDesc[]={
	{ "g_ecco2e.bin", 0x200000, 0x7B1BF89C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecco2e);
STD_ROM_FN(ecco2e);

struct BurnDriverD BurnDrvMDecco2e = {
	"g_ecco2e", NULL, NULL, "1994",
	"ECCO - The Tides of Time (E) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecco2eRomInfo, ecco2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO - The Tides of Time (J) [!]

static struct BurnRomInfo ecco2jRomDesc[]={
	{ "g_ecco2j.bin", 0x200000, 0x062D439C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecco2j);
STD_ROM_FN(ecco2j);

struct BurnDriverD BurnDrvMDecco2j = {
	"g_ecco2j", NULL, NULL, "1994",
	"ECCO - The Tides of Time (J) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecco2jRomInfo, ecco2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO Jr. (U) (REV01) [!]

static struct BurnRomInfo ecjr01RomDesc[]={
	{ "g_ecjr01.bin", 0x100000, 0x3C517975, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecjr01);
STD_ROM_FN(ecjr01);

struct BurnDriverD BurnDrvMDecjr01 = {
	"g_ecjr01", NULL, NULL, "1995",
	"ECCO Jr. (U) (REV01) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecjr01RomInfo, ecjr01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO The Dolphin (J) [!]

static struct BurnRomInfo eccodjRomDesc[]={
	{ "g_eccodj.bin", 0x100000, 0x6520304D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eccodj);
STD_ROM_FN(eccodj);

struct BurnDriverD BurnDrvMDeccodj = {
	"g_eccodj", NULL, NULL, "199?",
	"ECCO The Dolphin (J) [!]\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eccodjRomInfo, eccodjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// El Viento (J) [!]

static struct BurnRomInfo elvinjRomDesc[]={
	{ "g_elvinj.bin", 0x100000, 0x6091C36E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(elvinj);
STD_ROM_FN(elvinj);

struct BurnDriverD BurnDrvMDelvinj = {
	"g_elvinj", NULL, NULL, "1900",
	"El Viento (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, elvinjRomInfo, elvinjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Elemental Master (J) [!]

static struct BurnRomInfo elemjRomDesc[]={
	{ "g_elemj.bin", 0x080000, 0x5F553E29, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(elemj);
STD_ROM_FN(elemj);

struct BurnDriverD BurnDrvMDelemj = {
	"g_elemj", NULL, NULL, "1900",
	"Elemental Master (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, elemjRomInfo, elemjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESWAT Cyber Police (J) [!]

static struct BurnRomInfo eswatjRomDesc[]={
	{ "g_eswatj.bin", 0x080000, 0x87B636A2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(eswatj);
STD_ROM_FN(eswatj);

struct BurnDriverD BurnDrvMDeswatj = {
	"g_eswatj", NULL, NULL, "1900",
	"ESWAT Cyber Police (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, eswatjRomInfo, eswatjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Eternal Champions (E) [!]

static struct BurnRomInfo echmpeRomDesc[]={
	{ "g_echmpe.bin", 0x300000, 0xB9512F5E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(echmpe);
STD_ROM_FN(echmpe);

struct BurnDriverD BurnDrvMDechmpe = {
	"g_echmpe", NULL, NULL, "1900",
	"Eternal Champions (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, echmpeRomInfo, echmpeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Eternal Champions (J) [c][!]

static struct BurnRomInfo echmpjRomDesc[]={
	{ "g_echmpj.bin", 0x300000, 0x66AA3C64, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(echmpj);
STD_ROM_FN(echmpj);

struct BurnDriverD BurnDrvMDechmpj = {
	"g_echmpj", NULL, NULL, "1900",
	"Eternal Champions (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, echmpjRomInfo, echmpjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Yuu Yuu Hakusho - Sunset Fighters (B) [!]

static struct BurnRomInfo yuyubRomDesc[]={
	{ "g_yuyub.bin", 0x300000, 0xFE3FB8EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yuyub);
STD_ROM_FN(yuyub);

struct BurnDriverD BurnDrvMDyuyub = {
	"g_yuyub", NULL, NULL, "1900",
	"Yuu Yuu Hakusho - Sunset Fighters (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yuyubRomInfo, yuyubRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ys III - Wanderers from Ys (J) [!]

static struct BurnRomInfo ys3jRomDesc[]={
	{ "g_ys3j.bin", 0x100000, 0x52DA4E76, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ys3j);
STD_ROM_FN(ys3j);

struct BurnDriverD BurnDrvMDys3j = {
	"g_ys3j", NULL, NULL, "1900",
	"Ys III - Wanderers from Ys (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ys3jRomInfo, ys3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// XZR (J) [!]

static struct BurnRomInfo xzrRomDesc[]={
	{ "g_xzr.bin", 0x100000, 0x880BF311, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xzr);
STD_ROM_FN(xzr);

struct BurnDriverD BurnDrvMDxzr = {
	"g_xzr", NULL, NULL, "1900",
	"XZR (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xzrRomInfo, xzrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// X-Men (E) [!]

static struct BurnRomInfo xmeneRomDesc[]={
	{ "g_xmene.bin", 0x100000, 0x0B78CA97, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(xmene);
STD_ROM_FN(xmene);

struct BurnDriverD BurnDrvMDxmene = {
	"g_xmene", NULL, NULL, "1900",
	"X-Men (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, xmeneRomInfo, xmeneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// WWF Wrestlemania Arcade (Alpha) [!]

static struct BurnRomInfo wfwaalRomDesc[]={
	{ "g_wfwaal.bin", 0x040000, 0x719D6155, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wfwaal);
STD_ROM_FN(wfwaal);

struct BurnDriverD BurnDrvMDwfwaal = {
	"g_wfwaal", NULL, NULL, "1900",
	"WWF Wrestlemania Arcade (Alpha) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wfwaalRomInfo, wfwaalRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Worms (E) (Prototype) [c][!]

static struct BurnRomInfo wormpRomDesc[]={
	{ "g_wormp.bin", 0x200000, 0x1D191694, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wormp);
STD_ROM_FN(wormp);

struct BurnDriverD BurnDrvMDwormp = {
	"g_wormp", NULL, NULL, "1900",
	"Worms (E) (Prototype) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wormpRomInfo, wormpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World of Illusion Starring Mickey Mouse & Donald Duck (E) [!]

static struct BurnRomInfo willeRomDesc[]={
	{ "g_wille.bin", 0x100000, 0x121C6A49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wille);
STD_ROM_FN(wille);

struct BurnDriverD BurnDrvMDwille = {
	"g_wille", NULL, NULL, "1992",
	"World of Illusion Starring Mickey Mouse & Donald Duck (E) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, willeRomInfo, willeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Heroes (J) [!]

static struct BurnRomInfo wherojRomDesc[]={
	{ "g_wheroj.bin", 0x200000, 0x56E3CEFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wheroj);
STD_ROM_FN(wheroj);

struct BurnDriverD BurnDrvMDwheroj = {
	"g_wheroj", NULL, NULL, "1900",
	"World Heroes (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wherojRomInfo, wherojRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Championship Soccer (JU) (REV00) [!]

static struct BurnRomInfo wcs00RomDesc[]={
	{ "g_wcs00.bin", 0x040000, 0xB01C3D70, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcs00);
STD_ROM_FN(wcs00);

struct BurnDriverD BurnDrvMDwcs00 = {
	"g_wcs00", NULL, NULL, "1994",
	"World Championship Soccer (JU) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wcs00RomInfo, wcs00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wimbledon Championship Tennis (U) (Prototype) [!]

static struct BurnRomInfo wimbpRomDesc[]={
	{ "g_wimbp.bin", 0x100000, 0x9FEBC760, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wimbp);
STD_ROM_FN(wimbp);

struct BurnDriverD BurnDrvMDwimbp = {
	"g_wimbp", NULL, NULL, "1900",
	"Wimbledon Championship Tennis (U) (Prototype) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wimbpRomInfo, wimbpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wimbledon Championship Tennis (E) [!]

static struct BurnRomInfo wimbeRomDesc[]={
	{ "g_wimbe.bin", 0x100000, 0xB791A435, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wimbe);
STD_ROM_FN(wimbe);

struct BurnDriverD BurnDrvMDwimbe = {
	"g_wimbe", NULL, NULL, "1900",
	"Wimbledon Championship Tennis (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wimbeRomInfo, wimbeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtua Racing (J) [!]

static struct BurnRomInfo virrajRomDesc[]={
	{ "g_virraj.bin", 0x200000, 0x53A293B5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(virraj);
STD_ROM_FN(virraj);

struct BurnDriverD BurnDrvMDvirraj = {
	"g_virraj", NULL, NULL, "199?",
	"Virtua Racing (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, virrajRomInfo, virrajRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtua Racing (E) [!]

static struct BurnRomInfo virraeRomDesc[]={
	{ "g_virrae.bin", 0x200000, 0x9624D4EF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(virrae);
STD_ROM_FN(virrae);

struct BurnDriverD BurnDrvMDvirrae = {
	"g_virrae", NULL, NULL, "199?",
	"Virtua Racing (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, virraeRomInfo, virraeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vectorman (UE) (Prototype) [!]

static struct BurnRomInfo vectpRomDesc[]={
	{ "g_vectp.bin", 0x200000, 0xA315C8AA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vectp);
STD_ROM_FN(vectp);

struct BurnDriverD BurnDrvMDvectp = {
	"g_vectp", NULL, NULL, "1995",
	"Vectorman (UE) (Prototype) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vectpRomInfo, vectpRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vectorman 2 (U) (Prototype) [!]

static struct BurnRomInfo vect2pRomDesc[]={
	{ "g_vect2p.bin", 0x200000, 0xADA2B0EF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vect2p);
STD_ROM_FN(vect2p);

struct BurnDriverD BurnDrvMDvect2p = {
	"g_vect2p", NULL, NULL, "1996",
	"Vectorman 2 (U) (Prototype) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vect2pRomInfo, vect2pRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Valis SD (J) [!]

static struct BurnRomInfo valsdjRomDesc[]={
	{ "g_valsdj.bin", 0x080000, 0x1AEF72EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(valsdj);
STD_ROM_FN(valsdj);

struct BurnDriverD BurnDrvMDvalsdj = {
	"g_valsdj", NULL, NULL, "1900",
	"Valis SD (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, valsdjRomInfo, valsdjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Valis III (J) [!]

static struct BurnRomInfo val3jRomDesc[]={
	{ "g_val3j.bin", 0x100000, 0x4D49A166, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(val3j);
STD_ROM_FN(val3j);

struct BurnDriverD BurnDrvMDval3j = {
	"g_val3j", NULL, NULL, "1900",
	"Valis III (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, val3jRomInfo, val3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Valis (J) [!]

static struct BurnRomInfo valjRomDesc[]={
	{ "g_valj.bin", 0x100000, 0x24431625, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(valj);
STD_ROM_FN(valj);

struct BurnDriverD BurnDrvMDvalj = {
	"g_valj", NULL, NULL, "1900",
	"Valis (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, valjRomInfo, valjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Uzu Keobukseon (K) [!]

static struct BurnRomInfo uzukeRomDesc[]={
	{ "g_uzuke.bin", 0x080000, 0xA7255BA8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(uzuke);
STD_ROM_FN(uzuke);

struct BurnDriverD BurnDrvMDuzuke = {
	"g_uzuke", NULL, NULL, "1900",
	"Uzu Keobukseon (K) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, uzukeRomInfo, uzukeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 World Championship (E) [!]

static struct BurnRomInfo f1wlceRomDesc[]={
	{ "g_f1wlce.bin", 0x100000, 0xFBDD4520, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1wlce);
STD_ROM_FN(f1wlce);

struct BurnDriverD BurnDrvMDf1wlce = {
	"g_f1wlce", NULL, NULL, "1900",
	"F1 World Championship (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1wlceRomInfo, f1wlceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-22 Interceptor (Beta) [c][!]

static struct BurnRomInfo f22bRomDesc[]={
	{ "g_f22b.bin", 0x0C0000, 0xD6A880A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f22b);
STD_ROM_FN(f22b);

struct BurnDriverD BurnDrvMDf22b = {
	"g_f22b", NULL, NULL, "1991",
	"F-22 Interceptor (Beta) [c][!]\0", NULL, "Electronic Arts / Edward Lemer", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f22bRomInfo, f22bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-117 Stealth - Operation Night Storm (J) [!]

static struct BurnRomInfo f117jRomDesc[]={
	{ "g_f117j.bin", 0x200000, 0xEA6E421A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f117j);
STD_ROM_FN(f117j);

struct BurnDriverD BurnDrvMDf117j = {
	"g_f117j", NULL, NULL, "1900",
	"F-117 Stealth - Operation Night Storm (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f117jRomInfo, f117jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fantasia (E) [!]

static struct BurnRomInfo fanteRomDesc[]={
	{ "g_fante.bin", 0x080000, 0xD351B242, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fante);
STD_ROM_FN(fante);

struct BurnDriverD BurnDrvMDfante = {
	"g_fante", NULL, NULL, "1900",
	"Fantasia (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fanteRomInfo, fanteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fantasia (U) (REV00) [!]

static struct BurnRomInfo fant00RomDesc[]={
	{ "g_fant00.bin", 0x080000, 0x34E04627, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fant00);
STD_ROM_FN(fant00);

struct BurnDriverD BurnDrvMDfant00 = {
	"g_fant00", NULL, NULL, "1900",
	"Fantasia (U) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fant00RomInfo, fant00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ferias Frustradas do Pica-Pau (B) [!]

static struct BurnRomInfo feriasRomDesc[]={
	{ "g_ferias.bin", 0x100000, 0x7B2E416D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ferias);
STD_ROM_FN(ferias);

struct BurnDriverD BurnDrvMDferias = {
	"g_ferias", NULL, NULL, "1900",
	"Ferias Frustradas do Pica-Pau (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, feriasRomInfo, feriasRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// FIFA Soccer 99 (R) [!]

static struct BurnRomInfo fi99rRomDesc[]={
	{ "g_fi99r.bin", 0x200000, 0xC5C5A4B0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fi99r);
STD_ROM_FN(fi99r);

struct BurnDriver BurnDrvMDfi99r = {
	"g_fi99r", "g_fi96", NULL, "1900",
	"FIFA Soccer 99 (R) [!]\0", NULL, "Unknown (Unlicensed)", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fi99rRomInfo, fi99rRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fighting Masters (J) [!]

static struct BurnRomInfo fghmsjRomDesc[]={
	{ "g_fghmsj.bin", 0x080000, 0x39BE80EC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fghmsj);
STD_ROM_FN(fghmsj);

struct BurnDriverD BurnDrvMDfghmsj = {
	"g_fghmsj", NULL, NULL, "1900",
	"Fighting Masters (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fghmsjRomInfo, fghmsjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fire Shark (E) [!]

static struct BurnRomInfo fshrkeRomDesc[]={
	{ "g_fshrke.bin", 0x080000, 0x2351CE61, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fshrke);
STD_ROM_FN(fshrke);

struct BurnDriverD BurnDrvMDfshrke = {
	"g_fshrke", NULL, NULL, "1900",
	"Fire Shark (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fshrkeRomInfo, fshrkeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fire Shark (U) [a1][!]

static struct BurnRomInfo fshrkuRomDesc[]={
	{ "g_fshrku.bin", 0x080000, 0x570B5024, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fshrku);
STD_ROM_FN(fshrku);

struct BurnDriverD BurnDrvMDfshrku = {
	"g_fshrku", NULL, NULL, "1900",
	"Fire Shark (U) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fshrkuRomInfo, fshrkuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flintstone

static struct BurnRomInfo flinteRomDesc[]={
	{ "g_flinte.bin", 0x080000, 0x21845D61, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(flinte);
STD_ROM_FN(flinte);

struct BurnDriverD BurnDrvMDflinte = {
	"g_flinte", NULL, NULL, "1900",
	"Flintstone\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, flinteRomInfo, flinteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Flintstone

static struct BurnRomInfo flintjRomDesc[]={
	{ "g_flintj.bin", 0x080000, 0x920A3031, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(flintj);
STD_ROM_FN(flintj);

struct BurnDriverD BurnDrvMDflintj = {
	"g_flintj", NULL, NULL, "1900",
	"Flintstone\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, flintjRomInfo, flintjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Forgotten Worlds (W) (REV00) [!]

static struct BurnRomInfo fw00RomDesc[]={
	{ "g_fw00.bin", 0x080000, 0xD0EE6434, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fw00);
STD_ROM_FN(fw00);

struct BurnDriverD BurnDrvMDfw00 = {
	"g_fw00", NULL, NULL, "1900",
	"Forgotten Worlds (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fw00RomInfo, fw00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gain Ground (J) [!]

static struct BurnRomInfo ggroujRomDesc[]={
	{ "g_ggrouj.bin", 0x080000, 0x8641A2AB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ggrouj);
STD_ROM_FN(ggrouj);

struct BurnDriverD BurnDrvMDggrouj = {
	"g_ggrouj", NULL, NULL, "1900",
	"Gain Ground (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ggroujRomInfo, ggroujRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// George Foreman's KO Boxing (E) [!]

static struct BurnRomInfo gfkobeRomDesc[]={
	{ "g_gfkobe.bin", 0x100000, 0xBD556381, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gfkobe);
STD_ROM_FN(gfkobe);

struct BurnDriverD BurnDrvMDgfkobe = {
	"g_gfkobe", NULL, NULL, "1900",
	"George Foreman's KO Boxing (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gfkobeRomInfo, gfkobeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ghostbusters (W) (REV00) [!]

static struct BurnRomInfo gbus00RomDesc[]={
	{ "g_gbus00.bin", 0x080000, 0x00419DA3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gbus00);
STD_ROM_FN(gbus00);

struct BurnDriverD BurnDrvMDgbus00 = {
	"g_gbus00", NULL, NULL, "1900",
	"Ghostbusters (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gbus00RomInfo, gbus00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ghouls 'N Ghosts (UE) (REV01) [!]

static struct BurnRomInfo gng01RomDesc[]={
	{ "g_gng01.bin", 0x0A0000, 0xD31BD910, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gng01);
STD_ROM_FN(gng01);

struct BurnDriverD BurnDrvMDgng01 = {
	"g_gng01", NULL, NULL, "1989",
	"Ghouls 'N Ghosts (UE) (REV01) [!]\0", NULL, "Capcom / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gng01RomInfo, gng01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Golden Axe (W) (REV00) [!]

static struct BurnRomInfo gax00RomDesc[]={
	{ "g_gax00.bin", 0x080000, 0xE8182B90, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gax00);
STD_ROM_FN(gax00);

struct BurnDriver BurnDrvMDgax00 = {
	"g_gax00", "g_gax", NULL, "1900",
	"Golden Axe (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gax00RomInfo, gax00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Granada (JU) (REV00) [!]

static struct BurnRomInfo gran00RomDesc[]={
	{ "g_gran00.bin", 0x080000, 0x7F45719B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gran00);
STD_ROM_FN(gran00);

struct BurnDriverD BurnDrvMDgran00 = {
	"g_gran00", NULL, NULL, "1900",
	"Granada (JU) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gran00RomInfo, gran00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Greatest Heavyweights of the Ring (J) [c][!]

static struct BurnRomInfo ghwjRomDesc[]={
	{ "g_ghwj.bin", 0x200000, 0x7EF8B162, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ghwj);
STD_ROM_FN(ghwj);

struct BurnDriverD BurnDrvMDghwj = {
	"g_ghwj", NULL, NULL, "1900",
	"Greatest Heavyweights of the Ring (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ghwjRomInfo, ghwjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gunstar Heroes (Sample) (J) [!]

static struct BurnRomInfo gshsamRomDesc[]={
	{ "g_gshsam.bin", 0x100000, 0x6F90B502, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gshsam);
STD_ROM_FN(gshsam);

struct BurnDriverD BurnDrvMDgshsam = {
	"g_gshsam", NULL, NULL, "1993",
	"Gunstar Heroes (Sample) (J) [!]\0", NULL, "Sega / Treasure", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gshsamRomInfo, gshsamRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gynoug (E) [!]

static struct BurnRomInfo gynogeRomDesc[]={
	{ "g_gynoge.bin", 0x080000, 0x03405102, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gynoge);
STD_ROM_FN(gynoge);

struct BurnDriverD BurnDrvMDgynoge = {
	"g_gynoge", NULL, NULL, "1991",
	"Gynoug (E) [!]\0", NULL, "NCS", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gynogeRomInfo, gynogeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hellfire (J) [!]

static struct BurnRomInfo helfijRomDesc[]={
	{ "g_helfij.bin", 0x080000, 0x8E5E13BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(helfij);
STD_ROM_FN(helfij);

struct BurnDriverD BurnDrvMDhelfij = {
	"g_helfij", NULL, NULL, "1900",
	"Hellfire (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, helfijRomInfo, helfijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Herzog Zwei (J) [!]

static struct BurnRomInfo herzojRomDesc[]={
	{ "g_herzoj.bin", 0x080000, 0x4CF676B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(herzoj);
STD_ROM_FN(herzoj);

struct BurnDriverD BurnDrvMDherzoj = {
	"g_herzoj", NULL, NULL, "1900",
	"Herzog Zwei (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, herzojRomInfo, herzojRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hybrid Fron

static struct BurnRomInfo hybripRomDesc[]={
	{ "g_hybrip.bin", 0x300000, 0x04F02687, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hybrip);
STD_ROM_FN(hybrip);

struct BurnDriverD BurnDrvMDhybrip = {
	"g_hybrip", NULL, NULL, "1900",
	"Hybrid Fron\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hybripRomInfo, hybripRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hyper Dunk - The Playoff Edition (J) [!]

static struct BurnRomInfo hdunkjRomDesc[]={
	{ "g_hdunkj.bin", 0x200000, 0x5BAF53D7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hdunkj);
STD_ROM_FN(hdunkj);

struct BurnDriverD BurnDrvMDhdunkj = {
	"g_hdunkj", NULL, NULL, "1900",
	"Hyper Dunk - The Playoff Edition (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hdunkjRomInfo, hdunkjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Indiana Jones and the Last Crusade (E) [c][!]

static struct BurnRomInfo indlceRomDesc[]={
	{ "g_indlce.bin", 0x100000, 0xEB8F4374, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(indlce);
STD_ROM_FN(indlce);

struct BurnDriverD BurnDrvMDindlce = {
	"g_indlce", NULL, NULL, "1900",
	"Indiana Jones and the Last Crusade (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, indlceRomInfo, indlceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Insector X (J) [!]

static struct BurnRomInfo insxjRomDesc[]={
	{ "g_insxj.bin", 0x080000, 0x9625C434, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(insxj);
STD_ROM_FN(insxj);

struct BurnDriverD BurnDrvMDinsxj = {
	"g_insxj", NULL, NULL, "1900",
	"Insector X (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, insxjRomInfo, insxjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// J. League Pro Striker (J) (REV00) [c][!]

static struct BurnRomInfo jlps00RomDesc[]={
	{ "g_jlps00.bin", 0x100000, 0xEC229156, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jlps00);
STD_ROM_FN(jlps00);

struct BurnDriverD BurnDrvMDjlps00 = {
	"g_jlps00", NULL, NULL, "1900",
	"J. League Pro Striker (J) (REV00) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jlps00RomInfo, jlps00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Pond II - Codename RoboCod (J) [!]

static struct BurnRomInfo jp2jRomDesc[]={
	{ "g_jp2j.bin", 0x080000, 0x98794702, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jp2j);
STD_ROM_FN(jp2j);

struct BurnDriver BurnDrvMDjp2j = {
	"g_jp2j", "g_jp2", NULL, "1991",
	"James Pond II - Codename RoboCod (J) [!]\0", NULL, "Electronic Arts / Millenium", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jp2jRomInfo, jp2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jewel Master (J) [c][!]

static struct BurnRomInfo jewljRomDesc[]={
	{ "g_jewlj.bin", 0x080000, 0x2CF6926C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jewlj);
STD_ROM_FN(jewlj);

struct BurnDriverD BurnDrvMDjewlj = {
	"g_jewlj", NULL, NULL, "1900",
	"Jewel Master (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jewljRomInfo, jewljRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jordan vs Bird - Super One-on-One (J) [!]

static struct BurnRomInfo jb11jRomDesc[]={
	{ "g_jb11j.bin", 0x080000, 0x8837E896, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jb11j);
STD_ROM_FN(jb11j);

struct BurnDriverD BurnDrvMDjb11j = {
	"g_jb11j", NULL, NULL, "1900",
	"Jordan vs Bird - Super One-on-One (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jb11jRomInfo, jb11jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jordan vs Bird - Super One-on-One (UE) (REV00) [!]

static struct BurnRomInfo jb1100RomDesc[]={
	{ "g_jb1100.bin", 0x080000, 0x22D77E6D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jb1100);
STD_ROM_FN(jb1100);

struct BurnDriverD BurnDrvMDjb1100 = {
	"g_jb1100", NULL, NULL, "1900",
	"Jordan vs Bird - Super One-on-One (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jb1100RomInfo, jb1100RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park (E) [!]

static struct BurnRomInfo jparkeRomDesc[]={
	{ "g_jparke.bin", 0x200000, 0x448341F6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jparke);
STD_ROM_FN(jparke);

struct BurnDriverD BurnDrvMDjparke = {
	"g_jparke", NULL, NULL, "1900",
	"Jurassic Park (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jparkeRomInfo, jparkeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park (J) [!]

static struct BurnRomInfo jparkjRomDesc[]={
	{ "g_jparkj.bin", 0x200000, 0xEC8E5783, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jparkj);
STD_ROM_FN(jparkj);

struct BurnDriverD BurnDrvMDjparkj = {
	"g_jparkj", NULL, NULL, "1900",
	"Jurassic Park (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jparkjRomInfo, jparkjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ka-Ge-Ki (J) [!]

static struct BurnRomInfo kagekiRomDesc[]={
	{ "g_kageki.bin", 0x100000, 0x391866A1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kageki);
STD_ROM_FN(kageki);

struct BurnDriverD BurnDrvMDkageki = {
	"g_kageki", NULL, NULL, "1900",
	"Ka-Ge-Ki (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kagekiRomInfo, kagekiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King of the Monsters (E) [!]

static struct BurnRomInfo kotmeRomDesc[]={
	{ "g_kotme.bin", 0x100000, 0x7A94FD49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kotme);
STD_ROM_FN(kotme);

struct BurnDriverD BurnDrvMDkotme = {
	"g_kotme", NULL, NULL, "1900",
	"King of the Monsters (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kotmeRomInfo, kotmeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// King Salmon - The Big Catch (J) [c][!]

static struct BurnRomInfo ksalmjRomDesc[]={
	{ "g_ksalmj.bin", 0x080000, 0x2CFC9F61, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ksalmj);
STD_ROM_FN(ksalmj);

struct BurnDriverD BurnDrvMDksalmj = {
	"g_ksalmj", NULL, NULL, "1900",
	"King Salmon - The Big Catch (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ksalmjRomInfo, ksalmjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lethal Enforcers II - Gun Fighters (E) [!]

static struct BurnRomInfo lth2jRomDesc[]={
	{ "g_lth2j.bin", 0x200000, 0x4BFE045C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lth2j);
STD_ROM_FN(lth2j);

struct BurnDriverD BurnDrvMDlth2j = {
	"g_lth2j", NULL, NULL, "1900",
	"Lethal Enforcers II - Gun Fighters (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lth2jRomInfo, lth2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// LHX Attack Chopper (J) [!]

static struct BurnRomInfo lhxjRomDesc[]={
	{ "g_lhxj.bin", 0x100000, 0x224FF103, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lhxj);
STD_ROM_FN(lhxj);

struct BurnDriverD BurnDrvMDlhxj = {
	"g_lhxj", NULL, NULL, "1900",
	"LHX Attack Chopper (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lhxjRomInfo, lhxjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Light Crusader (E) (M4) [!]

static struct BurnRomInfo licrueRomDesc[]={
	{ "g_licrue.bin", 0x200000, 0x52C7252B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(licrue);
STD_ROM_FN(licrue);

struct BurnDriverD BurnDrvMDlicrue = {
	"g_licrue", NULL, NULL, "1900",
	"Light Crusader (E) (M4) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, licrueRomInfo, licrueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Light Crusader (J) [!]

static struct BurnRomInfo licrujRomDesc[]={
	{ "g_licruj.bin", 0x200000, 0x237076A4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(licruj);
STD_ROM_FN(licruj);

struct BurnDriverD BurnDrvMDlicruj = {
	"g_licruj", NULL, NULL, "1900",
	"Light Crusader (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, licrujRomInfo, licrujRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Light Crusader (K) [!]

static struct BurnRomInfo licrukRomDesc[]={
	{ "g_licruk.bin", 0x200000, 0x6D0CBCB2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(licruk);
STD_ROM_FN(licruk);

struct BurnDriverD BurnDrvMDlicruk = {
	"g_licruk", NULL, NULL, "1900",
	"Light Crusader (K) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, licrukRomInfo, licrukRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marvel Land (J) [!]

static struct BurnRomInfo marvjRomDesc[]={
	{ "g_marvj.bin", 0x100000, 0x5D162D21, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(marvj);
STD_ROM_FN(marvj);

struct BurnDriverD BurnDrvMDmarvj = {
	"g_marvj", NULL, NULL, "1900",
	"Marvel Land (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, marvjRomInfo, marvjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Master of Monsters (J) [!]

static struct BurnRomInfo momonjRomDesc[]={
	{ "g_momonj.bin", 0x080000, 0xD51EE8C2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(momonj);
STD_ROM_FN(momonj);

struct BurnDriverD BurnDrvMDmomonj = {
	"g_momonj", NULL, NULL, "1900",
	"Master of Monsters (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, momonjRomInfo, momonjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mazin Wars (E) [!]

static struct BurnRomInfo mazieRomDesc[]={
	{ "g_mazie.bin", 0x100000, 0x4B07A105, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mazie);
STD_ROM_FN(mazie);

struct BurnDriverD BurnDrvMDmazie = {
	"g_mazie", NULL, NULL, "1993",
	"Mazin Wars (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mazieRomInfo, mazieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// McDonald's Treasure Land Adventure (J) [!]

static struct BurnRomInfo mcdtjRomDesc[]={
	{ "g_mcdtj.bin", 0x100000, 0xFEBCFD06, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mcdtj);
STD_ROM_FN(mcdtj);

struct BurnDriverD BurnDrvMDmcdtj = {
	"g_mcdtj", NULL, NULL, "1993",
	"McDonald's Treasure Land Adventure (J) [!]\0", NULL, "Sega / Treasure / McDonalds", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mcdtjRomInfo, mcdtjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mick & Mack as the Global Gladiators (E) [!]

static struct BurnRomInfo micmajRomDesc[]={
	{ "g_micmaj.bin", 0x100000, 0x5C218C6A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micmaj);
STD_ROM_FN(micmaj);

struct BurnDriverD BurnDrvMDmicmaj = {
	"g_micmaj", NULL, NULL, "1994",
	"Mick & Mack as the Global Gladiators (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micmajRomInfo, micmajRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey Mania - Timeless Adventures of Mickey Mouse (E) [!]

static struct BurnRomInfo mmanieRomDesc[]={
	{ "g_mmanie.bin", 0x200000, 0xCB5A8B85, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmanie);
STD_ROM_FN(mmanie);

struct BurnDriverD BurnDrvMDmmanie = {
	"g_mmanie", NULL, NULL, "1994",
	"Mickey Mania - Timeless Adventures of Mickey Mouse (E) [!]\0", NULL, "Disney / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmanieRomInfo, mmanieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey Mania - Timeless Adventures of Mickey Mouse (J) [!]

static struct BurnRomInfo mmanijRomDesc[]={
	{ "g_mmanij.bin", 0x200000, 0x23180CF7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmanij);
STD_ROM_FN(mmanij);

struct BurnDriverD BurnDrvMDmmanij = {
	"g_mmanij", NULL, NULL, "1994",
	"Mickey Mania - Timeless Adventures of Mickey Mouse (J) [!]\0", NULL, "Disney / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmanijRomInfo, mmanijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines 2 - Turbo Tournament (E) (J-Cart) [c][!]

static struct BurnRomInfo micm2eRomDesc[]={
	{ "g_micm2e.bin", 0x100000, 0x42BFB7EB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micm2e);
STD_ROM_FN(micm2e);

struct BurnDriverD BurnDrvMDmicm2e = {
	"g_micm2e", NULL, NULL, "1994",
	"Micro Machines 2 - Turbo Tournament (E) (J-Cart) [c][!]\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micm2eRomInfo, micm2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Midnight Resistance (J) [!]

static struct BurnRomInfo midrejRomDesc[]={
	{ "g_midrej.bin", 0x100000, 0x8F3F6E4D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(midrej);
STD_ROM_FN(midrej);

struct BurnDriverD BurnDrvMDmidrej = {
	"g_midrej", NULL, NULL, "1900",
	"Midnight Resistance (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, midrejRomInfo, midrejRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mig-29 Fighter Pilot (E) [!]

static struct BurnRomInfo mig29eRomDesc[]={
	{ "g_mig29e.bin", 0x100000, 0x70B0A5D7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mig29e);
STD_ROM_FN(mig29e);

struct BurnDriverD BurnDrvMDmig29e = {
	"g_mig29e", NULL, NULL, "1900",
	"Mig-29 Fighter Pilot (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mig29eRomInfo, mig29eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mike Ditka Power Football (U) [a1][!]

static struct BurnRomInfo mdpfuaRomDesc[]={
	{ "g_mdpfua.bin", 0x100000, 0xDE50CA8E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mdpfua);
STD_ROM_FN(mdpfua);

struct BurnDriverD BurnDrvMDmdpfua = {
	"g_mdpfua", NULL, NULL, "1900",
	"Mike Ditka Power Football (U) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mdpfuaRomInfo, mdpfuaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mutant League Football (J) [!]

static struct BurnRomInfo mutlfjRomDesc[]={
	{ "g_mutlfj.bin", 0x100000, 0x2A97E6AF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mutlfj);
STD_ROM_FN(mutlfj);

struct BurnDriverD BurnDrvMDmutlfj = {
	"g_mutlfj", NULL, NULL, "1900",
	"Mutant League Football (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mutlfjRomInfo, mutlfjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mystic Defender (W) (REV00) [!]

static struct BurnRomInfo mysd00RomDesc[]={
	{ "g_mysd00.bin", 0x080000, 0xF9CE1AB8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mysd00);
STD_ROM_FN(mysd00);

struct BurnDriverD BurnDrvMDmysd00 = {
	"g_mysd00", NULL, NULL, "1900",
	"Mystic Defender (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mysd00RomInfo, mysd00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NFL Football '94 Starring Joe Montana (J) [!]

static struct BurnRomInfo nfl94jRomDesc[]={
	{ "g_nfl94j.bin", 0x200000, 0xE490DC4A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nfl94j);
STD_ROM_FN(nfl94j);

struct BurnDriverD BurnDrvMDnfl94j = {
	"g_nfl94j", NULL, NULL, "1900",
	"NFL Football '94 Starring Joe Montana (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nfl94jRomInfo, nfl94jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Gold - Barcelona 92 (E) (M8) [c][!]

static struct BurnRomInfo olgoleRomDesc[]={
	{ "g_olgole.bin", 0x080000, 0x924E57D3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olgole);
STD_ROM_FN(olgole);

struct BurnDriverD BurnDrvMDolgole = {
	"g_olgole", NULL, NULL, "1900",
	"Olympic Gold - Barcelona 92 (E) (M8) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olgoleRomInfo, olgoleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Gold - Barcelona 92 (J) (M8) [c][!]

static struct BurnRomInfo olgoljRomDesc[]={
	{ "g_olgolj.bin", 0x080000, 0xE9C925B8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olgolj);
STD_ROM_FN(olgolj);

struct BurnDriverD BurnDrvMDolgolj = {
	"g_olgolj", NULL, NULL, "1900",
	"Olympic Gold - Barcelona 92 (J) (M8) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olgoljRomInfo, olgoljRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Gold - Barcelona 92 (U) (M8) [a1][c][!]

static struct BurnRomInfo olgoluRomDesc[]={
	{ "g_olgolu.bin", 0x080000, 0xAF639376, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olgolu);
STD_ROM_FN(olgolu);

struct BurnDriverD BurnDrvMDolgolu = {
	"g_olgolu", NULL, NULL, "1900",
	"Olympic Gold - Barcelona 92 (U) (M8) [a1][c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olgoluRomInfo, olgoluRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Winter Games - Lillehammer 94 (E) [c][!]

static struct BurnRomInfo olwgeRomDesc[]={
	{ "g_olwge.bin", 0x200000, 0xFA537A45, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olwge);
STD_ROM_FN(olwge);

struct BurnDriverD BurnDrvMDolwge = {
	"g_olwge", NULL, NULL, "1900",
	"Olympic Winter Games - Lillehammer 94 (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olwgeRomInfo, olwgeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Olympic Winter Games - Lillehammer 94 (J) [c][!]

static struct BurnRomInfo olwgjRomDesc[]={
	{ "g_olwgj.bin", 0x200000, 0x654A4684, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(olwgj);
STD_ROM_FN(olwgj);

struct BurnDriverD BurnDrvMDolwgj = {
	"g_olwgj", NULL, NULL, "1900",
	"Olympic Winter Games - Lillehammer 94 (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, olwgjRomInfo, olwgjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Saint Sword (J) [c][!]

static struct BurnRomInfo sswojRomDesc[]={
	{ "g_sswoj.bin", 0x080000, 0x3960A00F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sswoj);
STD_ROM_FN(sswoj);

struct BurnDriverD BurnDrvMDsswoj = {
	"g_sswoj", NULL, NULL, "1900",
	"Saint Sword (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sswojRomInfo, sswojRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Same! Same! Same! (J) [!]

static struct BurnRomInfo samex3RomDesc[]={
	{ "g_samex3.bin", 0x080000, 0x77BBD841, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(samex3);
STD_ROM_FN(samex3);

struct BurnDriverD BurnDrvMDsamex3 = {
	"g_samex3", NULL, NULL, "1900",
	"Same! Same! Same! (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, samex3RomInfo, samex3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadow of the Beast (J) [!]

static struct BurnRomInfo shbeajRomDesc[]={
	{ "g_shbeaj.bin", 0x100000, 0x0CD09D31, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shbeaj);
STD_ROM_FN(shbeaj);

struct BurnDriverD BurnDrvMDshbeaj = {
	"g_shbeaj", NULL, NULL, "1900",
	"Shadow of the Beast (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shbeajRomInfo, shbeajRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shadowrun (J) [!]

static struct BurnRomInfo shrunjRomDesc[]={
	{ "g_shrunj.bin", 0x200000, 0xD32199F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shrunj);
STD_ROM_FN(shrunj);

struct BurnDriverD BurnDrvMDshrunj = {
	"g_shrunj", NULL, NULL, "1900",
	"Shadowrun (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shrunjRomInfo, shrunjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shin Changsegi - Ragnacenty (K) [!]

static struct BurnRomInfo shinchRomDesc[]={
	{ "g_shinch.bin", 0x200000, 0x77B5B10B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shinch);
STD_ROM_FN(shinch);

struct BurnDriverD BurnDrvMDshinch = {
	"g_shinch", NULL, NULL, "1994",
	"Shin Changsegi - Ragnacenty (K) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shinchRomInfo, shinchRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining and the Darkness (J) [!]

static struct BurnRomInfo shdrkjRomDesc[]={
	{ "g_shdrkj.bin", 0x100000, 0x496AF51C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shdrkj);
STD_ROM_FN(shdrkj);

struct BurnDriverD BurnDrvMDshdrkj = {
	"g_shdrkj", NULL, NULL, "1991",
	"Shining and the Darkness (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shdrkjRomInfo, shdrkjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force - The Legacy of Great Intention (J) [!]

static struct BurnRomInfo shfrcjRomDesc[]={
	{ "g_shfrcj.bin", 0x180000, 0x9378FBCD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shfrcj);
STD_ROM_FN(shfrcj);

struct BurnDriverD BurnDrvMDshfrcj = {
	"g_shfrcj", NULL, NULL, "1993",
	"Shining Force - The Legacy of Great Intention (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shfrcjRomInfo, shfrcjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force II - Inishie no Fuuin (J) [!]

static struct BurnRomInfo shfr2jRomDesc[]={
	{ "g_shfr2j.bin", 0x200000, 0x0288F3E1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shfr2j);
STD_ROM_FN(shfr2j);

struct BurnDriverD BurnDrvMDshfr2j = {
	"g_shfr2j", NULL, NULL, "1994",
	"Shining Force II - Inishie no Fuuin (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shfr2jRomInfo, shfr2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force II (E) [!]

static struct BurnRomInfo shfr2eRomDesc[]={
	{ "g_shfr2e.bin", 0x200000, 0x83CB46D1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shfr2e);
STD_ROM_FN(shfr2e);

struct BurnDriverD BurnDrvMDshfr2e = {
	"g_shfr2e", NULL, NULL, "1994",
	"Shining Force II (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shfr2eRomInfo, shfr2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining in the Darkness (B) [!]

static struct BurnRomInfo shdrkbRomDesc[]={
	{ "g_shdrkb.bin", 0x100000, 0x3EE2BBC4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shdrkb);
STD_ROM_FN(shdrkb);

struct BurnDriverD BurnDrvMDshdrkb = {
	"g_shdrkb", NULL, NULL, "1991",
	"Shining in the Darkness (B) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shdrkbRomInfo, shdrkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Show do Milhao (B) [!]

static struct BurnRomInfo showdRomDesc[]={
	{ "g_showd.bin", 0x200000, 0x0A22DF04, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(showd);
STD_ROM_FN(showd);

struct BurnDriverD BurnDrvMDshowd = {
	"g_showd", NULL, NULL, "1900",
	"Show do Milhao (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, showdRomInfo, showdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Show do Milhao Volume 2 (B) [!]

static struct BurnRomInfo showd2RomDesc[]={
	{ "g_showd2.bin", 0x200000, 0x48EE66CB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(showd2);
STD_ROM_FN(showd2);

struct BurnDriverD BurnDrvMDshowd2 = {
	"g_showd2", NULL, NULL, "1900",
	"Show do Milhao Volume 2 (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, showd2RomInfo, showd2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Show do Milhao Volume 2 (B) [a1][!]

static struct BurnRomInfo shwd2aRomDesc[]={
	{ "g_shwd2a.bin", 0x200000, 0xD8C9AC6D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shwd2a);
STD_ROM_FN(shwd2a);

struct BurnDriverD BurnDrvMDshwd2a = {
	"g_shwd2a", NULL, NULL, "1900",
	"Show do Milhao Volume 2 (B) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shwd2aRomInfo, shwd2aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sokoban (J) [!]

static struct BurnRomInfo sokobaRomDesc[]={
	{ "g_sokoba.bin", 0x040000, 0x40F4AACC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sokoba);
STD_ROM_FN(sokoba);

struct BurnDriverD BurnDrvMDsokoba = {
	"g_sokoba", NULL, NULL, "1900",
	"Sokoban (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sokobaRomInfo, sokobaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic The Hedgehog 2 (Prototype) [!]

static struct BurnRomInfo soni2pRomDesc[]={
	{ "g_soni2p.bin", 0x100000, 0xEEA21B5C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soni2p);
STD_ROM_FN(soni2p);

struct BurnDriverD BurnDrvMDsoni2p = {
	"g_soni2p", "g_son2", NULL, "1992",
	"Sonic The Hedgehog 2 (Prototype) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soni2pRomInfo, soni2pRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sorcer Kingdom (J) [c][!]

static struct BurnRomInfo sorkinRomDesc[]={
	{ "g_sorkin.bin", 0x100000, 0x944135CA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sorkin);
STD_ROM_FN(sorkin);

struct BurnDriverD BurnDrvMDsorkin = {
	"g_sorkin", NULL, NULL, "1900",
	"Sorcer Kingdom (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sorkinRomInfo, sorkinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Space Harrier II (J) [!]

static struct BurnRomInfo shar2jRomDesc[]={
	{ "g_shar2j.bin", 0x080000, 0xEDC0FB28, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shar2j);
STD_ROM_FN(shar2j);

struct BurnDriverD BurnDrvMDshar2j = {
	"g_shar2j", NULL, NULL, "1900",
	"Space Harrier II (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shar2jRomInfo, shar2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sparkster (E) [!]

static struct BurnRomInfo sparkeRomDesc[]={
	{ "g_sparke.bin", 0x100000, 0xD63E9F2D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sparke);
STD_ROM_FN(sparke);

struct BurnDriverD BurnDrvMDsparke = {
	"g_sparke", NULL, NULL, "1900",
	"Sparkster (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sparkeRomInfo, sparkeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sparkster (J) [!]

static struct BurnRomInfo sparkjRomDesc[]={
	{ "g_sparkj.bin", 0x100000, 0x914EC662, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sparkj);
STD_ROM_FN(sparkj);

struct BurnDriverD BurnDrvMDsparkj = {
	"g_sparkj", NULL, NULL, "1900",
	"Sparkster (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sparkjRomInfo, sparkjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Speed Ball 2 - Brutal Deluxe (E) [!]

static struct BurnRomInfo sbal2eRomDesc[]={
	{ "g_sbal2e.bin", 0x080000, 0x056A6E03, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sbal2e);
STD_ROM_FN(sbal2e);

struct BurnDriverD BurnDrvMDsbal2e = {
	"g_sbal2e", NULL, NULL, "1900",
	"Speed Ball 2 - Brutal Deluxe (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sbal2eRomInfo, sbal2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse 2 (E) [c][!]

static struct BurnRomInfo shou2eRomDesc[]={
	{ "g_shou2e.bin", 0x100000, 0x2559E03C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shou2e);
STD_ROM_FN(shou2e);

struct BurnDriverD BurnDrvMDshou2e = {
	"g_shou2e", NULL, NULL, "1900",
	"Splatterhouse 2 (E) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shou2eRomInfo, shou2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse Part 3 (J) [c][!]

static struct BurnRomInfo shou3jRomDesc[]={
	{ "g_shou3j.bin", 0x200000, 0x31B83D22, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shou3j);
STD_ROM_FN(shou3j);

struct BurnDriverD BurnDrvMDshou3j = {
	"g_shou3j", NULL, NULL, "1900",
	"Splatterhouse Part 3 (J) [c][!]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shou3jRomInfo, shou3jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spot Goes to Hollywood (E) [!]

static struct BurnRomInfo spot2eRomDesc[]={
	{ "g_spot2e.bin", 0x300000, 0xFBE254EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spot2e);
STD_ROM_FN(spot2e);

struct BurnDriverD BurnDrvMDspot2e = {
	"g_spot2e", NULL, NULL, "199?",
	"Spot Goes to Hollywood (E) [!]\0", NULL, "Virgin / Acclaim / Eurocom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spot2eRomInfo, spot2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Cruiser (J) [!]

static struct BurnRomInfo starcjRomDesc[]={
	{ "g_starcj.bin", 0x080000, 0x2B75B52F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(starcj);
STD_ROM_FN(starcj);

struct BurnDriverD BurnDrvMDstarcj = {
	"g_starcj", NULL, NULL, "1900",
	"Star Cruiser (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, starcjRomInfo, starcjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Trek - The Next Generation (U) (REV00) [!]

static struct BurnRomInfo stng00RomDesc[]={
	{ "g_stng00.bin", 0x200000, 0x272153FB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stng00);
STD_ROM_FN(stng00);

struct BurnDriverD BurnDrvMDstng00 = {
	"g_stng00", NULL, NULL, "1900",
	"Star Trek - The Next Generation (U) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stng00RomInfo, stng00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Starflight (UE) (REV00) [!]

static struct BurnRomInfo strf00RomDesc[]={
	{ "g_strf00.bin", 0x100000, 0xD550C928, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(strf00);
STD_ROM_FN(strf00);

struct BurnDriverD BurnDrvMDstrf00 = {
	"g_strf00", NULL, NULL, "1900",
	"Starflight (UE) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, strf00RomInfo, strf00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Steel Talons (J) [!]

static struct BurnRomInfo staljRomDesc[]={
	{ "g_stalj.bin", 0x080000, 0x04F388E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stalj);
STD_ROM_FN(stalj);

struct BurnDriverD BurnDrvMDstalj = {
	"g_stalj", NULL, NULL, "1900",
	"Steel Talons (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, staljRomInfo, staljRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Stormlord (J) [!]

static struct BurnRomInfo slordjRomDesc[]={
	{ "g_slordj.bin", 0x080000, 0x0B440FED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(slordj);
STD_ROM_FN(slordj);

struct BurnDriverD BurnDrvMDslordj = {
	"g_slordj", NULL, NULL, "1900",
	"Stormlord (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, slordjRomInfo, slordjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Strider Hiryuu (J) [!]

static struct BurnRomInfo stridjRomDesc[]={
	{ "g_stridj.bin", 0x100000, 0x859173F2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stridj);
STD_ROM_FN(stridj);

struct BurnDriverD BurnDrvMDstridj = {
	"g_stridj", NULL, NULL, "1900",
	"Strider Hiryuu (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stridjRomInfo, stridjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sub-Terrania (E) [!]

static struct BurnRomInfo subteRomDesc[]={
	{ "g_subte.bin", 0x200000, 0xE8CED28D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(subte);
STD_ROM_FN(subte);

struct BurnDriverD BurnDrvMDsubte = {
	"g_subte", NULL, NULL, "1993",
	"Sub-Terrania (E) [!]\0", NULL, "Zyrinx", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, subteRomInfo, subteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sub-Terrania (J) [!]

static struct BurnRomInfo subtjRomDesc[]={
	{ "g_subtj.bin", 0x200000, 0x7638EA91, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(subtj);
STD_ROM_FN(subtj);

struct BurnDriverD BurnDrvMDsubtj = {
	"g_subtj", NULL, NULL, "1993",
	"Sub-Terrania (J) [!]\0", NULL, "Zyrinx", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, subtjRomInfo, subtjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sunset Riders (E) [!]

static struct BurnRomInfo ssrideRomDesc[]={
	{ "g_ssride.bin", 0x080000, 0x0FF33054, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ssride);
STD_ROM_FN(ssride);

struct BurnDriverD BurnDrvMDssride = {
	"g_ssride", NULL, NULL, "1900",
	"Sunset Riders (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ssrideRomInfo, ssrideRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Baseball 2020 (J) [!]

static struct BurnRomInfo g_2020jRomDesc[]={
	{ "g_2020j.bin", 0x200000, 0x2BBEE127, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2020j);
STD_ROM_FN(g_2020j);

struct BurnDriverD BurnDrvMDg_2020j = {
	"g_2020j", "g_2020", NULL, "1900",
	"Super Baseball 2020 (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2020jRomInfo, g_2020jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Fantasy Zone (E) [!]

static struct BurnRomInfo sfzeRomDesc[]={
	{ "g_sfze.bin", 0x100000, 0x927975BE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sfze);
STD_ROM_FN(sfze);

struct BurnDriverD BurnDrvMDsfze = {
	"g_sfze", NULL, NULL, "1900",
	"Super Fantasy Zone (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sfzeRomInfo, sfzeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Hang-On (W) (REV00) [!]

static struct BurnRomInfo sho00RomDesc[]={
	{ "g_sho00.bin", 0x080000, 0xCB2201A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sho00);
STD_ROM_FN(sho00);

struct BurnDriverD BurnDrvMDsho00 = {
	"g_sho00", NULL, NULL, "1900",
	"Super Hang-On (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sho00RomInfo, sho00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Hydlide (E) [!]

static struct BurnRomInfo shydeRomDesc[]={
	{ "g_shyde.bin", 0x080000, 0x1FE2D90B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shyde);
STD_ROM_FN(shyde);

struct BurnDriverD BurnDrvMDshyde = {
	"g_shyde", NULL, NULL, "1900",
	"Super Hydlide (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shydeRomInfo, shydeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Hydlide (J) [c][!]

static struct BurnRomInfo shydjRomDesc[]={
	{ "g_shydj.bin", 0x080000, 0x599BE386, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shydj);
STD_ROM_FN(shydj);

struct BurnDriverD BurnDrvMDshydj = {
	"g_shydj", NULL, NULL, "1900",
	"Super Hydlide (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shydjRomInfo, shydjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Monaco Grand Prix (U) (M2) (REV03) [!]

static struct BurnRomInfo smgp03RomDesc[]={
	{ "g_smgp03.bin", 0x080000, 0x725018EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smgp03);
STD_ROM_FN(smgp03);

struct BurnDriverD BurnDrvMDsmgp03 = {
	"g_smgp03", NULL, NULL, "1990",
	"Super Monaco Grand Prix (U) (M2) (REV03) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smgp03RomInfo, smgp03RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Monaco Grand Prix (W) (M2) (REV00) [!]

static struct BurnRomInfo smgp00RomDesc[]={
	{ "g_smgp00.bin", 0x080000, 0x90F9BAB3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smgp00);
STD_ROM_FN(smgp00);

struct BurnDriverD BurnDrvMDsmgp00 = {
	"g_smgp00", NULL, NULL, "1990",
	"Super Monaco Grand Prix (W) (M2) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smgp00RomInfo, smgp00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Monaco Grand Prix (W) (M2) (REV01) [!]

static struct BurnRomInfo smgp01RomDesc[]={
	{ "g_smgp01.bin", 0x080000, 0xB1823595, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(smgp01);
STD_ROM_FN(smgp01);

struct BurnDriverD BurnDrvMDsmgp01 = {
	"g_smgp01", NULL, NULL, "1990",
	"Super Monaco Grand Prix (W) (M2) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, smgp01RomInfo, smgp01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Real Basketball (J) [c][!]

static struct BurnRomInfo srealjRomDesc[]={
	{ "g_srealj.bin", 0x080000, 0x4346E11A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(srealj);
STD_ROM_FN(srealj);

struct BurnDriverD BurnDrvMDsrealj = {
	"g_srealj", NULL, NULL, "1900",
	"Super Real Basketball (J) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, srealjRomInfo, srealjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Shinobi I

static struct BurnRomInfo sshin2RomDesc[]={
	{ "g_sshin2.bin", 0x100000, 0x5B412816, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sshin2);
STD_ROM_FN(sshin2);

struct BurnDriverD BurnDrvMDsshin2 = {
	"g_sshin2", NULL, NULL, "1993",
	"Super Shinobi I\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sshin2RomInfo, sshin2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Thunder Blade (W) (REV00) [!]

static struct BurnRomInfo stb00RomDesc[]={
	{ "g_stb00.bin", 0x080000, 0x8BD77836, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stb00);
STD_ROM_FN(stb00);

struct BurnDriverD BurnDrvMDstb00 = {
	"g_stb00", NULL, NULL, "1900",
	"Super Thunder Blade (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stb00RomInfo, stb00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Volleyball (U) [a1][!]

static struct BurnRomInfo svoluaRomDesc[]={
	{ "g_svolua.bin", 0x040000, 0x85102799, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(svolua);
STD_ROM_FN(svolua);

struct BurnDriverD BurnDrvMDsvolua = {
	"g_svolua", NULL, NULL, "1900",
	"Super Volleyball (U) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, svoluaRomInfo, svoluaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Superman (E) [!]

static struct BurnRomInfo supmneRomDesc[]={
	{ "g_supmne.bin", 0x100000, 0x7DB434BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(supmne);
STD_ROM_FN(supmne);

struct BurnDriverD BurnDrvMDsupmne = {
	"g_supmne", NULL, NULL, "1900",
	"Superman (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, supmneRomInfo, supmneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sword of Sodan (J) [!]

static struct BurnRomInfo swsojRomDesc[]={
	{ "g_swsoj.bin", 0x080000, 0x58EDB3F3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(swsoj);
STD_ROM_FN(swsoj);

struct BurnDriverD BurnDrvMDswsoj = {
	"g_swsoj", NULL, NULL, "1900",
	"Sword of Sodan (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, swsojRomInfo, swsojRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sword of Vermilion (J) [c][!]

static struct BurnRomInfo swvejRomDesc[]={
	{ "g_swvej.bin", 0x0A0000, 0xE400DFC3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(swvej);
STD_ROM_FN(swvej);

struct BurnDriverD BurnDrvMDswvej = {
	"g_swvej", NULL, NULL, "1900",
	"Sword of Vermilion (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, swvejRomInfo, swvejRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pachinko Canyon (J) [!]

static struct BurnRomInfo pachinRomDesc[]={
	{ "g_pachin.bin", 0x100000, 0x9D137E7F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pachin);
STD_ROM_FN(pachin);

struct BurnDriverD BurnDrvMDpachin = {
	"g_pachin", NULL, NULL, "1900",
	"Pachinko Canyon (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pachinRomInfo, pachinRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pagemaste

static struct BurnRomInfo pagemeRomDesc[]={
	{ "g_pageme.bin", 0x200000, 0x79A180E2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pageme);
STD_ROM_FN(pageme);

struct BurnDriverD BurnDrvMDpageme = {
	"g_pageme", NULL, NULL, "1994",
	"Pagemaste\0", NULL, "Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pagemeRomInfo, pagemeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Paperboy (J) [!]

static struct BurnRomInfo pboyjRomDesc[]={
	{ "g_pboyj.bin", 0x080000, 0xE14250AE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pboyj);
STD_ROM_FN(pboyj);

struct BurnDriverD BurnDrvMDpboyj = {
	"g_pboyj", NULL, NULL, "1900",
	"Paperboy (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pboyjRomInfo, pboyjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pebble Beach no Hatou (J) [!]

static struct BurnRomInfo pblbejRomDesc[]={
	{ "g_pblbej.bin", 0x180000, 0x96ED2E5D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pblbej);
STD_ROM_FN(pblbej);

struct BurnDriverD BurnDrvMDpblbej = {
	"g_pblbej", NULL, NULL, "1900",
	"Pebble Beach no Hatou (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pblbejRomInfo, pblbejRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pete Sampras Tennis (E) (REV03) (J-Cart) [!]

static struct BurnRomInfo pste03RomDesc[]={
	{ "g_pste03.bin", 0x100000, 0xAA8B19BC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pste03);
STD_ROM_FN(pste03);

struct BurnDriverD BurnDrvMDpste03 = {
	"g_pste03", NULL, NULL, "1900",
	"Pete Sampras Tennis (E) (REV03) (J-Cart) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pste03RomInfo, pste03RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf (UE) (REV01) [!]

static struct BurnRomInfo pgat01RomDesc[]={
	{ "g_pgat01.bin", 0x080000, 0x0489FF8E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pgat01);
STD_ROM_FN(pgat01);

struct BurnDriverD BurnDrvMDpgat01 = {
	"g_pgat01", NULL, NULL, "1900",
	"PGA Tour Golf (UE) (REV01) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pgat01RomInfo, pgat01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf II (J) [!]

static struct BurnRomInfo pga2jRomDesc[]={
	{ "g_pga2j.bin", 0x100000, 0xC05B7A4A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pga2j);
STD_ROM_FN(pga2j);

struct BurnDriverD BurnDrvMDpga2j = {
	"g_pga2j", NULL, NULL, "1900",
	"PGA Tour Golf II (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pga2jRomInfo, pga2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// PGA Tour Golf II (UE) (REV00) [c][!]

static struct BurnRomInfo pga200RomDesc[]={
	{ "g_pga200.bin", 0x100000, 0x16B2D816, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pga200);
STD_ROM_FN(pga200);

struct BurnDriverD BurnDrvMDpga200 = {
	"g_pga200", NULL, NULL, "1900",
	"PGA Tour Golf II (UE) (REV00) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pga200RomInfo, pga200RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II (B) (REV01) [!]

static struct BurnRomInfo phst2bRomDesc[]={
	{ "g_phst2b.bin", 0x0C0000, 0xE6688B66, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(phst2b);
STD_ROM_FN(phst2b);

struct BurnDriverD BurnDrvMDphst2b = {
	"g_phst2b", NULL, NULL, "1989",
	"Phantasy Star II (B) (REV01) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, phst2bRomInfo, phst2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star III - Generations of Doom (B) [!]

static struct BurnRomInfo phst3bRomDesc[]={
	{ "g_phst3b.bin", 0x0C0000, 0x2E9B4C23, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(phst3b);
STD_ROM_FN(phst3b);

struct BurnDriverD BurnDrvMDphst3b = {
	"g_phst3b", NULL, NULL, "1991",
	"Phantasy Star III - Generations of Doom (B) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, phst3bRomInfo, phst3bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phelios (E) [c][!]

static struct BurnRomInfo phelieRomDesc[]={
	{ "g_phelie.bin", 0x080000, 0x13ABC2B2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(phelie);
STD_ROM_FN(phelie);

struct BurnDriverD BurnDrvMDphelie = {
	"g_phelie", NULL, NULL, "1900",
	"Phelios (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, phelieRomInfo, phelieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phelios (J) [c][!]

static struct BurnRomInfo phelijRomDesc[]={
	{ "g_phelij.bin", 0x080000, 0x94596174, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(phelij);
STD_ROM_FN(phelij);

struct BurnDriverD BurnDrvMDphelij = {
	"g_phelij", NULL, NULL, "1900",
	"Phelios (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, phelijRomInfo, phelijRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puggsy (E) [!]

static struct BurnRomInfo puggseRomDesc[]={
	{ "g_puggse.bin", 0x100000, 0x5D5C9ADE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puggse);
STD_ROM_FN(puggse);

struct BurnDriverD BurnDrvMDpuggse = {
	"g_puggse", NULL, NULL, "1900",
	"Puggsy (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puggseRomInfo, puggseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Quack Shot Starring Donald Duck (W) (REV00) [!]

static struct BurnRomInfo quac00RomDesc[]={
	{ "g_quac00.bin", 0x080000, 0x88C8DD94, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(quac00);
STD_ROM_FN(quac00);

struct BurnDriverD BurnDrvMDquac00 = {
	"g_quac00", NULL, NULL, "1994",
	"Quack Shot Starring Donald Duck (W) (REV00) [!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, quac00RomInfo, quac00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Quack Shot Starring Donald Duck (W) (REV01) [a1][c][!]

static struct BurnRomInfo quac01RomDesc[]={
	{ "g_quac01.bin", 0x140000, 0xA5C946B3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(quac01);
STD_ROM_FN(quac01);

struct BurnDriverD BurnDrvMDquac01 = {
	"g_quac01", NULL, NULL, "1994",
	"Quack Shot Starring Donald Duck (W) (REV01) [a1][c][!]\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, quac01RomInfo, quac01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rambo III (W) (REV00) [!]

static struct BurnRomInfo ram300RomDesc[]={
	{ "g_ram300.bin", 0x040000, 0x2232F03D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ram300);
STD_ROM_FN(ram300);

struct BurnDriverD BurnDrvMDram300 = {
	"g_ram300", NULL, NULL, "1900",
	"Rambo III (W) (REV00) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ram300RomInfo, ram300RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ranger-X (E) [!]

static struct BurnRomInfo ranxeRomDesc[]={
	{ "g_ranxe.bin", 0x100000, 0xB8C04804, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ranxe);
STD_ROM_FN(ranxe);

struct BurnDriverD BurnDrvMDranxe = {
	"g_ranxe", NULL, NULL, "1993",
	"Ranger-X (E) [!]\0", NULL, "Sega / Gau", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ranxeRomInfo, ranxeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rastan Saga II (J) [!]

static struct BurnRomInfo rastjRomDesc[]={
	{ "g_rastj.bin", 0x080000, 0xEBACFB5A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rastj);
STD_ROM_FN(rastj);

struct BurnDriverD BurnDrvMDrastj = {
	"g_rastj", NULL, NULL, "1900",
	"Rastan Saga II (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rastjRomInfo, rastjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Revenge of Shinob

static struct BurnRomInfo rshi00RomDesc[]={
	{ "g_rshi00.bin", 0x080000, 0x5C7E5EA6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rshi00);
STD_ROM_FN(rshi00);

struct BurnDriverD BurnDrvMDrshi00 = {
	"g_rshi00", NULL, NULL, "1990",
	"Revenge of Shinob\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rshi00RomInfo, rshi00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Revenge of Shinob

static struct BurnRomInfo rshi01RomDesc[]={
	{ "g_rshi01.bin", 0x080000, 0x05F27994, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rshi01);
STD_ROM_FN(rshi01);

struct BurnDriverD BurnDrvMDrshi01 = {
	"g_rshi01", NULL, NULL, "1990",
	"Revenge of Shinob\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rshi01RomInfo, rshi01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Revenge of Shinob

static struct BurnRomInfo rshi02RomDesc[]={
	{ "g_rshi02.bin", 0x080000, 0xFE91AB7E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rshi02);
STD_ROM_FN(rshi02);

struct BurnDriverD BurnDrvMDrshi02 = {
	"g_rshi02", NULL, NULL, "1990",
	"Revenge of Shinob\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rshi02RomInfo, rshi02RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ristar - The Shooting Star (J) [!]

static struct BurnRomInfo ristjRomDesc[]={
	{ "g_ristj.bin", 0x200000, 0xCE464F0E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ristj);
STD_ROM_FN(ristj);

struct BurnDriverD BurnDrvMDristj = {
	"g_ristj", NULL, NULL, "1900",
	"Ristar - The Shooting Star (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ristjRomInfo, ristjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Road Blasters (J) [!]

static struct BurnRomInfo roadbjRomDesc[]={
	{ "g_roadbj.bin", 0x080000, 0xA0015440, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(roadbj);
STD_ROM_FN(roadbj);

struct BurnDriverD BurnDrvMDroadbj = {
	"g_roadbj", NULL, NULL, "1900",
	"Road Blasters (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, roadbjRomInfo, roadbjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rock n' Roll Racing (E) [!]

static struct BurnRomInfo rnrreRomDesc[]={
	{ "g_rnrre.bin", 0x100000, 0xBC5A0562, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rnrre);
STD_ROM_FN(rnrre);

struct BurnDriverD BurnDrvMDrnrre = {
	"g_rnrre", NULL, NULL, "1900",
	"Rock n' Roll Racing (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rnrreRomInfo, rnrreRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rocket Knight Adventures (E) [!]

static struct BurnRomInfo rkadveRomDesc[]={
	{ "g_rkadve.bin", 0x100000, 0x8EEDFD51, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rkadve);
STD_ROM_FN(rkadve);

struct BurnDriverD BurnDrvMDrkadve = {
	"g_rkadve", NULL, NULL, "1900",
	"Rocket Knight Adventures (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rkadveRomInfo, rkadveRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rocket Knight Adventures (J) [!]

static struct BurnRomInfo rkadvjRomDesc[]={
	{ "g_rkadvj.bin", 0x100000, 0xD1C8C1C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rkadvj);
STD_ROM_FN(rkadvj);

struct BurnDriverD BurnDrvMDrkadvj = {
	"g_rkadvj", NULL, NULL, "1900",
	"Rocket Knight Adventures (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rkadvjRomInfo, rkadvjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rockman Megaworld (J) [a1][!]

static struct BurnRomInfo rkmnjaRomDesc[]={
	{ "g_rkmnja.bin", 0x200000, 0x4D87235E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rkmnja);
STD_ROM_FN(rkmnja);

struct BurnDriverD BurnDrvMDrkmnja = {
	"g_rkmnja", NULL, NULL, "1900",
	"Rockman Megaworld (J) [a1][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rkmnjaRomInfo, rkmnjaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rolling Thunder 2 (E) [c][!]

static struct BurnRomInfo rthn2eRomDesc[]={
	{ "g_rthn2e.bin", 0x100000, 0xC440F292, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rthn2e);
STD_ROM_FN(rthn2e);

struct BurnDriverD BurnDrvMDrthn2e = {
	"g_rthn2e", NULL, NULL, "1900",
	"Rolling Thunder 2 (E) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rthn2eRomInfo, rthn2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Rolling Thunder 2 (J) [c][!]

static struct BurnRomInfo rthn2jRomDesc[]={
	{ "g_rthn2j.bin", 0x100000, 0x965B2628, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rthn2j);
STD_ROM_FN(rthn2j);

struct BurnDriverD BurnDrvMDrthn2j = {
	"g_rthn2j", NULL, NULL, "1900",
	"Rolling Thunder 2 (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rthn2jRomInfo, rthn2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ronaldinho 98 (B) [c][!]

static struct BurnRomInfo ron98bRomDesc[]={
	{ "g_ron98b.bin", 0x200000, 0xDD27C84E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ron98b);
STD_ROM_FN(ron98b);

struct BurnDriverD BurnDrvMDron98b = {
	"g_ron98b", NULL, NULL, "1998",
	"Ronaldinho 98 (B) [c][!]\0", NULL, "bootleg", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ron98bRomInfo, ron98bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Task Force Harrier EX (J) [!]

static struct BurnRomInfo tfhxjRomDesc[]={
	{ "g_tfhxj.bin", 0x100000, 0xE9A54EED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tfhxj);
STD_ROM_FN(tfhxj);

struct BurnDriverD BurnDrvMDtfhxj = {
	"g_tfhxj", NULL, NULL, "1900",
	"Task Force Harrier EX (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tfhxjRomInfo, tfhxjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl (J) [!]

static struct BurnRomInfo tsbwljRomDesc[]={
	{ "g_tsbwlj.bin", 0x100000, 0x90C6E20C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsbwlj);
STD_ROM_FN(tsbwlj);

struct BurnDriverD BurnDrvMDtsbwlj = {
	"g_tsbwlj", NULL, NULL, "1900",
	"Tecmo Super Bowl (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsbwljRomInfo, tsbwljRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl (U) (Sep 1993) [!]

static struct BurnRomInfo tsbwluRomDesc[]={
	{ "g_tsbwlu.bin", 0x100000, 0xBD5933EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsbwlu);
STD_ROM_FN(tsbwlu);

struct BurnDriverD BurnDrvMDtsbwlu = {
	"g_tsbwlu", NULL, NULL, "1900",
	"Tecmo Super Bowl (U) (Sep 1993) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsbwluRomInfo, tsbwluRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super Bowl II SE (J) [!]

static struct BurnRomInfo tsbw2jRomDesc[]={
	{ "g_tsbw2j.bin", 0x200000, 0x32FB633D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsbw2j);
STD_ROM_FN(tsbw2j);

struct BurnDriverD BurnDrvMDtsbw2j = {
	"g_tsbw2j", NULL, NULL, "1900",
	"Tecmo Super Bowl II SE (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsbw2jRomInfo, tsbw2jRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Super NBA Basketball (J) [!]

static struct BurnRomInfo tsnbajRomDesc[]={
	{ "g_tsnbaj.bin", 0x100000, 0x79F33EB6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tsnbaj);
STD_ROM_FN(tsnbaj);

struct BurnDriverD BurnDrvMDtsnbaj = {
	"g_tsnbaj", NULL, NULL, "1900",
	"Tecmo Super NBA Basketball (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tsnbajRomInfo, tsnbajRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Ninja Turtles - Return of the Shredder (J) [!]

static struct BurnRomInfo tmntjRomDesc[]={
	{ "g_tmntj.bin", 0x100000, 0x1B003498, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tmntj);
STD_ROM_FN(tmntj);

struct BurnDriverD BurnDrvMDtmntj = {
	"g_tmntj", NULL, NULL, "1900",
	"Teenage Mutant Ninja Turtles - Return of the Shredder (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tmntjRomInfo, tmntjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Ninja Turtles - Tournament Fighters (J) [!]

static struct BurnRomInfo tmnttjRomDesc[]={
	{ "g_tmnttj.bin", 0x200000, 0x8843F2C9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tmnttj);
STD_ROM_FN(tmnttj);

struct BurnDriverD BurnDrvMDtmnttj = {
	"g_tmnttj", NULL, NULL, "1900",
	"Teenage Mutant Ninja Turtles - Tournament Fighters (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tmnttjRomInfo, tmnttjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Telebradesco Residencia (B) [!]

static struct BurnRomInfo telerbRomDesc[]={
	{ "g_telerb.bin", 0x040000, 0x1DB99045, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(telerb);
STD_ROM_FN(telerb);

struct BurnDriverD BurnDrvMDtelerb = {
	"g_telerb", NULL, NULL, "1900",
	"Telebradesco Residencia (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, telerbRomInfo, telerbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Thunder Fox (J) [c][!]

static struct BurnRomInfo tfoxjRomDesc[]={
	{ "g_tfoxj.bin", 0x100000, 0xECA6CFFA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tfoxj);
STD_ROM_FN(tfoxj);

struct BurnDriverD BurnDrvMDtfoxj = {
	"g_tfoxj", NULL, NULL, "1900",
	"Thunder Fox (J) [c][!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tfoxjRomInfo, tfoxjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Time Dominator 1st (J) [!]

static struct BurnRomInfo tdom1RomDesc[]={
	{ "g_tdom1.bin", 0x100000, 0x7EBA7A5C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tdom1);
STD_ROM_FN(tdom1);

struct BurnDriverD BurnDrvMDtdom1 = {
	"g_tdom1", NULL, NULL, "1993",
	"Time Dominator 1st (J) [!]\0", NULL, "Vic Tokai", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tdom1RomInfo, tdom1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Time Killers (E) [!]

static struct BurnRomInfo tkilleRomDesc[]={
	{ "g_tkille.bin", 0x200000, 0xA4F48A1A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tkille);
STD_ROM_FN(tkille);

struct BurnDriverD BurnDrvMDtkille = {
	"g_tkille", NULL, NULL, "1900",
	"Time Killers (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tkilleRomInfo, tkilleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tiny Toon Adventures - Buster's Hidden Treasure (E) [!]

static struct BurnRomInfo ttabeRomDesc[]={
	{ "g_ttabe.bin", 0x080000, 0xD10FBA51, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ttabe);
STD_ROM_FN(ttabe);

struct BurnDriverD BurnDrvMDttabe = {
	"g_ttabe", NULL, NULL, "1900",
	"Tiny Toon Adventures - Buster's Hidden Treasure (E) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ttabeRomInfo, ttabeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Todd's Adventures in Slime World (J) [!]

static struct BurnRomInfo toddjRomDesc[]={
	{ "g_toddj.bin", 0x080000, 0x7FF5529F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(toddj);
STD_ROM_FN(toddj);

struct BurnDriverD BurnDrvMDtoddj = {
	"g_toddj", NULL, NULL, "1900",
	"Todd's Adventures in Slime World (J) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, toddjRomInfo, toddjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tom and Jerry - Frantic Antics (U) (1993) [!]

static struct BurnRomInfo tajuaRomDesc[]={
	{ "g_tajua.bin", 0x100000, 0xB9992E1C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tajua);
STD_ROM_FN(tajua);

struct BurnDriverD BurnDrvMDtajua = {
	"g_tajua", NULL, NULL, "1900",
	"Tom and Jerry - Frantic Antics (U) (1993) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tajuaRomInfo, tajuaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Turma da Monica na Terra Dos Monstros (B) [!]

static struct BurnRomInfo turmaRomDesc[]={
	{ "g_turma.bin", 0x100000, 0xF8288DE1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(turma);
STD_ROM_FN(turma);

struct BurnDriverD BurnDrvMDturma = {
	"g_turma", NULL, NULL, "1900",
	"Turma da Monica na Terra Dos Monstros (B) [!]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, turmaRomInfo, turmaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Classic Collection (UE) [!]

static struct BurnRomInfo clasclRomDesc[]={
	{ "g_clascl.bin", 0x200000, 0x73F948B1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clascl);
STD_ROM_FN(clascl);

struct BurnDriverD BurnDrvMDclascl = {
	"g_clascl", NULL, NULL, "199?",
	"Classic Collection (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clasclRomInfo, clasclRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Megadrive 6-Pak (U) [!]

static struct BurnRomInfo gen6pkRomDesc[]={
	{ "g_gen6pk.bin", 0x300000, 0x1A6F45DC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gen6pk);
STD_ROM_FN(gen6pk);

struct BurnDriverD BurnDrvMDgen6pk = {
	"g_gen6pk", NULL, NULL, "199?",
	"Megadrive 6-Pak (U) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gen6pkRomInfo, gen6pkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 2 (E) [!]

static struct BurnRomInfo mg2eRomDesc[]={
	{ "g_mg2e.bin", 0x200000, 0x30D59F2F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg2e);
STD_ROM_FN(mg2e);

struct BurnDriverD BurnDrvMDmg2e = {
	"g_mg2e", NULL, NULL, "199?",
	"Mega Games 2 (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg2eRomInfo, mg2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 3 (E) [!]

static struct BurnRomInfo mg3eRomDesc[]={
	{ "g_mg3e.bin", 0x200000, 0xB4247D98, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg3e);
STD_ROM_FN(mg3e);

struct BurnDriverD BurnDrvMDmg3e = {
	"g_mg3e", NULL, NULL, "199?",
	"Mega Games 3 (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg3eRomInfo, mg3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 6 (Vol 1) (E) [!]

static struct BurnRomInfo mg6v1eRomDesc[]={
	{ "g_mg6v1e.bin", 0x300000, 0xB66FB80D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg6v1e);
STD_ROM_FN(mg6v1e);

struct BurnDriverD BurnDrvMDmg6v1e = {
	"g_mg6v1e", NULL, NULL, "199?",
	"Mega Games 6 (Vol 1) (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg6v1eRomInfo, mg6v1eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 6 (Vol 2) (E) [!]

static struct BurnRomInfo mg6v2eRomDesc[]={
	{ "g_mg6v2e.bin", 0x300000, 0xE8D10DB9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg6v2e);
STD_ROM_FN(mg6v2e);

struct BurnDriverD BurnDrvMDmg6v2e = {
	"g_mg6v2e", NULL, NULL, "199?",
	"Mega Games 6 (Vol 2) (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg6v2eRomInfo, mg6v2eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 6 (Vol 3) (E) [!]

static struct BurnRomInfo mg6v3eRomDesc[]={
	{ "g_mg6v3e.bin", 0x300000, 0xFE3E7E4F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg6v3e);
STD_ROM_FN(mg6v3e);

struct BurnDriverD BurnDrvMDmg6v3e = {
	"g_mg6v3e", NULL, NULL, "199?",
	"Mega Games 6 (Vol 3) (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg6v3eRomInfo, mg6v3eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games 10 in 1 (EB) [!]

static struct BurnRomInfo mg10i1RomDesc[]={
	{ "g_mg10i1.bin", 0x400000, 0xC19AE368, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg10i1);
STD_ROM_FN(mg10i1);

struct BurnDriverD BurnDrvMDmg10i1 = {
	"g_mg10i1", NULL, NULL, "199?",
	"Mega Games 10 in 1 (EB) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg10i1RomInfo, mg10i1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Games I (E) [!]

static struct BurnRomInfo mg1eRomDesc[]={
	{ "g_mg1e.bin", 0x100000, 0xDB753224, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mg1e);
STD_ROM_FN(mg1e);

struct BurnDriverD BurnDrvMDmg1e = {
	"g_mg1e", NULL, NULL, "199?",
	"Mega Games I (E) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mg1eRomInfo, mg1eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Menacer 6-in-1 Game Pack (UE) [!]

static struct BurnRomInfo menaceRomDesc[]={
	{ "g_menace.bin", 0x100000, 0x936B85F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(menace);
STD_ROM_FN(menace);

struct BurnDriverD BurnDrvMDmenace = {
	"g_menace", NULL, NULL, "199?",
	"Menacer 6-in-1 Game Pack (UE) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, menaceRomInfo, menaceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sega Sports 1 (Wimbledo

static struct BurnRomInfo segsp1RomDesc[]={
	{ "g_segsp1.bin", 0x280000, 0x07FEDAF1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(segsp1);
STD_ROM_FN(segsp1);

struct BurnDriverD BurnDrvMDsegsp1 = {
	"g_segsp1", NULL, NULL, "199?",
	"Sega Sports 1 (Wimbledo\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, segsp1RomInfo, segsp1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sega Top 5 (B) [!]

static struct BurnRomInfo stop5bRomDesc[]={
	{ "g_stop5b.bin", 0x200000, 0x61069069, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stop5b);
STD_ROM_FN(stop5b);

struct BurnDriverD BurnDrvMDstop5b = {
	"g_stop5b", NULL, NULL, "199?",
	"Sega Top 5 (B) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stop5bRomInfo, stop5bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Classics (Compilation) (E) (REV00) [!]

static struct BurnRomInfo soncleRomDesc[]={
	{ "g_soncle.bin", 0x300000, 0x8C70B84E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soncle);
STD_ROM_FN(soncle);

struct BurnDriverD BurnDrvMDsoncle = {
	"g_soncle", "g_sonclu", NULL, "199?",
	"Sonic Classics (Compilation) (E) (REV00) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soncleRomInfo, soncleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Classics (Compilation) (UE) (REV01) [!]

static struct BurnRomInfo soncluRomDesc[]={
	{ "g_sonclu.bin", 0x300000, 0x95B5E8D7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sonclu);
STD_ROM_FN(sonclu);

struct BurnDriverD BurnDrvMDsonclu = {
	"g_sonclu", NULL, NULL, "199?",
	"Sonic Classics (Compilation) (UE) (REV01) [!]\0", "Bad sound", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soncluRomInfo, soncluRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sport Games (B) [c][!]

static struct BurnRomInfo sptgbRomDesc[]={
	{ "g_sptgb.bin", 0x200000, 0x7E3ECABF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sptgb);
STD_ROM_FN(sptgb);

struct BurnDriverD BurnDrvMDsptgb = {
	"g_sptgb", NULL, NULL, "199?",
	"Sport Games (B) [c][!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sptgbRomInfo, sptgbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Addams Family, The (Beta)

static struct BurnRomInfo adambRomDesc[]={
	{ "g_adamb.bin", 0x100000, 0x2803A5CA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(adamb);
STD_ROM_FN(adamb);

struct BurnDriver BurnDrvMDadamb = {
	"g_adamb", "g_afam", NULL, "1900",
	"Addams Family, The (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, adambRomInfo, adambRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Adventures of Mighty Ma

static struct BurnRomInfo mmaxeRomDesc[]={
	{ "g_mmaxe.bin", 0x100000, 0x24F1A3BB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmaxe);
STD_ROM_FN(mmaxe);

struct BurnDriverD BurnDrvMDmmaxe = {
	"g_mmaxe", NULL, NULL, "1900",
	"Adventures of Mighty Ma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmaxeRomInfo, mmaxeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Andre Agassi Tennis (Beta)

static struct BurnRomInfo aatebRomDesc[]={
	{ "g_aateb.bin", 0x080000, 0x3BBF700D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aateb);
STD_ROM_FN(aateb);

struct BurnDriverD BurnDrvMDaateb = {
	"g_aateb", "g_aate", NULL, "1900",
	"Andre Agassi Tennis (Beta)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aatebRomInfo, aatebRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ATP Tour Championship Tennis (E)

static struct BurnRomInfo atpteRomDesc[]={
	{ "g_atpte.bin", 0x200000, 0x1A3DA8C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(atpte);
STD_ROM_FN(atpte);

struct BurnDriverD BurnDrvMDatpte = {
	"g_atpte", "g_atpt", NULL, "1900",
	"ATP Tour Championship Tennis (E)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, atpteRomInfo, atpteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Awesome Possum Kicks Dr. Machino's Butt! (Beta)

static struct BurnRomInfo awsepRomDesc[]={
	{ "g_awsep.bin", 0x200000, 0x0158DC53, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(awsep);
STD_ROM_FN(awsep);

struct BurnDriverD BurnDrvMDawsep = {
	"g_awsep", "g_awep", NULL, "1900",
	"Awesome Possum Kicks Dr. Machino's Butt! (Beta)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, awsepRomInfo, awsepRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// B.O.B (Beta)

static struct BurnRomInfo bobbRomDesc[]={
	{ "g_bobb.bin", 0x100000, 0xE3E8421E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bobb);
STD_ROM_FN(bobb);

struct BurnDriverD BurnDrvMDbobb = {
	"g_bobb", "g_bob", NULL, "1994",
	"B.O.B (Beta)\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bobbRomInfo, bobbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Baby's Day Out (Beta 1)

static struct BurnRomInfo babyb1RomDesc[]={
	{ "g_babyb1.bin", 0x100000, 0x459B891C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(babyb1);
STD_ROM_FN(babyb1);

struct BurnDriverD BurnDrvMDbabyb1 = {
	"g_babyb1", "g_babyb2", NULL, "1900",
	"Baby's Day Out (Beta 1)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, babyb1RomInfo, babyb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Baby's Day Out (Beta 2)

static struct BurnRomInfo babyb2RomDesc[]={
	{ "g_babyb2.bin", 0x100000, 0xB2E7CC49, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(babyb2);
STD_ROM_FN(babyb2);

struct BurnDriver BurnDrvMDbabyb2 = {
	"g_babyb2", NULL, NULL, "1900",
	"Baby's Day Out (Beta 2)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, babyb2RomInfo, babyb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Barbie Vacation Adventure (Beta)

static struct BurnRomInfo barbvbRomDesc[]={
	{ "g_barbvb.bin", 0x100000, 0x10E0BA69, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(barbvb);
STD_ROM_FN(barbvb);

struct BurnDriverD BurnDrvMDbarbvb = {
	"g_barbvb", NULL, NULL, "1900",
	"Barbie Vacation Adventure (Beta)\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, barbvbRomInfo, barbvbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bare Knuckle II (Beta)

static struct BurnRomInfo bk2bRomDesc[]={
	{ "g_bk2b.bin", 0x130000, 0x0CF2ACBE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bk2b);
STD_ROM_FN(bk2b);

struct BurnDriver BurnDrvMDbk2b = {
	"g_bk2b", "g_sor2", NULL, "1992",
	"Bare Knuckle II (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bk2bRomInfo, bk2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bare Knuckle III (Beta)

static struct BurnRomInfo bk3bRomDesc[]={
	{ "g_bk3b.bin", 0x300000, 0xE7FF99DB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bk3b);
STD_ROM_FN(bk3b);

struct BurnDriver BurnDrvMDbk3b = {
	"g_bk3b", "g_sor3", NULL, "1994",
	"Bare Knuckle III (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bk3bRomInfo, bk3bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Batman (E)

static struct BurnRomInfo batmeRomDesc[]={
	{ "g_batme.bin", 0x080000, 0x61C60C35, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(batme);
STD_ROM_FN(batme);

struct BurnDriverD BurnDrvMDbatme = {
	"g_batme", "g_bat", NULL, "1900",
	"Batman (E)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, batmeRomInfo, batmeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beavis and Butt-head (Beta)

static struct BurnRomInfo beavibRomDesc[]={
	{ "g_beavib.bin", 0x200000, 0x81ED5335, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beavib);
STD_ROM_FN(beavib);

struct BurnDriverD BurnDrvMDbeavib = {
	"g_beavib", "g_beav", NULL, "1900",
	"Beavis and Butt-head (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beavibRomInfo, beavibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Best of the Best - Championship Karate (Beta)

static struct BurnRomInfo botbbRomDesc[]={
	{ "g_botbb.bin", 0x100000, 0xF842240B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(botbb);
STD_ROM_FN(botbb);

struct BurnDriver BurnDrvMDbotbb = {
	"g_botbb", "g_botb", NULL, "1900",
	"Best of the Best - Championship Karate (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, botbbRomInfo, botbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Beyond Zero Tolerance (Beta)

static struct BurnRomInfo bzerotRomDesc[]={
	{ "g_bzerot.bin", 0x200000, 0xC61ED2ED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bzerot);
STD_ROM_FN(bzerot);

struct BurnDriver BurnDrvMDbzerot = {
	"g_bzerot", NULL, NULL, "1900",
	"Beyond Zero Tolerance (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bzerotRomInfo, bzerotRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bio-Hazard Battle (Beta)

static struct BurnRomInfo biohzbRomDesc[]={
	{ "g_biohzb.bin", 0x100000, 0xDD10DD1A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(biohzb);
STD_ROM_FN(biohzb);

struct BurnDriver BurnDrvMDbiohzb = {
	"g_biohzb", "g_bhb", NULL, "1900",
	"Bio-Hazard Battle (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, biohzbRomInfo, biohzbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blaster Master 2 (Beta)

static struct BurnRomInfo blam2bRomDesc[]={
	{ "g_blam2b.bin", 0x100000, 0x08F78C70, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blam2b);
STD_ROM_FN(blam2b);

struct BurnDriverD BurnDrvMDblam2b = {
	"g_blam2b", "g_blma", NULL, "1900",
	"Blaster Master 2 (Beta)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blam2bRomInfo, blam2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Blockbuster World Video Game Championship II (U)

static struct BurnRomInfo blocb2RomDesc[]={
	{ "g_blocb2.bin", 0x400000, 0x4385E366, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blocb2);
STD_ROM_FN(blocb2);

struct BurnDriverD BurnDrvMDblocb2 = {
	"g_blocb2", NULL, NULL, "1900",
	"Blockbuster World Video Game Championship II (U)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	0, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blocb2RomInfo, blocb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Body Count (Beta) (M5)

static struct BurnRomInfo bcounbRomDesc[]={
	{ "g_bcounb.bin", 0x100000, 0xB4FFB6CE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bcounb);
STD_ROM_FN(bcounb);

struct BurnDriverD BurnDrvMDbcounb = {
	"g_bcounb", "g_body", NULL, "1900",
	"Body Count (Beta) (M5)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bcounbRomInfo, bcounbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brian Lara Cricket (Beta)

static struct BurnRomInfo blcrbRomDesc[]={
	{ "g_blcrb.bin", 0x100000, 0x90F5C2B7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blcrb);
STD_ROM_FN(blcrb);

struct BurnDriverD BurnDrvMDblcrb = {
	"g_blcrb", "g_blcr", NULL, "1900",
	"Brian Lara Cricket (Beta)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blcrbRomInfo, blcrbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brutal - Paws of Fury (E)

static struct BurnRomInfo brutleRomDesc[]={
	{ "g_brutle.bin", 0x200000, 0x7E9A8D32, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(brutle);
STD_ROM_FN(brutle);

struct BurnDriverD BurnDrvMDbrutle = {
	"g_brutle", "g_brpw", NULL, "1900",
	"Brutal - Paws of Fury (E)\0", "No sound in-game", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, brutleRomInfo, brutleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Bubba N Stix (Beta)

static struct BurnRomInfo bubbabRomDesc[]={
	{ "g_bubbab.bin", 0x100000, 0xA8731CB4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(bubbab);
STD_ROM_FN(bubbab);

struct BurnDriverD BurnDrvMDbubbab = {
	"g_bubbab", "g_buba", NULL, "1900",
	"Bubba N Stix (Beta)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, bubbabRomInfo, bubbabRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Burning Force (E)

static struct BurnRomInfo burnfeRomDesc[]={
	{ "g_burnfe.bin", 0x080000, 0x776FF6FF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(burnfe);
STD_ROM_FN(burnfe);

struct BurnDriverD BurnDrvMDburnfe = {
	"g_burnfe", "g_burf", NULL, "1900",
	"Burning Force (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, burnfeRomInfo, burnfeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Caesar no Yabo (J)

static struct BurnRomInfo caenoRomDesc[]={
	{ "g_caeno.bin", 0x100000, 0x69796E93, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(caeno);
STD_ROM_FN(caeno);

struct BurnDriverD BurnDrvMDcaeno = {
	"g_caeno", NULL, NULL, "1991",
	"Caesar no Yabo (J)\0", NULL, "Micronet", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, caenoRomInfo, caenoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Caesar no Yabo II (J)

static struct BurnRomInfo caeno2RomDesc[]={
	{ "g_caeno2.bin", 0x100000, 0x4F327B3A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(caeno2);
STD_ROM_FN(caeno2);

struct BurnDriverD BurnDrvMDcaeno2 = {
	"g_caeno2", NULL, NULL, "1992",
	"Caesar no Yabo II (J)\0", NULL, "Micronet", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, caeno2RomInfo, caeno2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Captain America and the Avengers (Beta)

static struct BurnRomInfo capambRomDesc[]={
	{ "g_capamb.bin", 0x100000, 0xBAAC59C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(capamb);
STD_ROM_FN(capamb);

struct BurnDriverD BurnDrvMDcapamb = {
	"g_capamb", NULL, NULL, "1900",
	"Captain America and the Avengers (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, capambRomInfo, capambRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Captain America and the Avengers (E)

static struct BurnRomInfo capameRomDesc[]={
	{ "g_capame.bin", 0x100000, 0x43225612, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(capame);
STD_ROM_FN(capame);

struct BurnDriverD BurnDrvMDcapame = {
	"g_capame", NULL, NULL, "1900",
	"Captain America and the Avengers (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, capameRomInfo, capameRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Captain Planet and the Planeteers (Beta)

static struct BurnRomInfo cappbRomDesc[]={
	{ "g_cappb.bin", 0x080000, 0xBF2CBD3A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cappb);
STD_ROM_FN(cappb);

struct BurnDriverD BurnDrvMDcappb = {
	"g_cappb", NULL, NULL, "1900",
	"Captain Planet and the Planeteers (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cappbRomInfo, cappbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Castlevania - The New Generation (Beta)

static struct BurnRomInfo cvtngbRomDesc[]={
	{ "g_cvtngb.bin", 0x100000, 0x84CD103A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cvtngb);
STD_ROM_FN(cvtngb);

struct BurnDriverD BurnDrvMDcvtngb = {
	"g_cvtngb", NULL, NULL, "1994",
	"Castlevania - The New Generation (Beta)\0", NULL, "Konami", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cvtngbRomInfo, cvtngbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chaos Engin

static struct BurnRomInfo cengbRomDesc[]={
	{ "g_cengb.bin", 0x100000, 0x3FB045C2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cengb);
STD_ROM_FN(cengb);

struct BurnDriverD BurnDrvMDcengb = {
	"g_cengb", NULL, NULL, "1900",
	"Chaos Engin\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cengbRomInfo, cengbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck II - Son of Chuck (Beta)

static struct BurnRomInfo chk2bRomDesc[]={
	{ "g_chk2b.bin", 0x100000, 0xD6A3B324, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chk2b);
STD_ROM_FN(chk2b);

struct BurnDriverD BurnDrvMDchk2b = {
	"g_chk2b", NULL, NULL, "1900",
	"Chuck II - Son of Chuck (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chk2bRomInfo, chk2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Chuck's Excellent Art Tool Animator (U)

static struct BurnRomInfo chuckRomDesc[]={
	{ "g_chuck.bin", 0x060000, 0x6360EE58, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(chuck);
STD_ROM_FN(chuck);

struct BurnDriverD BurnDrvMDchuck = {
	"g_chuck", NULL, NULL, "1900",
	"Chuck's Excellent Art Tool Animator (U)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, chuckRomInfo, chuckRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cliffhanger (Beta)

static struct BurnRomInfo clifhbRomDesc[]={
	{ "g_clifhb.bin", 0x100000, 0x628251FD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clifhb);
STD_ROM_FN(clifhb);

struct BurnDriverD BurnDrvMDclifhb = {
	"g_clifhb", NULL, NULL, "1900",
	"Cliffhanger (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clifhbRomInfo, clifhbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cliffhanger (E)

static struct BurnRomInfo clifheRomDesc[]={
	{ "g_clifhe.bin", 0x100000, 0x35BFF1FD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(clifhe);
STD_ROM_FN(clifhe);

struct BurnDriverD BurnDrvMDclifhe = {
	"g_clifhe", NULL, NULL, "1900",
	"Cliffhanger (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, clifheRomInfo, clifheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Combat Aces (Beta)

static struct BurnRomInfo comacbRomDesc[]={
	{ "g_comacb.bin", 0x080000, 0x84560D5A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comacb);
STD_ROM_FN(comacb);

struct BurnDriverD BurnDrvMDcomacb = {
	"g_comacb", NULL, NULL, "1900",
	"Combat Aces (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comacbRomInfo, comacbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Comix Zone (Beta)

static struct BurnRomInfo comixbRomDesc[]={
	{ "g_comixb.bin", 0x200000, 0x2EFCB6EE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(comixb);
STD_ROM_FN(comixb);

struct BurnDriverD BurnDrvMDcomixb = {
	"g_comixb", NULL, NULL, "1995",
	"Comix Zone (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, comixbRomInfo, comixbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cool Spot (Beta)

static struct BurnRomInfo spotbRomDesc[]={
	{ "g_spotb.bin", 0x100000, 0x0EBAA4A8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(spotb);
STD_ROM_FN(spotb);

struct BurnDriverD BurnDrvMDspotb = {
	"g_spotb", NULL, NULL, "1900",
	"Cool Spot (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, spotbRomInfo, spotbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Cyborg Justice (Beta)

static struct BurnRomInfo cyjusbRomDesc[]={
	{ "g_cyjusb.bin", 0x080000, 0x91DAF11E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(cyjusb);
STD_ROM_FN(cyjusb);

struct BurnDriverD BurnDrvMDcyjusb = {
	"g_cyjusb", NULL, NULL, "1993",
	"Cyborg Justice (Beta)\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, cyjusbRomInfo, cyjusbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daffy Duck in Hollywood (Beta)

static struct BurnRomInfo daffybRomDesc[]={
	{ "g_daffyb.bin", 0x200000, 0x0EAA4740, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daffyb);
STD_ROM_FN(daffyb);

struct BurnDriverD BurnDrvMDdaffyb = {
	"g_daffyb", NULL, NULL, "1900",
	"Daffy Duck in Hollywood (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daffybRomInfo, daffybRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daikoukai Jidai II (J)

static struct BurnRomInfo daik2RomDesc[]={
	{ "g_daik2.bin", 0x200000, 0xE040F0DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(daik2);
STD_ROM_FN(daik2);

struct BurnDriverD BurnDrvMDdaik2 = {
	"g_daik2", NULL, NULL, "1900",
	"Daikoukai Jidai II (J)\0", NULL, "Koei", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, daik2RomInfo, daik2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Darius II (J) [a1]

static struct BurnRomInfo dari2aRomDesc[]={
	{ "g_dari2a.bin", 0x100000, 0x0140AB58, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dari2a);
STD_ROM_FN(dari2a);

struct BurnDriverD BurnDrvMDdari2a = {
	"g_dari2a", NULL, NULL, "1900",
	"Darius II (J) [a1]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dari2aRomInfo, dari2aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dashin' Desperadoes (Beta)

static struct BurnRomInfo dashbRomDesc[]={
	{ "g_dashb.bin", 0x100000, 0xADAFFC3F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dashb);
STD_ROM_FN(dashb);

struct BurnDriverD BurnDrvMDdashb = {
	"g_dashb", NULL, NULL, "1900",
	"Dashin' Desperadoes (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dashbRomInfo, dashbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Davis Cup World Tour Tennis 2 (Beta 1)

static struct BurnRomInfo dwctb1RomDesc[]={
	{ "g_dwctb1.bin", 0x200000, 0x6F4183C0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dwctb1);
STD_ROM_FN(dwctb1);

struct BurnDriverD BurnDrvMDdwctb1 = {
	"g_dwctb1", NULL, NULL, "1900",
	"Davis Cup World Tour Tennis 2 (Beta 1)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dwctb1RomInfo, dwctb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Davis Cup World Tour Tennis 2 (Beta 2)

static struct BurnRomInfo dwctb2RomDesc[]={
	{ "g_dwctb2.bin", 0x200000, 0x76F2BED8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dwctb2);
STD_ROM_FN(dwctb2);

struct BurnDriverD BurnDrvMDdwctb2 = {
	"g_dwctb2", NULL, NULL, "1900",
	"Davis Cup World Tour Tennis 2 (Beta 2)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dwctb2RomInfo, dwctb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Davis Cup World Tour Tennis 2 (Beta 1)

static struct BurnRomInfo dwctbRomDesc[]={
	{ "g_dwctb.bin", 0x100000, 0x7C6B0646, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dwctb);
STD_ROM_FN(dwctb);

struct BurnDriverD BurnDrvMDdwctb = {
	"g_dwctb", NULL, NULL, "1900",
	"Davis Cup World Tour Tennis 2 (Beta 1)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dwctbRomInfo, dwctbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Daze Before Christma

static struct BurnRomInfo dazebRomDesc[]={
	{ "g_dazeb.bin", 0x200000, 0x317C9491, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dazeb);
STD_ROM_FN(dazeb);

struct BurnDriverD BurnDrvMDdazeb = {
	"g_dazeb", NULL, NULL, "1900",
	"Daze Before Christma\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dazebRomInfo, dazebRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Demolition Man (Beta)

static struct BurnRomInfo demombRomDesc[]={
	{ "g_demomb.bin", 0x200000, 0x57FFAD7A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(demomb);
STD_ROM_FN(demomb);

struct BurnDriverD BurnDrvMDdemomb = {
	"g_demomb", NULL, NULL, "1900",
	"Demolition Man (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, demombRomInfo, demombRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dominus (Beta)

static struct BurnRomInfo dominuRomDesc[]={
	{ "g_dominu.bin", 0x0C0000, 0x30006EBD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dominu);
STD_ROM_FN(dominu);

struct BurnDriverD BurnDrvMDdominu = {
	"g_dominu", NULL, NULL, "1900",
	"Dominus (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dominuRomInfo, dominuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dr. Robotnik's Mean Bean Machine (Beta)

static struct BurnRomInfo beanbRomDesc[]={
	{ "g_beanb.bin", 0x100000, 0x4D0E5273, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(beanb);
STD_ROM_FN(beanb);

struct BurnDriverD BurnDrvMDbeanb = {
	"g_beanb", "g_bean", NULL, "1900",
	"Dr. Robotnik's Mean Bean Machine (Beta)\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, beanbRomInfo, beanbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dragon - The Bruce Lee Story (E)

static struct BurnRomInfo drgbleRomDesc[]={
	{ "g_drgble.bin", 0x200000, 0xFDEED51D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(drgble);
STD_ROM_FN(drgble);

struct BurnDriverD BurnDrvMDdrgble = {
	"g_drgble", "g_blee", NULL, "1900",
	"Dragon - The Bruce Lee Story (E)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, drgbleRomInfo, drgbleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dune - Der Kampf um den Wuestenplaneten (G)

static struct BurnRomInfo dunegRomDesc[]={
	{ "g_duneg.bin", 0x100000, 0x39790728, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(duneg);
STD_ROM_FN(duneg);

struct BurnDriverD BurnDrvMDduneg = {
	"g_duneg", NULL, NULL, "1900",
	"Dune - Der Kampf um den Wuestenplaneten (G)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dunegRomInfo, dunegRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dune - The Battle for Arrakis (E)

static struct BurnRomInfo duneeRomDesc[]={
	{ "g_dunee.bin", 0x100000, 0xB58AE71D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dunee);
STD_ROM_FN(dunee);

struct BurnDriverD BurnDrvMDdunee = {
	"g_dunee", NULL, NULL, "1900",
	"Dune - The Battle for Arrakis (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, duneeRomInfo, duneeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dyna Brothers (J) (REV01)

static struct BurnRomInfo dynabrRomDesc[]={
	{ "g_dynabr.bin", 0x100000, 0x360C1B20, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dynabr);
STD_ROM_FN(dynabr);

struct BurnDriverD BurnDrvMDdynabr = {
	"g_dynabr", NULL, NULL, "1900",
	"Dyna Brothers (J) (REV01)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dynabrRomInfo, dynabrRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Dynamite Headdy (Beta)

static struct BurnRomInfo dheadbRomDesc[]={
	{ "g_dheadb.bin", 0x200000, 0x5C25E934, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dheadb);
STD_ROM_FN(dheadb);

struct BurnDriverD BurnDrvMDdheadb = {
	"g_dheadb", NULL, NULL, "1900",
	"Dynamite Headdy (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dheadbRomInfo, dheadbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ECCO - The Tides of Time (Beta)

static struct BurnRomInfo ecco2bRomDesc[]={
	{ "g_ecco2b.bin", 0x200000, 0x1D1470EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ecco2b);
STD_ROM_FN(ecco2b);

struct BurnDriverD BurnDrvMDecco2b = {
	"g_ecco2b", NULL, NULL, "1994",
	"ECCO - The Tides of Time (Beta)\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ecco2bRomInfo, ecco2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// ESPN National Hockey Night (Beta)

static struct BurnRomInfo e_nhbRomDesc[]={
	{ "g_e_nhb.bin", 0x200000, 0xA427814A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(e_nhb);
STD_ROM_FN(e_nhb);

struct BurnDriverD BurnDrvMDe_nhb = {
	"g_e_nhb", NULL, NULL, "1900",
	"ESPN National Hockey Night (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, e_nhbRomInfo, e_nhbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Eternal Champions (Beta)

static struct BurnRomInfo etchmbRomDesc[]={
	{ "g_etchmb.bin", 0x300000, 0xE0665F06, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(etchmb);
STD_ROM_FN(etchmb);

struct BurnDriverD BurnDrvMDetchmb = {
	"g_etchmb", NULL, NULL, "1900",
	"Eternal Champions (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, etchmbRomInfo, etchmbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Exo-Squad (Beta)

static struct BurnRomInfo exosbRomDesc[]={
	{ "g_exosb.bin", 0x100000, 0x70EDF964, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exosb);
STD_ROM_FN(exosb);

struct BurnDriverD BurnDrvMDexosb = {
	"g_exosb", NULL, NULL, "1900",
	"Exo-Squad (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exosbRomInfo, exosbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ex-Ranza (Beta)

static struct BurnRomInfo exrnzbRomDesc[]={
	{ "g_exrnzb.bin", 0x100000, 0xC642FDF4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(exrnzb);
STD_ROM_FN(exrnzb);

struct BurnDriverD BurnDrvMDexrnzb = {
	"g_exrnzb", NULL, NULL, "1993",
	"Ex-Ranza (Beta)\0", NULL, "Sega / Gau", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, exrnzbRomInfo, exrnzbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F1 World Championship Edition (Beta)

static struct BurnRomInfo f1wcebRomDesc[]={
	{ "g_f1wceb.bin", 0x200000, 0x2269ED6B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f1wceb);
STD_ROM_FN(f1wceb);

struct BurnDriverD BurnDrvMDf1wceb = {
	"g_f1wceb", NULL, NULL, "1900",
	"F1 World Championship Edition (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f1wcebRomInfo, f1wcebRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// F-15 Strike Eagle II (Beta)

static struct BurnRomInfo f15bRomDesc[]={
	{ "g_f15b.bin", 0x100000, 0xFD4F5A01, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(f15b);
STD_ROM_FN(f15b);

struct BurnDriverD BurnDrvMDf15b = {
	"g_f15b", NULL, NULL, "1900",
	"F-15 Strike Eagle II (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, f15bRomInfo, f15bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fatal Fury (E)

static struct BurnRomInfo fatfueRomDesc[]={
	{ "g_fatfue.bin", 0x180000, 0x2E730A91, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fatfue);
STD_ROM_FN(fatfue);

struct BurnDriverD BurnDrvMDfatfue = {
	"g_fatfue", NULL, NULL, "1993",
	"Fatal Fury (E)\0", NULL, "SNK / Takara", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fatfueRomInfo, fatfueRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ferrari Grand Prix Challenge (Beta)

static struct BurnRomInfo fergpbRomDesc[]={
	{ "g_fergpb.bin", 0x100000, 0xD48D02D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fergpb);
STD_ROM_FN(fergpb);

struct BurnDriverD BurnDrvMDfergpb = {
	"g_fergpb", NULL, NULL, "1900",
	"Ferrari Grand Prix Challenge (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fergpbRomInfo, fergpbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Fun-N-Games (E)

static struct BurnRomInfo funngeRomDesc[]={
	{ "g_funnge.bin", 0x100000, 0xDA4AB3CD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(funnge);
STD_ROM_FN(funnge);

struct BurnDriverD BurnDrvMDfunnge = {
	"g_funnge", NULL, NULL, "1900",
	"Fun-N-Games (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, funngeRomInfo, funngeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Futbol Argentino 98 - Pasion de Multitudes (Unl)

static struct BurnRomInfo fut98RomDesc[]={
	{ "g_fut98.bin", 0x200000, 0x5C015888, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(fut98);
STD_ROM_FN(fut98);

struct BurnDriver BurnDrvMDfut98 = {
	"g_fut98", "g_fi95", NULL, "1900",
	"Futbol Argentino 98 - Pasion de Multitudes (Unl)\0", NULL, "Unknown (Unlicensed)", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, fut98RomInfo, fut98RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Galaxy Force II (W) (REV00)

static struct BurnRomInfo glf200RomDesc[]={
	{ "g_glf200.bin", 0x100000, 0xCAE883C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(glf200);
STD_ROM_FN(glf200);

struct BurnDriverD BurnDrvMDglf200 = {
	"g_glf200", NULL, NULL, "1900",
	"Galaxy Force II (W) (REV00)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, glf200RomInfo, glf200RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gauntlet 4 (UE) (Sep 1993)

static struct BurnRomInfo gaun4aRomDesc[]={
	{ "g_gaun4a.bin", 0x100000, 0xF9D60510, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gaun4a);
STD_ROM_FN(gaun4a);

struct BurnDriverD BurnDrvMDgaun4a = {
	"g_gaun4a", NULL, NULL, "1994",
	"Gauntlet 4 (UE) (Sep 1993)\0", NULL, "Tengen / Atari", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gaun4aRomInfo, gaun4aRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// G-LOC Air Battle (Beta)

static struct BurnRomInfo glocbRomDesc[]={
	{ "g_glocb.bin", 0x100000, 0x175C7E63, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(glocb);
STD_ROM_FN(glocb);

struct BurnDriverD BurnDrvMDglocb = {
	"g_glocb", NULL, NULL, "1900",
	"G-LOC Air Battle (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, glocbRomInfo, glocbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Gods (Beta)

static struct BurnRomInfo godsbRomDesc[]={
	{ "g_godsb.bin", 0x100000, 0x2C06BB64, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(godsb);
STD_ROM_FN(godsb);

struct BurnDriverD BurnDrvMDgodsb = {
	"g_godsb", NULL, NULL, "1900",
	"Gods (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, godsbRomInfo, godsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Golden Axe II (Beta)

static struct BurnRomInfo gax2bRomDesc[]={
	{ "g_gax2b.bin", 0x080000, 0xE62EA1BB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(gax2b);
STD_ROM_FN(gax2b);

struct BurnDriverD BurnDrvMDgax2b = {
	"g_gax2b", NULL, NULL, "1900",
	"Golden Axe II (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, gax2bRomInfo, gax2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hellfire (E)

static struct BurnRomInfo helfieRomDesc[]={
	{ "g_helfie.bin", 0x080000, 0xCF30ACEC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(helfie);
STD_ROM_FN(helfie);

struct BurnDriverD BurnDrvMDhelfie = {
	"g_helfie", NULL, NULL, "1900",
	"Hellfire (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, helfieRomInfo, helfieRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Home Alone (Beta)

static struct BurnRomInfo homeabRomDesc[]={
	{ "g_homeab.bin", 0x100000, 0x3A235FB9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(homeab);
STD_ROM_FN(homeab);

struct BurnDriverD BurnDrvMDhomeab = {
	"g_homeab", NULL, NULL, "1900",
	"Home Alone (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, homeabRomInfo, homeabRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hyper Dunk - The Playoff Edition (Beta)

static struct BurnRomInfo hdunkbRomDesc[]={
	{ "g_hdunkb.bin", 0x200000, 0xDB124BBB, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hdunkb);
STD_ROM_FN(hdunkb);

struct BurnDriverD BurnDrvMDhdunkb = {
	"g_hdunkb", NULL, NULL, "1900",
	"Hyper Dunk - The Playoff Edition (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hdunkbRomInfo, hdunkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// I Love Mickey & Donald - Fushigi na Magic Box (J)

static struct BurnRomInfo micdoRomDesc[]={
	{ "g_micdo.bin", 0x100000, 0xCB9EE238, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micdo);
STD_ROM_FN(micdo);

struct BurnDriverD BurnDrvMDmicdo = {
	"g_micdo", NULL, NULL, "1992",
	"I Love Mickey & Donald - Fushigi na Magic Box (J)\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micdoRomInfo, micdoRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Incredible Crash Dummie

static struct BurnRomInfo icdbRomDesc[]={
	{ "g_icdb.bin", 0x100000, 0x623A920F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(icdb);
STD_ROM_FN(icdb);

struct BurnDriverD BurnDrvMDicdb = {
	"g_icdb", NULL, NULL, "1900",
	"Incredible Crash Dummie\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, icdbRomInfo, icdbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// It Came From The Desert (Beta)

static struct BurnRomInfo icftdRomDesc[]={
	{ "g_icftd.bin", 0x080000, 0x25AFB4F7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(icftd);
STD_ROM_FN(icftd);

struct BurnDriverD BurnDrvMDicftd = {
	"g_icftd", NULL, NULL, "1900",
	"It Came From The Desert (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, icftdRomInfo, icftdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// James Bond 007 - The Duel (W)

static struct BurnRomInfo jbondwRomDesc[]={
	{ "g_jbondw.bin", 0x080000, 0x4E614548, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jbondw);
STD_ROM_FN(jbondw);

struct BurnDriver BurnDrvMDjbondw = {
	"g_jbondw", "g_bond", NULL, "1993",
	"James Bond 007 - The Duel (W)\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jbondwRomInfo, jbondwRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Judge Dredd - The Movie (Beta)

static struct BurnRomInfo jdrdbRomDesc[]={
	{ "g_jdrdb.bin", 0x200000, 0x8D46F4DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jdrdb);
STD_ROM_FN(jdrdb);

struct BurnDriverD BurnDrvMDjdrdb = {
	"g_jdrdb", NULL, NULL, "1995",
	"Judge Dredd - The Movie (Beta)\0", NULL, "Acclaim / Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jdrdbRomInfo, jdrdbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Judge Dredd - The Movie (Beta) [a1]

static struct BurnRomInfo jdrdbaRomDesc[]={
	{ "g_jdrdba.bin", 0x200000, 0xE649F784, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jdrdba);
STD_ROM_FN(jdrdba);

struct BurnDriverD BurnDrvMDjdrdba = {
	"g_jdrdba", NULL, NULL, "1995",
	"Judge Dredd - The Movie (Beta) [a1]\0", NULL, "Acclaim / Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jdrdbaRomInfo, jdrdbaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jungle Strike (Beta)

static struct BurnRomInfo jstrkbRomDesc[]={
	{ "g_jstrkb.bin", 0x200000, 0x0CD540D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jstrkb);
STD_ROM_FN(jstrkb);

struct BurnDriverD BurnDrvMDjstrkb = {
	"g_jstrkb", NULL, NULL, "1900",
	"Jungle Strike (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jstrkbRomInfo, jstrkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Junkers High (Beta)

static struct BurnRomInfo junkbRomDesc[]={
	{ "g_junkb.bin", 0x100000, 0x23534949, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(junkb);
STD_ROM_FN(junkb);

struct BurnDriverD BurnDrvMDjunkb = {
	"g_junkb", "g_or20", NULL, "1992",
	"Junkers High (Beta)\0", NULL, "Sims", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, junkbRomInfo, junkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Jurassic Park (Beta)

static struct BurnRomInfo jparkbRomDesc[]={
	{ "g_jparkb.bin", 0x200000, 0xCF890EED, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(jparkb);
STD_ROM_FN(jparkb);

struct BurnDriverD BurnDrvMDjparkb = {
	"g_jparkb", NULL, NULL, "1900",
	"Jurassic Park (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, jparkbRomInfo, jparkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kawasaki Superbike Challenge (Beta)

static struct BurnRomInfo kawabRomDesc[]={
	{ "g_kawab.bin", 0x100000, 0x55934D1B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kawab);
STD_ROM_FN(kawab);

struct BurnDriverD BurnDrvMDkawab = {
	"g_kawab", NULL, NULL, "1900",
	"Kawasaki Superbike Challenge (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kawabRomInfo, kawabRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - The Treasures of King Nole (Beta)

static struct BurnRomInfo landsbRomDesc[]={
	{ "g_landsb.bin", 0x200000, 0x70483D03, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(landsb);
STD_ROM_FN(landsb);

struct BurnDriverD BurnDrvMDlandsb = {
	"g_landsb", NULL, NULL, "1994",
	"Landstalker - The Treasures of King Nole (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landsbRomInfo, landsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Landstalker - The Treasures of King Nole (F)

static struct BurnRomInfo landsfRomDesc[]={
	{ "g_landsf.bin", 0x200000, 0x5DE7D917, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(landsf);
STD_ROM_FN(landsf);

struct BurnDriverD BurnDrvMDlandsf = {
	"g_landsf", NULL, NULL, "1994",
	"Landstalker - The Treasures of King Nole (F)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, landsfRomInfo, landsfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Langrisser II (J) (REV01)

static struct BurnRomInfo lng201RomDesc[]={
	{ "g_lng201.bin", 0x200000, 0x0CAA0593, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lng201);
STD_ROM_FN(lng201);

struct BurnDriverD BurnDrvMDlng201 = {
	"g_lng201", NULL, NULL, "1900",
	"Langrisser II (J) (REV01)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lng201RomInfo, lng201RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lost Viking

static struct BurnRomInfo lostvbRomDesc[]={
	{ "g_lostvb.bin", 0x100000, 0x17BED25F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lostvb);
STD_ROM_FN(lostvb);

struct BurnDriverD BurnDrvMDlostvb = {
	"g_lostvb", NULL, NULL, "1900",
	"Lost Viking\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lostvbRomInfo, lostvbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lost Viking

static struct BurnRomInfo lostveRomDesc[]={
	{ "g_lostve.bin", 0x100000, 0x1F14EFC6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lostve);
STD_ROM_FN(lostve);

struct BurnDriverD BurnDrvMDlostve = {
	"g_lostve", NULL, NULL, "1900",
	"Lost Viking\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lostveRomInfo, lostveRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Lotus II RECS (Beta)

static struct BurnRomInfo lotu2bRomDesc[]={
	{ "g_lotu2b.bin", 0x100000, 0x2997B7D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(lotu2b);
STD_ROM_FN(lotu2b);

struct BurnDriverD BurnDrvMDlotu2b = {
	"g_lotu2b", NULL, NULL, "1900",
	"Lotus II RECS (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, lotu2bRomInfo, lotu2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Marko's Magic Football (Beta) (M4)

static struct BurnRomInfo mmfbRomDesc[]={
	{ "g_mmfb.bin", 0x200000, 0x0273E564, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmfb);
STD_ROM_FN(mmfb);

struct BurnDriverD BurnDrvMDmmfb = {
	"g_mmfb", NULL, NULL, "1900",
	"Marko's Magic Football (Beta) (M4)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmfbRomInfo, mmfbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mazin Saga (Beta)

static struct BurnRomInfo mazibRomDesc[]={
	{ "g_mazib.bin", 0x100000, 0x36459B59, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mazib);
STD_ROM_FN(mazib);

struct BurnDriverD BurnDrvMDmazib = {
	"g_mazib", NULL, NULL, "1993",
	"Mazin Saga (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mazibRomInfo, mazibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// McDonald's Treasure Land Adventure (Beta)

static struct BurnRomInfo mcdtlbRomDesc[]={
	{ "g_mcdtlb.bin", 0x100000, 0x7BF477E8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mcdtlb);
STD_ROM_FN(mcdtlb);

struct BurnDriverD BurnDrvMDmcdtlb = {
	"g_mcdtlb", NULL, NULL, "1993",
	"McDonald's Treasure Land Adventure (Beta)\0", NULL, "Sega / Treasure / McDonalds", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mcdtlbRomInfo, mcdtlbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// McDonald's Treasure Land Adventure (E)

static struct BurnRomInfo mcdtleRomDesc[]={
	{ "g_mcdtle.bin", 0x100000, 0x6AB6A8DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mcdtle);
STD_ROM_FN(mcdtle);

struct BurnDriverD BurnDrvMDmcdtle = {
	"g_mcdtle", NULL, NULL, "1993",
	"McDonald's Treasure Land Adventure (E)\0", NULL, "Sega / Treasure / McDonalds", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mcdtleRomInfo, mcdtleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega Lo Mania (E) (REV01)

static struct BurnRomInfo mlom01RomDesc[]={
	{ "g_mlom01.bin", 0x100000, 0xAB9FED30, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mlom01);
STD_ROM_FN(mlom01);

struct BurnDriverD BurnDrvMDmlom01 = {
	"g_mlom01", NULL, NULL, "1994",
	"Mega Lo Mania (E) (REV01)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mlom01RomInfo, mlom01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mega SWIV (E)

static struct BurnRomInfo mswiveRomDesc[]={
	{ "g_mswive.bin", 0x100000, 0x78C2F046, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mswive);
STD_ROM_FN(mswive);

struct BurnDriverD BurnDrvMDmswive = {
	"g_mswive", NULL, NULL, "1900",
	"Mega SWIV (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mswiveRomInfo, mswiveRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Megaman - The Wily Wars (E)

static struct BurnRomInfo megmeRomDesc[]={
	{ "g_megme.bin", 0x200000, 0xDCF6E8B2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(megme);
STD_ROM_FN(megme);

struct BurnDriverD BurnDrvMDmegme = {
	"g_megme", NULL, NULL, "1900",
	"Megaman - The Wily Wars (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, megmeRomInfo, megmeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mick & Mack as the Global Gladiators (Beta)

static struct BurnRomInfo micmabRomDesc[]={
	{ "g_micmab.bin", 0x100000, 0x08C2AF21, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micmab);
STD_ROM_FN(micmab);

struct BurnDriverD BurnDrvMDmicmab = {
	"g_micmab", NULL, NULL, "1994",
	"Mick & Mack as the Global Gladiators (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micmabRomInfo, micmabRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Mickey Mania - Timeless Adventures of Mickey Mouse (Beta)

static struct BurnRomInfo mmanibRomDesc[]={
	{ "g_mmanib.bin", 0x200000, 0x7FC1BDF0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mmanib);
STD_ROM_FN(mmanib);

struct BurnDriverD BurnDrvMDmmanib = {
	"g_mmanib", NULL, NULL, "1994",
	"Mickey Mania - Timeless Adventures of Mickey Mouse (Beta)\0", NULL, "Disney / Sony", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mmanibRomInfo, mmanibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines - Turbo Tournament '96 (V1.1) (E)

static struct BurnRomInfo micm96RomDesc[]={
	{ "g_micm96.bin", 0x100000, 0x3137B3C4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micm96);
STD_ROM_FN(micm96);

struct BurnDriverD BurnDrvMDmicm96 = {
	"g_micm96", NULL, NULL, "1995",
	"Micro Machines - Turbo Tournament '96 (V1.1) (E)\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micm96RomInfo, micm96RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Micro Machines (C)

static struct BurnRomInfo micmcRomDesc[]={
	{ "g_micmc.bin", 0x080000, 0x54E4CFF1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(micmc);
STD_ROM_FN(micmc);

struct BurnDriver BurnDrvMDmicmc = {
	"g_micmc", "g_mic", NULL, "1993",
	"Micro Machines (C)\0", NULL, "Codemasters", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, micmcRomInfo, micmcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Might and Magic III - Isles of Terra (Beta)

static struct BurnRomInfo mima3bRomDesc[]={
	{ "g_mima3b.bin", 0x200000, 0x6EF7104A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mima3b);
STD_ROM_FN(mima3b);

struct BurnDriverD BurnDrvMDmima3b = {
	"g_mima3b", NULL, NULL, "1900",
	"Might and Magic III - Isles of Terra (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mima3bRomInfo, mima3bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Monopoly (Beta)

static struct BurnRomInfo monobRomDesc[]={
	{ "g_monob.bin", 0x080000, 0xDFBCC3FA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(monob);
STD_ROM_FN(monob);

struct BurnDriverD BurnDrvMDmonob = {
	"g_monob", NULL, NULL, "1900",
	"Monopoly (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, monobRomInfo, monobRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Muhammad Ali Heavyweight Boxing (Beta)

static struct BurnRomInfo mahbbRomDesc[]={
	{ "g_mahbb.bin", 0x100000, 0x7B852653, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mahbb);
STD_ROM_FN(mahbb);

struct BurnDriverD BurnDrvMDmahbb = {
	"g_mahbb", NULL, NULL, "1900",
	"Muhammad Ali Heavyweight Boxing (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mahbbRomInfo, mahbbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Muhammad Ali Heavyweight Boxing (E)

static struct BurnRomInfo mahbeRomDesc[]={
	{ "g_mahbe.bin", 0x100000, 0x8EA4717B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(mahbe);
STD_ROM_FN(mahbe);

struct BurnDriverD BurnDrvMDmahbe = {
	"g_mahbe", NULL, NULL, "1900",
	"Muhammad Ali Heavyweight Boxing (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, mahbeRomInfo, mahbeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NBA Showdown 94 (Beta)

static struct BurnRomInfo nba94bRomDesc[]={
	{ "g_nba94b.bin", 0x200000, 0x6643A308, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nba94b);
STD_ROM_FN(nba94b);

struct BurnDriverD BurnDrvMDnba94b = {
	"g_nba94b", NULL, NULL, "1900",
	"NBA Showdown 94 (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nba94bRomInfo, nba94bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHL 96 Elitserien (E)

static struct BurnRomInfo nhl96eRomDesc[]={
	{ "g_nhl96e.bin", 0x200000, 0x9821D0A3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nhl96e);
STD_ROM_FN(nhl96e);

struct BurnDriverD BurnDrvMDnhl96e = {
	"g_nhl96e", NULL, NULL, "1900",
	"NHL 96 Elitserien (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nhl96eRomInfo, nhl96eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// NHLPA Hockey '93 (UE) (REV00)

static struct BurnRomInfo nhlp00RomDesc[]={
	{ "g_nhlp00.bin", 0x080000, 0xCBBF4262, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nhlp00);
STD_ROM_FN(nhlp00);

struct BurnDriverD BurnDrvMDnhlp00 = {
	"g_nhlp00", NULL, NULL, "1900",
	"NHLPA Hockey '93 (UE) (REV00)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nhlp00RomInfo, nhlp00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nigel Mansell's World Championship (E)

static struct BurnRomInfo nigwceRomDesc[]={
	{ "g_nigwce.bin", 0x100000, 0x3FE3D63B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(nigwce);
STD_ROM_FN(nigwce);

struct BurnDriverD BurnDrvMDnigwce = {
	"g_nigwce", NULL, NULL, "1900",
	"Nigel Mansell's World Championship (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, nigwceRomInfo, nigwceRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Nightmare Circus (Beta)

static struct BurnRomInfo ncircbRomDesc[]={
	{ "g_ncircb.bin", 0x200000, 0x31DE5A94, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ncircb);
STD_ROM_FN(ncircb);

struct BurnDriverD BurnDrvMDncircb = {
	"g_ncircb", NULL, NULL, "1900",
	"Nightmare Circus (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ncircbRomInfo, ncircbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ninja Gaiden (Beta)

static struct BurnRomInfo ngaidbRomDesc[]={
	{ "g_ngaidb.bin", 0x100000, 0x0D7F74BA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ngaidb);
STD_ROM_FN(ngaidb);

struct BurnDriverD BurnDrvMDngaidb = {
	"g_ngaidb", NULL, NULL, "1900",
	"Ninja Gaiden (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ngaidbRomInfo, ngaidbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ottifant

static struct BurnRomInfo ottifbRomDesc[]={
	{ "g_ottifb.bin", 0x100000, 0xC6E3DD23, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ottifb);
STD_ROM_FN(ottifb);

struct BurnDriverD BurnDrvMDottifb = {
	"g_ottifb", NULL, NULL, "1900",
	"Ottifant\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ottifbRomInfo, ottifbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Out of this World (Beta)

static struct BurnRomInfo ootwbRomDesc[]={
	{ "g_ootwb.bin", 0x100000, 0x3AAD905A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ootwb);
STD_ROM_FN(ootwb);

struct BurnDriver BurnDrvMDootwb = {
	"g_ootwb", "g_ootw", NULL, "1992",
	"Out of this World (Beta)\0", NULL, "Delphine / Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ootwbRomInfo, ootwbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Outlander (Beta)

static struct BurnRomInfo outlnbRomDesc[]={
	{ "g_outlnb.bin", 0x100000, 0xC5BA7BBF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(outlnb);
STD_ROM_FN(outlnb);

struct BurnDriverD BurnDrvMDoutlnb = {
	"g_outlnb", NULL, NULL, "1900",
	"Outlander (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, outlnbRomInfo, outlnbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// OutRun 2019 (Beta)

static struct BurnRomInfo g_2019bRomDesc[]={
	{ "g_2019b.bin", 0x100000, 0xD2ECDDFA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_2019b);
STD_ROM_FN(g_2019b);

struct BurnDriverD BurnDrvMDg_2019b = {
	"g_2019b", "g_or20", NULL, "1993",
	"OutRun 2019 (Beta)\0", NULL, "Sims", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_2019bRomInfo, g_2019bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pagemaste

static struct BurnRomInfo pagembRomDesc[]={
	{ "g_pagemb.bin", 0x200000, 0x29895E3D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pagemb);
STD_ROM_FN(pagemb);

struct BurnDriverD BurnDrvMDpagemb = {
	"g_pagemb", NULL, NULL, "1994",
	"Pagemaste\0", NULL, "Probe", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pagembRomInfo, pagembRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pebble Beach Golf Links (E)

static struct BurnRomInfo pblbeeRomDesc[]={
	{ "g_pblbee.bin", 0x200000, 0x6CFC7297, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pblbee);
STD_ROM_FN(pblbee);

struct BurnDriverD BurnDrvMDpblbee = {
	"g_pblbee", NULL, NULL, "1900",
	"Pebble Beach Golf Links (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pblbeeRomInfo, pblbeeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II (UE) (REV01)

static struct BurnRomInfo pst201RomDesc[]={
	{ "g_pst201.bin", 0x0C0000, 0x0D07D0EF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pst201);
STD_ROM_FN(pst201);

struct BurnDriverD BurnDrvMDpst201 = {
	"g_pst201", NULL, NULL, "1989",
	"Phantasy Star II (UE) (REV01)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pst201RomInfo, pst201RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pink Goes to Hollywood (Beta)

static struct BurnRomInfo pinkbRomDesc[]={
	{ "g_pinkb.bin", 0x100000, 0x56087CFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pinkb);
STD_ROM_FN(pinkb);

struct BurnDriverD BurnDrvMDpinkb = {
	"g_pinkb", NULL, NULL, "1900",
	"Pink Goes to Hollywood (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pinkbRomInfo, pinkbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pinocchio (E)

static struct BurnRomInfo pinnoeRomDesc[]={
	{ "g_pinnoe.bin", 0x300000, 0x28014BDC, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pinnoe);
STD_ROM_FN(pinnoe);

struct BurnDriverD BurnDrvMDpinnoe = {
	"g_pinnoe", NULL, NULL, "1900",
	"Pinocchio (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pinnoeRomInfo, pinnoeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pirates of Dark Wate

static struct BurnRomInfo pirdwuRomDesc[]={
	{ "g_pirdwu.bin", 0x200000, 0x0A62DE34, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pirdwu);
STD_ROM_FN(pirdwu);

struct BurnDriverD BurnDrvMDpirdwu = {
	"g_pirdwu", NULL, NULL, "1900",
	"Pirates of Dark Wate\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pirdwuRomInfo, pirdwuRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pirates! Gold (Beta)

static struct BurnRomInfo pgoldbRomDesc[]={
	{ "g_pgoldb.bin", 0x100000, 0x0A525641, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pgoldb);
STD_ROM_FN(pgoldb);

struct BurnDriverD BurnDrvMDpgoldb = {
	"g_pgoldb", NULL, NULL, "1900",
	"Pirates! Gold (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pgoldbRomInfo, pgoldbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Prince of Persia (Beta 1)

static struct BurnRomInfo persb1RomDesc[]={
	{ "g_persb1.bin", 0x040000, 0x425E6A87, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(persb1);
STD_ROM_FN(persb1);

struct BurnDriverD BurnDrvMDpersb1 = {
	"g_persb1", NULL, NULL, "1993",
	"Prince of Persia (Beta 1)\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, persb1RomInfo, persb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Prince of Persia (Beta 2)

static struct BurnRomInfo persb2RomDesc[]={
	{ "g_persb2.bin", 0x100000, 0x505314B6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(persb2);
STD_ROM_FN(persb2);

struct BurnDriverD BurnDrvMDpersb2 = {
	"g_persb2", NULL, NULL, "1993",
	"Prince of Persia (Beta 2)\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, persb2RomInfo, persb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Prince of Persia (E)

static struct BurnRomInfo perseRomDesc[]={
	{ "g_perse.bin", 0x100000, 0x61DE6FE0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(perse);
STD_ROM_FN(perse);

struct BurnDriverD BurnDrvMDperse = {
	"g_perse", NULL, NULL, "1993",
	"Prince of Persia (E)\0", NULL, "Domark", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, perseRomInfo, perseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Puggsy (Beta)

static struct BurnRomInfo puggsbRomDesc[]={
	{ "g_puggsb.bin", 0x100000, 0x37FA4877, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(puggsb);
STD_ROM_FN(puggsb);

struct BurnDriverD BurnDrvMDpuggsb = {
	"g_puggsb", NULL, NULL, "1900",
	"Puggsy (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puggsbRomInfo, puggsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Punishe

static struct BurnRomInfo puniseRomDesc[]={
	{ "g_punise.bin", 0x200000, 0x729EDD17, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(punise);
STD_ROM_FN(punise);

struct BurnDriverD BurnDrvMDpunise = {
	"g_punise", NULL, NULL, "1900",
	"Punishe\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, puniseRomInfo, puniseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Radical Rex (E)

static struct BurnRomInfo rrexeRomDesc[]={
	{ "g_rrexe.bin", 0x100000, 0xD02D3282, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rrexe);
STD_ROM_FN(rrexe);

struct BurnDriverD BurnDrvMDrrexe = {
	"g_rrexe", NULL, NULL, "1900",
	"Radical Rex (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rrexeRomInfo, rrexeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// RBI Baseball 4 (Beta)

static struct BurnRomInfo rbi4bRomDesc[]={
	{ "g_rbi4b.bin", 0x100000, 0xF7420278, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rbi4b);
STD_ROM_FN(rbi4b);

struct BurnDriverD BurnDrvMDrbi4b = {
	"g_rbi4b", NULL, NULL, "1900",
	"RBI Baseball 4 (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rbi4bRomInfo, rbi4bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ren and Stimpy Sho

static struct BurnRomInfo renstbRomDesc[]={
	{ "g_renstb.bin", 0x100000, 0xFCB86336, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(renstb);
STD_ROM_FN(renstb);

struct BurnDriverD BurnDrvMDrenstb = {
	"g_renstb", NULL, NULL, "1900",
	"Ren and Stimpy Sho\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, renstbRomInfo, renstbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robocop Versus The Terminator (Beta 1)

static struct BurnRomInfo robtb1RomDesc[]={
	{ "g_robtb1.bin", 0x200000, 0xECEBFF29, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robtb1);
STD_ROM_FN(robtb1);

struct BurnDriverD BurnDrvMDrobtb1 = {
	"g_robtb1", NULL, NULL, "1993",
	"Robocop Versus The Terminator (Beta 1)\0", NULL, "Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robtb1RomInfo, robtb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robocop Versus The Terminator (Beta 2)

static struct BurnRomInfo robtb2RomDesc[]={
	{ "g_robtb2.bin", 0x200000, 0x2487049F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robtb2);
STD_ROM_FN(robtb2);

struct BurnDriverD BurnDrvMDrobtb2 = {
	"g_robtb2", NULL, NULL, "1993",
	"Robocop Versus The Terminator (Beta 2)\0", NULL, "Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robtb2RomInfo, robtb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robocop Versus The Terminator (E)

static struct BurnRomInfo robteRomDesc[]={
	{ "g_robte.bin", 0x200000, 0x85A93F8D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robte);
STD_ROM_FN(robte);

struct BurnDriverD BurnDrvMDrobte = {
	"g_robte", NULL, NULL, "1993",
	"Robocop Versus The Terminator (E)\0", NULL, "Virgin", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robteRomInfo, robteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robot Wreckage (Beta)

static struct BurnRomInfo robwrbRomDesc[]={
	{ "g_robwrb.bin", 0x100000, 0xC67DDB14, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robwrb);
STD_ROM_FN(robwrb);

struct BurnDriverD BurnDrvMDrobwrb = {
	"g_robwrb", NULL, NULL, "1993",
	"Robot Wreckage (Beta)\0", NULL, "Sega / Novotrade", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robwrbRomInfo, robwrbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Saturday Night Slam Masters (E)

static struct BurnRomInfo snsmeRomDesc[]={
	{ "g_snsme.bin", 0x400000, 0x08FA5A3F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(snsme);
STD_ROM_FN(snsme);

struct BurnDriverD BurnDrvMDsnsme = {
	"g_snsme", NULL, NULL, "1900",
	"Saturday Night Slam Masters (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, snsmeRomInfo, snsmeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Scrabble (Beta)

static struct BurnRomInfo scrabbRomDesc[]={
	{ "g_scrabb.bin", 0x100000, 0x360B2610, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(scrabb);
STD_ROM_FN(scrabb);

struct BurnDriverD BurnDrvMDscrabb = {
	"g_scrabb", NULL, NULL, "1900",
	"Scrabble (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, scrabbRomInfo, scrabbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// SeaQuest DSV (E)

static struct BurnRomInfo seaqeRomDesc[]={
	{ "g_seaqe.bin", 0x200000, 0x0BB511BD, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(seaqe);
STD_ROM_FN(seaqe);

struct BurnDriverD BurnDrvMDseaqe = {
	"g_seaqe", NULL, NULL, "1900",
	"SeaQuest DSV (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, seaqeRomInfo, seaqeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sensible Soccer (Beta)

static struct BurnRomInfo sensibRomDesc[]={
	{ "g_sensib.bin", 0x080000, 0xEF52664D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sensib);
STD_ROM_FN(sensib);

struct BurnDriverD BurnDrvMDsensib = {
	"g_sensib", "g_sen", NULL, "1993",
	"Sensible Soccer (Beta)\0", NULL, "Sensible Software", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sensibRomInfo, sensibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shanghai 2 - Dragon's Eye (Beta)

static struct BurnRomInfo shan2bRomDesc[]={
	{ "g_shan2b.bin", 0x100000, 0x5E33867B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(shan2b);
STD_ROM_FN(shan2b);

struct BurnDriverD BurnDrvMDshan2b = {
	"g_shan2b", NULL, NULL, "1900",
	"Shanghai 2 - Dragon's Eye (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, shan2bRomInfo, shan2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Shining Force (Beta)

static struct BurnRomInfo sfrcbtRomDesc[]={
	{ "g_sfrcbt.bin", 0x180000, 0xCE67143A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sfrcbt);
STD_ROM_FN(sfrcbt);

struct BurnDriverD BurnDrvMDsfrcbt = {
	"g_sfrcbt", NULL, NULL, "1993",
	"Shining Force (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sfrcbtRomInfo, sfrcbtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Skeleton Krew (E)

static struct BurnRomInfo skreweRomDesc[]={
	{ "g_skrewe.bin", 0x200000, 0x5F872737, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(skrewe);
STD_ROM_FN(skrewe);

struct BurnDriverD BurnDrvMDskrewe = {
	"g_skrewe", NULL, NULL, "1900",
	"Skeleton Krew (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, skreweRomInfo, skreweRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soleil (Beta)

static struct BurnRomInfo soleibRomDesc[]={
	{ "g_soleib.bin", 0x100000, 0x43797455, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soleib);
STD_ROM_FN(soleib);

struct BurnDriverD BurnDrvMDsoleib = {
	"g_soleib", NULL, NULL, "1994",
	"Soleil (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soleibRomInfo, soleibRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Soleil (S)

static struct BurnRomInfo soleisRomDesc[]={
	{ "g_soleis.bin", 0x200000, 0x9ED4C323, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soleis);
STD_ROM_FN(soleis);

struct BurnDriverD BurnDrvMDsoleis = {
	"g_soleis", NULL, NULL, "1994",
	"Soleil (S)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soleisRomInfo, soleisRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic and Crackers (Beta)

static struct BurnRomInfo soncrkRomDesc[]={
	{ "g_soncrk.bin", 0x100000, 0x7FADA88D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(soncrk);
STD_ROM_FN(soncrk);

struct BurnDriver BurnDrvMDsoncrk = {
	"g_soncrk", NULL, NULL, "1900",
	"Sonic and Crackers (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, soncrkRomInfo, soncrkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Spinball (Beta)

static struct BurnRomInfo sonsbRomDesc[]={
	{ "g_sonsb.bin", 0x140000, 0xB1524979, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sonsb);
STD_ROM_FN(sonsb);

struct BurnDriverD BurnDrvMDsonsb = {
	"g_sonsb", "g_sons", NULL, "1993",
	"Sonic Spinball (Beta)\0", "No sound in-game", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sonsbRomInfo, sonsbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sorcerer's Kingdom (U) (REV00)

static struct BurnRomInfo sork00RomDesc[]={
	{ "g_sork00.bin", 0x100000, 0xCBE6C1EA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sork00);
STD_ROM_FN(sork00);

struct BurnDriverD BurnDrvMDsork00 = {
	"g_sork00", NULL, NULL, "1900",
	"Sorcerer's Kingdom (U) (REV00)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sork00RomInfo, sork00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man - The Animated Series (Beta 1)

static struct BurnRomInfo s_asb1RomDesc[]={
	{ "g_s_asb1.bin", 0x200000, 0xB88A710D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_asb1);
STD_ROM_FN(s_asb1);

struct BurnDriverD BurnDrvMDs_asb1 = {
	"g_s_asb1", NULL, NULL, "1995",
	"Spider-Man - The Animated Series (Beta 1)\0", NULL, "Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_asb1RomInfo, s_asb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Spider-Man - The Animated Series (Beta 2)

static struct BurnRomInfo s_asb2RomDesc[]={
	{ "g_s_asb2.bin", 0x200000, 0xB88A710D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(s_asb2);
STD_ROM_FN(s_asb2);

struct BurnDriverD BurnDrvMDs_asb2 = {
	"g_s_asb2", NULL, NULL, "1995",
	"Spider-Man - The Animated Series (Beta 2)\0", NULL, "Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, s_asb2RomInfo, s_asb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Star Trek - Deep Space 9 - Crossroads of Time (E)

static struct BurnRomInfo stds9eRomDesc[]={
	{ "g_stds9e.bin", 0x100000, 0xD4B122F9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(stds9e);
STD_ROM_FN(stds9e);

struct BurnDriverD BurnDrvMDstds9e = {
	"g_stds9e", NULL, NULL, "1900",
	"Star Trek - Deep Space 9 - Crossroads of Time (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, stds9eRomInfo, stds9eRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Stargate (Beta)

static struct BurnRomInfo sgatbRomDesc[]={
	{ "g_sgatb.bin", 0x200000, 0x8DC8AB23, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sgatb);
STD_ROM_FN(sgatb);

struct BurnDriverD BurnDrvMDsgatb = {
	"g_sgatb", NULL, NULL, "1900",
	"Stargate (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sgatbRomInfo, sgatbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Steel Empir

static struct BurnRomInfo sempbRomDesc[]={
	{ "g_sempb.bin", 0x100000, 0xE5517B77, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sempb);
STD_ROM_FN(sempb);

struct BurnDriverD BurnDrvMDsempb = {
	"g_sempb", NULL, NULL, "1994",
	"Steel Empir\0", NULL, "Hot B / Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sempbRomInfo, sempbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (Beta)

static struct BurnRomInfo sthorbRomDesc[]={
	{ "g_sthorb.bin", 0x1B0000, 0xBFC11649, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthorb);
STD_ROM_FN(sthorb);

struct BurnDriver BurnDrvMDsthorb = {
	"g_sthorb", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorbRomInfo, sthorbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (F)

static struct BurnRomInfo sthorfRomDesc[]={
	{ "g_sthorf.bin", 0x300000, 0xB97CCA1C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthorf);
STD_ROM_FN(sthorf);

struct BurnDriver BurnDrvMDsthorf = {
	"g_sthorf", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (F)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorfRomInfo, sthorfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (G)

static struct BurnRomInfo sthorgRomDesc[]={
	{ "g_sthorg.bin", 0x300000, 0xFA20D011, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthorg);
STD_ROM_FN(sthorg);

struct BurnDriver BurnDrvMDsthorg = {
	"g_sthorg", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (G)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorgRomInfo, sthorgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (K)

static struct BurnRomInfo sthorkRomDesc[]={
	{ "g_sthork.bin", 0x300000, 0xEE1603C5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthork);
STD_ROM_FN(sthork);

struct BurnDriver BurnDrvMDsthork = {
	"g_sthork", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (K)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorkRomInfo, sthorkRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Story of Thor, The - A Successor of The Light (S)

static struct BurnRomInfo sthorsRomDesc[]={
	{ "g_sthors.bin", 0x300000, 0x4631F941, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sthors);
STD_ROM_FN(sthors);

struct BurnDriver BurnDrvMDsthors = {
	"g_sthors", "g_boas", NULL, "1995",
	"Story of Thor, The - A Successor of The Light (S)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sthorsRomInfo, sthorsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Street Fighter II' Turbo (Beta)

static struct BurnRomInfo sf2bRomDesc[]={
	{ "g_sf2b.bin", 0x200000, 0xA85491AE, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sf2b);
STD_ROM_FN(sf2b);

struct BurnDriverD BurnDrvMDsf2b = {
	"g_sf2b", NULL, NULL, "1900",
	"Street Fighter II' Turbo (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sf2bRomInfo, sf2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Striker (Beta)

static struct BurnRomInfo strikbRomDesc[]={
	{ "g_strikb.bin", 0x200000, 0xC10B270E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(strikb);
STD_ROM_FN(strikb);

struct BurnDriverD BurnDrvMDstrikb = {
	"g_strikb", NULL, NULL, "1900",
	"Striker (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, strikbRomInfo, strikbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sub-Terrania (Beta 1)

static struct BurnRomInfo subtb1RomDesc[]={
	{ "g_subtb1.bin", 0x140000, 0x9C13D25C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(subtb1);
STD_ROM_FN(subtb1);

struct BurnDriverD BurnDrvMDsubtb1 = {
	"g_subtb1", NULL, NULL, "1993",
	"Sub-Terrania (Beta 1)\0", NULL, "Zyrinx", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, subtb1RomInfo, subtb1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sub-Terrania (Beta 2)

static struct BurnRomInfo subtb2RomDesc[]={
	{ "g_subtb2.bin", 0x200000, 0x3A1022D1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(subtb2);
STD_ROM_FN(subtb2);

struct BurnDriverD BurnDrvMDsubtb2 = {
	"g_subtb2", NULL, NULL, "1993",
	"Sub-Terrania (Beta 2)\0", NULL, "Zyrinx", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, subtb2RomInfo, subtb2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super League (E)

static struct BurnRomInfo sleageRomDesc[]={
	{ "g_sleage.bin", 0x080000, 0x55BAEC6E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sleage);
STD_ROM_FN(sleage);

struct BurnDriverD BurnDrvMDsleage = {
	"g_sleage", NULL, NULL, "1900",
	"Super League (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sleageRomInfo, sleageRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Shinobi I

static struct BurnRomInfo sshi2bRomDesc[]={
	{ "g_sshi2b.bin", 0x100000, 0xC47E8AEA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sshi2b);
STD_ROM_FN(sshi2b);

struct BurnDriverD BurnDrvMDsshi2b = {
	"g_sshi2b", NULL, NULL, "1993",
	"Super Shinobi I\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sshi2bRomInfo, sshi2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Skidmarks (E) [a1]

static struct BurnRomInfo skidaRomDesc[]={
	{ "g_skida.bin", 0x200000, 0xA61A0F0C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(skida);
STD_ROM_FN(skida);

struct BurnDriverD BurnDrvMDskida = {
	"g_skida", NULL, NULL, "1995",
	"Super Skidmarks (E) [a1]\0", NULL, "Codemasters / Acid", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, skidaRomInfo, skidaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Superman (Beta)

static struct BurnRomInfo supmnbRomDesc[]={
	{ "g_supmnb.bin", 0x100000, 0x5CD0E1D4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(supmnb);
STD_ROM_FN(supmnb);

struct BurnDriverD BurnDrvMDsupmnb = {
	"g_supmnb", NULL, NULL, "1900",
	"Superman (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, supmnbRomInfo, supmnbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sylvester & Tweety in Cagey Capers (Beta)

static struct BurnRomInfo sylvbRomDesc[]={
	{ "g_sylvb.bin", 0x200000, 0x9D9C786B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sylvb);
STD_ROM_FN(sylvb);

struct BurnDriverD BurnDrvMDsylvb = {
	"g_sylvb", NULL, NULL, "1900",
	"Sylvester & Tweety in Cagey Capers (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sylvbRomInfo, sylvbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// T2 - The Arcade Game (Beta)

static struct BurnRomInfo t2arcbRomDesc[]={
	{ "g_t2arcb.bin", 0x100000, 0x94255703, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(t2arcb);
STD_ROM_FN(t2arcb);

struct BurnDriverD BurnDrvMDt2arcb = {
	"g_t2arcb", NULL, NULL, "1900",
	"T2 - The Arcade Game (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, t2arcbRomInfo, t2arcbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Hero Turtles - The Hyperstone Heist (E)

static struct BurnRomInfo tmhteRomDesc[]={
	{ "g_tmhte.bin", 0x100000, 0x966D5286, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tmhte);
STD_ROM_FN(tmhte);

struct BurnDriverD BurnDrvMDtmhte = {
	"g_tmhte", NULL, NULL, "1900",
	"Teenage Mutant Hero Turtles - The Hyperstone Heist (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tmhteRomInfo, tmhteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teenage Mutant Hero Turtles - Tournament Fighters (E)

static struct BurnRomInfo tmhtteRomDesc[]={
	{ "g_tmhtte.bin", 0x200000, 0x3CD2B7E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tmhtte);
STD_ROM_FN(tmhtte);

struct BurnDriverD BurnDrvMDtmhtte = {
	"g_tmhtte", NULL, NULL, "1900",
	"Teenage Mutant Hero Turtles - Tournament Fighters (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tmhtteRomInfo, tmhtteRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tiny Toon Adventures - Acme All-Stars (E)

static struct BurnRomInfo ttadaeRomDesc[]={
	{ "g_ttadae.bin", 0x100000, 0x1227B2B2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(ttadae);
STD_ROM_FN(ttadae);

struct BurnDriverD BurnDrvMDttadae = {
	"g_ttadae", NULL, NULL, "1900",
	"Tiny Toon Adventures - Acme All-Stars (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, ttadaeRomInfo, ttadaeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Triple Play Gold (U) [a1]

static struct BurnRomInfo tpgolaRomDesc[]={
	{ "g_tpgola.bin", 0x400000, 0xA89638A0, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tpgola);
STD_ROM_FN(tpgola);

struct BurnDriverD BurnDrvMDtpgola = {
	"g_tpgola", NULL, NULL, "1900",
	"Triple Play Gold (U) [a1]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tpgolaRomInfo, tpgolaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Twisted Flipper (Beta)

static struct BurnRomInfo twisfRomDesc[]={
	{ "g_twisf.bin", 0x080000, 0x6DD47554, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(twisf);
STD_ROM_FN(twisf);

struct BurnDriverD BurnDrvMDtwisf = {
	"g_twisf", NULL, NULL, "1992",
	"Twisted Flipper (Beta)\0", NULL, "Electronic Arts", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, twisfRomInfo, twisfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Two Crude Dudes (E)

static struct BurnRomInfo crudeeRomDesc[]={
	{ "g_crudee.bin", 0x100000, 0xB6D90A10, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(crudee);
STD_ROM_FN(crudee);

struct BurnDriverD BurnDrvMDcrudee = {
	"g_crudee", "g_2cd", NULL, "1900",
	"Two Crude Dudes (E)\0", "Bad sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, crudeeRomInfo, crudeeRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Vectorman (Beta)

static struct BurnRomInfo vectbRomDesc[]={
	{ "g_vectb.bin", 0x200000, 0x2084D3DA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(vectb);
STD_ROM_FN(vectb);

struct BurnDriverD BurnDrvMDvectb = {
	"g_vectb", NULL, NULL, "1995",
	"Vectorman (Beta)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, vectbRomInfo, vectbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Viewpoint (Beta)

static struct BurnRomInfo viewpbRomDesc[]={
	{ "g_viewpb.bin", 0x180000, 0xF2E69CE7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(viewpb);
STD_ROM_FN(viewpb);

struct BurnDriverD BurnDrvMDviewpb = {
	"g_viewpb", NULL, NULL, "1900",
	"Viewpoint (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, viewpbRomInfo, viewpbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Virtua Racing (E) [a1]

static struct BurnRomInfo virreaRomDesc[]={
	{ "g_virrea.bin", 0x200000, 0x5A943DF9, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(virrea);
STD_ROM_FN(virrea);

struct BurnDriverD BurnDrvMDvirrea = {
	"g_virrea", NULL, NULL, "199?",
	"Virtua Racing (E) [a1]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, virreaRomInfo, virreaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wacky Races (Beta)

static struct BurnRomInfo wacracRomDesc[]={
	{ "g_wacrac.bin", 0x200000, 0x1B173F09, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wacrac);
STD_ROM_FN(wacrac);

struct BurnDriverD BurnDrvMDwacrac = {
	"g_wacrac", NULL, NULL, "1900",
	"Wacky Races (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wacracRomInfo, wacracRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Warlock (Beta)

static struct BurnRomInfo warlobRomDesc[]={
	{ "g_warlob.bin", 0x200000, 0xC9B6EDB3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(warlob);
STD_ROM_FN(warlob);

struct BurnDriverD BurnDrvMDwarlob = {
	"g_warlob", NULL, NULL, "1994",
	"Warlock (Beta)\0", NULL, "Trimark / Acclaim", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, warlobRomInfo, warlobRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Waterworld (Beta)

static struct BurnRomInfo watrbRomDesc[]={
	{ "g_watrb.bin", 0x200000, 0x51C80498, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(watrb);
STD_ROM_FN(watrb);

struct BurnDriverD BurnDrvMDwatrb = {
	"g_watrb", NULL, NULL, "1900",
	"Waterworld (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, watrbRomInfo, watrbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Where in the World is Carmen Sandiego (E) (M5)

static struct BurnRomInfo wwcseRomDesc[]={
	{ "g_wwcse.bin", 0x100000, 0xEEF372E8, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wwcse);
STD_ROM_FN(wwcse);

struct BurnDriverD BurnDrvMDwwcse = {
	"g_wwcse", NULL, NULL, "1900",
	"Where in the World is Carmen Sandiego (E) (M5)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wwcseRomInfo, wwcseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Williams Arcade's Greatest Hits (E)

static struct BurnRomInfo wagheRomDesc[]={
	{ "g_waghe.bin", 0x080000, 0xC0DCE0E5, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(waghe);
STD_ROM_FN(waghe);

struct BurnDriverD BurnDrvMDwaghe = {
	"g_waghe", NULL, NULL, "1900",
	"Williams Arcade's Greatest Hits (E)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wagheRomInfo, wagheRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Winter Challenge (Beta)

static struct BurnRomInfo wchalbRomDesc[]={
	{ "g_wchalb.bin", 0x100000, 0x60D2A8C4, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wchalb);
STD_ROM_FN(wchalb);

struct BurnDriverD BurnDrvMDwchalb = {
	"g_wchalb", NULL, NULL, "1900",
	"Winter Challenge (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wchalbRomInfo, wchalbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Championship Soccer (JU) (REV02)

static struct BurnRomInfo wcs02RomDesc[]={
	{ "g_wcs02.bin", 0x040000, 0xBF84EDE6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcs02);
STD_ROM_FN(wcs02);

struct BurnDriverD BurnDrvMDwcs02 = {
	"g_wcs02", NULL, NULL, "1994",
	"World Championship Soccer (JU) (REV02)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wcs02RomInfo, wcs02RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Championship Soccer II (Beta)

static struct BurnRomInfo wcs2bRomDesc[]={
	{ "g_wcs2b.bin", 0x100000, 0xC1E21C1A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wcs2b);
STD_ROM_FN(wcs2b);

struct BurnDriverD BurnDrvMDwcs2b = {
	"g_wcs2b", NULL, NULL, "1900",
	"World Championship Soccer II (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wcs2bRomInfo, wcs2bRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World of Illusion Starring Mickey Mouse & Donald Duck (Beta)

static struct BurnRomInfo willbRomDesc[]={
	{ "g_willb.bin", 0x100000, 0x577F680F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(willb);
STD_ROM_FN(willb);

struct BurnDriverD BurnDrvMDwillb = {
	"g_willb", NULL, NULL, "1992",
	"World of Illusion Starring Mickey Mouse & Donald Duck (Beta)\0", NULL, "Disney / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, willbRomInfo, willbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Wrestle War (Beta)

static struct BurnRomInfo wwarbRomDesc[]={
	{ "g_wwarb.bin", 0x080000, 0x1CDEE87B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wwarb);
STD_ROM_FN(wwarb);

struct BurnDriverD BurnDrvMDwwarb = {
	"g_wwarb", NULL, NULL, "1900",
	"Wrestle War (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wwarbRomInfo, wwarbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Young Indiana Jones - Instrument of Chaos (Beta)

static struct BurnRomInfo yindybRomDesc[]={
	{ "g_yindyb.bin", 0x180000, 0xAD6C2050, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yindyb);
STD_ROM_FN(yindyb);

struct BurnDriverD BurnDrvMDyindyb = {
	"g_yindyb", NULL, NULL, "1900",
	"Young Indiana Jones - Instrument of Chaos (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yindybRomInfo, yindybRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Young Indiana Jones Chronicles (Beta)

static struct BurnRomInfo yindcbRomDesc[]={
	{ "g_yindcb.bin", 0x080000, 0x44F6BE35, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(yindcb);
STD_ROM_FN(yindcb);

struct BurnDriverD BurnDrvMDyindcb = {
	"g_yindcb", NULL, NULL, "1900",
	"Young Indiana Jones Chronicles (Beta)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, yindcbRomInfo, yindcbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zany Golf (UE) (REV01))

static struct BurnRomInfo zany01RomDesc[]={
	{ "g_zany01.bin", 0x080000, 0x74ED7607, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zany01);
STD_ROM_FN(zany01);

struct BurnDriverD BurnDrvMDzany01 = {
	"g_zany01", NULL, NULL, "1900",
	"Zany Golf (UE) (REV01))\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zany01RomInfo, zany01RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zero Wing (J)

static struct BurnRomInfo zwingjRomDesc[]={
	{ "g_zwingj.bin", 0x100000, 0x7E203D2B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zwingj);
STD_ROM_FN(zwingj);

struct BurnDriverD BurnDrvMDzwingj = {
	"g_zwingj", NULL, NULL, "1900",
	"Zero Wing (J)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zwingjRomInfo, zwingjRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Zombie High (U) (Prototype)

static struct BurnRomInfo zombhbRomDesc[]={
	{ "g_zombhb.bin", 0x0FA0EF, 0x7BEA6194, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(zombhb);
STD_ROM_FN(zombhb);

struct BurnDriverD BurnDrvMDzombhb = {
	"g_zombhb", NULL, NULL, "1900",
	"Zombie High (U) (Prototype)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, zombhbRomInfo, zombhbRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// 16 Ton (SN) (J) [!]

static struct BurnRomInfo g_16tonRomDesc[]={
	{ "g_16ton.bin", 0x040000, 0x537F04B6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(g_16ton);
STD_ROM_FN(g_16ton);

struct BurnDriverD BurnDrvMDg_16ton = {
	"g_16ton", NULL, NULL, "1994",
	"16 Ton (SN) (J) [!]\0", "No sound", "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, g_16tonRomInfo, g_16tonRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Hyper Marbles (SN) (J) [!]

static struct BurnRomInfo hymarRomDesc[]={
	{ "g_hymar.bin", 0x040000, 0x83BB2799, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(hymar);
STD_ROM_FN(hymar);

struct BurnDriverD BurnDrvMDhymar = {
	"g_hymar", NULL, NULL, "1994",
	"Hyper Marbles (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, hymarRomInfo, hymarRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Labyrinth of Death (SN) (J) [!]

static struct BurnRomInfo labydRomDesc[]={
	{ "g_labyd.bin", 0x040000, 0xA6D7E02D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(labyd);
STD_ROM_FN(labyd);

struct BurnDriverD BurnDrvMDlabyd = {
	"g_labyd", NULL, NULL, "1994",
	"Labyrinth of Death (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, labydRomInfo, labydRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Paddle Fighter (SN) (J) [!]

static struct BurnRomInfo padfiRomDesc[]={
	{ "g_padfi.bin", 0x040000, 0x3D8147E6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(padfi);
STD_ROM_FN(padfi);

struct BurnDriverD BurnDrvMDpadfi = {
	"g_padfi", NULL, NULL, "1994",
	"Paddle Fighter (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, padfiRomInfo, padfiRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II - Anne's Adventure (SN) (J) [!]

static struct BurnRomInfo p2anneRomDesc[]={
	{ "g_p2anne.bin", 0x040000, 0xFAFA5B6F, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(p2anne);
STD_ROM_FN(p2anne);

struct BurnDriverD BurnDrvMDp2anne = {
	"g_p2anne", NULL, NULL, "1994",
	"Phantasy Star II - Anne's Adventure (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, p2anneRomInfo, p2anneRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II - Huey's Adventure (SN) (J) [!]

static struct BurnRomInfo p2hueyRomDesc[]={
	{ "g_p2huey.bin", 0x040000, 0x1A076F83, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(p2huey);
STD_ROM_FN(p2huey);

struct BurnDriverD BurnDrvMDp2huey = {
	"g_p2huey", NULL, NULL, "1994",
	"Phantasy Star II - Huey's Adventure (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, p2hueyRomInfo, p2hueyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II - Kinds's Adventure (SN) (J) [!]

static struct BurnRomInfo p2kindRomDesc[]={
	{ "g_p2kind.bin", 0x040000, 0xC334F308, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(p2kind);
STD_ROM_FN(p2kind);

struct BurnDriverD BurnDrvMDp2kind = {
	"g_p2kind", NULL, NULL, "1994",
	"Phantasy Star II - Kinds's Adventure (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, p2kindRomInfo, p2kindRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Phantasy Star II - Shilka's Adventure (SN) (J) [!]

static struct BurnRomInfo p2shilRomDesc[]={
	{ "g_p2shil.bin", 0x040000, 0x1F83BEB2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(p2shil);
STD_ROM_FN(p2shil);

struct BurnDriverD BurnDrvMDp2shil = {
	"g_p2shil", NULL, NULL, "1994",
	"Phantasy Star II - Shilka's Adventure (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, p2shilRomInfo, p2shilRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Putter Golf (SN) (J) [!]

static struct BurnRomInfo putterRomDesc[]={
	{ "g_putter.bin", 0x040000, 0x20F168A6, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(putter);
STD_ROM_FN(putter);

struct BurnDriverD BurnDrvMDputter = {
	"g_putter", NULL, NULL, "1994",
	"Putter Golf (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, putterRomInfo, putterRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pyramid Magic (SN) (J) [!]

static struct BurnRomInfo pymagRomDesc[]={
	{ "g_pymag.bin", 0x040000, 0x306D839E, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pymag);
STD_ROM_FN(pymag);

struct BurnDriverD BurnDrvMDpymag = {
	"g_pymag", NULL, NULL, "1994",
	"Pyramid Magic (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pymagRomInfo, pymagRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pyramid Magic II (SN) (J) [!]

static struct BurnRomInfo pymag2RomDesc[]={
	{ "g_pymag2.bin", 0x040000, 0xC9DDAC72, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pymag2);
STD_ROM_FN(pymag2);

struct BurnDriverD BurnDrvMDpymag2 = {
	"g_pymag2", NULL, NULL, "1994",
	"Pyramid Magic II (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pymag2RomInfo, pymag2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pyramid Magic III (SN) (J) [!]

static struct BurnRomInfo pymag3RomDesc[]={
	{ "g_pymag3.bin", 0x040000, 0x8329820A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pymag3);
STD_ROM_FN(pymag3);

struct BurnDriverD BurnDrvMDpymag3 = {
	"g_pymag3", NULL, NULL, "1994",
	"Pyramid Magic III (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pymag3RomInfo, pymag3RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Pyramid Magic Special (SN) (J) [!]

static struct BurnRomInfo pymagsRomDesc[]={
	{ "g_pymags.bin", 0x040000, 0x153A3AFA, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(pymags);
STD_ROM_FN(pymags);

struct BurnDriverD BurnDrvMDpymags = {
	"g_pymags", NULL, NULL, "1994",
	"Pyramid Magic Special (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, pymagsRomInfo, pymagsRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sonic Eraser (SN) (J) [!]

static struct BurnRomInfo seraseRomDesc[]={
	{ "g_serase.bin", 0x040000, 0x62D8A0E7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(serase);
STD_ROM_FN(serase);

struct BurnDriverD BurnDrvMDserase = {
	"g_serase", NULL, NULL, "1994",
	"Sonic Eraser (SN) (J) [!]\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, seraseRomInfo, seraseRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Splatterhouse Part 3 (J) [a1]

static struct BurnRomInfo sho3jaRomDesc[]={
	{ "g_sho3ja.bin", 0x200000, 0xED68373A, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sho3ja);
STD_ROM_FN(sho3ja);

struct BurnDriverD BurnDrvMDsho3ja = {
	"g_sho3ja", NULL, NULL, "1900",
	"Splatterhouse Part 3 (J) [a1]\0", NULL, "Namco", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sho3jaRomInfo, sho3jaRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Radica: Volume 1 (Sonic the Hedgeho

static struct BurnRomInfo dicav1RomDesc[]={
	{ "radicav1.bin", 0x400000, 0x3B4C8438, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dicav1);
STD_ROM_FN(dicav1);

struct BurnDriverD BurnDrvMDdicav1 = {
	"radicav1", NULL, NULL, "2004",
	"Radica: Volume 1 (Sonic the Hedgeho\0", NULL, "Radica Games / Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dicav1RomInfo, dicav1RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Radica: Street Fighter Pack (Street Fighter 2' Special Champion Editio

static struct BurnRomInfo dicasfRomDesc[]={
	{ "radicasf.bin", 0x400000, 0x868AFB44, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(dicasf);
STD_ROM_FN(dicasf);

struct BurnDriverD BurnDrvMDdicasf = {
	"radicasf", NULL, NULL, "2004",
	"Radica: Street Fighter Pack (Street Fighter 2' Special Champion Editio\0", NULL, "Radica Games / Capcom", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, dicasfRomInfo, dicasfRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Prince of Persia 2 (Prototype)

static struct BurnRomInfo princ2RomDesc[]={
	{ "g_princ2.bin", 0x200000, 0x3AB44D46, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(princ2);
STD_ROM_FN(princ2);

struct BurnDriverD BurnDrvMDprinc2 = {
	"g_princ2", NULL, NULL, "1900",
	"Prince of Persia 2 (Prototype)\0", NULL, "Psygnosis", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, princ2RomInfo, princ2RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Sangokushi Retsuden (Ch)

static struct BurnRomInfo sanretRomDesc[]={
	{ "g_sanret.bin", 0x100000, 0x3B5CC398, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(sanret);
STD_ROM_FN(sanret);

struct BurnDriverD BurnDrvMDsanret = {
	"g_sanret", NULL, NULL, "1900",
	"Sangokushi Retsuden (Ch)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, sanretRomInfo, sanretRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// MegaMind (SN) (J)

static struct BurnRomInfo megamdRomDesc[]={
	{ "g_megamd.bin", 0x040000, 0x76DF2AE2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(megamd);
STD_ROM_FN(megamd);

struct BurnDriverD BurnDrvMDmegamd = {
	"g_megamd", NULL, NULL, "1900",
	"MegaMind (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, megamdRomInfo, megamdRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Aworg (SN) (J)

static struct BurnRomInfo aworgRomDesc[]={
	{ "g_aworg.bin", 0x040000, 0x069C27C1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(aworg);
STD_ROM_FN(aworg);

struct BurnDriver BurnDrvMDaworg = {
	"g_aworg", NULL, NULL, "1900",
	"Aworg (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, aworgRomInfo, aworgRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Teddy Boy Blues (SN) (J)

static struct BurnRomInfo teddyRomDesc[]={
	{ "g_teddy.bin", 0x040000, 0x733D2EB3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(teddy);
STD_ROM_FN(teddy);

struct BurnDriverD BurnDrvMDteddy = {
	"g_teddy", NULL, NULL, "1900",
	"Teddy Boy Blues (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, teddyRomInfo, teddyRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Robot Battler (SN) (J)

static struct BurnRomInfo robobtRomDesc[]={
	{ "g_robobt.bin", 0x040000, 0xFDF23EFF, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(robobt);
STD_ROM_FN(robobt);

struct BurnDriverD BurnDrvMDrobobt = {
	"g_robobt", NULL, NULL, "1900",
	"Robot Battler (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, robobtRomInfo, robobtRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Medal City (SN) (J)

static struct BurnRomInfo medalcRomDesc[]={
	{ "g_medalc.bin", 0x040000, 0x3EF4135D, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(medalc);
STD_ROM_FN(medalc);

struct BurnDriverD BurnDrvMDmedalc = {
	"g_medalc", NULL, NULL, "1900",
	"Medal City (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, medalcRomInfo, medalcRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Riddle Wired (SN) (J)

static struct BurnRomInfo riddleRomDesc[]={
	{ "g_riddle.bin", 0x040000, 0xFAE3D720, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(riddle);
STD_ROM_FN(riddle);

struct BurnDriverD BurnDrvMDriddle = {
	"g_riddle", NULL, NULL, "1900",
	"Riddle Wired (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, riddleRomInfo, riddleRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Kiss Shot (SN) (J)

static struct BurnRomInfo kissshRomDesc[]={
	{ "g_kisssh.bin", 0x040000, 0xE487088C, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(kisssh);
STD_ROM_FN(kisssh);

struct BurnDriverD BurnDrvMDkisssh = {
	"g_kisssh", NULL, NULL, "1900",
	"Kiss Shot (SN) (J)\0", NULL, "Sega", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, kissshRomInfo, kissshRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Ristar (UE) (REV00)

static struct BurnRomInfo rist00RomDesc[]={
	{ "g_rist00.bin", 0x200000, 0x9700139B, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(rist00);
STD_ROM_FN(rist00);

struct BurnDriverD BurnDrvMDrist00 = {
	"g_rist00", NULL, NULL, "1900",
	"Ristar (UE) (REV00)\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, rist00RomInfo, rist00RomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Super Volleyball (J) [x]

static struct BurnRomInfo svolxRomDesc[]={
	{ "g_svolx.bin", 0x040000, 0xE2EE8AD2, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(svolx);
STD_ROM_FN(svolx);

struct BurnDriverD BurnDrvMDsvolx = {
	"g_svolx", NULL, NULL, "1900",
	"Super Volleyball (J) [x]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, svolxRomInfo, svolxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Tecmo Cup (J) [x]

static struct BurnRomInfo tcupxRomDesc[]={
	{ "g_tcupx.bin", 0x080000, 0x88FDD060, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(tcupx);
STD_ROM_FN(tcupx);

struct BurnDriverD BurnDrvMDtcupx = {
	"g_tcupx", NULL, NULL, "1900",
	"Tecmo Cup (J) [x]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, tcupxRomInfo, tcupxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// World Class Leaderboard Golf (E) [x]

static struct BurnRomInfo wclbxRomDesc[]={
	{ "g_wclbx.bin", 0x080000, 0xDACA01C3, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(wclbx);
STD_ROM_FN(wclbx);

struct BurnDriverD BurnDrvMDwclbx = {
	"g_wclbx", NULL, NULL, "1900",
	"World Class Leaderboard Golf (E) [x]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, wclbxRomInfo, wclbxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Brian Lara Cricket 96 (E) [a1][x]

static struct BurnRomInfo blc96xRomDesc[]={
	{ "g_blc96x.bin", 0x100000, 0xFE52F7E1, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(blc96x);
STD_ROM_FN(blc96x);

struct BurnDriverD BurnDrvMDblc96x = {
	"g_blc96x", "g_bl96", NULL, "1900",
	"Brian Lara Cricket 96 (E) [a1][x]\0", NULL, "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, blc96xRomInfo, blc96xRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};

// Asterix and the Power of The Gods (E) (M5) [x] (Beta?)

static struct BurnRomInfo astpgxRomDesc[]={
	{ "g_astpgx.bin", 0x200000, 0x45C8B5B7, BRF_PRG }, // 68000 code
};

STD_ROM_PICK(astpgx);
STD_ROM_FN(astpgx);

struct BurnDriverD BurnDrvMDastpgx = {
	"g_astpgx", "g_aspg", NULL, "1900",
	"Asterix and the Power of The Gods (E) (M5) [x] (Beta?)\0", "No sound", "Unsorted", "Megadrive",
	NULL, NULL, NULL, NULL,
	BDF_GAME_WORKING | BDF_CLONE, 2, HARDWARE_SEGA_MEGADRIVE,
	NULL, astpgxRomInfo, astpgxRomName, MegadriveInputInfo, MegadriveDIPInfo,
	MegadriveInit, MegadriveExit, MegadriveFrame, NULL, MegadriveScan,
	&bMegadriveRecalcPalette, 320, 224, 4, 3
};
