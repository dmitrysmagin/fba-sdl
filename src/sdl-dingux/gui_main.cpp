/*
 * FinalBurn Alpha for Dingux/OpenDingux
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "burner.h"
#include "sdl_run.h"
#include "gui_main.h"
#include "gui_gfx.h"
#include "gui_romlist.h"
#include "gui_config.h"
#include "gui_setpath.h"

#define ROMLIST(A,B) romlist.A[gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone)[B]]

SDL_Event event;

SDL_Surface *screen2 = NULL;
SDL_Surface *gui_screen = NULL;
SDL_Surface *bg = NULL;
SDL_Surface *bgs = NULL;
SDL_Surface *bg_temp = NULL;
SDL_Surface *font = NULL;
SDL_Surface *barre = NULL;
SDL_Surface *preview = NULL;
SDL_Surface *title = NULL;
SDL_Surface *help = NULL;
SDL_Surface *credit = NULL;
SDL_Surface *Tmp = NULL;

FILE *fp;
FILE *fp2;

unsigned int font6x[255];
int i;
unsigned char flag_preview;
char g_string[255];
unsigned char offset_x, offset_y;

SELECTOR sel;

unsigned char joy_speed[4]={0,1,3,7};

static char *abreviation_cf[8][7]={
	{"Disable","Enable","","","","",""},
	{"Original","Fullscreen","","","","",""},
	{"Off","Auto","Manual","","","",""},
	{"C68k","M68k","A68k","","","",""},
	{"CZ80","MAME Z80","","","","",""},
	{"Off","On","","","","",""},
	{"Off","LIBAO","SDL","SDL old","","",""},
	{"11025", "16000", "22050", "32000", "44100", "", ""}
};

void load_lastsel();
void save_lastsel();

void redraw_screen(void)
{
	SDL_Rect dstRect;
	dstRect.x = (screen2->w - gui_screen->w) / 2;
	dstRect.y = (screen2->h - gui_screen->h) / 2;

	SDL_Delay(16);
	SDL_BlitSurface(gui_screen, NULL, screen2, &dstRect);
	SDL_Flip(screen2);
}

void free_memory(void)
{
	printf("Freeing surfaces\n");
	if (screen2) SDL_FreeSurface(screen2);
	SDL_FreeSurface(gui_screen);
	SDL_FreeSurface(bg);
	SDL_FreeSurface(bgs);
	SDL_FreeSurface(bg_temp);
	SDL_FreeSurface(font);
	SDL_FreeSurface(barre);
	SDL_FreeSurface(preview);
	SDL_FreeSurface(title);
	SDL_FreeSurface(help);
	SDL_FreeSurface(credit);
	//printf("Freeing memory\n");
	/*for (ii=0;ii<romlist.nb_list[0];++ii){
		free(romlist.name[ii]);
		free(romlist.zip[ii]);
		free(romlist.manufacturer[ii]);
		free(romlist.parent[ii]);
	}*/
}

int exit_prog(void)
{
	//menage avant execution
	free_memory();

	SDL_JoystickClose(0);
	//SDL_Quit();

	return 0;

}

void put_string(char *string, unsigned int pos_x, unsigned int pos_y, unsigned char couleur, SDL_Surface *s)
{
	SDL_Rect Src;
	SDL_Rect Dest;

	Src.y = couleur;
	Src.w = 5;
	Src.h = 9;
	Dest.y = pos_y;

	while(*string)
	{
		if (font6x[*string]){
			Src.x = font6x[*string];
			Dest.x = pos_x;
			SDL_BlitSurface(font, &Src, s, &Dest);
		}
		++string;
		pos_x += 6;
	}
}



void put_stringM(char *string, unsigned int pos_x, unsigned int pos_y, unsigned int taille, unsigned char couleur)
{
	SDL_Rect Src;
	SDL_Rect Dest;
	unsigned char caratere;

	if( taille > sel.x ){

		string += sel.x ;

		Src.y = couleur;
		Src.w = 5;
		Src.h = 9;
		Dest.y = pos_y;


		if ( (taille-sel.x) > 52 ) {
			for( caratere=sel.x ; caratere<(sel.x+48) ; ++caratere)
			{
				if (font6x[*string]){
					Src.x = font6x[*string];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, gui_screen, &Dest);
				}
				++string;
				pos_x += 6;
			}
			for( caratere=0 ; caratere<3 ; ++caratere)
			{
				if (font6x[*string]){
					Src.x = font6x[46];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, gui_screen, &Dest);
				}
				pos_x += 6;
			}
		}else{
			while(*string)
			{
				if (font6x[*string]){
					Src.x = font6x[*string];
					Dest.x = pos_x;
					SDL_BlitSurface(font, &Src, gui_screen, &Dest);
				}
				++string;
				pos_x += 6;
			}
		}
	}
}

/*void show_screen(char * text)
{
	#define CREDIT_X	68
	#define CREDIT_Y	62
	#define CREDIT_L	184
	#define CREDIT_H	116
	Uint32 Pnoir = SDL_MapRGB(credit->format, 0, 0, 0);
	Uint32 Pblanc = SDL_MapRGB(credit->format, 255, 255, 255 );
	//capture gui_screen actuel
	drawSprite( gui_screen , credit , 0 , 0 , 0 , 0 , 320 , 240 );
	//detourage
	ligneV( credit , CREDIT_X-1 , CREDIT_Y , CREDIT_H , Pnoir );
	ligneV( credit , CREDIT_X+CREDIT_L , CREDIT_Y , CREDIT_H , Pnoir );
	ligneH( credit , CREDIT_X , CREDIT_Y-1 , CREDIT_L , Pnoir);
	ligneH( credit , CREDIT_X , CREDIT_Y+CREDIT_H , CREDIT_L , Pnoir);
	//cadre
	carre_plein( credit , CREDIT_X, CREDIT_Y, CREDIT_L, CREDIT_H, Pblanc);
	carre_plein( credit , CREDIT_X+1, CREDIT_Y+1, CREDIT_L-2, CREDIT_H-2, Pnoir);

	put_string( "Set Keys" , 142 , CREDIT_Y+8 , BLANC , credit );
	put_string( text , CREDIT_X+8 , CREDIT_Y+24 , BLEU , credit );
}*/


void load_preview(unsigned int numero)
{
	if (romlist.nb_list[cfg.list] == 0) {
		flag_preview = 0;
		return;
	}

	char *ext[2] = {"png", "bmp"};
	FILE *fp;

	for(int i = 0; i < 2; i++) {
		sprintf((char*)g_string, "%s/%s.%s", szAppPreviewPath, ROMLIST(zip, numero), ext[i]);

		// check first current rom
		if((fp = fopen(g_string, "r")) != NULL) {
			fclose(fp);
			preview = IMG_Load(g_string);
			drawSprite(bg, bg_temp, 124, 3, 124, 3, 192, 112);
			drawSprite(preview, bg_temp, 0, 0, 220 - preview->w / 2, 3, 192, 112);

			flag_preview = 1;
			return;
		} 

		// then check parent rom
		if(strcmp(ROMLIST(parent, numero), "fba") != 0) {
			sprintf((char*)g_string, "%s/%s.%s", szAppPreviewPath, ROMLIST(parent, numero), ext[i]);

			if((fp = fopen(g_string, "r")) != NULL) {
				fclose(fp);
				preview = IMG_Load(g_string);
				drawSprite(bg, bg_temp, 124, 3, 124, 3, 192, 112);
				drawSprite(preview, bg_temp, 0, 0, 220 - preview->w / 2, 3, 192, 112);

				flag_preview = 1;
				return;
			} 
		}
	}

	// nothing is found
	drawSprite(bg, bg_temp, 124, 3, 124, 3, 192, 112);

	sprintf((char*)g_string, "PREVIEW %s.bmp", ROMLIST(zip, numero));
	put_string(g_string, 160, 49, ROUGE, bg_temp);
	put_string("NOT AVAILABLE", 181, 59, ROUGE, bg_temp);

	flag_preview = 0;
}

char ss_prg_credit(void)
{
	#define CREDIT_X	68
	#define CREDIT_Y	62
	#define CREDIT_L	184
	#define CREDIT_H	116

	unsigned int compteur = 1;
	Uint32 Pnoir = SDL_MapRGB(credit->format, 0, 0, 0);
	Uint32 Pblanc = SDL_MapRGB(credit->format, 255, 255, 255);

	drawSprite(gui_screen, credit, 0, 0, 0, 0, 320, 240);

	ligneV(credit, CREDIT_X - 1, CREDIT_Y, CREDIT_H, Pnoir);
	ligneV(credit, CREDIT_X + CREDIT_L, CREDIT_Y, CREDIT_H, Pnoir);
	ligneH(credit, CREDIT_X, CREDIT_Y - 1, CREDIT_L, Pnoir);
	ligneH(credit, CREDIT_X, CREDIT_Y + CREDIT_H, CREDIT_L, Pnoir);

	carre_plein( credit , CREDIT_X, CREDIT_Y, CREDIT_L, CREDIT_H, Pblanc);
	carre_plein( credit , CREDIT_X+1, CREDIT_Y+1, CREDIT_L-2, CREDIT_H-2, Pnoir);

	put_string("CREDIT", 142, CREDIT_Y + 8, BLANC, credit);
	put_string("Final Burn Alpha v" VERSION, CREDIT_X + 8, CREDIT_Y + 24, BLEU, credit);
	put_string("for OpenDingux", CREDIT_X + 48, CREDIT_Y + 34, BLEU, credit);
	put_string("Frontend is based on Capex", CREDIT_X + 8, CREDIT_Y + 54, VERT, credit);
	put_string("by JyCet and Juanvvc", CREDIT_X + 32, CREDIT_Y + 64, VERT, credit);
	put_string("Skin by HiBan", CREDIT_X + 56, CREDIT_Y + 88, VERT, credit);

	put_string("Press (SELECT) to quit", 85, CREDIT_Y + 100, BLANC, credit);

	while(1)
	{
		drawSprite( credit , gui_screen , 0 , 0 , 0 , 0 , 320 , 240 );
		redraw_screen();

		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN) {
			if(compteur == 0 || (compteur > cfg.delayspeed && ((compteur & joy_speed[cfg.repeatspeed]) == 0))) {
				if(event.key.keysym.sym == SDLK_ESCAPE ) {
					return 1;
				} else return 0;
			}
			++compteur;
		}else if(event.type == SDL_KEYUP) {
			compteur=0;
		}
	}
}

void ss_prg_help(void)
{
	#define HELP_X	53
	#define HELP_Y	62
	#define HELP_L	214
	#define HELP_H	116

	unsigned int compteur = 1;
	Uint32 Pnoir = SDL_MapRGB(help->format, 0, 0, 0);
	Uint32 Pblanc = SDL_MapRGB(help->format, 255, 255, 255);

	drawSprite(gui_screen, help, 0, 0, 0, 0, 320, 240);

	ligneV(help, HELP_X - 1, HELP_Y , HELP_H , Pnoir);
	ligneV(help, HELP_X + HELP_L, HELP_Y, HELP_H, Pnoir);
	ligneH(help, HELP_X, HELP_Y - 1, HELP_L, Pnoir);
	ligneH(help, HELP_X, HELP_Y + HELP_H, HELP_L, Pnoir);

	carre_plein(help, HELP_X, HELP_Y, HELP_L, HELP_H, Pblanc);
	carre_plein(help, HELP_X + 1, HELP_Y + 1, HELP_L - 2, HELP_H - 2, Pnoir);

	put_string("COLOR HELP", 130, HELP_Y + 8, BLANC, help);
	put_string("RED      missing", HELP_X + 48, HELP_Y + 24, ROUGE, help);
	put_string("YELLOW   parent rom", HELP_X + 48, HELP_Y + 34, JAUNE, help);
	put_string("ORANGE   clone rom", HELP_X + 48, HELP_Y + 44, ORANGE, help);
	//put_string("         & parent detected", HELP_X + 8, HELP_Y + 54, JAUNE, help);
	//put_string("GREEN    clone & parent & cache", HELP_X + 8, HELP_Y + 64, VERT, help);
	//put_string("         detected", HELP_X + 8, HELP_Y + 74, VERT, help);
	//put_string("BLUE     parent & cache detected", HELP_X + 8, HELP_Y + 84, BLEU, help);
	put_string("Any button to return", 100, HELP_Y + 100, BLANC, help);

	int Hquit = 0;
	while(!Hquit) {
		drawSprite(help, gui_screen, 0, 0, 0, 0, 320, 240);
		redraw_screen();

		SDL_PollEvent(&event);
		if (event.type==SDL_KEYDOWN){
			//if (compteur==0 || (compteur>cfg.delayspeed && ((compteur&joy_speed[cfg.repeatspeed])==0))){
				//if ( event.key.keysym.sym==SDLK_A ){
				if ( event.key.keysym.sym > 0)
					if (compteur==0) Hquit = 1 ;
				//}
			//}
			++compteur;
		}else if (event.type==SDL_KEYUP){
			compteur = 0;
		}
	}
}

void init_title(void)
{
	SDL_RWops *rw;

#if 0
	//load background interne ou skin
	rw = SDL_RWFromMem(gfx_BG,sizeof(gfx_BG)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (cfg.skin){
		if ((fp = fopen( "./skin/capex_bg.bmp" , "r")) != NULL){
			Tmp = SDL_LoadBMP( "./skin/capex_bg.bmp" );
			fclose(fp);
		}
	}
	bg = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
#endif
	bg = IMG_Load("./skin/fba_bg.png");

#if 0
	//load selector interne ou skin
	rw = SDL_RWFromMem(gfx_SELECTEUR,sizeof(gfx_SELECTEUR)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (cfg.skin){
		if ((fp = fopen( "./skin/capex_sel.bmp" , "r")) != NULL){
			Tmp = SDL_LoadBMP( "./skin/capex_sel.bmp" );
			fclose(fp);
		}
	}
	barre = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_SetColorKey(barre ,SDL_SRCCOLORKEY,SDL_MapRGB(barre ->format,255,0,255));
#endif
	barre = IMG_Load("./skin/fba_selector.png");

#if 0
	//load title interne ou skin
	rw = SDL_RWFromMem(gfx_CAPEX,sizeof(gfx_CAPEX)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	if (cfg.skin){
		if ((fp = fopen( "./skin/capex_title.bmp" , "r")) != NULL){
			Tmp = (SDL_Surface *)IMG_Load( "./skin/capex_title.bmp" );
			fclose(fp);
		}
	}
	title = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_SetColorKey(title ,SDL_SRCCOLORKEY,SDL_MapRGB(title ->format,255,0,255));
#endif
	title = IMG_Load("./skin/fba_title.png");

#if 0
	rw = SDL_RWFromMem(gfx_FONT,sizeof(gfx_FONT)/sizeof(unsigned char));
	Tmp = SDL_LoadBMP_RW(rw,0);
	font = SDL_DisplayFormat(Tmp);
	SDL_FreeSurface(Tmp);
	SDL_FreeRW (rw);
	SDL_SetColorKey(font,SDL_SRCCOLORKEY,SDL_MapRGB(font->format,255,0,255));
#endif
	font = IMG_Load("./skin/fba_font.png");

	bg_temp = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	bgs = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	help = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);
	credit = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);

	drawSprite( bg , bgs , 0 , 0 , 0 , 0 , 320 , 240 );
	if (cfg.FXshadow < 100) gui_set_gamma(bgs, cfg.FXshadow);

	preparation_fenetre( bgs , bg , 124 , 3 , 192 , 112 );
	preparation_fenetre( bgs , bg , 4 , 53 , 116 , 62 );

	drawSprite( title , bg, 0, 0, 0, 0, 123, 52);

	// precalculate font6 x coordinate
	for(i = 0; i < 32; ++i) font6x[i] = 0;
	for(i = 32; i < 255; ++i) font6x[i] = (i - 32) * 6;
}

void prep_bg()
{
	drawSprite(bg, bg_temp, 0, 0, 0, 0, 320, 240);
	preparation_fenetre(bgs, bg_temp, 4, 119, 312, 118);
	if(flag_preview && romlist.nb_list[cfg.list] != 0) {
		drawSprite(preview, bg_temp, 0, 0, 220 - preview->w / 2, 3, 192, 112);
	}

	switch(cfg.list) {
	case 0:
		sprintf((char*)g_string, "All: %d roms", unfiltered_nb_list[0]);
		break;
	case 1:
		sprintf((char*)g_string, "Missing: %d roms", unfiltered_nb_list[1]);
		break;
	case 2:
		sprintf((char*)g_string, "Available: %d roms", unfiltered_nb_list[2]);
		break;
	case 3:
		sprintf((char*)g_string, "Playable: %d roms", unfiltered_nb_list[3]);
		break;
	}

	put_string( g_string , 6 , 95 , BLANC , bg_temp );
	
	sprintf((char*)g_string, "Show: %d roms", romlist.nb_list[cfg.list]);
	put_string( g_string , 6 , 105 , BLANC , bg_temp );
}

void prep_bg_main(void)
{
	gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone); // update romlist counters
	prep_bg();
	sprintf((char*)g_string, "Hardware %s; Genre: %s", hardwares[cfg.hardware].label, genres[cfg.genre].label);
	put_string( g_string , 6 , 120 , BLEU , bg_temp );
}

void prep_bg_opt(int first)
{
	if (first == OPTION_MAIN_FIRST) {
		prep_bg();
		sprintf((char*)g_string, "Main settings:");
		put_string( g_string , 6 , 120 , BLEU , bg_temp );
	} else if (first == OPTION_FILTER_FIRST) {
		prep_bg_main();
	} else if (first == OPTION_PATHS_FIRST) {
		prep_bg();
		sprintf((char*)g_string, "ROMs Paths:");
		put_string( g_string , 6 , 120 , BLEU , bg_temp );
	}
}

void prep_bg_run(void)
{
	prep_bg();
	preparation_fenetre(bgs, bg_temp, 4, 119, 260, 118);
	preparation_fenetre(bgs, bg_temp, 269, 119, 47, 118);
}

void affiche_BG(void)
{
	drawSprite(bg_temp, gui_screen, 0, 0, 0, 0, 320, 240);

	if (romlist.nb_list[cfg.list] == 0)
	{
		return;
	}

	sprintf((char*)g_string, "Rom: %s", ROMLIST(zip, sel.rom));
	put_string(g_string, 6, 55, BLANC, gui_screen);

	if(strcmp(ROMLIST(parent, sel.rom), "fba") == 0) {
		//put_string("Parent rom", 6, 65, BLANC, gui_screen);
	} else {
		sprintf((char*)g_string, "Clone of %s", ROMLIST(parent, sel.rom));
		put_string(g_string, 6, 65, BLANC, gui_screen);
	}

	if(ROMLIST(year, sel.rom) != NULL) {
		put_string(ROMLIST(year, sel.rom), 6, 75, BLANC, gui_screen);
	}

	if(ROMLIST(manufacturer, sel.rom) != NULL) {
		put_string(ROMLIST(manufacturer, sel.rom), 6, 85, BLANC, gui_screen);
	}

}

void put_option_line(int first, unsigned char num, unsigned char y)
{
	switch(first + num) {
	// MAIN OPTIONS
	case OPTION_GUI_DELAYSPEED:
		sprintf((char*)g_string, "Keyrepeat delay: %d" , cfg.delayspeed );
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_REPEATSPEED:
		sprintf((char*)g_string, "Keyrepeat speed: %d" , cfg.repeatspeed );
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_FILTER:
		sprintf((char*)g_string, "Filter settings -->");
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_ROM_PATHS:
		sprintf((char*)g_string, "ROMs Paths -->");
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_SHADOW:
		sprintf((char*)g_string, "Background shadow: %d%c" , cfg.FXshadow, 37 );
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_SKIN:
		if (cfg.skin) put_string( "External skin: Enable" , OPTIONS_START_X , y , BLANC , gui_screen );
		else put_string( "External skin: Disable" , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_RETURN:
		put_string( "Return to the rom list" , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	// FILTER OPTIONS
	case OPTION_GUI_FILTER_LIST:
		if (cfg.list == 3) put_string( "Show roms: Playable only" , OPTIONS_START_X , y , BLANC , gui_screen );
		else if (cfg.list == 2) put_string( "Show roms: Available only" , OPTIONS_START_X , y , BLANC , gui_screen );
		else if (cfg.list == 1) put_string( "Show roms: Missing only" , OPTIONS_START_X , y , BLANC , gui_screen );
		else put_string( "Show roms: All" , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_FILTER_HARDWARE:
		sprintf((char*)g_string, "Hardware: %s",  hardwares[cfg.hardware].label);
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_FILTER_GENRE:
		sprintf((char*)g_string, "Genre: %s", genres[cfg.genre].label);
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_FILTER_CLONE:
		sprintf((char*)g_string, "Show clones: %s", clones[cfg.clone].label);
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_FILTER_RETURN:
		put_string( "Return to the main settings" , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	// PATHS OPTIONS
	case OPTION_GUI_PATH0:
	case OPTION_GUI_PATH1:
	case OPTION_GUI_PATH2:
	case OPTION_GUI_PATH3:
	case OPTION_GUI_PATH4:
	case OPTION_GUI_PATH5:
	case OPTION_GUI_PATH6:
	case OPTION_GUI_PATH7:
	case OPTION_GUI_PATH8:
	case OPTION_GUI_PATH9:
	case OPTION_GUI_PATH10:
	case OPTION_GUI_PATH11:
	case OPTION_GUI_PATH12:
	case OPTION_GUI_PATH13:
	case OPTION_GUI_PATH14:
	case OPTION_GUI_PATH15:
	case OPTION_GUI_PATH16:
	case OPTION_GUI_PATH17:
	case OPTION_GUI_PATH18:
	case OPTION_GUI_PATH19:
		sprintf((char*)g_string, "Rom path %d: %s" , first + num - OPTION_GUI_PATH0 + 1,szAppRomPaths[first + num - OPTION_GUI_PATH0]);
		put_string( g_string , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	case OPTION_GUI_PATH_RETURN:
		put_string( "Return to the main settings" , OPTIONS_START_X , y , BLANC , gui_screen );
		break;
	}
}

void gui_reset_selection()
{
	sel.y = START_Y - 1;
	sel.x = 0;
	sel.rom = 0;
	sel.ofs = 0;
}

void gui_validate_selection()
{
	gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone); // apply filters
	if (sel.rom < 0 || sel.ofs < 0 ||
		sel.y < START_Y - 1 || sel.y > START_Y + (LINES_COUNT - 1) * LINE_HEIGHT ||
		sel.rom > romlist.nb_list[cfg.list] - 1 ||
		sel.ofs > romlist.nb_list[cfg.list] - 1)
	{
		gui_reset_selection();	
	}
}

void ss_prg_options(int first, int last)
{
	int options_y, options_num, options_off, options_start_y, options_last_line;
	int Quit;
	unsigned int compteur = 1;

	options_last_line = OPTIONS_LINE_COUNT - 1;
	options_start_y = START_Y + LINE_HEIGHT;
	options_y = options_start_y - 1;
	options_num = 0;
	options_off = 0;

	last = last - first;

	unsigned option_start;

	gui_load_cfg();

	prep_bg_opt(first);
	Quit=0;
	while(!Quit) {
		affiche_BG();

		drawSprite(barre, gui_screen, 0, 0, 4, options_y, 312, 10);

		option_start = options_start_y;
		for(int y = options_off; y < (options_off + OPTIONS_LINE_COUNT); y++) {
			put_option_line(first, y, option_start);
			option_start += LINE_HEIGHT;
		}
		redraw_screen();
		//SDL_Flip(gui_screen);

		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN) {
			if(compteur == 0 || (compteur > cfg.delayspeed && ((compteur & joy_speed[cfg.repeatspeed]) == 0))) {
				if(event.key.keysym.sym == SDLK_DOWN) {
					if(options_num == last && compteur == 0) {
						options_y = options_start_y - 1;
						options_num = 0;
						options_off = 0;
					} else {
						if(options_num < options_last_line || options_off == ( last - options_last_line)) {
							if(options_num < last) {
								options_y += LINE_HEIGHT;
								++options_num;
							}
						} else {
							++options_off;
							++options_num;
						}
					}
				} else if(event.key.keysym.sym == SDLK_UP) {
					if(options_num == 0 && compteur == 0) {
						options_y = options_start_y - 1 + ((last < options_last_line ? last : options_last_line) * LINE_HEIGHT);
						options_num = last;
						options_off = last < options_last_line ? 0 : last - options_last_line;
					} else {
						if(options_num > (last - options_last_line / 2) || options_off == 0) {
							if(options_num > 0) {
								options_y -= LINE_HEIGHT;
								--options_num;
							}
						} else {
							--options_off;
							--options_num;
						}
					}
				// PROCESS OPTIONS
				} else if (event.key.keysym.sym == SDLK_LEFT) {
					switch(first + options_num) {
						case OPTION_GUI_DELAYSPEED:
							--cfg.delayspeed;
							if(cfg.delayspeed == 9) cfg.delayspeed = 50;
							break;
						case OPTION_GUI_REPEATSPEED:
							--cfg.repeatspeed;
							if(cfg.repeatspeed == -1) cfg.repeatspeed = 3;
							break;
						case OPTION_GUI_SHADOW:
							--cfg.FXshadow;
							if(cfg.FXshadow == -1) cfg.FXshadow = 100;
							break;
						case OPTION_GUI_SKIN:
							cfg.skin ^= 1;
							break;
						case OPTION_GUI_FILTER_LIST:
							// prev filter
							cfg.list--;
							if (cfg.list < 0) cfg.list = NB_FILTERS - 1;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_HARDWARE:
							// prev hardware
							cfg.hardware--;
							if (cfg.hardware < 0) cfg.hardware = NB_HARDWARES - 1;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_GENRE:
							// prev genre
							cfg.genre--;
							if (cfg.genre < 0) cfg.genre = NB_GENRES - 1;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_CLONE:
							// prev clone option
							cfg.clone--;
							if (cfg.clone < 0) cfg.clone = NB_CLONES - 1;
							gui_reset_selection();
							break;
					}
				} else if(event.key.keysym.sym == SDLK_RIGHT) {
					switch(first + options_num) {
						case OPTION_GUI_DELAYSPEED:
							++cfg.delayspeed;
							if(cfg.delayspeed == 51) cfg.delayspeed = 10;
							break;
						case OPTION_GUI_REPEATSPEED:
							++cfg.repeatspeed;
							if(cfg.repeatspeed == 4) cfg.repeatspeed = 0;
							break;
						case OPTION_GUI_SHADOW:
							++cfg.FXshadow;
							if(cfg.FXshadow == 101) cfg.FXshadow = 0;
							break;
						case OPTION_GUI_SKIN:
							cfg.skin ^= 1;
							break;
						case OPTION_GUI_FILTER_LIST:
							// next filter
							cfg.list = (cfg.list + 1) % NB_FILTERS;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_HARDWARE:
							// next hardware
							cfg.hardware = (cfg.hardware + 1) % NB_HARDWARES;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_GENRE:
							// next hardware
							cfg.genre = (cfg.genre + 1) % NB_GENRES;
							gui_reset_selection();
							break;
						case OPTION_GUI_FILTER_CLONE:
							// next clone option
							cfg.clone = (cfg.clone + 1) % NB_CLONES;
							gui_reset_selection();
							break;
					}
				} else if(event.key.keysym.sym == SDLK_LCTRL) {
					int option = first + options_num;		
					if(option >= OPTION_GUI_PATH0 && option <= OPTION_GUI_PATH19) {
						// call set path menu
						gui_setpath(szAppRomPaths[option - OPTION_GUI_PATH0]);
						prep_bg_opt(first);
					} else if(option == OPTION_GUI_RETURN) {
						prep_bg_main();
						Quit = 1;
					} else if(option == OPTION_GUI_FILTER_RETURN || option == OPTION_GUI_PATH_RETURN) {
						Quit = 1;
					} else if (option == OPTION_GUI_FILTER) {
						ss_prg_options(OPTION_FILTER_FIRST, OPTION_FILTER_LAST);
						gui_write_cfg();
						prep_bg_opt(first);
					} else if (option == OPTION_GUI_ROM_PATHS) {
						ss_prg_options(OPTION_PATHS_FIRST, OPTION_PATHS_LAST);
						gui_write_cfg();
						prep_bg_opt(first);
					}
				} else if(event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE) {
					if(first + options_num >= OPTION_GUI_PATH0 && first + options_num <= OPTION_GUI_PATH19) {
						strcpy(szAppRomPaths[first + options_num - OPTION_GUI_PATH0], "");
					}
				} else if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_LALT) {
					prep_bg_main();
					Quit = 1;
				}
			}
			++compteur;
		}else if(event.type == SDL_KEYUP){
			compteur = 0;// reinitialisation joystick
		}

		if (!Quit && first == OPTION_FILTER_FIRST)
		{
			prep_bg_opt(first);
		}

	}
	gui_write_cfg();
}

static int run_options[] = {
	OPTION_FBA_RUN,
	OPTION_FBA_SOUND,
	OPTION_FBA_SAMPLERATE,
	OPTION_FBA_VSYNC,
	OPTION_FBA_SHOWFPS,
	OPTION_FBA_68K,
#ifdef OPTIONS_FOR_A320
	OPTION_FBA_Z80,
#endif
#ifdef OPTIONS_FOR_GCW0
	OPTION_FBA_ANALOG,
#endif
	0
};

void put_run_option_line(unsigned char num, unsigned char y)
{
	#define OPTIONS_START_X		8
	#define CONF_START_X		272

	switch (num) {
	case OPTION_FBA_RUN:
		put_string("Run game", OPTIONS_START_X, y, BLANC, gui_screen);
		break;
	case OPTION_FBA_SOUND:
		put_string( "Sound" , OPTIONS_START_X , y , BLANC , gui_screen );
		put_string(abreviation_cf[6][options.sound], CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_SAMPLERATE:
		put_string("Audio sample rate", OPTIONS_START_X , y , BLANC , gui_screen );
		sprintf((char*)g_string, "%sHz" , abreviation_cf[7][options.samplerate]);
		put_string(g_string, CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_VSYNC:
		put_string("Vertical sync", OPTIONS_START_X, y, BLANC, gui_screen);
		put_string(abreviation_cf[5][options.vsync], CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_SHOWFPS:
		put_string("Show FPS", OPTIONS_START_X, y, BLANC, gui_screen);
		put_string(abreviation_cf[0][options.showfps], CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_68K:
		put_string("68K Emu Core", OPTIONS_START_X, y, BLANC, gui_screen);
		put_string(abreviation_cf[3][options.m68kcore], CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_Z80:
		put_string("Z80 Emu Core", OPTIONS_START_X, y, BLANC, gui_screen);
		put_string(abreviation_cf[4][options.z80core], CONF_START_X, y, VERT, gui_screen);
		break;
	case OPTION_FBA_ANALOG:
		put_string("Analogue Sensitivity", OPTIONS_START_X, y, BLANC, gui_screen);
		sprintf((char*)g_string, "%d%%" , options.sense);
		put_string(g_string, CONF_START_X, y, VERT, gui_screen);
		break;
	}
}

void ss_prog_run(void)
{
	int opt_first = 0, opt_last = (sizeof(run_options) / sizeof(int)) - 2;
#undef OPTION_FBA_FIRST
#undef OPTION_FBA_LAST

#define OPTION_FBA_FIRST opt_first
#define OPTION_FBA_LAST opt_last

	#define RUN_START_X	8

	int run_y, run_num, run_off;
	int Quit;
	unsigned int compteur = 1;

	nBurnDrvActive = gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone)[sel.rom];
	if(!ConfigGameLoad()) ConfigGameSave();

	run_y = START_Y-1;
	run_num = 0;
	run_off = 0;

	prep_bg_run();

	Quit=0;

	while(!Quit) {
		affiche_BG();

		drawSprite(barre, gui_screen, 0, 0, 4, run_y, 260, 10);
		drawSprite(barre, gui_screen, 0, 0, 269, run_y, 47, 10);

		int option_start = START_Y;

		for (int i = 0; i <= opt_last; i++) {
			if(i + run_off <= opt_last)
				put_run_option_line(run_options[i + run_off], option_start);
			option_start += 9;
		}

		redraw_screen();
		//SDL_Flip(gui_screen);

		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN) {
			if(compteur == 0 || (compteur > cfg.delayspeed && ((compteur & joy_speed[cfg.repeatspeed]) == 0))) {
				if(event.key.keysym.sym == SDLK_DOWN) {
					run_num++;
					if(run_num > OPTION_FBA_LAST) {
						run_y = START_Y - 1;
						run_num = OPTION_FBA_FIRST;
						run_off = run_num;
					} else {
						if(run_num < 12 || run_off > OPTION_FBA_LAST - 12) {
							run_y += 9;
						} else run_off++;
					}
				} else if(event.key.keysym.sym == SDLK_UP) {
					run_num--;
					if(run_num < OPTION_FBA_FIRST){
						run_y = START_Y - 1 + ((OPTION_FBA_LAST < 12 ? OPTION_FBA_LAST : 12) * 9);
						run_num = OPTION_FBA_LAST;
						run_off = OPTION_FBA_LAST < 12 ? 0 : OPTION_FBA_LAST - 12;
					} else {
						if(run_num >= OPTION_FBA_LAST - 7 || run_off == 0) run_y -= 9; else run_off--;
					}
				} else if (event.key.keysym.sym == SDLK_LEFT) {
					switch(run_options[run_num]) {
						case OPTION_FBA_SOUND:
							options.sound--;
							if(options.sound < 0) options.sound = 3;
							break;
						case OPTION_FBA_SAMPLERATE:
							options.samplerate--;
							if(options.samplerate < 0) options.samplerate = 4;
							break;
						case OPTION_FBA_VSYNC:
							options.vsync ^= 1;
							break;
						case OPTION_FBA_SHOWFPS:
							options.showfps ^= 1;
							break;
						case OPTION_FBA_68K:
							options.m68kcore--;
							if(options.m68kcore < 0) options.m68kcore = 2;
							break;
						case OPTION_FBA_Z80:
							options.z80core ^= 1;
							break;
						case OPTION_FBA_ANALOG:
							options.sense--;
							if(options.sense < 0) options.sense = 100;
							break;
					}
				} else if (event.key.keysym.sym == SDLK_RIGHT) {
					switch(run_options[run_num]) {
						case OPTION_FBA_SOUND:
							options.sound++;
							if(options.sound > 3) options.sound = 0;
							break;
						case OPTION_FBA_SAMPLERATE:
							options.samplerate++;
							if(options.samplerate >= 5) options.samplerate = 0;
							break;
						case OPTION_FBA_VSYNC:
							options.vsync ^= 1;
							break;
						case OPTION_FBA_SHOWFPS:
							options.showfps ^= 1;
							break;
						case OPTION_FBA_68K:
							options.m68kcore++;
							if(options.m68kcore > 2) options.m68kcore = 0;
							break;
						case OPTION_FBA_Z80:
							options.z80core ^= 1;
							break;
						case OPTION_FBA_ANALOG:
							options.sense++;
							if(options.sense > 100) options.sense = 0;
							break;
					}
				} else if (event.key.keysym.sym == SDLK_LCTRL) {
					save_lastsel();

					nBurnDrvActive = nBurnDrvSelect[0] = gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone)[sel.rom];
					ConfigGameSave();

					SDL_QuitSubSystem(SDL_INIT_VIDEO);

					// run emulator here
					RunEmulator(nBurnDrvActive);

					if(!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO)) {
						SDL_InitSubSystem(SDL_INIT_VIDEO);
					}

					screen2 = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
					SDL_ShowCursor(0);

					prep_bg();
					Quit = 1;
				} else if(event.key.keysym.sym == SDLK_LALT || event.key.keysym.sym == SDLK_ESCAPE) {
					prep_bg();
					Quit = 1;
				}
			}
			++compteur;
		} else if(event.type == SDL_KEYUP){
			compteur=0;// reinitialisation joystick
		}
	}

	nBurnDrvActive = gui_get_filtered_romsort(cfg.list, cfg.hardware, cfg.genre, cfg.clone)[sel.rom];
	ConfigGameSave();
}

int findfirst(int l, int s)
{
	l -= 32;

	int z=0;

	while(z < romlist.nb_list[cfg.list]) {
		if(ROMLIST(name, z)[0] == l) {
			s = z;
			z = romlist.nb_list[cfg.list];
		}
		z++;
	}

	if(s > romlist.nb_list[cfg.list] - 13) s = romlist.nb_list[cfg.list] - 13;
	return s;
}

void save_lastsel()
{
	FILE *fp;
	char filename[512];

	sprintf(filename, "%s/lastsel.cap", szAppConfigPath);
	fp = fopen(filename, "w");
	if(fp) {
		fwrite(&sel.rom, 1, sizeof(int), fp);
		fwrite(&sel.ofs, 1, sizeof(int), fp);
		fwrite(&sel.y, 1, sizeof(int), fp);
		fclose(fp);
	}
}

void load_lastsel()
{
	FILE *fp;
	char filename[512];

	sprintf(filename, "%s/lastsel.cap", szAppConfigPath);
	fp = fopen(filename, "r");
	if(fp) {
		fread(&sel.rom, 1, sizeof(int), fp);
		fread(&sel.ofs, 1, sizeof(int), fp);
		fread(&sel.y, 1, sizeof(int), fp);
		fclose(fp);
	}
	gui_validate_selection();
}

void gui_menu_main()
{
	int Quit;
	unsigned int zipnum;
	unsigned int y;
	unsigned int compteur = 0;

	sel.y = START_Y-1;
	sel.x=0;
	sel.rom = 0;
	sel.ofs = 0;

	load_lastsel();

	prep_bg_main();
	flag_preview = 0;
	load_preview(sel.rom);

	//load_cf();

	Quit = 0;
	while(!Quit) {
		affiche_BG();

		if (romlist.nb_list[cfg.list] != 0) {
			drawSprite(barre, gui_screen, 0, 0, 4, sel.y, 312, 10);
		}

		// show rom list
		zipnum = START_Y;
		if(romlist.nb_list[cfg.list] <= LINES_COUNT) {
			for(y = 0; y < romlist.nb_list[cfg.list]; ++y) {
				put_stringM(ROMLIST(name, y), // string
						START_X, // x
						zipnum, // y
						ROMLIST(longueur, y), // length
						ROMLIST(etat, y)); // color
				zipnum += LINE_HEIGHT;
			}
		} else {
			for(y = sel.ofs; y < sel.ofs + LINES_COUNT; ++y) {
				put_stringM(ROMLIST(name, y), 
						START_X, 
						zipnum, 
						ROMLIST(longueur, y), 
						ROMLIST(etat, y));
				zipnum += LINE_HEIGHT;
			}
		}

		redraw_screen();
		//SDL_Flip(gui_screen);

		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN) {
			if(compteur == 0 || (compteur > cfg.delayspeed && ((compteur & joy_speed[cfg.repeatspeed]) == 0))) {
				if((event.key.keysym.sym >= SDLK_a) && (event.key.keysym.sym <= SDLK_z) &&
					(romlist.nb_list[cfg.list] != 0)) {
					sel.rom = findfirst(event.key.keysym.sym,sel.rom);
					sel.ofs = sel.rom;
					sel.y = START_Y - 1;
				} else if(event.key.keysym.sym == SDLK_LSHIFT) { // X button
					// no need to increment compteur
					continue;
				} else if(event.key.keysym.sym == SDLK_TAB) { // page up
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// prev genre
							cfg.genre--;
							if (cfg.genre < 0) cfg.genre = NB_GENRES - 1;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] > LINES_COUNT) {
						sel.rom -= LINES_COUNT;
						if(sel.rom > LINES_COUNT_HALF) {
							sel.ofs = sel.rom - LINES_COUNT_HALF;
							sel.y = START_Y - 1 + LINES_COUNT_HALF * LINE_HEIGHT;
						} else {
							sel.ofs = sel.rom = 0;
							sel.y = START_Y - 1;
						}
					}
				} else if(event.key.keysym.sym == SDLK_BACKSPACE) { // page down
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// next genre
							cfg.genre = (cfg.genre + 1) % NB_GENRES;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] > LINES_COUNT) {
						sel.rom += LINES_COUNT;
						if(sel.rom < romlist.nb_list[cfg.list] - LINES_COUNT_HALF) {
							sel.ofs = sel.rom - LINES_COUNT_HALF;
							sel.y = START_Y - 1 + LINES_COUNT_HALF * LINE_HEIGHT;
						} else {
							sel.rom = romlist.nb_list[cfg.list] - 1;
							sel.ofs = sel.rom - (LINES_COUNT - 1);
							sel.y = START_Y - 1 + (LINES_COUNT - 1) * LINE_HEIGHT;
						}
					}
				} else if(event.key.keysym.sym == SDLK_DOWN) {
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// next filter
							cfg.list = (cfg.list + 1) % NB_FILTERS;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] == 0) {
					}
					// if in the end of list, reset to the beginning
					else if (sel.rom == romlist.nb_list[cfg.list] - 1 && compteur == 0) {
						sel.y = START_Y - 1;
						sel.rom = 0;
						sel.ofs = 0;
					} else {
						if (romlist.nb_list[cfg.list] < 14) { // if rom number in list < 14
								if (sel.rom < romlist.nb_list[cfg.list] - 1) {
									sel.y += LINE_HEIGHT;
									++sel.rom;
									if(compteur == 0) {
										load_preview(sel.rom);
									}
								}
						}else{
							if (sel.rom < LINES_COUNT_HALF || sel.ofs == (romlist.nb_list[cfg.list] - LINES_COUNT)) {
								if (sel.rom < (romlist.nb_list[cfg.list] - 1)) {
									sel.y += LINE_HEIGHT;
									++sel.rom;
									if(compteur == 0) {
										load_preview(sel.rom);
									}
								}
							} else {
								++sel.ofs;
								++sel.rom;
								if(compteur == 0) {
									load_preview(sel.rom);
								}
							}
						}
					}
				} else if(event.key.keysym.sym == SDLK_UP) {
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// prev filter
							cfg.list--;
							if (cfg.list < 0) cfg.list = NB_FILTERS - 1;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] == 0) {
					} else if (sel.rom == 0 && compteur == 0) {
						sel.rom = romlist.nb_list[cfg.list] - 1;
						if (romlist.nb_list[cfg.list] < LINES_COUNT) {
							sel.y = START_Y - 1 + ((romlist.nb_list[cfg.list] - 1) * LINE_HEIGHT);
							//sel.ofs = 0;
						} else {
							sel.y = START_Y - 1 + ((LINES_COUNT - 1) * LINE_HEIGHT);
							sel.ofs = romlist.nb_list[cfg.list] - LINES_COUNT;
						}
					} else {
						if(sel.rom > romlist.nb_list[cfg.list] - LINES_COUNT_HALF || sel.ofs == 0) {
							if(sel.rom > 0) {
								sel.y -= LINE_HEIGHT;
								--sel.rom;
								if(compteur == 0) {
									load_preview(sel.rom);
								}
							}
						} else {
							--sel.ofs;
							--sel.rom;
							if(compteur == 0) {
								load_preview(sel.rom);
							}
						}
					}
				} else if(event.key.keysym.sym == SDLK_LEFT) {
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// prev hardware
							cfg.hardware--;
							if (cfg.hardware < 0) cfg.hardware = NB_HARDWARES - 1;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] == 0) {
					} else if (sel.x > 0) {
						--sel.x;
					}
				} else if(event.key.keysym.sym == SDLK_RIGHT) {
					Uint8* keystate = SDL_GetKeyState(NULL);
					if (keystate[SDLK_LSHIFT]) {
						if (compteur == 0) {
							// next hardware
							cfg.hardware = (cfg.hardware + 1) % NB_HARDWARES;
							gui_reset_selection();
							prep_bg_main();
							gui_write_cfg();
						}
					} else if (romlist.nb_list[cfg.list] == 0) {
					} else if (sel.x < romlist.long_max - 53) {
						++sel.x;
					}

				} else if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_LALT) {
					if(ss_prg_credit()) Quit = 1;
				} else if(event.key.keysym.sym == SDLK_LCTRL){
					// executer l'emu
					if(romlist.nb_list[cfg.list] != 0 && ROMLIST(etat, sel.rom) != ROUGE) {
						ss_prog_run();
						prep_bg_main();

						// flush event queue
						while(SDL_PollEvent(&event));
						// simulate key unpress
						// important
						event.type = SDL_KEYUP;
						event.key.keysym.sym = SDLK_LCTRL;
						SDL_PushEvent(&event);
						compteur = 0;
						continue;
					}
				} else if(event.key.keysym.sym == SDLK_SPACE ){
					if(compteur == 0) ss_prg_help();
				} else if(event.key.keysym.sym == SDLK_RETURN ){
					ss_prg_options(OPTION_MAIN_FIRST, OPTION_MAIN_LAST);
				}
			}
			++compteur;
		} else if(event.type == SDL_KEYUP) {
			if(compteur) {
				load_preview(sel.rom);
			}
			compteur = 0; // reinitialisation joystick
		}
	}

	save_lastsel();
}

void GuiRun()
{
	// fill data with data
	gui_sort_romlist();

	screen2 = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	gui_screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0xf800, 0x07e0, 0x001f, 0x0000);

	SDL_ShowCursor(0);
	SDL_JoystickOpen(0);

	gui_load_cfg();
	init_title();

	gui_menu_main();

	exit_prog();
}

/*EOF*/
