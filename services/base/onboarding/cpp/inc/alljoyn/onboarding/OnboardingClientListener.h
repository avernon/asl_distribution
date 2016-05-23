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

#ifndef ONBOARDINGCLIENTLISTENER_H_
#define ONBOARDINGCLIENTLISTENER_H_

#include <qcc/String.h>

namespace ajn {
namespace services {
/**
 * OnboardingClientListener
 *
 *  is a helper class used by an AllJoyn IoE client application to receive OnboardingService signal notification.
 * The user of the class need to implement virtual void ConnectionResultSignalReceived(...) function
 */

class OnboardingClientListener {
  public:
    /**
     * Destructor
     */
    virtual ~OnboardingClientListener() { }

    /**
     * ConnectionResultSignalReceived
     * Needs to be implemented by the user for the desired behaviour when receiving the ConnectResult Signal
     * @param connectionResultCode
     * @param connectionResultMessage
     */
    virtual void ConnectionResultSignalReceived(short connectionResultCode, const qcc::String& connectionResultMessage) = 0;
};
}
}



#endif /* ONBOARDINGCLIENTLISTENER_H_ */
