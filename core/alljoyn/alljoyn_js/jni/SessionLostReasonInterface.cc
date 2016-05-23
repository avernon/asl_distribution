/*
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
 */
#include "SessionLostReasonInterface.h"

#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_JS"

std::map<qcc::String, int32_t> _SessionLostReasonInterface::constants;

std::map<qcc::String, int32_t>& _SessionLostReasonInterface::Constants()
{
    if (constants.empty()) {
        CONSTANT("INVALID",                     0x00); /**< Invalid */
        CONSTANT("REMOTE_END_LEFT_SESSION",     0x01); /**< Remote end called LeaveSession */
        CONSTANT("REMOTE_END_CLOSED_ABRUPTLY",  0x02); /**< Remote end closed abruptly */
        CONSTANT("REMOVED_BY_BINDER",           0x03); /**< Session binder removed this endpoint by calling RemoveSessionMember */
        CONSTANT("LINK_TIMEOUT",                0x04); /**< Link was timed-out */
        CONSTANT("REASON_OTHER",                0x05); /**< Unspecified reason for session loss */
    }
    return constants;
}

_SessionLostReasonInterface::_SessionLostReasonInterface(Plugin& plugin) :
    ScriptableObject(plugin, Constants())
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}

_SessionLostReasonInterface::~_SessionLostReasonInterface()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}

