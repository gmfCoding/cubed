/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:38:42 by clovell           #+#    #+#             */
/*   Updated: 2024/04/18 17:20:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "csv.h"
#include "modifier_data.h"

/*
 * XPOS, YPOS
 */
t_err	mod_gen_wn(char *content, int index, t_world *world, t_map *map)
{
	t_vec2i		pos;
	const int	found = ft_sescanf(content, "%u,%u\v", &pos.x, &pos.y);
	t_tile		*tile;

	(void)index;
	(void)world;
	(void)map;
	if (found != 2 || pos.x >= map->width || pos.y >= map->height)
		return (1);
	tile = map_get_tile_ref(map, pos.x, pos.y);
	tile->tex = TEX_WINDOW;
	tile->vis = 1;
	tile->type = WALL;
	return (0);
}
