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
#ifndef RENDER_H
# define RENDER_H
# include "vector2.h"
# include "texture.h"
# include "state.h"

/*** render_util.c ***/

/* Draws a texture to the screen */
void	texture_draw(t_game *gs, t_texture tex, t_vec2 pos);

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
