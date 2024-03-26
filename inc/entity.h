/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 06:52:39 by clovell           #+#    #+#             */
/*   Updated: 2024/03/16 13:32:11 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENTITY_H
# define ENTITY_H
# include <inttypes.h>
# include <stdbool.h>
# include "config.h"
# include "vector2.h"

typedef uint16_t		t_tid;
typedef struct s_sprite	t_sprite;
typedef struct s_entity	t_entity;
typedef struct s_mm_tile	t_mm_tile;

typedef struct s_game t_game; // FORWARD DECLARE
typedef struct s_world t_world; // FORWARD DECLARE
typedef void (*t_fn_event_handler)(t_entity *entity, t_game *game);

struct	s_sprite
{
	char		id;
	t_tid		tex;
	t_vec2		pos;
	t_vec2		s1;
	t_vec2		s2;
};

typedef enum e_entity_type
{
	ENT_DOOR,
	ENT_ENEMY
} t_entity_type;

struct	s_entity
{
	t_entity_type	type;
	t_vec2			pos;
	t_sprite		*sprite;
	t_mm_tile		*mm_tile;
};

typedef struct	s_door
{
	t_entity	base;
	char	name[NAME_SIZE];
	int		speed;
	float	percent;
	bool	closed;
	bool	locked;
} t_door;

t_entity	*entity_create(t_world *world, t_entity_type type);
void		entity_update(t_game *game);
#endif