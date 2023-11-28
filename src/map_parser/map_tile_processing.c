

#include "cubed.h"

t_tiletype get_tiletype(char c)
{
	if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else
		return (EMPTY);
}

int	map_tiles(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (content[i] == '\0' || content[i] == '\n')
			while(i < map->width)
				map->tiles[index + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[index + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}


int	map_tiles_surround(t_map *map, char *content, int index)
{
	int	i;

	i = 0;
	map->tiles[index].type = get_tiletype(' ');
	while (i < (map->width))
	{
		if (content[i] == '\0' || content[i] == '\n')
			while(i < map->width)
				map->tiles[(index + 1) + i++].type = get_tiletype(' ');
		else
		{
			map->tiles[(index + 1) + i].type = get_tiletype(content[i]);
			i++;
		}
	}
	return (i);
}

