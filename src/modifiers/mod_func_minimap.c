#include "map.h"

/*
 * NAME,LOCATION,MMAP_FOG
 */
void	mod_gen_mm(char *content, int index, t_world *world, t_map *map)
{
//TODO add toggle map postion
	(void)world;
	map->mods[index].type = MINI_MAP;
	map->mods[index].content = ft_strdup(content);

//	printf("%s\n",map->mods[index].content);
}



