/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:07:41 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 17:24:58 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR2_H
# define VECTOR2_H

typedef double	t_vecd;

typedef struct s_vec2
{
	union
	{
		struct
		{
			union
			{
				t_vecd	x;
				t_vecd	min;
			};
			union
			{
				t_vecd	y;
				t_vecd	max;
			};
		};
		t_vecd	v[2];
	};
}				t_vec2;

t_vec2	v2new(t_vecd x, t_vecd y);

/* Adds a vector to another */
t_vec2	v2add(t_vec2 f, t_vec2 s);

/* Subtracts a vector from another */
t_vec2	v2sub(t_vec2 f, t_vec2 s);

/* Inverts the components of a vector, essentially reversing the direction. */
t_vec2	v2inv(t_vec2 s);

/* Multiplies a vector by another */
t_vec2	v2mulv(t_vec2 f, t_vec2 s);

/* Scales the size of a vector by s */
t_vec2	v2muls(t_vec2 f, t_vecd s);

/* Return the squared magnitude of a vector */
t_vecd	v2sqrmag(t_vec2 vec);

/* Returns the magnitude of a vector */
t_vecd	v2mag(t_vec2 vec);

/* Returns a normalised (length of 1) copy of a vector */
t_vec2	v2norm(t_vec2 vec);

/* Returns the determinate (perp cross product)*/
t_vecd v2det(t_vec2 a, t_vec2 b);

/* Returns component wise division c = c / s */
t_vec2	v2divs(t_vec2 f, t_vecd s);

/* Returns component-wise inverse division c = s / c */
t_vec2	v2sdiv(t_vecd s, t_vec2 f);

char	*v2toa(int v[3]);
#endif
