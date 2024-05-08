/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:40:15 by clovell           #+#    #+#             */
/*   Updated: 2024/05/07 19:41:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "keys.h"
#include "input.h"
#include "state.h"

void	handle_closing(t_game *game, t_task *task)
{
	const t_vec2i	mouse = game->input.mouse;
	const int		margin_tl = (SCR_WIDTH - 800) / 2;
	const int		margin_br = SCR_WIDTH - margin_tl;

	if (input_keydown(&game->input, MB_LEFT))
	{
		if (!(mouse.x < margin_tl || mouse.y < margin_tl || \
		mouse.x > margin_br || mouse.y > margin_br))
			return ;
		task->show = false;
		task->init = false;
		game->player.state = CAN_MOVE;
	}
}
