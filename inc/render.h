/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:37 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 20:55:16 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H
# include "vector2.h"
# include "texture.h"
# include "rect.h"
# include "app.h"

typedef struct s_game t_game;

/*** render_util.c ***/
void	rect_draw(const t_rect *aabb, int colour, t_texture rt);

/* Draws a texture to the screen */
void	texture_draw(t_app app, t_texture tex, t_vec2 pos);

/* Wall rendering
	floor_render.c
*/
void	render_floor(t_game *game);

/* Wall rendering
	wall_render.c
*/
void	render_wall(t_game *game);

/* loop.c */
// TODO: Rename as game_update
void	render(t_game *ctx);
#endif
