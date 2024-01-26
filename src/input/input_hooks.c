/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:40:25 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 05:44:07 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "state.h"
#include "input.h"

void	input_cb_key_press(int key, t_inputctx *input)
{
	uint8_t	*state;

	state = input_get_state(input, &key);
	state[key] |= KEY_MASK_PRESS;
}

void	input_cb_key_release(int key, t_inputctx *input)
{
	uint8_t	*state;

	state = input_get_state(input, &key);
	state[key] |= KEY_MASK_RELEASE;
}

void	input_cb_mouse_press(int button, int x, int y, t_inputctx *input)
{
	uint8_t	*state;
	int		masked;

	(void)x;
	(void)y;
	masked = button | KEY_MB_MASK;
	state = input_get_state(input, &masked);
	state[button] |= KEY_MASK_PRESS;
}

void	input_cb_mouse_release(int button, int x, int y, t_inputctx *input)
{
	uint8_t	*state;
	int		masked;

	(void)x;
	(void)y;
	masked = button | KEY_MB_MASK;
	state = input_get_state(input, &masked);
	state[button] |= KEY_MASK_RELEASE;
}

void	input_cb_mouse_move(int x, int y, t_inputctx *input)
{
	input->mouse = v2inew(x, y);
}
