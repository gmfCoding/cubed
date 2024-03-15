/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 06:52:39 by clovell           #+#    #+#             */
/*   Updated: 2024/03/16 07:37:25 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENTITY_H
# define ENTITY_H
#include <inttypes.h>
#include "vector2.h"

typedef uint16_t	t_tid;
typedef struct s_sprite	t_sprite;

struct	s_sprite
{
	t_tid		tex;
	t_vec2		pos;
	t_vec2		s1;
	t_vec2		s2;
};

struct s_entity
{
	t_vec2		pos;
	t_sprite	sprite;
};
#endif