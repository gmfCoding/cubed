/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:38:42 by clovell           #+#    #+#             */
/*   Updated: 2024/03/16 08:06:36 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "csv.h"

/*
 * XPOS, YPOS
 */
t_err	mod_gen_wn(char *content, int index, t_world *world, t_map *map)
{
	char	**al;
	t_tile	*tile;
	int		x;
	int		y;
	t_err	e;

	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	e = csv_next('u', &content, &x);
	e |= csv_next('u', &content, &y);
	if (e || x >= map->width || y >= map->height)
		return (1);
	tile = map_get_tile_ref(map, x, y);
	tile->tex = TEX_WINDOW;
	tile->vis = 1;
	tile->type = WALL;
	return (0);
}
