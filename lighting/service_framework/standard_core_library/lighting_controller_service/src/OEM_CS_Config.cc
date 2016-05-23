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

#include <LSFAboutDataStore.h>
#include <OEM_CS_Config.h>
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <alljoyn/services_common/GuidUtil.h>

using namespace services;

namespace qcc {
extern uint64_t Rand64();
}

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

#define QCC_MODULE "OEM_CS_CONFIG"

// OEMs should modify this default lamp state value as required
static const LampState OEM_CS_DefaultLampState = LampState(true, 0, 0, 0, 0);

uint64_t OEM_MacAddr = 0;

void OEM_CS_GetFactorySetDefaultLampState(LampState& defaultState)
{
    QCC_DbgPrintf(("%s", __func__));
    defaultState = OEM_CS_DefaultLampState;
}

void OEM_CS_GetSyncTimeStamp(uint64_t& timeStamp)
{
    // This is just a sample implementation and so it passes back a
    // random value. OEMs are supposed to integrate this
    // with their Time Sync module to return a valid time stamp
    qcc::String timeString = qcc::RandHexString(16);
    timeStamp = StringToU64(timeString, 16);
    QCC_DbgPrintf(("%s: timeString = %s timestamp = %llu", __func__, timeString.c_str(), timeStamp));
}

bool OEM_CS_FirmwareStart(OEM_CS_NetworkCallback& networkCallback)
{
    // OEMs should add code here to initialize and start the firmware and
    // return true/false accordingly. The firmware should also save off the
    // reference to the OEM_CS_NetworkCallback object and invoke the
    // Connected() and Disconnected() functions defined in this callback
    // whenever the device connects to and disconnects from the network
    // accordingly
    return true;
}

bool OEM_CS_FirmwareStop(void)
{
    // OEMs should add code here to stop and cleanup the firmware and
    // return true/false accordingly
    return true;
}

uint64_t OEM_CS_GetMACAddress(void)
{
    // This is just a sample implementation and so it passes back a
    // random value. OEMs should add code here to return the MAC address
    // of the device as a 48-bit value
    while (OEM_MacAddr == 0) {
        OEM_MacAddr = qcc::Rand64();
        QCC_DbgPrintf(("%s: MAC Address = %llu", __func__, OEM_MacAddr));
    }
    QCC_DbgPrintf(("%s: MAC Address = %llu", __func__, OEM_MacAddr));
    return OEM_MacAddr;
}

bool OEM_CS_IsNetworkConnected(void)
{
    // OEMs should add code here to find out if the device is connected to a network and
    // return true/false accordingly
    return true;
}

OEM_CS_RankParam_Power OEM_CS_GetRankParam_Power(void)
{
    // OEMs should add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Power depending on the type of the device on which
    // the Controller Service is being run
    return ALWAYS_AC_POWERED;
}

OEM_CS_RankParam_Mobility OEM_CS_GetRankParam_Mobility(void)
{
    // OEMs should add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Mobility depending on the type of the device on which
    // the Controller Service is being run
    return ALWAYS_STATIONARY;
}

OEM_CS_RankParam_Availability OEM_CS_GetRankParam_Availability(void)
{
    // OEMs should add code here to return the appropriate enum value from
    // OEM_CS_RankParam_Availability depending on the type of the device on which
    // the Controller Service is being run
    return TWENTY_ONE_TO_TWENTY_FOUR_HOURS;
}

OEM_CS_RankParam_NodeType OEM_CS_GetRankParam_NodeType(void)
{
    // OEMs should add code here to return the appropriate enum value from
    // OEM_CS_RankParam_NodeType depending on network configuration of the device on which
    // the Controller Service is being run
    return WIRED;
}

// NOTE: this function will only be called if no Factory Configuration ini file is found.
// This file is specified on the command line and defaults to OEMConfig.ini in the current
// working directory.
void OEM_CS_PopulateDefaultProperties(AboutData* aboutData)
{
    QCC_DbgTrace(("%s", __func__));

    aboutData->SetDateOfManufacture("10/1/2199");
    aboutData->SetDefaultLanguage("en");
    aboutData->SetHardwareVersion("355.499. b");
    aboutData->SetModelNumber("Wxfy388i");
    aboutData->SetSoftwareVersion("12.20.44 build 44454");
    aboutData->SetSupportUrl("http://www.example.com");
    aboutData->SetSupportedLanguage("en");
    aboutData->SetSupportedLanguage("de-AT");
    aboutData->SetAppName("LightingControllerService", "en");
    aboutData->SetAppName("LightingControllerService", "de-AT");
    aboutData->SetDescription("Controller Service", "en");
    aboutData->SetDescription("Controller Service", "de-AT");
    aboutData->SetDeviceName("My device name", "en");
    aboutData->SetDeviceName("Mein Gerätename", "de-AT");
    aboutData->SetManufacturer("Company A (EN)", "en");
    aboutData->SetManufacturer("Firma A (DE-AT)", "de-AT");

    qcc::String appId;
#if !defined(LSF_OS_DARWIN)
    GuidUtil::GetInstance()->GenerateGUID(&appId);
#else
    /*
     * Anybody trying to build the Controller Service code on IOS would need
     * to generate a new random app ID and initialize "appId".
     * This is required because GuidUtil is not available in the services_common
     * IOS library.
     */
#endif
    aboutData->SetAppId(appId.c_str());
}

OPTIONAL_NAMESPACE_CLOSE

}
