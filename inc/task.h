#ifndef TASK_H
# define TASK_H
# include "texture.h"

typedef struct s_task t_task;

// FORWARD DECLARE
typedef struct s_game t_game;

typedef struct s_sprite
{
	t_texture	tex;
	t_vec2		pos;
} t_sprite;

//typedef int (t_taskwin_fn*)(t_game *game, t_task *task);
typedef int (*t_taskrender_fn)(t_game *game, t_task *task);
struct s_task
{
	char			*name;
	int				key;
	t_taskrender_fn	func;
	t_taskrender_fn	setup;
	bool			show;
};

# define TASK_LEN 1

extern t_task *g_tasks[TASK_LEN];

int    task_orbit_setup(t_game *game, t_task *task);
int    task_orbit_render(t_game *game, t_task *task);
#endif