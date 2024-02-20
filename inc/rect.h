/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:51:18 by clovell           #+#    #+#             */
/*   Updated: 2024/02/19 18:55:48 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RECT_H
# define RECT_H
# include <stdbool.h>
# include "vector2.h"
# include "vector4.h"


typedef struct s_vec4 t_rect; 
t_rect	rect_getbounded(t_rect rect);
t_rect	rect_offset(t_rect rect, t_vec2 offset);
bool	rect_contains_v2(t_rect rect, t_vec2 pos);
#endif