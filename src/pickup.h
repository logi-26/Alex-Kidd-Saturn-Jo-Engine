// Pickup Header File

#ifndef __PICKUP_H__
# define __PICKUP_H__
# define PICKUP_NUMBER (10)
# define PICKUP_WIDTH   (16)
# define PICKUP_HEIGHT  (16)

typedef struct{
	bool        visible;
	bool        collected;
	int         type;
    int         x;
    int         y;
} pickup_t;

extern pickup_t pickups[PICKUP_NUMBER];

void load_pickup(void);
void unload_pickup(void);
void update_pickup(int, int, int);
bool collision_with_pickup(int, int, int, int);
void display_pickup(int, int, int);

#endif

// END OF FILE