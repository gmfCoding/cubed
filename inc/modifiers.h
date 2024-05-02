/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:55:52 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 19:30:55 by clovell          ###   ########.fr       */
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
	ET_EMPTY,
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

enum e_mod_id
{
	MOD_ID_NO,
	MOD_ID_SO,
	MOD_ID_WE,
	MOD_ID_EA,
	MOD_ID_F,
	MOD_ID_C,
	MOD_ID_DR,
	MOD_ID_KE,
	MOD_ID_AL,
	MOD_ID_MM,
	MOD_ID_EN,
	MOD_ID_WN,
	MOD_ID_WL,
	MOD_ID_FL,
	MOD_ID_OB,
	MOD_ID_GO,
	MOD_ID_GA,
	MOD_ID_GM,
	MOD_ID_TA,
};

typedef struct s_key
{
	char	name[NAME_SIZE];
	char	doorname[NAME_SIZE];
	t_vec2	pos;
	bool	auto_open;
	bool	collected;
}		t_key;

# define TARGET_HANDLE_MAX_DEPTH 10
# define EVENT_ENT_MAX_TARGETS 4

typedef enum e_handle_result
{
	TARGET_HANDLE_NONE,
	TARGET_HANDLE_SUCCESS,
	TARGET_HANDLE_FAILED,
}	t_handle_result;

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
	union
	{
		struct
		{
			struct s_entity_2	*target; // targets[0]
			struct s_entity_2	*parent1; // targets[1]
			struct s_entity_2	*parent2; // targets[2]
		};
		struct
		{
			struct s_entity_2	*targets[EVENT_ENT_MAX_TARGETS]; // stores all targets
			char				*target_names[EVENT_ENT_MAX_TARGETS]; // stores all target names
		};
	};
	t_handle_result		(*handle)(t_game *game, struct s_entity_2 *self, struct s_entity_2 *other);
	t_entity			*entity; // Duct tape fix
	bool				state_1;
	bool				state_2;
	bool				state_3;//just incase i need something else stored
}			t_entity_2;

typedef t_err				(*t_ex_action)(char *, int, t_world *, t_map *);
t_err		mod_gen_no(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_so(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_we(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_ea(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_c(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_f(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_dr(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_ke(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_mm(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_al(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_en(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_wn(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_wl(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_fl(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_ob(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_go(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_ga(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_gm(char *content, int index, t_world *world, t_map *map);
t_err		mod_gen_ta(char *content, int index, t_world *world, t_map *map);

void		modifier_after(t_game *game);
t_err		modifier_setup(t_list *raw_map_file, t_map *map, t_world *world);

t_vec2		mod_dir_to_vec2(char dir);
t_mod		*mod_get_mod(t_map *map, t_modtype type, int *index);
t_entity_2	*mod_search_name(t_world *world, char *str);
#endif
