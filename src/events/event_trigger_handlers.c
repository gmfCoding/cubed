/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 19:02:51 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"

t_handle_result	target_handle_five_lights(t_game *game, t_entity_2 *five_lights, t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	five_lights->type = ET_FIVE_LIGHTS_OPEN;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_door(t_game *game, t_entity_2 *door, t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	door->type = ET_DOOR_UNLOCKED;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	entity_target_handle_a(t_game *game, t_entity_2 *ent, t_entity_2 *target)
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

t_handle_result	target_handle_or(t_game *game, t_entity_2 *self, t_entity_2 *other)
{
	(void)game;
	(void)other;
	//if (self->parent1 == other || other == self->parent2)
	if (entity_target_handle(game, self) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_and(t_game *game, t_entity_2 *self, t_entity_2 *other)
{
	if (self->parent1 == other)
		self->state_1 = true;
	if (self->parent2 == other)
		self->state_2 = true;
	printf("GA: %p ==? %p %d %d\n", other, self->parent2, self->state_1, self->state_2);
	if (self->state_1 == self->state_2)
		if (entity_target_handle(game, self))
			return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_splitter(t_game *game, t_entity_2 *self, t_entity_2 *other)
{
	printf("handle door : from(%s) -> to(%s)", other->name, self->name);
	if (entity_target_handle_a(game, self, self->targets[0]) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	if (entity_target_handle_a(game, self, self->targets[1]) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	if (entity_target_handle_a(game, self, self->targets[2]) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

/*
t_handle_result	target_handle_splitter(t_entity_2 *self, t_entity_2 *other)
{
	ssize_t i;

	i = -1;
	while (++i < sizeof(self->targets) / sizeof(*self->targets))
	{
		if (self->targets[i] == NULL)
			continue;
		if (entity_target_handle_a(self, self->targets[i]) == TARGET_HANDLE_FAILED)
        	return (TARGET_HANDLE_FAILED);
	}
  return (TARGET_HANDLE_SUCCESS);
}*/
