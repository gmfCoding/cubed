#include "map.h"
#include "events.h"
#include "state.h"

void	event_five_lights_closed(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
		printf("TASK IS COMPLETE\n");
	return ;
}

void	event_five_lights_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
	//	game->player.can_move = false;
		game->five_light.run_game = true;

		printf("in the events five lights run game = %d\n", game->five_light.run_game);
	}
	if (game->five_light.run_game = false)
	{
		if (game->five_light.finished == true)
		{
			ent->type = ET_FIVE_LIGHTS_CLOSED;
			ent->target->type = ET_DOOR_UNLOCKED;
		}
	}
}
