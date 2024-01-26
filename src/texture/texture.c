/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:11:47 by clovell           #+#    #+#             */
/*   Updated: 2024/01/27 05:34:06 by clovell          ###   ########.fr       */
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
	t.data = (int *)mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	return (t);
}

t_texture	texture_load(void *mlx, char *path)
{
	t_texture	t;

	t.img = mlx_xpm_file_to_image(mlx, path, &t.width, &t.height);
	t.data = (int *)mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	return (t);
}