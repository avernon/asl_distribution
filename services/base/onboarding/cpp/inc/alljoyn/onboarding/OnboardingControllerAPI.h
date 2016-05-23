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

#ifndef _ONBOARDINGCONTROLLERAPI_H
#define _ONBOARDINGCONTROLLERAPI_H

#include <stdio.h>
#include <map>
#include <string>

#include <qcc/platform.h>
#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/onboarding/Onboarding.h>
#include <alljoyn/Status.h>

namespace ajn {
namespace services {
/**
 *  OnboardingControllerAPI  interface class that is implemented  by the Application and controls the WIFI of the system.
 */

class OnboardingControllerAPI {

  public:

    /**
     * Destructor of OnboardingControllerAPI
     */
    virtual ~OnboardingControllerAPI() { }

    /**
     * ConfigureWiFi passing connection info to connect to WIFI
     * @param[in] SSID  of WIFI AP
     * @param[in] passphrase of WIFI AP in hex
     * @param[in] authType used by  WIFI AP
     * @param[out] status
     * @param[out] error
     * @param[out] errorMessage
     */
    virtual void ConfigureWiFi(qcc::String SSID, qcc::String passphrase, short authType, short& status, qcc::String& error, qcc::String& errorMessage) = 0;

    /**
     *	Connect to the WIFI using the ConfigureWiFi details supplied before
     */
    virtual void Connect() = 0;

    /**
     * GetScanInfo return a list of  OBScanInfo representing  WIFI scan info
     * @param[out] age time in minutes from the last scan
     * @param[out] scanInfoList list of OBScanInfo*
     * @param[out] scanListNumElements number of elements
     */
    virtual void GetScanInfo(unsigned short& age, OBScanInfo*& scanInfoList, size_t& scanListNumElements) = 0;

    /**
     *	Offboard disconnect from the WIFI
     */
    virtual void Offboard() = 0;

    /**
     * Getstate return the last state.
     */
    virtual short GetState() = 0;

    /**
     * GetLastError returns the last error
     * @return OBLastError
     */
    virtual const OBLastError& GetLastError() = 0;

  private:
};
}
}
#endif
