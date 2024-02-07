/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:01:30 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 00:18:40 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "tasks/mui.h"

void	mui_clone(const t_mui_ctx *src, t_mui_ctx *dst)
{
	int	i;

	*dst = *src;
	dst->buttons = malloc(sizeof(t_mui_button) * dst->len_buttons);
	i = -1;
	while (++i < src->len_buttons)
	{
		dst->buttons[i] = src->buttons[i];
	}
	dst->sliders = malloc(sizeof(t_mui_slider) * dst->len_sliders);
	i = -1;
	while (++i < src->len_sliders)
	{
		dst->sliders[i] = src->sliders[i];
	}
	dst->dials = malloc(sizeof(t_mui_dial) * dst->len_dials);
	i = -1;
	while (++i < src->len_dials)
	{
		dst->dials[i] = src->dials[i];
	}
	dst->heap = true;
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
