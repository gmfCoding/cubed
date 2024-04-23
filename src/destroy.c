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

void event_ent2_destroy(t_world *world)
{
	int i;
	int	j;

	i = 0;
	while (i < world->ent_count)
	{
		j = 0;
	//	printf("%s we here babay\n", world->ent_2[i].name);
		while (j < EVENT_ENT_MAX_TARGETS)
		{
	//		printf("free target_name: %p\n", world->ent_2[i].target_names[j]);
			if (world->ent_2[i].target_names[j] != NULL)
				free(world->ent_2[i].target_names[j]);
			j++;
		}
		i++;
	}
}

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
	free(ent);
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
	//event_ent2_destroy(game->world);
	world_destroy(game);
	sound_manager_deallocate(game->app.sfx);
	mlx_destroy_window(game->app.mlx, game->app.win);
	//TODO: Leak cleanup
//	__lsan_do_leak_check();
	exit(0);
	//abort();
}

void	shutdown_input_setup(t_game *game)
{
	mlx_hook(game->app.win, DESTROY, 0, (void *)game_destroy, game);
}
