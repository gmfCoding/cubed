/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 06:52:39 by clovell           #+#    #+#             */
/*   Updated: 2024/03/27 00:39:26 by clovell          ###   ########.fr       */
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


/***
 * Position, the position of the sprite.
 * Segments, the unbounded segments of the sprite.
 * Visual segements, the bounded segments of the sprite.
 * 		If the sprite is pushed into a wall, 
 * 		the visual segment will not clip through the wall.
 * ***/
struct	s_sprite
{
	char		id;
	t_tid		tex;
	t_vec2		pos;

	// Segment 1
	t_vec2		s1;

	// Segment 2
	t_vec2		s2;

	// Visual segment 1
	t_vec2		vs1;
	// Visual segment 2
	t_vec2		vs2;
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