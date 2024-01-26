#include <mlx.h>
#include "orbit.h"
#include "cubed.h"
#include "vector2.h"
#include "vectorconv.h"
#include "rect.h"

#define AU 1.495978707e+11
#define ARCS2DEG 0.000277778


typedef struct s_button t_button;
typedef struct s_ui_context t_ui_context;
typedef void	(*uibtn_click_cb)(t_button *, t_ui_context *);


typedef struct s_button t_button;
struct s_button
{
	t_rect			rect;
	t_texture		*texture;
	int				colour;
	void			*reference;
	void			*context;
	bool			repeat;
	uibtn_click_cb	callback;
	int				held;
};



struct s_ui_context
{
	void	*parent;
	union {
		struct s_buttons
		{
			t_button kep_prograde;	
			t_button kep_retrograde;	
		} b;
		t_button buttons[sizeof(struct s_buttons) / sizeof(t_button)]; 
	};
};

typedef struct s_sa_orbit_task
{
	t_kep_orb		kep;
	t_cart_orb		cart;
	t_orb_body		sun;
	t_texture		rt0;
	t_app 			app;
	t_ui_context	ui;
	t_inputctx		input;
} t_sa_orbit_task;

struct orbit_button_ctx
{
	t_sa_orbit_task *task;
	t_kep_orb		*kep;
};

void orbit_control_action(t_button *btn, t_ui_context *ctx)
{
	const t_sa_orbit_task *task = ctx->parent;
	const char *mode = btn->reference;
	t_cart_orb cart;

	printf("Applying thrust: %s\n", mode);
	kep_complete(&task->kep);
	orb_kepler_to_cart(task->kep, &cart);
	printf("velocity: %f\n", v3mag(cart.vel));
	if (mode[0] == '+')
		cart.vel = v3muls(cart.vel, 1.001);
	else
		cart.vel = v3muls(cart.vel, 1/1.001);
	orb_cart_to_kepler(cart, &task->kep);
	kep_complete(&task->kep);
}

void ui_setup(t_ui_context *ctx)
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

t_rect rect_getbounded(t_rect rect)
{
	t_rect result;
	result.pos = v2sub(rect.pos, v2divs(rect.size, 2));
	result.size = v2add(rect.pos, v2divs(rect.size, 2));
	return (result);
}

bool rect_contains_v2(t_rect rect, t_vec2 pos)
{
	return (pos.x >= rect.min.x && pos.y >= rect.min.y \
	&& pos.x <= rect.max.x && pos.y <= rect.max.y);
}

void ui_process_draw( t_ui_context *ctx, t_inputctx *in, t_texture target)
{
	t_button *curr;
	t_rect		aabb;
	int i;
	int colour;

	i = -1;
	while (++i < sizeof(ctx->buttons) / sizeof(t_button))
	{
		curr = &ctx->buttons[i];
		colour = curr->colour;
		aabb = curr->rect;
		if (rect_contains_v2(aabb, v2itov2(in->mouse)))
		{
			colour = R_GREEN | R_ALPHA;
			if (input_keyheld(in, MB_LEFT) && curr->callback != NULL)
				curr->callback(curr, ctx);
		}
		texture_draw_line(target, aabb.min, aabb.max, colour);
		texture_draw_line(target, aabb.min, v2new(aabb.min.x, aabb.max.y), colour);
		texture_draw_line(target, aabb.min, v2new(aabb.max.x, aabb.min.y), colour);
		texture_draw_line(target, aabb.max, v2new(aabb.max.x, aabb.min.y), colour);
		texture_draw_line(target, aabb.max, v2new(aabb.min.x, aabb.max.y), colour);
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
	double period;

	texture_clear(task->rt0, 0);
	mam = sqrt(task->kep.parent.grav / (task->kep.sma * task->kep.sma * task->kep.sma));
	ma = 45 * DEG2RAD;
	t = 0;
	period = 2 * PI * sqrt(task->kep.sma * task->kep.sma * task->kep.sma / task->kep.parent.grav);
	printf("v3:%f\n", v3dot(task->cart.pos, task->cart.vel));
	while (t < period + 1)
	{
		ma = mam * t;
		kep_elem_set(&task->kep, ma, KEP_MNA, ELEM_EXACT);
		kep_complete(&task->kep);
		orb_kepler_to_cart(task->kep, &task->cart);
		scr = orb_to_ndc(task->kep, task->cart.pos, v3new(1,1,0), 200);
		if (t != 0)
			texture_draw_line(task->rt0, v3tov2(prev), v3tov2(scr), R_RED | R_ALPHA);
		prev = scr;
		t += period / 36;
	}
	pixel_set_s(task->rt0, scr.x, scr.y, R_ALPHA | R_GREEN);
	pixel_set_s(task->rt0, 200, 200, R_ALPHA | R_GREEN);
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

int main(void)
{
	t_sa_orbit_task task;

	task.sun = orb_body_create_rm(6.96340e8, 1.9891E30);
	task.kep = (t_kep_orb){0};
	task.kep.parent = task.sun;
	task.kep.self = orb_body_create_rm(6378100, 5.9722E24);
	kep_elem_set(&task.kep, 1.00000011 * AU, KEP_SMA, ELEM_EXACT);
	kep_elem_set(&task.kep, 0.516708617, KEP_ECC, ELEM_EXACT);
	kep_elem_set(&task.kep, 45 * DEG2RAD, KEP_INC, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_LAN, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_TA, ELEM_EXACT);

	kep_elem_set(&task.kep, 1.00000011 * AU, KEP_SMA, ELEM_EXACT);
	kep_elem_set(&task.kep, 0.7167, KEP_ECC, ELEM_EXACT);
	kep_elem_set(&task.kep, 1 * DEG2RAD, KEP_INC, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_LAN, ELEM_EXACT);
	kep_elem_set(&task.kep, 0, KEP_TA, ELEM_EXACT);
	kep_elem_set(&task.kep, 0 * DEG2RAD, KEP_AOP, ELEM_EXACT);
	kep_complete(&task.kep);
	orb_kepler_to_cart(task.kep, &task.cart);
	task.app.mlx = mlx_init();
	task.app.win = mlx_new_window(task.app.mlx, 400, 400, "ORBIT");
	task.rt0 = texture_create(task.app.mlx, 400, 400);
	input_setup(task.app.mlx, task.app.win, &task.input);
	ui_setup(&task.ui);
	task.ui.parent = &task;
	mlx_loop_hook(task.app.mlx, &orbit_render, &task);
	mlx_loop(task.app.mlx);
	return (0);
}