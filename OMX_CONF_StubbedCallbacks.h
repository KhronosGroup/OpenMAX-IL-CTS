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

/** OMX_CONF_StubbedCallbacks.h
 *  Definition of stubbed of callback functions. Useful for tests that stub certain callback functions. 
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Core.h>
#include <OMX_Index.h>
#include <OMX_IndexExt.h>
#include <OMX_Image.h>
#include <OMX_ImageExt.h>
#include <OMX_Audio.h>
#include <OMX_Video.h>
#include <OMX_VideoExt.h>
#include <OMX_IVCommon.h>
#include <OMX_Other.h>

#include "OMX_OSAL_Interfaces.h"

OMX_ERRORTYPE StubbedEventHandler(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_PTR pAppData, OMX_IN OMX_EVENTTYPE eEvent, OMX_IN OMX_U32 nData1, OMX_IN OMX_U32 nData2, OMX_IN OMX_PTR pEventData);
OMX_ERRORTYPE StubbedEmptyBufferDone(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_PTR pAppData, OMX_IN OMX_BUFFERHEADERTYPE* pBuffer);
OMX_ERRORTYPE StubbedFillBufferDone(OMX_OUT OMX_HANDLETYPE hComponent, OMX_OUT OMX_PTR pAppData, OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* File EOF */
