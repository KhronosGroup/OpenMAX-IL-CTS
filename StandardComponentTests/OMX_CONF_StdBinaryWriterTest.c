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

/** OMX_CONF_StdBinaryWriterTest.c
 *  OpenMax IL conformance test - Standard Binary Writer Component Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdBinaryWriterTest"


/**************************** G L O B A L S **********************************/

/*****************************************************************************/

OMX_ERRORTYPE StdWriterTest_BinaryAudioWriter(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;
 
    eError = StdComponentTest_SetRole(pCtx, "audio_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard binary audio writer component, there must be at least one audio domain port. */
    if (pCtx->sPortParamAudio.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = APB + 0; output port */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying OMX_AUDIOPORTBASE + 0 is input port \n\n");
    nPortIndex = pCtx->sPortParamAudio.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:    
        return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdWriterTest_BinaryVideoWriter(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "video_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard binary video writer component, there must be at least one video domain port. */
    if (pCtx->sPortParamVideo.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = VPB + 0; output port */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying OMX_VIDEOPORTBASE + 0 is input port \n\n");
    nPortIndex = pCtx->sPortParamVideo.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:    
        return (eError);
}

/*****************************************************************************/

OMX_ERRORTYPE StdWriterTest_BinaryImageWriter(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex;

    eError = StdComponentTest_SetRole(pCtx, "image_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard binary image writer component, there must be at least one image domain port. */
    if (pCtx->sPortParamImage.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* Verify - Port Index = IPB + 0; output port */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying OMX_IMAGEPORTBASE + 0 is input port \n\n");
    nPortIndex = pCtx->sPortParamImage.nStartPortNumber + 0;
    if (StdComponentTest_IsInputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;                             
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = StdComponentTest_StdPortParameters(pCtx, nPortIndex);
    OMX_CONF_BAIL_ON_ERROR(eError);

OMX_CONF_TEST_BAIL:    
        return (eError);
}

/*****************************************************************************/
/* Test a component for compliance with the Standard Audio Writer Component. */

OMX_ERRORTYPE OMX_CONF_StdBinaryAudioWriterTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_IsRoleSupported(cComponentName, "audio_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdWriterTest_BinaryAudioWriter);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard Video Writer Component. */

OMX_ERRORTYPE OMX_CONF_StdBinaryVideoWriterTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_IsRoleSupported(cComponentName, "video_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdWriterTest_BinaryVideoWriter);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard Image Writer Component. */

OMX_ERRORTYPE OMX_CONF_StdBinaryImageWriterTest(
    OMX_IN OMX_STRING cComponentName)
{    
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_IsRoleSupported(cComponentName, "image_writer.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdWriterTest_BinaryImageWriter);    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* This runs through and tests all standard components of the binary writer class 
   exposed and supported by the component. 
*/
OMX_ERRORTYPE OMX_CONF_StdWriterTest(
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
        if (strstr(sRoles[i], "audio_writer.binary") != NULL) {
            eError = OMX_CONF_StdBinaryAudioWriterTest(cComponentName);
        }
        else if (strstr(sRoles[i], "video_writer.binary") != NULL) {
            eError = OMX_CONF_StdBinaryVideoWriterTest(cComponentName);
        }
        else if (strstr(sRoles[i], "image_writer.binary") != NULL) {
            eError = OMX_CONF_StdBinaryImageWriterTest(cComponentName);
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
