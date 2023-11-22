/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:52:55 by clovell           #+#    #+#             */
/*   Updated: 2023/11/23 01:42:28 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "state.h"
#include "input.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void	input_setup(t_game *game)
{
	game->input = (t_inputctx){0};
	mlx_hook(game->win, ON_KEYDOWN, (1L<<0), (void *)input_cb_key_press, game);
	mlx_hook(game->win, ON_KEYUP, (1L<<1), (void *)input_cb_key_release, game);
	mlx_hook(game->win, ON_MOUSEDOWN, (1L<<2), (void *)input_cb_mouse_press, game);
	mlx_hook(game->win, ON_MOUSEUP, (1L<<3), (void *)input_cb_mouse_release, game);
	mlx_hook(game->win, ON_MOUSEMOVE, (1L<<6), (void *)input_cb_mouse_move, game);
	mlx_do_key_autorepeatoff(game->mlx);
}