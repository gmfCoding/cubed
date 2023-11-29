/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:18:00 by clovell           #+#    #+#             */
/*   Updated: 2023/11/25 19:32:10 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include <stdbool.h>
# include <inttypes.h>

# include "vector2i.h"
# include "keys.h"

typedef struct s_inputstate	t_inputstate;
typedef struct s_inputctx	t_inputctx;

struct s_inputctx
{
	uint8_t	key_state[KEY_REG_MAX];
	uint8_t	special_state[256];
	uint8_t	mouse_state[5];

	t_vec2i	mouse;
	t_vec2i	mouse_prev;

	int		frame;
};

bool	input_keydown(t_inputctx *input, int key);
bool	input_keyup(t_inputctx *input, int key);
bool	input_keyheld(t_inputctx *input, int key);
void	input_process(t_inputctx *input);
uint8_t	*input_get_state(t_inputctx *input, int *key);

void	input_setup(void *mlx, void *win, t_inputctx *input);
void	input_cb_key_press(int key, t_inputctx *game);
void	input_cb_key_release(int key, t_inputctx *game);
void	input_cb_mouse_press(int button, int x, int y, t_inputctx *game);
void	input_cb_mouse_release(int button, int x, int y, t_inputctx *game);
void	input_cb_mouse_move(int x, int y, t_inputctx *game);

#endif