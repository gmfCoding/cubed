#ifndef CUBED_H
# define CUBED_H
# include <inttypes.h>

//#include "extra/optimised.h"
# include "texture.h"
# include "state.h"
# include "render.h"
# include "map.h"
# include "libft.h"
# include "get_next_line.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <errno.h>

# define SCR_WIDTH  960
# define SCR_HEIGHT 960

# define RT0_WIDTH SCR_WIDTH
# define RT0_HEIGHT SCR_HEIGHT

# define MAX_DEPTHS 5
# define MAX_TEX_BF 4



# define TARGET_FRAME_RATE 60.0
# define R_TFR TARGET_FRAME_RATE

typedef struct s_vec2f t_vec2f;
//typedef struct s_cellinfo t_cellinfo;

//typedef uint8_t t_cellheight;

/**
 * @param depth Distance from the normal plane
 * @param dist Distance from the start
 * @param minX The smallest height of the ray
 * @param minY The largest height of the ray
*/
typedef struct s_hitpoint t_hitpoint;
struct s_hitpoint
{
	float depth;
	float dist;
	float minX;
	float minY;
	int x;
	int y;
	int side;
};

typedef struct s_rayinfo t_rayinfo;
struct s_rayinfo
{
	t_hitpoint	depths[MAX_DEPTHS];
	uint8_t		hits;
};

typedef union u_texid t_texid;

union u_texid
{
	int8_t : MAX_TEX_BF;
};
/*
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
*/

/* util/time.c */
int64_t	time_get_ms(void);
#endif
