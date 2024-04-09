/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_orbit_task.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:20:00 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/09 19:05:51 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "vectorconv.h"
#include "modifiers.h"


/*
 * NAME,TARGET,ACTIVE,XPOS,YPOS
 */
t_err	mod_gen_ob(char *content, int index, t_world *world, t_map *map)
{
	t_mod_ob_data	mod;
	t_entity_2 *const	ent2 = &world->ent_2[world->ent_count];
	const int			found = ft_sescanf(content, "%N%s,%s,%c,%u,%u\v",
			sizeof(mod.name), &mod.name, &mod.target,
			&mod.active, &mod.pos.x, &mod.pos.y);

	if (found != 6 || mod.pos.x >= map->width \
					|| mod.pos.y >= map->height)
		return (1);
	*ent2 = (t_entity_2){0};
	ft_strlcpy(ent2->name, mod.name, NAME_SIZE);
	ft_strlcpy(map->mods[index].content, content, MOD_CONTENT_MAX);
	if (ft_strcmp(mod.target, "NULL") != 0)
		ent2->target =	mod_search_name(world, mod.target); // TODO: Remove after modifiers after target is done
	ent2->pos = v2itov2(mod.pos);
	*map_get_tile_refv(map, ent2->pos) = (t_tile){ .type = WALL, .vis = 0,
	.tex = TEX_FIVE_LIGHTS}; // TODO: Change to orbit task texture
	if (mod.active == 'O')
		ent2->type = ET_ORBIT_TASK_OPEN;
	else
		ent2->type = ET_ORBIT_TASK_CLOSED;
	world->ent_count++;
	return (0);
}
