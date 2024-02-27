#ifndef ENEMY_H
# define ENEMY_H

typedef struct	s_world t_world;
typedef struct	s_map t_map;
typedef struct	s_sprite t_sprite;
typedef struct	s_tile t_tile;
typedef enum	e_enemy_state
{
		NOT_ACTIVE,
		PATROL,
		HEAD_FOR_TARGET,
		TARGET_IN_SIGHT,
}		t_enemy_state;
/*
typedef uint16_t t_tid;
typedef struct	s_enemy_anim
{
	t_tid	tex[100];
}		t_enemy_anim;
*/
typedef struct		s_enemy
{
	t_vec2		pos;
	int		dir;
	t_vec2		*path;
//	t_enemy_anim	*anim;
	t_enemy_state	state;
	double		speed;
	struct s_tile	*tile_ref;
	struct s_sprite	*sprite_ref;
}			t_enemy;

#endif
