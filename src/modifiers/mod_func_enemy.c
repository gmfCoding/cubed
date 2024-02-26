#include "map.h"

/*
 * NAME,TARGET,SPEED,XPOS,YPOS,ISACTIVE
 */
void	mod_gen_en(char *content, int index, t_world *world, t_map *map)
{//still decidine on what an enemy should have in the way of structs i may need to have it on a seperate struct also and reference the entitie struct??
 //have to think about it more??
	int	i;
	char	**en;
	int	x;
	int	y;

	i = -1;
	en = ft_split(content, ',');
	x = ft_atoi(en[3]) - 1;
	y = ft_atoi(en[4]);
	while (en[0][++i] && i < NAME_SIZE)
		world->ent_2[world->ent_count].name[i] = en[0][i];
	world->ent_2[world->ent_count].target = NULL;
//	if (ft_strcmp(en[1], "NULL") != 0)
//		world->ent_2[world->ent_count].target =	mod_search_name(world, en[1]);
	map->mods[index].content = ft_strdup(content);
	get_pos_and_surrounding_tiles(world, x, y);
	world->ent_2[world->ent_count].ref_tile = &map->tiles[y * (map->width +x) - 1];
	world->ent_2[world->ent_count].speed = ft_atoi(en[2]);
	world->ent_2[world->ent_count].type = ENEMY;
	if (en[5][0] == 'Y')
		world->ent_2[world->ent_count].state_1 = true;
	world->ent_count++;

	world->sprite[world->sp_amount] = (t_sprite){.tex = 7, .pos = v2new((double)x + 0.5, (double )y + 0.5)};
	world->map.tiles[x + y * world->map.width].sp_count = 1;
	world->map.tiles[x + y * world->map.width].sprite[0] = 0;
	world->sp_amount++;
	printf("sp_amount = %d\n", world->sp_amount);
//need to organize the sprite struct or make a new one or rederence the image of what is being displayed



	free_str_array(en);
}

