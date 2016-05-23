/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/gateway/ConnectorAppStatus.h>
#include <alljoyn/gateway/LogModule.h>

namespace ajn {
namespace gwc {

QStatus ConnectorAppStatus::init(InstallStatus installStatus, const qcc::String& installDescription, ConnectionStatus connectionStatus, OperationalStatus operationalStatus)

{
    m_InstallStatus = (InstallStatus)installStatus;
    m_InstallDescription = installDescription;
    m_ConnectionStatus = (ConnectionStatus)connectionStatus;
    m_OperationalStatus = (OperationalStatus)operationalStatus;

    return ER_OK;
}

QStatus ConnectorAppStatus::init(const ajn::MsgArg* returnArgs)
{

    QStatus status = ER_OK;

    short installStatus;
    char*installDescription;
    short connectionStatus;
    short operationalStatus;

    status = returnArgs[0].Get("q", &installStatus);

    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting installStatus"));
        return status;
    }

    status = returnArgs[1].Get("s", &installDescription);

    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting installDescription"));
        return status;
    }
    status = returnArgs[2].Get("q", &connectionStatus);

    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting connectionStatus"));
        return status;
    }
    status = returnArgs[3].Get("q", &operationalStatus);

    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting operationalStatus"));
        return status;
    }

    m_InstallStatus = (InstallStatus)installStatus;
    m_InstallDescription = installDescription;
    m_ConnectionStatus = (ConnectionStatus)connectionStatus;
    m_OperationalStatus = (OperationalStatus)operationalStatus;

    return ER_OK;
}

ConnectorAppStatus::~ConnectorAppStatus() {
}

InstallStatus ConnectorAppStatus::getInstallStatus()
{
    return m_InstallStatus;
}

const qcc::String& ConnectorAppStatus::getInstallDescriptions()
{
    return m_InstallDescription;
}

ConnectionStatus ConnectorAppStatus::getConnectionStatus()
{
    return m_ConnectionStatus;
}

OperationalStatus ConnectorAppStatus::getOperationalStatus()
{
    return m_OperationalStatus;
}
}
}
