/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:14:49 by clovell           #+#    #+#             */
/*   Updated: 2024/02/04 19:31:34 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ui.h"
#include "orbit.h"
#include "tasks/task_orbit.h"

static const t_button	g_button_init[] = {
	(t_button)
{
	.rect = {.pos = {10, 10}, .size = {80, 30}},
	.callback = &orbit_control_action,
	.reference = BS_THRUST, .colour = R_ALPHA | R_BLUE,
},
	(t_button)
{
	.rect = {.pos = {10, 50}, .size = {80, 30}},
	.callback = &orbit_control_action,
	.reference = BS_RTHRUST, .colour = R_ALPHA | R_RED,
},
	(t_button)
{
	.rect = {.pos = {100, 10}, .size = {80, 30}},
	.callback = &orbit_control_action,
	.reference = BS_TIME, .colour = R_ALPHA | R_BLUE,
},
	(t_button)
{
	.rect = {.pos = {100, 50}, .size = {80, 30}},
	.callback = &orbit_control_action,
	.reference = BS_RTIME, .colour = R_ALPHA | R_RED,
},
	(t_button)
{
	.rect = {.pos = {190, 10}, .size = {30, 30}},
	.callback = &orbit_control_action,
	.reference = BS_PNODE, .colour = R_ALPHA | R_BLUE | R_RED,
},
	(t_button)
{
	.rect = {.pos = {190, 50}, .size = {30, 30}},
	.callback = &orbit_control_action,
	.reference = BS_NNODE, .colour = R_ALPHA | R_RED | R_GREEN,
},
};

void	ui_setup_btn_pos(t_ui_context *ctx)
{
	int	i;

	i = -1;
	while (++i < (int)(sizeof(ctx->buttons) / sizeof(t_button)))
	{
		ctx->buttons[i].rect.max = \
		v2add(ctx->buttons[i].rect.pos, ctx->buttons[i].rect.size);
	}
}

void	ui_setup_btn(t_ui_context *ctx)
{
	int	i;

	*ctx = (t_ui_context){0};
	i = -1;
	while (++i < (int)(sizeof(ctx->buttons) / sizeof(t_button)))
		ctx->buttons[i] = g_button_init[i];
	ui_setup_btn_pos(ctx);
}

void	ui_setup(t_ui_context *ctx)
{
	ui_setup_btn(ctx);
}