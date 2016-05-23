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

#include "alljoyn/gateway/GatewayMergedAcl.h"

using namespace ajn;
using namespace gw;
using namespace std;

QStatus GatewayMergedAcl::unmarshal(Message& msg)
{
    QStatus status = ER_OK;

    //exposed services
    MsgArg* exposedServiceArgs;
    size_t numExposedServiceArgs;
    const ajn::MsgArg* returnArgs = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, returnArgs);

    if (numArgs == 0) {
        return ER_BUS_UNEXPECTED_SIGNATURE;
    }

    status = msg->GetArg(0)->Get("a(obas)", &numExposedServiceArgs, &exposedServiceArgs);
    if (ER_OK != status) {
        return status;
    }
    status = unmarshalObjectDescriptions(exposedServiceArgs, numExposedServiceArgs, m_ExposedServices);
    if (ER_OK != status) {
        return status;
    }

    //remoted apps
    MsgArg* remotedAppArgs;
    size_t numRemotedAppArgs;
    status = msg->GetArg(1)->Get("a(saya(obas))", &numRemotedAppArgs, &remotedAppArgs);
    if (ER_OK != status) {
        return status;
    }
    for (size_t i = 0; i < numRemotedAppArgs; i++) {
        char* deviceIdArg;

        uint8_t* appIdArg;
        size_t appIdArgLen;
        size_t appIdLen = UUID_LENGTH;
        MsgArg* objDescArgs;
        size_t numObjDescArgs;

        status = remotedAppArgs[i].Get("(saya(obas))", &deviceIdArg, &appIdArgLen, &appIdArg, &numObjDescArgs, &objDescArgs);
        if (status != ER_OK) {
            return status;
        }

        if (appIdArgLen < UUID_LENGTH) {
            appIdLen = appIdArgLen;
        }

        RemotedApp remotedApp;
        remotedApp.deviceId.assign(deviceIdArg);
        memcpy(remotedApp.appId, appIdArg, appIdLen);
        status = unmarshalObjectDescriptions(objDescArgs, numObjDescArgs, remotedApp.objectDescs);
        if (status != ER_OK) {
            return status;
        }
        m_RemotedApps.push_back(remotedApp);
    }

    return status;
}

QStatus GatewayMergedAcl::unmarshalObjectDescriptions(MsgArg* objDescArgs, size_t numObjDescs, std::list<ObjectDescription>& dest)
{
    QStatus status = ER_OK;

    for (size_t i = 0; i < numObjDescs; i++) {
        ObjectDescription objDesc;

        char* objArg;
        bool isPrefix;
        MsgArg* ifcArgs;
        size_t numIfcArgs;
        status = (objDescArgs)[i].Get("(obas)", &objArg, &isPrefix, &numIfcArgs, &ifcArgs);
        if (ER_OK != status) {
            return status;
        }

        objDesc.objectPath.assign(objArg);
        objDesc.isPrefix = isPrefix;

        for (size_t j = 0; j < numIfcArgs; j++) {
            char* ifcArg;
            status = ifcArgs[j].Get("s", &ifcArg);
            if (ER_OK != status) {
                return status;
            }
            objDesc.interfaces.push_back(qcc::String(ifcArg));
        }

        dest.push_back(objDesc);
    }

    return status;
}
