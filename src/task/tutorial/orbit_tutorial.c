/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_tutorial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:17:13 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 18:24:09 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "tasks/tutorial.h"
#include "tasks/mui_orbit.h"

// static const t_list g_orb_tips[] = {
// 	{.content = "Welcome to the orbit task!\n"}
// }

static const t_task_tip	g_orb_tips[] = {
{
	.content = "Welcome to the orbit task!\n"\
	"Your goal is to modify your orbit by applying thrust at certain "\
	"angles along your orbit\n But watch out you only have five attempts.",
	.region = {0, 0, 0, 0},
},
{
	.content = "You can control your thrust with the thrust control slider.",
	.region = {ORB_THRTL_X, ORB_THRTL_Y, ORB_APL_MAX_X, ORB_APL_MAX_Y},
},
{
	.content = "And you can specify the mean (angle) with the mean dial.",
	.region = {ORB_DMS0_X, ORB_DMA_Y, ORB_DMS0_MAX_X, ORB_DMA_MAX_Y},
},
{
	.content = "The thrust lever applies thrust to the currently active"\
	" maneuver.",
	.region = {ORB_THRTL_X, ORB_THRTL_Y, ORB_APL_MAX_X, ORB_APL_MAX_Y},
},
{
	.content = "Use the maneuver select buttons to change the active maneuver.",
	.region = {ORB_MS1_X, ORB_MSA_Y, ORB_MS1_MAX_X, ORB_MSA_MAX_Y},
},
{
	.content = "Use the thrust lever, mean dials, and maneuver select buttons "\
	"to control your orbit\n"\
	"and reach the white target orbit it'll turn green when close enough",
	.region = {ORB_MS1_X, ORB_MSA_Y, ORB_MS1_MAX_X, ORB_MSA_MAX_Y},
},
{
	.content = "Once your orbit is near you can accept and close the task",
	.region = {ORB_APL_X, ORB_APL_Y, ORB_APL_MAX_X, ORB_APL_MAX_Y},
},
};

t_task_tutorial			g_orbit_tutorial = {
	.tips = g_orb_tips,
	.tips_len = sizeof(g_orb_tips) / sizeof(t_task_tip),
	.active = 0
};
