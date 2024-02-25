#include "map.h"
#include "state.h"
#include "mini_map.h"

void	event_alert_off(t_game *game, t_entity_2 *ent)
{
	game->mmap.alert_m = false;
	game->mmap.alert_h = false;
}


void	event_alert_medium(t_game *game, t_entity_2 *ent)
{
	game->mmap.alert_m = true;
	game->mmap.alert_h = false;
	game->mmap.al_pos = ent->target->pos[0];
	
}

void	event_alert_high(t_game *game, t_entity_2 *ent)
{
	game->mmap.alert_h = true;
	game->mmap.alert_m = false;
	game->mmap.al_pos = ent->target->pos[0];

}