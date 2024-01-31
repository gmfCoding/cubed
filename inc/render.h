/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:37 by clovell           #+#    #+#             */
/*   Updated: 2024/01/31 16:51:41 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILS_H
# define UTILS_H
# include "vector2.h"
# include "texture.h"
# include "state.h"

void    texture_draw(t_game *gs, t_texture tex, t_vec2 pos);

void	on_key_press(int key, t_game *game);
void	on_mouse(int key, int x, int y, t_game *game);
void	on_mouse_move(int x, int y, t_game *game);

void	render_floor(t_game *game);
void	render(t_game *ctx);
#endif
