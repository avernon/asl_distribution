/**
 * @file
 * Contains the ApplicationStateListener class
 */
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
#ifndef _ALLJOYN_APPLICATIONSTATELISTENER_H
#define _ALLJOYN_APPLICATIONSTATELISTENER_H

#include <alljoyn/PermissionConfigurator.h>

namespace ajn {

/**
 * Listener used to handle the security State signal.
 */
class ApplicationStateListener {
  public:
    /**
     * ApplicationStateListener constructor
     */
    ApplicationStateListener() { }

    /**
     * ApplicationStateListener destructor
     */
    virtual ~ApplicationStateListener() { }

    /**
     * Handler for the org.allseen.Bus.Application's State sessionless signal.
     *
     * @param[in] busName          unique name of the remote BusAttachment that
     *                             sent the State signal
     * @param[in] publicKeyInfo the application public key
     * @param[in] state the application state
     */
    virtual void State(const char* busName, const qcc::KeyInfoNISTP256& publicKeyInfo, PermissionConfigurator::ApplicationState state) = 0;
};
}
#endif //_ALLJOYN_APPLICATIONSTATELISTENER_H
