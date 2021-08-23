// Block Header File

#ifndef __BLOCK_H__
# define __BLOCK_H__
# define BLOCK_NUMBER     (50)
# define BLOCK_WIDTH      (16)
# define BLOCK_HEIGHT     (16)
# define FRAGMENT_WIDTH   (8)
# define FRAGMENT_HEIGHT  (8)

typedef struct{
	bool       drop_item;
	int	   	   drop_item_number;
	bool	   broken;
	int		   broken_spread_distance;
	int        type;
    int         x;
    int         y;
} block_t;

extern block_t blocks[BLOCK_NUMBER];

void load_block(void);
void unload_block(void);
bool collision_with_block(int, int, int, int);
void display_block(int, int, int);
int get_block_sprite_id(int);

#endif /* !__BLOCK_H__ */

// END OF FILE