/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/28 17:25:13 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <math.h>

#include "vectorconv.h"
#include "tasks/mui.h"
#include "input.h"
#include "rect.h"
#include "clmath.h"

void	mui_press_button(t_mui_button *curr, t_vec2 mouse)
{
	curr->on = !curr->on;
	curr->base.anim = 0;
}

void	mui_hold_dial(t_mui_dial *curr, t_vec2 mouse)
{
	t_vec2	centre;
	t_vec2	dmpos;

	curr->prev_angle = curr->curr_angle;
	centre = v2muls(v2sub(curr->base.rect.max, curr->base.rect.min), 0.5);
	centre = v2add(curr->base.rect.min, centre);
	dmpos = v2sub(mouse, centre);
	curr->curr_angle = v2x2ang(dmpos);
	curr->angle += angle_diff(curr->prev_angle, curr->curr_angle);
}

void	mui_hold_slider(t_mui_slider *curr, t_vec2 mouse)
{
	int				i;
	bool			held;

	curr->value = fmax(0, fmin(0.99, v2invlerp(curr->start, curr->end, mouse)));
}

/* Returns the mui component under the mouse cursor position. */
t_mui_base	*mui_hover(t_mui_ctx *ctx, t_vec2 mouse)
{
	t_mui_base	*base;
	int			i;
	int			j;

	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		i = -1;
		while (++i < ctx->lengths[j])
		{
			base = (t_mui_base *)((char *)(ctx->all[j]) + ctx->sizes[j] * i);
			if (!rect_contains_v2(base->rect, mouse))
				continue ;
			return (base);
		}
	}
	return (NULL);
}


void	mui_process(t_mui_ctx *ctx, t_inputctx *in)
{
	static t_mui_base	*base = NULL;
	int					key;

	key = input_keydown(in, MB_LEFT) + input_keyheld(in, MB_LEFT) * 2;
	if (key & 1)
		base = mui_hover(ctx, in->mousef);
	if (!base)
		return ;
	if (base->type == MUI_BUTTON && (key & 1))
	{
		mui_press_button((void *)base, in->mousef);
		mui_button_group_off(ctx, in, (void *)base);
	}
	else if (base->type == MUI_DIAL && (key & 2))
		mui_hold_dial((void *)base, in->mousef);
	else if (base->type == MUI_SLIDE && (key & 2))
		mui_hold_slider((void *)base, in->mousef);
	else if (base->type == MUI_SLIDE && ((t_mui_slider *)base)->elastic)
		((t_mui_slider *)base)->value = ((t_mui_slider *)base)->rest;
	return ;
}