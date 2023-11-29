/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2023/11/25 19:50:05 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# ifdef __linux__
#  define R_ALPHA 0xff000000
# else
#  define R_ALPHA 0x00000000
#endif

#define R_RED   0x00ff0000
#define R_GREEN 0x0000ff00
#define R_BLUE  0x000000ff

#define OF_ALPHA 24
#define OF_RED   16
#define OF_GREEN 8
#define OF_BLUE  0

#include "libft.h"
# define MAX_RAYCAST_DIST 100

void measure_frame_rate(t_app app)
{
	static int64_t timeprev = 0;
	static char *fps = NULL;
	
	fps = ft_strfmt("fps: %d",  (int) (1.0 / ((time_get_ms() - timeprev) / 1000.0)));
	mlx_string_put(app.mlx, app.win, 0, 10, 0x00FF00, fps);
	free(fps);
	// AUTO EXIT AFTER 4 SECONDS (used for GMON)
	// static int64_t time;
	// if (timeprev != 0)
	// 	time += time_get_ms() - timeprev;
	// if (time > 4 * 1000)
	// 	exit(0);
	timeprev = time_get_ms();
}

bool inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

# define MAP_WIDTH 6
# define MAP_HEIGHT 6
int map[MAP_WIDTH * MAP_HEIGHT] = 
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
	t_vec2i map;
	t_vec2i step;
	t_vec2 side;
};

t_dda dda_calculate(t_vec2 start, t_vec2 dir)
{
	t_dda dda;

	dda = (t_dda){0};
	dda.map = (t_vec2i){start.x, start.y};
	dda.delta.x = 1e30;
	if (dda.delta.x != 0)
		dda.delta.x = 1.0 / fabs(dir.x);
	dda.delta.y = 1e30;
	if (dda.delta.y != 0)
		dda.delta.y = 1.0 / fabs(dir.y);
	dda.step.x = 1;
	dda.side.x = (dda.map.x + 1.0 - start.x) * dda.delta.x;
	if (dir.x < 0)
	{
		dda.step.x = -1;
		dda.side.x = (start.x - dda.map.x) * dda.delta.x;
	}
	dda.step.y = 1;
	dda.side.y = (dda.map.y + 1.0 - start.y) * dda.delta.y;
	if (dir.y < 0)
	{
		dda.step.y = -1;
		dda.side.y = (start.y - dda.map.y) * dda.delta.y;
	}
	return (dda);
}

int raycast_hit(t_hitpoint *hit, t_dda *dda)
{
	while (1)
	{
		hit->side = dda->side.x >= dda->side.y;
		if (dda->side.x < dda->side.y)
		{
			dda->side.x += dda->delta.x;
			dda->map.x += dda->step.x;
		}
		else
		{
			dda->side.y += dda->delta.y;
			dda->map.y += dda->step.y;
		}
		if (!inside(dda->map.x, dda->map.y, MAP_WIDTH, MAP_HEIGHT))
			return -1;
		if (map[map_index(dda->map.x, dda->map.y)] > 0)
		{
			hit->depth = (dda->side.y - dda->delta.y);
			if (hit->side == 0)
				hit->depth = (dda->side.x - dda->delta.x);
			hit->x = dda->map.x;
			hit->y = dda->map.y;
			return 1;
		}
	}
}

t_rayinfo raycast(int *map, t_vec2 start, t_vec2 dir)
{
	t_rayinfo	ray = {0};
	t_dda		dda = {0};

	dda = dda_calculate(start, dir);
	while (ray.hits < MAX_DEPTHS)
	{
		raycast_hit(&ray.depths[ray.hits], &dda);
		ray.hits++;
	}
	return ray;
}

t_vec2	screen_to_map(t_vec2 mouse)
{
	return (t_vec2){mouse.x / SCR_WIDTH * MAP_WIDTH, mouse.y / SCR_HEIGHT * MAP_HEIGHT};
}

t_vec2	map_to_screen(t_vec2 map)
{
	return (t_vec2){map.x * SCR_WIDTH / (float)MAP_WIDTH, map.y * SCR_HEIGHT / (float)MAP_HEIGHT};
}

void	on_mouse_move(int x, int y, t_game *game)
{
	game->mouse = v2new(x, y);
}

void	on_mouse(int key, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)game;
}

void	player_controls(t_game *game)
{
	t_player *const player = &game->player;
	double oldDirX;
	double oldPlaneX;

	oldDirX = player->dir.x;
	oldPlaneX = player->plane.x;
	if (input_keyheld(&game->input, KEY_W))
	{
		if (map[map_index((int)(player->pos.x + player->dir.x * player->moveSpeed),(int)player->pos.y)] == false)
			player->pos.x += player->dir.x * player->moveSpeed;
		if (map[map_index((int)player->pos.x,(int)(player->pos.y + player->dir.y * player->moveSpeed))] == false)
			player->pos.y += player->dir.y * player->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_S))
	{
		if (map[map_index((int)(player->pos.x - player->dir.x * player->moveSpeed),(int)player->pos.y)] == false)
			player->pos.x -= player->dir.x * player->moveSpeed;
		if (map[map_index((int)player->pos.x,(int)(player->pos.y - player->dir.y * player->moveSpeed))] == false)
			player->pos.y -= player->dir.y * player->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_A))
	{
		// both camera direction and camera plane must be rotated
		player->dir.x = player->dir.x * cos(-player->rotSpeed) - player->dir.y * sin(-player->rotSpeed);
		player->dir.y = oldDirX * sin(-player->rotSpeed) + player->dir.y * cos(-player->rotSpeed);
		player->plane.x = player->plane.x * cos(-player->rotSpeed) - player->plane.y * sin(-player->rotSpeed);
		player->plane.y = oldPlaneX * sin(-player->rotSpeed) + player->plane.y * cos(-player->rotSpeed);
	}
	if (input_keyheld(&game->input, KEY_D))
	{
		// both camera direction and camera plane must be rotated
		player->dir.x = player->dir.x * cos(player->rotSpeed) - player->dir.y * sin(player->rotSpeed);
		player->dir.y = oldDirX * sin(player->rotSpeed) + player->dir.y * cos(player->rotSpeed);
		player->plane.x = player->plane.x * cos(player->rotSpeed) - player->plane.y * sin(player->rotSpeed);
		player->plane.y = oldPlaneX * sin(player->rotSpeed) + player->plane.y * cos(player->rotSpeed);
	}
}

void render_map_view(t_game *game)
{
	const int cell_width = SCR_WIDTH / MAP_WIDTH;
	const int cell_height = SCR_HEIGHT / MAP_HEIGHT;
	int y = -1;
	while (++y < MAP_HEIGHT)
	{
		int x = -1;
		while (++x < MAP_WIDTH)
		{
			t_vec2 cell = map_to_screen(v2new(x ,y));
			if (map[map_index(x, y)] > 0)
				texture_draw_square(texture_get_debug_view(game, 1), cell,\
				 v2new(cell_width, cell_height), R_ALPHA | 0xffffff);
		}
	}
}

void	render(t_game *game)
{
	player_controls(game);

	input_process(&game->input);

	texture_clear(game->rt0); // Window 1
	texture_clear(game->rt1); // Window 2

	render_map_view(game); // Window 2 (later window 1)
	int i = 0;
	while (i < SCR_HEIGHT)
	{
		double cameraX = 2 * i / (double)SCR_WIDTH - 1;
		t_vec2 dir = v2add(game->player.dir, v2muls(game->player.plane, cameraX));
		t_rayinfo ray = raycast(map, game->player.pos, dir);
		t_vec2 intersect = v2add(game->player.pos, v2muls(dir, ray.depths[0].depth));
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
		while (++c < drawEnd)
		{
			int col = 0xff;
			if (ray.depths[0].side)
				col = 0xff00;
			pixel_set_s(game->rt0, i, c, R_ALPHA | col);
		}
		i++;
		texture_draw_square(game->rt1, map_to_screen(intersect), v2new(5,5), R_ALPHA | 0xff0000);
	}
	texture_draw_square(game->rt1, map_to_screen(game->player.pos), v2new(5,5), R_ALPHA | 0xff);
	texture_draw_line(game->rt1, map_to_screen(game->player.pos), v2add(map_to_screen(game->player.pos), v2muls(game->player.plane,  50)), R_ALPHA | 0x00ff);
	texture_draw(game, game->rt0, v2new(0,0));
	texture_draw_debug_view(game, 1);
	measure_frame_rate(game->app);
}