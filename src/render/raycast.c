/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:31:27 by clovell           #+#    #+#             */
/*   Updated: 2024/02/26 01:43:40 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *************** */
/*  prior: loop.c: */
/* *************** */
#include <stdbool.h>
#include "vector2.h"
#include "vector2i.h"
#include "state.h"
#include "ray.h"

bool	inside(int x, int y, int maxX, int maxY)
{
	return (x >= 0 && y >= 0 && x < maxX && y < maxY);
}

// int	map_index(int x, int y)
// {
// 	return (x + y * MAP_WIDTH);
// }

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


// struct s_collider
// {
// 	bool type: 1;
// 	union
// 	{
// 		void *entity;
// 	};
// };

/* Preforms a raycast on the tile grid
	RETURNS:
	-1 if there were no hits
	0 if there was a hit but no more
	1 if there was a hit and potentially more
*/
int	raycast_hit(t_game *game, t_hitpoint *hit, t_dda *dda)
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
			return (-1);
		tile = map_get_tile_ref(map, dda->map.x, dda->map.y);
		if (tile->vis >= 0)
		{
			hit->x = dda->map.x;
			hit->y = dda->map.y;
			return (tile->vis);
		}
	}
	return (-1);
}

t_rayinfo	raycast(t_game *game, t_vec2 start, t_vec2 dir)
{
	t_rayinfo	ray;
	t_dda		dda;
	int			hit;

	ray = (t_rayinfo){0};
	dda = (t_dda){0};
	dda = dda_calculate(start, dir);
	while (ray.hits < MAX_DEPTHS)
	{
		hit = raycast_hit(game, &ray.depths[ray.hits], &dda);
		if (hit >= 0)
			ray.hits++;
		if (hit <= 0)
			break ;
	}
	return (ray);
}