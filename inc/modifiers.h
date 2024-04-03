#ifndef MODIFIERS_H
# define MODIFIERS_H

# define NAME_SIZE 50
# define MAX_ENT 100 
# include <stdbool.h>
# include "a_star.h"
typedef struct	s_world t_world;
typedef struct	s_map t_map;
typedef struct	s_tile t_tile;
typedef	struct	s_mm_tile t_mm_tile;
//typedef struct	s_game t_game;

typedef enum	e_modtype
{
	OTHER,
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR,
	MINI_MAP,
	ENEMY,
}				t_modtype;

typedef enum	e_ent_type
{
	DOOR_OPEN,
	DOOR_UNLOCKED,
	DOOR_LOCKED,
	KEY,
	ALERT_MEDIUM,
	ALERT_HIGH,
	ALERT_OFF,
	FIVE_LIGHTS_OPEN,
	FIVE_LIGHTS_CLOSED,
	ORBIT_TASK_OPEN,
	ORBIT_TASK_CLOSED,
}		t_ent_type;

typedef struct	s_mod
{
	t_modtype	type;
	char*		content;
}			t_mod;

typedef struct s_key
{
	char	name[NAME_SIZE];
	char	doorname[NAME_SIZE];
	t_vec2	pos;
	bool	auto_open;
	bool	collected;
}		t_key;

typedef struct s_door
{
	char	name[NAME_SIZE];
	t_vec2	pos;
	int	speed;
	bool	closed;
	bool	locked;
}		t_door;

typedef struct	s_entity_2
{
	t_ent_type	type;
	char		name[NAME_SIZE];
	char		ui_display_1[NAME_SIZE];
	char		ui_display_2[NAME_SIZE];
	t_vec2		pos[9];// 9 is for the event trigger
	t_tile		*ref_tile;
	t_mm_tile	*ref_mm_tile;
	int		speed;
	int		value;
	struct		s_entity_2 *target; // would be the door entity for instant or something else
	bool		state_1;
	bool		state_2;
	bool		state_3;//just incase i need something else stored
}			t_entity_2;

typedef struct	s_entity
{
	t_door	doors[MAX_ENT];
	t_key	keys[MAX_ENT];

}		t_entity;

typedef void	(*t_ex_action)(char *, int, t_world *, t_map *);
void		mod_gen_no(char *content, int index, t_world *world, t_map *map);
void		mod_gen_so(char *content, int index, t_world *world, t_map *map);
void		mod_gen_we(char *content, int index, t_world *world, t_map *map);
void		mod_gen_ea(char *content, int index, t_world *world, t_map *map);
void		mod_gen_c(char *content, int index, t_world *world, t_map *map);
void		mod_gen_f(char *content, int index, t_world *world, t_map *map);
void		mod_gen_dr(char *content, int index, t_world *world, t_map *map);
void		mod_gen_ke(char *content, int index, t_world *world, t_map *map);
void		mod_gen_mm(char *content, int index, t_world *world, t_map *map);
void		mod_gen_al(char *content, int index, t_world *world, t_map *map);
void		mod_gen_en(char *content, int index, t_world *world, t_map *map);
void		mod_gen_wn(char *content, int index, t_world *world, t_map *map);

void	modifier_after(t_game *game);
void	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world);
void	*get_pos_and_surrounding_tiles(t_world *world, int x, int y);
t_mod	*mod_get_mod(t_map *map, t_modtype type, int *index);
#endif
