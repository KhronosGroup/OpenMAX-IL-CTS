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

/** OMX_CONF_StdAudioMixerTest.c
 *  OpenMax IL conformance test - Standard Audio Mixer Component Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdAudioMixerTest"

/**************************** G L O B A L S **********************************/

/*****************************************************************************/

OMX_ERRORTYPE StdAudioMixerTest_PcmMixer(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex, i;
   
    OMX_AUDIO_PARAM_PCMMODETYPE sFormatPCM;
    OMX_AUDIO_CONFIG_VOLUMETYPE sVolume;
    OMX_AUDIO_CONFIG_MUTETYPE sMute;
    
    OMX_CONF_INIT_STRUCT(sFormatPCM, OMX_AUDIO_PARAM_PCMMODETYPE);
    OMX_CONF_INIT_STRUCT(sVolume, OMX_AUDIO_CONFIG_VOLUMETYPE);
    OMX_CONF_INIT_STRUCT(sMute, OMX_AUDIO_CONFIG_MUTETYPE);
    
    eError = StdComponentTest_SetRole(pCtx, "audio_mixer.pcm");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; output port, PCM format */    
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying PCM output port %d \n",nPortIndex);
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE)
        eError = OMX_ErrorUndefined; 
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_FALSE, 0, 0);
    OMX_CONF_BAIL_ON_ERROR(eError);        

    /* Verify additional defaults specific to this class. */
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioPcm, (OMX_PTR)&sFormatPCM);
    if ((sFormatPCM.bInterleaved != OMX_TRUE) ||
        (sFormatPCM.eChannelMapping[0] != OMX_AUDIO_ChannelLF) ||
        (sFormatPCM.eChannelMapping[1] != OMX_AUDIO_ChannelRF)) 
        eError = OMX_ErrorBadParameter;
     OMX_CONF_BAIL_ON_ERROR(eError);
     OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bInterleaved = OMX_TRUE, "
                            "eChannelMapping[0] = OMX_AUDIO_ChannelLF , "
                            "eChannelMapping[0] = OMX_AUDIO_ChannelRF\n");

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for OMX_IndexConfigAudioVolume\n");
    sVolume.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioVolume, (OMX_PTR)&sVolume);
    OMX_CONF_BAIL_ON_ERROR(eError);
    if (sVolume.bLinear != OMX_FALSE) 
        eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bLinear = OMX_FALSE\n");
    
    /* Verify this value can be changed.*/
    OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioVolume,
                                            (OMX_PTR)&sVolume, sVolume.bLinear,
                                            OMX_TRUE, OMX_FALSE, eError);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for OMX_IndexConfigAudioMute\n");
    sMute.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioMute, (OMX_PTR)&sMute);
    OMX_CONF_BAIL_ON_ERROR(eError);
    if (sMute.bMute != OMX_FALSE) 
        eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bMute = OMX_FALSE\n");

    /* Verify this value can be changed.*/
    OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioMute,
                                            (OMX_PTR)&sMute, sMute.bMute,
                                            OMX_TRUE, OMX_FALSE, eError);

    /* Verify - Port Index = (APB + 1) + i; input port, PCM format */
    for (i = 1; i < pCtx->sPortParamAudio.nPorts; i++) {
        nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + i;        
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying PCM input port %d \n",nPortIndex);
        if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
        OMX_CONF_BAIL_ON_ERROR(eError);
        eError = StdCompCommonAudio_PcmPortParameters(pCtx, nPortIndex, OMX_FALSE, 0, 0);
        OMX_CONF_BAIL_ON_ERROR(eError);

        /* Verify additional defaults specific to audio_mixer. */
        eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioPcm, (OMX_PTR)&sFormatPCM);
        OMX_CONF_BAIL_ON_ERROR(eError);
        if ((sFormatPCM.bInterleaved != OMX_TRUE) ||
            (sFormatPCM.eChannelMapping[0] != OMX_AUDIO_ChannelLF) ||
            (sFormatPCM.eChannelMapping[1] != OMX_AUDIO_ChannelRF)) 
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bInterleaved = OMX_TRUE, "
                                "eChannelMapping[0] = OMX_AUDIO_ChannelLF , "
                                "eChannelMapping[0] = OMX_AUDIO_ChannelRF\n");

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for OMX_IndexConfigAudioVolume\n");
        sVolume.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + i;
        eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioVolume, (OMX_PTR)&sVolume);
        OMX_CONF_BAIL_ON_ERROR(eError);
        if (sVolume.bLinear != OMX_FALSE) 
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bLinear = OMX_FALSE\n");
        
        /* Verify this value can be changed.*/
        OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioVolume,
                                                (OMX_PTR)&sVolume, sVolume.bLinear,
                                                OMX_TRUE, OMX_FALSE, eError);

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for OMX_IndexConfigAudioMute\n");
        sMute.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + i;
        eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioMute, (OMX_PTR)&sMute);
        OMX_CONF_BAIL_ON_ERROR(eError);
        if (sMute.bMute != OMX_FALSE) 
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " bMute = OMX_FALSE\n");

        /* Verify this value can be changed.*/
        OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioMute,
                                            (OMX_PTR)&sMute, sMute.bMute,
                                            OMX_TRUE, OMX_FALSE, eError);
    }   


OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard PCM Audio Mixer. */

OMX_ERRORTYPE OMX_CONF_StdPcmMixerTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_mixer.pcm");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioMixerTest_PcmMixer);

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* This runs through and tests all standard components of the Audio Mixer
   class exposed and supported by the component.
*/
OMX_ERRORTYPE OMX_CONF_StdAudioMixerTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nNumRoles;
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
        if (strstr(sRoles[i], "audio_mixer") != NULL) {
            eError = OMX_CONF_StdPcmMixerTest(cComponentName);
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
