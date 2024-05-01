/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:31:56 by clovell           #+#    #+#             */
/*   Updated: 2024/04/18 17:44:20 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector2.h"
#include "vector2i.h"
#include "config.h"
#include "state.h"

static void	render_floor_row(t_game *game, int y, t_vec2 step, t_vec2 *floor)
{
	int32_t	colour;
	t_vec2i	cell;
	t_vec2i	uv;
//	t_vec2	real;
	int		x;

	x = -1;
	while (++x < R_WIDTH)
	{
//		real = v2sub(*floor, game->player.pos); 
		cell = v2inew(floor->x, floor->y);
		uv.x = (int)(WALL_TEX_SIZE * (floor->x - cell.x)) & (WALL_TEX_SIZE - 1);
		uv.y = (int)(WALL_TEX_SIZE * (floor->y - cell.y)) & (WALL_TEX_SIZE - 1);
		if (floor->x >= 0 && floor->x < game->world->map.width && floor->y >= 0 \
			&& floor->y < game->world->map.height && \
			map_get_tile(&game->world->map, floor->x, floor->y).type != EMPTY)
		{
			colour = game->world->map.color_ceiling;
			if (!game->world->map.use_ceiling)
				colour = pixel_get(game->textures[TEX_CEILING], uv.x, uv.y);
			pixel_set(game->rt1, x, y, ((colour >> 1) & 8355711) | R_ALPHA);
			colour = game->world->map.color_floor;
			if (!game->world->map.use_floor)
				colour = pixel_get(game->textures[TEX_FLOOR], uv.x, uv.y);
			colour = (colour >> 1) & 0x7F7F7F;
		//	if ((int)floor->x % 2 == 0)
		//		colour = R_BLUE | R_ALPHA;
			pixel_set(game->rt1, x, R_HEIGHT - y - 1, colour | R_ALPHA);
		}
	//	pixel_set(game->rt1, x, R_HEIGHT - y - 1, ((int)(real.y / (float)game->world->map.height * 255.0)) | R_ALPHA);
		floor->x += step.x;
		floor->y += step.y;
	}
}

static void	render_floor_cols(t_game *game, t_vec2 dir, t_vec2 diff)
{
	const float	pos_z = 0.5 * -R_HEIGHT;
	t_vec2		floor;
	t_vec2		step;
	int			y;
	int			p;

	y = -1;
	while (++y < R_HEIGHT / 2)
	{
		p = (y - R_HEIGHT / 2);
		step = v2muls(v2muls(diff, pos_z / p), 1.0f / R_WIDTH);
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
