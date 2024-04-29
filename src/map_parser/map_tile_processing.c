/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tile_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:20:24 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 18:36:34 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "map.h"

t_tiletype	get_tiletype(char c)
{
	if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (FLOOR);
	else
		return (EMPTY);
}

/*
 * populates the map with the corrisponding tile there are only 3 types
 * FLOOR/0 WALL/1 and everything else will be considered EMPTY/2
 * could posisbly change to add more here but i would prefer to change them
 * in modifiers so the map remains default as subject request
 */
int	map_tiles(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (content[i] == '\0' || content[i] == '\n')
			while (i < map->width)
				map->tiles[index + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[index + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}

/*
 * surrounds the whole map in empty spaces used to check boarder
 * for error this is not included in gameplay map
 */
int	map_tiles_surround(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	map->tiles[index].type = get_tiletype(' ');
	while (i < (map->width))
	{
		if (content[i] == '\0' || content[i] == '\n')
			while (i < map->width)
				map->tiles[(index + 1) + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[(index + 1) + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}
