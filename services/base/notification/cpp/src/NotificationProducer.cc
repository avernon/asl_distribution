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

#include "NotificationProducer.h"
#include <alljoyn/BusAttachment.h>
#include <qcc/Debug.h>
#include "NotificationConstants.h"
#include <alljoyn/notification/NotificationService.h>
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace qcc;
using namespace nsConsts;

NotificationProducer::NotificationProducer(ajn::BusAttachment* bus, QStatus& status) :
    BusObject(AJ_NOTIFICATION_PRODUCER_PATH.c_str()), m_InterfaceDescription(NULL), m_BusAttachment(bus)
{
    m_InterfaceDescription = const_cast<InterfaceDescription*>(m_BusAttachment->GetInterface(AJ_NOTIFICATION_PRODUCER_INTERFACE.c_str()));
    if (!m_InterfaceDescription) {
        status = m_BusAttachment->CreateInterface(nsConsts::AJ_NOTIFICATION_PRODUCER_INTERFACE.c_str(), m_InterfaceDescription, false);
        if (status != ER_OK) {
            QCC_LogError(status, ("CreateInterface failed"));
            return;
        }

        if (!m_InterfaceDescription) {
            status = ER_FAIL;
            QCC_LogError(status, ("m_InterfaceDescription is NULL"));
            return;
        }

        status = m_InterfaceDescription->AddMethod(AJ_DISMISS_METHOD_NAME.c_str(), AJ_DISMISS_METHOD_PARAMS.c_str(), NULL, AJ_DISMISS_METHOD_PARAMS_NAMES.c_str());
        if (status != ER_OK) {
            QCC_LogError(status, ("AddMethod failed."));
            return;
        }

        status = m_InterfaceDescription->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), (uint8_t) PROP_ACCESS_READ);
        if (status != ER_OK) {
            QCC_LogError(status, ("AddMethod failed."));
            return;
        }

        m_InterfaceDescription->Activate();
    }

    status = AddInterface(*m_InterfaceDescription, ANNOUNCED);
    if (status != ER_OK) {
        QCC_LogError(status, ("AddInterface failed."));
        return;
    }

}

NotificationProducer::~NotificationProducer()
{

}

QStatus NotificationProducer::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    QCC_UNUSED(ifcName);
    QCC_DbgTrace(("Get property was called."));

    if (0 != strcmp(AJ_PROPERTY_VERSION.c_str(), propName)) {
        QCC_LogError(ER_BUS_NO_SUCH_PROPERTY, ("Called for property different than version."));
        return ER_BUS_NO_SUCH_PROPERTY;
    }

    val.typeId = ALLJOYN_UINT16;
    val.v_uint16 = NOTIFICATION_PRODUCER_VERSION;
    return ER_OK;
}

QStatus NotificationProducer::Set(const char* ifcName, const char* propName, MsgArg& val)
{
    QCC_UNUSED(ifcName);
    QCC_UNUSED(propName);
    QCC_UNUSED(val);
    return ER_ALLJOYN_ACCESS_PERMISSION_ERROR;
}
