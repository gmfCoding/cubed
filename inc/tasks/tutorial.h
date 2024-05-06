/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:58:59 by clovell           #+#    #+#             */
/*   Updated: 2024/05/06 23:08:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rect.h"

typedef struct s_task_tip		t_task_tip;

struct	s_task_tip
{
	char		*content;
	t_rect		close;
	t_rect		region;
};

typedef struct s_task_tutorial	t_task_tutorial;

struct	s_task_tutorial
{
	t_task_tip	*tips;
	size_t		tips_len;
	t_vec2i		pos;

	int			active;
	char		**active_split;
	int			active_len;
};

typedef enum e_iter_func_ctrl
{
	ITER_STOP,
	ITER_CONTINUE,
	ITER_SKIP_NEXT,
	ITER_REPEAT,
	ITER_ERR,
}	t_iter_func_ctrl;

typedef t_iter_func_ctrl	(*t_iter_func)(void *element, void *ctx);

int		task_tut_instance(t_task_tutorial *new, t_task_tutorial *prefab);

void	task_tut_render(t_task_tutorial *tut, t_texture *rt);
