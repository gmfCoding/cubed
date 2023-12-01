/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2023/12/01 02:25:17 by clovell          ###   ########.fr       */
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

#include "libft.h"

void measure_frame_rate(t_app app)
{
	static int64_t timeprev = 0;
	static char *fps = NULL;

	fps = ft_strfmt("fps: %d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0)));
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

void draw_debug_info(t_game *game)
{
	static int64_t timeprev = 0;
	const char *debugstr[] = {
		ft_strfmt("fps: %d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
		ft_strfmt("pos:(%f,%f)", (double)game->player.pos.x, (double)game->player.pos.y),
		ft_strfmt("dir:(%f,%f)", (double)game->player.dir.x, (double)game->player.dir.y),
		ft_strfmt("plane:(%f,%f)", (double)game->player.plane.x, (double)game->player.plane.y),
		ft_strfmt("hits:(%d)", game->half.hits),
	};
	int i;

	i = -1;
	while (++i < sizeof(debugstr) / sizeof(*debugstr))
	{
		mlx_string_put(game->app.mlx, game->app.win, 0, i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

bool inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int map[MAP_WIDTH * MAP_HEIGHT] =
	{
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		2,
		1,
		1,
		1,
		1,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		1,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		1,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		0,
		0,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		1,
		0,
		1,
		0,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		1,
		0,
		1,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		1,
		1,
		1,
		0,
		1,
		1,
		0,
		0,
		1,
		0,
		1,
		0,
		0,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
};

int texmap[MAP_WIDTH * MAP_HEIGHT] =
	{
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		6,
		8,
		6,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		4,
		4,
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		0,
		0,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		6,
		0,
		6,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		0,
		5,
		0,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		6,
		0,
		6,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		6,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		5,
		5,
		5,
		0,
		5,
		5,
		5,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		5,
		0,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		4,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		4,
		4,
		0,
		0,
		0,
		0,
		5,
		5,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		4,
		4,
		0,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		0,
		0,
		0,
		0,
		5,
		0,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		6,
		6,
		0,
		6,
		6,
		6,
		6,
		6,
		1,
		4,
		0,
		0,
		0,
		0,
		5,
		5,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		4,
		0,
		0,
		0,
		0,
		5,
		0,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		6,
		6,
		6,
		6,
		0,
		6,
		6,
		6,
		1,
		4,
		0,
		0,
		0,
		0,
		5,
		5,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		2,
		2,
		2,
		2,
		0,
		2,
		2,
		2,
		2,
		4,
		0,
		0,
		0,
		0,
		5,
		0,
		0,
		0,
		0,
		0,
		5,
		6,
		0,
		6,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		4,
		0,
		0,
		0,
		0,
		5,
		5,
		5,
		0,
		5,
		5,
		5,
		6,
		0,
		6,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		7,
		7,
		0,
		0,
		7,
		7,
		7,
		7,
		0,
		7,
		7,
		7,
		6,
		0,
		6,
		2,
		0,
		5,
		0,
		5,
		0,
		5,
		0,
		2,
		7,
		0,
		0,
		0,
		0,
		7,
		0,
		0,
		0,
		0,
		0,
		7,
		6,
		0,
		6,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		7,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		7,
		6,
		0,
		6,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		7,
		0,
		0,
		0,
		0,
		7,
		0,
		0,
		0,
		0,
		0,
		7,
		6,
		0,
		6,
		2,
		2,
		2,
		2,
		0,
		2,
		2,
		2,
		3,
		7,
		0,
		0,
		0,
		0,
		7,
		7,
		0,
		7,
		0,
		7,
		7,
		6,
		0,
		6,
		3,
		0,
		0,
		2,
		0,
		2,
		0,
		0,
		3,
		7,
		0,
		0,
		0,
		0,
		7,
		7,
		0,
		7,
		0,
		7,
		7,
		6,
		0,
		6,
		3,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		3,
		7,
		0,
		0,
		0,
		0,
		7,
		7,
		0,
		7,
		0,
		7,
		7,
		6,
		0,
		6,
		3,
		0,
		0,
		2,
		0,
		2,
		0,
		0,
		3,
		7,
		7,
		7,
		7,
		7,
		7,
		1,
		8,
		1,
		8,
		1,
		1,
		6,
		4,
		6,
		3,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		3,
};

int map_index(int x, int y)
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

/* Preforms a raycast on the tile grid
	RETURNS:
	-1 if there were no hits
	0 if there was a hit but no more
	1 if there was a hit and potentially more
*/
int raycast_hit(t_hitpoint *hit, t_dda *dda)
{
	while (1)
	{
		hit->side = dda->side.x >= dda->side.y;
		if (dda->side.x < dda->side.y)
		{
			hit->depth = dda->side.x;
			dda->side.x += dda->delta.x;
			dda->map.x += dda->step.x;
		}
		else
		{
			hit->depth = dda->side.y;
			dda->side.y += dda->delta.y;
			dda->map.y += dda->step.y;
		}
		if (!inside(dda->map.x, dda->map.y, MAP_WIDTH, MAP_HEIGHT))
			return -1;
		if (map[map_index(dda->map.x, dda->map.y)] > 0)
		{
			hit->x = dda->map.x;
			hit->y = dda->map.y;
			return map[map_index(dda->map.x, dda->map.y)] - 1;
		}
	}
}

t_rayinfo raycast(int *map, t_vec2 start, t_vec2 dir)
{
	t_rayinfo ray = {0};
	t_dda dda = {0};
	int hit;

	dda = dda_calculate(start, dir);
	while (ray.hits < MAX_DEPTHS)
	{
		int hit = raycast_hit(&ray.depths[ray.hits], &dda);
		if (hit >= 0)
			ray.hits++;
		if (hit <= 0)
			break;
	}
	return (ray);
}

t_vec2 screen_to_map(t_vec2 mouse)
{
	return (t_vec2){mouse.x / SCR_WIDTH * MAP_WIDTH, mouse.y / SCR_HEIGHT * MAP_HEIGHT};
}

t_vec2 map_to_screen(t_vec2 map)
{
	return (t_vec2){map.x * SCR_WIDTH / (float)MAP_WIDTH, map.y * SCR_HEIGHT / (float)MAP_HEIGHT};
}

void player_controls(t_game *game)
{
	t_player *const player = &game->player;
	double oldDirX;
	double oldPlaneX;

	oldDirX = player->dir.x;
	oldPlaneX = player->plane.x;
	if (input_keyheld(&game->input, KEY_W))
	{
		if (map[map_index((int)(player->pos.x + player->dir.x * player->moveSpeed), (int)player->pos.y)] == false)
			player->pos.x += player->dir.x * player->moveSpeed;
		if (map[map_index((int)player->pos.x, (int)(player->pos.y + player->dir.y * player->moveSpeed))] == false)
			player->pos.y += player->dir.y * player->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_S))
	{
		if (map[map_index((int)(player->pos.x - player->dir.x * player->moveSpeed), (int)player->pos.y)] == false)
			player->pos.x -= player->dir.x * player->moveSpeed;
		if (map[map_index((int)player->pos.x, (int)(player->pos.y - player->dir.y * player->moveSpeed))] == false)
			player->pos.y -= player->dir.y * player->moveSpeed;
	}
	if (input_keyheld(&game->input, KEY_D))
	{
		// both camera direction and camera plane must be rotated
		player->dir.x = player->dir.x * cos(-player->rotSpeed) - player->dir.y * sin(-player->rotSpeed);
		player->dir.y = oldDirX * sin(-player->rotSpeed) + player->dir.y * cos(-player->rotSpeed);
		player->plane.x = player->plane.x * cos(-player->rotSpeed) - player->plane.y * sin(-player->rotSpeed);
		player->plane.y = oldPlaneX * sin(-player->rotSpeed) + player->plane.y * cos(-player->rotSpeed);
	}
	if (input_keyheld(&game->input, KEY_A))
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
			t_vec2 cell = map_to_screen(v2new(x, y));
			if (map[map_index(x, y)] > 0)
				texture_draw_square(texture_get_debug_view(game, 1), cell,
									v2new(cell_width, cell_height), R_ALPHA | 0xffffff);
		}
	}
}

typedef struct s_vertical
{
	int x;
	double cameraX;
	t_vec2 dir;
	t_rayinfo ray;

} t_vertical;

typedef struct s_column
{
	int texture;
	int shaded;
	double sample_dy;
	int x;
	t_vec2 uv;
	t_vec2i sample;
	t_vec2i range;
} t_column;

t_column calculate_column(t_game *game, t_vertical *vertical, t_hitpoint hit)
{
	t_column column;
	int height;

	column.texture = texmap[hit.x + MAP_WIDTH * hit.y] - 1;
	column.uv.x = column.uv.x = game->player.pos.x + hit.depth * vertical->dir.x;
	if (hit.side == 0)
		column.uv.x = game->player.pos.y + hit.depth * vertical->dir.y;
	column.uv.x -= floor(column.uv.x);
	column.sample.x = (int)(column.uv.x * (double)WALL_TEX_SIZE);
	if (hit.side == 0 && vertical->dir.x > 0)
		column.sample.x = WALL_TEX_SIZE - column.sample.x - 1;
	if (hit.side == 1 && vertical->dir.y < 0)
		column.sample.x = WALL_TEX_SIZE - column.sample.x - 1;
	height = (int)(SCR_HEIGHT / hit.depth);
	column.range.s = -height / 2 + SCR_HEIGHT / 2;
	if (column.range.s < 0)
		column.range.s = 0;
	column.range.e = height / 2 + SCR_HEIGHT / 2;
	if (column.range.e >= SCR_HEIGHT)
		column.range.e = SCR_HEIGHT - 1;
	column.sample_dy = 1.0 * WALL_TEX_SIZE / height;
	column.uv.y = (column.range.s - SCR_HEIGHT / 2 + height / 2) * column.sample_dy;
	column.shaded = hit.side == 1;
	return (column);
}

void render_column(t_game *game, t_column column)
{
	int colour;
	int y;
	y = column.range.s;
	while (++y < column.range.e)
	{
		column.sample.y = (int)column.uv.y & (WALL_TEX_SIZE - 1);
		colour = pixel_get(game->textures[column.texture], column.sample.y, column.sample.x);
		column.uv.y += column.sample_dy;
		if (column.shaded == 1)
			colour = (colour >> 1) & 0x7F7F7F;
		pixel_set(game->rt0, column.x, y, R_ALPHA | colour);
	}
}

void render_vertical(t_game *game, t_vertical info)
{
	t_column col;
	int d;

	// d = info.ray.hits;
	// while (--d >= 0)
	d = -1;
	while (++d < info.ray.hits)
	{
		col = calculate_column(game, &info, info.ray.depths[d]);
		col.x = info.x;
		render_column(game, col);
	}
}

void render_floor_vertical(t_game *game)
{
	int h = SCR_HEIGHT;
	// FLOOR CASTING
	for (int y = 0; y < h; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = game->player.dir.x - game->player.plane.x;
		float rayDirY0 = game->player.dir.y - game->player.plane.y;
		float rayDirX1 = game->player.dir.x + game->player.plane.x;
		float rayDirY1 = game->player.dir.y + game->player.plane.y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - SCR_HEIGHT / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * SCR_HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCR_WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCR_WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = game->player.pos.x + rowDistance * rayDirX0;
		float floorY = game->player.pos.y + rowDistance * rayDirY0;

		for (int x = 0; x < SCR_WIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(WALL_TEX_SIZE * (floorX - cellX)) & (WALL_TEX_SIZE - 1);
			int ty = (int)(WALL_TEX_SIZE * (floorY - cellY)) & (WALL_TEX_SIZE - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;
			int32_t color;

			// floor
			color = pixel_get(game->textures[4], tx, ty);
			color = (color >> 1) & 8355711; // make a bit darker
			pixel_set(game->rt0, x, y, color);
			// ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = pixel_get(game->textures[4], tx, ty);
			color = (color >> 1) & 0x7F7F7F; // make a bit darker
			pixel_set(game->rt0, x, SCR_HEIGHT - y - 1, color);
		}
	}
}

void render(t_game *game)
{
	t_vertical vert;
	player_controls(game);

	input_process(&game->input);

	// texture_clear(game->rt0); // Window 1
	// texture_clear(game->rt1); // Window 2
	render_floor_vertical(game);
	// render_map_view(game); // Window 2 (later window 1)
	vert.x = -1;
	while (++vert.x < SCR_HEIGHT)
	{
		vert.cameraX = 2 * vert.x / (double)SCR_WIDTH - 1;
		vert.dir = v2add(game->player.dir, v2muls(game->player.plane, vert.cameraX));
		vert.ray = raycast(map, game->player.pos, vert.dir);
		if (vert.x == SCR_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
	// texture_draw_square(game->rt1, map_to_screen(game->player.pos), v2new(5,5), R_ALPHA | 0xff);
	// texture_draw_line(game->rt1, map_to_screen(game->player.pos), v2add(map_to_screen(game->player.pos), v2muls(game->player.plane,  50)), R_ALPHA | 0x00ff);
	texture_draw(game, game->rt0, v2new(0, 0));

	texture_draw_debug_view(game, 1);
	draw_debug_info(game);
	// exit(1);
}
