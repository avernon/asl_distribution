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

#include <time.h>
#include <stdio.h>

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/notification/Notification.h>
#include "NotificationReceiverImpl.h"
#include <alljoyn/Status.h>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace ajn;
using namespace services;
using namespace qcc;

static char const* const QCC_MODULE = "ServerSample";

NotificationReceiverImpl::NotificationReceiverImpl() {
}

NotificationReceiverImpl::~NotificationReceiverImpl() {
}

void NotificationReceiverImpl::Receive(Notification const& notification) {

    QCC_LogMsg(("Received message with msgId: %d; msgType: %d; from DeviceId: %s; DeviceName: %s; AppId: %s; AppName: %s; SenderBusName: %s;",
                notification.getMessageId(), notification.getMessageType(), notification.getDeviceId(),
                notification.getDeviceName(), notification.getAppId(), notification.getAppName(),
                notification.getSenderBusName()));

    // output the message text(s)
    std::vector<NotificationText> vecMessages = notification.getText();
    for (std::vector<NotificationText>::const_iterator vecMessage_it = vecMessages.begin(); vecMessage_it != vecMessages.end(); ++vecMessage_it) {
        QCC_LogMsg(("Message[%s]: %s;", vecMessage_it->getLanguage().c_str(),
                    vecMessage_it->getText().c_str()));
    }

}

void NotificationReceiverImpl::Dismiss(const int32_t msgId, const qcc::String appId)
{
    QCC_LogMsg(("Received dismiss for msgId=%d appId=%s", msgId, appId.c_str()));
}
