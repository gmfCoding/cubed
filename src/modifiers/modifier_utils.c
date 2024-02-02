
#include "map.h"

void	*get_pos_and_surrounding_tiles(t_world *world, int x, int y)
{
	world->ent_2[world->ent_count].pos[0].x = x;
	world->ent_2[world->ent_count].pos[0].y = y;
	world->ent_2[world->ent_count].pos[1].x = x + 1;
	world->ent_2[world->ent_count].pos[1].y = y;
	world->ent_2[world->ent_count].pos[2].x = x + 1;
	world->ent_2[world->ent_count].pos[2].y = y + 1;
	world->ent_2[world->ent_count].pos[3].x = x;
	world->ent_2[world->ent_count].pos[3].y = y + 1;
	world->ent_2[world->ent_count].pos[4].x = x - 1;
	world->ent_2[world->ent_count].pos[4].y = y + 1;
	world->ent_2[world->ent_count].pos[5].x = x - 1;
	world->ent_2[world->ent_count].pos[5].y = y;
	world->ent_2[world->ent_count].pos[6].x = x - 1;
	world->ent_2[world->ent_count].pos[6].y = y - 1;
	world->ent_2[world->ent_count].pos[7].x = x;
	world->ent_2[world->ent_count].pos[7].y = y - 1;
	world->ent_2[world->ent_count].pos[8].x = x + 1;
	world->ent_2[world->ent_count].pos[8].y = y - 1;
}

