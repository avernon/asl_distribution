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

#include <algorithm>
#include <qcc/Debug.h>
#include <alljoyn/about/AboutService.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/AllJoynStd.h>

#define QCC_MODULE "ALLJOYN_ABOUT_SERVICE"
#define ABOUT_SERVICE_VERSION 1

using namespace ajn;
using namespace services;

static const char* ABOUT_INTERFACE_NAME = "org.alljoyn.About";

AboutService::AboutService(ajn::BusAttachment& bus, PropertyStore& store) :
    BusObject("/About"), m_BusAttachment(&bus), m_PropertyStore(&store),
    m_AnnounceSignalMember(NULL), m_AnnouncePort(0) {

    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    std::vector<qcc::String> v;
    v.push_back(ABOUT_INTERFACE_NAME);
    m_announceObjectsLock.Lock(MUTEX_CONTEXT);
    m_AnnounceObjectsMap.insert(std::pair<qcc::String, std::vector<qcc::String> >("/About", v));
    m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
}

QStatus AboutService::Register(int port) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_OK;

    m_AnnouncePort = port;
    const InterfaceDescription* p_InterfaceDescription = NULL;
    if (m_BusAttachment) {
        p_InterfaceDescription = m_BusAttachment->GetInterface(org::alljoyn::About::InterfaceName);
    }

    if (!p_InterfaceDescription) {
        return ER_BUS_CANNOT_ADD_INTERFACE;
    }
    status = AddInterface(*p_InterfaceDescription);

    if (status == ER_OK) {
        status = AddMethodHandler(p_InterfaceDescription->GetMember("GetAboutData"),
                                  static_cast<MessageReceiver::MethodHandler>(&AboutService::GetAboutData));
        if (status != ER_OK) {
            return status;
        }
        status = AddMethodHandler(p_InterfaceDescription->GetMember("GetObjectDescription"),
                                  static_cast<MessageReceiver::MethodHandler>(&AboutService::GetObjectDescription));
        if (status != ER_OK) {
            return status;
        }

        m_AnnounceSignalMember = p_InterfaceDescription->GetMember("Announce");
        assert(m_AnnounceSignalMember);
    }

    return (status == ER_BUS_IFACE_ALREADY_EXISTS) ? ER_OK : status;
}

void AboutService::Unregister() {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
}

QStatus AboutService::AddObjectDescription(qcc::String const& path, std::vector<qcc::String> const& interfaceNames) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_OK;
    m_announceObjectsLock.Lock(MUTEX_CONTEXT);
    std::map<qcc::String, std::vector<qcc::String> >::iterator it = m_AnnounceObjectsMap.find(path);
    if (it != m_AnnounceObjectsMap.end()) {
        it->second.insert(it->second.end(), interfaceNames.begin(), interfaceNames.end());
    } else {
        m_AnnounceObjectsMap.insert(std::pair<qcc::String, std::vector<qcc::String> >(path, interfaceNames));
    }
    m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
    return status;
}

QStatus AboutService::RemoveObjectDescription(qcc::String const& path, std::vector<qcc::String> const& interfaceNames) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_OK;
    m_announceObjectsLock.Lock(MUTEX_CONTEXT);
    std::map<qcc::String, std::vector<qcc::String> >::iterator it = m_AnnounceObjectsMap.find(path);
    if (it != m_AnnounceObjectsMap.end()) {
        for (std::vector<qcc::String>::const_iterator itv = interfaceNames.begin(); itv != interfaceNames.end(); ++itv) {
            std::vector<qcc::String>::iterator findIterator = std::find(it->second.begin(), it->second.end(), itv->c_str());
            if (findIterator != it->second.end()) {
                it->second.erase(findIterator);
            }
        }
        if (it->second.empty()) {
            m_AnnounceObjectsMap.erase(it);
        }
    }
    m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
    return status;
}

QStatus AboutService::Announce() {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_OK;
    if (m_AnnounceSignalMember == NULL) {
        return ER_FAIL;
    }
    MsgArg announceArgs[4];
    status = announceArgs[0].Set("q", ABOUT_SERVICE_VERSION);
    if (status != ER_OK) {
        return status;
    }
    status = announceArgs[1].Set("q", m_AnnouncePort);
    if (status != ER_OK) {
        return status;
    }

    m_announceObjectsLock.Lock(MUTEX_CONTEXT);
    std::vector<MsgArg> announceObjectsArg(m_AnnounceObjectsMap.size());
    int objIndex = 0;
    for (std::map<qcc::String, std::vector<qcc::String> >::const_iterator it = m_AnnounceObjectsMap.begin();
         it != m_AnnounceObjectsMap.end(); ++it) {

        std::vector<const char*> interfacesVector(it->second.size());
        std::vector<qcc::String>::const_iterator interfaceIt;
        int interfaceIndex = 0;

        for (interfaceIt = it->second.begin(); interfaceIt != it->second.end(); ++interfaceIt) {
            interfacesVector[interfaceIndex++] = interfaceIt->c_str();
        }

        status = announceObjectsArg[objIndex].Set("(oas)", it->first.c_str(), interfacesVector.size(), (interfacesVector.empty()) ? NULL : &interfacesVector.front());
        if (status != ER_OK) {
            m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
            return status;
        }
        objIndex++;
    }
    m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
    status = announceArgs[2].Set("a(oas)", objIndex, (announceObjectsArg.empty()) ? NULL : &announceObjectsArg.front());
    if (status != ER_OK) {
        return status;
    }
    status = m_PropertyStore->ReadAll(NULL, PropertyStore::ANNOUNCE, announceArgs[3]);
    if (status != ER_OK) {
        return status;
    }
    Message msg(*m_BusAttachment);
    uint8_t flags = ALLJOYN_FLAG_SESSIONLESS;
#if !defined(NDEBUG)
    for (int i = 0; i < 4; i++) {
        QCC_DbgPrintf(("announceArgs[%d]=%s", i, announceArgs[i].ToString().c_str()));
    }
#endif
    status = Signal(NULL, 0, *m_AnnounceSignalMember, announceArgs, 4, (unsigned char) 0, flags);

    QCC_DbgPrintf(("Sent AnnounceSignal from %s  =%d", m_BusAttachment->GetUniqueName().c_str(), status));
    return status;

}

void AboutService::GetAboutData(const ajn::InterfaceDescription::Member* member, ajn::Message& msg) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_OK;
    const ajn::MsgArg* args = 0;
    size_t numArgs = 0;
    msg->GetArgs(numArgs, args);
    if (numArgs == 1) {
        ajn::MsgArg retargs[1];
        status = m_PropertyStore->ReadAll(args[0].v_string.str, PropertyStore::READ, retargs[0]);
        QCC_DbgPrintf(("m_pPropertyStore->ReadAll(%s,PropertyStore::READ)  =%s", args[0].v_string.str, QCC_StatusText(status)));
        if (status != ER_OK) {
            if (status == ER_LANGUAGE_NOT_SUPPORTED) {
                MethodReply(msg, "org.alljoyn.Error.LanguageNotSupported", "The language specified is not supported");
                return;
            }
            MethodReply(msg, status);
            return;
        } else {
            MethodReply(msg, retargs, 1);
        }
    } else {
        MethodReply(msg, ER_INVALID_DATA);
    }
}

void AboutService::GetObjectDescription(const ajn::InterfaceDescription::Member* member, ajn::Message& msg) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    const ajn::MsgArg* args = 0;
    size_t numArgs = 0;
    msg->GetArgs(numArgs, args);
    if (numArgs == 0) {
        ajn::MsgArg retargs[1];
        m_announceObjectsLock.Lock(MUTEX_CONTEXT);
        std::vector<MsgArg> objectArg(m_AnnounceObjectsMap.size());
        int objIndex = 0;
        for (std::map<qcc::String, std::vector<qcc::String> >::const_iterator it = m_AnnounceObjectsMap.begin();
             it != m_AnnounceObjectsMap.end(); ++it) {
            const qcc::String& key = it->first;
            std::vector<const char*> interfacesVec(it->second.size());
            std::vector<qcc::String>::const_iterator interfaceIt;
            int interfaceIndex = 0;

            for (interfaceIt = it->second.begin(); interfaceIt != it->second.end(); ++interfaceIt) {
                interfacesVec[interfaceIndex++] = interfaceIt->c_str();
            }

            objectArg[objIndex].Set("(oas)", key.c_str(), interfacesVec.size(), (interfacesVec.empty()) ? NULL : &interfacesVec.front());
            objIndex++;
        }
        m_announceObjectsLock.Unlock(MUTEX_CONTEXT);
        retargs[0].Set("a(oas)", objectArg.size(), (objectArg.empty()) ? NULL : &objectArg.front());
        MethodReply(msg, retargs, 1);
    } else {
        MethodReply(msg, ER_INVALID_DATA);
    }
}

QStatus AboutService::Get(const char*ifcName, const char*propName, MsgArg& val) {
    QCC_DbgTrace(("AboutService::%s", __FUNCTION__));
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;
    if (0 == strcmp(ifcName, ABOUT_INTERFACE_NAME)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", ABOUT_SERVICE_VERSION);
        }
    }
    return status;
}
