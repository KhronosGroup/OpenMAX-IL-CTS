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

/** OMX_CONF_StdAudioCapturerTest.c
 *  OpenMax IL conformance test - Standard Audio Capturer Class Component Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdAudioCapturerTest"


/**************************** G L O B A L S **********************************/

/*****************************************************************************/

OMX_ERRORTYPE StdAudioCapturerTest_PcmCapturer(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;
    OMX_AUDIO_CONFIG_MUTETYPE sMuteType;
    OMX_AUDIO_CONFIG_VOLUMETYPE sVolumeType;
    OMX_AUDIO_PARAM_PCMMODETYPE sFormatPCM;

    OMX_CONF_INIT_STRUCT(sMuteType, OMX_AUDIO_CONFIG_MUTETYPE);
    OMX_CONF_INIT_STRUCT(sVolumeType, OMX_AUDIO_CONFIG_VOLUMETYPE);
    OMX_CONF_INIT_STRUCT(sFormatPCM, OMX_AUDIO_PARAM_PCMMODETYPE);

    eError = StdComponentTest_SetRole(pCtx, "audio_capturer.pcm");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard PCM Capturer component, there must be at least one port each of 
       audio domain and other domain. */
    if (pCtx->sPortParamAudio.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);
    if (pCtx->sPortParamOther.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; Output port, PCM format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying PCM output port 0 \n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                            
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

    /* Verify support for OMX_IndexConfigAudioMute and verify the default value. */
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;          
    sMuteType.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0; 
    eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioMute, (OMX_PTR)&sMuteType);
    if (sMuteType.bMute != OMX_FALSE)
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify this value can be changed.*/
    OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioMute, 
                                            (OMX_PTR)&sMuteType, 
                                            sMuteType.bMute,
                                            OMX_TRUE, OMX_FALSE, eError);    

    /* Verify support for OMX_IndexConfigAudioVolume and verify the default value. */    
    sVolumeType.nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigAudioVolume, (OMX_PTR)&sVolumeType);
    if (sVolumeType.bLinear != OMX_FALSE) 
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify this value can be changed.*/
    OMX_CONF_CONFIG_READ_WRITE_VERIFY(pCtx, OMX_IndexConfigAudioVolume, 
                                            (OMX_PTR)&sVolumeType, 
                                            sVolumeType.bLinear,
                                            OMX_TRUE, OMX_FALSE, eError); 

    /* Verify - Port Index = OPB + 0; input port, OTHER format */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying other (media time) input port 0 \n");
    nPortIndex = pCtx->sPortParamOther.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdCompCommonOther_OtherPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:
    
    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard PCM Capturer. */

OMX_ERRORTYPE OMX_CONF_StdPcmCapturerTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_capturer.pcm");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdAudioCapturerTest_PcmCapturer);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* This runs through and tests all standard components of the audio capturer class 
   exposed and supported by the component. 
*/
OMX_ERRORTYPE OMX_CONF_StdAudioCapturerTest(
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
        if (strstr(sRoles[i], "audio_capturer.pcm") != NULL) {
            eError = OMX_CONF_StdPcmCapturerTest(cComponentName);
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
