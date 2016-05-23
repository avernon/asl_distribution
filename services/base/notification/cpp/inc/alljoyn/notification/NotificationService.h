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

#ifndef NOTIFICATIONSERVICE_H_
#define NOTIFICATIONSERVICE_H_

#include <qcc/Debug.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/notification/NotificationSender.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/about/PropertyStore.h>

namespace ajn {
namespace services {

class NotificationReceiver;

/**
 * Notification Service class. Used to initialize and shutdown the service
 */
class NotificationService {

  public:

    /**
     * Get Instance of NotificationService - singleton implementation
     * @return instance
     */
    static NotificationService* getInstance();

    /**
     * Destructor for NotificationService
     */
    ~NotificationService();

    /**
     *  Initialize Producer side via Transport. Create and
     *  return NotificationSender.
     * @param bus
     * @param store
     * @return NotificationSender instance
     */

    NotificationSender* initSend(ajn::BusAttachment* bus, ajn::AboutData* store);

    /**
     *  Initialize Producer side via Transport. Create and
     *  return NotificationSender.
     * @param bus
     * @param store
     *
     * @deprecated see initSend(ajn::BusAttachment*, ajn::AboutData*)
     *
     * @return NotificationSender instance
     */
    QCC_DEPRECATED(NotificationSender* initSend(ajn::BusAttachment* bus, ajn::services::PropertyStore* store));

    /**
     * Initialize Consumer side via Transport.
     * Set NotificationReceiver to given receiver
     * @param bus
     * @param notificationReceiver
     * @return status
     */
    QStatus initReceive(ajn::BusAttachment* bus, NotificationReceiver* notificationReceiver);

    /**
     * Stops sender but leaves bus and other objects alive
     */
    void shutdownSender();

    /**
     * Stops receiving but leaves bus and other objects alive
     */
    void shutdownReceiver();

    /**
     * Cleanup and get ready for shutdown
     */
    void shutdown();

    /**
     * @deprecated May 2015 for 15.04 release.
     * Disabling superagent mode.
     * Needs to be called before starting receiver
     * @return ER_OK
     */
    QCC_DEPRECATED(QStatus disableSuperAgent() {return ER_OK; });

    /**
     * Virtual method to get the busAttachment used in the service.
     */
    ajn::BusAttachment* getBusAttachment();

    /**
     * Get the Version of the NotificationService
     * @return the NotificationService version
     */
    static uint16_t getVersion();

  private:

    /**
     * Default constructor for NotificationServiceImpl
     * Private to allow for singleton implementation
     */
    NotificationService();

    /**
     * Version of the API
     */
    static uint16_t const NOTIFICATION_SERVICE_VERSION;

    /**
     * instance variable - NotificationServiceImpl is a singleton
     */
    static NotificationService* s_Instance;
};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONSERVICE_H_ */
