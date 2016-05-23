/**
 * @file
 * File for holding global variables.
 */

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
#include <qcc/StaticGlobals.h>

#ifdef CRYPTO_CNG
#include <qcc/CngCache.h>
#endif
#include <qcc/Logger.h>
#include <qcc/String.h>
#include <qcc/Thread.h>
#include <qcc/Util.h>
#ifdef QCC_OS_GROUP_WINDOWS
#include <qcc/windows/utility.h>
#endif
#include "Crypto.h"
#include "DebugControl.h"

#define QCC_MODULE "STATICGLOBALS"

namespace qcc {

class StaticGlobals {
  public:
    static QStatus Init()
    {
#if defined(QCC_OS_GROUP_WINDOWS)
        WSADATA wsaData;
        WORD version = MAKEWORD(2, 0);
        int error = WSAStartup(version, &wsaData);
        if (error) {
            printf("WSAStartup failed with error: %d\n", error);
            return ER_OS_ERROR;
        }
#endif
        Event::Init();
        Environ::Init();
        String::Init();
        DebugControl::Init();
        LoggerSetting::Init();
        QStatus status = Thread::Init();
        if (status != ER_OK) {
            Shutdown();
            return status;
        }
        status = Crypto::Init();
        if (status != ER_OK) {
            Shutdown();
            return status;
        }
        return ER_OK;
    }

    static QStatus Shutdown()
    {
#if defined(QCC_OS_GROUP_WINDOWS)
        int error = WSACleanup();
        if (SOCKET_ERROR == error) {
            printf("WSACleanup failed with error: %d\n", WSAGetLastError());
            /*
             * Continue on to shutdown as much as possible since recovery path
             * is not clear.
             */
        }
#endif
        Crypto::Shutdown();
        Thread::Shutdown();
        LoggerSetting::Shutdown();
        DebugControl::Shutdown();
        String::Shutdown();
        Environ::Shutdown();
        Event::Shutdown();
        return ER_OK;
    }
};

QStatus Init()
{
    return StaticGlobals::Init();
}

QStatus Shutdown()
{
    return StaticGlobals::Shutdown();
}

} /* namespace qcc */
