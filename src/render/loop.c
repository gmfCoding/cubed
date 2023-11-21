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
# define RAD2DEG 57.2957795131

#define R_ALPHA 0xff000000
#define R_RED   0x00ff0000
#define R_GREEN 0x0000ff00
#define R_BLUE  0x000000ff

#define OF_ALPHA 24
#define OF_RED   16
#define OF_GREEN 8
#define OF_BLUE  0

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

typedef struct s_dda t_dda;
struct s_dda
{
	t_vec2 delta;
	t_vec2i check;
	t_vec2i step;
	t_vec2 side;
};

//t_vec2 stepSize = {sqrt(1 + rayDir.y / rayDir.x * rayDir.y / rayDir.x), sqrt(1 + rayDir.x / rayDir.y * rayDir.x / rayDir.y)};


t_rayinfo raycast(int *map, t_vec2 start, t_vec2 dir)
{
	t_rayinfo	ray = {0};
	t_dda		dda = {0};
	int			side;
	float		dist;

	dist = 0;
	side = 0;
	dda.check = (t_vec2i){start.x, start.y};
	dda.delta.x = 1e30;
	if (dda.delta.x != 0)
		dda.delta.x =  fabs(1.0 / dir.x);
	dda.delta.y = 1e30;
	if (dda.delta.y != 0)
		dda.delta.y =  fabs(1.0 / dir.y);
	//dda.delta = (t_vec2){sqrt(1 + dir.y / dir.x * dir.y / dir.x), sqrt(1 + dir.x / dir.y * dir.x / dir.y)};
	if (dir.x < 0)
	{
		dda.step.x = -1;
		dda.side.x = (start.x - dda.check.x) * dda.delta.x;
	}
	else
	{
		dda.step.x = 1;
		dda.side.x = (dda.check.x + 1.0 - start.x) * dda.delta.x;
	}
	if (dir.y < 0)
	{
		dda.step.y = -1;
		dda.side.y = (start.y - dda.check.y) * dda.delta.y;
	}
	else
	{
		dda.step.y = 1;
		dda.side.y = (dda.check.y + 1.0 - start.y) * dda.delta.y;
	}
	while (dist < MAX_RAYCAST_DIST)
	{
		if (dda.side.x < dda.side.y)
		{
			dda.side.x += dda.delta.x;
			dda.check.x += dda.step.x;
			dist = dda.side.x;
			side = 0;
		}
		else
		{
			dda.side.y += dda.delta.y;
			dda.check.y += dda.step.y;
			dist = dda.side.y;
			side = 1;
		}
		if (!inside(dda.check.x, dda.check.y, MAP_WIDTH, MAP_HEIGHT))
			break;
		if (map[map_index(dda.check.x, dda.check.y)] > 0)
		{
			t_hitpoint hit = {0};
			if (side == 0)
				hit = (t_hitpoint) {.depth = (dda.side.x - dda.delta.x), .dist = dda.side.x, .side = side};
			else
				hit = (t_hitpoint) {.depth = (dda.side.y - dda.delta.y), .dist = dda.side.y, .side = side};
			ray.depths[ray.hits++] = hit;
			break;
		}
	}
	return ray;
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
	return 100.0f;
	*/
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
	if (key == KEY_F)
	{
		game->debug = 1;
		t_rayinfo ray = raycast(map, game->pos, coord);
		t_vec2 dir = v2new(cos(angle * DEG2RAD) * ray.depths[0].dist, sin(angle * DEG2RAD) * ray.depths[0].dist);
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
	texture_clear(game->rt0);

	//static t_vec2 start = {0,0};
	static bool init = false;
	static t_texture overlay;
	if (!init)
	{
		overlay = texture_create(game->mlx, game->rt0.width, game->rt0.height);
		game->pos = (t_vec2){1,1};
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
	texture_clear(overlay);

	const int cell_width = SCR_WIDTH / MAP_WIDTH;
	const int cell_height = SCR_HEIGHT / MAP_HEIGHT;

	// angle += 0.1f;
	// if (game->debug)
	// 	game->debug = 0;

	// float dist = raycast(map, game->pos, rayDir);
	// t_vec2 dir = v2new(cos(angle * DEG2RAD) * dist, sin(angle * DEG2RAD) * dist);
	// t_vec2 hit = v2add(mcoord, dir);
	// t_vec2 intersect = v2add(game->pos, v2muls(rayDir, dist));
	t_vec2 mcoord = screen_to_map(game->mouse);
	t_vec2 pDir = v2norm(v2sub(mcoord, game->pos));
	angle = acos(pDir.y / sqrt(pDir.x * pDir.x + pDir.y * pDir.y));

	float dot = 1*pDir.x + 0*pDir.y;     // dot product
	float det = 1* - 0*pDir.x;     // determinant
	//float angle = atan2(det, dot);
	float angle = ((int)(atan2(pDir.y, pDir.x) * RAD2DEG + 360) % 360) * DEG2RAD;
	float fov = 80 * DEG2RAD;
	float lAng = -fov/2;

	float lAngle = -fov/2;
	int i = 0;
	while (i < SCR_HEIGHT)
	{
		float x = cos(lAng + angle);
		float y = sin(lAng + angle);
		t_vec2 dir = v2new(x, y);
		t_rayinfo ray = raycast(map, game->pos, dir);
		t_vec2 intersect = v2add(game->pos, v2muls(dir, ray.depths[0].depth));
		texture_draw_square(overlay, map_to_screen(intersect), v2new(5,5), R_ALPHA | 0xffff00);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCR_HEIGHT / ray.depths[0].depth);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCR_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCR_HEIGHT / 2;
		if(drawEnd >= SCR_HEIGHT)
			drawEnd = SCR_HEIGHT - 1;

		int c = drawStart - 1;
		while (c++ < drawEnd)
		{
			int col = 0xff;
			if (ray.depths[0].side)
				col = 0xff00;
			pixel_set_s(game->rt0, i, c, /*R_ALPHA |*/ col);
		}
		// pixel_set_s(game->rt0, i, 51, dist * 0xff * 100);
		// pixel_set_s(game->rt0, i, 52, dist * 0xff * 100);
		lAng += fov / (float)SCR_WIDTH;
		i++;
	}

	{
		int y = -1;
		while (++y < MAP_HEIGHT)
		{
			int x = -1;
			while (++x < MAP_WIDTH)
			{
				t_vec2 cell = map_to_screen(v2new(x ,y));
				if (map[map_index(x, y)] > 0)
					texture_draw_square(overlay, cell, v2new(cell_width, cell_height), map[map_index(x, y)]);
				else
					texture_draw_square(overlay, cell, v2new(cell_width, cell_height), 00);
			}
		}
	}
	texture_draw_line(overlay, game->mouse, map_to_screen(game->pos), R_ALPHA | 0xff0000);
	texture_draw_square(overlay, map_to_screen(game->pos), v2new(5,5), R_ALPHA |  0xff0000);
	//texture_blit(game->tex, overlay, v2new(0,0));
	//texture_blit(overlay, game->rt0, v2new(0,0));
	//texture_clear(overlay);
	//texture_draw_square(game->rt0, map_to_screen(intersect), v2new(5,5), 0xff0000);
	texture_draw(game, game->rt0, v2new(0,0));
	texture_debug_view(game, 0, overlay, v2new(0,0));
	//texture_draw(game, overlay, v2new(0,0));
	//texture_draw(game, game->tex, v2new(0,0));
	//measure_frame_rate();
}