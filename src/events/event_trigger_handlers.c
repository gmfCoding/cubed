/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 13:38:28 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"
#include "title.h"

t_handle_result	target_handle_wincon(t_game *game, t_entity_2 *wincon, \
															t_entity_2 *parent)
{
	(void)wincon;
	(void)game;
	(void)parent;
	game->title.state = WIN_SCREEN;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_door(t_game *game, t_entity_2 *door, \
															t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	door->type = ET_DOOR_UNLOCKED;
	return (TARGET_HANDLE_SUCCESS);
}

//if (count >= TARGET_HANDLE_MAX_DEPTH)
//		return (TARGET_HANDLE_FAILED); // Maybe game destroy here?
t_handle_result	entity_target_handle_a(t_game *game, t_entity_2 *ent, \
															t_entity_2 *target)
{
	static int		count = 0;
	t_handle_result	res;

	count++;
	if (count >= TARGET_HANDLE_MAX_DEPTH)
		return (TARGET_HANDLE_FAILED);
	if (!ent)
		return (TARGET_HANDLE_NONE);
	if (target == NULL)
		target = ent->target;
	if (!target || !target->handle)
		return (TARGET_HANDLE_NONE);
	printf("trigger: %s -> %s\n", ent->name, target->name);
	res = target->handle(game, target, ent);
	count--;
	return (res);
}

t_handle_result	entity_target_handle(t_game *game, t_entity_2 *ent)
{
	if (!ent)
		return (TARGET_HANDLE_NONE);
	return (entity_target_handle_a(game, ent, NULL));
}
