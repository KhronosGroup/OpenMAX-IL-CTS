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

/** OMX_CONF_StdAudioDecoderTest.c
 *  OpenMax IL conformance test - Standard Audio Decoder Component Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdAudioDecoderTest"


/**************************** G L O B A L S **********************************/

/*****************************************************************************/
OMX_ERRORTYPE StdAudioDecoderTest_Mp3Decoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.mp3");
    OMX_CONF_BAIL_ON_ERROR(eError);
    
    /* For the standard MP3 decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, mp3 format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying mp3 input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_Mp3PortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_FALSE, 0, 0);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdAudioDecoderTest_AacDecoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.aac");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard AAC decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, AAC format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AAC input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_AacPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_FALSE, 0, 0);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdAudioDecoderTest_RealAudioDecoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.ra");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard Real Audio decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, Real Audio format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying Real Audio input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_RealAudioPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_TRUE, RA_DEFAULT_NCHANNELS, RA_DEFAULT_SAMPLE_RATE);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdAudioDecoderTest_WmaDecoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.wma");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard WMA decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, WMA format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying WMA input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_WmaPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                           
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_FALSE, 0, 0);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdAudioDecoderTest_AmrNbDecoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.amrnb");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard AMR-NB decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, AMR-NB format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AMR-NB input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_AmrNbPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined; 
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_TRUE, AMR_DEFAULT_NCHANNELS, AMR_DEFAULT_SAMPLE_RATE);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdAudioDecoderTest_AmrWbDecoder(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "audio_decoder.amrwb");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard AMR-WB decoder component, there must be at least two audio domain ports. */
    if (pCtx->sPortParamAudio.nPorts < 2) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; input port, AMR-WB format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AMR-WB input port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_AmrWbPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 1; outpt port, pcm format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying pcm output port 1 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 1;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_TRUE, AMRWB_DEFAULT_NCHANNELS, AMRWB_DEFAULT_SAMPLE_RATE);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard MP3 Decoder. */

OMX_ERRORTYPE OMX_CONF_StdMp3DecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.mp3");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_Mp3Decoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard AAC Decoder. */

OMX_ERRORTYPE OMX_CONF_StdAacDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.aac");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_AacDecoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard RealAudio Decoder. */

OMX_ERRORTYPE OMX_CONF_StdRealAudioDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.ra");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_RealAudioDecoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard WMA Decoder. */

OMX_ERRORTYPE OMX_CONF_StdWmaDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.wma");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_WmaDecoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard AMR-NB Decoder. */

OMX_ERRORTYPE OMX_CONF_StdAmrNbDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.amrnb");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_AmrNbDecoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard AMR-WB Decoder. */

OMX_ERRORTYPE OMX_CONF_StdAmrWbDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_decoder.amrwb");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioDecoderTest_AmrWbDecoder);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* This runs through and tests all standard components of the audio decoder class 
   exposed and supported by the component. 
*/
OMX_ERRORTYPE OMX_CONF_StdAudioDecoderTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nNumRoles = 0;
    OMX_STRING sRoles[MAX_COMPONENT_ROLES] = {NULL};
    OMX_U32 i;

    /* The following utility function calls OMX_GetRolesOfComponent,
       allocates memory, and populates strings.
    */
    eError = StdComponentTest_PopulateRolesArray(cComponentName, &nNumRoles, sRoles);
    OMX_CONF_BAIL_ON_ERROR(eError);

    eError = OMX_ErrorComponentNotFound;
    for (i = 0; i < nNumRoles; i++)
    {
        if (strstr(sRoles[i], "audio_decoder.mp3") != NULL) {
            eError = OMX_CONF_StdMp3DecoderTest(cComponentName);
        }
        else if (strstr(sRoles[i], "audio_decoder.aac") != NULL) {
            eError = OMX_CONF_StdAacDecoderTest(cComponentName);
        }
        else if (strstr(sRoles[i], "audio_decoder.ra") != NULL) {
            eError = OMX_CONF_StdRealAudioDecoderTest(cComponentName);
        }
        else if (strstr(sRoles[i], "audio_decoder.wma") != NULL) {
            eError = OMX_CONF_StdWmaDecoderTest(cComponentName);
        }
        else if (strstr(sRoles[i], "audio_decoder.amrnb") != NULL) {
            eError = OMX_CONF_StdAmrNbDecoderTest(cComponentName);
        }
	else if (strstr(sRoles[i], "audio_decoder.amrwb") != NULL) {
            eError = OMX_CONF_StdAmrWbDecoderTest(cComponentName);
        }
        else {
            continue;
        }
        OMX_CONF_BAIL_ON_ERROR(eError);
    }
    
OMX_CONF_TEST_BAIL:
    StdComponentTest_FreeRolesArray(nNumRoles, sRoles);
    return (eError);
}

/*****************************************************************************/



#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
