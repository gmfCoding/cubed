/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 18:22:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "mini_map.h"

void	mmap_door_update(t_door *door, t_mmap *mmap)
{
	if (door->closed)
	{
		if (door->base.mm_tile->vertical == true)
			door->base.mm_tile->img = &mmap->mm_img[13];
		else
			door->base.mm_tile->img = &mmap->mm_img[11];
	}
	else
	{
		if (door->base.mm_tile->vertical == true)
			door->base.mm_tile->img = &mmap->mm_img[14];
		else
			door->base.mm_tile->img = &mmap->mm_img[12];
	}
}

void	event_door_locked(t_game *game, t_entity_2 *ent)
{
	(void)ent;
	game->display_ui = UI_LOCKED_DOOR;
}

void	event_door_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = UI_INTERACT;
	if (input_keydown(&game->input, KEY_E))
	{
		event_door_modify(game, ent, false);
	}
}

void	event_door_unlocked(t_game *game, t_entity_2 *ent)
{
	game->display_ui = UI_INTERACT;
	if (input_keydown(&game->input, KEY_E))
	{
		event_door_modify(game, ent, true);
	}
}

void	event_door_modify(t_game *game, t_entity_2 *ent, bool open)
{
	t_door *const	door = (t_door *)ent->entity;
	t_tile			*tile;

	door->closed = !door->closed;
	play_sound(game->app.sfx, SFX_DOOR, PLAY);
	tile = map_get_tile_ref(&game->world->map, ent->pos.x, ent->pos.y);
	if (open)
	{
		tile->vis = -1;
		door->closed = false;
		ent->type = ET_DOOR_OPEN;
	}
	else
	{
		tile->vis = -2;
		door->closed = true;
		ent->type = ET_DOOR_UNLOCKED;
		if (game->world->enemy)
		{
			enemy_update_path_to_target(game, game->world->enemy);
			game->world->enemy->p_index = 0;
		}
	}
	mmap_door_update(door, &game->mmap);
}
