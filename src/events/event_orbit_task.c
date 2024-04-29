/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_orbit_task.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:28:44 by clovell           #+#    #+#             */
/*   Updated: 2024/04/29 14:58:23 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "events.h"
#include "state.h"

void	event_task_orbit_closed(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
		printf("TASK IS COMPLETE\n");
	return ;
}

void	event_task_orbit_open(t_game *game, t_entity_2 *ent)
{
	t_task	*task;

	task = task_create_or_find(game, "task_orbit");
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->player.state = START_TASK;
		task->show = true;
	}
	if (task && task->completed)
	{
		ent->type = ET_ORBIT_TASK_CLOSED;
		game->player.state = DONE_TASK;
		//task_destroy(task);
		// TODO: Handle target entity
		task->completed = false;
		task->init = false;
	}
}
