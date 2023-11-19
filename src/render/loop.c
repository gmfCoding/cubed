#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

#include "input.h"
#include "cubed.h"
#include "texture.h"

#define PI 3.141592653589

// define DEG2RAD PI / 180.0
# define DEG2RAD 0.01745329251993888888888888888889

bool inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

# define MAP_WIDTH 6
# define MAP_HEIGHT 6
int map[] = 
{
	1,1,1,1,1,1,
	1,0,0,0,0,1,
	1,0,0,0,0,1,
	1,0,1,1,0,1,
	1,0,0,0,0,1,
	1,1,1,1,1,1,
};

int	map_index(int x, int y)
{
	return (x + y * MAP_WIDTH);
}

float	raycast(int *map, t_vec2 pos, float angle)
{
	float dX = cos(angle);
	float dY = sin(angle);
	float Sy = sqrt(1 + dX/dY * dX/dY);
	float Sx = sqrt(1 + dY/dX * dY/dX);

	t_vec2 trv = v2new(0,0);
	while (1)
	{
		float segX = sqrt((trv.x + 1) * (trv.x + 1) + (trv.y + 0) * (trv.y + 0)) * Sx;
		float segY = sqrt((trv.x + 0) * (trv.x + 0) + (trv.y + 1) * (trv.y + 1)) * Sy;
		if (segX < segY)
			trv.x++;
		else
			trv.y++;
		if (map[map_index(pos.x + trv.x, pos.y + trv.y)])
			return v2mag(trv);
	}
	return 100.0f;
}

t_vec2	screen_to_map(t_vec2 mouse)
{
	return (t_vec2){mouse.x / SCR_WIDTH * MAP_WIDTH, mouse.y / SCR_HEIGHT * MAP_HEIGHT};
}

t_vec2	map_to_screen(t_vec2 map)
{
	return (t_vec2){map.x / (float)MAP_WIDTH * SCR_WIDTH, map.y / (float)MAP_HEIGHT * SCR_HEIGHT};
}


void	on_mouse_move(int x, int y, t_game *game)
{
	game->mouse = v2new(x, y);
}

void	on_mouse(int key, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	t_vec2 coord = screen_to_map(game->mouse);
	if (key == MB_LEFT)
	{
		//float dist = raycast(map, start, angle * DEG2RAD);
		printf("(%d,%d) state: %d\n", (int)coord.x, (int)coord.y, map[map_index((int)coord.x, (int)coord.y)]);
	}
	printf("(%f,%f)\n", game->mouse.x, game->mouse.y);
}
#include "extra/optimised.h"

void	render(t_game *game)
{
	//static t_vec2 start = {0,0};
	static float angle = 0;

	//const int cell_width = SCR_WIDTH / MAP_WIDTH;
	//const int cell_height = SCR_HEIGHT / MAP_HEIGHT;

	while (angle < 360)
	{	
		angle += 1;
	}
	// {
	// 	int y = -1;
	// 	while (++y < RT0_HEIGHT)
	// 	{
	// 		int x = -1;
	// 		while (++x < RT0_WIDTH)
	// 		{
				
	// 		}
	// 	}
	// }
	{
		int y = -1;
		while (++y < RT0_HEIGHT)
		{
			int x = -1;
			while (++x < RT0_WIDTH)
			{
				PIXEL_SET(game->rt0, x, y, 0x000000);
				t_vec2 cell = screen_to_map(v2new(x ,y));
				if (map[map_index(cell.x, cell.y)])
				{
					PIXEL_SET(game->rt0, x, y, 0x0000ff);
				}
				else
					PIXEL_SET(game->rt0, x, y, 0x0);
			}
		}
	}
	// {
	// 	int y = -1;
	// 	while (++y < MAP_HEIGHT)
	// 	{
	// 		int x = -1;
	// 		while (++x < MAP_WIDTH)
	// 		{
	// 			t_vec2 cell = map_to_screen(v2new(x ,y));
	// 			if (map[map_index(x, y)])
	// 				texture_draw_square(game->rt0, cell, v2new(cell_width, cell_height), 0xff);
	// 			else
	// 				texture_draw_square(game->rt0, cell, v2new(cell_width, cell_height), 0x00);
	// 		}
	// 	}
	// }

	texture_draw_square(game->rt0, v2new(0,0), v2new(5, 5), 0xff);
	texture_draw_square(game->rt0, v2new(5,5), v2new(5, 5), 0xff);
	static int64_t timeprev = 0;
	// static int64_t time;
	// if (timeprev != 0)
	// 	time += time_get_ms() - timeprev;
	// if (time > 4 * 1000)
	// 	exit(0);
	printf("time:%ld\n", time_get_ms() - timeprev);
	printf("fps:%f\n", 1.0 / ((time_get_ms() - timeprev) / 1000.0));
	timeprev = time_get_ms();
	texture_draw_line(game->rt0, v2new(SCR_WIDTH/2,SCR_HEIGHT/2), game->mouse, 0xff);
	angle = 0;
	texture_draw(game, game->rt0, v2new(0,0));
}