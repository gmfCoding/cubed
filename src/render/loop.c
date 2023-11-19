#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>

#include "input.h"
#include "cubed.h"
#include "texture.h"
#include "vector2i.h"

#define PI 3.141592653589

// define DEG2RAD PI / 180.0
# define DEG2RAD 0.01745329251993888888888888888889
# define MAX_RAYCAST_DIST 100
void measure_frame_rate()
{
	static int64_t timeprev = 0;
	// AUTO EXIT AFTER 4 SECONDS (used for GMON)
	// static int64_t time;
	// if (timeprev != 0)
	// 	time += time_get_ms() - timeprev;
	// if (time > 4 * 1000)
	// 	exit(0);
	printf("fps:%f\n", 1.0 / ((time_get_ms() - timeprev) / 1000.0));
	timeprev = time_get_ms();
}

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

float	raycast(int *map, t_vec2 rayStart, t_vec2 rayDir)
{
	t_vec2 stepSize = {sqrt(1 + rayDir.y / rayDir.x * rayDir.y / rayDir.x), sqrt(1 + rayDir.x / rayDir.y * rayDir.x / rayDir.y)};
	t_vec2i mapCheck = (t_vec2i){rayStart.x, rayStart.y};
	t_vec2 rayLen = v2new(0,0);
	t_vec2i step;
	float dist;
	
	if (rayDir.x < 0)
	{
		step.x = -1;
		rayLen.x = (rayStart.x  - (float)mapCheck.x) * stepSize.x;
	}
	else
	{
		step.x = 1;
		rayLen.x = ((float)(mapCheck.x + 1) - rayStart.x) * stepSize.x;
	}

	if (rayDir.y < 0)
	{
		step.y = -1;
		rayLen.y = (rayStart.y  - (float)mapCheck.y) * stepSize.y;
	}
	else
	{
		step.y = 1;
		rayLen.y = ((float)(mapCheck.y + 1) - rayStart.y) * stepSize.y;
	}
	dist = 0.0;
	while (dist < MAX_RAYCAST_DIST)
	{
		if (rayLen.x < rayLen.y)
		{
			mapCheck.x += step.x;
			dist = rayLen.x;
			rayLen.x += stepSize.x;
		}
		else
		{
			mapCheck.y += step.y;
			dist = rayLen.y;
			rayLen.y += stepSize.y;
		}
		if (!inside(mapCheck.x, mapCheck.y, MAP_WIDTH, MAP_HEIGHT))
			break;
		if (map[map_index(mapCheck.x, mapCheck.y)] > 0)
			break;
	}
	return dist;
	/*
	while (1)
	{
		float segX = sqrt((rayLen.x + 1) * (rayLen.x + 1) + (rayLen.y + 0) * (rayLen.y + 0)) * stepSize.x;
		float segY = sqrt((rayLen.x + 0) * (rayLen.x + 0) + (rayLen.y + 1) * (rayLen.y + 1)) * stepSize.y;
		if (segX < segY)
			rayLen.x++;
		else
			rayLen.y++;
		if (!inside(rayStart.x + rayLen.x, rayStart.y + rayLen.y, MAP_WIDTH, MAP_HEIGHT))
			break;
		if (map[map_index(rayStart.x + rayLen.x, rayStart.y + rayLen.y)])
			return v2mag(rayLen);
	}
	*/
	return 100.0f;
}

t_vec2	screen_to_map(t_vec2 mouse)
{
	return (t_vec2){mouse.x / SCR_WIDTH * MAP_WIDTH, mouse.y / SCR_HEIGHT * MAP_HEIGHT};
}

t_vec2	map_to_screen(t_vec2 map)
{
	return (t_vec2){map.x * SCR_WIDTH / (float)MAP_WIDTH, map.y * SCR_HEIGHT / (float)MAP_HEIGHT};
}

static float angle = 0;

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
		game->debug = 1;
		float dist = raycast(map, game->pos, coord);
		t_vec2 dir = v2new(cos(angle * DEG2RAD) * dist, sin(angle * DEG2RAD) * dist);
		t_vec2 hit = v2add(coord, dir);
		map[map_index(hit.x, hit.y)] = 0xff0000;
		//float dist = raycast(map, start, angle * DEG2RAD);
		printf("(%d,%d) state: %d\n", (int)coord.x, (int)coord.y, map[map_index((int)coord.x, (int)coord.y)]);
	}
	printf("(%f,%f)\n", game->mouse.x, game->mouse.y);
}

void	on_key_press(int key, t_game *game)
{
	if (key == KEY_A)
		game->pos.x -= 0.05;
	if (key == KEY_D)
		game->pos.x += 0.05;
	if (key == KEY_W)
		game->pos.y -= 0.05;
	if (key == KEY_S)
		game->pos.y += 0.05;
}

void	render(t_game *game)
{
	//static t_vec2 start = {0,0};

	static bool init = false;
	if (!init)
	{
		int y = -1;
		while (++y < MAP_HEIGHT)
		{
			int x = -1;
			while (++x < MAP_WIDTH)
			{
				if (map[map_index(x, y)])
					map[map_index(x, y)] = 0xff;
			}
		}
		init = 1;
	}

	const int cell_width = SCR_WIDTH / MAP_WIDTH;
	const int cell_height = SCR_HEIGHT / MAP_HEIGHT;

	// while (angle < 360)
	// {	
	// 	angle += 1;
	// }
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
	// {
	// 	int y = -1;
	// 	while (++y < RT0_HEIGHT)
	// 	{
	// 		int x = -1;
	// 		while (++x < RT0_WIDTH)
	// 		{
	// 			PIXEL_SET(game->rt0, x, y, 0x000000);
	// 			t_vec2 cell = screen_to_map(v2new(x ,y));
	// 			if (map[map_index(cell.x, cell.y)])
	// 			{
	// 				PIXEL_SET(game->rt0, x, y, 0x0000ff);
	// 			}
	// 			else
	// 				PIXEL_SET(game->rt0, x, y, 0x0);
	// 		}
	// 	}
	// }
	{
		int y = -1;
		while (++y < MAP_HEIGHT)
		{
			int x = -1;
			while (++x < MAP_WIDTH)
			{
				t_vec2 cell = map_to_screen(v2new(x ,y));
				if (map[map_index(x, y)] > 0)
					texture_draw_square(game->rt0, cell, v2new(cell_width, cell_height), map[map_index(x, y)]);
				else
					texture_draw_square(game->rt0, cell, v2new(cell_width, cell_height), 0x00);
			}
		}
	}

	angle += 0.1f;
	t_vec2 mcoord = screen_to_map(game->mouse);
	if (game->debug)
		game->debug = 0;
	t_vec2 rayDir = v2norm(v2sub(mcoord, game->pos));
	float dist = raycast(map, game->pos, rayDir);
	t_vec2 dir = v2new(cos(angle * DEG2RAD) * dist, sin(angle * DEG2RAD) * dist);
	t_vec2 hit = v2add(mcoord, dir);

	t_vec2 intersect = v2add(game->pos, v2muls(rayDir, dist));

	texture_draw_line(game->rt0, game->mouse, map_to_screen(game->pos), 0xff0000);
	texture_draw_square(game->rt0, map_to_screen(game->pos), v2new(5,5), 0xff0000);
	texture_draw_square(game->rt0, map_to_screen(intersect), v2new(5,5), 0xff0000);
	texture_draw(game, game->rt0, v2new(0,0));
	//measure_frame_rate();
}