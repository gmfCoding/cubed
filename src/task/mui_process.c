/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 19:54:06 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <math.h>

#include "vectorconv.h"
#include "tasks/mui.h"
#include "input.h"
#include "rect.h"
#include "clmath.h"

void	mui_process_buttons(t_mui_ctx *ctx, t_inputctx *in)
{
	t_mui_button	*curr;
	int				i;
	bool			key;

	key = input_keydown(in, MB_LEFT);
	if (!key)
		return ;
	i = -1;
	while (++i < ctx->len_buttons)
	{
		curr = &ctx->buttons[i];
		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
		{
			curr->on = !curr->on;
			curr->base.anim = 0;
		}
	}
}

void	mui_process_dials(t_mui_ctx *ctx, t_inputctx *in)
{
	t_mui_dial		*curr;
	int				i;
	bool			press;
	bool			held;

	press = input_keydown(in, MB_LEFT);
	held = input_keyheld(in, MB_LEFT);

	i = -1;
	while (++i < ctx->len_dials)
	{
		curr = &ctx->dials[i];
		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
		{
			// if (press)
			// 	curr->drag_start = in->mousef;
			// if (held)
			// 	curr->angle = sin(curr->drag_start.x - in->mousef.x);
			if (held)
			{
				curr->prev_angle = curr->curr_angle;
				//curr->curr_angle = v2x2ang(in->mousef);

				//printf("asdasd:%f\n", v2sub(curr->base.pos, v2new(curr->base.rect.max.x - curr->base.rect.min.x, curr->base.rect.max.y - curr->base.rect.min.y)).x);
				t_vec2 centre = v2add(curr->base.pos, v2new((curr->base.rect.max.x - curr->base.rect.min.x) / 2, (curr->base.rect.max.y - curr->base.rect.min.y) / 2));
				t_vec2 dmpos = v2sub(in->mousef, centre);
				curr->curr_angle = v2x2ang(dmpos);
				// printf("mouse:%f %f\n", in->mousef.x, in->mousef.y);
				// printf("centr:%f %f\n", centre.x, centre.y);
				double diff = angle_diff(curr->prev_angle, curr->curr_angle);
				curr->angle += diff;
				// if (diff > 0)
				// 	printf("Anti clockwise\n");
				// else if (diff < 0)
				// 	printf("Clockwise\n");
			}
			else
			{
				curr->prev_angle = curr->curr_angle;
				//curr->curr_angle = 0;
			}
			// printf("diff:%f\n", angle_diff(curr->prev_angle, curr->curr_angle));
			// printf("prev:%f\n", curr->prev_angle);
			// printf("curr:%f\n", curr->curr_angle);
			printf("angl:%f\n", curr->angle);
		}
	}
}

void	mui_process_sliders(t_mui_ctx *ctx, t_inputctx *in)
{
	t_mui_slider	*curr;
	int				i;
	bool			held;
	t_vec2			proj;
	double			t;

	held = input_keydown(in, MB_LEFT);
	if (!held)
		return ;
	i = -1;
	while (++i < ctx->len_sliders)
	{
		curr = &ctx->sliders[i];
		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
		{
			t = v2dot(v2divs(in->mousef, v2mag(curr->start)), \
			v2norm(curr->start));
			proj = v2lerp(curr->start, curr->end, t);
			curr->value = v2dist(proj, curr->end) \
			/ v2dist(curr->start, curr->end);
		}
	}
}

void	mui_process(t_mui_ctx *ctx, t_inputctx *in)
{
	mui_process_buttons(ctx, in);
	mui_process_dials(ctx, in);
	mui_process_sliders(ctx, in);
}
