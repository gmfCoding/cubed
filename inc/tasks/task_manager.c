/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:44:29 by marvin            #+#    #+#             */
/*   Updated: 2024/02/20 20:18:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "task.h"
#include "libft.h"
#include "tasks/task_orbit.h"
#include "random.h"

#define TASK_FIVE_LIGHTS_ID 0
#define TASK_ORBIT_ID 1

typedef struct	s_task_mgr
{
	t_list	*active_tasks;
	t_task	*defaults[TASK_LEN];
	size_t	task_sizes[TASK_LEN];

	double	task_weights[TASK_LEN];
} t_task_mgr;

const static t_task_mgr	g_task_mgr_init = {
	.defaults = {
		[TASK_FIVE_LIGHTS_ID] = (t_task*)&(t_task){.type = TASK_FIVE_LIGHTS_ID, 
		},
		[TASK_ORBIT_ID] = (t_task*)&(t_task_orbit){
		.task.type = TASK_ORBIT_ID, .task.name = "task_orbit", .task.key = KEY_E, 
		.task.func = task_orbit_render,
		.task.setup = task_orbit_setup,
		.maneuvers = 5, .active_path = 0, .zoom = 100, .brightness = 1.0, 
		.scr_offset = {161, 150}, 
		.gen = &(t_orb_gen){
			.sma = {0.5 * KM_AU, 1.25 * KM_AU}, .ecc = {0.0001, 0.8},
			.inc = {0.0001, 0.0001}, .aop = {0.0001, M_TAU}, .lan = {0.0001, 0.0001}},
		},
	},
	.task_sizes = {
		[TASK_FIVE_LIGHTS_ID] = sizeof(t_task),
		[TASK_ORBIT_ID] = sizeof(t_task_orbit),
	}
};

void	task_mgr_process(t_game *game, t_task_mgr *mgr);


t_task	*task_clone(t_task_mgr *mgr, t_task *task)
{
	t_task *res = malloc(mgr->task_sizes[task->type]);
	ft_memcpy(res, task, mgr->task_sizes[task->type]);
	return (res);
}

t_task  *task_enqueue(t_game *game, t_task_mgr *mgr, t_task *def)
{
	ft_lstadd_front(&mgr->active_tasks, ft_lstnew(task_clone(def)));
	return (mgr->active_tasks->content);
}

t_task  *task_enqueue_random(t_game *game, t_task_mgr *mgr)
{
	const double	weight = mrand_rangef(&game->rand, 0.0, 1.0);
	int				i;

	i = -1;
	while (++i < TASK_LEN)
	{
		if (mgr->task_weights[i] > weight)
			continue ;
		return (task_enqueue(game, mgr, mgr->defaults[i]));
	}
	return (NULL);
}

void	task_open(t_game *game, t_task *task);
void	task_close(t_game *game, t_task *task);
void	task_complete(t_game *game, t_task *task);
