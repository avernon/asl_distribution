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

#ifndef COMMONSAMPLEUTIL_H_
#define COMMONSAMPLEUTIL_H_

#include <alljoyn/BusAttachment.h>
#include <qcc/String.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/AboutObj.h>
#include "AboutObjApi.h"
#include "CommonBusListener.h"
#include <map>

typedef std::map<qcc::String, qcc::String> DeviceNamesType;

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
     * static method fillAboutData
     * @param aboutData
     * @param appIdHex
     * @param appName
     * @param deviceId
     * @param deviceNames
     * @param defaultLanguage
     * @return the property store created. NULL if failed
     */
    static QStatus fillAboutData(ajn::AboutData* aboutData, qcc::String const& appIdHex,
                                 qcc::String const& appName, qcc::String const& deviceId, DeviceNamesType const& deviceNames,
                                 qcc::String const& defaultLanguage = "en");

    /**
     * static method prepareAboutService
     * @param bus
     * @param aboutData
     * @param aboutObj
     * @param busListener
     * @param port
     * @return Qstatus
     */
    static QStatus prepareAboutService(ajn::BusAttachment* bus, ajn::AboutData* aboutData, ajn::AboutObj* aboutObj,
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
     */
    static void aboutServiceDestroy(ajn::BusAttachment* bus, CommonBusListener* busListener);

  private:

    /**
     * EnableSecurity
     * @param bus
     * @param authListener
     * @return success/failure
     */
    static QStatus EnableSecurity(ajn::BusAttachment* bus, ajn::AuthListener* authListener);
};

#endif /* COMMONSAMPLEUTIL_H_ */
