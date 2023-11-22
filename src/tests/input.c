#include <mlx.h>
#include <stdio.h>
#include "state.h"
#include "cubed.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

void input_on_key_press(int key, t_game *game)
{
	uint8_t	*state;
	//printf("press A\n");
	state = input_get_state(game, &key);
	state[key] |= KEY_MASK_PRESS;
}

void input_on_key_release(int key, t_game *game)
{
	uint8_t	*state;

	//printf("release A\n");
	state = input_get_state(game, &key);
	state[key] |= KEY_MASK_RELEASE;
}

void input_on_mouse_press(int button, int x, int y, t_game *game)
{
	uint8_t	*state;

	int masked = button | KEY_MB_MASK;
	state = input_get_state(game, &masked);
	state[button] |= KEY_MASK_PRESS;
}

void input_on_mouse_release(int button, int x, int y, t_game *game)
{
	uint8_t	*state;

	int masked = button | KEY_MB_MASK;
	state = input_get_state(game, &masked);
	state[button] |= KEY_MASK_RELEASE;
}

void input_on_mouse_move(int x, int y, t_game *game)
{
	game->input.mouse = v2inew(x, y);
}

int input_on_render(t_game *game)
{
	static int frame = -1;
	frame++;
	if (input_keydown(game, KEY_A))
	{
		printf("%d:input_keydown A\n", frame);
	}

	if (input_keyheld(game, KEY_A))
	{
		printf("%d:input_keyheld A\n", frame);
	}

	if (input_keyup(game, KEY_A))
	{
		printf("%d:input_keyup A\n", frame);
	}
	usleep(100000);
	input_process(game);
	return 0;
}

int main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");
	game.input = (t_inputctx){0};


	mlx_hook(game.win, ON_KEYDOWN, (1L<<0), (void *)input_on_key_press, &game);
	mlx_hook(game.win, ON_KEYUP, (1L<<1), (void *)input_on_key_release, &game);
	mlx_hook(game.win, ON_MOUSEDOWN, (1L<<2), (void *)input_on_mouse_press, &game);
	mlx_hook(game.win, ON_MOUSEUP, (1L<<3), (void *)input_on_mouse_release, &game);
	mlx_hook(game.win, ON_MOUSEMOVE, (1L<<6), (void *)input_on_mouse_move, &game);
	mlx_loop_hook(game.mlx, (void *)input_on_render, &game);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_loop(game.mlx);
}
