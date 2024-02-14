/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_opacity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:29:39 by clovell           #+#    #+#             */
/*   Updated: 2024/02/14 15:11:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "state.h"
#include "texture.h"
#include "render.h"

#define LEN_WIDGET 4
#define WDGT_GRID 0
#define WDGT_COLR 1
#define WDGT_COLG 2
#define WDGT_COLB 3

const char *const	g_widget_textures[] = {
	"assets/tests/opacity/grid.xpm",
	"assets/tests/opacity/red_96.xpm",
	"assets/tests/opacity/green_96.xpm",
	"assets/tests/opacity/blue_96.xpm"
};

typedef struct s_aabb
{
	t_vec2	min;
	t_vec2	max;
}	t_aabb;

typedef struct s_widget
{
	t_texture	tex;
	t_vec2		pos;
}	t_widget;

typedef struct s_test_opacity
{
	t_game		game;

	t_widget	widgets[LEN_WIDGET];
	t_widget	*selected;

	t_texture	test;

}				t_test_opacity;

t_widget	*get_widget_cursor(t_test_opacity *test)
{
	t_game *const	game = &test->game;
	t_vec2i			mouse;
	t_widget		*widget;
	int				i;

	mouse = game->input.mouse;
	i = LEN_WIDGET;
	while (--i >= 0)
	{
		widget = &test->widgets[i];
		if (mouse.x >= widget->pos.x && mouse.y >= widget->pos.y && \
			mouse.x < (widget->pos.x + widget->tex.width) && \
			mouse.y < (widget->pos.y + widget->tex.width))
			return (widget);
	}
	return ((void *)0);
}

static void	update(t_test_opacity *test)
{
	t_game *const	game = &test->game;
	const t_vec2	mouse = v2new(game->input.mouse.x, game->input.mouse.y);
	int				i;

	texture_clear(game->rt0, 0 | R_ALPHA);
	if (input_keydown(&game->input, MB_LEFT))
		test->selected = get_widget_cursor(test);
	if (input_keyup(&game->input, MB_LEFT))
		test->selected = (void *)0;
	if (test->selected)
		test->selected->pos = v2add(test->selected->pos, v2sub(mouse, \
		v2new(game->input.mouse_prev.x, game->input.mouse_prev.y)));
	i = -1;
	while (++i < LEN_WIDGET)
		texture_blit(test->widgets[i].tex, game->rt0, test->widgets[i].pos);
	texture_draw(game->app, game->rt0, v2new(0, 0));
	texture_draw(game->app, test->test, v2new(50, 50));
	input_process(&game->input);
}

#define NAME "opacity test"

int	main(void)
{
	t_test_opacity	test;
	t_game *const	game = &test.game;
	int				i;

	test = (t_test_opacity){0};
	*game = (t_game){0};
	game->app.mlx = mlx_init();
	test.test = texture_create(game->app.mlx, 10, 10);
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			pixel_set(test.test, x, y, 0xFFFFFF | R_ALPHA);
		}
	}
	
	game->rt0 = texture_create(game->app.mlx, R_WIDTH, R_HEIGHT);
	game->app.win = mlx_new_window(game->app.mlx, R_WIDTH, R_HEIGHT, NAME);
	i = -1;
	while (++i < LEN_WIDGET)
	{
		test.widgets[i].tex = texture_load(game->app.mlx, g_widget_textures[i]);
		test.widgets[i].pos = v2new(i * ((double)R_WIDTH / LEN_WIDGET), 0);
	}
	input_setup(game->app.mlx, game->app.win, &game->input);
	mlx_loop_hook(game->app.mlx, (void *)update, &test);
	mlx_loop(game->app.mlx);
}
