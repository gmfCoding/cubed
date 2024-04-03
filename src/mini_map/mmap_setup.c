
#include "mini_map.h"
#include "texture.h"
#include "state.h"

/* unsure if we need this function coz i didnt end up using it but its here
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

/*
 * set the fog on map if it is and 'F' in the .bur map
 */
bool	mmap_fog_check(t_game *game)
{
	t_mod *mm;

	mm = mod_get_mod(&game->world->map, MT_MINI_MAP, NULL);
	if (mm == NULL || mm->content == NULL)
		return (false);
	if (mm->content[0] == 'F')
		return (false);
	return (true);
}

/*
 * sets up mini map its called after the modifiers have been done
 */
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
