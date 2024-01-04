#include "state.h"
#include "task.h"

t_task *g_tasks[TASK_LEN] = {
    (t_task*)&(t_task_orbit){.task.name = "task_orbit", .task.key = KEY_E, .task.func = task_orbit_render,
	 .task.setup = task_orbit_setup},
};