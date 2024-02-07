/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_mui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:04 by clovell           #+#    #+#             */
/*   Updated: 2024/02/08 00:32:13 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tasks/mui.h"
#include "tasks/task_orbit.h"
#include "def_tex.h"

const t_def_tex g_orb_textures[] = {
{
	.id = "orb_mui_background",
	.path = "assets/orbit/panel/panel",
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
	.id = "orb_mui_mindicator",
	.path = "assets/orbit/panel/thrustindicator_",
	.frames = 20,
},
{
	.id = "orb_mui_throttle",
	.path = "assets/orbit/panel/throttle_",
	.frames = 20,
}
};

const size_t	g_orb_textures_len = sizeof(g_orb_textures) \
	/ sizeof(t_def_tex);

static t_mui_button g_mui_orbit_buttons[] = {
[ORB_MUI_BTN_APPLY] = {
	.base = {.pos = {23, 306}, .anim = 0, .frame = 0,
	.id = "orb_mui_apply", .unlock = true,
	.rect = {.min = {23, 306}, .max = {50, 331}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = false
},
[ORB_MUI_BTN_MS0] = {
	.base = {.pos = {124, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {124, 349}, .max = {149, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS1] = {
	.base = {.pos = {177, 349,}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {177, 349}, .max = {202, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS2] = {
	.base = {.pos = {231, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {231, 349}, .max = {255, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS3] = {
	.base = {.pos = {284, 349, }, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {284, 349}, .max = {309, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS4] = {
	.base = {.pos = {337, 349}, .anim = 0, .frame = 0,
	.id = "orb_mui_mselector", .unlock = true,
	.rect = {.min = {337, 349}, .max = {362, 374}},
	.type = MUI_BUTTON},
	.on = false,
	.toggle = true
},
};

static t_mui_dial g_mui_orbit_dials[] = {
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
	.rect = {{231, 325}, {257, 350}},
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
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_Y] = {
	.base = {.pos = {305, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {305, 301}, .max = {323, 319}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_Z] = {
	.base = {.pos = {325, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {325, 301}, .max = {343, 318}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
[ORB_MUI_DIAL_B] = {
	.base = {.pos = {344, 301}, .anim = 0, .frame = 0,
	.id = "orb_mui_screendial", .unlock = true,
	.rect = {.min = {344, 301}, .max = {362, 318}},
	.type = MUI_DIAL},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI}
},
};

static t_mui_slider g_mui_orbit_sliders[] = {
[ORB_MUI_SLD_THROTTLE] = {
	.base = {.pos = {61, 298}, .anim = 0, .frame = 0,
	.id = "orb_mui_throttle", .unlock = true,
	.rect = {.min = {61, 303}, .max = {100, 376}},
	.type = MUI_SLIDE},
	.start = {61, 303},
	.end = {100, 376}}
};

const t_mui_ctx g_orbit_mui = {
	.buttons = g_mui_orbit_buttons,
	.len_buttons = sizeof(g_mui_orbit_buttons) / sizeof(t_mui_button),
	.size_buttons = sizeof(t_mui_button),

	.dials = g_mui_orbit_dials,
	.len_dials = sizeof(g_mui_orbit_dials) / sizeof(t_mui_dial),
	.size_dials = sizeof(t_mui_dial),

	.sliders = g_mui_orbit_sliders,
	.len_sliders = sizeof(g_mui_orbit_sliders) / sizeof(t_mui_slider),
	.size_sliders = sizeof(t_mui_slider),
	.heap = false,
};