#include "map.h"
#include "vectorconv.h"
#include "modifier_data.h"

/*
 * NAME,TARGET,ALERT_TYPE,XPOS,YPOS,TIME
 */
t_err	mod_gen_al(char *content, int index, t_world *world, t_map *map)
{
	t_mod_alarmdata	mod;
	const int		found = ft_sescanf(content, "%N%s,%s,%c,%u,%u,%u\v",
			sizeof(mod.name), &mod.name, &mod.target, &mod.type,
			&mod.pos.x, &mod.pos.y, &mod.time);

	if (found != 7 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	world->ent_2[world->ent_count] = (t_entity_2){0};
	ft_strlcpy(world->ent_2[world->ent_count].name, mod.name, NAME_SIZE);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX); // Is this required?
	if (ft_strcmp(mod.target, "NULL") != 0)  // Could be removed as mod_search_name returns null anyways, without it would induce an overhead though from searching through the mods.
		world->ent_2[world->ent_count].target =	mod_search_name(world, mod.target); // What if the mod hasn't been loaded yet?
	world->ent_2[world->ent_count].pos = v2itov2(mod.pos);
	world->ent_2[world->ent_count].ref_tile = map_get_tile_ref(&world->map, mod.pos.x, mod.pos.y);
	world->ent_2[world->ent_count].speed = mod.time;
	world->ent_2[world->ent_count].type = ET_ALERT_OFF; // Default to off
	// No longer need mod.type == 'O' because it defaults to off
	if (mod.type == 'H')
		world->ent_2[world->ent_count].type = ET_ALERT_HIGH;
	if (mod.type == 'M')
		world->ent_2[world->ent_count].type = ET_ALERT_MEDIUM;

//	world->ent_2[world->ent_count]->handle = NULL;
	world->ent_count++;
	return (0);
}
/*
t_err	mod_gen_al(char *content, int index, t_world *world, t_map *map)
{
	int	i;
	char	**al;
	int	x;
	int	y;

	i = -1;
	al = ft_split(content, ',');
	x = ft_atoi(al[3]) - 1;
	y = ft_atoi(al[4]);
	while (al[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = al[0][i];
	world->ent_2[world->ent_count].target = NULL;
	if (ft_strcmp(al[1], "NULL") != 0)
		world->ent_2[world->ent_count].target =	mod_search_name(world, al[1]);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	world->ent_2[world->ent_count].pos = v2new(x, y);
	world->ent_2[world->ent_count].ref_tile = &map->tiles[y * (map->width + x) - 1];
		world->ent_2[world->ent_count].speed = ft_atoi(al[5]);
	if (al[2][0] == 'H')
		world->ent_2[world->ent_count].type = ET_ALERT_HIGH;
	if (al[2][0] == 'O')
		world->ent_2[world->ent_count].type = ET_ALERT_OFF;
	if (al[2][0] == 'M')
		world->ent_2[world->ent_count].type = ET_ALERT_MEDIUM;
	world->ent_count++;
	free_str_array(al);
	return (0);
}
*/
