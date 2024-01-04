#include "task.h"
#include "render.h"


int    task_orbit_setup(t_game *game, t_task *task)
{
    t_task_orbit *t = (t_task_orbit*)task;
    printf("task_setup: %s", task->name);
    t->pro_btn = (t_sprite){.pos = v2new(0,0), .tex = texture_load(game->app.mlx, "assets/debug.xpm")};
}

int    task_orbit_render(t_game *game, t_task *task)
{
    t_task_orbit *t = (t_task_orbit*)task;
    texture_draw(game, t->pro_btn.tex, t->pro_btn.pos);
}