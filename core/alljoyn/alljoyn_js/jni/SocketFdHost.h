/*
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
 */
#ifndef _SOCKETFDHOST_H
#define _SOCKETFDHOST_H

#include "ScriptableObject.h"

class _SocketFdHost : public ScriptableObject {
  public:
    _SocketFdHost(Plugin& plugin, qcc::SocketFd& socketFd);
    virtual ~_SocketFdHost();
    qcc::SocketFd GetFd() { return socketFd; }

  private:
    qcc::SocketFd socketFd;

    bool getFd(NPVariant* result);

    bool close(const NPVariant* args, uint32_t argCount, NPVariant* result);
    bool shutdown(const NPVariant* args, uint32_t argCount, NPVariant* result);
    bool recv(const NPVariant* args, uint32_t argCount, NPVariant* result);
    bool send(const NPVariant* args, uint32_t argCount, NPVariant* result);
};

typedef qcc::ManagedObj<_SocketFdHost> SocketFdHost;

#endif // _SOCKETFDHOST_H
