/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:37 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 19:37:58 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H
# include "vector2.h"
# include "texture.h"
# include "state.h"

typedef struct s_rect t_rect;

void	texture_draw(t_app app, t_texture tex, t_vec2 pos);
void	rect_draw(const t_rect *aabb, int colour, t_texture rt);

void	on_key_press(int key, t_game *game);
void	on_mouse(int key, int x, int y, t_game *game);
void	on_mouse_move(int x, int y, t_game *game);

void	render_floor(t_game *game);
void	render(t_game *ctx);
#endif