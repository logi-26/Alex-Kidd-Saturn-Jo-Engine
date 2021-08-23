// Pickup Class File

#include <jo/jo.h>
#include "pickup.h"

// Sprite ID for the pickup sprite
int pickup_sprite_id;

// Array of pickup items
pickup_t pickups[PICKUP_NUMBER];

// Tile sheet for the pickup item sprites
static jo_tile ItemTiles[] = {
    {PICKUP_WIDTH * 0, 0, PICKUP_WIDTH, PICKUP_HEIGHT}, // +0 Ring
    {PICKUP_WIDTH * 1, 0, PICKUP_WIDTH, PICKUP_HEIGHT}, // +1 Moneybag big
	{PICKUP_WIDTH * 2, 0, PICKUP_WIDTH, PICKUP_HEIGHT}, // +2 Moneybag small
	{PICKUP_WIDTH * 3, 0, PICKUP_WIDTH, PICKUP_HEIGHT}, // +3 Alex life
	{PICKUP_WIDTH * 4, 0, PICKUP_WIDTH, PICKUP_HEIGHT}  // +4 Level portal
};

// Load the pickup items
void load_pickup(){
	pickup_sprite_id = jo_sprite_add_tga_tileset("ITEMS", "PICKUP.TGA", JO_COLOR_Green, ItemTiles, JO_TILE_COUNT(ItemTiles));
}

// Unload the pickup item
void unload_pickup(void){

}

// Update the pickup item
void update_pickup(int pickup_number, int map_x, int map_y){
	
}

// Check for collisions between alex and the pickup item sprite
bool collision_with_pickup(int alex_id, int alex_x, int alex_y, int pickup_number){
	return jo_hitbox_detection(alex_id, alex_x, alex_y, pickup_sprite_id +pickups[pickup_number].type, pickups[pickup_number].x + 50, pickups[pickup_number].y + 10);
}

// Display the pickup item sprite
inline void display_pickup(int pickup_number, int map_x, int map_y){
	//jo_sprite_draw3D(pickup_sprite_id +pickups[pickup_number].type, pickups[pickup_number].x - map_x, pickups[pickup_number].y - map_y, 500);
	jo_sprite_draw3D(pickup_sprite_id +pickups[pickup_number].type, pickups[pickup_number].x - 100 - map_x, pickups[pickup_number].y - 100 - map_y, 100);
}

//END OF FILE