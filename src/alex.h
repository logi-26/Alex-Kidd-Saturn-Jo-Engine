// Alex Header File

#ifndef __ALEX_H__
# define __ALEX_H__

# define WORLD_MAP_ID		            (0)
# define WORLD_BACKGROUND_ID		    (1)

# define WORLD_DEFAULT_X                (50)
# define WORLD_DEFAULT_Y                (-50)

# define MAP_TILE_BLOCK_ATTR            (1)


# define ALEX_WIDTH                    (16)
# define ALEX_HEIGHT                   (24)

# define ALEX_WIDTH_HALF               (8)
# define ALEX_CROUCH_HEIGHT            (20)
# define ALEX_CROUCH_HEIGHT            (22)
# define ALEX_PUNCH_DISTANCE           (8)


/* If alex almost touches the ground we allow the user to jump */
# define ALEX_JUMP_PER_PIXEL_TOLERANCE (10)

typedef struct{
	bool 		alive;
	bool 		invincible;
	bool        flip_alex;
    bool        can_jump;
	bool        is_ducking;
	bool        is_punching;
	bool 		in_water;
	int         x;
    int         y;
	int         dead_x;
    int         dead_y;
	int 		lives;
	int 		score;
	int 		money;
	int 		invincible_start_time;
    int         walking_anim_id;
	int         death_anim_id;
	int         invincible_idle_anim_id;
	int         invincible_walking_anim_id;
	int         invincible_jumping_anim_id;
	int         invincible_crouching_anim_id;
	int         invincible_punching_anim_id;
}               alex_t;


extern alex_t player;





void            alex_running_animation_handling();
void 			alex_jump_animation_handler();
void            display_alex(int);
void            display_alex_death(void);
void            load_alex(void);
int             get_alex_sprite_id(void);

#endif /* !__ALEX_H__ */

/*
** END OF FILE
*/