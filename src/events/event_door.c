#include "map.h"
#include "state.h"
#include "mini_map.h"

void	event_door_locked(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
		printf("DOOR IS LOCKED\n");
	return ;
}

void	event_door_open(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].vis = 1;
		game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].type = FLOOR;
		ent->ref_mm_tile->img = &game->mmap.mm_img[13];
		ent->type = DOOR_UNLOCKED;	
	}
}

void	event_door_unlocked(t_game *game, t_entity_2 *ent)
{
	game->display_ui = true;
	if (input_keydown(&game->input, KEY_E))
	{
		game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].vis = -1;
		game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].type = DOOR;
		if (ent->ref_mm_tile->vertical == true)
			ent->ref_mm_tile->img = &game->mmap.mm_img[14];
		else
			ent->ref_mm_tile->img = &game->mmap.mm_img[12];
		ent->type = DOOR_OPEN;
	}
}
