/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_fivelights.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:20:00 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 20:39:47 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "vectorconv.h"
#include "modifiers.h"
#include "events.h"

/*
 * NAME,TARGET,ACTIVE,XPOS,YPOS
 */
t_err	mod_gen_fl(char *content, int index, t_world *world, t_map *map)
{
	t_mod_fl_data		mod;
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
	ent2->target_names[0] = ft_strdup(mod.target);
	ent2->pos = v2itov2(mod.pos);
	*map_get_tile_refv(map, ent2->pos) = (t_tile){.type = WALL, .vis = 0,
	.tex = TEX_FIVE_LIGHTS};
	if (mod.active == 'O')
		ent2->type = ET_FIVE_LIGHTS_OPEN;
	else
		ent2->type = ET_FIVE_LIGHTS_CLOSED;
	ent2->handle = target_handle_five_lights;
	world->ent_count++;
	return (0);
}
