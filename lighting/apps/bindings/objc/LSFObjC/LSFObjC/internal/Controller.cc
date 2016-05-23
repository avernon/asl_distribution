/******************************************************************************
 * Copyright (c) 2015, AllSeen Alliance. All rights reserved.
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

#include "Controller.h"

using namespace ajn;
using namespace lsf;
using namespace qcc;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#endif

id<LSFControllerServiceDelegate> controllerServiceDelegate = NULL;
OEM_CS_NetworkCallback* networkCallbackReference = NULL;

void ControllerServiceSleep(uint32_t msec)
{
    usleep(1000 * msec);
}

const char* getControllerDefaultDeviceId()
{
    printf("Controller.cc - getControllerDefaultDeviceId() executing\n");

    qcc::String rdd = qcc::RandHexString(16);
    NSString *randomDeviceID = [NSString stringWithUTF8String: rdd.c_str()];
    const char *deviceID = [[controllerServiceDelegate getControllerDefaultDeviceID: randomDeviceID] UTF8String];

    return deviceID;
}

uint64_t getMacAddress()
{
    printf("Controller.cc - getMacAddress() executing\n");

    qcc::String mac = qcc::RandHexString(12);
    NSString *generatedMacAddress = [NSString stringWithUTF8String: mac.c_str()];
    return [controllerServiceDelegate getMacAddressAsDecimal: generatedMacAddress];
}

bool isNetworkConnected()
{
    printf("Controller.cc - isNetworkConnected() executing\n");
    return [controllerServiceDelegate isNetworkConnected];
}

OEM_CS_RankParam_Power getRankPower()
{
    printf("Controller.cc - getRankPower() executing\n");
    return [controllerServiceDelegate getControllerRankPower];
}

OEM_CS_RankParam_Mobility getRankMobility()
{
    printf("Controller.cc - getRankMobility() executing\n");
    return [controllerServiceDelegate getControllerRankMobility];
}

OEM_CS_RankParam_Availability getRankAvailability()
{
    printf("Controller.cc - getRankAvailability() executing\n");
    return [controllerServiceDelegate getControllerRankAvailability];
}

OEM_CS_RankParam_NodeType getRankNodeType()
{
    printf("Controller.cc - getRankNodeType() executing\n");
    return [controllerServiceDelegate getControllerRankNodeType];
}

void populateDefaultProperties(ajn::AboutData* aboutData)
{
    printf("Controller.cc - populateDefaultProperties() executing\n");
    LSFSDKAboutData *myAboutData = [[LSFSDKAboutData alloc] initWithAboutData: aboutData];
    return [controllerServiceDelegate populateDefaultProperties: myAboutData];
}

Controller::Controller()
{
    printf("Controller.cc - Controller() constructor executing\n");
}

void Controller::SetControllerCallback(id<LSFControllerServiceDelegate> delegate)
{
    controllerServiceDelegate = delegate;
}

void Controller::StartController(const char *keyStoreFilePath)
{
    printf("controller.cc :: startControllerService keyStore: %s\n", keyStoreFilePath);
    int argc = 5;
    char* argv[argc];
    argv[0] = const_cast <char*>("controllerService");
    argv[1] = const_cast <char*>("-f");
    argv[2] = const_cast <char*>("-l");
    argv[3] = const_cast <char*>("-k");
    argv[4] = const_cast <char*>(keyStoreFilePath);
    g_running = true;

    runMain(argc, argv);
}

void Controller::StopController()
{
    printf("stopping ControllerService. g_running=%d\n", g_running);

    g_running = false;

    while (g_running && isRunning)
    {
        ControllerServiceSleep(1000);
        printf("Controller is in process of stopping\n");
    }

    printf("Controller has fully stopped\n");
}

void Controller::FactoryResetController()
{
    printf("resetting the controller service");

    if (controllerSvcManagerPtrForLuminaire != NULL)
    {
        controllerSvcManagerPtrForLuminaire->GetControllerServicePtr()->FactoryResetAPI();
    }
}

void Controller::LightingResetController()
{
    printf("factory resetting the controller service");

    if (controllerSvcManagerPtrForLuminaire != NULL)
    {
        controllerSvcManagerPtrForLuminaire->GetControllerServicePtr()->LightingResetAPI();
    }
}

void Controller::SendNetworkConnected()
{
    if (networkCallbackReference)
    {
        networkCallbackReference->Connected();
    }
}

void Controller::SendNetworkDisconnected()
{
    if (networkCallbackReference)
    {
        networkCallbackReference->Disconnected();
    }
}

qcc::String Controller::GetControllerName()
{
    if (controllerSvcManagerPtrForLuminaire != NULL)
    {
        LSFAboutDataStore dataStore = controllerSvcManagerPtrForLuminaire->GetControllerServicePtr()->GetAboutDataStore();

        char* controllerName = NULL;
        dataStore.GetDeviceName(&controllerName);
        return qcc::String(controllerName);
    }

    return qcc::String();
}

bool Controller::IsControllerLeader()
{
    return (controllerSvcManagerPtrForLuminaire) ? controllerSvcManagerPtrForLuminaire->GetControllerServicePtr()->IsLeader() : false;
}
