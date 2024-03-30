/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:41:22 by clovell           #+#    #+#             */
/*   Updated: 2024/03/30 18:42:05 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *************** */
/*  prior: loop.c: */
/* *************** */

#include "internal/wall.h"
#include "state.h"
#include "vector2.h"
#include "vector2i.h"
#include "ray.h"

static inline void	calculate_column_common(t_game *game,
t_vert *vertical, t_col *col, t_hitpoint hit)
{
	col->uv.x -= floor(col->uv.x);
	col->sample.x = (int)(col->uv.x * (double)col->tex_size);
	col->height = (int)(R_HEIGHT / hit.depth);
	col->range.s = -col->height / 2 + R_HEIGHT / 2;
	if (col->range.s < 0)
		col->range.s = 0;
	col->range.e = col->height / 2 + R_HEIGHT / 2;
	if (col->range.e >= R_HEIGHT)
		col->range.e = R_HEIGHT - 1;
	col->sample_dy = (double)col->tex_size / col->height;
	col->uv.y = (col->range.s - R_HEIGHT / 2 + col->height / 2) \
	* col->sample_dy;
}

static inline t_col	calculate_column_wall(t_game *game,
t_vert *vertical, t_hitpoint hit)
{
	t_col	col;

	col.type = C_WALL;
	col.texture = map_get_tile(&game->world->map, hit.x, hit.y).tex;
	if (col.texture == 0)
		col.texture = hit.side;
	col.tex_size = game->textures[col.texture].width;
	col.uv.x = game->player.pos.x + hit.depth * vertical->dir.x;
	if (hit.side == 2 || hit.side == 3)
		col.uv.x = game->player.pos.y + hit.depth * vertical->dir.y;
	calculate_column_common(game, vertical, &col, hit);
	if ((hit.side == 1 || hit.side == 2))
		col.sample.x = col.tex_size - col.sample.x - 1;
	col.shaded = hit.side == 1;
	return (col);
}

static inline t_col	calculate_column(t_game *game, t_vert *vertical,
t_hitpoint hit)
{
	t_sprite	*sp;
	t_col		col;

	col = (t_col){0};
	if (hit.sprite > 0)
	{
		sp = &game->world->sprite[hit.sprite - 1];
		col.type = C_SPRITE;
		col.uv.x = (hit.minX * sp->uv.scale.x) + sp->uv.offset.x;
		col.texture = sp->tex;
		col.tex_size = game->textures[sp->tex].width;
		calculate_column_common(game, vertical, &col, hit);
		col.shaded = 0;
	}
	else
		col = calculate_column_wall(game, vertical, hit);
	return (col);
}

static inline void	render_column(t_game *game, t_col col)
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
		if (col.type == C_WALL)
		{
			if (col.shaded == 1)
				f = (f >> 1) & 0x7F7F7F;
			else
				f = f & 0xFFFFFF;
		}
		pixel_set(game->rt1, col.x, y, R_ALPHA | f);
	}
}

void	render_vertical(t_game *game, t_vert info)
{
	t_col	col;
	int		d;

	d = info.ray.hits;
	while (--d >= 0)
	{
		col = calculate_column(game, &info, info.ray.depths[d]);
		col.x = info.x;
		render_column(game, col);
	}
}
