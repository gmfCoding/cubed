/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:16:59 by clovell           #+#    #+#             */
/*   Updated: 2024/04/10 17:44:43 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "task.h"
#include "tasks/task_orbit.h"
#include "tasks/task_fl.h"

int	task_orbit_setup(t_game *game, t_task *task);
int	task_orbit_render(t_game *game, t_task *task);

static const t_task *const	g_tasks[TASK_LEN] = {
	(t_task*)&(t_task_orbit){.task.name = "task_orbit",
	.task.size = sizeof(t_task_orbit),
	.task.key = KEY_E,
	.task.func = task_orbit_render,
	.task.setup = task_orbit_setup},

	(t_task*)&(t_task_fl){.task.name = "task_fl",
	.task.size = sizeof(t_task_orbit),
	.task.key = KEY_E,
	.task.func = task_fl_render,
	.task.setup = task_fl_setup},
};

t_task	*task_find(t_game *game, char *name)
{
	t_task	*task;
	t_list	*curr;

	curr = game->tasks;
	while (curr != NULL)
	{
		task = (t_task *)curr->content;
		if (task)
		{
			if (task->name && ft_strcmp(task->name, name) == 0)
				return (task);
		}
		curr = curr->next;
	}
	return (NULL);
}

void	task_process(t_game *game)
{
	t_task	*task;
	t_list	*curr;

	curr = game->tasks;
	while (curr != NULL)
	{
		task = (t_task *)curr->content;
		if (task)
			task->func(game, task);
		curr = curr->next;
	}
}

t_task	*task_create_or_find(t_game *game, char *name)
{
	t_task	*task;
	ssize_t	i;

	if (name == NULL)
		return (NULL);
	task = task_find(game, name);
	if (task)
		return (task->setup(game, task), task);
	printf("Couldn't find task: %s\n", name);
	i = -1;
	while (++i < sizeof(g_tasks) / sizeof(*g_tasks))
	{
		if (!g_tasks[i]->name || ft_strcmp(g_tasks[i]->name, name) != 0)
			continue ;
		task = malloc(g_tasks[i]->size);
		*task = *g_tasks[i];
		ft_lstadd_front(&game->tasks, ft_lstnew(task));
		task->setup(game, task);
		printf("Creating task: %s\n", name);
		return (task);
	}
	return (NULL);
}
