/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_enemy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:47:41 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 20:51:39 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "vectorconv.h"

//#include "vector2i.h"
void	enemy_variables_extended(t_mod_enemy_data	mod, t_enemy *enemy)
{
	enemy->speed = mod.speed;
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
}

/*
 * NAME,TARGET,SPEED,XPOS,YPOS,ENEMY_STATE
 */
//	if (ft_strcmp(en[0], "partick") != 0)//if we have more the one type of enemy
//		enemy->anim = patrik->anim;
// TODO: Use mod.speed in calculation maybe speed is in milliseconds?
t_err	mod_gen_en(char *content, int index, t_world *world, t_map *map)
{
	t_mod_enemy_data	mod;
	t_enemy				*enemy;
	const int			found = ft_sescanf(content, "%N%s,%s,%u,%u,%u,%c\v", \
						sizeof(mod.name), &mod.name, &mod.target, &mod.speed, \
						&mod.pos.x, &mod.pos.y, &mod.state);

	if (found != 7 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	map->mods[index].type = MT_ENEMY;
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	enemy = (t_enemy *)entity_create(world, ENT_ENEMY);
	*enemy = (t_enemy){.base = enemy->base};
	enemy_variables_extended(mod, enemy);
	world->sprite[world->sp_amount] = (t_sprite){.tex = TEX_ENEMY_START, \
		.pos = v2new((double)mod.pos.x + 0.5, (double )mod.pos.y + 0.5)};
	enemy->sprite_ref = &world->sprite[world->sp_amount++];
	enemy->sprite_ref->uv = (t_uv){.offset = {.x = 0, .y = 0}, \
		.scale = {.x = 1, .y = 1}};
	enemy->sprite_ref->visible = true;
	enemy->hear_steps = false;
	world->enemy = enemy;
	return (0);
}
