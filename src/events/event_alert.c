/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_alert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/18 16:59:42 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "mini_map.h"

void	event_alert_off(t_game *game, t_entity_2 *ent)
{
	(void)ent;
	if (ent->state_3 == false)
		return ;
	game->mmap.alert_m = false;
	game->mmap.alert_h = false;
	ent->state_3 = false;
}

void	event_alert_medium(t_game *game, t_entity_2 *ent)
{
	(void)ent;

	if (ent->state_3 == false)
		return ;
	play_sound(game->app.sfx, SFX_ALERT, PLAY);
	game->mmap.alert_m = true;
	game->mmap.alert_h = false;
	game->mmap.al_pos = ent->target->pos;
	ent->state_3 = false;
}

void	event_alert_high(t_game *game, t_entity_2 *ent)
{
	if (ent->state_3 == false)
		return ;
	(void)ent;
	play_sound(game->app.sfx, SFX_ALERT, PLAY);
	game->mmap.alert_h = true;
	game->mmap.alert_m = false;
	game->mmap.al_pos = ent->target->pos;
	ent->state_3 = false;
}
