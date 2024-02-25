/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:41:22 by clovell           #+#    #+#             */
/*   Updated: 2024/02/26 01:42:05 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* *************** */
/*  prior: loop.c: */
/* *************** */
#include "internal/wall.h"
#include "cubed.h"
#include "vector2.h"
#include "vector2i.h"
#include "ray.h"

t_column	calculate_column(t_game *game, t_vertical *vertical, t_hitpoint hit)
{
	t_column	col;
	int			height;

	col.texture = map_get_tile(&game->world->map, hit.x, hit.y).tex;
	col.tex_size = game->textures[col.texture].width;
	col.uv.x = game->player.pos.x + hit.depth * vertical->dir.x;
	if (hit.side == 2 || hit.side == 3)
		col.uv.x = game->player.pos.y + hit.depth * vertical->dir.y;
	col.uv.x -= floor(col.uv.x);
	col.sample.x = (int)(col.uv.x * (double)col.tex_size);
	if ((hit.side == 1 || hit.side == 2))
		col.sample.x = col.tex_size - col.sample.x - 1;
	height = (int)(R_HEIGHT / hit.depth);
	col.range.s = -height / 2 + R_HEIGHT / 2;
	if (col.range.s < 0)
		col.range.s = 0;
	col.range.e = height / 2 + R_HEIGHT / 2;
	if (col.range.e >= R_HEIGHT)
		col.range.e = R_HEIGHT - 1;
	col.sample_dy = 1.0 * col.tex_size / height;
	col.uv.y = (col.range.s - R_HEIGHT / 2 + height / 2) * col.sample_dy;
	col.shaded = hit.side >= 2;
	return (col);
}

void	render_column(t_game *game, t_column col)
{
	int	f;
	int	s;
	int	y;

	y = col.range.s;
	while (++y < col.range.e)
	{
		col.sample.y = (int)col.uv.y & (col.tex_size - 1);
		f = pixel_get(game->textures[col.texture], col.sample.x, col.sample.y);
		if ((f & M_APLHA) != R_ALPHA)
		{
			s = pixel_get(game->rt1, col.x, y);
			f = colour_blend(f, s);
		}
		col.uv.y += col.sample_dy;
		if (col.shaded == 1)
			f = (f >> 1) & 0x7F7F7F;
		else
			f = f & 0xFFFFFF;
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

void render_wall(t_game *game)
{
	t_vertical	vert;

	vert.x = -1;
	while (++vert.x < R_WIDTH)
	{
		vert.camera_x = 2 * vert.x / (double)R_WIDTH - 1;
		vert.dir = v2add(game->player.dir, \
		v2muls(game->player.plane, vert.camera_x));
		vert.ray = raycast(game, game->player.pos, vert.dir);
		if (vert.x == R_HEIGHT / 2)
			game->half = vert.ray;
		render_vertical(game, vert);
	}
}
