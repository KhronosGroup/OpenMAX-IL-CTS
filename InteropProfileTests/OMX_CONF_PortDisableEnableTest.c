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

/** OMX_CONF_PortDisableEnableTest.c
 *  OpenMax IL conformance test validating a component's port disable and enable functionality.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "OMX_OSAL_Interfaces.h"
#include "OMX_CONF_TestHarness.h"
#include "OMX_CONF_StubbedCallbacks.h"
#include "OMX_CONF_TunnelTestComponent.h"

/* callback data */
typedef struct PDETDATATYPE {
    OMX_STATETYPE eState;
    OMX_HANDLETYPE hStateChangeEvent;
    OMX_HANDLETYPE hEOSEvent;
    OMX_HANDLETYPE hDisableEvent;
    OMX_HANDLETYPE hEnableEvent;
    OMX_HANDLETYPE hCUT;
    OMX_U32 nEnabledPort;
    OMX_U32 nDisabledPort;
} PDETDATATYPE;

/* Port Disable Enable Test's implementation of OMX_CALLBACKTYPE.EventHandler */
OMX_ERRORTYPE PDETEventHandler(
        OMX_IN OMX_HANDLETYPE hComponent,
        OMX_IN OMX_PTR pAppData,
        OMX_IN OMX_EVENTTYPE eEvent,
        OMX_IN OMX_U32 nData1,
        OMX_IN OMX_U32 nData2,
        OMX_IN OMX_PTR pEventData)
{
    PDETDATATYPE* pContext = pAppData;

    UNUSED_PARAMETER(pEventData);

    if (hComponent != pContext->hCUT){
        return OMX_ErrorNone;
    }

    if (eEvent == OMX_EventCmdComplete){
        switch ((OMX_COMMANDTYPE)(nData1)){
        case OMX_CommandStateSet:
            pContext->eState = (OMX_STATETYPE)(nData2);
            OMX_OSAL_EventSet(pContext->hStateChangeEvent);
            break;
        case OMX_CommandPortDisable:
            if (pContext->nDisabledPort == nData2) OMX_OSAL_EventSet(pContext->hDisableEvent);
            break;
        case OMX_CommandPortEnable:
            if (pContext->nEnabledPort == nData2) OMX_OSAL_EventSet(pContext->hEnableEvent);
            break;
        case OMX_EventBufferFlag:
            OMX_OSAL_EventSet(pContext->hEOSEvent);
            break;
        default:
            break;
        } 
    }

    return OMX_ErrorNone;
}

/* Wait for the Component Under Test to change to state and confirm it is the one we expect */
OMX_ERRORTYPE PDETWaitForState(PDETDATATYPE *pAppData, OMX_STATETYPE eState)
{
    OMX_BOOL bTimedOut = OMX_FALSE;

    OMX_OSAL_EventWait(pAppData->hStateChangeEvent, OMX_CONF_TIMEOUT_EXPECTING_SUCCESS, &bTimedOut);
    if ( bTimedOut )
    {
        OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Timeout transitioning component state.  Proceeding with Test.\n");
    }   
    else if ( pAppData->eState != eState)
    {
        return OMX_ErrorUndefined;
    }
    return OMX_ErrorNone;
}

/* disable all ports on the component under test for a given domain */
OMX_ERRORTYPE PDETDisableCUTPorts(OMX_HANDLETYPE hComp, OMX_HANDLETYPE hTTComp, PDETDATATYPE *pAppData, OMX_INDEXTYPE iIndex)
{
    OMX_PORT_PARAM_TYPE oParam;
    OMX_U32 i;
    OMX_U32 iCUTPort;
    OMX_ERRORTYPE eError;
    OMX_BOOL bTimedOut = OMX_FALSE;

    INIT_PARAM(oParam);

    /* query # of ports */
    if ( OMX_ErrorNone != ( eError = OMX_GetParameter(hComp, iIndex, &oParam))){
        return eError;
    }
    
    /* if no ports then return */
    if (!oParam.nPorts) return OMX_ErrorNone;

    /* disable each discovered port */
    for (i=0;i<oParam.nPorts;i++)
    {        
        OMX_OSAL_EventReset(pAppData->hDisableEvent);
        iCUTPort = oParam.nStartPortNumber + i;
        pAppData->nDisabledPort = iCUTPort;
        if ( OMX_ErrorNone != ( eError = OMX_SendCommand(hComp, OMX_CommandPortDisable, iCUTPort, 0))){
            return eError;
        }
        /* Technically, this should disable the TTC ports as well, but the TTC
           does not have port disable implemented.  FIXME for later. */
        TTCReleaseBuffers(hTTComp);
        OMX_OSAL_EventWait(pAppData->hDisableEvent, OMX_CONF_TIMEOUT_EXPECTING_SUCCESS, &bTimedOut);
        if (bTimedOut) break;
    }

    return bTimedOut?OMX_ErrorUndefined:OMX_ErrorNone;
}

/* enable all ports on the component under test for a given domain */
OMX_ERRORTYPE PDETEnableCUTPorts(OMX_HANDLETYPE hComp, PDETDATATYPE *pAppData, OMX_INDEXTYPE iIndex)
{
    OMX_PORT_PARAM_TYPE oParam;
    OMX_U32 i;
    OMX_U32 iCUTPort;
    OMX_ERRORTYPE eError;
    OMX_BOOL bTimedOut = OMX_FALSE;

    INIT_PARAM(oParam);

    /* query # of ports */
    if ( OMX_ErrorNone != ( eError = OMX_GetParameter(hComp, iIndex, &oParam))){
        return eError;
    }

    /* if no ports then return */
    if (!oParam.nPorts) return OMX_ErrorNone;

    OMX_OSAL_EventReset(pAppData->hEnableEvent);
    pAppData->nEnabledPort = oParam.nStartPortNumber + (oParam.nPorts - 1);

    /* enable each discovered port */
    for (i=0;i<oParam.nPorts;i++)
    {        
        iCUTPort = oParam.nStartPortNumber + i;
        if ( OMX_ErrorNone != ( eError = OMX_SendCommand(hComp, OMX_CommandPortEnable, iCUTPort, 0))){
            return eError;
        }
        OMX_OSAL_EventWait(pAppData->hEnableEvent, OMX_CONF_TIMEOUT_EXPECTING_SUCCESS, &bTimedOut);
    }

    return bTimedOut?OMX_ErrorUndefined:OMX_ErrorNone;
}

OMX_ERRORTYPE PDETDisableReenable(OMX_HANDLETYPE *phWrappedTTComp, PDETDATATYPE *pWrappedAppData,
                                  OMX_CALLBACKTYPE *pWrappedCallbacks, OMX_HANDLETYPE *phTTComp, 
                                  OMX_HANDLETYPE hWrappedComp, PDETDATATYPE *pAppData)
{
    OMX_ERRORTYPE eError;

    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Transitioning both components to executing.\n");

    /* transition CUT to idle */
    OMX_OSAL_EventReset(pAppData->hStateChangeEvent);
    if (OMX_ErrorNone != (eError = OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;

    /* transition TTC to idle */
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;

    /* transition CUT to executing */
    if (OMX_ErrorNone != (eError = PDETWaitForState(pAppData, OMX_StateIdle))) return eError;
    OMX_OSAL_EventReset(pAppData->hStateChangeEvent);
    if (OMX_ErrorNone != (eError = OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateExecuting, 0))) return eError;
    if (OMX_ErrorNone != (eError = PDETWaitForState(pAppData, OMX_StateExecuting))) return eError;

    /* transition TTC to executing  */
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateExecuting, 0))) return eError;

    if (OMX_ErrorNone != (eError = OMX_CONF_WaitForBufferTraffic(*phTTComp))) return eError;   

    /* disable ports in each domain */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Disabling all ports.\n");
    if (OMX_ErrorNone != (eError = PDETDisableCUTPorts(hWrappedComp, *phTTComp, pAppData, OMX_IndexParamAudioInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETDisableCUTPorts(hWrappedComp, *phTTComp, pAppData, OMX_IndexParamVideoInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETDisableCUTPorts(hWrappedComp, *phTTComp, pAppData, OMX_IndexParamImageInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETDisableCUTPorts(hWrappedComp, *phTTComp, pAppData, OMX_IndexParamOtherInit)))return eError;

    /* transition TTC to idle then to loaded, then destroy it */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Transitioning TTC to idle then to loaded, then destroying it.\n");
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateLoaded, 0))) return eError;
    if (OMX_ErrorNone != (eError = OMX_CONF_FreeTunnelTestComponentHandle(*phTTComp))) return eError;
    if (OMX_ErrorNone != (eError = OMX_CONF_ComponentTracerDestroy(*phWrappedTTComp))) return eError;

    /* CREATE ANOTHER TTC */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Creating another TTC.\n");

    /* Acquire tunnel test component handle */
    if (OMX_ErrorNone != (eError = OMX_CONF_GetTunnelTestComponentHandle(phTTComp, pWrappedAppData, pWrappedCallbacks))) return eError; 
    if (OMX_ErrorNone != (eError = OMX_CONF_ComponentTracerCreate( *phTTComp, "OMX.CONF.tunnel.test", phWrappedTTComp))) return eError;

    /* Connect CUT to TTC */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Connecting all ports.\n");
    if (OMX_ErrorNone != (eError = OMX_CONF_TTCConnectAllPorts(*phWrappedTTComp, hWrappedComp))) return eError;

    /* transition TTC to idle */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Transitioning TTC to idle.\n");
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;

    /* transition TTC to executing */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Transitioning TTC to executing.\n");
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateExecuting, 0))) return eError;

    /* re-enable ports in each domain */
    OMX_OSAL_Trace(OMX_OSAL_TRACE_INFO, "Re-enabling all ports.\n");
    if (OMX_ErrorNone != (eError = PDETEnableCUTPorts(hWrappedComp, pAppData, OMX_IndexParamAudioInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETEnableCUTPorts(hWrappedComp, pAppData, OMX_IndexParamVideoInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETEnableCUTPorts(hWrappedComp, pAppData, OMX_IndexParamImageInit)))return eError;
    if (OMX_ErrorNone != (eError = PDETEnableCUTPorts(hWrappedComp, pAppData, OMX_IndexParamOtherInit)))return eError;

    if (OMX_ErrorNone != (eError = OMX_CONF_WaitForBufferTraffic(*phTTComp))) return eError;

    /* transition CUT to idle */
    OMX_OSAL_EventReset(pAppData->hStateChangeEvent);
    if (OMX_ErrorNone != (eError = OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;

    /* transition TTC to idle */
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0))) return eError;

    TTCReleaseBuffers(*phTTComp);
    if (OMX_ErrorNone != (eError = PDETWaitForState(pAppData, OMX_StateIdle))) return eError;

    /* transition CUT to loaded */
    OMX_OSAL_EventReset(pAppData->hStateChangeEvent);
    if (OMX_ErrorNone != (eError = OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateLoaded, 0))) return eError;

    /* transition TTC to loaded */
    if (OMX_ErrorNone != (eError = OMX_SendCommand(*phWrappedTTComp, OMX_CommandStateSet, OMX_StateLoaded, 0))) return eError;

    if (OMX_ErrorNone != (eError = PDETWaitForState(pAppData, OMX_StateLoaded))) return eError;

    return eError;
}

/* Main entrypoint into the Port Disable Enable Test */
OMX_ERRORTYPE OMX_CONF_PortDisableEnableTest(OMX_IN OMX_STRING cComponentName)
{
    OMX_PTR pWrappedAppData;
    OMX_CALLBACKTYPE *pWrappedCallbacks;
    OMX_HANDLETYPE hComp, hWrappedComp, hTTComp, hWrappedTTComp;
    OMX_ERRORTYPE  eTemp, eError = OMX_ErrorNone;
    OMX_CALLBACKTYPE oCallbacks;
    PDETDATATYPE oAppData;

    /* create state change event */
    OMX_OSAL_EventCreate(&oAppData.hStateChangeEvent);
    OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
    OMX_OSAL_EventCreate(&oAppData.hEOSEvent);
    OMX_OSAL_EventReset(oAppData.hEOSEvent);
    OMX_OSAL_EventCreate(&oAppData.hDisableEvent);
    OMX_OSAL_EventReset(oAppData.hDisableEvent);
    OMX_OSAL_EventCreate(&oAppData.hEnableEvent);
    OMX_OSAL_EventReset(oAppData.hEnableEvent);

    oAppData.nEnabledPort = 0xffffffff;
    oAppData.nDisabledPort = 0xffffffff;

    /* init component handles */
    hComp = hWrappedComp = hTTComp = hWrappedTTComp = 0;

    oCallbacks.EventHandler    = PDETEventHandler;
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
    
    OMX_CONF_FAIL_IF_ERROR(PDETDisableReenable(&hWrappedTTComp, pWrappedAppData, 
        pWrappedCallbacks, &hTTComp, hWrappedComp, &oAppData));


OMX_CONF_TEST_FAIL:
    
    /* Cleanup: Return function errors rather than closing errors if appropriate */

    /* transition CUT and TTC to Loaded state */
    if (eError != OMX_ErrorNone){
        if (hWrappedComp) {
            OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
            OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateIdle, 0));
        }
        if (hWrappedTTComp) {
            OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateIdle, 0));
            TTCReleaseBuffers(hTTComp);
        }
        if (hWrappedComp) {
            OMX_CONF_REMEMBER_ERROR(PDETWaitForState(&oAppData, OMX_StateIdle));
            OMX_OSAL_EventReset(oAppData.hStateChangeEvent);
            OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedComp, OMX_CommandStateSet, OMX_StateLoaded, 0));
            OMX_CONF_REMEMBER_ERROR(PDETWaitForState(&oAppData, OMX_StateLoaded));
        }
        if (hWrappedTTComp) {
            OMX_CONF_REMEMBER_ERROR(OMX_SendCommand(hWrappedTTComp, OMX_CommandStateSet, OMX_StateLoaded, 0));
        }
    }

    /* destroy state change event */
    OMX_OSAL_EventDestroy(oAppData.hStateChangeEvent);
    OMX_OSAL_EventDestroy(oAppData.hEOSEvent);
    OMX_OSAL_EventDestroy(oAppData.hDisableEvent);
    OMX_OSAL_EventDestroy(oAppData.hEnableEvent);

    if(hComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_FreeHandle(hComp));
    }

    if (hTTComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_CONF_FreeTunnelTestComponentHandle(hTTComp));
    }

    if (hWrappedComp) {
        OMX_CONF_REMEMBER_ERROR(OMX_CONF_ComponentTracerDestroy(hWrappedComp));
    }

    if (hWrappedTTComp) {
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
