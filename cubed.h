#include <inttypes.h>

#define MAX_DEPTHS 5
#define MAX_TEX_BF 4

#define MAP_MAX_XY 200
#define MAP_MAX_X MAP_MAX_XY
#define MAP_MAX_Y MAP_MAX_XY

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
	s_hitpoint	depths[MAX_DEPTHS];
	uint8_t		hits;
};

union u_texid
{
	int8_t : MAX_TEX_BF;
};

struct s_cellinfo
{
	t_cellheight	height;

	u_texid			floor;	
	u_texid			roof;
	u_texid			north;
	u_texid			south;
	u_texid			east;
	u_texid			west;
};

struct s_map
{
	t_cellinfo	cells[MAP_MAX_X * MAP_MAX_Y];
	uint8_t		width;
	uint8_t		height;

};