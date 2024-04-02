/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:37:03 by clovell           #+#    #+#             */
/*   Updated: 2024/03/30 21:41:25 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"

t_tile	map_get_tile(t_map *map, int x, int y)
{
	const t_tile	tile = map->tiles[x + y * map->width];

	return (tile);
}

t_tile	*map_get_tile_refv(t_map *map, t_vec2 v)
{
	return (map_get_tile_ref(map, v.x, v.y));
}

t_tile	*map_get_tile_ref(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (NULL);
	return (&map->tiles[x + y * map->width]);
}
