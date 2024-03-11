/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_mui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:04 by clovell           #+#    #+#             */
/*   Updated: 2024/03/04 19:15:46 by clovell          ###   ########.fr       */
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
	.base = {.pos = {ORB_MS0_X, ORB_MSA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {ORB_MS0_X, ORB_MSA_Y},
	.max = {ORB_MS0_MAX_X, ORB_MSA_MAX_Y}},
	.type = MUI_BUTTON},
	.on = true,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS1] = {
	.base = {.pos = {ORB_MS1_X, ORB_MSA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {ORB_MS1_X, ORB_MSA_Y},
	.max = {ORB_MS1_MAX_X, ORB_MSA_MAX_Y}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS2] = {
	.base = {.pos = {ORB_MS2_X, ORB_MSA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {ORB_MS2_X, ORB_MSA_Y},
	.max = {ORB_MS2_MAX_X, ORB_MSA_MAX_Y}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS3] = {
	.base = {.pos = {ORB_MS3_X, ORB_MSA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {ORB_MS3_X, ORB_MSA_Y},
	.max = {ORB_MS3_MAX_X, ORB_MSA_MAX_Y}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_MS4] = {
	.base = {.pos = {ORB_MS4_X, ORB_MSA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {ORB_MS4_X, ORB_MSA_Y},
	.max = {ORB_MS4_MAX_X, ORB_MSA_MAX_Y}},
	.type = MUI_BUTTON},
	.on = false,
	.group = 1,
	.toggle = true
},
[ORB_MUI_BTN_APPLY] = {
	.base = {.pos = {ORB_APL_X, ORB_APL_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_apply", .unlock = true,
	.rect = {.min = {ORB_APL_X, ORB_APL_Y},
	.max = {ORB_APL_MAX_X, ORB_APL_MAX_Y}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = false
},
};

static const t_mui_dial		g_mui_orbit_dials[] = {
[ORB_MUI_DIAL_M0] = {
	.base = {.pos = {122, ORB_DMA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {ORB_DMS0_X, ORB_DMA_Y, ORB_DMS0_MAX_X, ORB_DMA_MAX_Y},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI},
},
[ORB_MUI_DIAL_M1] = {
	.base = {.pos = {176, ORB_DMA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {ORB_DMS1_X, ORB_DMA_Y, ORB_DMS1_MAX_X, ORB_DMA_MAX_Y},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M2] = {
	.base = {.pos = {229, ORB_DMA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {ORB_DMS2_X, ORB_DMA_Y, ORB_DMS2_MAX_X, ORB_DMA_MAX_Y},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M3] = {
	.base = {.pos = {283, ORB_DMA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {ORB_DMS3_X, ORB_DMA_Y, ORB_DMS3_MAX_X, ORB_DMA_MAX_Y},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_M4] = {
	.base = {.pos = {336, ORB_DMA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_meandial", .unlock = true,
	.rect = {ORB_DMS4_X, ORB_DMA_Y, ORB_DMS4_MAX_X, ORB_DMA_MAX_Y},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_X] = {
	.base = {.pos = {ORB_BX_X, ORB_BA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {ORB_BX_X, ORB_BA_Y}, .max = {ORB_BX_MAX_X, ORB_BX_MAX_Y}},
	.type = MUI_DIAL},
	.angle = 161,
	.range = {-500, 500}
},
[ORB_MUI_DIAL_Y] = {
	.base = {.pos = {ORB_BY_X, ORB_BA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {ORB_BY_X, ORB_BA_Y, ORB_BY_MAX_X, ORB_BY_MAX_Y},
	.type = MUI_DIAL},
	.angle = 150,
	.range = {-500, 500}
},
[ORB_MUI_DIAL_Z] = {
	.base = {.pos = {ORB_BZ_X, ORB_BA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {ORB_BZ_X, ORB_BA_Y, ORB_BZ_MAX_X, ORB_BZ_MAX_Y},
	.type = MUI_DIAL},
	.angle = 70,
	.range = {50, 500}
},
[ORB_MUI_DIAL_B] = {
	.base = {.pos = {ORB_BB_X, ORB_BA_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {ORB_BB_X, ORB_BA_Y, ORB_BB_MAX_X, ORB_BB_MAX_Y},
	.type = MUI_DIAL},
	.angle = 1.0,
	.range = {0.0, 1.0}
},
};

static const t_mui_slider	g_mui_orbit_sliders[] = {
[ORB_MUI_SLD_THROTTLE] = {
	.base = {.pos = {ORB_THRTL_X, ORB_THRTL_Y}, .anim = 0, .frame = 0,
	.id = "orb_mui_throttle", .unlock = true,
	.rect = {ORB_THRTL_X, ORB_THRTL_Y, ORB_THRTL_MAX_X, ORB_THRTL_MAX_Y},
	.type = MUI_SLIDE},
	.start = {ORB_THRTL_X, ORB_THRTL_Y},
	.end = {ORB_THRTL_X, ORB_THRTL_MAX_Y},
	.value = 0.5,
	.rest = 0.5, .elastic = true},
};

static const t_mui_base		g_mui_orbit_inds[] = {
[ORB_MUI_IND0] = {
	.pos = {110, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	.type = MUI_BUTTON
},
[ORB_MUI_IND1] = {
	.pos = {163, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	.type = MUI_BUTTON
},
[ORB_MUI_IND2] = {
	.pos = {217, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
	.type = MUI_BUTTON
},
[ORB_MUI_IND3] = {
	.pos = {270, 325}, .anim = 0, .frame = 0,
	.id = "orb_mui_ind", .unlock = true,
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
	.oscale = 400.0,
	.scale = 800,
	.offset = {90.0, 90.0}
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
	t_task_orbit *const	t = ctx->ctx;
	int					i;

	t->scr_offset.x = ctx->dials[ORB_MUI_DIAL_X].angle;
	t->scr_offset.y = ctx->dials[ORB_MUI_DIAL_Y].angle;
	t->zoom = ctx->dials[ORB_MUI_DIAL_Z].angle;
	t->brightness = ctx->dials[ORB_MUI_DIAL_B].angle;
	i = -1;
	while (++i < ctx->len_buttons)
		if (ctx->buttons[i].on && i < T_ORBIT_MAX_MAN)
			t->active_path = i;
	i = -1;
	while (++i < ctx->len_dials)
		if (i < T_ORBIT_MAX_MAN)
			t->mean[i] = ctx->dials[i].angle;
	i = -1;
	t->delta[t->active_path] += (ctx->sliders[0].value - 0.5) / 100.0;
	if (orb_deviation(&t->target_path, &t->paths[t->maneuvers - 1]) < 0.05)
		t->task.show = !(ctx->buttons[ORB_MUI_BTN_APPLY].on);
	update_paths(t);
}
