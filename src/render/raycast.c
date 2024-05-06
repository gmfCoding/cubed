/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:31:27 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 23:01:16 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "vector2.h"
#include "vector3.h"
#include "vector2i.h"
#include "state.h"
#include "ray.h"
#include "vectorconv.h"
#include "clmath.h"

void	raycast_hit_extend(t_hitpoint *hit, t_dda *dda)
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
}

/* Preforms a raycast on the tile grid
	RETURNS:
	-1 if there were no hits
	0 if there was a hit but no more
	1 if there was a hit and potentially more
*/
t_hittype	raycast_hit(t_game *game, t_hitpoint *hit, t_dda *dda)
{
	t_tile			*tile;
	t_map *const	map = &game->world->map;

	while (1)
	{
		raycast_hit_extend(hit, dda);
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

/*
t_hittype	raycast_hit(t_game *game, t_hitpoint *hit, t_dda *dda)
{
	t_tile			*tile;
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
*/

void	raycast_sprite(t_game *game, t_rayinfo *ray, t_vec2i map)
{
	int				i;
	t_vec2			isect;
	t_sprite		*sp;
	const t_vec2	v2 = v2add(ray->start, v2muls(ray->dir, 20));
	const t_tile	*tile = map_get_tile_ref(&game->world->map, map.x, map.y);

	i = -1;
	while (++i < tile->sp_count && ray->hits < MAX_DEPTHS)
	{
		sp = &game->world->sprite[tile->sprite[i]];
		if (!sp->visible)
			continue ;
		if (test_two_seg_intersect(sp->vs2, sp->vs1, ray->start, v2))
		{
			isect = two_seg_intersect(sp->s2, sp->s1, ray->start, v2);
			ray->depths[ray->hits].depth = v2dist(v2proj_line(isect, \
				game->player.plane_start, game->player.plane_end), isect);
			ray->depths[ray->hits].min_x = v2invlerp(sp->s1, sp->s2, \
			v2add(game->player.pos, v2muls(ray->dir, \
				ray->depths[ray->hits].depth)));
			ray->depths[ray->hits].sprite = tile->sprite[i] + 1;
			ray->hits++;
		}
	}
}

/*//orginal now broken into multiple functions keeping justincase still need
void	raycast_sprite(t_game *game, t_rayinfo *ray, t_vec2i map)
{
	int				i;
	t_vec2			isect;
	t_sprite		*sp;
	const t_vec2	v2 = v2add(ray->start, v2muls(ray->dir, 20));
	const t_tile	*tile = map_get_tile_ref(&game->world->map, map.x, map.y);
	t_texture		tex;

	i = -1;
	while (++i < tile->sp_count && ray->hits < MAX_DEPTHS)
	{
		sp = &game->world->sprite[tile->sprite[i]];
		if (!sp->visible)
			continue ;
		if (test_two_seg_intersect(sp->vs2, sp->vs1, ray->start, v2))
		{
			isect = two_seg_intersect(sp->s2, sp->s1, ray->start, v2);
			#ifdef DEBUG
			if (game->ray == R_WIDTH / 2)
			{
				tex = texture_get_debug_view(game, 2);
				texture_draw_circle(&tex, \
	v2inew(isect.x * 25, isect.y * 25), 2, R_GREEN | R_ALPHA);
				texture_draw_circle(&tex, \
	v2tov2i(v2muls(game->player.plane_start, 25)), 2, R_RED | R_ALPHA);
				texture_draw_circle(&tex, \
	v2tov2i(v2muls(game->player.plane_end, 25)), 2, R_RED | R_ALPHA);
			}
			#endif
			ray->depths[ray->hits].depth = v2dist(v2proj_line(isect, \
	game->player.plane_start, game->player.plane_end), isect);
			ray->depths[ray->hits].min_x = v2invlerp(sp->s1, sp->s2, \
	v2add(game->player.pos, v2muls(ray->dir, ray->depths[ray->hits].depth)));
			ray->depths[ray->hits].sprite = tile->sprite[i] + 1;
			ray->hits++;
		}
	}
}
*/
t_vec2	ray_gethit(t_rayinfo *ray, int hit)
{
	if (hit >= ray->hits)
		return (v2new(0, 0));
	return (v2add(ray->start, v2muls(ray->dir, ray->depths[hit].depth)));
}

/* Performs a raycast (only objects include in mask) use */
t_rayinfo	raycast(t_game *game, t_vec2 start, t_vec2 dir, int mask)
{
	t_rayinfo	ray;
	t_dda		dda;
	t_hittype	hit;
	const bool	mask_wall = (mask & RAY_MASK_WALL) == RAY_MASK_WALL;

	ray = (t_rayinfo){.start = start, .dir = dir};
	dda = (t_dda){0};
	dda = dda_calculate(start, dir);
	while (ray.hits < MAX_DEPTHS)
	{
		hit = raycast_hit(game, &ray.depths[ray.hits], &dda);
		if (mask_wall && (hit == HT_WALL || hit == HT_CLEAR))
			ray.hits++;
		if ((mask_wall && hit == HT_WALL) || hit == HT_NONE)
			break ;
		if ((mask & RAY_MASK_SPRITE) == RAY_MASK_SPRITE)
			raycast_sprite(game, &ray, dda.map);
	}
	return (ray);
}
