/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:34:49 by clovell           #+#    #+#             */
/*   Updated: 2024/02/07 19:38:30 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "render.h"
#include "rect.h"

void	rect_draw(const t_rect *aabb, int colour, t_texture rt)
{
	texture_draw_line(rt, aabb->min, aabb->max, colour);
	texture_draw_line(rt, aabb->min, v2new(aabb->min.x, aabb->max.y), colour);
	texture_draw_line(rt, aabb->min, v2new(aabb->max.x, aabb->min.y), colour);
	texture_draw_line(rt, aabb->max, v2new(aabb->max.x, aabb->min.y), colour);
	texture_draw_line(rt, aabb->max, v2new(aabb->min.x, aabb->max.y), colour);
}
