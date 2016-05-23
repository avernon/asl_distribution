/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef COMMONSAMPLEUTIL_H_
#define COMMONSAMPLEUTIL_H_

#include <alljoyn/BusAttachment.h>
#include <qcc/String.h>
#include <alljoyn/about/AboutPropertyStoreImpl.h>
#include "CommonBusListener.h"

/**
 * Util class that creates a busAttachment, starts it and connects it
 */
class CommonSampleUtil {
  public:

    /**
     * static method that prepares the BusAttachment
     * @param authListener - authListener if want to run secured
     * @return the BusAttachment created. NULL if failed
     */
    static ajn::BusAttachment* prepareBusAttachment(ajn::AuthListener* authListener = 0);

    /**
     * static method preparePropertyStore
     * @param appIdHex
     * @param appName
     * @param deviceId
     * @param deviceName
     * @param defaultLanguage
     * @return the property store created. NULL if failed
     */
    static QStatus fillPropertyStore(ajn::services::AboutPropertyStoreImpl* propertyStore, qcc::String const& appIdHex,
                                     qcc::String const& appName, qcc::String const& deviceId, qcc::String const& deviceName,
                                     qcc::String const& defaultLanguage = "en");

    /**
     * static method prepareAboutService
     * @param bus
     * @param propertyStore
     * @param busListener
     * @param port
     * @return Qstatus
     */
    static QStatus prepareAboutService(ajn::BusAttachment* bus, ajn::services::AboutPropertyStoreImpl* propertyStore,
                                       CommonBusListener* busListener, uint16_t port);

    /**
     * static method aboutServiceAnnounce
     * @return Qstatus
     */
    static QStatus aboutServiceAnnounce();

    /**
     * static method aboutServiceDestory
     * @param bus
     * @param busListener
     * @param port
     */
    static void aboutServiceDestroy(ajn::BusAttachment* bus, CommonBusListener* busListener);

    /**
     * adds appropriate addMatch to Consumer application
     * @param bus
     * @return status - success/fail
     */
    static QStatus addSessionlessMatch(ajn::BusAttachment*bus);

  private:

    /**
     * EnableSecurity
     * @return success/failure
     */
    static QStatus EnableSecurity(ajn::BusAttachment* bus, ajn::AuthListener* authListener);
};

#endif /* COMMONSAMPLEUTIL_H_ */
