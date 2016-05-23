/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef _ABOUTSAMPLE_H_
#define _ABOUTSAMPLE_H_

/** @defgroup About Sample
 *
 *  @{
 */

#include <alljoyn.h>

#define AJ_ABOUT_SERVICE_PORT 900

/*
 * About Sample API
 */
/**
 * init
 * @param announceObjects
 * @return status
 */
AJ_Status About_Init(AJ_Object* announceObjects, const char* aboutIconMimetype, const uint8_t* aboutIconContent, const size_t aboutIconContentSize, const char* aboutIconUrl);

/**
 * called while no messages to process
 * @param busAttachment
 */
void About_DoWork(AJ_BusAttachment* busAttachment);

/**
 * handling finish service
 * @return status
 */
AJ_Status About_Finish();

/** @} */
 #endif // _ABOUTSAMPLE_H_
