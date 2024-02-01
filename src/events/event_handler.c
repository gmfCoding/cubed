#include "map.h"
#include "state.h"
#include "mini_map.h"


double v2dot(t_vec2 a, t_vec2 b)
{
  return (a.x * b.x + a.y * b.y);
}

void	event_display_ui(t_game *game)
{
	if (game->display_ui == true)
	{
		mlx_string_put (game->app.mlx, game->app.win, 400, 400, 0xffffff, "....PRESS 'E' TO INTERACT....");	
	}
}

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



void	event_door_locked(t_game *game, t_entity_2 *ent)
{
	printf("DOOR IS LOCKED\n");
	return ;
}

void	event_door_open(t_game *game, t_entity_2 *ent)
{
	game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].vis = 1;
	ent->ref_mm_tile->img = &game->mmap.mm_img[13];
	ent->type = DOOR_UNLOCKED;	
}

void	event_door_unlocked(t_game *game, t_entity_2 *ent)
{
	game->world->map.tiles[(int)(ent->pos[0].x + ent->pos[0].y * game->world->map.width)].vis = -1;
	if (ent->ref_mm_tile->vertical = true)
		ent->ref_mm_tile->img = &game->mmap.mm_img[14];
	else
		ent->ref_mm_tile->img = &game->mmap.mm_img[12];
	ent->type = DOOR_OPEN;
}

void	event_interact(t_game *game)
{
	int	i;

	i = -1;
	t_vec2	pos;
	while (game->events_active[++i] != NULL)
	{
		pos = v2add(game->events_active[i]->pos[0], v2new(0.5, 0.5));
		pos.x = game->events_active[i]->pos[0].x + 0.5;
		pos.y = game->events_active[i]->pos[0].y + 0.5;
		if(v2dot(v2norm(v2sub(pos, game->player.pos)), game->player.dir)> 0.8)
		{

			if (game->events_active[i]->type == DOOR_UNLOCKED)
			{
				game->display_ui = true;
				if (input_keydown(&game->input, KEY_E))
					event_door_unlocked(game, game->events_active[i]);
				return ;
			}
			if (game->events_active[i]->type == DOOR_OPEN)
			{
				game->display_ui = true;
				if (input_keydown(&game->input, KEY_E))
					event_door_open(game, game->events_active[i]);
				return ;
			}
			if (game->events_active[i]->type == DOOR_LOCKED)
			{
				game->display_ui = true;
				if (input_keydown(&game->input, KEY_E))
					event_door_locked(game, game->events_active[i]);
				return ;
			}
			if (game->events_active[i]->type == ALERT_HIGH)
			{
				event_alert_high(game, game->events_active[i]);
				return ;
			}
			if (game->events_active[i]->type == ALERT_MEDIUM)
			{
				event_alert_medium(game, game->events_active[i]);
				return ;
			}
			if (game->events_active[i]->type == ALERT_OFF)
			{
				event_alert_off(game, game->events_active[i]);
				return ;
			}
		}
		game->display_ui = false;
	}
}

void	event_check(t_game *game)
{
	int	i;
	int	j;
	int	k;

	k = -1;	
	i = -1;
	while (game->events_active[++k] != NULL)
		game->events_active[k] = NULL;
	k = -1;
	while (++i < game->world->ent_count)
	{
		j = -1;
		while(++j < 9)
		{
			if (game->world->ent_2[i].pos[j].x == (int)game->player.pos.x \
				&& game->world->ent_2[i].pos[j].y == (int)game->player.pos.y)
			{
				game->events_active[++k] = &game->world->ent_2[i];
				game->events_on = true;
			}
		}
	}
}

void	event_player(t_game *game)
{
	if ((int)game->player.pos.x != game->player.oldp_x || (int)game->player.pos.y != game->player.oldp_y)
	{
		game->display_ui = false;
		game->events_on = false;
		game->player.oldp_x = game->player.pos.x;
		game->player.oldp_y = game->player.pos.y;
		event_check(game);
	}


}
/*
void	event_trigger(t_game *game, t_vec2 pos, t_event_type type)
{
	printf("we are here in events\n");


}
*/
