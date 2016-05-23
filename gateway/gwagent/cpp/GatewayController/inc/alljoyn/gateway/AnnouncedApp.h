/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef AnnouncedApp_H
#define AnnouncedApp_H

#include <map>
#include <qcc/String.h>
#include <alljoyn/about/AboutClient.h>

#define UUID_LENGTH  16

namespace ajn {
namespace gwc {

class AnnouncedApp {
  public:

    AnnouncedApp() { }

    /**
     * init
     * @param busName The name of the {@link BusAttachment} of the device that sent the Announcement
     * @param appName The name of the application
     * @param appId The application id
     * @param appIdLength The application id length
     * @param deviceName The name of the device
     * @param deviceId The device id
     * @return {@link QStatus}
     */
    QStatus init(const qcc::String& busName, const qcc::String& appName, const uint8_t*appId, uint32_t appIdLength, const qcc::String& deviceName, const qcc::String& deviceId);

    /**
     * init
     * @param busName The name of the {@link BusAttachment} of the device that sent the Announcement
     * @param aboutData The data sent with the Announcement
     * @return {@link QStatus}
     */
    QStatus init(const qcc::String& busName, ajn::services::AboutClient::AboutData const& aboutData);

    /**
     * Destructor
     */
    virtual ~AnnouncedApp();

    /**
     * @return The bus name
     */
    const qcc::String& getBusName() const;

    /**
     * @return The name of the application that sent the announcement
     */
    const qcc::String& getAppName() const;

    /**
     * @return Id of the application that sent the announcement
     */
    const uint8_t*getAppId() const;


    /**
     * @return Length of Id of the application that sent the announcement
     */
    uint32_t getAppIdLength() const;

    /**
     * @return The name of the device that the application belongs to
     */
    const qcc::String& getDeviceName() const;

    /**
     * @return The id of the device that the application belongs to
     */
    const qcc::String& getDeviceId() const;

    /**
     * set bus name
     */

    void setBusName(const qcc::String& busName);

    /**
     * set bus name
     */
    void setAppName(const qcc::String& appName);

    /**
     * set app Id
     * @return {@link QStatus}
     */
    QStatus setAppId(const uint8_t*appId, size_t len);

    /**
     * set device name
     */
    void setDeviceName(const qcc::String& deviceName);

    /**
     * set device Id
     */
    void setDeviceId(const qcc::String& deviceId);


  private:
    /**
     * Create an entry. If information is missing from the aboutData map an empty string is entered instead
     */
    qcc::String getAboutDataEntry(ajn::services::AboutClient::AboutData const& aboutData, const qcc::String& key);

    /**
     * The unique name of the {@link BusAttachment} that sent the Announcement signal
     */
    qcc::String m_BusName;

    /**
     * The name of the application that sent the announcement
     */

    qcc::String m_AppName;

    /**
     * length of the appID. maximum is UUID_LENGTH
     */
    uint32_t m_AppIdLength;

    /**
     * The Id of the application that sent the announcement
     */
    uint8_t m_AppId[UUID_LENGTH];

    /**
     * The name of the device that the application belongs to
     */
    qcc::String m_DeviceName;

    /**
     * The id of the device that the application belongs to
     */
    qcc::String m_DeviceId;
};
}
}
#endif /* defined(AnnouncedApp_H) */
