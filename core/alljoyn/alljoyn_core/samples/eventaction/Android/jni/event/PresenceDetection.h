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

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/SessionPortListener.h>
#include <alljoyn/SessionListener.h>
#include <alljoyn/Session.h>
#include <qcc/String.h>
#include <qcc/platform.h>
#include "../Constants.h"
#include <pthread.h>
#include <vector>

#ifndef _PRESENCE_DETECTION_H_
#define _PRESENCE_DETECTION_H_

class PresenceDetection : public ajn::BusAttachment::PingAsyncCB {
  public:
    PresenceDetection(ajn::BusAttachment* busAttachment, JavaVM* vm, jobject jobj);

    ~PresenceDetection();

    void StartPing(qcc::String bus, ajn::SessionPort p);

    void Stop();

  private:
    struct PingContext {
        qcc::String busName;
        ajn::SessionPort port;
        bool isFound;
        PingContext(qcc::String bus, ajn::SessionPort p) : busName(bus), port(p), isFound(0) { }
    };

    static void* PingThreadLoop(void* context);

    void PingCB(QStatus status, void* context);

    pthread_t mThread;
    pthread_mutex_t mLock;
    std::vector<PingContext*> mPingList;

    ajn::BusAttachment* mBusAttachment;
    JavaVM* vm;
    jobject jobj;

};


#endif /* _PRESENCE_DETECTION_H_ */
