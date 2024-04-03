/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/04 01:25:41 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "mini_map.h"

void mmap_door_update(t_door *door, t_mmap *mmap)
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
	t_door *const	door = ent->entity;

	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		door->closed = false;
		printf("DOOR IS LOCKED\n");
	}
	return ;
}

void	event_door_open(t_game *game, t_entity_2 *ent)
{
	t_door *const	door = ent->entity;

	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		door->closed = true;
		ent->type = ET_DOOR_UNLOCKED;	
		mmap_door_update(door, &game->mmap);
		if (game->world->enemy)
		{
			enemy_update_path_to_target(game, game->world->enemy);
			game->world->enemy->p_index = 0;
		}
	}
}

void	event_door_unlocked(t_game *game, t_entity_2 *ent)
{
	t_door *const	door = ent->entity;

	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		door->closed = false;
		ent->type = ET_DOOR_OPEN;
		mmap_door_update(door, &game->mmap);
	}
}

void	event_door(t_door *door, t_game *game)
{
	if (door->locked)
		return ;
	door->closed = !door->closed;
	mmap_door_update(door, &game->mmap);
}
