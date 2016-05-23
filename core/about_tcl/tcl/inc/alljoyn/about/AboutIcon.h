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

#ifndef _ABOUTICONSERVICE_H_
#define _ABOUTICONSERVICE_H_

/** @defgroup AboutIcon
 *
 *  @{
 */

#include <alljoyn/services_common/Services_Common.h>

/**
 * published About Icon interfaces that will be announced
 */
extern const AJ_InterfaceDescription AJ_AboutIconInterfaces[];

#define NUM_ABOUT_ICON_OBJECTS 1

#define ABOUT_ICON_APPOBJECTS \
    { "/About/DeviceIcon",   AJ_AboutIconInterfaces },

/*
 * AboutIcon API
 */

AJ_Status AJ_AboutIcon_Start(const char* aboutIconMimetype, const uint8_t* aboutIconContent, const size_t aboutIconContentSize, const char* aboutIconUrl);

AJSVC_ServiceStatus AJ_AboutIcon_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status* msgStatus);

/** @} */

 #endif // _ABOUTICONSERVICE_H_
