/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include "NotificationProducerSender.h"
#include "Transport.h"
#include "NotificationConstants.h"
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace nsConsts;

NotificationProducerSender::NotificationProducerSender(ajn::BusAttachment* bus, QStatus& status) :
    NotificationProducer(bus, status)
{

    /**
     * Do not add code until the status that returned from the base class is verified.
     */
    if (status != ER_OK) {
        return;
    }

}

NotificationProducerSender::~NotificationProducerSender()
{
}

QStatus NotificationProducerSender::Dismiss(const char* busName, ajn::SessionId sessionId, int32_t mgsId)
{
    QCC_DbgPrintf(("NotificationProducerSender::Dismiss busName:%s sessionId:%u mgsId:%d", busName, sessionId, mgsId));

    QStatus status = ER_OK;
    if (!m_InterfaceDescription) {
        return ER_FAIL;
    }
    ProxyBusObject*proxyBusObj = new ProxyBusObject(*m_BusAttachment, busName, AJ_NOTIFICATION_PRODUCER_PATH.c_str(), sessionId);
    if (!proxyBusObj) {
        return ER_FAIL;
    }
    status = proxyBusObj->AddInterface(*m_InterfaceDescription);
    if (status != ER_OK) {
        QCC_LogError(status, ("MethodCallDismiss - AddInterface."));
        delete proxyBusObj;
        proxyBusObj = NULL;
        return status;
    }
    MsgArg args[1];
    Message replyMsg(*m_BusAttachment);

    args[0].Set(AJPARAM_INT.c_str(), mgsId);
    status = proxyBusObj->MethodCall(AJ_NOTIFICATION_PRODUCER_INTERFACE.c_str(), AJ_DISMISS_METHOD_NAME.c_str(), args, 1, replyMsg);
    if (status != ER_OK) {
        QCC_LogError(status, ("MethodCallDismiss - MethodCall."));
        delete proxyBusObj;
        proxyBusObj = NULL;
        return status;
    }

    delete proxyBusObj;
    proxyBusObj = NULL;
    return status;
}
