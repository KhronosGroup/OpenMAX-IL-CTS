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

/** OMX_CONF_StdCompCommonAudio.c
 *  OpenMax IL conformance test - Standard Component Test
 *  Contains common code that can be reused by various standard audio component tests.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"

#include <string.h>

/**************************** G L O B A L S **********************************/

/*****************************************************************************/

static OMX_ERRORTYPE StdCompCommonAudio_PortFormatSupported(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex,
    OMX_AUDIO_CODINGTYPE eEncoding)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;

    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;

    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying port format support\n");

    sPortFormat.nPortIndex = nPortIndex;

    for (sPortFormat.nIndex = 0; ; sPortFormat.nIndex++)
    {
        eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioPortFormat, (OMX_PTR)&sPortFormat);
        if (OMX_ErrorNoMore == eError)
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);

        if (sPortFormat.eEncoding == eEncoding)
            break;
    }

OMX_CONF_TEST_BAIL:
    return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_Mp3PortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    const OMX_U32 Mp3SampleRate[3] =
        {32000, 44100, 48000};
    
    OMX_U32 i;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    
    OMX_PARAM_PORTDEFINITIONTYPE sPortDefinition;
    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;
    OMX_AUDIO_PARAM_MP3TYPE sFormatMP3;
    OMX_AUDIO_PARAM_MP3TYPE sFormatMP3Save;

 
    OMX_CONF_INIT_STRUCT(sPortDefinition, OMX_PARAM_PORTDEFINITIONTYPE);
    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);    
    OMX_CONF_INIT_STRUCT(sFormatMP3, OMX_AUDIO_PARAM_MP3TYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying MP3 port %i Default parameters\n", nPortIndex);

    /* Verify support for the common standard component port parameters. */
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify Port Definition */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying MP3 port definition\n");
    sPortDefinition.nPortIndex = nPortIndex;
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPortDefinition, (OMX_PTR)&sPortDefinition);
    if ((sPortDefinition.eDomain != OMX_PortDomainAudio) ||
        (sPortDefinition.format.audio.eEncoding != OMX_AUDIO_CodingMP3))
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingMP3\n");

    /* Verify support for OMX_IndexParamAudioPortFormat and verify
       that the port format is as expected.
    */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying component supports OMX_IndexParamAudioPortFormat\n");
    eError = StdCompCommonAudio_PortFormatSupported(pCtx, nPortIndex, OMX_AUDIO_CodingMP3);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingMP3\n"); 
    
    /* Verify default settings for MP3 */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying default values for MP3\n");
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioMp3, (OMX_PTR)&sFormatMP3);
    if ((sFormatMP3.nChannels != 2) ||
        (sFormatMP3.nSampleRate != MP3_DEFAULT_SAMPLE_RATE) ||
        (sFormatMP3.eChannelMode != OMX_AUDIO_ChannelModeStereo) ||
        (sFormatMP3.eFormat != OMX_AUDIO_MP3StreamFormatMP1Layer3))
        eError = OMX_ErrorBadParameter;  /* Need a more informative error value. */
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " nChannels = %d, nSampleRate = %d,"
                        "eChannelMode = %d\n", sFormatMP3.nChannels, 
                        sFormatMP3.nSampleRate, sFormatMP3.eChannelMode);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eMP3StreamFormat =  OMX_AUDIO_MP3StreamFormatMP1Layer3\n");

    /* Verify all possible settings for OMX_IndexParamAudioMp3 now. */ 
    
    /* Store copy of parameter with index OMX_IndexParamAudioMp3 to allow restore after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    sFormatMP3Save = sFormatMP3;
 
    /* Verify all allowed channels could be specified. */   
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying number of audio channels supported\n");
    for (i=0; i < 2; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                            (OMX_PTR)&sFormatMP3, 
                                            sFormatMP3.nChannels,
                                            i+1, eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d \n", sFormatMP3.nChannels);
    }
    
    /* Verify all allowed sample rates can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for sample rates =\n");
    for (i=0; i < 3; i++) {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d ", Mp3SampleRate[i]);
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                            (OMX_PTR)&sFormatMP3, 
                                            sFormatMP3.nSampleRate,
                                            Mp3SampleRate[i], eError);
    } 
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "\n ");

    /* Verify all allowed AudioBandWidth values can be set. */
    for (i=0; i < 2; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                            (OMX_PTR)&sFormatMP3, 
                                            sFormatMP3.nAudioBandWidth,
                                            i, eError);
    }

    /* Verify all allowed eChannelMode values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for eChannelMode values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeStereo\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                        (OMX_PTR)&sFormatMP3, 
                                        sFormatMP3.eChannelMode,
                                        OMX_AUDIO_ChannelModeStereo, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeJointStereo\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                        (OMX_PTR)&sFormatMP3, 
                                        sFormatMP3.eChannelMode,
                                        OMX_AUDIO_ChannelModeJointStereo, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeDual\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                        (OMX_PTR)&sFormatMP3, 
                                        sFormatMP3.eChannelMode,
                                        OMX_AUDIO_ChannelModeDual, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeMono\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioMp3, 
                                        (OMX_PTR)&sFormatMP3, 
                                        sFormatMP3.eChannelMode,
                                        OMX_AUDIO_ChannelModeMono, eError);

    /* Restore parameter with index OMX_IndexParamAudioMp3 after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioMp3, (OMX_PTR)&sFormatMP3Save);

    OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_AacPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    const OMX_U32 AacSampleRate[9] =
        {8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000};
    
    OMX_U32 i;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    
    OMX_PARAM_PORTDEFINITIONTYPE sPortDefinition;
    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;
    OMX_AUDIO_PARAM_AACPROFILETYPE sFormatAAC;
    OMX_AUDIO_PARAM_AACPROFILETYPE sFormatAACSave;
 
    OMX_CONF_INIT_STRUCT(sPortDefinition, OMX_PARAM_PORTDEFINITIONTYPE);
    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);    
    OMX_CONF_INIT_STRUCT(sFormatAAC, OMX_AUDIO_PARAM_AACPROFILETYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AAC Port %i Default parameters\n", nPortIndex);

    /* Verify support for the common standard component port parameters. */
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify Port Definition */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AAC port definition\n");
    sPortDefinition.nPortIndex = nPortIndex;
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPortDefinition, (OMX_PTR)&sPortDefinition);
    if ((sPortDefinition.eDomain != OMX_PortDomainAudio) ||
        (sPortDefinition.format.audio.eEncoding != OMX_AUDIO_CodingAAC))
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingAAC\n");

    /* Verify support for OMX_IndexParamAudioPortFormat and verify
       that the port format is as expected.
    */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying component supports OMX_IndexParamAudioPortFormat\n");
    eError = StdCompCommonAudio_PortFormatSupported(pCtx, nPortIndex, OMX_AUDIO_CodingAAC);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingAAC\n"); 
    
    /* Verify default settings for AAC */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying default values for AAC Profile\n");
    OMX_CONF_INIT_STRUCT(sFormatAAC, OMX_AUDIO_PARAM_AACPROFILETYPE);
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAac, (OMX_PTR)&sFormatAAC);
    if ((sFormatAAC.nChannels != 2) ||
        (sFormatAAC.nSampleRate != AAC_DEFAULT_SAMPLE_RATE) ||
        (sFormatAAC.eAACProfile != OMX_AUDIO_AACObjectLC) ||
        (sFormatAAC.eAACStreamFormat != OMX_AUDIO_AACStreamFormatMP2ADTS) ||
        (sFormatAAC.eChannelMode != OMX_AUDIO_ChannelModeStereo))
        eError = OMX_ErrorBadParameter;  /* Need a more informative error value. */
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " nChannels = %d, nSampleRate = %d, "
                       "eAACProfile = %d, eChannelMode = %d, eAACStreamFormat = %d\n",
                        sFormatAAC.nChannels, sFormatAAC.nSampleRate,
                        sFormatAAC.eAACProfile, sFormatAAC.eAACStreamFormat,
                        sFormatAAC.eChannelMode);

    /* Verify additional defaults applicable to encoder only */
    if (sPortDefinition.eDir == OMX_DirOutput) {
        if ((sFormatAAC.nAudioBandWidth != 0) || (sFormatAAC.nFrameLength != 0))
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
                       " nAudioBandWidth = %d, nFrameLength = %d, ",
                        sFormatAAC.nAudioBandWidth, sFormatAAC.nFrameLength);
    }

    /* Verify all possible settings for OMX_IndexParamAudioAac now. */       
 
    /* Store copy of parameter with index OMX_IndexParamAudioAac to allow restore after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    sFormatAACSave = sFormatAAC;

    /* Verify all allowed channels could be specified. */   
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying number of audio channels supported\n");
    for (i=0; i < 2; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                            (OMX_PTR)&sFormatAAC, 
                                            sFormatAAC.nChannels,
                                            i+1, eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d \n", sFormatAAC.nChannels);
    }
    
    /* Verify all allowed sample rates can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for sample rates =\n");
    for (i=0; i<9; i++) {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d ", AacSampleRate[i]);
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                            (OMX_PTR)&sFormatAAC, 
                                            sFormatAAC.nSampleRate,
                                            AacSampleRate[i], eError);
    } 
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "\n ");
   
    /* Verify all allowed eAACProfile values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for eAACProfile values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACObjectLC\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACProfile,
                                        OMX_AUDIO_AACObjectLC, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACObjectHE\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACProfile,
                                        OMX_AUDIO_AACObjectHE, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACObjectHE_PS\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACProfile,
                                        OMX_AUDIO_AACObjectHE_PS, eError);

    /* Verify all allowed eAACStreamFormat values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for eAACStreamFormat values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACStreamFormatMP2ADTS\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACStreamFormat,
                                        OMX_AUDIO_AACStreamFormatMP2ADTS, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACStreamFormatMP4ADTS\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACStreamFormat,
                                        OMX_AUDIO_AACStreamFormatMP4ADTS, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACStreamFormatADIF\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACStreamFormat,
                                        OMX_AUDIO_AACStreamFormatADIF, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_AACStreamFormatRAW\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eAACStreamFormat,
                                        OMX_AUDIO_AACStreamFormatRAW, eError);

    /* Verify all allowed eChannelMode values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for eChannelMode values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeStereo\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eChannelMode,
                                        OMX_AUDIO_ChannelModeStereo, eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_ChannelModeMono\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAac, 
                                        (OMX_PTR)&sFormatAAC, 
                                        sFormatAAC.eChannelMode,
                                        OMX_AUDIO_ChannelModeMono, eError);

    /* Restore parameter with index OMX_IndexParamAudioAac after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAac, (OMX_PTR)&sFormatAACSave);

    OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_RealAudioPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;

    UNUSED_PARAMETER(pCtx);
    UNUSED_PARAMETER(nPortIndex);

    // Placeholder for actual real audio code.

    //OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_WmaPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;

    UNUSED_PARAMETER(pCtx);
    UNUSED_PARAMETER(nPortIndex);

    // Placeholder for actual real audio code.

    //OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_AmrNbPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    const OMX_U32 AmrBitRate[8] =
        {OMX_AUDIO_AMRBandModeNB0, 
		OMX_AUDIO_AMRBandModeNB1, 
		OMX_AUDIO_AMRBandModeNB2, 
		OMX_AUDIO_AMRBandModeNB3, 
		OMX_AUDIO_AMRBandModeNB4, 
		OMX_AUDIO_AMRBandModeNB5, 
		OMX_AUDIO_AMRBandModeNB6, 
		OMX_AUDIO_AMRBandModeNB7};
    
    OMX_U32 i;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    
    OMX_PARAM_PORTDEFINITIONTYPE sPortDefinition;
    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;
    OMX_AUDIO_PARAM_AMRTYPE sFormatAMR;
    OMX_AUDIO_PARAM_AMRTYPE sFormatAMRSave;
 
    OMX_CONF_INIT_STRUCT(sPortDefinition, OMX_PARAM_PORTDEFINITIONTYPE);
    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);    
    OMX_CONF_INIT_STRUCT(sFormatAMR, OMX_AUDIO_PARAM_AMRTYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AMR-NB port %i Default parameters\n", nPortIndex);

    /* Verify support for the common standard component port parameters. */
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify Port Definition */
    sPortDefinition.nPortIndex = nPortIndex;
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPortDefinition, (OMX_PTR)&sPortDefinition);
    if ((sPortDefinition.eDomain != OMX_PortDomainAudio) ||
        (sPortDefinition.format.audio.eEncoding != OMX_AUDIO_CodingAMR))
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify support for OMX_IndexParamAudioPortFormat and verify
       that the port format is as expected.
    */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying component supports OMX_IndexParamAudioPortFormat\n");
    eError = StdCompCommonAudio_PortFormatSupported(pCtx, nPortIndex, OMX_AUDIO_CodingAMR);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingAMR\n"); 
    
    /* Verify default settings for AMR */
    OMX_CONF_INIT_STRUCT(sFormatAMR, OMX_AUDIO_PARAM_AMRTYPE);
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAmr, (OMX_PTR)&sFormatAMR);
    if ((sFormatAMR.nChannels != 1))
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

    if ((sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB0) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB1) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB2) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB3) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB4) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB5) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB6) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeNB7)) 
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

	
    if ((sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOff) &&		
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnVAD1) &&
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnVAD2) &&
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnAuto)) 
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

    if ((sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatConformance) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatIF1) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatIF2) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatFSF) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatRTPPayload))
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

		
    /* Verify all possible settings for OMX_IndexParamAudioAmr now. */       
 
    /* Store copy of parameter with index OMX_IndexParamAudioAmr to allow restore after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    sFormatAMRSave = sFormatAMR;

    /* Verify all allowed channels could be specified. */   
    for (i=0; i < 1; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.nChannels,
                                            i+1, eError);
    }
    
    /* Verify all allowed band modes can be set. */
    for (i=0; i<8; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRBandMode,
                                            AmrBitRate[i], eError);
    } 

    /* Verify all allowed eAMRDTXMode values can be set. */
    for (i=0; i < 4; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRDTXMode,
                                            i, eError);
    }

    /* Verify all allowed eChannelMode values can be set. */
    for (i=0; i<5; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRFrameFormat,
                                            i, eError);
    } 


    /* Restore parameter with index OMX_IndexParamAudioAmr after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAmr, (OMX_PTR)&sFormatAMRSave);

    OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_AmrWbPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex)
{    
    const int AmrBitRate[9] =
        {OMX_AUDIO_AMRBandModeWB0, 
		OMX_AUDIO_AMRBandModeWB1, 
		OMX_AUDIO_AMRBandModeWB2, 
		OMX_AUDIO_AMRBandModeWB3, 
		OMX_AUDIO_AMRBandModeWB4, 
		OMX_AUDIO_AMRBandModeWB5, 
		OMX_AUDIO_AMRBandModeWB6, 
		OMX_AUDIO_AMRBandModeWB7, 
		OMX_AUDIO_AMRBandModeWB8};
    
    OMX_U32 i;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    
    OMX_PARAM_PORTDEFINITIONTYPE sPortDefinition;
    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;
    OMX_AUDIO_PARAM_AMRTYPE sFormatAMR;
    OMX_AUDIO_PARAM_AMRTYPE sFormatAMRSave;
 
    OMX_CONF_INIT_STRUCT(sPortDefinition, OMX_PARAM_PORTDEFINITIONTYPE);
    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);    
    OMX_CONF_INIT_STRUCT(sFormatAMR, OMX_AUDIO_PARAM_AMRTYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying AMR-WB port %i Default parameters\n", nPortIndex);

    /* Verify support for the common standard component port parameters. */
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify Port Definition */
    sPortDefinition.nPortIndex = nPortIndex;
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPortDefinition, (OMX_PTR)&sPortDefinition);
    if ((sPortDefinition.eDomain != OMX_PortDomainAudio) ||
        (sPortDefinition.format.audio.eEncoding != OMX_AUDIO_CodingAMR))
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify support for OMX_IndexParamAudioPortFormat and verify
       that the port format is as expected.
    */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying component supports OMX_IndexParamAudioPortFormat\n");
    eError = StdCompCommonAudio_PortFormatSupported(pCtx, nPortIndex, OMX_AUDIO_CodingAMR);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingAMR\n");
    
    /* Verify default settings for AMR */
    OMX_CONF_INIT_STRUCT(sFormatAMR, OMX_AUDIO_PARAM_AMRTYPE);
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAmr, (OMX_PTR)&sFormatAMR);
    if ((sFormatAMR.nChannels != 1))
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

    if ((sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB0) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB1) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB2) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB3) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB4) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB5) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB6) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB7) &&
		(sFormatAMR.eAMRBandMode != OMX_AUDIO_AMRBandModeWB8)) 
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

    if ((sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOff) &&		
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnVAD1) &&
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnVAD2) &&
		(sFormatAMR.eAMRDTXMode != OMX_AUDIO_AMRDTXModeOnAuto)) 
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

    if ((sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatConformance) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatIF1) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatIF2) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatFSF) &&		
		(sFormatAMR.eAMRFrameFormat != OMX_AUDIO_AMRFrameFormatRTPPayload))
		eError = OMX_ErrorBadParameter;
    OMX_CONF_BAIL_ON_ERROR(eError);

		
    /* Verify all possible settings for OMX_IndexParamAudioAmr now. */       
 
    /* Store copy of parameter with index OMX_IndexParamAudioAmr to allow restore after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    sFormatAMRSave = sFormatAMR;

    /* Verify all allowed channels could be specified. */   
    for (i=0; i < 1; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.nChannels,
                                            i+1, eError);
    }
    
    /* Verify all allowed band modes can be set. */
    for (i=0; i<9; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRBandMode,
                                            AmrBitRate[i], eError);
    } 

    /* Verify all allowed eAMRDTXMode values can be set. */
    for (i=0; i < 4; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRDTXMode,
                                            i, eError);
    }

    /* Verify all allowed eChannelMode values can be set. */
    for (i=0; i<5; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioAmr, 
                                            (OMX_PTR)&sFormatAMR, 
                                            sFormatAMR.eAMRFrameFormat,
                                            i, eError);
    } 


    /* Restore parameter with index OMX_IndexParamAudioAmr after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioAmr, (OMX_PTR)&sFormatAMRSave);

    OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdCompCommonAudio_PcmPortParameters(
    TEST_CTXTYPE *pCtx,
    OMX_U32 nPortIndex,
    OMX_BOOL bDefaultOverride,
    OMX_U32 nChannels,
    OMX_U32 nSamplingRate)

{    
    const OMX_U32 PcmSamplingRate[9] = 
        {8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000};

    OMX_U32 i;
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    
    OMX_PARAM_PORTDEFINITIONTYPE sPortDefinition;
    OMX_AUDIO_PARAM_PORTFORMATTYPE sPortFormat;
    OMX_AUDIO_PARAM_PCMMODETYPE sFormatPCM;
    OMX_AUDIO_PARAM_PCMMODETYPE sFormatPCMSave;

    OMX_U32 nSamplingRate_Default = PCM_DEFAULT_SAMPLE_RATE;
    OMX_U32 nChannels_Default = 2;
 
    OMX_CONF_INIT_STRUCT(sPortDefinition, OMX_PARAM_PORTDEFINITIONTYPE);
    OMX_CONF_INIT_STRUCT(sPortFormat, OMX_AUDIO_PARAM_PORTFORMATTYPE);    
    OMX_CONF_INIT_STRUCT(sFormatPCM, OMX_AUDIO_PARAM_PCMMODETYPE);

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying PCM Port %i Default parameters\n", nPortIndex);

    /* Verify support for the common standard component port parameters. */
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify Port Definition */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying PCM port definition\n");
    sPortDefinition.nPortIndex = nPortIndex;
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPortDefinition, (OMX_PTR)&sPortDefinition);
    if ((sPortDefinition.eDomain != OMX_PortDomainAudio) ||
        (sPortDefinition.format.audio.eEncoding != OMX_AUDIO_CodingPCM))
        eError = OMX_ErrorBadParameter;  // OMX_ErrorBadPortFormatEncoding
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingPCM\n");

    /* Verify support for OMX_IndexParamAudioPortFormat and verify
       that the port format is as expected.
    */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying component supports OMX_IndexParamAudioPortFormat\n");
    eError = StdCompCommonAudio_PortFormatSupported(pCtx, nPortIndex, OMX_AUDIO_CodingPCM);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " eEncoding = OMX_AUDIO_CodingPCM\n");
    
    /* Verify default settings for PCM */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying default values for PCM Param\n");
    OMX_CONF_INIT_STRUCT(sFormatPCM, OMX_AUDIO_PARAM_PCMMODETYPE);
    sFormatPCM.nPortIndex = nPortIndex; // Make sure asking for the right port!
    if(bDefaultOverride)
    {
      nSamplingRate_Default = nSamplingRate;
      nChannels_Default = nChannels;
    }
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioPcm, (OMX_PTR)&sFormatPCM);
    if ((sFormatPCM.nChannels != nChannels_Default) ||
        (sFormatPCM.eNumData != OMX_NumericalDataSigned) ||
        (sFormatPCM.nBitPerSample != 16) ||
        (sFormatPCM.nSamplingRate != nSamplingRate_Default) ||
        (sFormatPCM.ePCMMode != OMX_AUDIO_PCMModeLinear))
        eError = OMX_ErrorBadParameter;  /* Need a more informative error value. */
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " nChannels = %d, eNumData = %d, "
                       " nBitPerSample = %d, nSamplingRate = %d, ePCMMode = %d\n",
                        sFormatPCM.nChannels, sFormatPCM.eNumData,
                        sFormatPCM.nBitPerSample,
                        sFormatPCM.nSamplingRate, sFormatPCM.ePCMMode);

    /* Specific to encoder only. */
    if(sPortDefinition.eDir == OMX_DirInput) {                        
        if (sFormatPCM.bInterleaved != OMX_TRUE) 
            eError = OMX_ErrorBadParameter;
        OMX_CONF_BAIL_ON_ERROR(eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "bInterleaved = %d\n",
                                         sFormatPCM.bInterleaved);
    }

    /* Verify all possible settings for OMX_IndexParamAudioPcm now. */  
    /* Store copy of parameter with index OMX_IndexParamAudioPcm to allow restore after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    sFormatPCMSave = sFormatPCM;

    /* Verify all allowed channels could be specified. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying number of audio channels supported\n");
    for (i=0; i < 2; i++) {
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioPcm, 
                                            (OMX_PTR)&sFormatPCM, 
                                            sFormatPCM.nChannels,
                                            i+1, eError);
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d \n", sFormatPCM.nChannels);
    }
    
    /* Verify all allowed sample rates can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for sample rates\n");
    for (i=0; i<9; i++) {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " %d ", PcmSamplingRate[i]);
        OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioPcm, 
                                            (OMX_PTR)&sFormatPCM, 
                                            sFormatPCM.nSamplingRate,
                                            PcmSamplingRate[i], eError);
    } 
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "\n ");

    /* Verify all allowed eNumData values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for eNumData values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_NumericalDataSigned\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioPcm, 
                                        (OMX_PTR)&sFormatPCM, 
                                        sFormatPCM.eNumData,
                                        OMX_NumericalDataSigned, eError);

    /* Verify all allowed ePCMMode values can be set. */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying support for ePCMMode values\n");
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, " OMX_AUDIO_PCMModeLinear\n");
    OMX_CONF_PARAM_READ_WRITE_VERIFY(pCtx, OMX_IndexParamAudioPcm, 
                                        (OMX_PTR)&sFormatPCM, 
                                        sFormatPCM.ePCMMode,
                                        OMX_AUDIO_PCMModeLinear, eError);

    /* Restore parameter with index OMX_IndexParamAudioPcm after use of OMX_CONF_PARAM_READ_WRITE_VERIFY*/
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamAudioPcm, (OMX_PTR)&sFormatPCMSave);

    OMX_CONF_TEST_BAIL:
        return(eError);
}

/*****************************************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
