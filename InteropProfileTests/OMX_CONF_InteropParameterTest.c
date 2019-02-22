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

/** OMX_CONF_InteropParameterTest.c
 *  OpenMax IL conformance test - Interop Parameter Port Test
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_TestHarness.h"
#include "OMX_CONF_StubbedCallbacks.h"

#include <string.h>

#define TEST_NAME_STRING "InteropParameterTest"
#define NUM_DOMAINS 0x4

#define TEST_GROUPID 0xF00DBEEF
#define TEST_GROUPPRIORITY 0xDEADC0DE


#define OMX_CONF_BAIL_ON_ERROR(_e_) \
    if (OMX_ErrorNone != (_e_))\
    {\
        goto OMX_CONF_TEST_BAIL;\
    }


#define OMX_CONF_ASSERT(_e_, _a_, _r_) \
    if (!(_a_))\
    {\
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "%s\n", (_r_));\
        (_e_) = OMX_ErrorUndefined;\
        goto OMX_CONF_TEST_BAIL;\
    }

       


/************************* T Y P E   D E F I N I T I O N S *******************/

typedef struct _TEST_CTXTYPE
{
    OMX_HANDLETYPE hComp;
    OMX_HANDLETYPE hWrappedComp;
    OMX_STATETYPE eState;
    OMX_U32 nNumPorts;
    OMX_PORT_PARAM_TYPE sPortParam[NUM_DOMAINS];
    OMX_HANDLETYPE hStateChangeEvent;
    OMX_HANDLETYPE hPortStopEvent;
    OMX_HANDLETYPE hPortReStartEvent;
    OMX_U32 nReStartPort;
    OMX_U32 nStopPort;

} TEST_CTXTYPE;


/*************************  E X T E R N A L   F U N C T I O N S   ************/

/* Reside in OMX_CONF_BaseParameterTest.c */
extern OMX_ERRORTYPE paramtest_eventhandler(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_PTR pAppData,
    OMX_IN OMX_EVENTTYPE eEvent,
    OMX_IN OMX_U32 nData1,
    OMX_IN OMX_U32 nData2,
    OMX_IN OMX_PTR pEventData);

extern OMX_ERRORTYPE paramtest_bogusparameter(
    TEST_CTXTYPE *pCtx, 
    OMX_U32 nIndex,
    OMX_PTR pData);


/**************************** G L O B A L S **********************************/






/*****************************************************************************/
OMX_ERRORTYPE OMX_CONF_InteropParameterTest(
    OMX_IN OMX_STRING cComponentName)
{
    OMX_ERRORTYPE eError = OMX_ErrorNone;
    OMX_ERRORTYPE eCleanupError = OMX_ErrorNone;
    OMX_HANDLETYPE hComp  = 0x0;
    OMX_HANDLETYPE hWrappedComp = 0x0;
    OMX_CALLBACKTYPE *pWrappedCallbacks;
    OMX_PTR pWrappedAppData;
    OMX_CALLBACKTYPE sCallbacks;
    TEST_CTXTYPE ctx;
    TEST_CTXTYPE *pCtx;
    OMX_PRIORITYMGMTTYPE sPriorityMgmt;

    pCtx = &ctx;
    memset(pCtx, 0x0, sizeof(TEST_CTXTYPE));

    /* create callback tracer */
    sCallbacks.EventHandler    = paramtest_eventhandler;
    sCallbacks.EmptyBufferDone = StubbedEmptyBufferDone;
    sCallbacks.FillBufferDone  = StubbedFillBufferDone;

    eError = OMX_CONF_CallbackTracerCreate(&sCallbacks, (OMX_PTR)pCtx, cComponentName, 
        &pWrappedCallbacks, &pWrappedAppData);
    OMX_CONF_BAIL_ON_ERROR(eError);
    
    
    /* Initialize OpenMax */
    eError = OMX_Init(); 
    if (eError != OMX_ErrorNone) {
        goto OMX_CONF_TEST_BAIL;
    }

    /* Acquire handle */
    eError = OMX_GetHandle(&hComp, cComponentName, pWrappedAppData, pWrappedCallbacks);
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = OMX_CONF_ComponentTracerCreate(hComp, cComponentName, &hWrappedComp);
    OMX_CONF_BAIL_ON_ERROR(eError);
    pCtx->hWrappedComp = hWrappedComp;

    /* Verify start in Loaded state */
    eError = OMX_GetState(pCtx->hWrappedComp, &pCtx->eState);
    OMX_CONF_BAIL_ON_ERROR(eError);
    OMX_CONF_ASSERT(eError, (OMX_StateLoaded == pCtx->eState), 
                    "Component state is not OMX_StateLoaded\n");

    /* validate priority management structure */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Inspecting OMX_IndexParamPriorityMgmt\n");
    OMX_CONF_INIT_STRUCT(sPriorityMgmt, OMX_PRIORITYMGMTTYPE);
    eError = paramtest_bogusparameter(pCtx, OMX_IndexParamPriorityMgmt, (OMX_PTR)&sPriorityMgmt);
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPriorityMgmt, (OMX_PTR)&sPriorityMgmt);
    OMX_CONF_BAIL_ON_ERROR(eError);
    sPriorityMgmt.nGroupPriority = TEST_GROUPPRIORITY;
    sPriorityMgmt.nGroupID = TEST_GROUPID;
    eError = OMX_SetParameter(pCtx->hWrappedComp, OMX_IndexParamPriorityMgmt, (OMX_PTR)&sPriorityMgmt);
    OMX_CONF_BAIL_ON_ERROR(eError);
    eError = OMX_GetParameter(pCtx->hWrappedComp, OMX_IndexParamPriorityMgmt, (OMX_PTR)&sPriorityMgmt);
    OMX_CONF_BAIL_ON_ERROR(eError);
    if ((TEST_GROUPPRIORITY != sPriorityMgmt.nGroupPriority) || 
        (TEST_GROUPID != sPriorityMgmt.nGroupID))
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_ERROR, "Unexpected priority management values!\n");
        eError = OMX_ErrorUndefined;
        goto OMX_CONF_TEST_BAIL;
    }
    
OMX_CONF_TEST_BAIL:

    if (hComp) 
    {
        if (OMX_ErrorNone == eCleanupError)
        {
            eCleanupError = OMX_FreeHandle(hComp);
            
        } else
        {
            OMX_FreeHandle(hComp);
        }    
	}

	if (hWrappedComp) 
    {
        OMX_CONF_ComponentTracerDestroy(hWrappedComp);
	}


    if (OMX_ErrorNone != eCleanupError)
    {
        OMX_Deinit();
        
    } else
    {
        eCleanupError = OMX_Deinit();    
    }   
    
    if (OMX_ErrorNone != eCleanupError)
    {
        OMX_CONF_CallbackTracerDestroy(pWrappedCallbacks, pWrappedAppData);
    } else
    {
        eCleanupError = OMX_CONF_CallbackTracerDestroy(pWrappedCallbacks, pWrappedAppData);
    }

    if (OMX_ErrorNone == eError)
    {
        /* if there were no failures during the test, report any errors found
           during cleanup */
        eError = eCleanupError;   
    }
    
    return (eError);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
