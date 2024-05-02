#include "vector2.h"
#include "state.h" 
#include "entity.h"

void	model_orbit_update(t_game *game, t_vec2 pos, t_wm_task_orbit *m)
{
	const t_vec2	centre = v2add(pos, v2new(0.5, 0.5));
	const t_vec2	dir_s = v2muls(m->dir, 0.2);
	const t_vec2	tangent = v2clock(m->dir);

	m->m1 = v2sub(v2add(centre, v2muls(tangent, 0.45)), dir_s);
	m->m2 = v2sub(v2add(centre, v2muls(tangent, -0.45)), dir_s);
	m->o1 = v2add(centre, v2muls(tangent, 0.3));
	m->o2 = v2add(centre, v2muls(tangent, -0.3));
	m->b1 = v2sub(v2add(centre, v2muls(tangent, 0.45)), v2muls(m->dir, 0.5));
	m->b2 = v2sub(v2add(centre, v2muls(tangent, -0.45)), v2muls(m->dir, 0.5));
}

void	ent_task_orbit_update(t_ent_task_orbit *orbit, t_game *game)
{
	t_wm_task_orbit	m;

	m.dir = orbit->dir;
	model_orbit_update(game, orbit->base.pos, &m);
	orbit->sprites[0]->pos = v2lerp(m.m1, m.o1, 0.5);
	orbit->sprites[0]->s1 = m.m1;
	orbit->sprites[0]->s2 = m.o1;
	orbit->sprites[1]->pos = v2lerp(m.o1, m.o2, 0.5);
	orbit->sprites[1]->s1 = m.o1;
	orbit->sprites[1]->s2 = m.o2;
	orbit->sprites[2]->pos = v2lerp(m.o2, m.m2, 0.5);
	orbit->sprites[2]->s1 = m.m2;
	orbit->sprites[2]->s2 = m.o2;
	orbit->sprites[3]->pos = v2lerp(m.m1, m.b1, 0.5);
	orbit->sprites[3]->s1 = m.m1;
	orbit->sprites[3]->s2 = m.b1;
	orbit->sprites[4]->pos = v2lerp(m.m2, m.b2, 0.5);
	orbit->sprites[4]->s1 = m.m2;
	orbit->sprites[4]->s2 = m.b2;
}
