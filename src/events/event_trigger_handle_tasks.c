/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_trigger_handle_tasks.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:21:24 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 22:22:35 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"

t_handle_result	target_handle_five_lights(t_game *game, \
									t_entity_2 *five_lights, t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	five_lights->type = ET_FIVE_LIGHTS_OPEN;
	return (TARGET_HANDLE_SUCCESS);
}

t_handle_result	target_handle_orbit_task(t_game *game, t_entity_2 *orbit, \
															t_entity_2 *parent)
{
	(void)game;
	(void)parent;
	orbit->type = ET_ORBIT_TASK_OPEN;
	return (TARGET_HANDLE_SUCCESS);
}
