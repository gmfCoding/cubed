/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_fl_wrapper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:18:06 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 14:05:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "task.h"
#include "tasks/task_fl.h"
#include "state.h"

int	task_fl_setup(t_game *game, t_task *base)
{
	t_task_fl *const	task = (t_task_fl*)base;

	task->game = game;
	return (0);
}

int	task_fl_render(t_game *game, t_task *base)
{
	(void)base;
	five_lights(game);
	return (0);
}
