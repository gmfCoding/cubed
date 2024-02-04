/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:18:06 by clovell           #+#    #+#             */
/*   Updated: 2024/02/04 19:16:56 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "task.h"
#include "render.h"
#include <stdio.h>

int	task_orbit_setup(t_game *game, t_task *task)
{
	t_task_orbit *const	t = (t_task_orbit*)task;
	printf("task_setup:%s", task->name);
	t->pro_btn = (t_sprite){.pos = v2new(0, 0), .tex = texture_load(game->app.mlx, "assets/debug.xpm")};
	return (0);
}

int	task_orbit_render(t_game *game, t_task *task)
{
	(void)game;
	(void)task;
	return (0);
}