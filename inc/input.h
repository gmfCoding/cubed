/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:18:00 by clovell           #+#    #+#             */
/*   Updated: 2023/11/22 21:39:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INPUT_H
# define INPUT_H
#include <stdbool.h>
#include <inttypes.h>

#include "vector2i.h"
#include "keys.h"

typedef struct s_inputstate t_inputstate;
typedef struct s_inputctx t_inputctx;

struct s_inputctx
{
	uint8_t key_state[256];
	uint8_t special_state[256];
	uint8_t mouse_state[5];

	t_vec2i mouse;
	t_vec2i mouse_prev;

	int				frame;
};

typedef struct s_game t_game;

bool	input_keydown(t_game *game, int key);
bool	input_keyup(t_game *game, int key);
bool	input_keyheld(t_game *game, int key);
void	input_process(t_game *game);
uint8_t	*input_get_state(t_game *game, int *key);

#endif