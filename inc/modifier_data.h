/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_data.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:08:09 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/29 15:00:52 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODIFIER_DATA_H
# define MODIFIER_DATA_H

typedef enum e_modtype
{
	MT_OTHER,
	MT_NORTH_TEXTURE,
	MT_SOUTH_TEXTURE,
	MT_WEST_TEXTURE,
	MT_EAST_TEXTURE,
	MT_FLOOR_COLOR,
	MT_CEILING_COLOR,
	MT_MINI_MAP,
	MT_DOOR,
	MT_ENEMY,
	MT_FIVELIGHT_TASK,
	MT_ORBIT_TASK,
	MT_GATE_AND,
	MT_GATE_OR,
	MT_GATE_SPLITTER
}				t_modtype;


typedef struct s_mod_door_data
{
	char		name[50];
	char		tex[50];
	t_vec2i		pos;
	uint32_t	speed;
	char		locked;
	char		closed;
}	t_mod_door_data;

typedef struct s_mod_enemy_data
{
	char		name[50];
	char		target[50];
	uint32_t	speed;
	t_vec2i		pos;
	char		state;
}	t_mod_enemy_data;

typedef struct s_mod_task_data
{
	char		name[50];
	char		target[50];
	char		active;
	t_vec2i		pos;
	char		dir; 
}	t_mod_task_data;

typedef t_mod_task_data	t_mod_fl_data;
typedef t_mod_task_data	t_mod_ob_data;

typedef struct s_mod_alarm_data
{
	char		name[50];
	char		target[50];
	char		type;
	t_vec2i		pos;
	uint32_t	time;
}	t_mod_alarmdata;

typedef struct s_mod_any
{
	union
	{
		t_mod_door_data		dr;
		t_mod_enemy_data	en;
		t_vec2i				wn;
		t_mod_alarmdata		al;
		t_mod_fl_data		fl;
		t_mod_ob_data		ob;
	};
}	t_mod_any;

#endif