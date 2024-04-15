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
/*
void	mmap_init_img_2(t_mmap *mmap, void *mlx)
{
	mmap->mm_img[1] = texture_load(mlx, "assets/minimap/mm01.xpm");
	mmap->mm_img[2] = texture_load(mlx, "assets/minimap/mm02.xpm");
	mmap->mm_img[3] = texture_load(mlx, "assets/minimap/mm03.xpm");
	mmap->mm_img[4] = texture_load(mlx, "assets/minimap/mm04.xpm");
	mmap->mm_img[5] = texture_load(mlx, "assets/minimap/mm05.xpm");
	mmap->mm_img[6] = texture_load(mlx, "assets/minimap/mm06.xpm");
	mmap->mm_img[7] = texture_load(mlx, "assets/minimap/mm07.xpm");
	mmap->mm_img[8] = texture_load(mlx, "assets/minimap/mm08.xpm");
	mmap->mm_img[9] = texture_load(mlx, "assets/minimap/mm09.xpm");
	mmap->mm_img[10] = texture_load(mlx, "assets/minimap/mm10.xpm");
	mmap->mm_img[11] = texture_load(mlx, "assets/minimap/mm11.xpm");
	mmap->mm_img[12] = texture_load(mlx, "assets/minimap/mm12.xpm");
	mmap->mm_img[13] = texture_load(mlx, "assets/minimap/mm13.xpm");
	mmap->mm_img[14] = texture_load(mlx, "assets/minimap/mm14.xpm");
	mmap->mm_img[15] = texture_load(mlx, "assets/minimap/mm15.xpm");
	mmap->mm_img[16] = texture_load(mlx, "assets/minimap/mm16.xpm");
	mmap->mm_img[17] = texture_load(mlx, "assets/minimap/mm17.xpm");
	mmap->mm_img[18] = texture_load(mlx, "assets/minimap/mm18.xpm");
	mmap->mm_img[19] = texture_load(mlx, "assets/minimap/mm19.xpm");
	mmap->mm_img[20] = texture_load(mlx, "assets/minimap/mm20.xpm");
	mmap->mm_img[21] = texture_load(mlx, "assets/minimap/mm21.xpm");
	mmap->mm_img[22] = texture_load(mlx, "assets/minimap/mm22.xpm");
	mmap->mm_img[23] = texture_load(mlx, "assets/minimap/mm23.xpm");
	mmap->mm_img[24] = texture_load(mlx, "assets/minimap/mm24.xpm");
	mmap->mm_img[25] = texture_load(mlx, "assets/minimap/mm25.xpm");
}

void	mmap_init_img_1(t_mmap *mmap, void *mlx)
{
	mmap->img_pr = texture_load(mlx, "assets/minimap/mm_player_r.xpm");
	mmap->img_pp = texture_load(mlx, "assets/minimap/mm_player_p.xpm");
	mmap->img_case[0] = texture_load(mlx, "assets/minimap/mmcase.xpm");
	mmap->img_case[1] = texture_load(mlx, "assets/minimap/mm_back_b.xpm");
	mmap->img_case[2] = texture_load(mlx, "assets/minimap/mm_back_y.xpm");
	mmap->img_case[3] = texture_load(mlx, "assets/minimap/mm_back_r.xpm");
	mmap->mm_img[0] = texture_load(mlx, "assets/minimap/mm00.xpm");
	mmap_init_img_2(mmap, mlx);
}
*/
//	texture_destroy(void *mlx, t_texture *tex, t_texture **tex_ptr, bool use_free)
void	textures_destroy(t_game *game)
{
	int i;

	i = TEX_ARRAY_SIZE;
	while (--i > 3)
	{
		printf("index %d \n", i);
		texture_destroy(game->app.mlx, &game->textures[i], NULL, 0);
	}
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
