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

#ifndef LSFController_Controller_h
#define LSFController_Controller_h

#include <LSFTypes.h>
#include <algorithm>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Status.h>
#include <alljoyn/version.h>
#include <climits>
#include <lsf/controllerservice/ControllerService.h>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <lsf/controllerservice/LSFAboutDataStore.h>
#include <qcc/Debug.h>
#include <qcc/StringUtil.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <AJInitializer.h>
#include <ControllerServiceManagerInit.h>
#import "LSFControllerServiceDelegate.h"

using namespace ajn;

extern lsf::controllerservice::ControllerServiceManager* controllerSvcManagerPtrForLuminaire;
extern int runMain(int argc, char** argv);
extern volatile sig_atomic_t g_running;
extern volatile sig_atomic_t isRunning;
extern bool g_IsLeader;
extern lsf::controllerservice::LSFAboutDataStore* luminaireDS;
extern qcc::String controllerName;
//Not in use functions
extern long getNTPOffset();
extern uint64_t getNTPTimeFromJava();
extern const char* getControllerDefaultDeviceId();
//extern qcc::String* getControllerDefaultAppId(const char* str);
extern uint64_t getMacAddress();
extern bool isNetworkConnected();
extern lsf::controllerservice::OEM_CS_NetworkCallback* networkCallbackReference;
extern lsf::controllerservice::OEM_CS_RankParam_Power getRankPower();
extern lsf::controllerservice::OEM_CS_RankParam_Mobility getRankMobility();
extern lsf::controllerservice::OEM_CS_RankParam_Availability getRankAvailability();
extern lsf::controllerservice::OEM_CS_RankParam_NodeType getRankNodeType();
extern void populateDefaultProperties(ajn::AboutData* aboutData);

class Controller {
    public:
        Controller();
        void SetControllerCallback(id<LSFControllerServiceDelegate> delegate);
        void StartController(const char *keyStoreFilePath);
        void StopController();
        void FactoryResetController();
        void LightingResetController();
        void SendNetworkConnected();
        void SendNetworkDisconnected();
        qcc::String GetControllerName();
        bool IsControllerLeader();
};

#endif
