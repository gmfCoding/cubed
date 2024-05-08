/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_orbit_task.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:28:44 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 13:38:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "events.h"
#include "state.h"

void	event_task_orbit_closed(t_game *game, t_entity_2 *ent)
{
	(void)ent;
	game->display_ui = UI_INACTIVE_TASK;
	return ;
}

//task_destroy(task);
//		if (entity_target_handle(game, ent) == TARGET_HANDLE_FAILED)
//			printf("HANDLE ERROR!\n");// TODO: How handle error/exits?
void	event_task_orbit_open(t_game *game, t_entity_2 *ent)
{
	t_task	*task;

	task = task_create_or_find(game, "task_orbit");
	game->display_ui = UI_INTERACT;
	if (input_keydown(&game->input, KEY_E))
	{
		play_sound(game->app.sfx, SFX_ORBIT, PLAY);
		game->player.state = START_TASK;
		task->show = true;
	}
	if (task && task->completed)
	{
		play_sound(game->app.sfx, SFX_TASK_COMPLETE, PLAY);
		ent->type = ET_ORBIT_TASK_CLOSED;
		game->player.state = DONE_TASK;
		task->completed = false;
		task->init = false;
		if (entity_target_handle(game, ent) == TARGET_HANDLE_FAILED)
			printf("HANDLE ERROR!\n");
	}
}
