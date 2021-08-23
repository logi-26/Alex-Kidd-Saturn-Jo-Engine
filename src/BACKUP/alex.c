/*
** Alex Class File
*/

#include <jo/jo.h>
#include "alex.h"


alex_t player;
extern jo_sidescroller_physics_params physics;


static int alex_sprite_id = -1;
static int alex_dead_sprite_id = -1;
static int alex_walking_sprite_id = -1;


static int alex_invincible_idle_sprite_id = -1;


static int alex_invincible_crouching_sprite_id = -1;
static int alex_invincible_punching_sprite_id = -1;



// Tile list for the static alex tile sheet (idle, jump, crouch, punch)
static const jo_tile StaticAlexTiles[] = {
    {ALEX_WIDTH * 0, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 1, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 2, 0, ALEX_WIDTH, ALEX_HEIGHT},
	{ALEX_WIDTH * 3, 0, ALEX_WIDTH + 8, ALEX_HEIGHT}
};

// Tile list for the dead alex tile sheet
static const jo_tile DeadAlexTiles[] = {
    {ALEX_WIDTH * 0, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 1, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 2, 0, ALEX_WIDTH, ALEX_HEIGHT}
};

// Tile list for the standard alex walking tile sheet
static const jo_tile WalkingAlexTiles[] = {
    {ALEX_WIDTH * 0, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 1, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 2, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 3, 0, ALEX_WIDTH, ALEX_HEIGHT},
};



// Tile list for the invincible alex idle tile sheet
static const jo_tile InvincibleAlexIdleTiles[] = {
    {ALEX_WIDTH * 0, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 1, 0, ALEX_WIDTH, ALEX_HEIGHT}
};


// Tile list for the invincible alex punching tile sheet
static const jo_tile InvincibleAlexPunchTiles[] = {
    {48 * 0, 0, 24, ALEX_HEIGHT},
    {48 * 1, 0, 24, ALEX_HEIGHT}
};

// Tile list for the invincible alex crouch tile sheet
static const jo_tile InvincibleAlexCrouchTiles[] = {
    {ALEX_WIDTH * 0, 0, ALEX_WIDTH, ALEX_HEIGHT},
    {ALEX_WIDTH * 1, 0, ALEX_WIDTH, ALEX_HEIGHT}
};






// Animation handler (Alex running)
inline void alex_running_animation_handler(void){
	
    int speed_step;

    if (jo_physics_is_standing(&physics)){
        if (!jo_is_sprite_anim_stopped(player.walking_anim_id)){
			jo_reset_sprite_anim(player.walking_anim_id);
		}     
    }
    else{
		
        if (jo_is_sprite_anim_stopped(player.walking_anim_id)){
			jo_start_sprite_anim_loop(player.walking_anim_id);
		}
            
        speed_step = (int)JO_ABS(physics.speed);
		
        if (speed_step >= 6){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 3);} 
        else if (speed_step >= 5){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 4);} 
        else if (speed_step >= 4){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 5);}
        else if (speed_step >= 3){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 6);}
        else if (speed_step >= 2){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 7);}  
        else if (speed_step >= 1){jo_set_sprite_anim_frame_rate(player.walking_anim_id, 8);}  
        else{jo_set_sprite_anim_frame_rate(player.walking_anim_id, 9);}     
    }
}






inline void alex_jump_animation_handler(void){
	jo_stop_sprite_anim	(player.walking_anim_id);	
}










// Display Alex
inline void display_alex(void){
	
	if (player.alive){
		if (player.flip_alex){jo_sprite_enable_horizontal_flip();}
       
		if (!physics.is_in_air){
			
			// Display Alex crouch sprite
			if (player.is_ducking) {
				
				if (player.invincible){
					if (jo_is_sprite_anim_stopped(player.invincible_crouching_anim_id)){
						jo_start_sprite_anim_loop(player.invincible_crouching_anim_id);
					}
					
					jo_set_sprite_anim_frame_rate(player.invincible_crouching_anim_id, 3);
					jo_sprite_draw3D2(jo_get_anim_sprite(player.invincible_crouching_anim_id), player.x, player.y, 450);
				}
				else {
					jo_sprite_draw3D(alex_sprite_id + 1, player.x -150, player.y -109, 500);
				}	
			}
			// Display Alex punch sprite
			else if (player.is_punching) {
				
				if (player.invincible){
					if (jo_is_sprite_anim_stopped(player.invincible_punching_anim_id)){
						jo_start_sprite_anim_loop(player.invincible_punching_anim_id);
					}
					
					jo_set_sprite_anim_frame_rate(player.invincible_punching_anim_id, 3);
					jo_sprite_draw3D2(jo_get_anim_sprite(player.invincible_punching_anim_id), player.x, player.y, 450);
				}
				else {
					jo_sprite_draw3D(alex_sprite_id + 3, player.x -150, player.y -109, 500);
				}
			}
			else {
				if (!jo_physics_is_standing(&physics)){
					// Display Alex walking animation
					jo_sprite_draw3D2(jo_get_anim_sprite(player.walking_anim_id), player.x, player.y, 450);
				}
				else{
					// Display Alex idle sprite
					if (player.invincible){
						if (jo_is_sprite_anim_stopped(player.invincible_idle_anim_id)){
							jo_start_sprite_anim_loop(player.invincible_idle_anim_id);
						}
						
						jo_set_sprite_anim_frame_rate(player.invincible_idle_anim_id, 3);
						jo_sprite_draw3D2(jo_get_anim_sprite(player.invincible_idle_anim_id), player.x, player.y, 450);
					}
					else {
						jo_sprite_draw3D(alex_sprite_id, player.x -150, player.y -109, 500);
					}
				}
			}
		}
		else{
			
			// Display Alex jump sprite
			jo_sprite_draw3D(alex_sprite_id + 2, player.x -150, player.y -109, 500);
		}
		
		if (player.flip_alex){jo_sprite_disable_horizontal_flip();}
	}
}







// Display Alex Death
inline void display_alex_death(void){
	
	if (jo_is_sprite_anim_stopped(player.death_anim_id)){
		jo_start_sprite_anim_loop(player.death_anim_id);
	}
	
	jo_sprite_draw3D2(jo_get_anim_sprite(player.death_anim_id), player.x, player.y, 450);
}



















int get_alex_sprite_id(void){
	return alex_sprite_id;
}






// Load Alex
void load_alex(void){
	
	// Create a sprite from the Alex walking tile sheet in the WALK.BIN file
    alex_walking_sprite_id = jo_sprite_add_tga_tileset("ALEX", "WALK.TGA", JO_COLOR_Green, WalkingAlexTiles, JO_TILE_COUNT(WalkingAlexTiles));
	
	// Create the player walking animation from the Alex walking tile sheet
	player.walking_anim_id = jo_create_sprite_anim(alex_walking_sprite_id, JO_TILE_COUNT(WalkingAlexTiles), 4);
    
	// Create a sprite from the alex static tile sheet
	alex_sprite_id = jo_sprite_add_tga_tileset("ALEX", "SHEET.TGA", JO_COLOR_Green, StaticAlexTiles, JO_TILE_COUNT(StaticAlexTiles));
	
	// Create a sprite from the alex dead tile sheet
	alex_dead_sprite_id = jo_sprite_add_tga_tileset("ALEX", "DEAD.TGA", JO_COLOR_Blue, DeadAlexTiles, JO_TILE_COUNT(DeadAlexTiles));
	
	// Create the player death animation from the DEAD tile sheet
	player.death_anim_id = jo_create_sprite_anim(alex_dead_sprite_id, JO_TILE_COUNT(DeadAlexTiles), 3);
	
	
	
	
	// Create a sprite from the alex invincible idle tile sheet
	alex_invincible_idle_sprite_id = jo_sprite_add_tga_tileset("ALEX", "IDLE.TGA", JO_COLOR_Green, InvincibleAlexIdleTiles, JO_TILE_COUNT(InvincibleAlexIdleTiles));
	
	// Create the player invincible idle animation from the IDLE tile sheet
	player.invincible_idle_anim_id = jo_create_sprite_anim(alex_invincible_idle_sprite_id, JO_TILE_COUNT(InvincibleAlexIdleTiles), 2);
	
	
	
	
	// Create a sprite from the alex invincible punching tile sheet
	alex_invincible_punching_sprite_id = jo_sprite_add_tga_tileset("ALEX", "PUNCH.TGA", JO_COLOR_Green, InvincibleAlexPunchTiles, JO_TILE_COUNT(InvincibleAlexPunchTiles));
	
	// Create the player invincible idle animation from the PUNCH tile sheet
	player.invincible_punching_anim_id = jo_create_sprite_anim(alex_invincible_punching_sprite_id, JO_TILE_COUNT(InvincibleAlexPunchTiles), 2);
	
	
	// Create a sprite from the alex invincible crouching tile sheet
	alex_invincible_crouching_sprite_id = jo_sprite_add_tga_tileset("ALEX", "CROUCH.TGA", JO_COLOR_Green, InvincibleAlexCrouchTiles, JO_TILE_COUNT(InvincibleAlexCrouchTiles));
	
	// Create the player invincible idle animation from the CROUCH tile sheet
	player.invincible_crouching_anim_id = jo_create_sprite_anim(alex_invincible_crouching_sprite_id, JO_TILE_COUNT(InvincibleAlexCrouchTiles), 2);
	
	
	
}





// Unload Alex
void unload_alex(void){
	// Clear the sprites from memory
	jo_sprite_free_from(alex_sprite_id);
	jo_sprite_free_from(alex_walking_sprite_id);
	jo_sprite_free_from(alex_dead_sprite_id);
	jo_sprite_free_from(alex_invincible_idle_sprite_id);

	jo_sprite_free_from(alex_invincible_crouching_sprite_id);
	jo_sprite_free_from(alex_invincible_punching_sprite_id);
	
	// Clear the sprite animations from memory
	jo_sprite_free_from(player.walking_anim_id);
	jo_sprite_free_from(player.death_anim_id);
	jo_sprite_free_from(player.invincible_idle_anim_id);
	jo_sprite_free_from(player.invincible_punching_anim_id);
	jo_sprite_free_from(player.invincible_crouching_anim_id);
}






/*
** END OF FILE
*/
