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

#include "NotificationTransportProducer.h"
#include "NotificationConstants.h"
#include "Transport.h"
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace nsConsts;
using namespace qcc;

NotificationTransportProducer::NotificationTransportProducer(BusAttachment* bus,
                                                             String const& servicePath, QStatus& status,
                                                             qcc::String const& interfaceName, uint32_t serialNumber) :
    NotificationTransport(bus, servicePath, status, interfaceName),
    m_SerialNumber(serialNumber), m_MsgId(0)
{
}

QStatus NotificationTransportProducer::sendSignal(ajn::MsgArg const notificationArgs[AJ_NOTIFY_NUM_PARAMS],
                                                  uint16_t ttl)
{
    if (m_SignalMethod == 0) {
        QCC_LogError(ER_BUS_INTERFACE_NO_SUCH_MEMBER, ("signalMethod not set. Can't send signal"));
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    uint8_t flags =  ALLJOYN_FLAG_SESSIONLESS;

    Message msg(*Transport::getInstance()->getBusAttachment());
    m_MsgId = notificationArgs[1].v_int32; //grab message id from payload.

    QStatus status = Signal(NULL, 0, *m_SignalMethod, notificationArgs, AJ_NOTIFY_NUM_PARAMS, ttl, flags, &msg);

    if (status != ER_OK) {
        QCC_LogError(status, ("Could not send signal."));
        return status;
    }

    m_SerialNumber = msg->GetCallSerial();

    QCC_DbgPrintf(("Sent signal successfully"));
    return status;
}

QStatus NotificationTransportProducer::deleteLastMsg(NotificationMessageType messageType)
{
    QCC_UNUSED(messageType);
    if (m_SerialNumber == 0) {
        QCC_LogError(ER_BUS_INVALID_HEADER_SERIAL, ("Unable to delete the last message.  No message on this object."));
        return ER_BUS_INVALID_HEADER_SERIAL;
    }

    QStatus status = CancelSessionlessMessage(m_SerialNumber);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not delete last message."));
        return status;
    }

    m_SerialNumber = 0;
    m_MsgId = 0;

    QCC_DbgPrintf(("Deleted last message successfully"));
    return status;
}

QStatus NotificationTransportProducer::getLastMsgId(NotificationMessageType messageType, int32_t* messageId)
{
    QCC_UNUSED(messageType);
    QCC_DbgTrace(("NotificationTransportProducer::getLastMsgId()"));

    if (m_SerialNumber == 0) {
        QCC_LogError(ER_BUS_INVALID_HEADER_SERIAL, ("No message on this object."));
        return ER_BUS_INVALID_HEADER_SERIAL;
    }

    *messageId = m_MsgId;
    return ER_OK;
}


QStatus NotificationTransportProducer::deleteMsg(int32_t msgId)
{
    QCC_DbgTrace(("NotificationTransportProducer::deleteMsg()"));

    if (m_SerialNumber == 0) {
        return ER_BUS_INVALID_HEADER_SERIAL;
    }

    if (m_MsgId != msgId) {
        QCC_LogError(ER_BUS_INVALID_HEADER_SERIAL, ("Unable to delete the message. No such message id on this object."));
        return ER_BUS_INVALID_HEADER_SERIAL;
    }

    QStatus status = CancelSessionlessMessage(m_SerialNumber);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not delete last message."));
        return status;
    }

    m_SerialNumber = 0;
    m_MsgId = 0;

    QCC_DbgPrintf(("Deleted last message successfully"));
    return status;
}
