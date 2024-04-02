/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:59:35 by clovell           #+#    #+#             */
/*   Updated: 2024/02/19 19:34:39 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include "clmath.h"
#include "tasks/mui.h"
#include "texture.h"
#include "render.h"

static void	mui_frame_buttons(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_button	*curr;
	int				i;

	i = -1;
	while (++i < ctx->len_buttons)
	{
		curr = &ctx->buttons[i];
		curr->base.frame = 0;
		if (curr->on)
			curr->base.frame = 3;
	}
}

static void	mui_frame_dials(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_dial	*curr;
	double		angle;
	int			frame;
	int			i;

	i = -1;
	while (++i < ctx->len_dials)
	{
		curr = &ctx->dials[i];
		angle = curr->angle;
		frame = ((int)(angle / (M_PI * 2) * (curr->base.def->frames))) \
		% curr->base.def->frames;
		if (frame > 0)
			frame = curr->base.def->frames - frame;
		curr->base.frame = abs(frame) % curr->base.def->frames;
	}
}

static void	mui_frame_sliders(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_slider	*curr;
	int				frame;
	int				i;

	i = -1;
	while (++i < ctx->len_sliders)
	{
		curr = &ctx->sliders[i];
		curr->base.frame = (curr->value * curr->base.def->frames);
	}
}

static void	mui_render_all(t_mui_ctx *ctx, const t_texture *rt)
{
	t_mui_base	*base;
	t_texture	target;
	int			i;
	int			j;

	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		base = ctx->all[j];
		i = -1;
		while (++i < ctx->lengths[j])
		{
			target = base->def->tex[base->frame % base->def->frames];
			texture_blit(target, *rt, base->pos);
			base = (void *)((char *)base + ctx->sizes[j]);
		}
	}
}

void	mui_render(t_mui_ctx *ctx, const t_texture *rt)
{
	mui_frame_dials(ctx, rt);
	mui_frame_sliders(ctx, rt);
	mui_frame_buttons(ctx, rt);
	mui_render_all(ctx, rt);
}
