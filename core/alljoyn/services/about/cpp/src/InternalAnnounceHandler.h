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

#ifndef INTERNALANNOUNCEHANDLER_H_
#define INTERNALANNOUNCEHANDLER_H_

#include <map>
#include <set>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/about/AnnounceHandler.h>

#include <qcc/Mutex.h>

namespace ajn {
namespace services {

/**
 * AnnounceHandler is a helper class used by an AllJoyn IoE client application to receive AboutService signal notification.
 * The user of the class need to implement   virtual void Announce(...) function
 */

class InternalAnnounceHandler : public ajn::MessageReceiver {

    friend class AnnouncementRegistrar;
  public:
    /**
     *  map of AboutData using qcc::String as key and ajn::MsgArg as value.
     */
    typedef std::map<qcc::String, ajn::MsgArg> AboutData;

    /**
     * map of ObjectDescriptions using qcc::String as key std::vector<qcc::String>   as value, describing interfaces
     *
     */
    typedef std::map<qcc::String, std::vector<qcc::String> > ObjectDescriptions;

    /**
     * Construct an AnnounceHandler.
     */
    InternalAnnounceHandler(ajn::BusAttachment& bus);

    /**
     * Destruct AnnounceHandler
     */
    ~InternalAnnounceHandler();

    /**
     * Add the announce handler to the map of handlers
     */
    QStatus AddHandler(AnnounceHandler& handler, const char** implementsInterfaces, size_t numberInterfaces);

    /**
     * Remove the announce handler from the map of handlers
     */
    QStatus RemoveHandler(AnnounceHandler& handler, const char** implementsInterfaces, size_t numberInterfaces);

    /**
     * Remove all announce handlers from the map of handlers
     */
    void RemoveAllHandlers();
  private:
    /**
     * AnnounceHandler is a callback registered to receive AllJoyn Signal.
     * @param[in] member
     * @param[in] srcPath
     * @param[in] message
     */
    void AnnounceSignalHandler(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& message);

    bool ContainsInterface(const ObjectDescriptions& objectDescriptions, const qcc::String interface) const;

    qcc::String GetMatchRule(const std::set<qcc::String>& interfaces) const;

    /**
     * reference to the BusAttachment used by this InternalAnnounceHandler
     */
    ajn::BusAttachment& bus;
    /**
     *  pointer to InterfaceDescription::Member
     */
    const ajn::InterfaceDescription::Member* announceSignalMember;

    /**
     * the state of a single AnnounceHandler registration
     */
    struct RegisteredHandlerState {
        std::set<qcc::String> interfaces;
        std::set<qcc::String> matchingPeers;
    };

    /**
     * Map of the AnnounceHandler with the interfaces it is listening for.
     */
    typedef std::multimap<AnnounceHandler*, RegisteredHandlerState> AnnounceMap;

    /**
     * protected AnnounceHandlers
     */
    typedef qcc::ManagedObj<AnnounceHandler*> ProtectedAnnounceHandler;

    /**
     * the announceHandlerList
     */
    std::vector<ProtectedAnnounceHandler> announceHandlerList;

    /**
     * lock used to prevent deletion of announceHandlers while in a callback
     */
    qcc::Mutex announceHandlerLock;

    /*
     * Mutex that protects the announceMap
     */
    qcc::Mutex announceMapLock;

    /**
     * the announce Map contans all the handlers and all the interfaces that the
     * should be implemented if you are going to get a callback on that handler.
     */
    AnnounceMap announceMap;

    /**
     * default matchrule without any `implements` rules added to it.
     */
    qcc::String emptyMatchRule;

};

}
}

#endif /* INTERNALANNOUNCEHANDLER_H_ */
