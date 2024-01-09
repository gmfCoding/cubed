#ifndef MODIFIERS_H
# define MODIFIERS_H

# define NAME_SIZE 50
# define MAX_ENT 100 
# include <stdbool.h>
typedef struct s_world t_world;
typedef struct	s_map t_map;
typedef struct s_world t_world;

typedef enum	e_modtype
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR,
	DOOR,
}				t_modtype;

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

void	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world);

#endif
