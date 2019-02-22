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

#ifndef OMX_CONF_PlatformAbstraction_h
#define OMX_CONF_PlatformAbstraction_h

#include <OMX_Types.h>
#include <OMX_Core.h>

/** OMX_OSAL_Interfaces.h
 *  Interface definitions of the OpenMax IL OS abstraction layer including memory, threading,
 *  mutex, event, time query and tracing functionality.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**********************************************************************
 * MEMORY               
 **********************************************************************/
OMX_PTR OMX_OSAL_Malloc( OMX_IN OMX_U32 size );
void OMX_OSAL_Free( OMX_IN OMX_PTR pData );

OMX_PTR OMX_OSAL_MallocBuffer(    OMX_IN OMX_U32 size,
                            OMX_BOOL bBuffersContiguous, 
                            OMX_U32 nBufferAlignment );

void OMX_OSAL_FreeBuffer( OMX_IN OMX_PTR pData,
                            OMX_BOOL bBuffersContiguous, 
                            OMX_U32 nBufferAlignment );    

/**********************************************************************
 * THREADS               
 **********************************************************************/

/** Create a thread given the thread function, a data parameter to pass 
 *  to the thread, and the thread priority (higher values=higher priority,
 *  0 = normal priority). The thread is created and executed immediately 
 *  calling the thread function with the supplied data parameter. */
OMX_ERRORTYPE OMX_OSAL_ThreadCreate( OMX_IN OMX_U32 (*pFunc)(OMX_PTR pParam), 
                                     OMX_IN OMX_PTR pParam, 
                                     OMX_IN OMX_U32 nPriority, 
                                     OMX_OUT OMX_HANDLETYPE *phThread );
OMX_ERRORTYPE OMX_OSAL_ThreadDestroy( OMX_IN OMX_HANDLETYPE hThread ); /** Destroy a thread */

/**********************************************************************
 * MUTEX               
 **********************************************************************/

OMX_ERRORTYPE OMX_OSAL_MutexCreate(OMX_OUT OMX_HANDLETYPE *phMutex); /** Create a mutex */
OMX_ERRORTYPE OMX_OSAL_MutexDestroy(OMX_IN OMX_HANDLETYPE hMutex); /** Destroy a mutex */
OMX_ERRORTYPE OMX_OSAL_MutexLock(OMX_IN OMX_HANDLETYPE hMutex); /** Lock a mutex. Block until available if neccessary.*/ 
OMX_ERRORTYPE OMX_OSAL_MutexUnlock(OMX_IN OMX_HANDLETYPE hMutex); /** Unlock a mutex */

/**********************************************************************
 * EVENTS               
 **********************************************************************/

#define INFINITE_WAIT 0xffffffff

OMX_ERRORTYPE OMX_OSAL_EventCreate(OMX_OUT OMX_HANDLETYPE *phEvent); /** Create an event */
OMX_ERRORTYPE OMX_OSAL_EventDestroy(OMX_IN OMX_HANDLETYPE hEvent);/** Destroy an event */
OMX_ERRORTYPE OMX_OSAL_EventReset(OMX_IN OMX_HANDLETYPE hEvent);/** Reset an event */
OMX_ERRORTYPE OMX_OSAL_EventSet(OMX_IN OMX_HANDLETYPE hEvent);/** Set an event */
/** Wait at most mSec milliseconds for the specified event to be set. 
 *  If mSec==INFINITE_WAIT wait indefinitely. If bTimedout is set the wait timed out before
 *  the event was signaled. */
OMX_ERRORTYPE OMX_OSAL_EventWait(OMX_IN OMX_HANDLETYPE hEvent, OMX_IN OMX_U32 mSec, OMX_OUT OMX_BOOL *pbTimedOut); 

/**********************************************************************
 * TIME
 **********************************************************************/

/** Returns a time value in milliseconds based on a clock starting at
 *  some arbitrary base. Given a call to GetTime that returns a value
 *  of n a subsequent call to GetTime made m milliseconds later should 
 *  return a value of (approximately) (n+m). This method is used, for
 *  instance, to compute the duration of call. */
OMX_U32 OMX_OSAL_GetTime();

/***********************************************************************
 * TRACE
 *
 * Examples:
 *   OMX_OSAL_Trace(OMX_OSAL_TracePASSFAIL, "StateTransitionTest FAILED!\n");
 *   OMX_OSAL_Trace(OMX_OSAL_TraceCALLSEQUENCE, "FreeBuffer(");
 *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\thComponent = 0x%08x", hComponent);
 *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\tnPortIndex = 0x%08x", nPortIndex);
 *   OMX_OSAL_Trace(OMX_OSAL_TracePARAMETERS, "\n\tpBufer = 0x%08x", pBuffer);
 *   OMX_OSAL_Trace(OMX_OSAL_TraceCALLSEQUENCE, ")\n");
 *
 ***********************************************************************/

extern OMX_HANDLETYPE g_OMX_CONF_hTraceMutex;

/** Trace flags. */
#define OMX_OSAL_TRACE_PASSFAIL       0x0001 /**< Messages indicating the success or failure of a test*/
#define OMX_OSAL_TRACE_CALLSEQUENCE   0x0002 /**< The name of each function in the call sequence */
#define OMX_OSAL_TRACE_PARAMETERS     0x0004 /**< The parameters of each function in the call sequence */
#define OMX_OSAL_TRACE_INFO           0x0008 /**< Generalized info. */
#define OMX_OSAL_TRACE_ERROR          0x0010 /**< Errors that occur during processing. */
#define OMX_OSAL_TRACE_BUFFER         0x0020 /**< Buffer header fields. */
#define OMX_OSAL_TRACE_WARNING        0x0040 /**< Warnings reported during processing. */

/** Output a trace message */
OMX_ERRORTYPE OMX_OSAL_Trace(OMX_IN OMX_U32 nTraceFlags, OMX_IN char *format, ...);

OMX_ERRORTYPE OMX_OSAL_ProcessCommandsFromFile(OMX_STRING sFileName);
OMX_ERRORTYPE OMX_OSAL_ProcessCommandsFromPrompt();

/** Open logfile. All enabled tracing will be sent to the file (in addition
 *  to the display). */
OMX_ERRORTYPE OMX_OSAL_OpenLogfile(OMX_IN OMX_STRING sFilename);
/** Close logfile.*/
OMX_ERRORTYPE OMX_OSAL_CloseLogfile();

/**********************************************************************
 * INPUT FILE MAPPING
 **********************************************************************/

/** Open the input file associated with the given port index.*/
OMX_ERRORTYPE OMX_OSAL_OpenInputFile( OMX_IN OMX_U32 nPortIndex );

/** Read the given number bytes from the input file associated with the given port index.
 *  Return the actual number of bytes read. */
OMX_U32 OMX_OSAL_ReadFromInputFile( OMX_OUT OMX_PTR pData, OMX_IN OMX_U32 nBytes, OMX_IN OMX_U32 nPortIndex );

/** Read a specified number of bytes from input file associated with the given port index. The specified number of bytes is either the maxbytes passed in, or it is the corresponding number of bytes specified in a .length file */
OMX_U32 OMX_OSAL_ReadFromInputFileWithSize( OMX_OUT OMX_PTR pData, OMX_IN OMX_U32 nMaxBytes, OMX_IN OMX_U32 nPortIndex);
 
/** Return if an input file associated with the given port index is at EOS or not. */
OMX_BOOL OMX_OSAL_InputFileAtEOS( OMX_IN OMX_U32 nPortIndex );

/** Close the input file associated with the given port index.*/
OMX_ERRORTYPE OMX_OSAL_CloseInputFile( OMX_IN OMX_U32 nPortIndex );

/**********************************************************************
 * OUTPUT FILE MAPPING
 **********************************************************************/

/** Open the output file associated with the given port index.*/
OMX_ERRORTYPE OMX_OSAL_OpenOutputFile( OMX_IN OMX_U32 nPortIndex );

/** Write the given bytes to the output file associated with the given port index.
 *  Return the actual number of bytes written. */
OMX_U32 OMX_OSAL_WriteToOutputFile( OMX_OUT OMX_PTR pData, OMX_IN OMX_U32 nBytes, OMX_IN OMX_U32 nPortIndex );

/** Close the output file associated with the given port index.*/
OMX_ERRORTYPE OMX_OSAL_CloseOutputFile( OMX_IN OMX_U32 nPortIndex );


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
