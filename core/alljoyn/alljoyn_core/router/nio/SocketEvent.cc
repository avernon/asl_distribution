/*
 * SocketEvent.cc
 *
 *  Created on: Jun 8, 2015
 *      Author: erongo
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
#include "SocketEvent.h"

using namespace nio;

SocketEvent::SocketEvent(qcc::SocketFd fd, SocketCallback cb) :
    fd(fd), cb(cb), status(ER_OK)
{

}

SocketEvent::~SocketEvent()
{
}

void SocketEvent::ExecuteInternal()
{
    cb(fd, status);
}

qcc::SocketFd SocketEvent::GetSocket() const
{
    return fd;
}

void SocketEvent::SetStatus(QStatus status)
{
    this->status = status;
}
