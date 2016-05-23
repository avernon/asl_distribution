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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/Message.h>
#include <alljoyn/notification/NotificationService.h>

#include "NotificationDismisserSender.h"
#include "NotificationConstants.h"
#include "Transport.h"
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace nsConsts;
using namespace qcc;

NotificationDismisserSender::NotificationDismisserSender(BusAttachment* bus, String const& objectPath, QStatus& status) :
    NotificationDismisser(bus, objectPath, status)

{
    /**
     * Do not add code until the status that returned from the base class is verified.
     */
    if (status != ER_OK) {
        return;
    }

    //Add code here
    QCC_DbgPrintf(("NotificationDismisserSender()  - Got objectpath=%s", objectPath.c_str()));
}

QStatus NotificationDismisserSender::sendSignal(ajn::MsgArg const dismisserArgs[AJ_DISMISSER_NUM_PARAMS],
                                                uint16_t ttl)
{
    QCC_DbgTrace(("Notification::sendSignal() called"));

    if (m_SignalMethod == 0) {
        QCC_LogError(ER_BUS_INTERFACE_NO_SUCH_MEMBER, ("signalMethod not set. Can't send signal"));
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    uint8_t flags =  ALLJOYN_FLAG_SESSIONLESS;
    QStatus status = Signal(NULL, 0, *m_SignalMethod, dismisserArgs, AJ_DISMISSER_NUM_PARAMS, ttl, flags);

    if (status != ER_OK) {
        QCC_LogError(status, ("Could not send signal."));
        return status;
    }

    QCC_DbgPrintf(("Sent signal successfully"));
    return status;
}
