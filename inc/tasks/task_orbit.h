/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_orbit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:58:32 by clovell           #+#    #+#             */
/*   Updated: 2024/05/07 18:12:47 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TASK_ORBIT_H
# define TASK_ORBIT_H
# include "cubed.h"
# include "orbit.h"
# include "ui.h"
# include "random.h"
# include "tasks/mui_orbit.h"
# include "task.h"

/*** Button selector references ***/
# define BS_THRUST "+"
# define BS_RTHRUST "-"
# define BS_TIME "t"
# define BS_RTIME "T"
# define BS_NNODE "n"
# define BS_PNODE "p"
# define BS_NTAR "G"

# define ORB_RED 0x00CA522A
# define ORB_GREEN 0x003DB92A
# define ORB_GREEN2 0x002DA9AA
# define ORB_BLUE 0x003552D5
# define ORB_WHITE 0x00CAB9D5

# define ORB_PLANET 0x006DBF6E
# define T_ORBIT_MAX_MAN 5
# define T_ORBIT_MAX_ALL 7

typedef struct s_sa_orbit_task
{
	t_task			task;
	t_kep_ang		start_ang;
	t_rand			rand;
	union
	{
		t_kep_path		paths_all[T_ORBIT_MAX_ALL];
		/* DON'T CHANGE: Memory layout very important for rendering code. 
			start_path must be JUST before paths.
		*/
		struct
		{
			t_kep_path		start_path;
			t_kep_path		paths[T_ORBIT_MAX_MAN];
			t_kep_path		target_path;
		};
	};
	t_kep_ang		nodes[T_ORBIT_MAX_MAN];
	double			delta[T_ORBIT_MAX_MAN];		
	double			mean[T_ORBIT_MAX_MAN];		
	int				maneuvers;
	int				active_path;

	t_orb_cart		cart;
	t_orb_body		sun;
	t_mui_ctx		mui;
	t_inputctx		input;
	float			zoom;
	float			brightness;
	t_vec2			scr_offset;
	t_orb_gen		*gen;
}	t_task_orbit;

// TODO: Remove
void	handle_closing(t_game *game, t_task *task);
void	orbit_control_action(t_button *btn, t_ui_context *ctx);
void	update_paths(t_task_orbit *t);

#endif
