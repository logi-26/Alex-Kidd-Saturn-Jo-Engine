/*
** Enemy Header File
*/

#ifndef __ENEMY_H__
# define __ENEMY_H__

# define ENEMY_WIDTH                    (24)
# define ENEMY_HEIGHT                   (16)

# define ENEMY_NUMBER                   (12)


typedef struct{
	bool        alive;
	bool        recently_died;
    int         x;
    int         y;
	int         start_x;
    int         distance;
    int         direction;
}        enemy_t;

extern enemy_t enemies[ENEMY_NUMBER];




void load_enemy();
void unload_enemy(void);
void update_enemy(int, int, int);
bool collision_with_enemy(int, int, int, int);
void display_enemy(int, int, int);
void display_enemy_death(int, int, int);

#endif /* !__ENEMY_H__ */

/*
** END OF FILE
*/