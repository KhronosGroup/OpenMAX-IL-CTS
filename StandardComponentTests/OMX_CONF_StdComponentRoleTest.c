/*
 * Copyright (c) 2019 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** OMX_CONF_StdComponentRoleTest.c
 *  OpenMax IL conformance test - Standard Component Roles Query and Verification Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_TestHarness.h"
#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdComponentRoleTest"

OMX_ERRORTYPE OMX_CONF_StdPcmCapturerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMp3DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAacDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRealAudioDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWmaDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMp3EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAacEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdPcmMixerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorChorusTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorEqualizerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorEqualizerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorReverberationTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorStereoWideningHeadphonesTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorStereoWideningLoudspeakersTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdPcmRendererTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryClockTest_BinaryClockTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryAudioReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryVideoReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryImageReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryAudioWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryVideoWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryImageWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdYuvCameraTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_Std3GpContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAsfContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRealContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_Std3GpContainerMuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdJpegDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWebpDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdJpegEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWebpEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdYuvOverlayTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRgbOverlayTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdH263DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAvcDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMpeg4DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRvDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWmvDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVp8DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdH263EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAvcEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMpeg4EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVp8EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryVideoSchdulerTest(OMX_IN OMX_STRING cComponentName);

/**************************** G L O B A L S **********************************/

/*****************************************************************************/
/*  Get all roles of the given standard component and test each of those roles
    for the 'standardness'.
*/
OMX_ERRORTYPE OMX_CONF_StdComponentRoleTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError;

    OMX_U32 nNumRoles;
    OMX_STRING sRoles[MAX_COMPONENT_ROLES];
    OMX_U32 nRoleCounter;
    OMX_U32 nTestCounter;

    OMX_CONF_TESTLOOKUPTYPE pLookupTable[] = 
    {
        {"audio_capturer.pcm",                               OMX_CONF_StdPcmCapturerTest,                              0},
        {"audio_decoder.mp3",                                OMX_CONF_StdMp3DecoderTest,                               0},
        {"audio_decoder.aac",                                OMX_CONF_StdAacDecoderTest,                               0},
        {"audio_decoder.ra",                                 OMX_CONF_StdRealAudioDecoderTest,                         0},
        {"audio_decoder.wma",                                OMX_CONF_StdWmaDecoderTest,                               0},
        {"audio_encoder.mp3",                                OMX_CONF_StdMp3EncoderTest,                               0},
        {"audio_encoder.aac",                                OMX_CONF_StdAacEncoderTest,                               0},
        {"audio_mixer",                                      OMX_CONF_StdPcmMixerTest,                                 0},
        {"audio_processor.pcm.chorus",                       OMX_CONF_StdAudioProcessorChorusTest,                     0},
        {"audio_processor.pcm.equalizer",                    OMX_CONF_StdAudioProcessorEqualizerTest,                  0},
        {"audio_processor.pcm.equalizer",                    OMX_CONF_StdAudioProcessorEqualizerTest,                  0},
        {"audio_processor.pcm.reverberation",                OMX_CONF_StdAudioProcessorReverberationTest,              0},
        {"audio_processor.pcm.stereo_widening_headphones",   OMX_CONF_StdAudioProcessorStereoWideningHeadphonesTest,   0},
        {"audio_processor.pcm.stereo_widening_loudspeakers", OMX_CONF_StdAudioProcessorStereoWideningLoudspeakersTest, 0},
        {"audio_renderer.pcm",                               OMX_CONF_StdPcmRendererTest,                              0},
        {"clock.binary",                                     OMX_CONF_StdBinaryClockTest_BinaryClockTest,              0},
        {"audio_reader.binary",                              OMX_CONF_StdBinaryAudioReaderTest,                        0},
        {"video_reader.binary",                              OMX_CONF_StdBinaryVideoReaderTest,                        0},
        {"image_reader.binary",                              OMX_CONF_StdBinaryImageReaderTest,                        0},
        {"audio_writer.binary",                              OMX_CONF_StdBinaryAudioWriterTest,                        0},
        {"video_writer.binary",                              OMX_CONF_StdBinaryVideoWriterTest,                        0},
        {"image_writer.binary",                              OMX_CONF_StdBinaryImageWriterTest,                        0},
        {"camera.yuv",                                       OMX_CONF_StdYuvCameraTest,                                0},
        {"container_demuxer.3gp",                            OMX_CONF_Std3GpContainerDemuxerTest,                      0},
        {"container_demuxer.asf",                            OMX_CONF_StdAsfContainerDemuxerTest,                      0},
        {"container_demuxer.real",                           OMX_CONF_StdRealContainerDemuxerTest,                     0},
        {"container_muxer.3gp",                              OMX_CONF_Std3GpContainerMuxerTest,                        0},
        {"image_decoder.jpeg",                               OMX_CONF_StdJpegDecoderTest,                              0},
        {"image_decoder.webp",                               OMX_CONF_StdWebpDecoderTest,                              0},
        {"image_encoder.jpeg",                               OMX_CONF_StdJpegEncoderTest,                              0},
        {"image_encoder.webp",                               OMX_CONF_StdWebpEncoderTest,                              0},
        {"iv_renderer.yuv.overlay",                          OMX_CONF_StdYuvOverlayTest,                               0},
        {"iv_renderer.rgb.overlay",                          OMX_CONF_StdRgbOverlayTest,                               0},
        {"video_decoder.h263",                               OMX_CONF_StdH263DecoderTest,                              0},
        {"video_decoder.avc",                                OMX_CONF_StdAvcDecoderTest,                               0},
        {"video_decoder.mpeg4",                              OMX_CONF_StdMpeg4DecoderTest,                             0},
        {"video_decoder.rv",                                 OMX_CONF_StdRvDecoderTest,                                0},
        {"video_decoder.wmv",                                OMX_CONF_StdWmvDecoderTest,                               0},
        {"video_decoder.vp8",                                OMX_CONF_StdVp8DecoderTest,                               0},
        {"video_encoder.h263",                               OMX_CONF_StdH263EncoderTest,                              0},
        {"video_encoder.avc",                                OMX_CONF_StdAvcEncoderTest,                               0},
        {"video_encoder.mpeg4",                              OMX_CONF_StdMpeg4EncoderTest,                             0},
        {"video_encoder.vp8",                                OMX_CONF_StdVp8EncoderTest,                               0},
        {"video_scheduler.binary",                           OMX_CONF_StdBinaryVideoSchdulerTest,                      0}
    };

    OMX_U32 nTableSize = sizeof(pLookupTable)/sizeof(OMX_CONF_TESTLOOKUPTYPE);

    eError = StdComponentTest_PopulateRolesArray(cComponentName, &nNumRoles, sRoles);
    OMX_CONF_BAIL_ON_ERROR(eError);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Roles supported by %s : \n", cComponentName);
    for (nRoleCounter = 0; nRoleCounter < nNumRoles; nRoleCounter++)
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "\tIndex %d : %s\n", nRoleCounter, sRoles[nRoleCounter]);

    eError = OMX_ErrorComponentNotFound;
    for (nRoleCounter = 0; nRoleCounter < nNumRoles; nRoleCounter++)
    {
        for (nTestCounter = 0; nTestCounter < nTableSize; nTestCounter++)
        {
            if (strstr(sRoles[nRoleCounter], pLookupTable[nTestCounter].pName) != NULL)
            {
                OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Testing Role %s of %s\n", sRoles[nRoleCounter], cComponentName);

                eError = pLookupTable[nTestCounter].pFunc(cComponentName);
                OMX_CONF_BAIL_ON_ERROR(eError);
            }
        }
    }

OMX_CONF_TEST_BAIL:
    StdComponentTest_FreeRolesArray(nNumRoles, sRoles);
    return (eError);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
