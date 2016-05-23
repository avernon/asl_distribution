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

#include <iostream>
#include <signal.h>
#include "Menu.h"
#include "ContentSourceTracker.h"
#include <ContentServiceClient.h>
#include <ContentClientParams.h>
#include <SrpKeyXListener.h>
#include <qcc/Debug.h>
#include <qcc/Log.h>
#include <CommonSampleUtil.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using namespace mdf;

#define QCC_MODULE "Controller"

Menu* menu;
ContentClientParams* contentClientParams;
SrpKeyXListener* srpKeyXListener = 0;
ContentSourceTracker* contentSourceTracker = 0;

void cleanup()
{
    if (menu) {
        delete menu;
    }

    if (contentSourceTracker) {
        ContentServiceClient::GetInstance()->UnRegisterContentSourceListener(*contentSourceTracker);
        delete contentSourceTracker;
    }

    ContentServiceClient::GetInstance()->Shutdown();

    if (contentClientParams) {
        delete contentClientParams;
    }
}

static void signal_callback_handler(int32_t signum)
{
    cleanup();
    exit(signum);
}

void initServices() {

    //Init ContentServiceClient
    ContentServiceClient* csClient = ContentServiceClient::GetInstance();

    contentSourceTracker = new ContentSourceTracker();
    ContentSourceTracker* constTracker = contentSourceTracker;
    csClient->RegisterContentSourceListener(*constTracker);

    ContentClientParams* contentClientParams = new ContentClientParams();
    csClient->Init(contentClientParams);
    //End ContentServiceClient
}

int main(int argc, char**argv)
{
    // Allow CTRL+C to end application
    signal(SIGINT, signal_callback_handler);
    QCC_SetLogLevels("ALL=0");

    initServices();
    #ifdef _WIN32
    Sleep(1000);
    #else
    sleep(1);
    #endif

    menu = new Menu(contentSourceTracker);
    cout << "" << endl;
    while (menu->DisplayMenu()) {
        //NOOP
    }
    cleanup();

    return 1;
}

