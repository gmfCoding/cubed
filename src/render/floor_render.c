/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:31:56 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 17:04:14 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubed.h"
#include "vector2.h"
#include "vector2i.h"

static void	render_floor_row(t_game *game, int y, t_vec2 step, t_vec2 *floor)
{
	int32_t	color;
	t_vec2i	cell;
	t_vec2i	uv;
	int		x;

	x = -1;
	while (++x < SCR_WIDTH)
	{
		cell = v2inew(floor->x, floor->y);
		uv.x = (int)(WALL_TEX_SIZE * (floor->x - cell.x)) & (WALL_TEX_SIZE - 1);
		uv.y = (int)(WALL_TEX_SIZE * (floor->y - cell.y)) & (WALL_TEX_SIZE - 1);
		floor->x += step.x;
		floor->y += step.y;
		color = pixel_get(game->textures[4], uv.x, uv.y);
		pixel_set(game->rt0, x, y, (color >> 1) & 8355711);
		pixel_set(game->rt0, x, SCR_HEIGHT - y - 1, (color >> 1) & 0x7F7F7F);
	}
}

static void	render_floor_cols(t_game *game, t_vec2 dir, t_vec2 diff)
{
	const float	pos_z = SCR_HEIGHT / 2.0;
	t_vec2		floor;
	t_vec2		step;
	int			y;
	int			p;

	y = -1;
	while (++y < SCR_HEIGHT)
	{
		p = y - SCR_HEIGHT / 2;
		step = v2muls(v2muls(diff, pos_z / p), 1.0f / SCR_WIDTH);
		floor = v2add(game->player.pos, v2muls(dir, pos_z / p));
		render_floor_row(game, y, step, &floor);
	}
}

void	render_floor(t_game *game)
{
	t_vec2	dir;
	t_vec2	diff;

	dir = v2sub(game->player.dir, game->player.plane);
	diff = v2sub(v2add(game->player.dir, game->player.plane), dir);
	render_floor_cols(game, dir, diff);
}