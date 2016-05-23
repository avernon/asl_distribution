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

#include "ConfigServiceListenerImpl.h"
#include "AboutObjApi.h"
#include <signal.h>
#include <iostream>

using namespace ajn;
using namespace services;

extern volatile sig_atomic_t s_restart;

ConfigServiceListenerImpl::ConfigServiceListenerImpl(AboutDataStore& store, BusAttachment& bus, CommonBusListener& busListener) :
    ConfigService::Listener(), m_AboutDataStore(&store), m_Bus(&bus), m_BusListener(&busListener)
{
}

QStatus ConfigServiceListenerImpl::Restart()
{
    std::cout << "Restart has been called !!!" << std::endl;
    s_restart = true;
    return ER_OK;
}

QStatus ConfigServiceListenerImpl::FactoryReset()
{
    QStatus status = ER_OK;
    std::cout << "FactoryReset has been called!!!" << std::endl;
    m_AboutDataStore->FactoryReset();
    std::cout << "Clearing Key Store" << std::endl;
    m_Bus->ClearKeyStore();

    AboutObjApi* aboutObjApi = AboutObjApi::getInstance();
    if (aboutObjApi) {
        status = aboutObjApi->Announce();
        std::cout << "Announce for " << m_Bus->GetUniqueName().c_str() << " = " << QCC_StatusText(status) << std::endl;
    }

    return status;
}

QStatus ConfigServiceListenerImpl::SetPassphrase(const char* daemonRealm, size_t passcodeSize, const char* passcode, ajn::SessionId sessionId)
{
    qcc::String passCodeString(passcode, passcodeSize);
    std::cout << "SetPassphrase has been called daemonRealm=" << daemonRealm << " passcode="
              << passCodeString.c_str() << " passcodeLength=" << passcodeSize << std::endl;

    PersistPassword(daemonRealm, passCodeString.c_str());

    std::cout << "Clearing Key Store" << std::endl;
    m_Bus->ClearKeyStore();
    m_Bus->EnableConcurrentCallbacks();

    std::vector<SessionId> sessionIds = m_BusListener->getSessionIds();
    for (size_t i = 0; i < sessionIds.size(); i++) {
        if (sessionIds[i] == sessionId) {
            continue;
        }
        m_Bus->LeaveSession(sessionIds[i]);
        std::cout << "Leaving session with id: " << sessionIds[i];
    }
    m_AboutDataStore->write();
    return ER_OK;
}

ConfigServiceListenerImpl::~ConfigServiceListenerImpl()
{
}

void ConfigServiceListenerImpl::PersistPassword(const char* daemonRealm, const char* passcode)
{
    MsgArg argPasscode;
    MsgArg argDaemonrealm;
    argPasscode.Set("s", passcode);
    argDaemonrealm.Set("s", daemonRealm);
    m_AboutDataStore->SetField("Passcode", argPasscode);
    m_AboutDataStore->SetField("Daemonrealm", argDaemonrealm);
}
