/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/10 01:39:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"

t_handle_result target_handle_five_lights(t_entity_2 *five_lights, t_entity_2 *parent)
{
	five_lights->type = ET_FIVE_LIGHTS_OPEN;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result target_handle_door(t_entity_2 *door, t_entity_2 *parent)
{
	door->type = ET_DOOR_UNLOCKED;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	entity_target_handle_a(t_entity_2 *ent, t_entity_2 *target)
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
	res = target->handle(target, ent);
	count--;
	return (res);
}

t_handle_result	entity_target_handle(t_entity_2 *ent)
{
	if (!ent)
		return (TARGET_HANDLE_NONE);
	return (entity_target_handle_a(ent, NULL));
}

t_handle_result	target_handle_or(t_entity_2 *self, t_entity_2 *other)
{
	//if (self->parent1 == other || other == self->parent2)
    if (entity_target_handle(self) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_and(t_entity_2 *self, t_entity_2 *other)
{
	if (self->parent1 == other)
		self->state_1 = true;
	if (self->parent2 == other)
		self->state_2 = true;
	printf("GA: %p ==? %p %d %d\n", other, self->parent2, self->state_1, self->state_2);
	if (self->state_1 == self->state_2)
		if (entity_target_handle(self))
        	return (TARGET_HANDLE_FAILED);
  return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_splitter(t_entity_2 *self, t_entity_2 *other)
{
	if (entity_target_handle_a(self, self->targets[0]) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	if (entity_target_handle_a(self, self->targets[1]) == TARGET_HANDLE_FAILED)
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
