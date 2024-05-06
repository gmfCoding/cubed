/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_fl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:58:32 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 22:18:19 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TASK_FL_H
# define TASK_FL_H
# include "cubed.h"
# include "task.h"

typedef struct s_task_fl
{
	t_task			task;
	t_game			*game;
}	t_task_fl;

int	task_fl_setup(t_game *game, t_task *base);
int	task_fl_render(t_game *game, t_task *base);

#endif
