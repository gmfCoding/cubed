/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:52:55 by clovell           #+#    #+#             */
/*   Updated: 2023/11/23 21:39:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include "input.h"

enum {
	KDOWN = 2,
	KUP = 3,
	MDOWN = 4,
	MUP = 5,
	MMOVE = 6,
	EXPOSE = 12,
	DESTROY = 17
};

void	input_setup(t_game *game)
{
	game->input = (t_inputctx){0};
	mlx_hook(game->win, KDOWN, (1L << 0), (void *)input_cb_key_press, game);
	mlx_hook(game->win, KUP, (1L << 1), (void *)input_cb_key_release, game);
	mlx_hook(game->win, MDOWN, (1L << 2), (void *)input_cb_mouse_press, game);
	mlx_hook(game->win, MUP, (1L << 3), (void *)input_cb_mouse_release, game);
	mlx_hook(game->win, MMOVE, (1L << 6), (void *)input_cb_mouse_move, game);
	mlx_do_key_autorepeatoff(game->mlx);
}
