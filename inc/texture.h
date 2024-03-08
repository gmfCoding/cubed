/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:13:28 by clovell           #+#    #+#             */
/*   Updated: 2024/03/09 03:45:59 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include "vector2.h"
# include "pixel.h"
# include "structs/s_texture.h"

void	texture_draw_line(t_texture data, t_vec2 start, t_vec2 end, int colour);
void	texture_draw_square(t_texture data, t_vec2 start, t_vec2 width, int colour);

void	texture_blit_s(t_texture src, t_texture dst, t_vec2 pos, int scale);
void    texture_blit(t_texture src, t_texture dst, t_vec2 pos);
void    texture_clear(t_texture src, int colour);

t_texture	texture_create(void *mlx, int width, int height);

t_texture	texture_copy(void *mlx, t_texture tex, const t_vec2 reg[2], int scale);

/* create a copy of 'tex' that has been rotated by 90-deg * 'rot' */
t_texture	texture_rotate(void *mlx, t_texture tex, int rot);

t_texture	texture_load(void *mlx, char *path);

#endif
