#include "sound.h"
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
[SFX_STEP01] = "assets/sounds/step01.flac",
[SFX_STEP02] = "assets/sounds/step02.flac",
[SFX_STEP03] = "assets/sounds/step03.flac",
[SFX_STEP04] = "assets/sounds/step04.flac",
[SFX_STEP05] = "assets/sounds/step05.flac",
[SFX_STEP06] = "assets/sounds/step06.flac",
[SFX_STEP07] = "assets/sounds/step07.flac",
};

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

    while (totalFramesRead < frameCount) {
        ma_uint64 iSample;
        ma_uint64 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        result = ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration, &framesReadThisIteration);
        if (result != MA_SUCCESS || framesReadThisIteration == 0) {
            break;
        }

        for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample) {
            pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample];
        }

        totalFramesRead += (ma_uint32)framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;
        }
    }
    
    return (totalFramesRead);
}

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
//create the device
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
	//we use an event to stop the device but here we are just setting it up we maybe dont need it
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
/*
void	sound_setup(t_game *game)
{
	//change this function if extented defined or bonus
	game->app->sfx = NULL; 
}
*/































































/*
int play2sounds_test()
{


ma_uint32   g_decoderCount;
//ma_decoder* g_pDecoders;
ma_decoder g_wavDecoder;
ma_decoder g_flacDecoder;
ma_bool32*  g_pDecodersAtEnd;
ma_bool32 g_playFlac = MA_FALSE;

ma_event g_stopEvent; 


ma_sound g_wavSound;
ma_sound g_flacSound;

ma_bool32 are_all_decoders_at_end()
{
    ma_uint32 iDecoder;
    for (iDecoder = 0; iDecoder < g_decoderCount; ++iDecoder) {
        if (g_pDecodersAtEnd[iDecoder] == MA_FALSE) {
            return MA_FALSE;
        }
    }

    return MA_TRUE;
}

void startFlacPlayback() {
	ma_decoder_seek_to_pcm_frame(&g_flacDecoder, 0);
    g_playFlac = MA_TRUE;
}

ma_uint32 read_and_mix_pcm_frames_f32(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount)
{
    ma_result result;
    float temp[4096];
    ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount) {
        ma_uint64 iSample;
        ma_uint64 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;
        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        result = ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration, &framesReadThisIteration);
        if (result != MA_SUCCESS || framesReadThisIteration == 0) {
            break;
        }

        for (iSample = 0; iSample < framesReadThisIteration * CHANNEL_COUNT; ++iSample) {
            pOutputF32[totalFramesRead * CHANNEL_COUNT + iSample] += temp[iSample];
        }

        totalFramesRead += (ma_uint32)framesReadThisIteration;

        if (framesReadThisIteration < framesToReadThisIteration) {
            break;
        }
    }
    
    return totalFramesRead;
}

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    float* pOutputF32 = (float*)pOutput;

    ma_uint32 framesReadFlac = 0;

    MA_ASSERT(pDevice->playback.format == SAMPLE_FORMAT);



    ma_uint32 framesReadWav = read_and_mix_pcm_frames_f32(&g_wavDecoder, pOutputF32, frameCount);
 

    if (g_playFlac) {
        ma_uint32 framesReadFlac = read_and_mix_pcm_frames_f32(&g_flacDecoder, pOutputF32, frameCount);
        if (framesReadFlac == 0) {
            g_playFlac = MA_FALSE;
        }
    }

//    if (framesReadWav == 0) {
        // Reset the WAV decoder's playback position to the beginning
//        ma_decoder_seek_to_pcm_frame(&g_wavDecoder, 2);
//	framesReadWav = 1;
 //   }
//    ma_uint32 framesReadFlac = read_and_mix_pcm_frames_f32(&g_flacDecoder, pOutputF32, frameCount);

    if (framesReadWav == 0 && framesReadFlac == 0) {
        ma_event_signal(&g_stopEvent);
    }

    (void)pInput;
}



int main()
{
    ma_result result;
    ma_decoder_config decoderConfig;
    ma_device_config deviceConfig;
    ma_device device;
    const char* wavFilePath = "assets/sounds/intro_sound.wav";
    const char* flacFilePath = "assets/sounds/interface_click.flac";

    decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
    result = ma_decoder_init_file(wavFilePath, &decoderConfig, &g_wavDecoder);
    if (result != MA_SUCCESS) {
        printf("Failed to load %s.\n", wavFilePath);
        return -1;
    }

    result = ma_decoder_init_file(flacFilePath, &decoderConfig, &g_flacDecoder);
    if (result != MA_SUCCESS) {
        printf("Failed to load %s.\n", flacFilePath);
        ma_decoder_uninit(&g_wavDecoder);
        return -1;
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = NULL;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&g_wavDecoder);
        ma_decoder_uninit(&g_flacDecoder);
        return -1;
    }

    ma_event_init(&g_stopEvent);

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        ma_decoder_uninit(&g_wavDecoder);
        ma_decoder_uninit(&g_flacDecoder);
        return -1;
    }

    int count = 0;
    while(count/2 < 300000000)
    {
		if (count % 100000000 == 0)
		{
			printf("playing sounds\n");
 	  		 startFlacPlayback();
		}
		count++;
    }


    printf("Waiting for playback to complete...\n");
    ma_event_wait(&g_stopEvent);

    ma_device_uninit(&device);
    ma_decoder_uninit(&g_wavDecoder);
    ma_decoder_uninit(&g_flacDecoder);

    return 0;
}
*/











