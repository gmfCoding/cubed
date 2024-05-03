/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_five_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <kmordaun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:21 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/03 21:16:03 by kmordaun         ###   ########.fr       */
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

//			if (entity_target_handle(game, ent) == TARGET_HANDLE_FAILED)
//				printf("HANDLE ERROR!\n");// TODO: How handle error/exits?
void	event_five_lights_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = UI_INTERACT;
	if (input_keydown(&game->input, KEY_E))
	{
		play_sound(game->app.sfx, SFX_HEARTBEAT, LOOP);
		play_sound(game->app.sfx, SFX_TASK, PLAY);
		game->player.state = START_TASK;
		game->five_light.run_game = true;
	}
	if (game->five_light.run_game == false)
	{
		if (game->five_light.finished == true)
		{
			play_sound(game->app.sfx, SFX_HEARTBEAT, STOP);
			ent->type = ET_FIVE_LIGHTS_CLOSED;
			if (entity_target_handle(game, ent) == TARGET_HANDLE_FAILED)
				printf("HANDLE ERROR!\n");
		}
		game->five_light.finished = false;
	}
}
