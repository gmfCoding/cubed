/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:36:58 by clovell           #+#    #+#             */
/*   Updated: 2024/03/27 00:40:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "map.h"
#include "state.h"
#include "rect.h"

void	map_sprite_clear(t_map *map)
{
	t_tile	*tile;
	int		x;
	int		y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			tile = map_get_tile_ref(map, x, y);
			tile->sp_count = 0;
		}
	}
}

/* Updates all the sprites in the world. 
 *
 * Implementation notes:
 * The order of sprite_update is from closest to furthest
 * (Determined by `t_game::indices`)
 *

In order from the  */
void	sprite_update_all(t_world *world)
{
	int	i;
	int	j;

	map_sprite_clear(&world->map);
	i = -1;
	while (++i <world->sp_amount)
	{
		j = world->indices[i];
		sprite_update(&world->map, &world->sprite[j], j);
	}
}
// Old approach
// void	sprite_update(t_map *map, t_sprite *const sprite, int index)
// {
// 	t_tile	*tile;
// 	float	x;
// 	float	y;

// 	y = fminf(sprite->s1.y, sprite->s2.y);
// 	while (y < fmaxf(sprite->s1.y, sprite->s2.y) + 0.5f)
// 	{
// 		x = fminf(sprite->s1.x, sprite->s2.x);
// 		while (x < fmaxf(sprite->s1.x, sprite->s2.x) + 0.5f)
// 		{
// 			if (x > 0 && y > 0 && x < map->width && y < map->height)
// 			{
// 				tile = map_get_tile_ref(map, x, y);
// 				if (tile->sp_count < TILE_SP_MAX && tile->type != WALL)
// 				{
// 					tile->sprite[tile->sp_count] = index;
// 					tile->sp_count++;
// 				}
// 			}
// 			x += 1.0;
// 		}
// 		y += 1.0;
// 	}
// }

/*
 * Places the sprite `sprite` into the tiles of `map`
 *
 * Implementation notes:
 * Get the position of the center tile, min_x/y
 * Loop in the 3x3 region surrounding it (inclusive)
 * Check if the sprite intersects any of those tiles, if it does.
 * insert the sprite into the tile.
 */
void	sprite_update(t_map *map, t_sprite *const sprite, int index)
{
	const int	min_x = (int)floorf(sprite->pos.x);
	const int	min_y = (int)floorf(sprite->pos.y);
	int			i;
	int			j;
	t_tile		*tile;

	j = (int)min_y - (1 + 1);
	while (++j <= min_y + 1)
	{
		i = (int)min_x - (1 + 1);
		while (++i <= min_x + 1)
		{
			if (rect_contains_seg((t_rect){i, j, i + 1, j + 1}, \
			(t_vec4){.min = sprite->s1, .max = sprite->s2}) && \
			i >= 0 && j >= 0 && i < map->width && j < map->height)
			{
				tile = map_get_tile_ref(map, i, j);
				if (tile->sp_count < TILE_SP_MAX && tile->type != WALL)
				{
					tile->sprite[tile->sp_count] = index;
					tile->sp_count++;
				}
			}
		}
	}
}

/* Rotates the sprite `curr` to look in `dir` direction. */
void	sprite_rotate(t_game *game, t_sprite *curr, t_vec2 dir)
{
	t_rayinfo	info;
	t_vec2		hit;
	float		temp;

	dir = dir;
	temp = dir.x;
	dir.x = dir.y;
	dir.y = -temp;
	curr->s1 = v2add(curr->pos, v2muls(dir, 0.5));
	curr->s2 = v2add(curr->pos, v2muls(dir, -0.5));
	curr->vs1 = curr->s1;
	curr->vs2 = curr->s2;
	if (game != NULL)
	{
		info = raycast(game, curr->pos, dir, RAY_MASK_WALL);
		hit = ray_gethit(&info, 0);
		if (v2dist(curr->s1, curr->pos) > v2dist(hit, curr->pos))
			curr->vs1 = hit;
		info = raycast(game, curr->pos, v2rev(dir), RAY_MASK_WALL);
		hit = ray_gethit(&info, 0);
		if (v2dist(curr->s2, curr->pos) > v2dist(hit, curr->pos))
			curr->vs1 = hit;
	}
}

/* Orders the sprites from `arr` from closest to furthest from `cent`
 *	and stores the sorted indices into `ind`.
 */
void	sprite_order_distance(t_vec2 cent, t_sprite *arr, short *ind, int size)
{
	int				i;
	int				j;
	t_sprite		key;
	int				index;
	float			kdist;

	i = -1;
	while (++i < size)
		ind[i] = i;
	i = 0u;
	while (++i < size)
	{
		index = ind[i];
		key = arr[index];
		kdist = v2dist(cent, key.pos);
		j = i - 1;
		while (j >= 0 && v2dist(cent, arr[ind[j]].pos) > kdist)
		{
			ind[j + 1] = ind[j];
			j--;
		}
		ind[j + 1] = index;
	}
}
