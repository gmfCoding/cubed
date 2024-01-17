/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:11:47 by clovell           #+#    #+#             */
/*   Updated: 2024/01/17 16:24:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "texture.h"

#ifdef __linux__

static void	texture_init(t_texture tex)
{

}
#else

static void	texture_init(t_texture tex)
{
	int	x;
	int	y;
	int	c;

	y = -1;
	while (++y < tex.height)
	{
		x = -1;
		while (++x < tex.width)
		{
			c = pixel_get(tex, x, y);
			c = ((255 - (c >> OF_ALPHA)) << OF_ALPHA) | (c & 0x00FFFFFF);
			pixel_set(tex, x, y, c);
		}
	}
}
#endif

t_texture	texture_create(void *mlx, int width, int height)
{
	t_texture	t;

	t.width = width;
	t.height = height;
	t.img = mlx_new_image(mlx, width, height);
	t.data = mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	return (t);
}

t_texture	texture_load(void *mlx, char *path)
{
	t_texture	t;

	t.img = mlx_xpm_file_to_image(mlx, path, &t.width, &t.height);
	t.data = mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	texture_init(t);
	return (t);
}

