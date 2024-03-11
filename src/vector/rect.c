/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:34:17 by clovell           #+#    #+#             */
/*   Updated: 2024/02/19 19:13:11 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rect.h"
#include "vector2.h"

t_rect	rect_getbounded(t_rect rect)
{
	t_rect	result;

	result.pos = v2sub(rect.pos, v2divs(rect.size, 2));
	result.size = v2add(rect.pos, v2divs(rect.size, 2));
	return (result);
}

bool	rect_contains_v2(t_rect rect, t_vec2 pos)
{
	return (pos.x >= rect.min.x && pos.y >= rect.min.y \
	&& pos.x <= rect.max.x && pos.y <= rect.max.y);
}

t_rect	rect_offset(t_rect rect, t_vec2 offset)
{
	rect.min = v2add(rect.min, offset);
	rect.max = v2add(rect.max, offset);
	return (rect);
}
