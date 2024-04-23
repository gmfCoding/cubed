/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:18:31 by clovell           #+#    #+#             */
/*   Updated: 2024/04/23 18:25:19 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "state.h"
#include "sound.h"


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

	i = game->loaded_index[0];
	while (--i > -1)
		texture_destroy(game->app.mlx, &game->textures[i], NULL, 0);
	if (game->mmap.img_case[0].img != NULL)
	{
		i = 2;
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


void	destroy_entity(void *ent)
{
	const t_entity *entity = (t_entity *)ent; // maybe use cast fn pointer instead
	const t_enemy *as_enemy = (t_enemy *)entity;
	if (entity->type == ENT_ENEMY)
	{
		if (as_enemy->path != NULL)
			free(as_enemy->path);
	}
}

void	world_destroy(t_game *game)
{
	ft_lstclear(&game->world->entities, destroy_entity);
	//need to free from entiry create change to a function for freeing
	free(game->world);
}

void	game_destroy(t_game *game)
{
	textures_destroy(game);
	world_destroy(game);
	sound_manager_deallocate(game->app.sfx);

	//TODO: Leak cleanup
	exit(0);
}

void	shutdown_input_setup(t_game *game)
{
	mlx_hook(game->app.win, DESTROY, 0, (void *)game_destroy, game);
}
