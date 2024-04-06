
#include "state.h"
#include "five_light.h"

void	fl_change_state(t_game *game, int click_state, int index)
{
	if (click_state < 20)
	{
		game->five_light.state[index] = 2;
		fl_gather_up_state(game, index);
	}
	else
	{
		game->five_light.state[index] = 3;
		fl_gather_down_state(game, index);
	}
}

void	fl_pass_state_rules(t_game *game, int click_state)
{
	int	index;

	index = click_state%10;
	if (game->five_light.state[index] >= 1 && game->five_light.state[index] <= 3)
		return ;
	if (click_state == 10 || click_state == 29 || click_state == 11 || click_state == 28)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] >= 4 && game->five_light.state[index] <= 6)
	{
		fl_reset_game(game);
		return ;
	}
	if (game->five_light.state[index] == 0)
		fl_change_state(game, click_state, index);
}


