/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 06:52:39 by clovell           #+#    #+#             */
/*   Updated: 2024/05/04 01:34:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENTITY_H
# define ENTITY_H
# include <inttypes.h>
# include <stdbool.h>
# include "config.h"
# include "vector2.h"

typedef uint16_t			t_tid;
typedef struct s_sprite		t_sprite;
typedef struct s_entity		t_entity;
typedef struct s_mm_tile	t_mm_tile;

typedef struct s_game		t_game; // FORWARD DECLARE
typedef struct s_world		t_world; // FORWARD DECLARE
typedef struct s_entity_2	t_entity_2; // FORWARD DECLARE
typedef void				(*t_fn_event_handler)(t_entity *, t_game *);
typedef void				(*t_fn_entity_update)(t_entity *, t_game *);

typedef struct s_uv
{
	t_vec2	offset;
	t_vec2	scale;
}				t_uv;

/***
 * Position, the position of the sprite.
 * Segments, the unbounded segments of the sprite.
 * Visual segements, the bounded segments of the sprite.
 * 		If the sprite is pushed into a wall, 
 * 		the visual segment will not clip through the wall.
 * ***/
struct	s_sprite
{
	t_tid		tex;
	t_vec2		pos;
	bool		visible;

	t_uv		uv;

	// Segment 1
	t_vec2		s1;

	// Segment 2
	t_vec2		s2;

	// Visual segement fall back
	bool		vsfb;
	// Visual segment 1
	t_vec2		vs1;
	// Visual segment 2
	t_vec2		vs2;
};

typedef enum e_entity_type
{
	ENT_DOOR,
	ENT_ENEMY,
	ENT_TASK_ORBIT,
	ENT_TRIGGER_AREA,
}	t_entity_type;

struct	s_entity
{
	t_entity_type	type;
	t_vec2			pos;
	t_sprite		*sprite;
	t_mm_tile		*mm_tile;
};

typedef struct s_door
{
	t_entity	base;
	char		name[NAME_SIZE];
	float		speed;
	float		pct;
	bool		closed;
	bool		locked;

	t_sprite	*sprites[4];
}	t_door;

typedef struct s_door_model
{
	t_vec2	wall_left;
	t_vec2	inset_left;
	t_vec2	left_left;
	t_vec2	door_left;
	t_vec2	far_left;

	t_vec2	wall_right;
	t_vec2	inset_right;
	t_vec2	right_right;
	t_vec2	door_right;
	t_vec2	far_right;
}	t_door_model;

typedef struct s_wm_task_orbit
{
	t_vec2		m1;
	t_vec2		m2;

	t_vec2		o1;
	t_vec2		o2;

	t_vec2		b1;
	t_vec2		b2;

	t_vec2		dir;
}	t_wm_task_orbit;

typedef struct s_ent_task_orbit
{
	t_entity	base;
	t_sprite	*sprites[5];
	t_vec2		dir;
}	t_ent_task_orbit;

enum e_dynamic_ent
{
	DYN_ENT_PLAYER,
	DYN_ENT_ENEMY,
};

typedef struct s_ent_trigger_area
{
	t_entity			base;
	bool				enabled;
	bool				manhattan;
	enum e_dynamic_ent	watch;
	float				radius;
	t_entity_2			*ent2;
}	t_ent_trigger_area;

# define ENT_DOOR_SPEED 2.0

t_entity	*entity_create(t_world *world, t_entity_type type);
void		entity_update(t_game *game);
#endif
