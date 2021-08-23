/*
** Title Class File
*/

#include <jo/jo.h>
#include "title.h"

static int title_sprite_id = -1; // Takes sprite ID's 1-3 for the 3 frames
static int image1_sprite_id = 4;
static int image2_sprite_id = 5;
static int image3_sprite_id = 6;
static int image4_sprite_id = 7;
static int image5_sprite_id = 8;
static int text_sprite_id = 9;

int titleTimer = 0;
bool gameStarted = false;


// Tile sheet for the title logo
static jo_tile LogoTiles[] = {
    {TITLE_WIDTH * 0, 0, TITLE_WIDTH, TITLE_HEIGHT},
    {TITLE_WIDTH * 1, 0, TITLE_WIDTH, TITLE_HEIGHT},
    {TITLE_WIDTH * 2, 0, TITLE_WIDTH, TITLE_HEIGHT}
};


// Used to check if the title screen has finished loading so that the player can start the game
bool game_started(void){
	return gameStarted;
}


// Load the sprites that are used for the title screen
void load_title(void){
	
	// Used to calculate when the sprites should appear
	titleTimer = jo_get_ticks();
	
	// Animated title image
	int sprite_id;
	sprite_id = jo_sprite_add_tga_tileset("UI", "TITLE.TGA", JO_COLOR_RGB(0,0,255), LogoTiles, JO_TILE_COUNT(LogoTiles));
	title_sprite_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(LogoTiles), 3);
	
	jo_reset_sprite_anim(title_sprite_id);
	
	// Static title images
	image1_sprite_id = jo_sprite_add_tga("UI", "TITLE1.TGA", JO_COLOR_RGB(0,0,255));
	image2_sprite_id = jo_sprite_add_tga("UI", "TITLE2.TGA", JO_COLOR_RGB(0,0,255));
	image3_sprite_id = jo_sprite_add_tga("UI", "TITLE3.TGA", JO_COLOR_RGB(0,0,255));
	image4_sprite_id = jo_sprite_add_tga("UI", "TITLE4.TGA", JO_COLOR_RGB(0,0,255));
	image5_sprite_id = jo_sprite_add_tga("UI", "TITLE5.TGA", JO_COLOR_RGB(0,0,255));
	text_sprite_id = jo_sprite_add_tga("UI", "TEXT.TGA", JO_COLOR_Green);
}


// Unload the sprites from memory
void unload_title(void){
	jo_clear_screen();
	jo_sprite_free_from(title_sprite_id);
	jo_sprite_free_from(image1_sprite_id);
	jo_sprite_free_from(image2_sprite_id);
	jo_sprite_free_from(image3_sprite_id);
	jo_sprite_free_from(image4_sprite_id);
	jo_sprite_free_from(image5_sprite_id);
	jo_sprite_free_from(text_sprite_id);
}


// Display title screen images
inline void display_title(void){
	
	// Display the static logo image
	jo_sprite_draw3D2(jo_get_anim_sprite(title_sprite_id), 84, 22, 500);
	
	// After 2000 ticks have elapsed, this displays the first title image
	if (jo_get_ticks() > titleTimer +2000) {
		//jo_sprite_draw3D(image1_sprite_id, -122, -72, 400);
		jo_sprite_draw3D(image5_sprite_id, 98, -86, 400);
	}

	// After 3000 ticks have elapsed, this displays the second title image
	if (jo_get_ticks() > titleTimer +3000) {
		//jo_sprite_draw3D(image2_sprite_id, -106, 44, 400);
		jo_sprite_draw3D(image3_sprite_id, 26, 40, 400);
	}
	
	// After 4000 ticks have elapsed, this displays the third title image
	if (jo_get_ticks() > titleTimer +4000) {
		//jo_sprite_draw3D(image3_sprite_id, 26, 40, 400);
		jo_sprite_draw3D(image1_sprite_id, -122, -72, 400);
	}
	
	// After 5000 ticks have elapsed, this displays the fourth title image
	if (jo_get_ticks() > titleTimer +5000) {
		jo_sprite_draw3D(image4_sprite_id, 130, 0, 400);
	}
	
	// After 6000 ticks have elapsed, this displays the fifth title image
	if (jo_get_ticks() > titleTimer +6000) {
		//jo_sprite_draw3D(image5_sprite_id, 98, -86, 400);
		jo_sprite_draw3D(image2_sprite_id, -106, 44, 400);
	}
	
	// After 7000 ticks have elapsed, this displays the title text image
	if (jo_get_ticks() > titleTimer +7000) {
		jo_sprite_draw3D(text_sprite_id, 40, 90, 400);
	}
	
	// After 8000 ticks have elapsed, this starts the animation loop for the title
	if (jo_get_ticks() > titleTimer +8000) {
		if (jo_is_sprite_anim_stopped(title_sprite_id)){
			jo_start_sprite_anim_loop(title_sprite_id);
		}
		
		// Update the animation loop
		jo_sprite_draw3D2(jo_get_anim_sprite(title_sprite_id), 84, 22, 500);

		// Enable the user to start the game
		gameStarted = true;
	}
}


/*
** END OF FILE
*/