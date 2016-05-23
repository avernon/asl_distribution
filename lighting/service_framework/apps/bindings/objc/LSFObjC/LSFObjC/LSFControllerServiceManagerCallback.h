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

#ifndef _LSF_CONTROLLER_SERVICE_MANAGER_CALLBACK_H
#define _LSF_CONTROLLER_SERVICE_MANAGER_CALLBACK_H

#import "LSFControllerServiceManagerCallbackDelegate.h"
#import "ControllerServiceManager.h"

using namespace lsf;

class LSFControllerServiceManagerCallback : public ControllerServiceManagerCallback {
  public:
    LSFControllerServiceManagerCallback(id<LSFControllerServiceManagerCallbackDelegate> delegate);
    ~LSFControllerServiceManagerCallback();
    void GetControllerServiceVersionReplyCB(uint32_t version);
    void LightingResetControllerServiceReplyCB(LSFResponseCode responseCode);
    void ControllerServiceLightingResetCB(void);
    void ControllerServiceNameChangedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName);
    
  private:
    id<LSFControllerServiceManagerCallbackDelegate> _csmDelegate;
};

#endif /* defined(_LSF_CONTROLLER_SERVICE_MANAGER_CALLBACK_H) */
