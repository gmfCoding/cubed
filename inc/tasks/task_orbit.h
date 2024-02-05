/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_orbit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:58:32 by clovell           #+#    #+#             */
/*   Updated: 2024/02/05 17:46:18 by clovell          ###   ########.fr       */
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