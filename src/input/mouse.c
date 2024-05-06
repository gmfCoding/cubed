/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:27:16 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 21:07:56 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "app.h"

#ifdef __linux__

void	mouse_get_pos(t_app *app, int *x, int *y)
{
	int	x1;
	int	y1;

	mlx_mouse_get_pos(app->mlx, app->win, &x1, &y1);
	if (x)
		*x = x1;
	if (y)
		*y = y1;
}
#else

void	mouse_get_pos(t_app *app, int *x, int *y)
{
	int	x1;
	int	y1;

	mlx_mouse_get_pos(app->win, &x1, &y1);
	if (x)
		*x = x1;
	if (y)
		*y = y1;
}
#endif
