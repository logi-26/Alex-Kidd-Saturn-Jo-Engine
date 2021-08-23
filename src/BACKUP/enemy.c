// Enemy Class File

#include <jo/jo.h>
#include "enemy.h"

// Sprite ID's for the enemy sprite regular and death sprites
int sprite_id;
int enemy_sprite_id;
int enemy_death_sprite_id;

// Array of enemies
enemy_t enemies[ENEMY_NUMBER];


// Tile sheet for the animated enemy sprite (only 2 frames)
static jo_tile EnemyTiles[] = {
    {ENEMY_WIDTH * 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT},
    {ENEMY_WIDTH * 1, 0, ENEMY_WIDTH, ENEMY_HEIGHT}
};

// Tile sheet for the animated enemy sprite death (smoke cloud)
static jo_tile EnemyDeathTiles[] = {
    {24 * 0, 0, 24, 32},
    {24 * 1, 0, 24, 32}
};


// Load the enemy
void load_enemy(){

	// Load the sprite sheet for the enemy into a new animated sprite object
	sprite_id = jo_sprite_add_tga_tileset("ENEMIES", "BIRD.TGA", JO_COLOR_RGB(0,0,255), EnemyTiles, JO_TILE_COUNT(EnemyTiles));
	enemy_sprite_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(EnemyTiles), 2);
	jo_reset_sprite_anim(enemy_sprite_id);
	jo_set_sprite_anim_frame_rate(enemy_sprite_id, 40);		
	
	// Load the sprite sheet for the enemy death into a new animated sprite object
	//sprite_id = jo_sprite_add_tga_tileset("ENEMIES", "DEATH.TGA", JO_COLOR_RGB(0,0,255), EnemyDeathTiles, JO_TILE_COUNT(EnemyDeathTiles));
	//enemy_death_sprite_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(EnemyDeathTiles), 2);
	//jo_reset_sprite_anim(enemy_death_sprite_id);
	//jo_set_sprite_anim_frame_rate(enemy_death_sprite_id, 1);	
}


// Unload the enemy
void unload_enemy(void){
	jo_sprite_free_from(sprite_id);
	jo_sprite_free_from(enemy_sprite_id);
	jo_sprite_free_from(enemy_death_sprite_id);
}


// Check for collisions between alex and the enemy sprite
bool collision_with_enemy(int alex_id, int alex_x, int alex_y, int enemy_number){
	return jo_hitbox_detection(alex_id, alex_x, alex_y, enemy_sprite_id, enemies[enemy_number].x, enemies[enemy_number].y);
}


// Update the enemy
void update_enemy(int enemy_number, int map_x, int map_y){
	
	// Move enemy right
	if (enemies[enemy_number].direction == 1 && enemies[enemy_number].x <= enemies[enemy_number].start_x + enemies[enemy_number].distance){
		enemies[enemy_number].x++;
	} 
	else if (enemies[enemy_number].direction == 1 && enemies[enemy_number].x > enemies[enemy_number].start_x + enemies[enemy_number].distance){
		enemies[enemy_number].direction = 0;
	}
	
	// Move enemy left
	if (enemies[enemy_number].direction == 0 && enemies[enemy_number].x >= enemies[enemy_number].start_x){
		enemies[enemy_number].x--;
	} 
	else if (enemies[enemy_number].direction == 0 && enemies[enemy_number].x < enemies[enemy_number].start_x){
		enemies[enemy_number].direction = 1;
	}
}


// Display the animated enemy sprite
inline void display_enemy(int enemy_number, int map_x, int map_y){
	
	if (enemies[enemy_number].alive) {
		if (jo_is_sprite_anim_stopped(enemy_sprite_id)){
			jo_start_sprite_anim_loop(enemy_sprite_id);
		}
		
		// Update the animation loop
		if (enemies[enemy_number].direction == 0){jo_sprite_enable_horizontal_flip();}
		jo_sprite_draw3D2(jo_get_anim_sprite(enemy_sprite_id), enemies[enemy_number].x - map_x, enemies[enemy_number].y - map_y, 500);
		if (enemies[enemy_number].direction == 0){jo_sprite_disable_horizontal_flip();}
	}
}


// Display the animated dead enemy sprite
inline void display_enemy_death(int enemy_number, int map_x, int map_y){
	enemies[enemy_number].recently_died = false;
	jo_start_sprite_anim_loop(enemy_death_sprite_id);
	jo_sprite_draw3D2(jo_get_anim_sprite(enemy_death_sprite_id), enemies[enemy_number].x - map_x, enemies[enemy_number].y - map_y, 500);
	
}

//END OF FILE