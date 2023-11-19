/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:13:28 by clovell           #+#    #+#             */
/*   Updated: 2023/05/15 14:59:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "vector2.h"

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
}				t_texture;

void	pixel_set(t_texture data, int x, int y, int color);
int	pixel_get(t_texture data, int x, int y);
void	texture_draw_line(t_texture data, t_vec2 start, t_vec2 end, int colour);
void	texture_draw_square(t_texture data, t_vec2 start, t_vec2 width, int colour);


t_texture	texture_create(void *mlx, int width, int height);

t_texture	texture_copy(void *mlx, t_texture tex, const t_vec2 reg[2], int scale);

/* create a copy of 'tex' that has been rotated by 90-deg * 'rot' */
t_texture	texture_rotate(void *mlx, t_texture tex, int rot);

t_texture	texture_load(void *mlx, char *path);

#endif
