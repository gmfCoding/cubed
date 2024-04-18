#include "map.h"
#include "state.h"
#include "vectorconv.h"

//#include "vector2i.h"

/*
 * NAME,TARGET,SPEED,XPOS,YPOS,ENEMY_STATE
 */
t_err	mod_gen_en(char *content, int index, t_world *world, t_map *map)
{
	//still need to add images ill that will be done elsewhere
	t_mod_enemy_data	mod;
	t_enemy				*enemy;
	const int			found = ft_sescanf(content, "%N%s,%s,%u,%u,%u,%c\v", \
			sizeof(mod.name), &mod.name, &mod.target, &mod.speed, 
			&mod.pos.x, &mod.pos.y, &mod.state);

	if (found != 7 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	map->mods[index].type = MT_ENEMY;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
//	if (ft_strcmp(en[0], "partick") != 0)//if we have more the one type of enemy
//		enemy->anim = patrik->anim;
	enemy = (t_enemy *)entity_create(world, ENT_ENEMY);
	*enemy = (t_enemy){.base = enemy->base};
	enemy->speed = mod.speed; // TODO: Use mod.speed in calculation maybe speed is in milliseconds?
	if (mod.state == 'N')
		enemy->state = NOT_ACTIVE;
	if (mod.state == 'T')
		enemy->state = TARGET_IN_SIGHT;
	if (mod.state == 'G')
		enemy->state = GO_PATH_TO_TARGET;
	if (mod.state == 'P')
		enemy->state = PATROL;
	enemy->angle_frame = 1;
	enemy->p_index = 1;
	enemy->base.pos = v2itov2(mod.pos);
	enemy->old_pos[0] = mod.pos;
	enemy->old_pos[1] = mod.pos;
	enemy->old_pos[2] = mod.pos;
	world->sprite[world->sp_amount] = (t_sprite){.tex = TEX_ENEMY_START, .pos = v2new((double)mod.pos.x + 0.5, (double )mod.pos.y + 0.5)};
	enemy->sprite_ref = &world->sprite[world->sp_amount++];
	enemy->sprite_ref->uv = (t_uv){.offset = { .x = 0, .y = 0}, .scale = {.x = 1, .y = 1}};
	enemy->sprite_ref->visible = true;
	world->enemy = enemy;
	return (0);
}

/*
t_err	mod_gen_en(char *content, int index, t_world *world, t_map *map)
{//still need to add images ill that will be done elsewhere
	char	**en;
	int	x;
	int	y;
	t_enemy	*enemy;

	map->mods[index].type = MT_ENEMY;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	en = ft_split(content, ',');
	x = ft_atoi(en[3]) - 1;
	y = ft_atoi(en[4]);
//	if (ft_strcmp(en[0], "partick") != 0)//if we have more the one type of enemy
//		enemy->anim = patrik->anim;
//	enemy->speed = ft_atoi(en[2]);
	enemy = (t_enemy *)entity_create(world, ENT_ENEMY);
	*enemy = (t_enemy){.base = enemy->base};
	enemy->speed = 0.01;
	if (en[5][0] == 'N')
		enemy->state = NOT_ACTIVE;
	if (en[5][0] == 'T')
		enemy->state = TARGET_IN_SIGHT;
	if (en[5][0] == 'G')
		enemy->state = GO_PATH_TO_TARGET;
	if (en[5][0] == 'P')
		enemy->state = PATROL;
	enemy->angle_frame = 1;
	enemy->p_index = 1;
	t_tile *tile = &world->map.tiles[x + y * world->map.width]; // TODO: Use map_get_tile_ref (after main merge)
	world->sprite[world->sp_amount] = (t_sprite){.tex = TEX_ENEMY_START, .pos = v2new((double)x + 0.5, (double )y + 0.5)};
	enemy->old_pos[0] = v2inew(x, y);//using to track if we move to a new tile
	enemy->old_pos[1] = v2inew(x, y);//using to track if we move to a new tile
	enemy->old_pos[2] = v2inew(x, y);//using to track if we move to a new tile
	enemy->sprite_ref = &world->sprite[world->sp_amount++];
	enemy->sprite_ref->uv = (t_uv){.offset = {0, 0}, .scale = {1, 1}};
	enemy->sprite_ref->visible = true;
	world->enemy = enemy;
	free_str_array(en);
	return (0);
}*/

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
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	get_pos_and_surrounding_tiles(world, x, y);
	world->ent_2[world->ent_count].ref_tile = &map->tiles[y * (map->width +x) - 1];
	world->ent_2[world->ent_count].speed = ft_atoi(en[2]);
	world->ent_2[world->ent_count].type = ENEMY;
	if (en[5][0] == 'Y')
		world->ent_2[world->ent_count].state_1 = true;
	world->ent_count++;
*/

