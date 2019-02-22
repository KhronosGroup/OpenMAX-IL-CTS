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

/** OMX_CONF_Tests.c
 *  Implemenation of the OpenMax IL conformance tests lookup table. 
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_TestHarness.h"

/** Base Profile Tests */
OMX_ERRORTYPE OMX_CONF_StateTransitionTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_ComponentNameTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_BaseParameterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_BufferTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_BufferFlagTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_FlushTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_BaseMultiThreadedTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_PortCommunicationTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_ResourceExhaustionTest(OMX_IN OMX_STRING cComponentName);

/** Interop Profile Tests */
OMX_ERRORTYPE OMX_CONF_ClockComponentTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_InteropParameterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_ParameterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_MultiThreadedTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_PortBufferSupplierTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_PortDisableEnableTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_InvalidInputOutputTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_ValidInputOutputTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_IncompleteStopTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_ResourcePreemptionTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_WaitForResourcesTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_MinPayloadSizeTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_SeekingComponentTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_TunnelledUnitTest(OMX_IN OMX_STRING cComponentName);

/* OSAL Test Prototypes */
OMX_ERRORTYPE OMX_OSAL_TestAll(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_OSAL_MemoryTest1(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_OSAL_MultiThreadTest1(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_OSAL_TimerTest1(OMX_IN OMX_STRING cComponentName);

/* Standard Component Class tests */
OMX_ERRORTYPE OMX_CONF_StdAudioDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMp3DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAacDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRealAudioDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWmaDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVideoDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdH263DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAvcDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMpeg4DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRvDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWmvDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVp8DecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryAudioReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryVideoReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryImageReaderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryAudioWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryVideoWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdBinaryImageWriterTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioCapturerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdPcmCapturerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVideoEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdH263EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAvcEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMpeg4EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVp8EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdImageDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdJpegDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWebpDecoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdImageEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdJpegEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdWebpEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdIVRendererTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdYuvOverlayTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRgbOverlayTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioProcessorTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioMixerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdPcmMixerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioRendererTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdPcmRendererTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAudioEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdMp3EncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAacEncoderTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdClockTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdComponentRoleTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdCameraTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdYuvCameraTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_Std3GpContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdAsfContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdRealContainerDemuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_Std3GpContainerMuxerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_StdVideoSchedulerTest(OMX_IN OMX_STRING cComponentName);
OMX_ERRORTYPE OMX_CONF_DataMetabolismTest(OMX_IN OMX_STRING cComponentName);


OMX_CONF_TESTLOOKUPTYPE g_OMX_CONF_TestLookupTable [] = 
{
    /* Base Profile Tests */
    {"StateTransitionTest",         OMX_CONF_StateTransitionTest,         OMX_CONF_TestFlag_Base},
    {"ComponentNameTest",           OMX_CONF_ComponentNameTest,           OMX_CONF_TestFlag_Base},
    {"BaseParameterTest",           OMX_CONF_BaseParameterTest,           OMX_CONF_TestFlag_Base},
    {"BufferTest",                  OMX_CONF_BufferTest,                  OMX_CONF_TestFlag_Base},
    {"BufferFlagTest",              OMX_CONF_BufferFlagTest,              OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_AutoOutput},
    {"BaseMultiThreadedTest",       OMX_CONF_BaseMultiThreadedTest,       OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_AutoOutput|OMX_CONF_TestFlag_Threaded},
    {"FlushTest",                   OMX_CONF_FlushTest,                   OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_AutoOutput}, 
    {"PortCommunicationTest",       OMX_CONF_PortCommunicationTest,       OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_AutoOutput}, 
    {"ResourceExhaustionTest",      OMX_CONF_ResourceExhaustionTest,      OMX_CONF_TestFlag_Base}, 
                                                                         
    /* Interop Profile Tests */                                          
    {"ClockComponentTest",          OMX_CONF_ClockComponentTest,          OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_ClockComp},
    {"ValidInputOutputTest",        OMX_CONF_ValidInputOutputTest,        OMX_CONF_TestFlag_Interop},
    {"InvalidInputOutputTest",      OMX_CONF_InvalidInputOutputTest,      OMX_CONF_TestFlag_Interop},
    {"InteropMultiThreadedTest",    OMX_CONF_MultiThreadedTest,           OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_Threaded},
    {"InteropParameterTest",        OMX_CONF_InteropParameterTest,        OMX_CONF_TestFlag_Interop},
    {"PortBufferSupplierTest",      OMX_CONF_PortBufferSupplierTest,      OMX_CONF_TestFlag_Interop},
    {"PortDisableEnableTest",       OMX_CONF_PortDisableEnableTest,       OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_AutoOutput},
    {"IncompleteStopTest",          OMX_CONF_IncompleteStopTest,          OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_AutoOutput},
    {"ResourcePreemptionTest",      OMX_CONF_ResourcePreemptionTest,      OMX_CONF_TestFlag_Interop},
    {"WaitForResourcesTest",        OMX_CONF_WaitForResourcesTest,        OMX_CONF_TestFlag_Interop},
    {"MinPayloadSizeTest",          OMX_CONF_MinPayloadSizeTest,          OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_AutoOutput},
    {"SeekingComponentTest",        OMX_CONF_SeekingComponentTest,        OMX_CONF_TestFlag_Interop|OMX_CONF_TestFlag_Seeking|OMX_CONF_TestFlag_AutoOutput},
//    {"TunnelledUnitTest",           OMX_CONF_TunnelledUnitTest,           0},

    /* Standard Component Class Tests */
    {"StdAudioDecoderTest",         OMX_CONF_StdAudioDecoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdMp3DecoderTest",           OMX_CONF_StdMp3DecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAacDecoderTest",           OMX_CONF_StdAacDecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdRealAudioDecoderTest",     OMX_CONF_StdRealAudioDecoderTest,     OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdWmaDecoderTest",           OMX_CONF_StdWmaDecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdVideoDecoderTest",         OMX_CONF_StdVideoDecoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdH263DecoderTest",          OMX_CONF_StdH263DecoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAvcDecoderTest",           OMX_CONF_StdAvcDecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdMpeg4DecoderTest",         OMX_CONF_StdMpeg4DecoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdRvDecoderTest",            OMX_CONF_StdRvDecoderTest,            OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdWmvDecoderTest",           OMX_CONF_StdWmvDecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdVp8DecoderTest",           OMX_CONF_StdVp8DecoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdReaderTest",               OMX_CONF_StdReaderTest,               OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryAudioReaderTest",    OMX_CONF_StdBinaryAudioReaderTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryVideoReaderTest",    OMX_CONF_StdBinaryVideoReaderTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryImageReaderTest",    OMX_CONF_StdBinaryImageReaderTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdWriterTest",               OMX_CONF_StdWriterTest,               OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryAudioWriterTest",    OMX_CONF_StdBinaryAudioWriterTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryVideoWriterTest",    OMX_CONF_StdBinaryVideoWriterTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdBinaryImageWriterTest",    OMX_CONF_StdBinaryImageWriterTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAudioCapturerTest",        OMX_CONF_StdAudioCapturerTest,        OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdPcmCapturerTest",          OMX_CONF_StdPcmCapturerTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdVideoEncoderTest",         OMX_CONF_StdVideoEncoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdH263EncoderTest",          OMX_CONF_StdH263EncoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAvcEncoderTest",           OMX_CONF_StdAvcEncoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdMpeg4EncoderTest",         OMX_CONF_StdMpeg4EncoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdVp8EncoderTest",           OMX_CONF_StdVp8EncoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdImageDecoderTest",         OMX_CONF_StdImageDecoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdJpegDecoderTest",          OMX_CONF_StdJpegDecoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdWebpDecoderTest",          OMX_CONF_StdWebpDecoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdImageEncoderTest",         OMX_CONF_StdImageEncoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdJpegEncoderTest",          OMX_CONF_StdJpegEncoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdWebpEncoderTest",          OMX_CONF_StdWebpEncoderTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdIVRendererTest",           OMX_CONF_StdIVRendererTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdYuvOverlayTest",           OMX_CONF_StdYuvOverlayTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdRgbOverlayTest",           OMX_CONF_StdRgbOverlayTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAudioProcessorTest",       OMX_CONF_StdAudioProcessorTest,       OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAudioMixerTest",           OMX_CONF_StdAudioMixerTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdPcmMixerTest",             OMX_CONF_StdPcmMixerTest,             OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAudioRendererTest",        OMX_CONF_StdAudioRendererTest,        OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdPcmRendererTest",          OMX_CONF_StdPcmRendererTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAudioEncoderTest",         OMX_CONF_StdAudioEncoderTest,         OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdMp3EncoderTest",           OMX_CONF_StdMp3EncoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAacEncoderTest",           OMX_CONF_StdAacEncoderTest,           OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdClockTest",                OMX_CONF_StdClockTest,                OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdCameraTest",               OMX_CONF_StdCameraTest,               OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdYuvCameraTest",            OMX_CONF_StdYuvCameraTest,            OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdContainerDemuxerTest",     OMX_CONF_StdContainerDemuxerTest,     OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"Std3GpContainerDemuxerTest",  OMX_CONF_Std3GpContainerDemuxerTest,  OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdAsfContainerDemuxerTest",  OMX_CONF_StdAsfContainerDemuxerTest,  OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdRealContainerDemuxerTest", OMX_CONF_StdRealContainerDemuxerTest, OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"Std3GpContainerMuxerTest",    OMX_CONF_Std3GpContainerMuxerTest,    OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdVideoSchedulerTest",       OMX_CONF_StdVideoSchedulerTest,       OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_StdRoleClass},
    {"StdComponentRoleTest",        OMX_CONF_StdComponentRoleTest,        OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent},
    {"DataMetabolismTest",          OMX_CONF_DataMetabolismTest,          OMX_CONF_TestFlag_Base|OMX_CONF_TestFlag_StdComponent|OMX_CONF_TestFlag_Metabolism}

    
#ifdef OSAL_TESTS
    /* special tests for OSAL layer (useful when bringing up new platform); component is ignored */
    ,{"_OSAL_All", OMX_OSAL_TestAll},
    {"_OSAL_MemoryTest1", OMX_OSAL_MemoryTest1},
    {"_OSAL_MultiThreadTest1", OMX_OSAL_MultiThreadTest1},
    {"_OSAL_TimereTest1", OMX_OSAL_TimerTest1}
#endif
};

OMX_U32 g_OMX_CONF_nTestLookupTableEntries = sizeof(g_OMX_CONF_TestLookupTable)/sizeof(OMX_CONF_TESTLOOKUPTYPE);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
