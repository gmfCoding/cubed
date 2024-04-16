#include "texture.h"
#include "state.h"
#include "destroy.h"

void	title_lose_screen(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_MISSION_FAILED], game->rt0, v2new(140, 250));
	texture_blit(game->textures[TEX_TITLE_CREATED_CHRIS_KYLE], game->rt0, v2new(200, 900));
 	if (input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.anim_frame--;
	if (input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.anim_frame++;
	game->title.anim_frame = (game->title.anim_frame + 3) % 3;
	texture_blit(game->textures[TEX_TITLE_RETRY_0 + (game->title.anim_frame == 0)], game->rt0, v2new(200, 500));
	texture_blit(game->textures[TEX_TITLE_MAIN_MENU_0 + (game->title.anim_frame == 1)], game->rt0, v2new(200, 600));
	texture_blit(game->textures[TEX_TITLE_QUIT_0 + (game->title.anim_frame == 2)], game->rt0, v2new(200, 700));
	if (input_keydown(&game->input, KEY_ENTER))
	{
		if(game->title.anim_frame == 0)
		{
			title_back_to_title(game);
			title_load_and_run(game);
		}
		if(game->title.anim_frame == 1)
			game->title.state = BACK_TO_TITLE;
		if(game->title.anim_frame == 2)
			game_destroy(game);
	}
}

void	title_win_screen(t_game *game)
{
	texture_blit(game->textures[TEX_TITLE_SPACE_BACK], game->rt0, v2new(0, 0));
	texture_blit(game->textures[TEX_TITLE_MISSION_COMPLETED], game->rt0, v2new(40, 250));
	texture_blit(game->textures[TEX_TITLE_CREATED_CHRIS_KYLE], game->rt0, v2new(200, 900));
 	if (input_keydown(&game->input, KEY_UARROW) || input_keydown(&game->input, KEY_W))
		game->title.anim_frame--;
	if (input_keydown(&game->input, KEY_DARROW) || input_keydown(&game->input, KEY_S))
		game->title.anim_frame++;
	game->title.anim_frame = (game->title.anim_frame + 3) % 3;
	if (game->title.anim_forward != game->title.map_str_amount)
		texture_blit(game->textures[TEX_TITLE_NEXT_LEVEL_0 + (game->title.anim_frame == 0)], game->rt0, v2new(200, 500));
	texture_blit(game->textures[TEX_TITLE_MAIN_MENU_0 + (game->title.anim_frame == 1)], game->rt0, v2new(200, 600));
	texture_blit(game->textures[TEX_TITLE_QUIT_0 + (game->title.anim_frame == 2)], game->rt0, v2new(200, 700));
	if (input_keydown(&game->input, KEY_ENTER))
	{
		if(game->title.anim_frame == 0 && game->title.anim_forward != game->title.map_str_amount)
		{
			game->title.anim_forward++;
			title_back_to_title(game);
			title_load_and_run(game);
		}
		if(game->title.anim_frame == 1)
			game->title.state = BACK_TO_TITLE;
		if(game->title.anim_frame == 2)
			game_destroy(game);
	}
}

