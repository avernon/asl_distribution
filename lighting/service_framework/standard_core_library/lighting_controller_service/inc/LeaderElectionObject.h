# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef LEADER_ELECTION_OBJECT_H
#define LEADER_ELECTION_OBJECT_H
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for leader election object
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

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/AboutListener.h>
#include <LSFTypes.h>
#include <Mutex.h>
#include <Alarm.h>

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/OEM_CS_Config.h>
#else
#include <OEM_CS_Config.h>
#endif

#include <Rank.h>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

class ControllerService;
/**
 * LeaderElectionObject class. \n
 * Implementing the algorithm of leader election. \n
 * Implementing the election behavior of the entity as a leader and also as a follower. \n
 */
class LeaderElectionObject : public ajn::BusObject, public Thread, public AlarmListener, public OEM_CS_NetworkCallback {
  public:
    /**
     * constructor
     */
    LeaderElectionObject(ControllerService& controller);
    /**
     * destructor
     */
    ~LeaderElectionObject();
    /**
     * On announcement callback
     */
    void OnAnnounced(ajn::SessionPort port, const char* busName, Rank rank, bool isLeader, const char* deviceId);
    /**
     * Start threads
     */
    QStatus Start(Rank& rank);
    /**
     * Stop threads
     */
    void Stop(void);
    /**
     * Join threads
     */
    void Join(void);
    /**
     * get blob reply. \n
     * Get data and metadata about lamps
     */
    void SendGetBlobReply(ajn::Message& message, LSFBlobType type, std::string blob, uint32_t checksum, uint64_t timestamp);
    /**
     * Send blob update. \n
     * Get data and metadata about lamps
     */
    QStatus SendBlobUpdate(ajn::SessionId session, LSFBlobType type, std::string blob, uint32_t checksum, uint64_t timestamp);
    /**
     * send blob update. \n
     * Send data and metadata about lamps
     */
    QStatus SendBlobUpdate(LSFBlobType type, std::string blob, uint32_t checksum, uint64_t timestamp);
    /**
     * On session member removed
     */
    void OnSessionMemberRemoved(SessionId sessionId, const char* uniqueName);
    /**
     * Run thread
     */
    void Run(void);
    /**
     * Alarm triggered callback
     */
    void AlarmTriggered(void);
    /**
     * Get my rank
     */
    Rank& GetRank(void) {
        return myRank;
    }

    void Connected(void);

    void Disconnected(void);

    uint32_t GetLeaderElectionAndStateSyncInterfaceVersion(void);

  private:

    /**
     * Clear the state of the LeaderElectionObject
     */
    void ClearState(void);

    struct Synchronization {
        volatile int32_t numWaiting;
    };

    void GetChecksumAndModificationTimestamp(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void OnGetChecksumAndModificationTimestampReply(ajn::Message& message, void* context);

    void Overthrow(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void OnOverthrowReply(ajn::Message& message, void* context);

    void GetBlob(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void OnGetBlobReply(ajn::Message& message, void* context);

    void OnBlobChanged(const ajn::InterfaceDescription::Member* member, const char* sourcePath, ajn::Message& msg);

    ControllerService& controller;
    BusAttachment& bus;

    class Handler;
    Handler* handler;

    // everything below is related to leader election
    struct ControllerEntry {
      public:
        ajn::SessionPort port;
        qcc::String busName;
        qcc::String deviceId;
        Rank rank;
        bool isLeader;
        uint64_t announcementTimestamp;

        void Clear() {
            busName = "";
            deviceId = "";
            rank = Rank();
            isLeader = false;
            port = 0;
            announcementTimestamp = 0;
        }
    };

    void OnSessionLost(SessionId sessionId);
    void OnSessionJoined(QStatus status, SessionId sessionId, void* context);

    typedef std::list<ajn::Message> OverThrowList;
    typedef std::map<Rank, ControllerEntry> ControllersMap;
    typedef std::map<Rank, std::pair<ControllerEntry, uint32_t> > SuccessfulJoinSessionReplies;
    typedef std::list<ControllerEntry> FailedJoinSessionReplies;
    typedef std::list<uint32_t> SessionLostList;
    typedef std::map<uint32_t, const char*> SessionMemberRemovedMap;
    typedef struct _CurrentLeader {
        ControllerEntry controllerDetails;
        ajn::ProxyBusObject proxyObj;

        void Clear(void) {
            controllerDetails.Clear();
            proxyObj = ProxyBusObject();
        }
    } CurrentLeader;

    Mutex currentLeaderMutex;
    CurrentLeader currentLeader;

    Mutex failedJoinSessionMutex;
    FailedJoinSessionReplies failedJoinSessions;

    Mutex sessionAlreadyJoinedRepliesMutex;
    FailedJoinSessionReplies sessionAlreadyJoinedReplies;

    Mutex successfulJoinSessionMutex;
    SuccessfulJoinSessionReplies successfulJoinSessions;

    Mutex sessionLostMutex;
    SessionLostList sessionLostList;

    Mutex sessionMemberRemovedMutex;
    SessionMemberRemovedMap sessionMemberRemoved;

    Mutex controllersMapMutex;
    ControllersMap controllersMap;

    Mutex overThrowListMutex;
    OverThrowList overThrowList;

    Rank myRank;

    Mutex connectionStateMutex;
    volatile sig_atomic_t isRunning;

    const ajn::InterfaceDescription::Member* blobChangedSignal;

    LSFSemaphore wakeSem;

    Mutex electionAlarmMutex;
    Alarm electionAlarm;

    volatile sig_atomic_t alarmTriggered;
    volatile sig_atomic_t isLeader;
    volatile sig_atomic_t startElection;
    volatile sig_atomic_t okToSetAlarm;
    volatile sig_atomic_t gotOverthrowReply;
    Mutex outGoingLeaderMutex;
    ControllerEntry outGoingLeader;
    Mutex upComingLeaderMutex;
    ControllerEntry upComingLeader;
};

OPTIONAL_NAMESPACE_CLOSE

} //lsf


#endif
