#include <inttypes.h>
#include <stddef.h>
#include "state.h"
#include "vector2i.h"
#include "input.h"

bool	input_keydown(t_game *game, int key)
{
	uint8_t	*state;

	state = input_get_state(game, &key);
	return ((state[key] & KEY_MASK_PRESS) == KEY_MASK_PRESS);
}

bool	input_keyup(t_game *game, int key)
{
	uint8_t	*state;

	state = input_get_state(game, &key);
	return ((state[key] & KEY_MASK_RELEASE) == KEY_MASK_RELEASE);
}

bool	input_keyheld(t_game *game, int key)
{	
	uint8_t	*state;

	state = input_get_state(game, &key);
	return ((state[key] & KEY_MASK_PRESS) == KEY_MASK_PRESS || \
	((state[key] & KEY_MASK_RELEASE) != KEY_MASK_RELEASE &&\
	 (state[key] & KEY_MASK_PREV) == KEY_MASK_PREV));
}

void	input_process(t_game *game)
{
	const int size[] = {
		sizeof(game->input.mouse_state), sizeof(game->input.key_state),
		sizeof(game->input.special_state),
		0,
	};
	uint8_t *const states[] = {
		game->input.mouse_state, game->input.key_state,
		game->input.special_state, NULL,
	};
	int i;
	int j;

	j = -1;
	while (states[++j])
	{
		i = -1;
		while (++i < size[j])
		{
			if ((states[j][i] & KEY_MASK_PRESS) == KEY_MASK_PRESS)
			{
				states[j][i] &= ~KEY_MASK_PRESS;
				states[j][i] |= KEY_MASK_PREV;
			}
			if ((states[j][i] & KEY_MASK_RELEASE) == KEY_MASK_RELEASE)
				states[j][i] = 0;
			//if ((states[j][i] & KEY_MASK_RELEASE) == KEY_MASK_RELEASE)
			//	states[j][i] &= ~KEY_MASK_PREV;
		}
	}
	game->input.mouse_prev = game->input.mouse;
}

uint8_t	*input_get_state(t_game *game, int *key)
{
	uint8_t *state;

	state = game->input.key_state;
	if ((*key & KEY_CMD_MASK) == KEY_CMD_MASK)
	{
		*key &= ~KEY_CMD_MASK;
		state = game->input.special_state;
	}
	else if ((*key & KEY_MB_MASK) == KEY_MB_MASK)
	{
		*key &= ~KEY_MB_MASK;
		state = game->input.mouse_state;
	}
	return state;
}
