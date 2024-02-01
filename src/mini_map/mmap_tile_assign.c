#include "mini_map.h"
#include "texture.h"
#include "state.h"

t_texture	*mmap_get_img(t_game *game, int pos)
{
	int	index;

	index = mmap_decide_img(game->world->map.tiles, game->world->map.width, game->world->map.height, pos);
	return (&game->mmap.mm_img[index]);
}

t_texture	*mmap_get_door_img(t_game *game, int pos, int i)
{
	if (game->world->map.tiles[pos+1].type == FLOOR)
	{
		game->mmap.tiles[i].vertical = true;
		return (&game->mmap.mm_img[13]);
	}
	else
	{
		game->mmap.tiles[i].vertical = false;
		return (&game->mmap.mm_img[11]);
	}
}

void	mmap_tile_assign_set(t_game *game, int i, int x, int y)
{
	game->mmap.tiles[i].pos.x = x * MAP_S + MAP_POS_X + MAP_CASE;
	game->mmap.tiles[i].pos.y = y * MAP_S + MAP_POS_Y + MAP_CASE;
	game->mmap.tiles[i++].vis = false;
}

int	mmap_tile_assign(t_game *game, int i, int y)
{
	int	x;
	int	index;

	x = -1;
	while (++x < game->world->map.width)
	{
		index = x + y * game->world->map.width;
		if (game->world->map.tiles[index].type == WALL)
		{
			if (game->mmap.tiles[i].img == NULL)
				game->mmap.tiles[i].img = mmap_get_img(game, index);
			mmap_tile_assign_set(game, i, x, y);
			game->mmap.tiles[i++].ref = index;
		}
		if (game->world->map.tiles[index].type == DOOR)
		{
			game->mmap.tiles[i].img = mmap_get_door_img(game, index, i);
			mmap_tile_assign_set(game, i, x, y);
			game->mmap.tiles[i++].ref = index;
		}
	}
	return (i);
}
