/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_process_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:24:32 by clovell           #+#    #+#             */
/*   Updated: 2024/04/16 18:36:44 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tasks/mui.h"

void	mui_button_group_off(t_mui_ctx *ctx, t_mui_button *last)
{
	int	i;

	i = -1;
	while (++i < ctx->len_buttons)
	{
		if (ctx->buttons[i].group <= 0)
			continue ;
		if (&ctx->buttons[i] != last && ctx->buttons[i].group == last->group)
		{
			ctx->buttons[i].on = false;
		}
	}
}
