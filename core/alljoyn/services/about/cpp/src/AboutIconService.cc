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

#include <qcc/Debug.h>
#include <alljoyn/about/AboutIconService.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>

#define QCC_MODULE "ALLJOYN_ABOUT_ICON_SERVICE"

using namespace ajn;
using namespace services;

static const char* ABOUT_ICON_INTERFACE_NAME = "org.alljoyn.Icon";

AboutIconService::AboutIconService(ajn::BusAttachment& bus, qcc::String const& mimetype, qcc::String const& url,
                                   uint8_t* content, size_t contentSize) :
    BusObject("/About/DeviceIcon"),  m_BusAttachment(&bus), m_MimeType(mimetype), m_Url(url),
    m_Content(content), m_ContentSize(contentSize) {
    QCC_DbgTrace(("AboutIconService::%s", __FUNCTION__));
}

QStatus AboutIconService::Register() {
    QStatus status = ER_OK;
    QCC_DbgTrace(("AboutIconService::%s", __FUNCTION__));

    const InterfaceDescription* intf = NULL;
    if (m_BusAttachment) {
        intf = m_BusAttachment->GetInterface(org::alljoyn::Icon::InterfaceName);
    }

    if (!intf) {
        return ER_BUS_CANNOT_ADD_INTERFACE;
    }

    status = AddInterface(*intf);
    if (status == ER_OK) {
        status = AddMethodHandler(intf->GetMember("GetUrl"),
                                  static_cast<MessageReceiver::MethodHandler>(&AboutIconService::GetUrl));
        if (status != ER_OK) {
            return status;
        }
        status = AddMethodHandler(intf->GetMember("GetContent"),
                                  static_cast<MessageReceiver::MethodHandler>(&AboutIconService::GetContent));
        if (status != ER_OK) {
            return status;
        }
    }
    return status;
}

void AboutIconService::GetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg) {
    QCC_DbgTrace(("AboutIconService::%s", __FUNCTION__));
    const ajn::MsgArg* args;
    size_t numArgs;
    msg->GetArgs(numArgs, args);
    if (numArgs == 0) {
        ajn::MsgArg retargs[1];
        QStatus status = retargs[0].Set("s", m_Url.c_str());
        if (status != ER_OK) {
            MethodReply(msg, status);
        } else {
            MethodReply(msg, retargs, 1);
        }
    } else {
        MethodReply(msg, ER_INVALID_DATA);
    }
}

void AboutIconService::GetContent(const ajn::InterfaceDescription::Member* member, ajn::Message& msg) {
    QCC_DbgTrace(("AboutIconService::%s", __FUNCTION__));
    const ajn::MsgArg* args;
    size_t numArgs;
    msg->GetArgs(numArgs, args);
    if (numArgs == 0) {
        ajn::MsgArg retargs[1];
        QStatus status = retargs[0].Set("ay", m_ContentSize, m_Content);
        if (status != ER_OK) {
            MethodReply(msg, status);
        } else {
            MethodReply(msg, retargs, 1);
        }
    } else {
        MethodReply(msg, ER_INVALID_DATA);
    }
}

QStatus AboutIconService::Get(const char*ifcName, const char*propName, MsgArg& val) {
    QCC_DbgTrace(("AboutIconService::%s", __FUNCTION__));
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;
    if (0 == strcmp(ifcName, ABOUT_ICON_INTERFACE_NAME)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", 1);
        } else if (0 == strcmp("MimeType", propName)) {
            status = val.Set("s", m_MimeType.c_str());
        } else if (0 == strcmp("Size", propName)) {
            status = val.Set("u", m_ContentSize);
        }
    }
    return status;
}
