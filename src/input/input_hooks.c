/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 21:40:25 by clovell           #+#    #+#             */
/*   Updated: 2023/11/23 21:40:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "state.h"
#include "input.h"

void	input_cb_key_press(int key, t_game *game)
{
	uint8_t	*state;

	state = input_get_state(game, &key);
	state[key] |= KEY_MASK_PRESS;
}

void	input_cb_key_release(int key, t_game *game)
{
	uint8_t	*state;

	state = input_get_state(game, &key);
	state[key] |= KEY_MASK_RELEASE;
}

void	input_cb_mouse_press(int button, int x, int y, t_game *game)
{
	uint8_t	*state;
	int		masked;

	masked = button | KEY_MB_MASK;
	state = input_get_state(game, &masked);
	state[button] |= KEY_MASK_PRESS;
}

void	input_cb_mouse_release(int button, int x, int y, t_game *game)
{
	uint8_t	*state;
	int		masked;

	masked = button | KEY_MB_MASK;
	state = input_get_state(game, &masked);
	state[button] |= KEY_MASK_RELEASE;
}

void	input_cb_mouse_move(int x, int y, t_game *game)
{
	game->input.mouse = v2inew(x, y);
}
