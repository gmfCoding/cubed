/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:33:50 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 19:38:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "ui.h"
#include "input.h"

void	ui_process_draw(t_ui_context *ctx, t_inputctx *in, t_texture target)
{
	t_button	*curr;
	t_rect		aabb;
	int			i;
	int			col;
	int			key;

	key = input_keydown(in, MB_LEFT) + input_keyheld(in, MB_LEFT) * 2;
	i = -1;
	while (++i < (int)(sizeof(ctx->buttons) / sizeof(t_button)))
	{
		if (!curr->visible)
			continue ;
		curr = &ctx->buttons[i];
		col = curr->colour;
		aabb = curr->rect;
		if (curr->enabled && rect_contains_v2(aabb, in->mousef))
		{
			col = R_GREEN | R_ALPHA;
			if ((key & 1 || curr->repeat && key & 2) && curr->callback != NULL)
				curr->callback(curr, ctx);
		}
		rect_draw(aabb, target);
	}
}
