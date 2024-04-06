
#include "map.h"

t_modtype *mod_get_mod(t_map *map, t_modtype type, int *index)
{
	int	i;

	i = 0;
	while (i < sizeof(map->mods) / sizeof(t_mod) && map->mods[i].type != type)
		i++;
	if (index != NULL)
		*index = i;
	if (i < sizeof(map->mods) / sizeof(*map->mods))
		return (&map->mods[i].type);
	return (NULL);
}
