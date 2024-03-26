/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:31:27 by clovell           #+#    #+#             */
/*   Updated: 2024/03/18 22:52:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *************** */
/*  prior: loop.c: */
/* *************** */
#include <stdbool.h>
#include "vector2.h"
#include "vector3.h"
#include "vector2i.h"
#include "state.h"
#include "ray.h"

bool	inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

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

static int	ccw(t_vec2 a, t_vec2 b, t_vec2 c)
{
	return ((c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x));
}

static int	test_two_seg_intersect(t_vec2 a1, t_vec2 b1, t_vec2 a2, t_vec2 b2)
{
	return (ccw(a1, a2, b2) != ccw(b1, a2, b2) \
	&& ccw(a1, b1, a2) != ccw(a1, b1, b2));
}

// Find the intersection point of a1b1 and a2b2
t_vec2	two_seg_intersect(t_vec2 a1, t_vec2 b1, t_vec2 a2, t_vec2 b2)
{
	const t_vecd	a = v2det(a1, b1);
	const t_vecd	b = v2det(a2, b2);
	const t_vecd	c = f4det(f4det(a1.x, 1, b1.x, 1), f4det(a1.y, 1, b1.y, 1), \
	f4det(a2.x, 1, b2.x, 1), f4det(a2.y, 1, b2.y, 1));
	if (c == 0)
		return (v2new(0, 0));
	return \
	(v2new(f4det(a, f4det(a1.x, 1, b1.x, 1), b, f4det(a2.x, 1, b2.x, 1)) / c, \
	f4det(a, f4det(a1.y, 1, b1.y, 1), b, f4det(a2.y, 1, b2.y, 1)) / c));
}

/* Preforms a raycast on the tile grid
	RETURNS:
	-1 if there were no hits
	0 if there was a hit but no more
	1 if there was a hit and potentially more
*/
t_hittype raycast_hit(t_game *game, t_hitpoint *hit, t_dda *dda)
{
	t_tile	*tile;
	t_map *const	map = &game->world->map;

	while (1)
	{
		if (dda->side.x < dda->side.y)
		{
			hit->depth = dda->side.x;
			dda->side.x += dda->delta.x;
			dda->map.x += dda->step.x;
			hit->side = (dda->step.x > 0) + 2;
		}
		else
		{
			hit->depth = dda->side.y;
			dda->side.y += dda->delta.y;
			dda->map.y += dda->step.y;
			hit->side = dda->step.y > 0;
		}
		if (!inside(dda->map.x, dda->map.y, map->width, map->height))
			return (HT_NONE);
		tile = map_get_tile_ref(map, dda->map.x, dda->map.y);
		if (tile->vis >= 0 || tile->sp_count > 0)
		{
			hit->x = dda->map.x;
			hit->y = dda->map.y;
			if (tile->vis >= 1)
				return (HT_CLEAR);
			if (tile->sp_count > 0)
				return (HT_SPRITE);
			return (HT_WALL);
		}
	}
	return (-1);
}
#include "vectorconv.h"

t_rayinfo	raycast(t_game *game, t_vec2 start, t_vec2 dir)
{
	t_rayinfo	ray;
	t_dda		dda;
	t_sprite	*sp;
	t_hittype	hit;
	t_tile		*tile;
	t_vec2		v2;
	t_vec2		isect;
	int			i;

	ray = (t_rayinfo){0};
	dda = (t_dda){0};
	dda = dda_calculate(start, dir);
	v2 = v2add(start, v2muls(dir, 20));
	while (ray.hits < MAX_DEPTHS)
	{
		hit = raycast_hit(game, &ray.depths[ray.hits], &dda);
		if (hit == HT_WALL || hit == HT_CLEAR)
			ray.hits++;
		if (hit == HT_NONE || hit == HT_WALL)
			break ;
		tile = map_get_tile_ref(&game->world->map, dda.map.x, dda.map.y);
		i = -1;
		while (++i < tile->sp_count)
		{
			sp = &game->world->sprite[tile->sprite[i]];
			if (test_two_seg_intersect(sp->s2, sp->s1, start, v2))
			{
				isect = two_seg_intersect(sp->s2, sp->s1, start, v2);
				if (game->ray == R_WIDTH / 2)
				{
					t_texture tex = texture_get_debug_view(game, 2);
					printf("(%f, %f)\n", isect.x, isect.y);
					texture_draw_circle(&tex, v2inew(isect.x * 25, isect.y * 25), 2, R_GREEN | R_ALPHA);
					texture_draw_circle(&tex, v2tov2i(v2muls(game->player.plane_start, 25)), 2, R_RED | R_ALPHA);
					texture_draw_circle(&tex, v2tov2i(v2muls(game->player.plane_end, 25)), 2, R_RED | R_ALPHA);
				}
				//ray.depths[ray.hits].depth = v2mag(v2sub(v2proj_line(game->player.pos, sp->s1, sp->s2), game->player.pos));
				//ray.depths[ray.hits].depth = v2mag(v2proj_line(isect, sp->s1, sp->s2));
				ray.depths[ray.hits].depth = v2dist(v2proj_line(isect, game->player.plane_start,  game->player.plane_end), isect);
				//ray.depths[ray.hits].depth = v2dist(isect, game->player.pos);
				ray.depths[ray.hits].minX = v2invlerp(sp->s1, sp->s2, v2add(game->player.pos, v2muls(dir, ray.depths[ray.hits].depth)));
				ray.depths[ray.hits].sp_tex = sp->tex;
				ray.hits++;
			}
		}
	}
	return (ray);
}
