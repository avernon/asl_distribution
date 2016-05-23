/**
 * @file
 */
/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/
#ifndef AJS_STORAGE_H_
#define AJS_STORAGE_H_

#include "ajs.h"

/**
 * Open a script for reading or writing
 *
 * @param length            Length of the script (zero implies a read)
 * @param ctx[out]          Out parameter containing the context for the opened script
 * @return                  AJ_OK if opened
 *                          AJ_ERR_RESOURCES if the script was too large
 *                          AJ_ERR_FAILURE for some other failure
 */
AJ_Status AJS_OpenScript(uint32_t length, void** ctx);

/**
 * Write a portion (or all) of a script to persistant storage
 *
 * @param script            Section of script to write
 * @param length            Length of script section
 * @param ctx               Context returned from AJS_OpenScript()
 * @return                  AJ_OK if written
 */
AJ_Status AJS_WriteScript(uint8_t* script, uint32_t length, void* ctx);

/**
 * Read a script out of persistant storage
 *
 * @param[out] script       Pointer that will contain script buffer
 * @param[out] length       Pointer that will contain scripts length
 * @param ctx               Context returned from AJS_OpenScript()
 * @return                  AJ_OK if read
 */
AJ_Status AJS_ReadScript(uint8_t** script, uint32_t* length, void* ctx);

/**
 * Close a script
 *
 * @param ctx               Context of script to close
 * @return                  AJ_OK if closed
 */
AJ_Status AJS_CloseScript(void* ctx);

/**
 * Delete a script from persistant storage
 *
 * @return                  AJ_OK if deleted
 */
AJ_Status AJS_DeleteScript(void);

/**
 * Returns the maximum space to allocate for a script. The value returned is target specific
 * and depends on available resources.
 *
 * @return  The maximum permitted script length in bytes.
 */
uint32_t AJS_MaxScriptLen(void);

#endif /* AJS_STORAGE_H_ */
