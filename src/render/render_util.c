/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2024/02/18 14:50:46 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <stddef.h>
#include "vector2.h"
#include "texture.h"
#include "state.h"

void	texture_draw(t_game *gs, t_texture tex, t_vec2 pos)
{
	mlx_put_image_to_window(gs->app.mlx, gs->app.win, tex.img, pos.x, pos.y);
}

// int	colour_blend(int first, int second)
// {
//     unsigned char    r = ((first & M_RED) >> OF_RED);
//     unsigned char    g = ((first & M_GREEN) >> OF_GREEN);
//     unsigned char    b = ((first & M_BLUE) >> OF_BLUE);
//     unsigned char    a = ((first & M_APLHA) >> OF_ALPHA);
//     float           i = a / 255.0f;

//     r = (int)(r * i) + (int)((((second & M_RED) >> OF_RED)) * (1.0 - i));
//     g = (int)(g * i) + (int)((((second & M_GREEN) >> OF_GREEN)) * (1.0 - i));
//     b = (int)(b * i) + (int)((((second & M_BLUE) >> OF_BLUE)) * (1.0 - i));
//     return (r << OF_RED | g << OF_GREEN | b << OF_BLUE | R_ALPHA);
// }
// typedef uint32_t color_t, channel_t;
// int colour_blend(int first, int second)
// {
// 	color_t s = first + second;
//     color_t m = (s - (	(first ^ second) & 0x01010100)) & 0x01010100;
//     return (m >> 8 | 0x01000000 * (second < first)) * 0xff | (s - m);
// }
// int	colour_blend(int first, int second)
// {
//     unsigned char    r = ((first & M_RED) >> OF_RED);
//     unsigned char    g = ((first & M_GREEN) >> OF_GREEN);
//     unsigned char    b = ((first & M_BLUE) >> OF_BLUE);
//     unsigned char    a = ((first & M_APLHA) >> OF_ALPHA);
// 	float			i = a * (1.0f/255.0f);

//     r = r * i + (((second & M_RED) >> OF_RED)) * (1.0 - i);
//     g = g * i + (((second & M_GREEN) >> OF_GREEN)) * (1.0 - i);
//     b = b * i + (((second & M_BLUE) >> OF_BLUE)) * (1.0 - i);
//     return (r << OF_RED | g << OF_GREEN | b << OF_BLUE | R_ALPHA);
// }

// int	colour_blend(int first, int second)
// {
//     unsigned	r = (first >> OF_RED) & 0xFF;
//     unsigned	g = (first >> OF_GREEN) & 0xFF;
//     unsigned	b = (first >> OF_BLUE) & 0xFF;
//     unsigned	a = (first >> OF_ALPHA) & 0xFF;
//     float	i = a * (1.0f / 255.0f);

// 	r = r * i + ((second >> OF_RED) & 0xFF) * (1.0 - i);
// 	g = g * i + ((second >> OF_GREEN) & 0xFF) * (1.0 - i);
// 	b = b * i + ((second >> OF_BLUE) & 0xFF) * (1.0 - i);
// 	return (r << OF_RED | g << OF_GREEN | b << OF_BLUE | R_ALPHA);
// }


#ifdef __linux__
int	colour_blend(int first, int second)
{
	uint8_t *const	f = (uint8_t*)&first;
	uint8_t *const	s = (uint8_t*)&second;
	const float		a = (f[3] * (1.0f / 255.0f));

	f[0] = f[0] * a + s[0] * (1.0 - a);
	f[1] = f[1] * a + s[1] * (1.0 - a);
	f[2] = f[2] * a + s[2] * (1.0 - a);
	return (((int *)f)[0]);
}
# else
int	colour_blend(int first, int second)
{
	uint8_t *const	f = (uint8_t*)&first;
	uint8_t *const	s = (uint8_t*)&second;
	const float		a = 1.0 - (f[3] * (1.0f / 255.0f));

	f[0] = f[0] * a + s[0] * (1.0 - a);
	f[1] = f[1] * a + s[1] * (1.0 - a);
	f[2] = f[2] * a + s[2] * (1.0 - a);
	return (((int *)f)[0]);
}
#endif

t_texture texture_get_debug_view(t_game *game, int view)
{
	if (game->views[view].rt.img == NULL)
	{
		printf("Creating new debug view: %d\n", view);
		game->views[view].win = mlx_new_window(game->app.mlx, game->rt0.width, game->rt0.height, "DEBUG VIEW");
		game->views[view].rt = texture_create(game->app.mlx, game->rt0.width, game->rt0.height);
	} 
	return game->views[view].rt;
}

void texture_draw_debug_view(t_game *game, int view)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	mlx_put_image_to_window(game->app.mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}

void texture_debug_view_blit(t_game *game, int view, t_texture tex, t_vec2 pos)
{
	t_texture rt;

	if (view >= MAX_DEBUG_VIEWS)
		return ;
	rt = texture_get_debug_view(game, view);
	texture_blit(tex, rt, pos);
	mlx_put_image_to_window(game->app.mlx, game->views[view].win, game->views[view].rt.img, 0, 0);
}
