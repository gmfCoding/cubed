#include <mlx.h>
#include "orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"

#define AU 1.495978707e+11
#define ARCS2DEG 0.000277778


typedef struct s_button		t_button;
typedef struct s_ui_context	t_ui_context;
typedef void				(*t_uibtn_click_cb)(t_button *, t_ui_context *);


typedef struct s_button	t_button;
struct s_button
{
	t_rect				rect;
	t_texture			*texture;
	int					colour;
	void				*reference;
	void				*context;
	bool				repeat;
	t_uibtn_click_cb	callback;
	int					held;
};



struct s_ui_context
{
	void	*parent;
	union {
		struct s_buttons
		{
			t_button	kep_prograde;	
			t_button	kep_retrograde;	
		} b;
		t_button	buttons[sizeof(struct s_buttons) / sizeof(t_button)];
	};
};

typedef struct s_sa_orbit_task
{
	t_orb_obj		obj0;
	t_kep_path		obj_path;
	t_orb_cart		cart;
	t_orb_body		sun;
	t_texture		rt0;
	t_app			app;
	t_ui_context	ui;
	t_inputctx		input;
}	t_sa_orbit_task;

struct s_orbit_button_ctx
{
	t_sa_orbit_task	*task;
	t_orb_obj		*kep;
};

void	orbit_control_action(t_button *btn, t_ui_context *ctx)
{
	const t_sa_orbit_task	*task = ctx->parent;
	const char				*mode = btn->reference;
	t_orb_cart *const		cart = &task->obj0.cart;

	printf("Applying thrust: %s\n", mode);
	orb_cart_vel(&task->obj0.path, &task->obj0.ang, cart);
	printf("velocity: %f\n", v3mag(cart->vel));
	if (mode[0] == '+')
		cart->vel = v3muls(cart->vel, 1.001);
	else
		cart->vel = v3muls(cart->vel, 1 / 1.001);
	orb_cart_to_kep(cart, &task->obj0.path, &task->obj0.ang);
}

void	ui_setup(t_ui_context *ctx)
{
	*ctx = (t_ui_context){0}; 
	ctx->b.kep_retrograde = (t_button){
		.rect = (t_rect){.min = v2new(10, 10), .max = v2new(90, 40)},
		.callback = &orbit_control_action,
		.reference = "-",
		.colour = R_ALPHA | R_RED,
	};
	ctx->b.kep_prograde = (t_button){
		.rect = (t_rect){.min = v2new(100, 10), .max = v2new(180, 40)},
		.callback = &orbit_control_action,
		.reference = "+",
		.colour = R_ALPHA | R_BLUE,
	};
}

t_rect	rect_getbounded(t_rect rect)
{
	t_rect result;
	result.pos = v2sub(rect.pos, v2divs(rect.size, 2));
	result.size = v2add(rect.pos, v2divs(rect.size, 2));
	return (result);
}

bool	rect_contains_v2(t_rect rect, t_vec2 pos)
{
	return (pos.x >= rect.min.x && pos.y >= rect.min.y \
	&& pos.x <= rect.max.x && pos.y <= rect.max.y);
}

void	ui_process_draw( t_ui_context *ctx, t_inputctx *in, t_texture target)
{
	t_button	*curr;
	t_rect		aabb;
	int			i;
	int			col;

	i = -1;
	while (++i < sizeof(ctx->buttons) / sizeof(t_button))
	{
		curr = &ctx->buttons[i];
		col = curr->colour;
		aabb = curr->rect;
		if (rect_contains_v2(aabb, v2itov2(in->mouse)))
		{
			col = R_GREEN | R_ALPHA;
			if (input_keyheld(in, MB_LEFT) && curr->callback != NULL)
				curr->callback(curr, ctx);
		}
		texture_draw_line(target, aabb.min, aabb.max, col);
		texture_draw_line(target, aabb.min, v2new(aabb.min.x, aabb.max.y), col);
		texture_draw_line(target, aabb.min, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.max.x, aabb.min.y), col);
		texture_draw_line(target, aabb.max, v2new(aabb.min.x, aabb.max.y), col);
	}
}

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

int	sa_task_orbit_process(t_sa_orbit_task *task)
{
	texture_clear(task->rt0, 0);
	orbit_path_render(&task->obj0, &task->rt0);
	orbit_obj_render(&task->obj0, &task->rt0);
	usleep(16666);
	ui_process_draw(&task->ui, &task->input, task->rt0);
	texture_draw(task->app, task->rt0, v2new(0,0));
	l_draw_debug_info(task);
	input_process(&task->input);
}

// void draw_element_controls(t_sa_orbit_task *task)
// {
// 	if (input_keydown())
// }

int	main(void)
{
	t_sa_orbit_task	task;

	task.obj0 = (t_orb_obj){0};
	task.sun = orb_body_create_rm(6.96340e8, 1.9891e30);
	//task.earth = orb_body_create_rm(6378100, 5.9722E24);
	task.obj0.self = task.sun;
	task.obj0.path.sma = 1.00000011 * KM_AU;
	//task.obj0.path.ecc = 0.0;
	task.obj0.path.ecc = 0.516708617;
	task.obj0.path.inc = 0 * DEG2RAD;
	//task.obj0.path.inc = 45 * DEG2RAD;
	task.obj0.path.lan = 0 * KM_AU;
	task.obj0.path.sgp_u = task.sun.u;
	task.obj0.ang.s_0.mna0 = 0;
	task.obj0.ang.s_0.time0 = 0;
	task.obj0.ang.time = 0;
	kep_ang_set(&task.obj0.path, &task.obj0.ang, 0);
	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	input_setup(task.app.mlx, task.app.win, &task.input);
	ui_setup(&task.ui);
	task.ui.parent = &task;
	mlx_loop_hook(task.app.mlx, &sa_task_orbit_process, &task);
	mlx_loop(task.app.mlx);
	return (0);
}
