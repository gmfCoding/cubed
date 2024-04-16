#include "texture.h"
#include "state.h"
#include "destroy.h"




void	title_show_options(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_OPTIONS_0], game->rt0, v2new(270, 105));
	if(input_keydown(&game->input, KEY_BACKSPACE))
		game->title.state = SELECT_START;
//	if(input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
//		game->title.state = SELECT_QUIT;
}
