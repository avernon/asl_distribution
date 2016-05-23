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

#include <alljoyn/notification/NotificationService.h>
#include "NotificationTransport.h"
#include "NotificationConstants.h"
#include <alljoyn/notification/LogModule.h>

using namespace ajn;
using namespace services;
using namespace nsConsts;
using namespace qcc;

NotificationTransport::NotificationTransport(ajn::BusAttachment* bus,
                                             qcc::String const& servicePath, QStatus& status, String const& interfaceName) :
    BusObject(servicePath.c_str()), m_SignalMethod(0)
{
    InterfaceDescription* intf = NULL;
    status = bus->CreateInterface(interfaceName.c_str(), intf);

    if (status == ER_OK) {
        intf->AddSignal(AJ_SIGNAL_METHOD.c_str(), AJ_NOTIFY_PARAMS.c_str(), AJ_NOTIFY_PARAM_NAMES.c_str(), 0);
        intf->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ);
        intf->Activate();
    } else if (status == ER_BUS_IFACE_ALREADY_EXISTS) {
        intf = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
        if (!intf) {
            status = ER_BUS_UNKNOWN_INTERFACE;
            QCC_LogError(status, ("Could not get interface"));
            return;
        }
    } else {
        QCC_LogError(status, ("Could not create interface"));
        return;
    }

    status = AddInterface(*intf, ANNOUNCED);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not add interface"));
        return;
    }

    // Get the signal method for future use
    m_SignalMethod = intf->GetMember(AJ_SIGNAL_METHOD.c_str());
}

NotificationTransport::~NotificationTransport()
{

}

QStatus NotificationTransport::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    QCC_UNUSED(ifcName);
    QCC_DbgTrace(("Get property was called"));

    if (0 != strcmp(AJ_PROPERTY_VERSION.c_str(), propName)) {
        QCC_LogError(ER_BUS_NO_SUCH_PROPERTY, ("Called for property different than version."));
        return ER_BUS_NO_SUCH_PROPERTY;
    }

    val.typeId = ALLJOYN_UINT16;
    val.v_uint16 = NotificationService::getVersion();
    return ER_OK;
}

QStatus NotificationTransport::Set(const char* ifcName, const char* propName, MsgArg& val)
{
    QCC_UNUSED(ifcName);
    QCC_UNUSED(propName);
    QCC_UNUSED(val);
    return ER_ALLJOYN_ACCESS_PERMISSION_ERROR;
}
