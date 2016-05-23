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

#include <alljoyn/gateway/AclRules.h>
#include <alljoyn/gateway/LogModule.h>
#include "PayloadAdapter.h"

namespace ajn {
namespace gwc {

AclRules::AclRules()
{

}

QStatus AclRules::init(std::vector<RuleObjectDescription*> const& exposedServices, std::vector<RemotedApp*> const& remotedApps)
{
    m_ExposedServices = exposedServices;
    m_RemotedApps = remotedApps;

    return ER_OK;
}

QStatus AclRules::init(const MsgArg*exposedServicesArrayArg, const MsgArg*remotedAppsArrayArg, const ConnectorCapabilities& connectorCapabilities, const std::map<qcc::String, qcc::String>& internalMetadata)
{
    const ajn::MsgArg* exposedServicesArray;
    size_t exposedServicesCount;

    QStatus status = exposedServicesArrayArg->Get("a(obas)", &exposedServicesCount, &exposedServicesArray);
    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting Manifest object"));
        return status;
    }

    for (size_t i = 0; i != exposedServicesCount; i++) {

        RuleObjectDescription* exposedService = PayloadAdapter::unmarshalObjectDescriptionsWithoutNames(&exposedServicesArray[i], connectorCapabilities.getExposedServices(), status);

        if (status != ER_OK) {
            QCC_LogError(status, ("Failed unmarshalObjectDesciptionsWithoutNames"));
            return status;
        }

        m_ExposedServices.push_back(exposedService);
    }

    const ajn::MsgArg* remotedAppsArray;
    size_t remotedAppsCount;

    status = remotedAppsArrayArg->Get("a(saya(obas))", &remotedAppsCount, &remotedAppsArray);
    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting remoted app object"));
        return status;
    }

    for (size_t i = 0; i != remotedAppsCount; i++) {
        RemotedApp*remotedApp = new RemotedApp();

        QStatus status = remotedApp->init(&remotedAppsArray[i], connectorCapabilities.getRemotedServices(), internalMetadata);

        if (status != ER_OK) {
            delete remotedApp;
            return status;
        }

        m_RemotedApps.push_back(remotedApp);
    }

    return ER_OK;
}

AclRules::~AclRules()
{

}

const std::vector<RemotedApp*>&  AclRules::getRemotedApps()
{
    return m_RemotedApps;
}

const std::vector<RuleObjectDescription*>& AclRules::getExposedServices()
{
    return m_ExposedServices;
}

void AclRules::setMetadata(std::map<qcc::String, qcc::String> const& metadata)
{
    m_Metadata.insert(metadata.begin(), metadata.end());
}

qcc::String*AclRules::getMetadata(const qcc::String& key)
{
    std::map<qcc::String, qcc::String>::iterator value = m_Metadata.find(key);

    if (value != m_Metadata.end()) {
        return &value->second;
    } else {
        return NULL;
    }


}

const std::map<qcc::String, qcc::String>& AclRules::getMetadata()
{
    return m_Metadata;
}


void AclRules::emptyVectors()
{
    for (size_t indx = 0; indx < m_ExposedServices.size(); indx++) {
        QStatus status = m_ExposedServices[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_ExposedServices[indx];
    }

    m_ExposedServices.clear();


    for (size_t indx = 0; indx < m_RemotedApps.size(); indx++) {
        QStatus status = m_RemotedApps[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_RemotedApps[indx];
        m_RemotedApps[indx] = NULL;
    }

    m_RemotedApps.clear();

}

QStatus AclRules::release()
{
    emptyVectors();

    return ER_OK;
}


}
}



