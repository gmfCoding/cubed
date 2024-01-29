#include "map.h"






/*
 * NAME,TARGET,ALERT_TYPE,XPOS,YPOS,TIME
 */
void	mod_gen_al(char *content, int index, t_world *world, t_map *map)
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
	if (ft_strcmp(al[1], "NULL") == 0)
		printf("need to search for name and add to target\n");
//	ft_strcpy(world->ent_2[world->ent_count].ui_display_1, "FIND THE TURD");
//	ft_strcpy(world->ent_2[world->ent_count].ui_display_2, "TURD FOUND");
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
	world->ent_2[world->ent_count].ref_tile = &map->tiles[y * (map->width + x) - 1];
	world->ent_2[world->ent_count].target = NULL;
	world->ent_2[world->ent_count].speed = ft_atoi(al[5]);
	if (al[2][0] == 'H')
		world->ent_2[world->ent_count].type = ALERT_HIGH;
	if (al[2][0] == 'O')
		world->ent_2[world->ent_count].type = ALERT_OFF;
	if (al[2][0] == 'M')
		world->ent_2[world->ent_count].type = ALERT_MEDIUM;
	world->ent_count++;
	free_str_array(al);
}
