/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_func_door_control.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:34:08 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 18:24:54 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "events.h"

t_handle_result	target_handle_door_control(t_game *game, t_entity_2 *self, \
															t_entity_2 *parent)
{
	t_door	*door;
 
	(void)parent;
	(void)game;
	if (self->target == NULL || self->target->entity == NULL \
		|| self->target->entity->type != ENT_DOOR)
		return (TARGET_HANDLE_SUCCESS);

	door = (t_door *)self->target->entity;
	door->closed = self->state_1;
	event_door_modify(game, self->target, !door->closed);
	return (TARGET_HANDLE_SUCCESS);
}

/*
 * NAME,TARGET,ACTION (O | C)
 */
t_err	mod_gen_dc(char *content, int index, t_world *world, t_map *map)
{
	t_mod_door_control	mod;
	const int			found = ft_sescanf(content, "%N%s,%s,%c\v",
			sizeof(mod.name), &mod.name, &mod.target, &mod.action);

	(void)map;
	(void)index;
	if (found != 4)
		return (1);
	world->ent_2[world->ent_count] = (t_entity_2){0};
	ft_strlcpy(world->ent_2[world->ent_count].name, mod.name, NAME_SIZE);
	world->ent_2[world->ent_count].target_names[0] = ft_strdup(mod.target);
	world->ent_2[world->ent_count].handle = &target_handle_door_control;
	world->ent_count++;
	return (0);
}