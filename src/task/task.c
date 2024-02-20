#include "state.h"
#include "task.h"
#include "tasks/task_orbit.h"

typedef struct s_task t_task;

t_task *g_tasks[TASK_LEN] = {
    (t_task*)&(t_task_orbit){.task.name = "task_orbit", .task.key = KEY_E, .task.func = task_orbit_render,
	 .task.setup = task_orbit_setup},
};

//typedef int (t_taskwin_fn*)(t_game *game, t_task *task);
typedef int (*t_taskrender_fn)(t_game *game, t_task *task);

t_taskrender_fn task_renderers = {
    task_orbit_render,
};