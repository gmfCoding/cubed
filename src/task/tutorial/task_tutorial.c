/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_tutorial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:35:50 by clovell           #+#    #+#             */
/*   Updated: 2024/03/04 20:00:24 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "tasks/tutorial.h"
#include "texture.h"
#include "vector2i.h"
#include "vectorconv.h"

int	task_tut_instance(t_task_tutorial *new, t_task_tutorial *prefab)
{
	*new = *prefab;
}

int	ft_line_longest(char *str)
{
	int	max;
	int	curr;

	max = 0;
	curr = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			if (max < curr)
				max = curr;
			curr = 0;
		}
		curr++;
		str++;
	}
	return (max);
}

typedef enum e_iter_func_ctrl
{
	ITER_STOP,
	ITER_CONTINUE,
	ITER_SKIP_NEXT,
	ITER_REPEAT,
	ITER_ERR,
}	t_iter_func_ctrl;

typedef t_iter_func_ctrl	(*t_iter_func)(void *element, void *ctx);

int	ft_split_func_iter(char **str, t_iter_func func, void *ctx)
{
	t_iter_func_ctrl	prev;

	prev = ITER_CONTINUE;
	while (*str != NULL)
	{
		prev = func(*str, ctx);
		if (prev == ITER_ERR || prev == ITER_STOP)
			break ;
		if (prev != ITER_REPEAT)
			str++;
		if (*str == NULL)
			break ;
		if (prev == ITER_SKIP_NEXT)
			str++;
	}
	return (prev == ITER_ERR);
}

t_iter_func_ctrl	ft_iter_strlen(char *element, void *ctx)
{
	const char	*str = element;
	int *const	max = ctx;
	const int	len = ft_strlen(str);

	if (*max < len)
		*max = len;
	return (ITER_CONTINUE);
}

void	task_tut_render(t_task_tutorial *tut, t_texture *rt)
{
	int	tip_size;

	if (tut->active >= tut->tips_len)
		tut->active = 0;
	if (tut->active < 0)
		tut->active = tut->tips_len - 1;
	tip_size = 0;
	ft_split_func_iter(tut->active_split, ft_iter_strlen, &tip_size);
	texture_draw_square(*rt, v2sub(v2itov2(tut->pos), (t_vec2){tip_size, 0}), (t_vec2){tip_size, 0}, 0x00111111 | R_ALPHA);
}
