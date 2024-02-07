/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_mui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:04 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 16:17:15 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tasks/mui.h"
#include "tasks/task_orbit.h"



const char	*g_orb_mui_apply_paths[] = {
	"assets/orbit/panel/apply_0.xpm",
	"assets/orbit/panel/apply_1.xpm",
	"assets/orbit/panel/apply_2.xpm",
	"assets/orbit/panel/apply_3.xpm",
	NULL
};

const char	*g_orb_mui_mselector_paths[] = {
	"assets/orbit/panel/selector_0.xpm",
	"assets/orbit/panel/selector_1.xpm",
	"assets/orbit/panel/selector_2.xpm",
	"assets/orbit/panel/selector_3.xpm",
	NULL
};

const char	*g_orb_mui_mdial_paths[] = {
	"assets/orbit/panel/meandial_0.xpm",
	"assets/orbit/panel/meandial_1.xpm",
	"assets/orbit/panel/meandial_2.xpm",
	"assets/orbit/panel/meandial_3.xpm",
	"assets/orbit/panel/meandial_4.xpm",
	"assets/orbit/panel/meandial_5.xpm",
	"assets/orbit/panel/meandial_6.xpm",
	"assets/orbit/panel/meandial_7.xpm",
	"assets/orbit/panel/meandial_8.xpm",
	"assets/orbit/panel/meandial_9.xpm",
	"assets/orbit/panel/meandial_10.xpm",
	"assets/orbit/panel/meandial_11.xpm",
	"assets/orbit/panel/meandial_12.xpm",
	"assets/orbit/panel/meandial_13.xpm",
	"assets/orbit/panel/meandial_14.xpm",
	"assets/orbit/panel/meandial_15.xpm",
	"assets/orbit/panel/meandial_16.xpm",
	"assets/orbit/panel/meandial_17.xpm",
	"assets/orbit/panel/meandial_18.xpm",
	"assets/orbit/panel/meandial_19.xpm",
	NULL
};

const char	*g_orb_mui_mscreendial_paths[] = {
	"assets/orbit/panel/screendial_0.xpm",
	"assets/orbit/panel/screendial_1.xpm",
	"assets/orbit/panel/screendial_2.xpm",
	"assets/orbit/panel/screendial_3.xpm",
	"assets/orbit/panel/screendial_4.xpm",
	"assets/orbit/panel/screendial_5.xpm",
	"assets/orbit/panel/screendial_6.xpm",
	"assets/orbit/panel/screendial_7.xpm",
	"assets/orbit/panel/screendial_8.xpm",
	"assets/orbit/panel/screendial_9.xpm",
	"assets/orbit/panel/screendial_10.xpm",
	"assets/orbit/panel/screendial_11.xpm",
	"assets/orbit/panel/screendial_12.xpm",
	"assets/orbit/panel/screendial_13.xpm",
	"assets/orbit/panel/screendial_14.xpm",
	"assets/orbit/panel/screendial_15.xpm",
	"assets/orbit/panel/screendial_16.xpm",
	"assets/orbit/panel/screendial_17.xpm",
	"assets/orbit/panel/screendial_18.xpm",
	"assets/orbit/panel/screendial_19.xpm",
	NULL
};

const char	*g_orb_mui_mindicator_paths[] = {
	"assets/orbit/panel/thrustindicator_0.xpm",
	"assets/orbit/panel/thrustindicator_1.xpm",
	"assets/orbit/panel/thrustindicator_2.xpm",
	"assets/orbit/panel/thrustindicator_3.xpm",
	"assets/orbit/panel/thrustindicator_4.xpm",
	"assets/orbit/panel/thrustindicator_5.xpm",
	"assets/orbit/panel/thrustindicator_6.xpm",
	"assets/orbit/panel/thrustindicator_7.xpm",
	"assets/orbit/panel/thrustindicator_8.xpm",
	"assets/orbit/panel/thrustindicator_9.xpm",
	"assets/orbit/panel/thrustindicator_10.xpm",
	"assets/orbit/panel/thrustindicator_11.xpm",
	"assets/orbit/panel/thrustindicator_12.xpm",
	"assets/orbit/panel/thrustindicator_13.xpm",
	"assets/orbit/panel/thrustindicator_14.xpm",
	"assets/orbit/panel/thrustindicator_15.xpm",
	"assets/orbit/panel/thrustindicator_16.xpm",
	"assets/orbit/panel/thrustindicator_17.xpm",
	"assets/orbit/panel/thrustindicator_18.xpm",
	"assets/orbit/panel/thrustindicator_19.xpm",
	NULL
};

const char	*g_orb_mui_mthrot_paths[] = {
	"assets/orbit/panel/throttle_0.xpm",
	"assets/orbit/panel/throttle_1.xpm",
	"assets/orbit/panel/throttle_2.xpm",
	"assets/orbit/panel/throttle_3.xpm",
	"assets/orbit/panel/throttle_4.xpm",
	"assets/orbit/panel/throttle_5.xpm",
	"assets/orbit/panel/throttle_6.xpm",
	"assets/orbit/panel/throttle_7.xpm",
	"assets/orbit/panel/throttle_8.xpm",
	"assets/orbit/panel/throttle_9.xpm",
	"assets/orbit/panel/throttle_10.xpm",
	"assets/orbit/panel/throttle_11.xpm",
	"assets/orbit/panel/throttle_12.xpm",
	"assets/orbit/panel/throttle_13.xpm",
	"assets/orbit/panel/throttle_14.xpm",
	"assets/orbit/panel/throttle_15.xpm",
	"assets/orbit/panel/throttle_16.xpm",
	"assets/orbit/panel/throttle_17.xpm",
	"assets/orbit/panel/throttle_18.xpm",
	"assets/orbit/panel/throttle_19.xpm",
	NULL
};

static t_mui_button g_mui_orbit_buttons[] = {
[ORB_MUI_BTN_APPLY] = {
	.base = {.pos = {23, 306}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_apply_paths,
	.rect = {.min = {23, 306}, .max = {50, 331}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = false
},
[ORB_MUI_BTN_MS0] = {
	.base = {.pos = {124, 351}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {124, 351}, .max = {149, 374}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS1] = {
	.base = {.pos = {177, 351,}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {177, 351}, .max = {202, 374}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS2] = {
	.base = {.pos = {231, 351}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {231, 351}, .max = {255, 374}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS3] = {
	.base = {.pos = {284, 351, }, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {284, 351}, .max = {309, 374}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = true
},
[ORB_MUI_BTN_MS4] = {
	.base = {.pos = {337, 351}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {337, 351}, .max = {362, 374}},
	.type = MUI_BUTTON, .unlock = true},
	.on = false,
	.toggle = true
},
};

static t_mui_dial g_mui_orbit_dials[] = {
[ORB_MUI_DIAL_M0] = {
	.base = {.pos = {124, 326}, .anim = 0, .frame = 0, .frames = 4,
	.paths = g_orb_mui_mselector_paths,
	.rect = {.min = {124, 326}, .max = {148, 347}},
	.type = MUI_BUTTON, .unlock = true},
	.angle = 0,
	.range = {-INT16_MAX * M_PI, INT16_MAX * M_PI},
},
};

static t_mui_slider g_mui_orbit_sliders[] = {
	
};

const t_mui_ctx g_orbit_mui = {
	.buttons = g_mui_orbit_buttons,
	.len_buttons = sizeof(g_mui_orbit_buttons) / sizeof(t_mui_button),

	.dials = g_mui_orbit_dials,
	.len_dials = sizeof(g_mui_orbit_dials) / sizeof(t_mui_dial),

	.sliders = g_mui_orbit_sliders,
	.len_sliders = sizeof(g_mui_orbit_sliders) / sizeof(t_mui_slider),
	.heap = false,
};