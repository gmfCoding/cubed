/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:07:41 by clovell           #+#    #+#             */
/*   Updated: 2023/04/25 17:08:29 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR_H
# define VECTOR_H

typedef float	t_vecd;

typedef struct s_vec2
{
	t_vecd	x;
	t_vecd	y;
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
#endif
