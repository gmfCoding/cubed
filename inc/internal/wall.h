/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:39:55 by clovell           #+#    #+#             */
/*   Updated: 2024/03/09 04:04:27 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef WALL_H
# define WALL_H
# include "vector2.h"
# include "vector2i.h"
# include "ray.h"

# define C_WALL 0
# define C_SPRITE 1

typedef struct s_vertical
{
	int			x;
	double		camera_x;
	t_vec2		dir;
	t_rayinfo	ray;

}			t_vert;

typedef struct s_column
{
	int		texture;
	int		tex_size;
	int		shaded;
	double	sample_dy;
	int		x;
	int		height;
	t_vec2	uv;
	t_vec2i	sample;
	t_vec2i	range;
	int		type;
}			t_col;

void	render_vertical(t_game *game, t_vert info);
#endif