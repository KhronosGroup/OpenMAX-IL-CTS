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

/** OMX_CONF_StubbedComponent.h
 *  Definition of stubbed of component functions. Useful for tests that stub certain component functions. 
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <OMX_Types.h>
#include <OMX_Core.h>

#include <stdlib.h>

OMX_ERRORTYPE StubbedGetComponentVersion(OMX_IN  OMX_HANDLETYPE hComponent, OMX_OUT OMX_STRING cComponentName, OMX_OUT OMX_VERSIONTYPE* pComponentVersion, OMX_OUT OMX_VERSIONTYPE* pSpecVersion, OMX_OUT OMX_UUIDTYPE* pComponentUUID);
OMX_ERRORTYPE StubbedSendCommand( OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_COMMANDTYPE Cmd, OMX_IN  OMX_U32 nParam1, OMX_IN  OMX_PTR pCmdData);
OMX_ERRORTYPE StubbedGetParameter(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_INDEXTYPE nParamIndex, OMX_INOUT OMX_PTR ComponentParameterStructure);
OMX_ERRORTYPE StubbedSetParameter(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_INDEXTYPE nIndex, OMX_IN  OMX_PTR ComponentParameterStructure);
OMX_ERRORTYPE StubbedGetConfig(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_INDEXTYPE nIndex, OMX_INOUT OMX_PTR pComponentConfigStructure);
OMX_ERRORTYPE StubbedSetConfig(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_INDEXTYPE nIndex, OMX_IN  OMX_PTR pComponentConfigStructure);
OMX_ERRORTYPE StubbedGetExtensionIndex(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_STRING cParameterName, OMX_OUT OMX_INDEXTYPE* pIndexType);
OMX_ERRORTYPE StubbedGetState(OMX_IN  OMX_HANDLETYPE hComponent, OMX_OUT OMX_STATETYPE* pState);
OMX_ERRORTYPE StubbedComponentTunnelRequest(OMX_IN  OMX_HANDLETYPE hComp, OMX_IN  OMX_U32 nPort, OMX_IN  OMX_HANDLETYPE hTunneledComp, OMX_IN  OMX_U32 nTunneledPort, OMX_INOUT  OMX_TUNNELSETUPTYPE* pTunnelSetup); 
OMX_ERRORTYPE StubbedUseBuffer(OMX_IN OMX_HANDLETYPE hComponent, OMX_INOUT OMX_BUFFERHEADERTYPE** ppBufferHdr, OMX_IN OMX_U32 nPortIndex, OMX_IN OMX_PTR pAppPrivate, OMX_IN OMX_U32 nSizeBytes, OMX_IN OMX_U8* pBuffer);
OMX_ERRORTYPE StubbedAllocateBuffer(OMX_IN OMX_HANDLETYPE hComponent, OMX_INOUT OMX_BUFFERHEADERTYPE** pBuffer, OMX_IN OMX_U32 nPortIndex, OMX_IN OMX_PTR pAppPrivate, OMX_IN OMX_U32 nSizeBytes);
OMX_ERRORTYPE StubbedFreeBuffer(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_U32 nPortIndex, OMX_IN  OMX_BUFFERHEADERTYPE* pBuffer);
OMX_ERRORTYPE StubbedEmptyThisBuffer(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_BUFFERHEADERTYPE* pBuffer);
OMX_ERRORTYPE StubbedFillThisBuffer(OMX_IN  OMX_HANDLETYPE hComponent, OMX_IN  OMX_BUFFERHEADERTYPE* pBuffer);
OMX_ERRORTYPE StubbedSetCallbacks(OMX_IN  OMX_HANDLETYPE hComponent,OMX_IN  OMX_CALLBACKTYPE* pCallbacks, OMX_IN  OMX_PTR pAppData);
OMX_ERRORTYPE StubbedComponentDeInit(OMX_IN  OMX_HANDLETYPE hComponent);
OMX_ERRORTYPE StubbedComponentInit(OMX_IN  OMX_HANDLETYPE hComponent);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
