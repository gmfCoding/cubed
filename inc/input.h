/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:18:00 by clovell           #+#    #+#             */
/*   Updated: 2023/11/22 20:47:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INPUT_H
# define INPUT_H

#include <stdbool.h>
#include "vector2i.h"
#include "keys.h"
#include "state.h"

typedef struct s_inputstate t_inputstate;
typedef struct s_inputctx t_inputctx;

struct s_inputstate
{
	bool key_state[256];
	bool special_state[256];
	bool mouse_state[5];
	t_vec2i mouse;
};

struct s_inputctx
{
	t_inputstate curr;
	t_inputstate prev;
};



typedef struct s_game t_game;

bool	input_keydown(t_game *game, int key);
bool	input_keyup(t_game *game, int key);
bool	input_keyheld(t_game *game, int key);
void	input_process(t_game *game);
int		*input_get_state(t_game *game, int *key);

#endif