#include "state.h"
#include "cubed.h"

void input_on_key_press(int key, t_game *game)
{
	int *state;

	state = input_get_state(game, &key);
	state[key] = 1;
}

void input_on_key_release(int key, t_game *game)
{
	int *state;

	state = input_get_state(game, &key);
	state[key] = 0;
}

void input_on_mouse_press(int button, int x, int y, t_game *game)
{
	int *state;

	button |= KEY_MB_MASK;
	state = input_get_state(game, &button);
	state[button] = 1;
}

void input_on_mouse_release(int button, int x, int y, t_game *game)
{
	int *state;

	button |= KEY_MB_MASK;
	state = input_get_state(game, &button);
	state[button] = 0;
}

void input_on_mouse_move(int x, int y, t_game *game)
{
	game->input.curr.mouse = v2inew(x, y);
}

void input_on_render(t_game *game)
{
	if (input_keydown(game, KEY_A))
	{
		printf("input_keydown A\n");
	}

	if (input_keyheld(game, KEY_A))
	{
		printf("input_keyheld A\n");
	}

	if (input_keyup(game, KEY_A))
	{
		printf("input_keyup A\n");
	}
	
	input_process(game);
}

int main(void)
{
	t_game	game;
	
	game = (t_game){0};
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3d");

	mlx_loop_hook(game.mlx, (void *)render, &game);

	mlx_hook(game.win, (void *)on_mouse, &game);

	mlx_hook(game.win, 2, (1L<<0), (void *)input_on_key_press, &game);
	mlx_hook(game.win, 3, (1L<<1), (void *)input_on_key_release, &game);
	mlx_hook(game.win, 4, (1L<<2), (void *)input_on_mouse_press, &game);
	mlx_hook(game.win, 5, (1L<<3), (void *)input_on_mouse_release, &game);

	mlx_hook(game.win, 6, (1L<<6), (void *)input_on_mouse_move, &game);

	mlx_do_key_autorepeatoff(game.mlx); // change to off when we implement the input system

	mlx_loop(game.mlx);
}
