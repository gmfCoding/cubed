/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:56:06 by clovell           #+#    #+#             */
/*   Updated: 2024/03/18 23:32:49 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "entity.h"
#include "state.h"
#include "map.h"
#include "clmath.h"
typedef void (*t_fn_entity_update)(t_entity *entity, t_game *game);

// void	ent_door_update(t_door *door, t_game *game)
// {
// 	t_vec2	pct;
// 	bool	vert;
// 	// if (door->closed)
// 	// 	door->percent += door->speed;
// 	// else
// 	// 	door->percent -= door->speed;
// 	// door->percent = fclamp(0.0, 1.0, door->percent);
// 	door->percent = 0.5;
// 	vert = map_get_tile_refv(&game->world->map, \
// 	v2add(door->base.pos, v2new(1, 0)))->type == FLOOR;
// 	door->base.sprite->pos = v2add(door->base.pos, v2new(0.5, 0));
// 	pct = v2new(0.5 * door->percent, 0);
// 	if (vert)
// 		pct = v2new(0, door->percent);
// 	door->base.sprite->s1 = v2add(door->base.sprite->pos, pct);
// 	door->base.sprite->s2 = door->base.sprite->pos;
// }

void	ent_door_update(t_door *door, t_game *game)
{
	t_vec2	pct;
	bool	vert;
	// if (door->closed)
	// 	door->percent += door->speed;
	// else
	// 	door->percent -= door->speed;
	// door->percent = fclamp(0.0, 1.0, door->percent);
	door->percent = 1;
	vert = map_get_tile_refv(&game->world->map, \
	v2add(door->base.pos, v2new(1, 0)))->type == FLOOR;
	pct = v2new(0.5, 0);
	if (vert)
		pct = v2new(0, 0.5);
	door->base.sprite->pos = v2add(door->base.pos, v2clock(pct));
	pct = v2muls(pct, door->percent * 2);
	door->base.sprite->s1 = v2add(door->base.sprite->pos, pct);
	door->base.sprite->s2 = door->base.sprite->pos;
}

static const t_fn_entity_update	g_entity_updates[] = {
	[ENT_DOOR] = ent_door_update,
};

static const size_t	g_entity_sizes[] = {
	[ENT_DOOR] = sizeof(t_door),
	[ENT_ENEMY] = sizeof(t_enemy),
};

void	entity_update(t_game *game)
{
	t_list	*lst;

	lst = game->world->entities;
	while (lst != NULL && lst->content != NULL)
	{
		g_entity_updates[((t_entity *)lst->content)->type](lst->content, game);
		lst = lst->next;
	}
}

t_entity	*entity_create(t_world *world, t_entity_type type)
{
	void	*const data = malloc(g_entity_sizes[type]);

	ft_lstadd_front(&world->entities, ft_lstnew(data));
	*(t_entity *)data = (t_entity){.type = type, .pos = v2new(0, 0), 0};
	return (data);
}
