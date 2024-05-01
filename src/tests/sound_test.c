/*
Demonstrates one way to load multiple files and play them all back at the same time.

When mixing multiple sounds together, you should not create multiple devices. Instead you should create only a single
device and then mix your sounds together which you can do by simply summing their samples together. The simplest way to
do this is to use floating point samples and use miniaudio's built-in clipper to handling clipping for you. (Clipping
is when sample are clampled to their minimum and maximum range, which for floating point is -1..1.)

```
Usage:   simple_mixing [input file 0] [input file 1] ... [input file n]
Example: simple_mixing file1.wav file2.flac
```
*/
#define MINIAUDIO_IMPLEMENTATION


#include <stdio.h>

#include "../../inc/miniaudio.h"

//#include <stdio.h>
//#include <stdlib.h> // Needed for malloc and free

#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000



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
