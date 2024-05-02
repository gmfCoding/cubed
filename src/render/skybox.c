/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:27:39 by clovell           #+#    #+#             */
/*   Updated: 2024/04/07 18:32:08 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"
#include "state.h"

void    render_skybox(t_vec2 dir, t_texture src, t_texture rt)
{
    int            x;
    int            y;
    int            col;
    int            x_offset;

    x_offset = v2x2ang(dir) / 6.28 * src.width * 5.0;
    y = -1;
    while (++y < rt.height)
    {
        x = -1;
        while (++x < rt.width)
        {
            col = pixel_get_s(src, (x + x_offset) % src.width, y % src.height);
            pixel_set_s(rt, x, y, col);
        }
    }
}
/*
// Renders the skybox fitting it to the screen (bottom image)
void    render_skybox(t_vec2 dir, t_texture src, t_texture rt)
{
    int            x;
    int            y;
    int            col;
    int            x_offset;
    const float    scale = src.height / (float)rt.height;

    x_offset = v2x2ang(dir) / 6.28 * src.width;
    y = -1;
    while (++y < rt.height)
    {
        x = -1;
        while (++x < rt.width)
        {
            col = pixel_get_s(src, (int)((x * scale) + x_offset) % src.width, (int)(y * scale) % src.height);
            pixel_set_s(rt, x, y, col);
        }
    }
}
*/
/*
void	render_skybox(t_vec2 dir, t_texture src, t_texture rt)
{
	int		x;
	int		y;
	int		col;
	int		x_offset;


	x_offset = v2x2ang(dir) / 6.28 * 3840;
	y = -1;
	while (++y < rt.height/2)
	{
		x = -1;
		while (++x < rt.width/2)
		{
			col = pixel_get_s(src, x + x_offset, y);
			pixel_set_s(rt, x, y, col);
		}
	}
}
*/
