/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:11:47 by clovell           #+#    #+#             */
/*   Updated: 2023/05/15 14:42:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "texture.h"

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
	return (t);
}

__attribute__((always_inline))
inline void	pixel_set(t_texture data, int x, int y, int color)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_texture data, int x, int y)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	return (*(int *)dst);
}
