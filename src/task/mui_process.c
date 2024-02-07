/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 02:34:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <math.h>

#include "vectorconv.h"
#include "tasks/mui.h"
#include "input.h"
#include "rect.h"
#include "clmath.h"

// void	mui_process_buttons(t_mui_ctx *ctx, t_inputctx *in)
// {
// 	t_mui_button	*curr;
// 	int				i;
// 	bool			key;

// 	key = input_keydown(in, MB_LEFT);
// 	if (!key)
// 		return ;
// 	i = -1;
// 	while (++i < ctx->len_buttons)
// 	{
// 		curr = &ctx->buttons[i];
// 		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
// 		{
// 			curr->on = !curr->on;
// 			curr->base.anim = 0;
// 		}
// 	}
// }

// void	mui_process_dials(t_mui_ctx *ctx, t_inputctx *in)
// {
// 	t_mui_dial		*curr;
// 	int				i;
// 	bool			press;
// 	bool			held;

// 	press = input_keydown(in, MB_LEFT);
// 	held = input_keyheld(in, MB_LEFT);

// 	i = -1;
// 	while (++i < ctx->len_dials)
// 	{
// 		curr = &ctx->dials[i];
// 		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
// 		{
// 			// if (press)
// 			// 	curr->drag_start = in->mousef;
// 			// if (held)
// 			// 	curr->angle = sin(curr->drag_start.x - in->mousef.x);
// 			if (held)
// 			{
// 				curr->prev_angle = curr->curr_angle;
// 				//curr->curr_angle = v2x2ang(in->mousef);

// 				//printf("asdasd:%f\n", v2sub(curr->base.pos, v2new(curr->base.rect.max.x - curr->base.rect.min.x, curr->base.rect.max.y - curr->base.rect.min.y)).x);
// 				t_vec2 centre = v2add(curr->base.pos, v2new((curr->base.rect.max.x - curr->base.rect.min.x) / 2, (curr->base.rect.max.y - curr->base.rect.min.y) / 2));
// 				t_vec2 dmpos = v2sub(in->mousef, centre);
// 				curr->curr_angle = v2x2ang(dmpos);
// 				// printf("mouse:%f %f\n", in->mousef.x, in->mousef.y);
// 				// printf("centr:%f %f\n", centre.x, centre.y);
// 				double diff = angle_diff(curr->prev_angle, curr->curr_angle);
// 				curr->angle += diff;
// 				// if (diff > 0)
// 				// 	printf("Anti clockwise\n");
// 				// else if (diff < 0)
// 				// 	printf("Clockwise\n");
// 			}
// 			else
// 			{
// 				curr->prev_angle = curr->curr_angle;
// 				//curr->curr_angle = 0;
// 			}
// 			// printf("diff:%f\n", angle_diff(curr->prev_angle, curr->curr_angle));
// 			// printf("prev:%f\n", curr->prev_angle);
// 			// printf("curr:%f\n", curr->curr_angle);
// 			printf("angl:%f\n", curr->angle);
// 		}
// 	}
// }

// void	mui_process_sliders(t_mui_ctx *ctx, t_inputctx *in)
// {
// 	t_mui_slider	*curr;
// 	int				i;
// 	bool			held;
// 	t_vec2			proj;
// 	double			t;

// 	held = input_keydown(in, MB_LEFT);
// 	if (!held)
// 		return ;
// 	i = -1;
// 	while (++i < ctx->len_sliders)
// 	{
// 		curr = &ctx->sliders[i];
// 		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
// 		{
// 			t = v2dot(v2divs(in->mousef, v2mag(curr->start)), \
// 			v2norm(curr->start));
// 			proj = v2lerp(curr->start, curr->end, t);
// 			curr->value = v2dist(proj, curr->end) \
// 			/ v2dist(curr->start, curr->end);
// 		}
// 	}
// }

// void	mui_process(t_mui_ctx *ctx, t_inputctx *in)
// {
// 	mui_process_buttons(ctx, in);
// 	mui_process_dials(ctx, in);
// 	mui_process_sliders(ctx, in);
// }

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
	centre = v2add(curr->base.pos, centre);
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
		mui_press_button((void *)base, in->mousef);
	else if (base->type == MUI_DIAL && (key & 2))
		mui_hold_dial((void *)base,  in->mousef);
	else if (base->type == MUI_SLIDE && (key & 2))
		mui_hold_slider((void *)base, in->mousef);
	return ;
}
