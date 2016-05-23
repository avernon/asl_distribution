/**
 * @file This file defines the class for handling the client and server
 * endpoints for the message bus wire protocol
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

#include <qcc/platform.h>
#include <qcc/GUID.h>
#include <qcc/Debug.h>
#include <qcc/Thread.h>

#include <BusEndpoint.h>

#define QCC_MODULE "ALLJOYN"

using namespace qcc;
using namespace ajn;

String _BusEndpoint::GetControllerUniqueName() const {

    /* An endpoint with unique name :X.Y has a controller with a unique name :X.1 */
    String ret = GetUniqueName();
    ret[qcc::GUID128::SHORT_SIZE + 2] = '1';
    ret.resize(qcc::GUID128::SHORT_SIZE + 3);
    return ret;
}

void _BusEndpoint::Invalidate()
{
    QCC_DbgPrintf(("Invalidating endpoint type=%d %s", endpointType, GetUniqueName().c_str()));
    isValid = false;
}

