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

#ifndef HTTPCONTROL_H_
#define HTTPCONTROL_H_

/** @defgroup HttpControl Http Control
 * details Http Control Struct and Functions that assist in Marshaling
 * HttpControl into a message.
 *  @{
 */

#include <alljoyn.h>

/**
 * HttpControl structure
 */
typedef struct {
    const char* url;         //!< The url of the Http control
    const char* (*getUrl)(); //!< Getter for the url of the Http control
} HttpControl;

/**
 * Initialize HttpControl
 */
void initializeHttpControl(HttpControl* httpControl);

/**
 * Marshal HttpControlUrl into given reply message
 */
AJ_Status marshalHttpControlUrl(HttpControl* httpControl, AJ_Message* reply, uint16_t language);

/** @} */
#endif /* HTTPCONTROL_H_ */
