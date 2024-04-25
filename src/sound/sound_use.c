#include "sound.h"
#include "miniaudio_wrapper.h"
#include <stdlib.h>

void	stop_all_sound(void *s_sfx)
{
	int						i;
	t_sound_manager *const	s_man = (t_sound_manager *)s_sfx;

	if (s_sfx == NULL)
		return ;
	i = 0;
	while (i < SFX_AMOUNT)
		s_man->sounds[i++].state = STOP;
}

void	set_sound_volume(void *s_sfx, unsigned int index, float volume)
{
	t_sound_manager *const	s_man = (t_sound_manager *)s_sfx;

	if (s_sfx == NULL)
		return ;
	s_man->sounds[index].volume = volume;
}

void	play_sound(void *s_sfx, unsigned int index, t_sound_state sfc_ctrl)
{
	t_sound_manager *const	s_man = (t_sound_manager *)s_sfx;

	if (s_sfx == NULL)
		return ;
	ma_decoder_seek_to_pcm_frame(&s_man->sounds[index].decoder, 0);
	s_man->sounds[index].state = sfc_ctrl;
}

void	sound_manager_deallocate(void *s_sfx)
{
	int						i;
	t_sound_manager *const	s_man = (t_sound_manager *)s_sfx;

	i = 0;
	if (s_sfx == NULL)
		return ;
	ma_device_uninit(&s_man->device);
	while (i < SFX_AMOUNT)
		ma_decoder_uninit(&s_man->sounds[i++].decoder);
	free(s_man);
}
