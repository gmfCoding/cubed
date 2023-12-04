/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2i.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:07:41 by clovell           #+#    #+#             */
/*   Updated: 2023/11/30 22:44:39 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR2I_H
# define VECTOR2I_H

typedef int	t_veci;

typedef struct s_vec2i
{
	union
	{
		t_veci	x;
		t_veci	s;
	};
	
	union
	{
		t_veci	y;
		t_veci	e;
	};
}				t_vec2i;

t_vec2i	v2inew(t_veci x, t_veci y);

/* Adds a vector to another */
t_vec2i	v2iadd(t_vec2i f, t_vec2i s);

/* Subtracts a vector from another */
t_vec2i	v2isub(t_vec2i f, t_vec2i s);

/* Inverts the components of a vector, essentially reversing the direction. */
t_vec2i	v2iinv(t_vec2i s);

/* Multiplies a vector by another */
t_vec2i	v2imulv(t_vec2i f, t_vec2i s);

/* Scales the size of a vector by s */
t_vec2i	v2imuls(t_vec2i f, t_veci s);

/* Return the squared magnitude of a vector */
t_veci	v2isqrmag(t_vec2i vec);

/* Returns the magnitude of a vector */
t_veci	v2imag(t_vec2i vec);

/* Returns a normalised (length of 1) copy of a vector */
t_vec2i	v2inorm(t_vec2i vec);
#endif
