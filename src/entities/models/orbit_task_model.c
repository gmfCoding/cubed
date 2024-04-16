#include "vector2.h"
#include "state.h" 

void	model_orbit_update(t_game *game, t_vec2 pos, t_wm_task_orbit *m)
{
	const t_vec2	centre = v2add(pos, v2new(0.5, 0.5));
	const t_vec2	dir_s = v2muls(m->dir, 0.3);
	const t_vec2	tangent = v2clock(m->dir);

	m->m1 = v2muls(tangent, 0.45);
	m->m2 = v2muls(tangent, -0.45);
	m->o1 = v2add(v2add(centre, dir_s), v2muls(tangent, 0.3));
	m->o2 = v2add(v2add(centre, dir_s), v2muls(tangent, -0.3));
}