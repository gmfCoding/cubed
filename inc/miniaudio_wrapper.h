/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniaudio_wrapper.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:44:49 by kmordaun          #+#    #+#             */
/*   Updated: 2024/04/30 20:44:51 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIAUDIO_WRAPPER_H
# define MINIAUDIO_WRAPPER_H

# include "sound.h"
# include "../lib/mlx/miniaudio.h"

typedef enum e_sound_state	t_sound_state;

typedef struct s_sound
{
	ma_decoder		decoder;
	t_sound_state	state;
	float			volume;
}		t_sound;

typedef struct s_sound_manager
{
	t_sound		sounds[SFX_AMOUNT];
	ma_bool32	p_decoders_at_end;
	ma_event	stop_event;
	ma_device	device;
}		t_sound_manager;

#endif
