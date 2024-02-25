#include "map.h"
#include "state.h"

/*
 * XPOS,YPOS
 */
void	mod_gen_wn(char *content, int index, t_world *world, t_map *map)
{
	char	**al;
	int		x;
	int		y;

	al = ft_split(content, ',');
	x = ft_atoi(al[0]);
	y = ft_atoi(al[1]);
	t_tile *tile = &map->tiles[y * map->width + x]; // TODO: Use map_get_tile_ref
	tile->tex = TEX_WINDOW;
	tile->vis = 1;
	tile->type = WALL;
	free_str_array(al);
}
