#include "sound.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio_wrapper.h"
#include "state.h"
#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000

static const char	*g_sound_paths[] = {
[SFX_DOOR] = "assets/sounds/door.flac",
[SFX_GAME_01] = "assets/sounds/game_sound01.wav",
[SFX_HEARTBEAT] = "assets/sounds/heartbeat.flac",
[SFX_INTRO] = "assets/sounds/intro_sound.wav",
[SFX_ALERT] = "assets/sounds/map_alert.flac",
[SFX_SELECT] = "assets/sounds/select.flac",
[SFX_SELECTION] = "assets/sounds/selection.flac",
[SFX_SWITCH] = "assets/sounds/switch.flac",
[SFX_ESTEP01] = "assets/sounds/enemy_step (1).flac",
[SFX_ESTEP02] = "assets/sounds/enemy_step (2).flac",
[SFX_ESTEP03] = "assets/sounds/enemy_step (3).flac",
[SFX_PSTEP01] = "assets/sounds/player_step (1).flac",
[SFX_PSTEP02] = "assets/sounds/player_step (2).flac",
[SFX_PSTEP03] = "assets/sounds/player_step (3).flac",
[SFX_PSTEP04] = "assets/sounds/player_step (4).flac",
[SFX_TASK] = "assets/sounds/task.flac",
[SFX_TASK_COMPLETE] = "assets/sounds/task_complete.flac",
[SFX_CLANK] = "assets/sounds/clank.flac",
[SFX_ORBIT] = "assets/sounds/obit_task.flac",
};

void	stop_all_sound(void *s_sfx)
{
	int	i;
	t_sound_manager *const s_man = (t_sound_manager *)s_sfx;

	i = 0;
	while (i < SFX_AMOUNT)
		s_man->sounds[i++].state = STOP;
}

void	set_sound_volume(void *s_sfx, unsigned int index, double volume)
{
	t_sound_manager *const s_man = (t_sound_manager *)s_sfx;

	s_man->sounds[index].volume = volume;
}

void	play_sound(void *s_sfx, unsigned int index, t_sound_state sfc_ctrl)
{
	t_sound_manager *const s_man = (t_sound_manager *)s_sfx;

	ma_decoder_seek_to_pcm_frame(&s_man->sounds[index].decoder, 0);
	s_man->sounds[index].state = sfc_ctrl;
}

void	sound_manager_deallocate(void* s_sfx)
{
	int	i;
	t_sound_manager *const s_man = (t_sound_manager *)s_sfx;

	i = 0;
	if (s_sfx == NULL)
		return ;
	ma_device_uninit(&s_man->device);
	while (i < SFX_AMOUNT)
		ma_decoder_uninit(&s_man->sounds[i++].decoder);
	free(s_man);
}


ma_bool32	are_all_decoders_at_end(t_sound_manager *s_mgr)
{
	ma_uint32	i;

	i = 0;
	while (i < SFX_AMOUNT)
		if (s_mgr->sounds[i++].state != STOP)
			return MA_FALSE;
	return (MA_TRUE);
}

ma_uint32	read_and_mix_pcm_frames_f32(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount)
{
	ma_result result;
	float temp[4096];
	ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
	ma_uint32 totalFramesRead = 0;

	while (totalFramesRead < frameCount)
	{
		ma_uint64 iSample;
		ma_uint64 framesReadThisIteration;
		ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
		ma_uint32 framesToReadThisIteration = tempCapInFrames;
		if (framesToReadThisIteration > totalFramesRemaining)
			framesToReadThisIteration = totalFramesRemaining;
		result = ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration, &framesReadThisIteration);
		if (result != MA_SUCCESS || framesReadThisIteration == 0)
			break;
		for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample)
		{
			pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample];
		}
		totalFramesRead += (ma_uint32)framesReadThisIteration;
		if (framesReadThisIteration < framesToReadThisIteration)
			break;
	}
	return (totalFramesRead);
}
/*
void adjust_volume(float* samples, ma_uint32 frameCount, float volume)
{
	for (ma_uint32 i = 0; i < frameCount; ++i)
		for (ma_uint32 channel = 0; channel < CHANNEL_COUNT; ++channel)
			samples[i * CHANNEL_COUNT + channel] *= volume;
}
*/
void	data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	float* pOutputF32 = (float*)pOutput;
	t_sound_manager* s_mgr = (t_sound_manager*)pDevice->pUserData;
	ma_uint32 iDecoder;
	ma_uint32 framesRead;
	MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);   // <-- Important for this example. 

	for (iDecoder = 0; iDecoder < SFX_AMOUNT; ++iDecoder)
	{
		if (s_mgr->sounds[iDecoder].state != STOP)
		{
			framesRead = read_and_mix_pcm_frames_f32(&s_mgr->sounds[iDecoder].decoder, pOutputF32, frameCount);
			if (framesRead < frameCount)
			{
				if (s_mgr->sounds[iDecoder].state == LOOP)
					ma_decoder_seek_to_pcm_frame(&s_mgr->sounds[iDecoder].decoder, 0);
				else
					s_mgr->sounds[iDecoder].state = STOP;
			}
		//	adjust_volume(pOutputF32, framesRead, s_mgr->sounds[iDecoder].volume);
		}
	}
	if (are_all_decoders_at_end(s_mgr))
		ma_event_signal(&s_mgr->stop_event);
	(void)pInput;
}

void	*sound_manager_init()
{
	ma_result		result;
	ma_decoder_config	decoderConfig;
	ma_device_config	deviceConfig;
	int			i;
	int			j;

	i = 0;
	t_sound_manager* s_mgr = (t_sound_manager*)malloc(sizeof(t_sound_manager));
	if (s_mgr == NULL)
		return (NULL);
	decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
	while (i < SFX_AMOUNT)
	{
		result = ma_decoder_init_file((char *)g_sound_paths[i], &decoderConfig, &s_mgr->sounds[i].decoder);
		if (result != MA_SUCCESS)
		{
			j = -1;
			while (++j < i)
				ma_decoder_uninit(&s_mgr->sounds[j].decoder);
			free(s_mgr);
			printf("Error\nFailed to load %s.\n", g_sound_paths[i]);
			return (NULL);
		}
		s_mgr->sounds[i].state = STOP;
		s_mgr->sounds[i].volume = 1.0f; // Default volume is 100%
		i++;
	}
	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format	= SAMPLE_FORMAT;
	deviceConfig.playback.channels	= CHANNEL_COUNT;
	deviceConfig.sampleRate		= SAMPLE_RATE;
	deviceConfig.dataCallback	= data_callback;
	deviceConfig.pUserData		= s_mgr;
	if (ma_device_init(NULL, &deviceConfig, &s_mgr->device) != MA_SUCCESS)
	{
		for (i = 0; i < SFX_AMOUNT; ++i)
		{
			ma_decoder_uninit(&s_mgr->sounds[i].decoder);
		}
		free(s_mgr);
		printf("Failed to open playback device.\n");
		return (NULL);
	}
	ma_event_init(&s_mgr->stop_event);
	if (ma_device_start(&s_mgr->device) != MA_SUCCESS)
	{
		sound_manager_deallocate(s_mgr);
		printf("failed to start device\n");
		return (NULL);
	}
	return (s_mgr);
}

void	sound_init(t_game *game)
{
	//change this function if extented defined or bonus
	game->app.sfx = sound_manager_init();
}
