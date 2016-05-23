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
#ifndef _ONBOARDINGSERVICE_H
#define _ONBOARDINGSERVICE_H

#include <alljoyn/BusObject.h>
#include <alljoyn/Status.h>
#include  <alljoyn/onboarding/OnboardingControllerAPI.h>

namespace ajn {
namespace services {

/**
 * OnboardingService is an AllJoyn BusObject that implements the org.alljoyn.Onboarding standard interface.
 * Applications that provide AllJoyn IoE services use an instance of this class to enable onboarding of
 * the device.
 */
class OnboardingService : public ajn::BusObject {

  public:

    /**
     * Constructor of OnboardingService
     * @param[in] bus is a reference to BusAttachment
     * @param[in] pOnboardingControllerAPI is a reference to OnboardingControllerAPI
     */
    OnboardingService(ajn::BusAttachment& bus, OnboardingControllerAPI& pOnboardingControllerAPI);

    /**
     * Destructor of OnboardingService
     */
    ~OnboardingService() { }

    /**
     * Register the OnboardingService on the alljoyn bus.
     * @return status.
     */
    QStatus Register();
    /**
     *  Unregister the OnboardingService from  the alljoyn bus .
     */
    void Unregister();

  private:

    /**
     * Handles the ConfigureWiFi method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void ConfigureWiFiHandler(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    /**
     * Handles the Connect method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void ConnectHandler(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    /**
     * Handles the Offboard method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OffboardHandler(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    /**
     * Handles the GetScanInfo method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void GetScanInfoHandler(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    /**
     * Handles the Get Property requests
     * @param ifcName
     * @param propName
     * @param val
     * @return
     */
    QStatus Get(const char*ifcName, const char*propName, MsgArg& val);
    /**
     * check if method reply is needed and print if encounter an error
     * @param Message&
     * @param const MsgArg*
     * @param numArgs
     * @return
     */
    void Check_MethodReply(const Message& msg, const MsgArg* args = NULL, size_t numArgs = 0);
    /**
     * check if method reply is needed and print if encounter an error
     * @param Message&
     * @param QStatus
     * @return
     */
    void Check_MethodReply(const Message& msg, QStatus status);
    /**
     *	pointer of BusAttachment
     */
    ajn::BusAttachment* m_BusAttachment;
    /**
     * pointer of OnboardingControllerAPI
     */
    OnboardingControllerAPI& m_OnboardingController;
};

}
}

#endif /*_ONBOARDINGSERVICE_H*/
