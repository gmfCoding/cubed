#ifndef UTILS_H
# define UTILS_H
# include "vector2.h"
# include "texture.h"
# include "state.h"

void    texture_draw(t_game *gs, t_texture tex, t_vec2 pos);

void render(t_game *ctx);
#endif