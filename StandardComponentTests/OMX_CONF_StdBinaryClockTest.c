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

/** OMX_CONF_StdBinaryClockTest.c
 *  OpenMax IL conformance test - Standard Binary Clock Component Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_CONF_StdCompCommon.h"
#include <string.h>

#define TEST_NAME_STRING "StdBinaryClockTest"

/**************************** G L O B A L S **********************************/

/*****************************************************************************/

OMX_ERRORTYPE StdBinaryClockTest_BinaryClock(TEST_CTXTYPE *pCtx)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_U32 nPortIndex, i;

    OMX_TIME_CONFIG_SCALETYPE sScale;   //OMX_IndexConfigTimeScale      
    OMX_TIME_CONFIG_CLOCKSTATETYPE sClockState; //OMX_IndexConfigTimeClockState
    OMX_TIME_CONFIG_ACTIVEREFCLOCKTYPE sActiveRefClock; //OMX_IndexConfigTimeActiveRefClock
    OMX_TIME_CONFIG_TIMESTAMPTYPE sTimeStamp;   // OMX_IndexConfigTimeCurrentMediaTime, 
                                                // OMX_IndexConfigTimeCurrentWallTime 
                                                // OMX_IndexConfigTimeCurrentAudioReference
                                                // OMX_IndexConfigTimeCurrentVideoReference
                                                // OMX_IndexConfigTimeClientStartTime
    OMX_TIME_CONFIG_MEDIATIMEREQUESTTYPE sMediaTimeRequest; //OMX_IndexConfigTimeMediaTimeRequest

    OMX_CONF_INIT_STRUCT(sScale, OMX_TIME_CONFIG_SCALETYPE);
    OMX_CONF_INIT_STRUCT(sClockState, OMX_TIME_CONFIG_CLOCKSTATETYPE);
    OMX_CONF_INIT_STRUCT(sActiveRefClock, OMX_TIME_CONFIG_ACTIVEREFCLOCKTYPE);
    OMX_CONF_INIT_STRUCT(sTimeStamp, OMX_TIME_CONFIG_TIMESTAMPTYPE);
    OMX_CONF_INIT_STRUCT(sMediaTimeRequest, OMX_TIME_CONFIG_MEDIATIMEREQUESTTYPE);

    eError = StdComponentTest_SetRole(pCtx, "clock.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    /* For the standard binary clock component, there must be at least one
       OTHER domain ports. There is no limit on the maximum number of ports.*/ 
    if (pCtx->sPortParamOther.nPorts < 1) eError = OMX_ErrorUndefined;
    OMX_CONF_BAIL_ON_ERROR(eError);    

    /* Verify - Port Index = OPB + i; output port, other format */
    for (i = 0; i < pCtx->sPortParamOther.nPorts; i++) {
        nPortIndex = pCtx->sPortParamOther.nStartPortNumber + i;        
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Verifying clock output port %d \n",nPortIndex);
        if (StdComponentTest_IsOutputPort(pCtx, nPortIndex) == OMX_FALSE) eError = OMX_ErrorUndefined;
        OMX_CONF_BAIL_ON_ERROR(eError);
        eError = StdCompCommonOther_OtherPortParameters(pCtx, nPortIndex);
        OMX_CONF_BAIL_ON_ERROR(eError);

        /* Verify R/W accesses. There are no default values in the specification. */
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying R/W access for OMX_IndexConfigTimeScale\n");
        OMX_CONF_CONFIG_REQUIREDGETSET(pCtx, OMX_IndexConfigTimeScale, 
                                        (OMX_PTR)&sScale,
                                        eError);    // R/W

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying R/W access for OMX_IndexConfigTimeClockState\n");
        OMX_CONF_CONFIG_REQUIREDGETSET(pCtx, OMX_IndexConfigTimeClockState, 
                                        (OMX_PTR)&sClockState,
                                        eError);    // R/W

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying R/W access for OMX_IndexConfigTimeActiveRefClock\n");
        OMX_CONF_CONFIG_REQUIREDGETSET(pCtx, OMX_IndexConfigTimeActiveRefClock, 
                                        (OMX_PTR)&sActiveRefClock,
                                        eError);    // R/W

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Read access for iOMX_IndexConfigTimeCurrentMediaTime\n");
        eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeCurrentMediaTime, 
                                     (OMX_PTR)&sTimeStamp);   //Read Access.
        OMX_CONF_BAIL_ON_ERROR(eError);    

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Read access for OMX_IndexConfigTimeCurrentWallTime\n");
        eError = OMX_GetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeCurrentWallTime, 
                                     (OMX_PTR)&sTimeStamp);   //Read Access.
        OMX_CONF_BAIL_ON_ERROR(eError);

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Write access for OMX_IndexConfigTimeCurrentAudioReference\n");
        eError = OMX_SetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeCurrentAudioReference, 
                                     (OMX_PTR)&sTimeStamp);   //Write Access.
        OMX_CONF_BAIL_ON_ERROR(eError);

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Write access for  OMX_IndexConfigTimeCurrentVideoReference\n");
        eError = OMX_SetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeCurrentVideoReference, 
                                     (OMX_PTR)&sTimeStamp);   //Write Access.
        OMX_CONF_BAIL_ON_ERROR(eError);

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Write access for OMX_IndexConfigTimeMediaTimeRequest\n");
	sMediaTimeRequest.nPortIndex = nPortIndex;
        eError = OMX_SetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeMediaTimeRequest, 
                                     (OMX_PTR)&sMediaTimeRequest);   //Write Access.
        OMX_CONF_BAIL_ON_ERROR(eError);

        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO,
            "Verifying Write access for OMX_IndexConfigTimeClientStartTime\n");
	sTimeStamp.nPortIndex = nPortIndex;
        eError = OMX_SetConfig(pCtx->hWrappedComp, OMX_IndexConfigTimeClientStartTime, 
                                     (OMX_PTR)&sTimeStamp);   //Write Access.
        OMX_CONF_BAIL_ON_ERROR(eError);

    }    

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* Test a component for compliance with the Standard Binary Clock. */

OMX_ERRORTYPE OMX_CONF_StdBinaryClockTest_BinaryClockTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    TEST_CTXTYPE ctx;

    eError = StdComponentTest_IsRoleSupported(cComponentName, "clock.binary");
    OMX_CONF_BAIL_ON_ERROR(eError);

    memset(&ctx, 0x0, sizeof(TEST_CTXTYPE));

    eError = StdComponentTest_StdComp(cComponentName, &ctx,
            (STDCOMPTEST_COMPONENT)StdBinaryClockTest_BinaryClock);

OMX_CONF_TEST_BAIL:

    return (eError);
}

/*****************************************************************************/

/* This runs through and tests all standard components of the binary clock
   class exposed and supported by the component.
*/
OMX_ERRORTYPE OMX_CONF_StdClockTest(
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
        if (strstr(sRoles[i], "clock.binary") != NULL) {
            eError = OMX_CONF_StdBinaryClockTest_BinaryClockTest(cComponentName);
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
