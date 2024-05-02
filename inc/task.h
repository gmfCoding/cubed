/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:45:33 by clovell           #+#    #+#             */
/*   Updated: 2024/05/02 18:59:14 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASK_H
# define TASK_H
# include <stddef.h>
# include <stdbool.h>

typedef struct s_task	t_task;

// FORWARD DECLARE
typedef struct s_game	t_game;
//typedef int (t_taskwin_fn*)(t_game *game, t_task *task);
typedef int (*t_taskrender_fn)(t_game *game, t_task *task);
struct s_task
{
	char			*name;
	int				key;
	size_t			size;
	t_taskrender_fn	func;
	t_taskrender_fn	setup;
	bool			show;
	bool			init;
	bool			completed;
};

# define TASK_LEN 2

t_task	*task_find(t_game *game, char *name);
t_task	*task_create_or_find(t_game *game, char *name);
void	task_process(t_game *game);

int    task_orbit_setup(t_game *game, t_task *task);
int    task_orbit_render(t_game *game, t_task *task);
#endif
