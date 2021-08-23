/*
** Pause Class File
*/

#include <jo/jo.h>
#include "pause.h"


static int map_image_sprite_id = 100;
static int money_sprite_id = 101;
static int life_sprite_id = 102;
static int blast_sprite_id = 103;
static int ring_sprite_id = 104;


// Load the pause screen images
void load_pause(void){
	map_image_sprite_id = jo_sprite_add_tga("UI", "MAP.TGA", JO_COLOR_Black);
	money_sprite_id = jo_sprite_add_tga("UI", "MBAG.TGA", JO_COLOR_Green);
	life_sprite_id = jo_sprite_add_tga("UI", "LIFE.TGA", JO_COLOR_Green);
	blast_sprite_id = jo_sprite_add_tga("UI", "BLST.TGA", JO_COLOR_Green);
	ring_sprite_id = jo_sprite_add_tga("UI", "RING.TGA", JO_COLOR_Green);
}


// Unload the pause screen images
void unload_pause(void){
	jo_sprite_free_from(map_image_sprite_id);
	jo_sprite_free_from(money_sprite_id);
	jo_sprite_free_from(life_sprite_id);
	jo_sprite_free_from(blast_sprite_id);
	jo_sprite_free_from(ring_sprite_id);
}


// Display pause screen images
inline void display_pause(void){
	jo_sprite_draw3D(map_image_sprite_id, 0, -50, 400);
	
	jo_sprite_draw3D(money_sprite_id, -110, 50, 400);
	jo_sprite_draw3D(life_sprite_id,  -110, 80, 400);
	jo_sprite_draw3D(blast_sprite_id,  -40, 50, 400);
	jo_sprite_draw3D(ring_sprite_id,     0, 50, 400);
}


/*
** END OF FILE
*/