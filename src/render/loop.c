/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:42:59 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:48:08 by clovell          ###   ########.fr       */
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

void	measure_frame_rate(t_app app)
{
	static int64_t	timeprev = 0;
	static char		*fps = NULL;

	fps = ft_strfmt("fps:%d", \
	(int)(1.0 / ((time_get_ms() - timeprev) / 1000.0)));
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

void	draw_debug_info(t_game *game)
{
	t_player *const	player = &game->player;
	static int64_t	timeprev = 0;
	const char		*debugstr[] = {
		ft_strfmt("fps:%d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
		ft_strfmt("pos:(%f,%f)", (double)player->pos.x, (double)player->pos.y),
		ft_strfmt("dir:(%f,%f)", (double)player->dir.x, (double)player->dir.y),
		ft_strfmt("plane:(%f,%f)", \
		(double)game->player.plane.x, (double)game->player.plane.y),
		ft_strfmt("hits:(%d)", game->half.hits),
	};
	int				i;

	i = -1;
	while (++i < sizeof(debugstr) / sizeof(*debugstr))
	{
		mlx_string_put(game->app.mlx, game->app.win, 0, \
			i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

bool	inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

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

int	map_index(int x, int y)
{
	return (x + y * MAP_WIDTH);
}

typedef struct s_dda
{
	t_vec2	delta;
	t_vec2i	map;
	t_vec2i	step;
	t_vec2	side;
}			t_dda;

t_dda	dda_calculate(t_vec2 start, t_vec2 dir)
{
	t_dda	dda;

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
int	raycast_hit(t_hitpoint *hit, t_dda *dda)
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
			return (-1);
		if (map[map_index(dda->map.x, dda->map.y)] > 0)
		{
			hit->x = dda->map.x;
			hit->y = dda->map.y;
			return (map[map_index(dda->map.x, dda->map.y)] - 1);
		}
	}
	return (-1);
}

t_rayinfo	raycast(int *map, t_vec2 start, t_vec2 dir)
{
	t_rayinfo	ray;
	t_dda		dda;
	int			hit;

	ray = (t_rayinfo){0};
	dda = (t_dda){0};
	dda = dda_calculate(start, dir);
	while (ray.hits < MAX_DEPTHS)
	{
		hit = raycast_hit(&ray.depths[ray.hits], &dda);
		if (hit >= 0)
			ray.hits++;
		if (hit <= 0)
			break ;
	}
	return (ray);
}

t_vec2	screen_to_map(t_vec2 mouse)
{
	return ((t_vec2){mouse.x / R_WIDTH * MAP_WIDTH, \
	mouse.y / R_HEIGHT * MAP_HEIGHT});
}

t_vec2	map_to_screen(t_vec2 map)
{
	return ((t_vec2){map.x * R_WIDTH / (float)MAP_WIDTH, \
	map.y * R_HEIGHT / (float)MAP_HEIGHT});
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


void	render_map_view(t_game *game)
{
	const int	cell_width = SCR_WIDTH / MAP_WIDTH;
	const int	cell_height = SCR_HEIGHT / MAP_HEIGHT;
	int			y;
	int			x;
	t_vec2		cell;

	y = -1;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			cell = map_to_screen(v2new(x, y));
			if (map[map_index(x, y)] > 0)
				texture_draw_square(texture_get_debug_view(game, 1), cell, \
					v2new(cell_width, cell_height), R_ALPHA | 0xffffff);
		}
	}
}

typedef struct s_vertical
{
	int			x;
	double		camera_x;
	t_vec2		dir;
	t_rayinfo	ray;

}			t_vertical;

typedef struct s_column
{
	int		texture;
	int		shaded;
	double	sample_dy;
	int		x;
	t_vec2	uv;
	t_vec2i	sample;
	t_vec2i	range;
}			t_column;

t_column	calculate_column(t_game *game, t_vertical *vertical, t_hitpoint hit)
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

void	render_column(t_game *game, t_column col)
{
	int	f;
	int	s;
	int	y;

	y = col.range.s;
	while (++y < col.range.e)
	{
		col.sample.y = (int)col.uv.y & (WALL_TEX_SIZE - 1);
		f = pixel_get(game->textures[col.texture], col.sample.x, col.sample.y);
		if ((f & M_APLHA) != R_ALPHA)
		{
			s = pixel_get(game->rt1, col.x, y);
			f = colour_blend(f, s);
		}
		col.uv.y += col.sample_dy;
		if (col.shaded == 1)
			f = (f >> 1) & 0x7F7F7F;
		pixel_set(game->rt1, col.x, y, R_ALPHA | f);
	}
}


void	render_vertical(t_game *game, t_vertical info)
{
	t_column	col;
	int			d;

	d = info.ray.hits;
	while (--d >= 0)
	{
		col = calculate_column(game, &info, info.ray.depths[d]);
		col.x = info.x;
		render_column(game, col);
	}
}

void	render(t_game *game)
{
	t_vertical	vert;

	player_controls(game);
	input_process(&game->input);
	render_floor(game);
	vert.x = -1;
	while (++vert.x < R_HEIGHT)
	{
		vert.camera_x = 2 * vert.x / (double)R_WIDTH - 1;
		vert.dir = v2add(game->player.dir, \
		v2muls(game->player.plane, vert.camera_x));
		vert.ray = raycast(map, game->player.pos, vert.dir);
		if (vert.x == R_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
	texture_blit_s(game->rt1, game->rt0, v2new(0, 0), R_SCALE);
	texture_draw(game, game->rt0, v2new(0, 0));
	draw_debug_info(game);
}
