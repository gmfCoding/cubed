/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/03/16 12:30:47 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "map.h"
#include "state.h"
#include "mini_map.h"

void	event_door_locked(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
		printf("DOOR IS LOCKED\n");
	return ;
}

void	event_door_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->world->map.tiles[(int)(ent->pos.x + ent->pos.y * game->world->map.width)].vis = 1;
		game->world->map.tiles[(int)(ent->pos.x + ent->pos.y * game->world->map.width)].type = FLOOR;
		ent->ref_mm_tile->img = &game->mmap.mm_img[13];
		ent->type = ET_DOOR_UNLOCKED;	
	}
}

void	event_door_unlocked(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->world->map.tiles[(int)(ent->pos.x + ent->pos.y * game->world->map.width)].vis = -1;
		game->world->map.tiles[(int)(ent->pos.x + ent->pos.y * game->world->map.width)].type = DOOR;
		if (ent->ref_mm_tile->vertical == true)
			ent->ref_mm_tile->img = &game->mmap.mm_img[14];
		else
			ent->ref_mm_tile->img = &game->mmap.mm_img[12];
		ent->type = ET_DOOR_OPEN;
	}
}

void	event_door(t_door *door, t_game *game)
{
	if (door->locked)
		return ;
	door->closed = !door->closed;
	if (door->closed)
	{
		if (door->base.mm_tile->vertical == true)
			door->base.mm_tile->img = &game->mmap.mm_img[13];
		else
			door->base.mm_tile->img = &game->mmap.mm_img[11];
	}
	else
	{
		if (door->base.mm_tile->vertical == true)
			door->base.mm_tile->img = &game->mmap.mm_img[14];
		else
			door->base.mm_tile->img  = &game->mmap.mm_img[12];
	}
}
