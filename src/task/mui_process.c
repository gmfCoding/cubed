/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 13:17:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

#include "vectorconv.h"
#include "tasks/mui.h"
#include "input.h"

void	mui_process_buttons(t_mui_ctx *ctx, t_inputctx *in)
{
	t_mui_button	*curr;
	int				i;
	bool			key[2];

	key[0] = input_keydown(in, MB_LEFT);
	key[1] = input_keyheld(in, MB_LEFT);
	i = -1;
	while (++i < ctx->len_buttons)
	{
		curr = &ctx->buttons[i];
		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
		{
			curr->on = false;
			if (curr->toggle && key[0])
				curr->on = !curr->on;
			else if (!curr->toggle && key[1])
				curr->on = true;
			if ((curr->toggle && key[0]) || (!curr->toggle && key[1]))
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
			if (held)
				curr->angle = (curr->drag_start.x - in->mousef.x) \
				+ (curr->drag_start.y - in->mousef.y);
			if (press)
				curr->drag_start = in->mousef;
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

	held = input_keyheld(in, MB_LEFT);
	i = -1;
	while (++i < ctx->len_sliders)
	{
		curr = &ctx->sliders[i];
		if (curr->base.unlock && rect_contains_v2(curr->base.rect, in->mousef))
		{
			if (!held)
				continue ;
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