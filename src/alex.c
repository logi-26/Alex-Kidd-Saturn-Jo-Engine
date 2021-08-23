// Alex Class File

#include <jo/jo.h>
#include "alex.h"

alex_t player;
extern jo_sidescroller_physics_params physics;
static int alex_sprite_id = -1;

// Tile list for the alex tile sheet
static const jo_tile AlexTiles[] = {
    {ALEX_WIDTH * 0, ALEX_HEIGHT * 0, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 0, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 0, ALEX_WIDTH, ALEX_HEIGHT}, 
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 1, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 1, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 1, ALEX_WIDTH, ALEX_HEIGHT}, 
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 2, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 2, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 2, ALEX_WIDTH, ALEX_HEIGHT}, 
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 3, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 3, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 3, ALEX_WIDTH, ALEX_HEIGHT},
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 4, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 4, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 4, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 3, ALEX_HEIGHT * 4, ALEX_WIDTH, ALEX_HEIGHT},
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 5, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 5, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 5, ALEX_WIDTH, ALEX_HEIGHT}, {ALEX_WIDTH * 3, ALEX_HEIGHT * 5, ALEX_WIDTH, ALEX_HEIGHT},
	{ALEX_WIDTH * 0, ALEX_HEIGHT * 6, ALEX_WIDTH + ALEX_PUNCH_DISTANCE, ALEX_HEIGHT}, {ALEX_WIDTH * 1, ALEX_HEIGHT * 6, ALEX_WIDTH + ALEX_PUNCH_DISTANCE, ALEX_HEIGHT}, {ALEX_WIDTH * 2, ALEX_HEIGHT * 6, ALEX_WIDTH + ALEX_PUNCH_DISTANCE, ALEX_HEIGHT}
};



// Animation handler (Alex running)
inline void alex_running_animation_handler(void){
	
    int speed_step;

    if (jo_physics_is_standing(&physics)){
		
		// Restart the walking animation if it is not stopped
        if (!jo_is_sprite_anim_stopped(player.walking_anim_id)){jo_reset_sprite_anim(player.walking_anim_id);}     
    }
    else{
		
		// Start the walking animation if it is stopped
        if (jo_is_sprite_anim_stopped(player.walking_anim_id)){jo_start_sprite_anim_loop(player.walking_anim_id);}  
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
inline void display_alex(int current_ticks){
	
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
					jo_sprite_draw3D(alex_sprite_id + 3, player.x -150, player.y -109, 500);
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
					jo_sprite_draw3D(alex_sprite_id + 20, player.x -150, player.y -109, 500);
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
						
						
						if (current_ticks %2 == 0){
							jo_sprite_draw3D(alex_sprite_id +1, player.x -150, player.y -109, 500);
						}
						else {
							jo_sprite_draw3D(alex_sprite_id +2, player.x -150, player.y -109, 500);
						}
						
						//if (jo_is_sprite_anim_stopped(player.invincible_idle_anim_id)){
							//jo_start_sprite_anim_loop(player.invincible_idle_anim_id);
						//}
						
						//jo_set_sprite_anim_frame_rate(player.invincible_idle_anim_id, 3);
						//jo_sprite_draw3D2(jo_get_anim_sprite(player.invincible_idle_anim_id), player.x, player.y, 450);
						
						
						
						
					}
					else {
						jo_sprite_draw3D(alex_sprite_id, player.x -150, player.y -109, 500);
					}
				}
			}
		}
		else{			
			if (player.is_punching) {
				// Display Alex punch sprite
				jo_sprite_draw3D(alex_sprite_id + 20, player.x -150, player.y -109, 500);
			}
			else {
				// Display Alex jump sprite
				jo_sprite_draw3D(alex_sprite_id + 6, player.x -150, player.y -109, 500);
			}
		}
		
		if (player.flip_alex){jo_sprite_disable_horizontal_flip();}
	}
}


// Display Alex Death
inline void display_alex_death(void){
	
	// Start and draw the alex death animation
	if (jo_is_sprite_anim_stopped(player.death_anim_id)){jo_start_sprite_anim_loop(player.death_anim_id);}
	jo_sprite_draw3D2(jo_get_anim_sprite(player.death_anim_id), player.x, player.y, 450);
}


// Return the sprite ID for the player (alex)
int get_alex_sprite_id(void){
	return alex_sprite_id;
}


// Load Alex
void load_alex(void){
	
	// Create a sprite from the alex tile sheet
	alex_sprite_id = jo_sprite_add_tga_tileset("ALEX", "SHEET_2.TGA", JO_COLOR_Green, AlexTiles, JO_TILE_COUNT(AlexTiles));
	
	// Create the player walking animation from the Alex walking tile sheet
	player.walking_anim_id = jo_create_sprite_anim(alex_sprite_id +12, 4, 4);
	
	// Create the player death animation
	player.death_anim_id = jo_create_sprite_anim(alex_sprite_id +9, 3, 3);
	
	// Create the player invincible idle animation
	player.invincible_idle_anim_id = jo_create_sprite_anim(alex_sprite_id +1, 2, 2);

	// Create the player invincible punching animation
	player.invincible_punching_anim_id = jo_create_sprite_anim(alex_sprite_id +21, 2, 2);

	// Create the player invincible crouching animation from the CROUCH tile sheet
	player.invincible_crouching_anim_id = jo_create_sprite_anim(alex_sprite_id +4, 2, 2);
}


// Unload Alex
void unload_alex(void){
	// Clear the sprites from memory
	jo_sprite_free_from(alex_sprite_id);
	
	// Clear the sprite animations from memory
	jo_sprite_free_from(player.walking_anim_id);
	jo_sprite_free_from(player.death_anim_id);
	jo_sprite_free_from(player.invincible_idle_anim_id);
	jo_sprite_free_from(player.invincible_punching_anim_id);
	jo_sprite_free_from(player.invincible_crouching_anim_id);
}

// END OF FILE