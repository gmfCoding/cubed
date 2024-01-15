#include <mlx.h>
#include "orbit.h"
#include "cubed.h"
#include "vectorconv.h"

#define AU 1.495978707e+11
#define ARCS2DEG 0.000277778

typedef struct s_sa_orbit_task
{
	t_kep_orb	kep;
	t_cart_orb	cart;
	t_orb_body	sun;
	t_texture	rt0;
	t_app app;
} t_sa_orbit_task;

#define SEC_YEAR 3.154E7
static void	l_draw_debug_info(t_sa_orbit_task *task)
{
	static int64_t	timeprev = 0;
	const char		*debugstr[] = {
		ft_strfmt("fps:%d", (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0))),
	};
	int				i;

	i = -1;
	while (++i < sizeof(debugstr) / sizeof(*debugstr))
	{
		mlx_string_put(task->app.mlx, task->app.win, 0, \
			i * 12 + 12, 0xFFFFFF, debugstr[i]);
		free(debugstr[i]);
	}
	timeprev = time_get_ms();
}

t_vec3	orb_to_ndc(t_kep_orb kep, t_vec3 cart, t_vec3 offset, t_vecd scale)
{
	t_vec3	dev;
	dev = v3divs(cart, kep.apo);
	dev = v3add(dev, offset);
	dev = v3muls(dev, scale);
	return (dev);
}

int	orbit_render(t_sa_orbit_task *task)
{
	double t;
	double ma;
	double mam;
	t_vec3	scr;
	t_vec3	prev;

	mam = sqrt(task->kep.body.grav / (task->kep.sma * task->kep.sma * task->kep.sma));
	ma = 45 * DEG2RAD;
	t = 0;
	while (t < SEC_YEAR + 1)
	{
		ma = mam * t;
		kep_elem_set(&task->kep, ma, KEP_MNA, ELEM_EXACT);
		kep_complete(&task->kep);
		orb_kepler_to_cart(task->kep, &task->cart);
		scr = orb_to_ndc(task->kep, task->cart.position, v3new(1,1,0), 200);
		if (t != 0)
			texture_draw_line(task->rt0, v3tov2(prev), v3tov2(scr), R_RED | R_ALPHA);
		//pixel_set_s(task->rt0, scr.x + 1, scr.y + 1, R_GREEN | R_ALPHA);
		prev = scr;
		t += SEC_YEAR / 36;
	}
	static double aop = 0;
	aop += 0.05f;
	kep_elem_set(&task->kep, aop, KEP_LAN, ELEM_EXACT);
	kep_elem_set(&task->kep, -aop * 2, KEP_AOP, ELEM_EXACT);
	usleep(16666);
	texture_draw(task->app, task->rt0, v2new(0,0));
	l_draw_debug_info(task);
}

int main(void)
{
	t_sa_orbit_task task;

	task.sun = orb_body_create(6.96340e8, 1406.313);
	task.kep = (t_kep_orb){0};
	task.kep.body = task.sun;
	kep_elem_set(&task.kep, 1.00000011 * AU, KEP_SMA, ELEM_EXACT);
	kep_elem_set(&task.kep, 0.716708617, KEP_ECC, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_INC, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_LAN, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_TA, ELEM_EXACT);
	kep_elem_set(&task.kep, 40 * DEG2RAD, KEP_AOP, ELEM_EXACT);
	kep_complete(&task.kep);
	orb_kepler_to_cart(task.kep, &task.cart);
	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	orbit_render(&task);
	mlx_loop_hook(task.app.mlx, &orbit_render, &task);
	mlx_loop(task.app.mlx);
	return (0);
}