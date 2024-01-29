#ifndef EVENTS_H
# define EVENTS_H

# define MAX_EVENT 100


//#include "input.h"


typedef struct	s_world t_world;
typedef struct	s_map t_map;

typedef enum	e_event_type
{
	DOOR_UNLOCKED_O,
	DOOR_UNLOCKED_C,
	ALARM_MEDIUM,
	ALARM_HIGH,	
}		t_event_type;

typedef struct s_event
{
	t_vec2		pos[9];
	t_event_type	type;
}		t_event;

void	event_trigger(t_game *game, t_vec2 pos, t_event_type type);
void	event_player(t_game *game);
void	event_interact(t_game *game);
/*
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
*/
#endif
