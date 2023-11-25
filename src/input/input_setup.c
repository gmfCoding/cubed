/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:52:55 by clovell           #+#    #+#             */
/*   Updated: 2023/11/25 19:42:45 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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

void	input_setup(void *mlx, void *win, t_inputctx *input)
{
	*input = (t_inputctx){0};
	mlx_hook(win, KDOWN, (1L << 0), (void *)input_cb_key_press, input);
	mlx_hook(win, KUP, (1L << 1), (void *)input_cb_key_release, input);
	mlx_hook(win, MDOWN, (1L << 2), (void *)input_cb_mouse_press, input);
	mlx_hook(win, MUP, (1L << 3), (void *)input_cb_mouse_release, input);
	mlx_hook(win, MMOVE, (1L << 6), (void *)input_cb_mouse_move, input);
	mlx_do_key_autorepeatoff(mlx);
}
