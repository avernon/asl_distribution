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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include "MyDeviceTurnFanOff.h"
#include "ControlPanelProvided.h"


namespace ajn {
namespace services {

MyDeviceTurnFanOff::MyDeviceTurnFanOff(qcc::String name, Widget* rootWidget) : Dialog(name, rootWidget)
{

}

MyDeviceTurnFanOff::~MyDeviceTurnFanOff()
{

}

bool MyDeviceTurnFanOff::executeAction1CallBack()
{
    OnTurnFanOffButton(true);

    //by default return success
    return true;
}

bool MyDeviceTurnFanOff::executeAction2CallBack()
{
    OnTurnFanOffButton(false);

    //by default return success
    return true;
}

bool MyDeviceTurnFanOff::executeAction3CallBack()
{
    return executeActionNotDefined();
}

} /* namespace services */
} /* namespace ajn */
