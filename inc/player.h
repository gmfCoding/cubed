/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:45:11 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:45:13 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vector2.h"
# include <stdbool.h>
typedef struct s_game t_game;
typedef struct s_list t_list;

typedef enum e_p_state
{
	START_TASK,
	DONE_TASK,
	CANT_MOVE,
	CAN_MOVE,
}				t_p_state;

typedef struct	s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	t_vec2	plane_start;
	t_vec2	plane_end;
	int	oldp_x;//this can be a t_vec2i also, or get rid of it all together and come up with another way to see if the player has moved to a new tile
	int		oldp_y;
	double		moveSpeed;
	double		rotSpeed;
	double		angle;
	double		angle_offset;
	t_p_state	state;
}		t_player;

void	player_setup(t_list *curr, t_game *game);

#endif
