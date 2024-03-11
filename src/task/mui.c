/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/28 17:40:12 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "tasks/mui.h"
#include "rect.h"

void	mui_clone(const t_mui_ctx *src, t_mui_ctx *dst)
{
	char		*src_iter;
	char		*dst_iter;
	int			j;
	int			i;

	*dst = *src;
	i = -1;
	while (++i < MUI_LEN_TYPES)
		dst->all[i] = malloc(src->sizes[i] * src->lengths[i]);
	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		i = -1;
		src_iter = (void *)&src->all[j][0];
		dst_iter = (void *)&dst->all[j][0];
		dst->lengths[j] = src->lengths[j];
		dst->sizes[j] = src->sizes[j];
		while (++i < src->lengths[j])
		{
			ft_memcpy(dst_iter, src_iter, src->sizes[j]);
			src_iter = &src_iter[0] + src->sizes[j];
			dst_iter = &dst_iter[0] + src->sizes[j];
		}
	}
	mui_init(dst);
}

void	mui_init(t_mui_ctx *ctx)
{
	t_mui_any	iter;
	int			j;
	int			i;

	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		i = -1;
		iter.base = ctx->all[j];
		while (++i < ctx->lengths[j])
		{
			iter.base->rect = v4muls(iter.base->rect, 1.0 / ctx->oscale);
			iter.base->rect = v4muls(iter.base->rect, ctx->scale);
			iter.base->rect = rect_offset(iter.base->rect, ctx->offset);
			if (iter.base->type == MUI_SLIDE)
				iter.s->start = iter.base->rect.min;
			if (iter.base->type == MUI_SLIDE)
				iter.s->end = v2new(iter.p->rect.min.x, iter.p->rect.max.y);
			iter.base = (void *)((char *)iter.base + ctx->sizes[j]);
		}
	}
}

void	mui_def_preload(t_app *app, t_mui_ctx *ctx)
{
	t_mui_base	*base;
	int			i;
	int			j;

	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		base = ctx->all[j];
		i = -1;
		while (++i < ctx->lengths[j])
		{
			base->def = def_tex_get_def(app, base->id);
			base = (void *)((char *)base + ctx->sizes[j]);
		}
	}
}

void	mui_destroy(t_mui_ctx *mui, t_mui_ctx **store, bool heap)
{
	free(mui->sliders);
	free(mui->buttons);
	free(mui->dials);
	free(mui);
	if (store != NULL)
		*store = NULL;
}
