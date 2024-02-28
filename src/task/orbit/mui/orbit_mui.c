/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_mui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:04 by clovell           #+#    #+#             */
/*   Updated: 2024/02/28 17:26:48 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tasks/mui.h"
#include "tasks/task_orbit.h"
#include "def_tex.h"

static const t_def_tex		g_orb_textures[] = {
{
	.id = "orb_mui_bg",
	.path = "assets/orbit/panel/panel",
	.frames = 1,
},
{
	.id = "orb_mui_scr",
	.path = "assets/orbit/panel/screen",
	.frames = 1,
},
{
	.id = "orb_mui_apply",
	.path = "assets/orbit/panel/apply_",
	.frames = 4,
},
{
	.id = "orb_mui_mselector",
	.path = "assets/orbit/panel/selector_",
	.frames = 4,
},
{
	.id = "orb_mui_meandial",
	.path = "assets/orbit/panel/meandial_",
	.frames = 20,
},
{
	.id = "orb_mui_screendial",
	.path = "assets/orbit/panel/screendial_",
	.frames = 20,
},
{
	.id = "orb_mui_ind",
	.path = "assets/orbit/panel/thrustindicator_",
	.frames = 20,
},
{
	.id = "orb_mui_throttle",
	.path = "assets/orbit/panel/throttle_",
	.frames = 20,
}
};

static const t_mui_button	g_mui_orbit_buttons[] = {
[ORB_MUI_BTN_MS0] = {
	.base = {.pos = {124, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {124, 349}, .max = {149, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS1] = {
	.base = {.pos = {177, 349,}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {177, 349}, .max = {202, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS2] = {
	.base = {.pos = {231, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {231, 349}, .max = {255, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS3] = {
	.base = {.pos = {284, 349, }, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {284, 349}, .max = {309, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS4] = {
	.base = {.pos = {337, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {337, 349}, .max = {362, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_APPLY] = {
	.base = {.pos = {23, 306}, .anim = 0, .frame = 0,
	.id = "orb_mui_apply", .unlock = true,
	.rect = {.min = {23, 306}, .max = {50, 331}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = false
},
};

static const t_mui_dial		g_mui_orbit_dials[] = {
[ORB_MUI_DIAL_M0] = {
	.base = {.pos = {122, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {.min = {122, 325}, .max = {152, 350}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI},
},
[ORB_MUI_DIAL_M1] = {
	.base = {.pos = {176, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {.min = {176, 325}, .max = {204, 350}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M2] = {
	.base = {.pos = {229, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {231, 325, 257, 350},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M3] = {
	.base = {.pos = {283, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {.min = {285, 325}, .max = {311, 350}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M4] = {
	.base = {.pos = {336, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {.min = {336, 325}, .max = {364, 350}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_X] = {
	.base = {.pos = {285, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {285, 301}, .max = {303, 318}},
	.type = MUI_DIAL},
	.angle = 161,
	.range = {-500, 500}
},
[ORB_MUI_DIAL_Y] = {
	.base = {.pos = {305, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {305, 301}, .max = {323, 319}},
	.type = MUI_DIAL},
	.angle = 150,
	.range = {-500, 500}
},
[ORB_MUI_DIAL_Z] = {
	.base = {.pos = {325, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {325, 301}, .max = {343, 318}},
	.type = MUI_DIAL},
	.angle = 70,
	.range = {50, 500}
},
[ORB_MUI_DIAL_B] = {
	.base = {.pos = {344, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {344, 301}, .max = {362, 318}},
	.type = MUI_DIAL},
	.angle = 1.0,
	.range = {0.0, 1.0}
},
};

static const t_mui_slider	g_mui_orbit_sliders[] = {
[ORB_MUI_SLD_THROTTLE] = {
	.base = {.pos = {61, 298}, .anim = 0, .frame = 0,
	.id = "orb_mui_throttle", .unlock = true,
	.rect = {.min = {61, 303}, .max = {100, 376}},
	.type = MUI_SLIDE},
	.start = {61, 303},
	.end = {61, 376},
	.value = 0.5,
	.rest = 0.5, .elastic = true},
};

static const t_mui_base		g_mui_orbit_inds[] = {
[ORB_MUI_IND0] = {
	.pos = {110, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	// .rect = {.min = {124, 349}, .max = {149, 374}},
	.type = MUI_BUTTON
},
[ORB_MUI_IND1] = {
	.pos = {163, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	// .rect = {.min = {177, 349}, .max = {202, 374}},
	.type = MUI_BUTTON
},
[ORB_MUI_IND2] = {
	.pos = {217, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	// .rect = {.min = {231, 349}, .max = {255, 374}},
	.type = MUI_BUTTON
},
[ORB_MUI_IND3] = {
	.pos = {270, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	// .rect = {.min = {284, 349}, .max = {309, 374}},
	.type = MUI_BUTTON
},
[ORB_MUI_IND4] = {
	.pos = {323, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	// .rect = {.min = {337, 349}, .max = {362, 374}},
	.type = MUI_BUTTON
},
};

static const t_mui_ctx		g_orbit_mui = {
	.buttons = (t_mui_button *)g_mui_orbit_buttons,
	.len_buttons = sizeof(g_mui_orbit_buttons) / sizeof(t_mui_button),
	.size_buttons = sizeof(t_mui_button),
	.dials = (t_mui_dial *)g_mui_orbit_dials,
	.len_dials = sizeof(g_mui_orbit_dials) / sizeof(t_mui_dial),
	.size_dials = sizeof(t_mui_dial),
	.sliders = (t_mui_slider *)g_mui_orbit_sliders,
	.len_sliders = sizeof(g_mui_orbit_sliders) / sizeof(t_mui_slider),
	.size_sliders = sizeof(t_mui_slider),
	.inds = (t_mui_base *)g_mui_orbit_inds,
	.len_inds = sizeof(g_mui_orbit_inds) / sizeof(t_mui_base),
	.size_inds = sizeof(t_mui_base),
	.heap = false,
	.oscale = 400.0,
	.scale = 800,
	.offset = {90.0 , 90.0}
};

void	mui_orbit_setup(t_app *app, t_mui_ctx *mui)
{
	const int	g_len_tex = sizeof(g_orb_textures) / sizeof(t_def_tex);

	mui_clone(&g_orbit_mui, mui);
	def_tex_add(g_orb_textures, g_len_tex);
	mui_def_preload(app, mui);
}

void	orbit_mui_control_action(t_mui_ctx *ctx)
{
	t_task_orbit *const	task = ctx->ctx;
	int						i;

	task->scr_offset.x = ctx->dials[ORB_MUI_DIAL_X].angle;
	task->scr_offset.y = ctx->dials[ORB_MUI_DIAL_Y].angle;
	task->zoom = ctx->dials[ORB_MUI_DIAL_Z].angle;
	task->brightness = ctx->dials[ORB_MUI_DIAL_B].angle;
	i = -1;
	while (++i < ctx->len_buttons)
		if (ctx->buttons[i].on && i < T_ORBIT_MAX_MAN)
			task->active_path = i;
	i = -1;
	while (++i < ctx->len_dials)
		if (i < T_ORBIT_MAX_MAN)
			task->mean[i] = ctx->dials[i].angle;
	i = -1;
	task->delta[task->active_path] += (ctx->sliders[0].value - 0.5) / 100.0;
	update_paths(task);
}
