#include "vector2.h"

t_vec2	v2divs(t_vec2 f, t_vecd s)
{
	t_vec2	vec;

	vec.x = f.x / s;
	vec.y = f.y / s;
	return (vec);
}

t_vec2	v2sdiv(t_vecd s, t_vec2 f)
{
	t_vec2	vec;

	vec.x = s / f.x;
	vec.y = s / f.y;
	return (vec);
}

t_vec2	v2inv(t_vec2 f)
{
	t_vec2	vec;

	vec.x = 1.0 / f.x;
	vec.y = 1.0 / f.y;
	return (vec);
}

t_vec2	v2norm(t_vec2 vec)
{
	t_vecd	mag;

	mag = v2mag(vec);
	if (mag == 0)
		return (v2new(0, 0));
	vec.x /= mag;
	vec.y /= mag;
	return (vec);
}