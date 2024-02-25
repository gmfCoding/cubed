
#include "map.h"

void	*get_pos_and_surrounding_tiles(t_world *world, int x, int y)
{
	world->ent_2[world->ent_count].pos[0].x = x;
	world->ent_2[world->ent_count].pos[0].y = y;
	world->ent_2[world->ent_count].pos[1].x = x + 1;
	world->ent_2[world->ent_count].pos[1].y = y;
	world->ent_2[world->ent_count].pos[2].x = x + 1;
	world->ent_2[world->ent_count].pos[2].y = y + 1;
	world->ent_2[world->ent_count].pos[3].x = x;
	world->ent_2[world->ent_count].pos[3].y = y + 1;
	world->ent_2[world->ent_count].pos[4].x = x - 1;
	world->ent_2[world->ent_count].pos[4].y = y + 1;
	world->ent_2[world->ent_count].pos[5].x = x - 1;
	world->ent_2[world->ent_count].pos[5].y = y;
	world->ent_2[world->ent_count].pos[6].x = x - 1;
	world->ent_2[world->ent_count].pos[6].y = y - 1;
	world->ent_2[world->ent_count].pos[7].x = x;
	world->ent_2[world->ent_count].pos[7].y = y - 1;
	world->ent_2[world->ent_count].pos[8].x = x + 1;
	world->ent_2[world->ent_count].pos[8].y = y - 1;
}

t_mod *mod_get_mod(t_map *map, t_modtype type, int *index)
{
	int	i;

	i = 0;
	while (i < sizeof(map->mods) / sizeof(t_mod) && map->mods[i].type != type)
		i++;
	if (index != NULL)
		*index = i;
	if (i < sizeof(map->mods) / sizeof(*map->mods))
		return (map->mods[i].type);
	return (NULL);
}
