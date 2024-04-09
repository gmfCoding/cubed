/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_five_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:47:21 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/09 20:05:48 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "events.h"
#include "state.h"

void	event_five_lights_closed(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
		printf("TASK IS COMPLETE\n");
	return ;
}

void	event_five_lights_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->player.state = START_TASK;
		game->five_light.run_game = true;
	}
	if (game->five_light.run_game == false)
	{
		if (game->five_light.finished == true)
		{
			ent->type = ET_FIVE_LIGHTS_CLOSED;
			entity_target_handle(ent);
		}
		game->five_light.finished = false;
	}
}
