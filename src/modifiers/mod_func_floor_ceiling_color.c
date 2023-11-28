#include "cubed.h"

void	fn_F(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = FLOOR_COLOR;
	map->mods[mod_pos].content = content;
}
void	fn_C(char *content, int mod_pos, t_world *world, t_map *map)
{
	(void)world;
	map->mods[mod_pos].type = CEILING_COLOR;
	map->mods[mod_pos].content = content;
}
