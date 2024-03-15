#include "map.h"

/*
 * NAME,LOCATION,MMAP_FOG
 */
t_err	mod_gen_mm(char *content, int index, t_world *world, t_map *map)
{
//TODO add toggle map postion
	(void)world;
	map->mods[index].type = MINI_MAP;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	return (0);
//	printf("%s\n",map->mods[index].content);
}



