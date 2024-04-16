/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:52:55 by clovell           #+#    #+#             */
/*   Updated: 2024/04/08 01:02:03 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "state.h"
#include "input.h"

#define KDOWN 2
#define KUP 3
#define MDOWN 4
#define MUP 5
#define MMOVE 6
#define EXPOSE 12
#define DESTROY 17

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
