/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2023/05/02 08:20:01 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "vector2.h"
#include "texture.h"
#include "state.h"

void    texture_draw(t_game *gs, t_texture tex, t_vec2 pos)
{
	mlx_put_image_to_window(gs->mlx, gs->win, tex.img, pos.x, pos.y);
}