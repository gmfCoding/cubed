#ifndef ENEMY_H
# define ENEMY_H
# include <stdint.h>
# include <math.h>
# include "vector2.h"
# include "vector2i.h"


typedef struct	s_game t_game;
typedef struct	s_world t_world;
typedef struct	s_map t_map;
typedef struct	s_sprite t_sprite;
typedef struct	s_tile t_tile;
typedef enum	e_enemy_state
{
		NOT_ACTIVE,
		PATROL,
		GO_PATH_TO_TARGET,
		TARGET_IN_SIGHT,
}		t_enemy_state;

typedef uint16_t t_tid;
typedef struct	s_enemy_anim
{
	t_tid	tex[576];
}		t_enemy_anim;

typedef struct		s_enemy
{
	t_vec2		patrol_target;
	t_vec2i		old_pos[3];
	int		angle_frame;
	t_vec2		*path;
	int		p_index;
	t_enemy_anim	*anim;
	t_enemy_state	state;
	float		speed;
//	struct s_tile	*tile_ref[9];
	struct s_sprite	*sprite_ref;
}			t_enemy;


void	enemy_load_directory(t_game *game);
void	enemy_routine(t_game *game, t_enemy *enemy);

#endif
