#ifndef CUBED_H
# define CUBED_H
# include <inttypes.h>

//#include "extra/optimised.h"
# include "texture.h"
# include "render.h"

#define PI 3.141592653589

// define DEG2RAD PI / 180.0
# define DEG2RAD 0.01745329251993888888888888888889
# define RAD2DEG 57.2957795131

# define MAX_RAYCAST_DIST 100

typedef struct s_vec2f t_vec2f;
typedef struct s_cellinfo t_cellinfo;

typedef uint8_t t_cellheight;

typedef union u_texid t_texid;

union u_texid
{
	int8_t : MAX_TEX_BF;
};

struct s_cellinfo
{
	t_cellheight	height;

	t_texid			floor;	
	t_texid			roof;
	t_texid			north;
	t_texid			south;
	t_texid			east;
	t_texid			west;
};

struct s_map
{
	t_cellinfo	cells[MAP_MAX_X * MAP_MAX_Y];
	uint8_t		width;
	uint8_t		height;

};


/* util/time.c */
int64_t	time_get_ms(void);
#endif