// Block Class File

#include <jo/jo.h>
#include "block.h"
#include "pickup.h"

// Sprite ID for the block sprite
static int block_sprite_id = -1;
static int broken_block_sprite_id = -1;

// Array of blocks
block_t blocks[BLOCK_NUMBER];

// Tile sheet for the brick and boulder sprites
static jo_tile BlockTiles[] = {
    {BLOCK_WIDTH * 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT}, // +0 Star brick
    {BLOCK_WIDTH * 1, 0, BLOCK_WIDTH, BLOCK_HEIGHT}, // +1 Question brick
	{BLOCK_WIDTH * 2, 0, BLOCK_WIDTH, BLOCK_HEIGHT}, // +2 Skull brick
	{BLOCK_WIDTH * 3, 0, BLOCK_WIDTH, BLOCK_HEIGHT}, // +3 Pink skull brick
	{BLOCK_WIDTH * 4, 0, BLOCK_WIDTH, BLOCK_HEIGHT}, // +4 Brown boulder
	{BLOCK_WIDTH * 5, 0, BLOCK_WIDTH, BLOCK_HEIGHT}  // +5 Green boulder
};

// Tile sheet for the brick and boulder fragment sprites
static jo_tile BrokenBlockTiles[] = {
    {FRAGMENT_WIDTH * 0, 24, FRAGMENT_WIDTH, FRAGMENT_HEIGHT}, 
    {FRAGMENT_WIDTH * 1, 24, FRAGMENT_WIDTH, FRAGMENT_HEIGHT},
	{FRAGMENT_WIDTH * 2, 24, FRAGMENT_WIDTH, FRAGMENT_HEIGHT},
	{FRAGMENT_WIDTH * 3, 24, FRAGMENT_WIDTH, FRAGMENT_HEIGHT}
};

// Load the block
void load_block(){
	block_sprite_id = jo_sprite_add_tga_tileset("ITEMS", "BLOCKS.TGA", JO_COLOR_Blue, BlockTiles, JO_TILE_COUNT(BlockTiles));
	broken_block_sprite_id = jo_sprite_add_tga_tileset("UI", "BLAST.TGA", JO_COLOR_Blue, BrokenBlockTiles, JO_TILE_COUNT(BrokenBlockTiles));	
}

// Unload the block
void unload_block(void){

}

// Return the sprite ID for the block 
int get_block_sprite_id(int block_number){
	return block_sprite_id +blocks[block_number].type;
}

// Display the block sprite
inline void display_block(int block_number, int map_x, int map_y){

	// Display the block
	if (!blocks[block_number].broken){
		jo_sprite_draw3D(block_sprite_id +blocks[block_number].type, blocks[block_number].x - 100 - map_x, blocks[block_number].y - 100 - map_y, 100);
	}
	else {
		
		// Display the block fragments and update their position until they are off screen
		if (blocks[block_number].y < map_y +300){
			blocks[block_number].broken_spread_distance += 1;
			blocks[block_number].y += 1;
			jo_sprite_draw3D(broken_block_sprite_id, blocks[block_number].x - 104 - map_x - blocks[block_number].broken_spread_distance, blocks[block_number].y - 104 - map_y, 100);
			jo_sprite_draw3D(broken_block_sprite_id +2, blocks[block_number].x - 104 - map_x - blocks[block_number].broken_spread_distance, blocks[block_number].y - 96 - map_y + blocks[block_number].broken_spread_distance, 100);
			jo_sprite_draw3D(broken_block_sprite_id +1, blocks[block_number].x - 96 - map_x + blocks[block_number].broken_spread_distance, blocks[block_number].y - 104 - map_y, 100);
			jo_sprite_draw3D(broken_block_sprite_id +3, blocks[block_number].x - 96 - map_x + blocks[block_number].broken_spread_distance, blocks[block_number].y - 96 - map_y + blocks[block_number].broken_spread_distance, 100);
		}
		
		// Drop the item from the blcok
		if (blocks[block_number].drop_item){
			pickups[blocks[block_number].drop_item_number].visible = true;
		}
	}
}

//END OF FILE