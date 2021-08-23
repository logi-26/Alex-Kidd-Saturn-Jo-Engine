// Title Class File

#include <jo/jo.h>
#include "title.h"

static int title_sprite_id = -1;  // Takes sprite ID's 1-3 for the 3 frames
static int image_sprite_id = -1;  // Takes sprite ID's 4-9 for the 6 single frame images

int titleTimer = 0;
bool gameStarted = false;

// Tile sheet for the title logo
static jo_tile LogoTiles[] = {
    {152 * 0, 96 * 0, 152, 96},
    {152 * 0, 96 * 1, 152, 96},
    {152 * 0, 96 * 2, 152, 96}
};

// Tile sheet for the UI images
static jo_tile TileTiles[] = {
    {0, 0, 80, 114},	
    {80, 0, 32, 87},	
    {112, 0, 104, 38},  
	{112, 38, 88, 43},  
	{216, 0, 40, 54},
	{80, 90, 112, 24}
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
	sprite_id = jo_sprite_add_tga_tileset("UI", "LOGO.TGA", JO_COLOR_Blue, LogoTiles, JO_TILE_COUNT(LogoTiles));
	title_sprite_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(LogoTiles), 3);
	jo_reset_sprite_anim(title_sprite_id);
	
	// Static title images
	image_sprite_id = jo_sprite_add_tga_tileset("UI", "TITLE.TGA", JO_COLOR_Green, TileTiles, JO_TILE_COUNT(TileTiles));
}

// Unload the sprites from memory
void unload_title(void){
	jo_clear_screen();
	jo_sprite_free_from(title_sprite_id);
	jo_sprite_free_from(image_sprite_id);
}

// Display title screen images
inline void display_title(void){
	
	// Display the static logo image
	jo_sprite_draw3D2(jo_get_anim_sprite(title_sprite_id), 84, 22, 500);
	
	if (jo_get_ticks() > titleTimer +2000) {jo_sprite_draw3D(image_sprite_id +3, 98, -86, 400);}	// After 2000 ticks have elapsed, this displays the first title image
	if (jo_get_ticks() > titleTimer +3000) {jo_sprite_draw3D(image_sprite_id +2, 30, 40, 400);}		// After 3000 ticks have elapsed, this displays the second title image
	if (jo_get_ticks() > titleTimer +4000) {jo_sprite_draw3D(image_sprite_id +4, -122, -72, 400);}	// After 4000 ticks have elapsed, this displays the third title image
	if (jo_get_ticks() > titleTimer +5000) {jo_sprite_draw3D(image_sprite_id +1, 126, 0, 400);}		// After 5000 ticks have elapsed, this displays the fourth title image
	if (jo_get_ticks() > titleTimer +6000) {jo_sprite_draw3D(image_sprite_id +0, -101, 44, 400);}   // After 6000 ticks have elapsed, this displays the fifth title image
	if (jo_get_ticks() > titleTimer +7000) {jo_sprite_draw3D(image_sprite_id +5, 40, 90, 400);}		// After 7000 ticks have elapsed, this displays the title text image
	
	// After 8000 ticks have elapsed, this starts the animation loop for the title logo
	if (jo_get_ticks() > titleTimer +8000) {
		
		// Start the title sprite animation if it is stopped
		if (jo_is_sprite_anim_stopped(title_sprite_id)){jo_start_sprite_anim_loop(title_sprite_id);}
		
		// Update the sprite animation loop
		jo_sprite_draw3D2(jo_get_anim_sprite(title_sprite_id), 84, 22, 500);

		// Enable the user to start the game
		gameStarted = true;
	}
}

// END OF FILE