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

void	game_destroy(t_game *game)
{
	//TODO: Leak cleanup
	exit(0);
}

void	shutdown_input_setup(t_game *game)
{
	mlx_hook(game->app.win, DESTROY, 0, (void *)game_destroy, game);
}
