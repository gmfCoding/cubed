/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_orbit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:58:32 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 03:06:22 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TASK_ORBIT_H
# define TASK_ORBIT_H
# include "cubed.h"
# include "orbit.h"
# include "ui.h"
# include "random.h"

/*** Button selector references ***/
# define BS_THRUST "+"
# define BS_RTHRUST "-"
# define BS_TIME "t"
# define BS_RTIME "T"
# define BS_NNODE "n"
# define BS_PNODE "p"
# define BS_NTAR "G"

# define ORB_MUI_BTN_APPLY 0
# define ORB_MUI_BTN_MS0 1
# define ORB_MUI_BTN_MS1 2
# define ORB_MUI_BTN_MS2 3
# define ORB_MUI_BTN_MS3 4
# define ORB_MUI_BTN_MS4 5

# define ORB_MUI_LEN_BTN 6

# define ORB_MUI_DIAL_M0 0
# define ORB_MUI_DIAL_M1 1
# define ORB_MUI_DIAL_M2 2
# define ORB_MUI_DIAL_M3 3
# define ORB_MUI_DIAL_M4 4

# define ORB_MUI_DIAL_X 5
# define ORB_MUI_DIAL_Y 6
# define ORB_MUI_DIAL_Z 7
# define ORB_MUI_DIAL_B 8
# define ORB_MUI_LEN_DIAL 9

# define ORB_MUI_SLD_THROTTLE 0

# define T_ORBIT_MAX_MAN 5

typedef struct s_sa_orbit_task
{
	t_kep_path		start_path;
	t_kep_ang		start_ang;

	t_rand			rand;
	t_kep_path		target_path;

	t_kep_path		paths[T_ORBIT_MAX_MAN];
	t_kep_ang		nodes[T_ORBIT_MAX_MAN];
	double			delta[T_ORBIT_MAX_MAN];		
	double			mean[T_ORBIT_MAX_MAN];		
	int				maneuvers;
	int				active_path;

	t_orb_cart		cart;
	t_orb_body		sun;
	t_texture		rt0;
	t_app			app;
	t_ui_context	ui;
	t_inputctx		input;
}	t_sa_orbit_task;

void	orbit_control_action(t_button *btn, t_ui_context *ctx);

#endif