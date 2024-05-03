/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:56:06 by clovell           #+#    #+#             */
/*   Updated: 2024/05/04 01:51:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "entity.h"
#include "state.h"
#include "map.h"
#include "clmath.h"

// Function declarations
void	ent_task_orbit_update(t_ent_task_orbit *orbit, t_game *game);
void	ent_trigger_area_update(t_ent_trigger_area *area, t_game *game);
void	ent_door_update(t_door *door, t_game *game);

static const t_fn_entity_update	g_entity_updates[] = {
[ENT_DOOR] = (void *)ent_door_update,
[ENT_ENEMY] = (void *) NULL,
[ENT_TASK_ORBIT] = (void *)ent_task_orbit_update,
[ENT_TRIGGER_AREA] = (void *)ent_trigger_area_update,
};

static const size_t	g_entity_sizes[] = {
[ENT_DOOR] = sizeof(t_door),
[ENT_ENEMY] = sizeof(t_enemy),
[ENT_TASK_ORBIT] = sizeof(t_ent_task_orbit),
[ENT_TRIGGER_AREA] = sizeof(t_ent_trigger_area),
};

void	entity_update(t_game *game)
{
	t_list				*lst;
	t_fn_entity_update	fn;

	lst = game->world->entities;
	while (lst != NULL && lst->content != NULL)
	{
		fn = g_entity_updates[((t_entity *)lst->content)->type];
		if (fn)
			fn(lst->content, game);
		lst = lst->next;
	}
}

t_entity	*entity_create(t_world *world, t_entity_type type)
{
	void *const	data = malloc(g_entity_sizes[type]);

	ft_lstadd_front(&world->entities, ft_lstnew(data));
	*(t_entity *)data = (t_entity){.type = type, .pos = v2new(0, 0), 0};
	return (data);
}
