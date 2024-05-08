/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_window_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:38:42 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 13:35:06 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "csv.h"
#include "modifier_data.h"

void	set_window_line(t_vec2i start, t_vec2i end, t_map *map)
{
	int			start_x;
	t_tile		*tile;

	start_x = start.x;
	while (++start.y <= end.y)
	{
		start.x = start_x - 1;
		while (++start.x <= end.x)
		{
			tile = map_get_tile_ref(map, start.x, start.y);
			if (tile->type != WALL)
				continue ;
			tile->tex = TEX_WINDOW;
			tile->vis = 1;
			tile->type = WALL;
		}
	}
}

/*
 * X_START, Y_START, X_END, Y_END
 */
t_err	mod_gen_wl(char *content, int index, t_world *world, t_map *map)
{
	t_vec2i		start;
	t_vec2i		end;
	const int	found = ft_sescanf(content, "%u,%u,%u,%u\v", &start.x, \
													&start.y, &end.x, &end.y);

	(void)world;
	(void)index;
	if (found != 4 || start.x >= map->width || start.y >= map->height \
		|| end.x >= map->width || end.y >= map->height)
		return (1);
	start.y--;
	set_window_line(start, end, map);
	return (0);
}
