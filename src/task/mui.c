/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/11 22:42:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "tasks/mui.h"

void	mui_clone(const t_mui_ctx *src, t_mui_ctx *dst)
{
	char		*src_iter;
	char		*dst_iter;
	int			j;
	int			i;

	i = -1;
	while (++i < MUI_LEN_TYPES)
		dst->all[i] = malloc(src->sizes[i] * src->lengths[i]);
	j = -1;
	while (++j < MUI_LEN_TYPES)
	{
		i = -1;
		src_iter = &src->all[j][0];
		dst_iter = &dst->all[j][0];
		dst->lengths[j] = src->lengths[j];
		dst->sizes[j] = src->sizes[j];
		while (++i < src->lengths[j])
		{
			ft_memcpy(dst_iter, src_iter, src->sizes[j]);
			src_iter = &src_iter[0] + src->sizes[j];
			dst_iter = &dst_iter[0] + src->sizes[j];
		}
	}
	dst->heap = true;
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
	if (mui->heap)
	{
		free(mui->sliders);
		free(mui->buttons);
		free(mui->dials);
	}
	if (heap)
		free(mui);
	if (store != NULL)
		*store = NULL;
}
