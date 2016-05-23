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

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/AboutIconProxy.h>
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_ABOUT"

using namespace ajn;

AboutIconProxy::AboutIconProxy(ajn::BusAttachment& bus, const char* busName, SessionId sessionId) :
    ProxyBusObject(bus, busName, org::alljoyn::Icon::ObjectPath, sessionId)
{
    QCC_DbgTrace(("AboutIcontClient::%s", __FUNCTION__));
    const InterfaceDescription* p_InterfaceDescription = bus.GetInterface(org::alljoyn::Icon::InterfaceName);
    assert(p_InterfaceDescription);
    AddInterface(*p_InterfaceDescription);
}

QStatus AboutIconProxy::GetIcon(AboutIcon& icon) {
    QCC_DbgTrace(("AboutIcontClient::%s", __FUNCTION__));
    QStatus status = ER_OK;

    Message replyMsg(GetBusAttachment());
    status = MethodCall(org::alljoyn::Icon::InterfaceName, "GetContent", NULL, 0, replyMsg);
    if (status == ER_OK) {
        const ajn::MsgArg* returnArgs;
        size_t numArgs;
        replyMsg->GetArgs(numArgs, returnArgs);
        if (numArgs == 1) {
            status = icon.SetContent(returnArgs[0]);
        } else {
            status = ER_BUS_BAD_VALUE;
        }
    }

    status = MethodCall(org::alljoyn::Icon::InterfaceName, "GetUrl", NULL, 0, replyMsg);
    if (status == ER_OK) {
        const ajn::MsgArg* returnArgs;
        size_t numArgs;
        replyMsg->GetArgs(numArgs, returnArgs);
        if (numArgs == 1) {
            char* temp;
            status = returnArgs[0].Get("s", &temp);
            if (status == ER_OK) {
                icon.url.assign(temp);
            }
        } else {
            status = ER_BUS_BAD_VALUE;
        }
    }

    MsgArg iconsProperties_arg;
    status = GetAllProperties(org::alljoyn::Icon::InterfaceName, iconsProperties_arg);
    if (ER_OK == status) {
        MsgArg* iconPropertiesValues;
        size_t numValues;
        status = iconsProperties_arg.Get("a{sv}", &numValues, &iconPropertiesValues);
        if (status != ER_OK) {
            return status;
        }
        for (size_t i = 0; i < numValues; ++i) {
            if (status == ER_OK) {
                if (iconPropertiesValues[i].v_dictEntry.key->v_string.str != NULL) {
                    if (strcmp("MimeType", iconPropertiesValues[i].v_dictEntry.key->v_string.str) == 0) {
                        icon.mimetype.assign(iconPropertiesValues[i].v_dictEntry.val->v_variant.val->v_string.str);
                        continue;
                    }
                    if (strcmp("Size", iconPropertiesValues[i].v_dictEntry.key->v_string.str) == 0) {
                        icon.contentSize = iconPropertiesValues[i].v_dictEntry.val->v_variant.val->v_uint32;
                        continue;
                    }
                }
            } else {
                return status;
            }
        }
    }

    return status;
}

QStatus AboutIconProxy::GetVersion(uint16_t& version) {
    QCC_DbgTrace(("AboutIcontClient::%s", __FUNCTION__));
    QStatus status = ER_OK;

    MsgArg arg;
    status = GetProperty(org::alljoyn::Icon::InterfaceName, "Version", arg);
    if (ER_OK == status) {
        version = arg.v_variant.val->v_int16;
    }
    return status;
}
