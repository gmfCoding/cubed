/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:27:18 by clovell           #+#    #+#             */
/*   Updated: 2024/05/03 14:35:53 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CONFIG_H
# define CONFIG_H

// How many possible depths can a raycast contain?
# define MAX_DEPTHS 5

// Screen resolution X
# define SCR_WIDTH 960
// Screen resolution Y
# define SCR_HEIGHT 960

# define R_SCALE 1

// Render resolution X
# define R_WIDTH (SCR_WIDTH/R_SCALE)
// Render resolution Y
# define R_HEIGHT (SCR_HEIGHT/R_SCALE)

# define MOUSE_SENSITIVITY 2 

# define RT0_WIDTH SCR_WIDTH
# define RT0_HEIGHT SCR_HEIGHT

// Wall texture resolution
# define WALL_TEX_SIZE 512
# define FLOOR_TEX_SIZE WALL_TEX_SIZE

# define MAX_TEX_BF 4

# define MAP_MAX_XY 200
# define MAP_MAX_X MAP_MAX_XY
# define MAP_MAX_Y MAP_MAX_XY

# define TARGET_FRAME_RATE 60.0
# define R_TFR TARGET_FRAME_RATE

# define MOD_CONTENT_MAX 100
# define NAME_SIZE 50
# define MAX_ENT 100 
# define MAP_PATH "./maps/"
#endif
