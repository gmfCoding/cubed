#include "cubed.h"
#include "vectorconv.h"
#include "orbit.h"

t_vec3	orb_to_ndc(t_kep_path *path, t_vec3 cart, t_vec3 offset, t_vecd scale)
{
	t_vec3	dev;

	dev = v3divs(cart, path->sma);
	dev = v3add(dev, offset);
	dev = v3muls(dev, scale);
	return (dev);
}

void	orbit_path_render(t_kep_path *path, t_texture *rt)
{
	double		t;
	t_kep_ang	ang;
	t_vec3		pos;
	t_vec3		prev;
	double		period;

	t = 0;
	period = kep_period(path);
	while (t < period + 1)
	{
		kep_ang_set(path, &ang, t);
		orb_pos(path, &ang, &pos);
		pos = orb_to_ndc(path, pos, v3new(2, 2, 0), 100);
		if (t != 0)
			texture_draw_line(*rt, v3tov2(prev), v3tov2(pos), R_RED | R_ALPHA);
		prev = pos;
		t += period / 100;
	}
}

void	orbit_obj_render(t_orb_obj *obj, t_texture *rt)
{
	double		t;
	t_vec3		pos;

	orb_pos(&obj->path, &obj->ang, &pos);
	pos = orb_to_ndc(&obj->path, pos, v3new(2, 2, 0), 100);
	pixel_set_s(*rt, pos.x, pos.y, R_ALPHA | R_GREEN);
}
