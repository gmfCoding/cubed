#include "state.h"
#include "vector2i.h"
#include "input.h"

bool input_keydown(t_game *game, int key)
{
	int *state;
	int *prev;

	state = input_get_state(game, &key);
	prev = state + sizeof(t_inputstate);
	return (state[key] & !prev[key]);
}

bool input_keyup(t_game *game, int key)
{
	int *state;
	int *prev;

	state = input_get_state(game, &key);
	prev = state + sizeof(t_inputstate);
	return (!state[key] & prev[key]);
}

bool input_keyheld(t_game *game, int key)
{	
	int *state;
	int *prev;

	state = input_get_state(game, &key);
	prev = state + sizeof(t_inputstate);
	return (state[key] || (state[key] && prev[key]));
}

void input_process(t_game *game)
{
	int i;

	i = 0;
	while (i < 256)
	{
		if (i < 5)
			game->input.prev.mouse_state[i] = game->input.curr.mouse_state[i];
		game->input.prev.key_state[i] = game->input.curr.key_state[i];
		game->input.prev.special_state[i] = game->input.curr.special_state[i];
		i++;
	}
	game->input.prev.mouse = game->input.curr.mouse;
}

int *input_get_state(t_game *game, int *key)
{
	int *state;

	state = game->input.curr.key_state;
	if (*key & KEY_CMD_MASK == KEY_CMD_MASK)
	{
		*key &= ~KEY_CMD_MASK;
		state = game->input.curr.special_state;
	}
	else if (*key & KEY_MB_MASK == KEY_MB_MASK)
	{
		*key &= ~KEY_MB_MASK;
		state = game->input.curr.mouse_state;
	}
	return state;
}
