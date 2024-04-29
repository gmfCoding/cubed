/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_orbit_task.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:20:00 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 19:40:17 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "vectorconv.h"
#include "modifiers.h"

static t_err	setup_entity(t_world *world, t_mod_ob_data *data)
{
	t_ent_task_orbit	*orbit;

	orbit = (t_ent_task_orbit *)entity_create(world, ENT_TASK_ORBIT);
	if (orbit == NULL)
		return (1);
	orbit->dir = mod_dir_to_vec2(data->dir);
	orbit->base.pos = v2itov2(data->pos);
	orbit->sprites[0] = &world->sprite[world->sp_amount++];
	orbit->sprites[1] = &world->sprite[world->sp_amount++];
	orbit->sprites[2] = &world->sprite[world->sp_amount++];
	orbit->sprites[3] = &world->sprite[world->sp_amount++];
	orbit->sprites[4] = &world->sprite[world->sp_amount++];
	*orbit->sprites[1] = (t_sprite){.visible = true, .tex = TEX_WALL_OB, \
	.vsfb = true, .uv = (t_uv){.offset.v = {0.2, 0}, .scale.v = {0.6, 1}}};
	*orbit->sprites[0] = *orbit->sprites[1];
	orbit->sprites[0]->uv = (t_uv){.offset.v = {0, 0}, .scale.v = {0.2, 1}};
	*orbit->sprites[2] = *orbit->sprites[0];
	*orbit->sprites[3] = *orbit->sprites[0];
	*orbit->sprites[4] = *orbit->sprites[0];
	return (0);
}

/*
 * NAME,TARGET,ACTIVE (O | C), XPOS, YPOS, DIR (N | E | W | S)
 */
t_err	mod_gen_ob(char *content, int index, t_world *world, t_map *map)
{
	t_mod_ob_data		mod;
	t_entity_2 *const	ent2 = &world->ent_2[world->ent_count];
	const int			found = ft_sescanf(content, "%N%s,%s,%c,%u,%u,%c\v",
			sizeof(mod.name), &mod.name, &mod.target,
			&mod.active, &mod.pos.x, &mod.pos.y, &mod.dir);

	if (found != 7 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	*ent2 = (t_entity_2){0};
	ft_strlcpy(ent2->name, mod.name, NAME_SIZE);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	ent2->target_names[0] = ft_strdup(mod.target);
	ent2->pos = v2itov2(mod.pos);
	*map_get_tile_refv(map, ent2->pos) = (t_tile){ .type = FLOOR, .vis = -2 };
	ent2->handle = &target_handle_orbit_task;
	if (mod.active == 'O')
		ent2->type = ET_ORBIT_TASK_OPEN;
	else
		ent2->type = ET_ORBIT_TASK_CLOSED;
	if (setup_entity(world, &mod))
		return (1);
	world->ent_count++;
	return (0);
}
