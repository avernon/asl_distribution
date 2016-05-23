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

#ifndef GATEWAYAPPIDDEVICEIDKEY_H_
#define GATEWAYAPPIDDEVICEIDKEY_H_

#include <qcc/String.h>

namespace ajn {
namespace gw {

#define APPID_LENGTH 16

/**
 * Class used to define a key combining appId and DeviceId
 */
class GatewayAppIdentifier {
  public:

    /**
     * Constructor for GatewayAppIdentifier
     * @param appId as a qcc::String
     * @param deviceId
     */
    GatewayAppIdentifier(qcc::String const& appId, qcc::String const& deviceId);

    /**
     * Constructor for GatewayAppIdentifier
     * @param appId as array of uint8_t
     * @param appIdLen len of array
     * @param deviceId
     */
    GatewayAppIdentifier(uint8_t* appId, size_t appIdLen, qcc::String const& deviceId);

    /**
     * Destructor for GatewayAppIdentifier
     */
    virtual ~GatewayAppIdentifier();

    /**
     * operator < used for key comparisons
     * @param other
     * @return boolean smaller or not
     */
    bool operator<(const GatewayAppIdentifier& other) const;

    /**
     * operator == used for map finds
     * @param other
     * @return boolean equal or not
     */
    bool operator==(const GatewayAppIdentifier& other) const;

    /**
     * get the AppId as string
     * @return appID
     */
    const qcc::String& getAppId() const;

    /**
     * get the AppIdHex
     * @return appID
     */
    const uint8_t* getAppIdHex() const;

    /**
     * Get the length of the AppId hex value
     * @return appIdHexLength
     */
    size_t getAppIdHexLength() const;

    /**
     * get the DeviceId
     * @return DeviceId
     */
    const qcc::String& getDeviceId() const;

  private:

    /**
     * the AppId of the Key
     */
    qcc::String m_AppId;

    /**
     * The AppId in Hex form of the Key
     */
    uint8_t m_AppIdHex[APPID_LENGTH];

    /**
     * The DeviceId of the Key
     */
    qcc::String m_DeviceId;

};

} /* namespace gw */
} /* namespace ajn */

#endif /* GATEWAYAPPIDDEVICEIDKEY_H_ */
