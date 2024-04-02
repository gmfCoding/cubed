/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:38:42 by clovell           #+#    #+#             */
/*   Updated: 2024/02/25 20:38:51 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"

/*
 * XPOS, YPOS
 */
void	mod_gen_wn(char *content, int index, t_world *world, t_map *map)
{
	char	**al;
	t_tile	*tile;
	int		x;
	int		y;

	al = ft_split(content, ',');
	x = ft_atoi(al[0]);
	y = ft_atoi(al[1]);
	tile = map_get_tile_ref(map, x, y);
	tile->tex = TEX_WINDOW;
	tile->vis = 1;
	tile->type = WALL;
	free_str_array(al);
}
