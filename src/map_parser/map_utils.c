/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:37:03 by clovell           #+#    #+#             */
/*   Updated: 2024/02/25 20:37:04 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"

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