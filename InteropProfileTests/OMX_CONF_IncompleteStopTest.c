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

/** OMX_CONF_IncompleteStopTest.c
 *  OpenMax IL conformance test validating the proper behavior of a component when a stop is issued without the
 *  tunneled component returning all the buffers. 
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_TestHarness.h"
#include "OMX_CONF_StubbedCallbacks.h"
#include "OMX_CONF_TunnelTestComponent.h"

/* Callback data */
typedef struct ISTDATATYPE {
    OMX_STATETYPE eState;
    OMX_HANDLETYPE hStateChangeEvent;
    OMX_HANDLETYPE hEOSEvent;
    OMX_HANDLETYPE hCUT;
} ISTDATATYPE;

/* Incomplete Stop Component's implementation of OMX_CALLBACKTYPE.EventHandler */
OMX_ERRORTYPE ISTEventHandler(
        OMX_IN OMX_HANDLETYPE hComponent,
        OMX_IN OMX_PTR pAppData,
        OMX_IN OMX_EVENTTYPE eEvent,
        OMX_IN OMX_U32 nData1,
        OMX_IN OMX_U32 nData2,
        OMX_IN OMX_PTR pEventData)
{
    ISTDATATYPE* pContext = pAppData;

    UNUSED_PARAMETER(pEventData);

    if (hComponent != pContext->hCUT){
        return OMX_ErrorNone;
    }

    if ((eEvent == OMX_EventCmdComplete) && ((OMX_COMMANDTYPE)(nData1) == OMX_CommandStateSet)){
        pContext->eState = (OMX_STATETYPE)(nData2);
        OMX_OSAL_EventSet(pContext->hStateChangeEvent);
    }

    if (eEvent == OMX_EventBufferFlag){
        OMX_OSAL_EventSet(pContext->hEOSEvent);
    }
    return OMX_ErrorNone;
}

/* Wait for the Component Under Test to change to state and confirm it is the one we expect */
OMX_ERRORTYPE ISTWaitForState(ISTDATATYPE *pAppData, OMX_STATETYPE eState)
{
    OMX_BOOL bTimedOut = OMX_FALSE;

    OMX_OSAL_EventWait(pAppData->hStateChangeEvent, OMX_CONF_TIMEOUT_EXPECTING_SUCCESS, &bTimedOut);
    if ( bTimedOut )
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Timeout transitioning component state.  Proceeding with Test.\n");
    }
    else if ( pAppData->eState != eState )
    {
        return OMX_ErrorUndefined;
    }
    return OMX_ErrorNone;
}

/* Main entrypoint into the Incomplete Stop Test */
OMX_ERRORTYPE OMX_CONF_IncompleteStopTest(OMX_IN OMX_STRING cComponentName)
{
    OMX_PTR pWrappedAppData;
    OMX_CALLBACKTYPE *pWrappedCallbacks;
    OMX_HANDLETYPE hComp, hWrappedComp, hTTComp, hWrappedTTComp;
    OMX_ERRORTYPE  eTemp, eError = OMX_ErrorNone;
    OMX_CALLBACKTYPE oCallbacks;
    ISTDATATYPE oAppData;
    OMX_BOOL bTimedOut;
    OMX_ERRORTYPE eHoldTimedOut;
 
    /* create state change event */
    OMX_OSAL_EventCreate(&oAppData.hStateChangeEvent);
    OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
    OMX_OSAL_EventCreate(&oAppData.hEOSEvent);
    OMX_OSAL_EventReset(oAppData.hEOSEvent);

    /* init component handles */
    hComp = hWrappedComp = hTTComp = hWrappedTTComp = 0;

    oCallbacks.EventHandler    = ISTEventHandler;
    oCallbacks.EmptyBufferDone = StubbedEmptyBufferDone;
    oCallbacks.FillBufferDone  = StubbedFillBufferDone;
    eError = OMX_CONF_CallbackTracerCreate(&oCallbacks, (OMX_PTR)&oAppData, cComponentName, 
        &pWrappedCallbacks, &pWrappedAppData);
    
    /* Initialize OpenMax */
    eError = OMX_Init(); 

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Creating component under test and tunnel test component.\n");

    /* Acquire component under test handle */
    OMX_CONF_FAIL_IF_ERROR(OMX_GetHandle(&hComp, cComponentName, pWrappedAppData, pWrappedCallbacks)); 
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_ComponentTracerCreate( hComp, cComponentName, &hWrappedComp));
    oAppData.hCUT = hComp;

    /* Acquire tunnel test component handle */
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_GetTunnelTestComponentHandle(&hTTComp, pWrappedAppData, pWrappedCallbacks)); 
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_ComponentTracerCreate( hTTComp, "OMX.CONF.tunnel.test", &hWrappedTTComp));

    /* Connect CUT to TTC */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Connecting all ports.\n");
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_TTCConnectAllPorts(hWrappedTTComp, hWrappedComp));

    /* Force all CUT ports to be suppliers */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Forcing all component ports to be suppliers.\n");
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_ForceSuppliers(hWrappedComp, OMX_TRUE));
    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_ForceSuppliers(hWrappedTTComp, OMX_FALSE));

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Transitioning to executing.\n");

    /* transition CUT to idle */
    OMX_CONF_FAIL_IF_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateIdle, 0));

    /* transition TTC to idle */
    OMX_CONF_FAIL_IF_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0));

    /* transition CUT to executing */
    OMX_CONF_FAIL_IF_ERROR(ISTWaitForState(&oAppData, OMX_StateIdle));
    OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
    OMX_CONF_FAIL_IF_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateExecuting, 0));
    OMX_CONF_FAIL_IF_ERROR(ISTWaitForState(&oAppData, OMX_StateExecuting));

    /* transition TTC to executing  */
    OMX_CONF_FAIL_IF_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateExecuting, 0));

    OMX_CONF_FAIL_IF_ERROR(OMX_CONF_WaitForBufferTraffic(hTTComp));

    /* tell TTC to hold buffers */
    eHoldTimedOut = TTCHoldBuffers(hTTComp);

    /* transition CUT to back to idle */
    OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
    OMX_CONF_FAIL_IF_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateIdle, 0));

    if (eHoldTimedOut == OMX_ErrorNone)
    { 
        /* wait for change to idle - this must time out */
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Holding outstanding buffers, waiting for transition to idle.\n");
        OMX_OSAL_EventWait(oAppData.hStateChangeEvent, OMX_CONF_TIMEOUT_EXPECTING_FAILURE, &bTimedOut);
        if (!bTimedOut){
            OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "-ERROR: Transitioned to idle.\n");
            eError = OMX_ErrorUndefined;
        } else {
            OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "-OK: Didn't transitioned to idle.\n");
        }
    }

    /* tell TTC to release buffers */
    TTCReleaseBuffers(hTTComp);

    /* wait for change to idle - this must succeed */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Released outstanding buffers, waiting for transition to idle.\n");
    OMX_OSAL_EventWait(oAppData.hStateChangeEvent, OMX_CONF_TIMEOUT_EXPECTING_SUCCESS, &bTimedOut);
    if (bTimedOut || oAppData.eState != OMX_StateIdle){
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "-ERROR: Didn't transition to idle.\n");
        eError = OMX_ErrorUndefined;
    } else {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "-OK: Transitioned to idle.\n");
    }

OMX_CONF_TEST_FAIL:
    
    /* Cleanup: Return function errors rather than closing errors if appropriate */

    /* transition CUT to Loaded state */
    if (hWrappedComp) {
        OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
        OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateLoaded, 0));
    }

    /* transition TTC to Loaded state */
    if (hWrappedTTComp)
    {
        OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0));
        OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateLoaded, 0));
    }

    OMX_CONF_REMEMBER_ERROR(ISTWaitForState(&oAppData, OMX_StateLoaded));

    /* destroy state change event */
    OMX_OSAL_EventDestroy(oAppData.hStateChangeEvent);
    OMX_OSAL_EventDestroy(oAppData.hEOSEvent);

    if (hWrappedComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_CONF_ComponentTracerDestroy(hWrappedComp));
    }

    if(hComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_FreeHandle(hComp));
    }

    if (hTTComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_CONF_FreeTunnelTestComponentHandle(hTTComp));
        OMX_CONF_REMEMBER_ERROR(OMX_CONF_ComponentTracerDestroy(hWrappedTTComp));
    }

    OMX_CONF_REMEMBER_ERROR(OMX_CONF_CallbackTracerDestroy(pWrappedCallbacks, pWrappedAppData));
    OMX_CONF_REMEMBER_ERROR(OMX_Deinit());

    return eError;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
