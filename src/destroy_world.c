/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:44:11 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 15:32:35 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "task.h"
#include "tasks/task_orbit.h"

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
	{
		printf("freeing task_orbit!\n");
		mui_destroy(((t_task_orbit *)task)->mui, NULL);
		free(task);
	}
	else
		free(task);
}

void	world_destroy(t_game *game)
{
	ft_lstclear(&game->world->tasks, destroy_task);
	ft_lstclear(&game->world->entities, destroy_entity);
	free(game->world);
}
