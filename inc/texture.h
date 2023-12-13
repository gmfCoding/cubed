/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:13:28 by clovell           #+#    #+#             */
/*   Updated: 2023/12/13 13:11:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "vector2.h"

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
}				t_texture;

# ifdef __linux__
// Full opaque colour (linux)
#  define R_ALPHA 0xff000000
#  else
// Full opaque colour (mac)
#  define R_ALPHA 0x00000000
# endif

// Full red colour
# define R_RED   0x00ff0000
// Full green colour
# define R_GREEN 0x0000ff00
// Full blue colour
# define R_BLUE  0x000000ff

// Red colour mask
# define M_RED   R_RED
// Green colour mask
# define M_GREEN R_GREEN
// Blue colour mask
# define M_BLUE  R_BLUE
// Alpha colour mask
# define M_APLHA 0xff000000

# define OF_ALPHA 24
# define OF_RED   16
# define OF_GREEN 8
# define OF_BLUE  0


// typedef struct s_col
// {
// 	uint8_t r;
// 	uint8_t g;
// 	uint8_t b;
// 	uint8_t a;
// } t_col;

int		colour_blend(int first, int second);

void	pixel_set_s(t_texture data, int x, int y, int color);
void	pixel_set(t_texture data, int x, int y, int color);

int		pixel_get_s(t_texture data, int x, int y);
int		pixel_get(t_texture data, int x, int y);

void	texture_draw_line(t_texture data, t_vec2 start, t_vec2 end, int colour);
void	texture_draw_square(t_texture data, t_vec2 start, t_vec2 width, int colour);

void    texture_blit(t_texture src, t_texture dst, t_vec2 pos);
void    texture_clear(t_texture src);

t_texture	texture_create(void *mlx, int width, int height);

t_texture	texture_copy(void *mlx, t_texture tex, const t_vec2 reg[2], int scale);

/* create a copy of 'tex' that has been rotated by 90-deg * 'rot' */
t_texture	texture_rotate(void *mlx, t_texture tex, int rot);

t_texture	texture_load(void *mlx, char *path);

#endif
