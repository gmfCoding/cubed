/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/07 01:00:15 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODIFIERS_H
# define MODIFIERS_H
# include "config.h"
# include <stdbool.h>
# include "a_star.h"
# include "entity.h"
# include "modifier_data.h"

typedef struct s_world		t_world;
typedef struct s_map		t_map;
typedef struct s_tile		t_tile;
typedef struct s_mm_tile	t_mm_tile;
//typedef struct	s_game t_game;

typedef enum e_ent_type
{
	ET_DOOR_OPEN,
	ET_DOOR_UNLOCKED,
	ET_DOOR_LOCKED,
	ET_KEY,
	ET_ALERT_MEDIUM,
	ET_ALERT_HIGH,
	ET_ALERT_OFF,
	ET_FIVE_LIGHTS_OPEN,
	ET_FIVE_LIGHTS_CLOSED,
	ET_ORBIT_TASK_OPEN,
	ET_ORBIT_TASK_CLOSED,
}		t_ent_type;

typedef struct s_mod
{
	t_modtype	type;
	char		content[MOD_CONTENT_MAX];
}			t_mod;

typedef struct s_key
{
	char	name[NAME_SIZE];
	char	doorname[NAME_SIZE];
	t_vec2	pos;
	bool	auto_open;
	bool	collected;
}		t_key;

typedef struct s_entity_2
{
	t_ent_type			type;
	char				name[NAME_SIZE];
	char				(*ui_display)[NAME_SIZE];
	char				ui_display_1[NAME_SIZE];
	char				ui_display_2[NAME_SIZE];
	t_vec2				pos;// 9 is for the event trigger
	t_tile				*ref_tile;
	t_mm_tile			*ref_mm_tile;
	int					speed;
	int					value;
	// would be the door entity for instant or something else
	struct s_entity_2	*target; 
	t_entity			*entity; // Duct tape fix
	bool				state_1;
	bool				state_2;
	bool				state_3;//just incase i need something else stored
}			t_entity_2;

typedef t_err				(*t_ex_action)(char *, int, t_world *, t_map *);
t_err	mod_gen_no(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_so(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_we(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_ea(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_c(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_f(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_dr(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_ke(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_mm(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_al(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_en(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_wn(char *content, int index, t_world *world, t_map *map);
t_err	mod_gen_fl(char *content, int index, t_world *world, t_map *map);

void	modifier_after(t_game *game);
t_err	modifier_setup(t_list *raw_map_file, t_map *map, t_world *world);
t_mod *mod_get_mod(t_map *map, t_modtype type, int *index);
#endif
