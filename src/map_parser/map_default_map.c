#include "map.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int map[MAP_WIDTH * MAP_HEIGHT] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int	texmap[MAP_WIDTH * MAP_HEIGHT] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 6, 0, 6, 4, 0, 0, 0, 6, 0, 6, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 4, 0, 0, 0, 0, 5, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 4, 0, 0, 0, 6, 0, 6, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 5, 5, 5, 0, 5, 5, 5, 6, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 6, 0, 6, 4, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 6, 0, 6, 4, 4, 0, 4, 4, 4, 4, 4, 1,
	1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 6, 0, 6, 6, 6, 0, 6, 6, 6, 6, 6, 1,
	1, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 6, 0, 6, 6, 6, 6, 6, 0, 6, 6, 6, 1,
	1, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 5, 6, 0, 6, 2, 2, 2, 2, 0, 2, 2, 2, 1,
	1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 6, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 5, 5, 5, 0, 5, 5, 5, 6, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 7, 0, 0, 7, 7, 7, 7, 0, 7, 7, 7, 6, 0, 6, 2, 0, 5, 0, 5, 0, 5, 0, 1,
	1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 6, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 0, 6, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 6, 0, 6, 2, 2, 2, 2, 0, 2, 2, 2, 1,
	1, 0, 0, 0, 0, 7, 7, 0, 7, 0, 7, 7, 6, 0, 6, 3, 0, 0, 2, 0, 2, 0, 0, 1,
	1, 0, 0, 0, 0, 7, 7, 0, 7, 0, 7, 7, 6, 0, 6, 3, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 7, 7, 0, 7, 0, 7, 7, 6, 0, 6, 3, 0, 0, 2, 0, 2, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};


void map_default_map_init(t_world *world)
{
	int	x;
	int	y;
	world->map.width = MAP_WIDTH;
	world->map.height = MAP_HEIGHT;
	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			world->map.tiles[x + y * MAP_WIDTH].type = map[x + y * MAP_WIDTH] > 0;
			world->map.tiles[x + y * MAP_WIDTH].vis = map[x + y * MAP_WIDTH] > 1;
			world->map.tiles[x + y * MAP_WIDTH].tex = texmap[x + y * MAP_WIDTH] - 1;
		}
	}
	world->player.pos = v2new(22, 11.5);
	world->player.dir = v2new(-1, 0);
	world->player.plane = v2new(0, -0.5);
	world->player.moveSpeed = 1 / R_TFR * 2.0; // the constant value is in squares/second
	world->player.rotSpeed = -1 / R_TFR * 2.0;  // the constant value is in radians/second
}