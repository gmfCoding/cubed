#include "map.h"

/*
 * NAME,TARGET,SPEED,XPOS,YPOS,ENEMY_STATE
 */
void	mod_gen_en(char *content, int index, t_world *world, t_map *map)
{//still need to add images ill that will be done elsewhere
	char	**en;
	int	x;
	int	y;

	map->mods[index].type = ENEMY;
	map->mods[index].content = ft_strdup(content);
	en = ft_split(content, ',');
	x = ft_atoi(en[3]) - 1;
	y = ft_atoi(en[4]);
//	if (ft_strcmp(en[0], "partick") != 0)//if we have more the one type of enemy
//		enemy->anim = patrik->anim;
	world->enemy.speed = ft_atoi(en[2]);
	if (en[5][0] == 'N')
		world->enemy.state = NOT_ACTIVE;
	world->enemy.dir = 0;

	world->enemy.tile_ref = &world->map.tiles[x + y * world->map.width]; // TODO: Use map_get_tile_ref (after main merge)
	world->sprite[world->sp_amount] = (t_sprite){.tex = 7, .pos = v2new((double)x + 0.5, (double )y + 0.5)};
	world->enemy.pos = v2new((double)x + 0.5, (double )y + 0.5);//maybe dont need this if we are using the sprite position

	world->enemy.tile_ref->sprite[world->enemy.tile_ref->sp_count] = world->sp_amount;
	world->sp_amount++;
	world->enemy.tile_ref->sp_count++;



	free_str_array(en);
}

/*// if we wanted the enemy to be aprt of the event triggers or to be at leased looped through

	int	i;
	char	**en;
	int	x;
	int	y;



	i = -1;
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
*/

