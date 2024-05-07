/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:44:11 by clovell           #+#    #+#             */
/*   Updated: 2024/05/07 19:44:41 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "task.h"

void	destroy_entity(void *ent)
{
	const t_entity	*entity = (t_entity *)ent;
	const t_enemy	*as_enemy = (t_enemy *)entity;

	if (entity->type == ENT_ENEMY)
	{
		if (as_enemy->path != NULL)
			free(as_enemy->path);
	}
	free(ent);
}

void	destroy_task(void *ent)
{
	const t_task	*task = (t_task *)ent;

	if (ft_strcmp(task->name, "task_orbit") == 0)
		free(task);
	else
		free(task);
}

void	world_destroy(t_game *game)
{
	ft_lstclear(&game->world->tasks, destroy_entity);
	ft_lstclear(&game->world->entities, destroy_entity);
	free(game->world);
}
