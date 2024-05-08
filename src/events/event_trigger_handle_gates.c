/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handle_gates.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:20:43 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 13:37:55 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "render.h"

//if (self->parent1 == other || other == self->parent2)
t_handle_result	target_handle_or(t_game *game, t_entity_2 *self, \
															t_entity_2 *other)
{
	(void)game;
	(void)other;
	if (entity_target_handle(game, self) == TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

//	printf("GA: %p ==? %p %d %d\n", other, \
//		self->parent2, self->state_1, self->state_2);
t_handle_result	target_handle_and(t_game *game, t_entity_2 *self, \
															t_entity_2 *other)
{
	if (self->parent1 == other)
		self->state_1 = true;
	if (self->parent2 == other)
		self->state_2 = true;
	if (self->state_1 == self->state_2)
		if (entity_target_handle(game, self))
			return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}

//	printf("handle door : from(%s) -> to(%s)", other->name, self->name);
t_handle_result	target_handle_splitter(t_game *game, t_entity_2 *self, \
														t_entity_2 *other)
{
	(void)other;
	if (entity_target_handle_a(game, self, self->targets[0]) \
													== TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	if (entity_target_handle_a(game, self, self->targets[1]) \
													== TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	if (entity_target_handle_a(game, self, self->targets[2]) \
													== TARGET_HANDLE_FAILED)
		return (TARGET_HANDLE_FAILED);
	return (TARGET_HANDLE_SUCCESS);
}
