/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/09 19:53:25 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"

void target_handle_five_lights(t_entity_2 *five_lights, t_entity_2 *parent)
{
	five_lights->type = ET_FIVE_LIGHTS_OPEN;
}

void target_handle_door(t_entity_2 *door, t_entity_2 *parent)
{
	door->type = ET_DOOR_UNLOCKED;
}

bool entity_target_handle(t_entity_2 *ent)
{
	const bool has = (ent && ent->target && ent->target->handle);

	if (has)
		ent->target->handle(ent->target, ent);
	return (has);
}
/*
void and_gate_handle(t_entity2 *ent, t_entity2 *from)
{
	if (ent->parent1 == from)
		ent->state++;
	if (ent->parent2 == from)
		ent->state++;
	if (ent->state == 2)
		ent->target->handle(ent->target, ent);
}

void or_gate_handle(t_entity2 *ent, t_entity2 *from)
{
	//if (ent->parent1 == from)
	//	ent->state++;
	//if (ent->parent2 == from)
	//	ent->state++;
	//if (ent->state >= 1)
	if (ent->parent1 == from || ent->parent2 == from)
		ent->target->handle(ent->target, ent);
}
*/
