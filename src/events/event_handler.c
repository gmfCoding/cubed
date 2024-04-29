/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 14:49:51 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "state.h"
#include "mini_map.h"
#include "vectorconv.h"

/*
 * a temperoraly function ran straight from loop to display ui
 * should be replaced with actual image of font or interaction
 * image
 */
void	event_display_ui(t_game *game)
{
	if (game->display_ui == UI_INTERACT)
	{
		if (game->fpsc % 50 > 25)
			texture_blit(game->textures[TEX_UI_INTERACT_DUL], \
				game->rt0, v2new(400, 600));
		else
			texture_blit(game->textures[TEX_UI_INTERACT_BRIGHT], \
				game->rt0, v2new(400, 600));
	}
	if (game->display_ui == UI_LOCKED_DOOR)
		texture_blit(game->textures[TEX_UI_DOOR_LOCKED], \
			game->rt0, v2new(380, 600));
	if (game->display_ui == UI_INACTIVE_TASK)
		texture_blit(game->textures[TEX_UI_TASK_INACTIVE], \
			game->rt0, v2new(370, 600));
	texture_blit(game->textures[TEX_UI_CONTROLS], game->rt0, v2new(250, 940));
}

t_event_fn			g_events[] = {
[ET_DOOR_UNLOCKED] = &event_door_unlocked,
[ET_DOOR_OPEN] = &event_door_open,
[ET_DOOR_LOCKED] = &event_door_locked,
[ET_ALERT_HIGH] = &event_alert_high,
[ET_ALERT_MEDIUM] = &event_alert_medium,
[ET_ALERT_OFF] = &event_alert_off,
[ET_FIVE_LIGHTS_OPEN] = &event_five_lights_open,
[ET_FIVE_LIGHTS_CLOSED] = &event_five_lights_closed,
[ET_ORBIT_TASK_OPEN] = &event_task_orbit_open,
[ET_ORBIT_TASK_CLOSED] = &event_task_orbit_closed,
};

/*
 * function is run if the bool events_on is on
 * loops over the referenced events_active and runs the 
 * function based apon its type if the fucntion requires input 
 * to run that is checked in the function itself otherwise it
 * will display only the ui if it has
 */
void	event_interact(t_game *game)
{
	int		i;
	t_vec2	pos;

	i = -1;
	while (game->events_active[++i] != NULL)
	{
		pos = v2add(game->events_active[i]->pos, v2new(0.5, 0.5));
		if (v2dot(v2norm(v2sub(pos, game->player.pos)), game->player.dir) > 0.8)
		{
			g_events[game->events_active[i]->type](game, \
				game->events_active[i]);
			return ;
		}
		game->display_ui = UI_NONE;
	}
}

// 123
// 456
// 789
const static t_vec2	g_directions[] = {
{.v = {-1, -1}},
{.v = {0, -1}},
{.v = {1, -1}},
{.v = {-1, 0}},
{.v = {0, 0}},
{.v = {1, 0}},
{.v = {-1, 1}},
{.v = {0, 1}},
{.v = {1, 1}},
};

/*
 * whenever the player moves to a new tile it will set all events
 * that could be triggered by iteraction if there are any to NULL
 * it will then loop through all posible events that exist 
 * and check if they have any triggerable tiles for that players
 * position if there are any events in that tile a reference is
 * stored in events active only a maximum of 9 events can be stored
 * in events active.
 * 
 * this fucntion could be done in segments where the map is split
 * up into more section and then you would only loop through the
 * events in that section where the player is located it really 
 * depends on how many events are in a single game round
 */
void	event_check(t_game *game)
{
	int	i;
	int	j;
	int	k;

	k = -1;
	i = -1;
	while (game->events_active[++k] != NULL)
		game->events_active[k] = NULL;
	k = -1;
	while ((size_t)++i < game->world->ent_count)
	{
		j = -1;
		while (++j < 9)
		{
			if (v2dist(v2add(game->world->ent_2[i].pos, g_directions[j]), \
					v2itov2(v2tov2i(game->player.pos))) < 0.05f)
			{
				game->events_active[++k] = &game->world->ent_2[i];
				game->events_on = true;
			}
		}
	}
}

/*
 * the fucntion is triggered on player movement,
 * checking if the players tile is different from last tile
 * player was in 
 */
void	event_player(t_game *game, bool force)
{
	if ((int)game->player.pos.x != game->player.oldp_x || \
	(int)game->player.pos.y != game->player.oldp_y || force)
	{
		game->display_ui = UI_NONE;
		game->events_on = false;
		game->player.oldp_x = game->player.pos.x;
		game->player.oldp_y = game->player.pos.y;
		event_check(game);
	}
}
