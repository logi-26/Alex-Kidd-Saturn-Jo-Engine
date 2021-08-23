// Pause Class File

#include <jo/jo.h>
#include "pause.h"

// Sprite ID's
static int map_image_sprite_id = -1;
static int pause_sprite_id = -1;

// Tile sheet for pause menu images
static jo_tile PauseTiles[] = {
    {16 * 0, 0, 16, 16}, // +0 Alex life
    {16 * 1, 0, 16, 16}, // +1 Moneybag
    {16 * 2, 0, 16, 16}, // +2 Ring
	{16 * 3, 0, 16, 16}, // +3 Blast
	{16 * 4, 0, 32, 8},  // +4 Score font
	{16 * 4, 8, 8, 8},   // +5 Down arrow
	{64 + 8, 8, 8, 8},   // +6 Up arrow
	{64 + 16, 8, 8, 8},  // +7 Left arrow
	{64 + 24, 8, 8, 8}   // +8 Right arrow
};

// Load the pause screen images
void load_pause(void){
	map_image_sprite_id = jo_sprite_add_tga("UI", "MAP.TGA", JO_COLOR_Black);
	pause_sprite_id = jo_sprite_add_tga_tileset("UI", "PAUSE.TGA", JO_COLOR_Green, PauseTiles, JO_TILE_COUNT(PauseTiles));	
}

// Unload the pause screen images
void unload_pause(void){
	jo_sprite_free_from(map_image_sprite_id);
	jo_sprite_free_from(pause_sprite_id);
}

// Display pause screen images
inline void display_pause(int alex_score, int alex_lives, int alex_money){
	jo_sprite_draw3D(map_image_sprite_id, 0, -50, 400);
	jo_sprite_draw3D(pause_sprite_id +1, -110, 48, 400);
	jo_sprite_draw3D(pause_sprite_id +0, -110, 81, 400);
	jo_sprite_draw3D(pause_sprite_id +3,  -40, 48, 400);
	jo_sprite_draw3D(pause_sprite_id +2,    0, 48, 400);
	jo_sprite_draw3D(pause_sprite_id +4,  -37, 82, 400);
	
	jo_sprite_draw3D(pause_sprite_id +5,  -43, -23, 100);
	jo_sprite_draw3D(pause_sprite_id +5,  0, 33, 100);
	
	jo_printf_with_color(8, 21, JO_COLOR_INDEX_Yellow, "%d", alex_money);
	jo_printf_with_color(8, 25, JO_COLOR_INDEX_Yellow, "%d", alex_lives);
	jo_printf_with_color(20, 25, JO_COLOR_INDEX_White, "%d", alex_score);
}

// END OF FILE