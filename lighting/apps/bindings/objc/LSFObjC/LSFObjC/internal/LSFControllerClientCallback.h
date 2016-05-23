    /******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#ifndef _LSF_CONTROLLER_CALLBACK_H
#define _LSF_CONTROLLER_CALLBACK_H

#import "LSFControllerClientCallbackDelegate.h"
#import <ControllerClient.h>

using namespace lsf;

class LSFControllerClientCallback : public ControllerClientCallback {
  public:
    LSFControllerClientCallback(id<LSFControllerClientCallbackDelegate> delegate);
    ~LSFControllerClientCallback();
    void ConnectedToControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName);
    void ConnectToControllerServiceFailedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName);
    void DisconnectedFromControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName);
    void ControllerClientErrorCB(const ErrorCodeList& errorCodeList);

  private:
    id<LSFControllerClientCallbackDelegate> _ccDelegate;
};

#endif /* defined(_LSF_CONTROLLER_CALLBACK_H) */
