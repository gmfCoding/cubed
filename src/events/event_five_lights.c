/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_five_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:21 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 14:46:03 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"

void	event_five_lights_closed(t_game *game, t_entity_2 *ent)
{
	(void)ent;
	game->display_ui = UI_INACTIVE_TASK;
}

void	event_five_lights_open(t_game *game, t_entity_2 *ent)
{
	t_task	*task;

	game->display_ui = UI_INTERACT;
	if (input_keydown(&game->input, KEY_E))
	{
		task = task_create_or_find(game, "task_fl");
		game->player.state = START_TASK;
		game->five_light.run_game = true;
	}
	if (game->five_light.run_game == false)
	{
		if (game->five_light.finished == true)
		{
			ent->type = ET_FIVE_LIGHTS_CLOSED;
			if (entity_target_handle(game, ent) == TARGET_HANDLE_FAILED)
				printf("HANDLE ERROR!\n");// TODO: How handle error/exits?
		}
		game->five_light.finished = false;
	}
}
