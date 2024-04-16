/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:18:31 by clovell           #+#    #+#             */
/*   Updated: 2024/03/11 20:52:26 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"

#define KDOWN 2
#define KUP 3
#define MDOWN 4
#define MUP 5
#define MMOVE 6
#define EXPOSE 12
#define DESTROY 17

void	textures_destroy(t_game *game)
{
	int i;

	i = TEX_ARRAY_SIZE;
	while (--i > 3)
		texture_destroy(game->app.mlx, &game->textures[i], NULL, 0);
	if (game->mmap.img_case[0].img != NULL)
	{
		while (i > -1)
			texture_destroy(game->app.mlx, &game->mmap.img_case[i--], NULL, 0);
		while (++i < 26)
			texture_destroy(game->app.mlx, &game->mmap.mm_img[i], NULL, 0);
		texture_destroy(game->app.mlx, &game->mmap.img_pr, NULL, 0);
		texture_destroy(game->app.mlx, &game->mmap.img_pp, NULL, 0);
	}
	if (game->five_light.run_game == true)
		destroy_five_lights_images(game->app.mlx, &game->five_light);

	//need to sort out walls NSEW and free coz some walls are pointing to other walls

}

void	world_destroy(t_game *game)
{
	int i;

	i = -1;
	if (game->world->enemy != NULL)
	{
		if (game->world->enemy->path != NULL)
			free(game->world->enemy->path);
		free(game->world->enemy);
	}
	//need to free from entiry create change to a function for freeing
	free(game->world);
}

void	game_destroy(t_game *game)
{
	textures_destroy(game);
	world_destroy(game);
	//TODO: Leak cleanup
	exit(0);
}

void	shutdown_input_setup(t_game *game)
{
	mlx_hook(game->app.win, DESTROY, 0, (void *)game_destroy, game);
}
