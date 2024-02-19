/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:22:39 by clovell           #+#    #+#             */
/*   Updated: 2024/02/20 00:35:31 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "clmath.h"

t_tile map_get_tile(t_map *map, int x, int y)
{
	t_tile tile = map->tiles[x + y * map->width];
	return (tile);
}

t_tile *map_get_tile_ref(t_map *map, int x, int y)
{
	t_tile *tile = &map->tiles[x + y * map->width];
	return (tile);
}

t_tile map_get_tile_s(t_map *map, int x, int y)
{
	if (inside(x, y, map->width, map->height))
		return (map->tiles[x + y * map->width]);
	return (map->tiles[0]);
}

t_tile *map_get_tile_ref_s(t_map *map, int x, int y)
{
	if (inside(x, y, map->width, map->height))
		return (&map->tiles[x + y * map->width]);
	return (NULL);
}
