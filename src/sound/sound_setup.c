/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmordaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:54:01 by kmordaun          #+#    #+#             */
/*   Updated: 2024/05/08 15:03:01 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"
#define MINIAUDIO_IMPLEMENTATION
/*
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
//#define MA_ENABLE_WASAPI
//#define MA_ENABLE_DSOUND
//#define MA_ENABLE_WINMM
//#define MA_ENABLE_ALSA
#define MA_ENABLE_PULSEAUDIO
//#define MA_ENABLE_JACK
//#define MA_ENABLE_COREAUDIO
//#define MA_ENABLE_SNDIO
//#define MA_ENABLE_AUDIO4
//#define MA_ENABLE_OSS
//#define MA_ENABLE_AAUDIO
//#define MA_ENABLE_OPENSL
//#define MA_ENABLE_WEBAUDIO
//#define MA_ENABLE_NULL
//#define MA_NO_DECODING
#define MA_NO_ENCODING
//#define MA_NO_WAV
//#define MA_NO_FLAC
#define MA_NO_MP3
//#define MA_NO_DEVICE_IO
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_GENERATION
//#define MA_DEBUG_OUTPUT
*/
#include "miniaudio_wrapper.h"

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
[SFX_PSTEP01] = "assets/sounds/enemy_step (1).flac",
[SFX_PSTEP02] = "assets/sounds/enemy_step (2).flac",
[SFX_PSTEP03] = "assets/sounds/enemy_step (3).flac",
[SFX_PSTEP04] = "assets/sounds/step_basic.flac",
[SFX_TASK] = "assets/sounds/task.flac",
[SFX_TASK_COMPLETE] = "assets/sounds/task_complete.flac",
[SFX_CLANK] = "assets/sounds/clank.flac",
[SFX_ORBIT] = "assets/sounds/obit_task.flac",
[SFX_ORBIT_THRUSTUP] = "assets/sounds/orbit_thrustup.flac",
[SFX_ORBIT_THRUSTDOWN] = "assets/sounds/orbit_thrustdown.flac",
};

ma_bool32	are_all_decoders_at_end(t_sound_manager *s_sfx)
{
	ma_uint32	i;

	i = 0;
	while (i < SFX_AMOUNT)
		if (s_sfx->sounds[i++].state != STOP)
			return MA_FALSE;
	return (MA_TRUE);
}

ma_uint32	read_and_mix_pcm_frames_f32(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount, float volume)
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
			pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample] * volume;
		totalFramesRead += (ma_uint32)framesReadThisIteration;
		if (framesReadThisIteration < framesToReadThisIteration)
			break;
	}
	return (totalFramesRead);
}

void	data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	float* pOutputF32 = (float*)pOutput;
	t_sound_manager* s_sfx = (t_sound_manager*)pDevice->pUserData;
	ma_uint32 iDecoder;
	ma_uint32 framesRead;
	MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);   // <-- Important for this example. 

	for (iDecoder = 0; iDecoder < SFX_AMOUNT; ++iDecoder)
	{
		if (s_sfx->sounds[iDecoder].state != STOP)
		{
			framesRead = read_and_mix_pcm_frames_f32(&s_sfx->sounds[iDecoder].decoder, pOutputF32, frameCount, s_sfx->sounds[iDecoder].volume);
			if (framesRead < frameCount)
			{
				if (s_sfx->sounds[iDecoder].state == LOOP)
					ma_decoder_seek_to_pcm_frame(&s_sfx->sounds[iDecoder].decoder, 0);
				else
					s_sfx->sounds[iDecoder].state = STOP;
			}
		}
	}
	if (are_all_decoders_at_end(s_sfx))
		ma_event_signal(&s_sfx->stop_event);
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
	t_sound_manager *s_mgr = (t_sound_manager *)malloc(sizeof(t_sound_manager));
	//s_mgr = (t_sound_manager*){0};
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
		s_mgr->sounds[i++].volume = 1.0f;
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
/*//TODO:remove above code and enable this for eval
void	*sound_manager_init()
{
	return (NULL);
}
*/