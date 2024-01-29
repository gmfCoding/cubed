#include "map.h"
#include "state.h"




double v2dot(t_vec2 a, t_vec2 b)
{
  return (a.x * b.x + a.y * b.y);
}


void	event_interact(t_game *game)
{
//	t_vec2 mapPos = v2new(game->half.depths[0].x, game->half.depths[0].y);

	if(v2dot(v2norm(v2sub(game->events_active[0]->pos[0], game->player.pos)), game->player.dir)> 0.8)
	{
		printf("hell yeah\n");
		if (game->events_active[0]->state_3 == false)
		{
			game->world->map.tiles[(int)(game->events_active[0]->pos[0].x + game->events_active[0]->pos[0].y * game->world->map.width)].vis = -1;
			game->events_active[0]->state_3 = true;	
		}
		else if (game->events_active[0]->state_3 == true)
		{
			game->world->map.tiles[(int)(game->events_active[0]->pos[0].x + game->events_active[0]->pos[0].y * game->world->map.width)].vis = 0;
			game->events_active[0]->state_3 = false;	
		}

		
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
		game->events_on = false;
		game->player.oldp_x = game->player.pos.x;
		game->player.oldp_y = game->player.pos.y;
		event_check(game);
	}


}

void	event_trigger(t_game *game, t_vec2 pos, t_event_type type)
{
	printf("we are here in events\n");


}
