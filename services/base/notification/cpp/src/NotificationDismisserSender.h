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

#ifndef NOTIFICATIONDISMISSERSENDER_H_
#define NOTIFICATIONDISMISSERSENDER_H_

#include <alljoyn/notification/NotificationEnums.h>
#include "NotificationDismisser.h"
#include "NotificationConstants.h"

namespace ajn {
namespace services {

/**
 * Implementing the sender side of the dismiss signal in dismisser interface
 */
class NotificationDismisserSender : public NotificationDismisser {

  public:

    /**
     * Constructor for TransportProducer. Creates Interface and prepares
     * infrastructure to be able to send Signal
     * @param bus            - BusAttachment that is used
     * @param objectPath     - Object path name of the dismisser
     * @param status         - success/failure
     */
    NotificationDismisserSender(ajn::BusAttachment* bus, qcc::String const& objectPath, QStatus& status);

    /**
     * Destructor for TransportProducer
     */
    ~NotificationDismisserSender() { };

    /**
     * Send Signal over Bus.
     * @param notificationArgs
     * @param ttl
     * @return status
     */
    QStatus sendSignal(ajn::MsgArg const dismisserArgs[nsConsts::AJ_DISMISSER_NUM_PARAMS],
                       uint16_t ttl);


};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONDISMISSERSENDER_H_ */
