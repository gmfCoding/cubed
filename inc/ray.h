#ifndef RAY_H
# define RAY_H

# include <inttypes.h>
# include "config.h"
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
#endif