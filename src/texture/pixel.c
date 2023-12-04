/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:34:56 by clovell           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/13 13:16:18 by clovell          ###   ########.fr       */
=======
/*   Updated: 2023/12/04 16:34:57 by clovell          ###   ########.fr       */
>>>>>>> d8df9dc (Add verbatim impl of floor/ceiling textures from lodev.org)
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"
#include "cerror.h"

// __attribute__((always_inline))
// inline void	pixel_set(t_texture data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// __attribute__((always_inline))
// inline void	pixel_set_s(t_texture data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || y < 0 || x >= data.width || y >= data.height)
// 		return ;
// 	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
// 	*(unsigned int *)dst = color;
// }

__attribute__((always_inline))
inline void	pixel_set(t_texture data, int x, int y, int color)
{
	data.data[x + y * data.width] = color;
}

__attribute__((always_inline))
inline void	pixel_set_s(t_texture data, int x, int y, int color)
{
<<<<<<< HEAD
	if (x < 0 || y < 0 || x >= data.width || y >= data.height)
		return ;
	data.data[x + y * data.width] = color;
=======
	char	*dst;

	if (x < 0 || y < 0 || x >= data.width || y >= data.height)
		return ;
	dst = data.data + (y * data.line_size + x * 4);
	*(unsigned int *)dst = color;
>>>>>>> d8df9dc (Add verbatim impl of floor/ceiling textures from lodev.org)
}

// int	pixel_get(t_texture data, int x, int y)
// {
// 	char	*dst;

// 	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
// 	return (*(int *)dst);
// }

inline int	pixel_get(t_texture data, int x, int y)
{
	return (data.data[x + y * data.width]);
}

#ifdef D_ASSERT_PIXEL_NO_GET

int	pixel_get_s(t_texture data, int x, int y)
{
	char	*dst;

	if (x < 0 || y < 0 || x > data.width || y > data.height)
		ft_assert(1, ERR_BADPARAM, __FILE__, __LINE__);
	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	return (*(int *)dst);
}
#else

// int	pixel_get_s(t_texture data, int x, int y)
// {
// 	char	*dst;

// 	if (x < 0 || y < 0 || x > data.width || y > data.height)
// 		return (R_ALPHA);
// 	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
// 	return (*(int *)dst);
// }

int	pixel_get_s(t_texture data, int x, int y)
{
	if (x < 0 || y < 0 || x > data.width || y > data.height)
		return (R_ALPHA);
	return (data.data[x + y * data.width]);
}
#endif
