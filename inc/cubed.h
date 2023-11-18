#ifndef CUBED_H
# define CUBED_H
# include <inttypes.h>

# include "texture.h"
# include "state.h"
# include "render_utils.h"

# define RES_WIDTH 1280
# define RES_HEIGHT 720

# define MAX_DEPTHS 5
# define MAX_TEX_BF 4

# define MAP_MAX_XY 200
# define MAP_MAX_X MAP_MAX_XY
# define MAP_MAX_Y MAP_MAX_XY

typedef struct s_vec2f t_vec2f;
typedef struct s_hitpoint t_hitpoint;
typedef struct s_cellinfo t_cellinfo;

typedef uint8_t t_cellheight;

struct s_vec2f
{
	float	x;
	float	y;
};

struct s_hitpoint
{
	float depth;
	float minX;
	float minY;
};

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
#endif