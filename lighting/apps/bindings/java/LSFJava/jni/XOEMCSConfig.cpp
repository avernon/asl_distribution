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
 *
 ******************************************************************************/

#include <algorithm>
#include <time.h>

#include <qcc/Debug.h>
#include <qcc/String.h>

#include <alljoyn/AboutData.h>

#include "XControllerService.h"
#include "XOEMCSConfig.h"

namespace lsf {
namespace controllerservice {

#define QCC_MODULE "AJN-LSF-JNI"

void OEM_CS_GetFactorySetDefaultLampState(LampState& defaultState)
{
    // Must define the default lamp state value
    static const LampState OEM_CS_DefaultLampState = LampState(true, 0, 0, 0, 0);

    defaultState = OEM_CS_DefaultLampState;
}

void OEM_CS_GetSyncTimeStamp(uint64_t& timeStamp)
{
    struct timespec res;

    clock_gettime(CLOCK_REALTIME, &res);
    timeStamp = ((uint64_t) 1000 * res.tv_sec) + ((uint64_t) res.tv_nsec / 1e6);
}

bool OEM_CS_FirmwareStart(OEM_CS_NetworkCallback& networkCallback)
{
    // Must have code here to initialize and start the firmware and
    // return true/false accordingly. The code should also save off the
    // reference to the OEM_CS_NetworkCallback object and invoke the
    // Connected() and Disconnected() functions defined in this callback
    // whenever the device connects to and disconnects from the network
    // accordingly
    XControllerService *activeController = XControllerService::getActive();

    if (activeController != NULL) {
        activeController->cNetworkCallback = &networkCallback;
    } else {
        // This should not happen (Start is initiated by the active XControllerService)
        QCC_LogError(ER_FAIL, ("No active controller"));
    }

    // Start is initiated by the active XControllerService, so nothing else to do
    return true;
}

bool OEM_CS_FirmwareStop(void)
{
    // Must have code here to stop and cleanup the firmware and
    // return true/false accordingly

    // Stop is initiated by the active XControllerService, so nothing else to do
    return true;
}

uint64_t OEM_CS_GetMACAddress(void)
{
    // Must have code here to return the MAC address
    // of the device as a 48-bit value
    XControllerService *activeController = XControllerService::getActive();
    LSFString defaultMacAddress = qcc::RandHexString(6).c_str(); // 6 bytes = 48 bits
    LSFString returnedMacAddress = activeController ? activeController->GetMacAddress(defaultMacAddress) : defaultMacAddress;

    // Remove any punctuation
    returnedMacAddress.erase(std::remove(returnedMacAddress.begin(), returnedMacAddress.end(), ' '), returnedMacAddress.end());
    returnedMacAddress.erase(std::remove(returnedMacAddress.begin(), returnedMacAddress.end(), '.'), returnedMacAddress.end());
    returnedMacAddress.erase(std::remove(returnedMacAddress.begin(), returnedMacAddress.end(), ':'), returnedMacAddress.end());

    char *nextChar = NULL;
    uint64_t macValue = strtoull(returnedMacAddress.c_str(), &nextChar, 16) & 0x0000FFFFFFFFFFFFL;

    if (macValue == 0 || *nextChar != '\0') {
        QCC_LogError(ER_FAIL, ("Invalid MAC address: %s", returnedMacAddress.c_str()));
        QCC_LogError(ER_FAIL, ("Using default MAC address: %s", defaultMacAddress.c_str()));
        macValue = strtoull(defaultMacAddress.c_str(), NULL, 16) & 0x0000FFFFFFFFFFFFL;
    }

    QCC_DbgPrintf(("%s: MAC Address = %llu", __func__, macValue));

    return macValue;
}

bool OEM_CS_IsNetworkConnected(void)
{
    // Must have code here to find out if the device is connected to a network and
    // return true/false accordingly
    XControllerService *activeController = XControllerService::getActive();
    bool defaultIsNetworkConnected = false;

    return activeController ? activeController->IsNetworkConnected(defaultIsNetworkConnected) : defaultIsNetworkConnected;
}

OEM_CS_RankParam_Power OEM_CS_GetRankParam_Power(void)
{
    // Must have add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Power depending on the type of the device on which
    // the Controller Service is being run
    XControllerService *activeController = XControllerService::getActive();
    OEM_CS_RankParam_Power defaultRankPower = BATTERY_POWERED_CHARGABLE;

    return activeController ? activeController->GetRankPower(defaultRankPower) : defaultRankPower;
}

OEM_CS_RankParam_Mobility OEM_CS_GetRankParam_Mobility(void)
{
    // Must have add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Mobility depending on the type of the device on which
    // the Controller Service is being run
    XControllerService *activeController = XControllerService::getActive();
    OEM_CS_RankParam_Mobility defaultRankMobility = HIGH_MOBILITY;

    return activeController ? activeController->GetRankMobility(defaultRankMobility) : defaultRankMobility;
}

OEM_CS_RankParam_Availability OEM_CS_GetRankParam_Availability(void)
{
    // Must have add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Availability depending on the type of the device on which
    // the Controller Service is being run
    XControllerService *activeController = XControllerService::getActive();
    OEM_CS_RankParam_Availability defaultRankAvailability = SIX_TO_NINE_HOURS;

    return activeController ? activeController->GetRankAvailability(defaultRankAvailability) : defaultRankAvailability;
}

OEM_CS_RankParam_NodeType OEM_CS_GetRankParam_NodeType(void)
{
    // Must have add code here to return the appropriate enum value from
    // OEM_CS_RankParam_NodeType depending on network configuration of the device on which
    // the Controller Service is being run
    XControllerService *activeController = XControllerService::getActive();
    OEM_CS_RankParam_NodeType defaultRankNodeType = WIRELESS;

    return activeController ? activeController->GetRankNodeType(defaultRankNodeType) : defaultRankNodeType;
}

// NOTE: this function will only be called if no Factory Configuration ini file is found.
// This file is specified on the command line and defaults to OEMConfig.ini in the current
// working directory.
void OEM_CS_PopulateDefaultProperties(AboutData* aboutData)
{
    QCC_DbgTrace(("%s", __func__));

    XControllerService *activeController = XControllerService::getActive();

    if (activeController != NULL) {
        activeController->PopulateDefaultProperties(aboutData);
    }
}

}
}
