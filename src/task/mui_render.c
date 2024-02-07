/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:59:35 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 19:41:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "clmath.h"
#include "tasks/mui.h"
#include "texture.h"
#include "render.h"

static void	mui_render_buttons(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_button	*curr;
	t_texture		target;
	int				i;

	i = -1;
	while (++i < ctx->len_buttons)
	{
		curr = &ctx->buttons[i];
		target = curr->base.def->tex[0];
		if (curr->on)
			target = curr->base.def->tex[3];
		texture_blit(target, *rt, curr->base.pos);
		rect_draw(&curr->base.rect, R_RED | R_ALPHA, *rt);
	}
}

static void	mui_render_dials(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_dial	*curr;
	t_texture	target;
	double		angle;
	int			frame;
	int			i;

	i = -1;
	while (++i < ctx->len_dials)
	{
		curr = &ctx->dials[i];
		angle = curr->angle;
		frame = ((int)(angle / (2 * M_PI) * curr->base.def->frames)) % curr->base.def->frames;
		if (frame > 0)
			frame = curr->base.def->frames - frame;
		target = curr->base.def->tex[abs(frame) % curr->base.def->frames];
		texture_blit(target, *rt, curr->base.pos);
		rect_draw(&curr->base.rect, R_RED | R_ALPHA, *rt);
	}
}

static void	mui_render_sliders(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_slider	*curr;
	t_texture		target;
	int				frame;
	int				i;

	i = -1;
	while (++i < ctx->len_sliders)
	{
		curr = &ctx->sliders[i];
		frame = (curr->value * curr->base.def->frames);
		target = curr->base.def->tex[frame];
		texture_blit(target, *rt, curr->base.pos);
		rect_draw(&curr->base.rect, R_RED | R_ALPHA, *rt);
	}
}

void	mui_render(t_mui_ctx *ctx, const t_texture *rt)
{
	mui_render_dials(ctx, rt);
	mui_render_sliders(ctx, rt);
	mui_render_buttons(ctx, rt);
}
