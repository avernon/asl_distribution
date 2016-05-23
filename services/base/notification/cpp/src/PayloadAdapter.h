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

#ifndef PAYLOADADAPTER_H_
#define PAYLOADADAPTER_H_

#include <iostream>
#include <vector>
#include <map>
#include <alljoyn/Message.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/notification/NotificationText.h>
#include <alljoyn/notification/RichAudioUrl.h>
#include <alljoyn/notification/NotificationEnums.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/about/PropertyStore.h>

namespace ajn {
namespace services {

/**
 * PayloadAdapter - a class used to prepare the payload from variables to alljoyn message parameters
 * and unpack the alljoyn message parameters into the individual variables
 */
class PayloadAdapter {
  public:

    /**
     * Constructor of PayloadAdapter
     */
    PayloadAdapter() { };

    /**
     * Destructor of PayloadAdapter
     */
    ~PayloadAdapter() { };

    /**
     * SendPayload Marshals the Arguments to be sent
     * @param propertyStore
     * @param messageType
     * @param notificationText
     * @param customAttributes
     * @param ttl
     * @param richIconUrl
     * @param richAudioUrl
     * @param richIconObjectPath
     * @param richAudioObjectPath
     * @param controlPanelServiceObjectPath
     * @param originalSender
     * @return status - success/failure
     */
    static QStatus sendPayload(ajn::AboutData* propertyStore,
                               NotificationMessageType messageType,
                               std::vector<NotificationText> const&  notificationText,
                               std::map<qcc::String, qcc::String> const& customAttributes,
                               uint16_t ttl,
                               const char* richIconUrl, std::vector<RichAudioUrl> const&  richAudioUrl,
                               const char* richIconObjectPath, const char* richAudioObjectPath,
                               const char* controlPanelServiceObjectPath,
                               const char* originalSender);

    /**
     * SendPayload Marshals the Arguments to be sent
     * @param propertyStore
     * @param messageType
     * @param notificationText
     * @param customAttributes
     * @param ttl
     * @param richIconUrl
     * @param richAudioUrl
     * @param richIconObjectPath
     * @param richAudioObjectPath
     * @param controlPanelServiceObjectPath
     * @param originalSender
     * @return status - success/failure
     */
    static QStatus sendPayload(ajn::services::PropertyStore* propertyStore,
                               NotificationMessageType messageType,
                               std::vector<NotificationText> const&  notificationText,
                               std::map<qcc::String, qcc::String> const& customAttributes,
                               uint16_t ttl,
                               const char* richIconUrl, std::vector<RichAudioUrl> const&  richAudioUrl,
                               const char* richIconObjectPath, const char* richAudioObjectPath,
                               const char* controlPanelServiceObjectPath,
                               const char* originalSender);

    /**
     * SendPayload Marshals the Arguments to be sent
     * @param deviceId
     * @param deviceName
     * @param appId
     * @param appIdlen
     * @param appName
     * @param messageType
     * @param notificationText
     * @param customAttributes
     * @param ttl
     * @param richIconUrl
     * @param richAudioUrl
     * @param richIconObjectPath
     * @param richAudioObjectPath
     * @param controlPanelServiceObjectPath
     * @param originalSender
     * @param messageId
     * @return status - success/failure
     */
    static QStatus sendPayload(const char* deviceId, const char* deviceName,
                               const uint8_t* appId, size_t appIdlen, const char* appName,
                               NotificationMessageType messageType,
                               std::vector<NotificationText> const&  notificationText,
                               std::map<qcc::String, qcc::String> const& customAttributes,
                               uint16_t ttl,
                               const char* richIconUrl, std::vector<RichAudioUrl> const&  richAudioUrl,
                               const char* richIconObjectPath, const char* richAudioObjectPath,
                               const char* controlPanelServiceObjectPath, const char* originalSender, int32_t messageId);

    /**
     * ReceivePayload Unmarshals the arguments received
     * @param msg
     */
    static void receivePayload(ajn::Message& msg);

  private:

    /**
     * SendPayload Marshals the Arguments to be sent
     * @param deviceId
     * @param deviceName
     * @param appId
     * @param appName
     * @param messageType
     * @param notificationText
     * @param customAttributes
     * @param ttl
     * @param richIconUrl
     * @param richAudioUrl
     * @param richIconObjectPath
     * @param richAudioObjectPath
     * @param controlPanelServiceObjectPath
     * @param originalSender
     * @param messageId
     * @return status - success/failure
     */
    static QStatus sendPayload(ajn::MsgArg deviceIdArg, ajn::MsgArg deviceNameArg,
                               ajn::MsgArg appIdArg, ajn::MsgArg appNameArg,
                               NotificationMessageType messageType,
                               std::vector<NotificationText> const&  notificationText,
                               std::map<qcc::String, qcc::String> const& customAttributes,
                               uint16_t ttl,
                               const char* richIconUrl, std::vector<RichAudioUrl> const&  richAudioUrl,
                               const char* richIconObjectPath, const char* richAudioObjectPath,
                               const char* controlPanelServiceObjectPath, const char* originalSender, int32_t messageId);

    /**
     * static MessageId
     */
    static int32_t m_MessageId;
};
} //namespace services
} //namespace ajn

#endif /* PAYLOADADAPTER_H_ */

