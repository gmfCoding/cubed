
#include "mini_map.h"
#include "texture.h"
#include "state.h"

/*
t_vec2	v2diff(t_vec2 f, t_vec2 s)
{
	t_vec2	vec;
	
	vec.x = 0;
	vec.y = 0;
	if (f.x > s.x)
		vec.x = f.x - s.x;
	else
		vec.x = s.x - f.x;
	if (f.y > s.y)
		vec.y = f.y - s.y;
	else
		vec.y = s.y - f.y;
	return (vec);
}
*/
bool	mmap_fog_check(t_game *game)
{
	int	i;

	i = -1;
	while (game->world->map.mods[i].type != MINI_MAP)
		i++;
	if (game->world->map.mods[i].content == NULL)
		return (false);
	if (game->world->map.mods[i].content[0] == 'F')
		return (false);
	return (true);
}

void	mmap_init(t_game *game)
{
	int	x;
	int	y;
	int	index;
	int	i;

	game->mmap.mm_big = false;
	game->mmap.mm_small = true;
	game->mmap.alert_m = false;
	game->mmap.alert_h = false;
	mmap_init_img_1(&game->mmap, game->app.mlx);
	y = -1;
	i = 0;
	while (++y < game->world->map.height)
		i = mmap_tile_assign(game, i, y);
	while(i > -1)
		game->mmap.tiles[i--].vis = mmap_fog_check(game);
}
