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
 *
 ******************************************************************************/

#ifndef LSF_JNI_XCONTROLLERSERVICEMANAGERCALLBACK_H_
#define LSF_JNI_XCONTROLLERSERVICEMANAGERCALLBACK_H_

#include <jni.h>

#include <ControllerServiceManager.h>   // lighting/service_framework

#include "NDefs.h"

namespace lsf {

class XControllerServiceManagerCallback : public ControllerServiceManagerCallback {
public:
    XControllerServiceManagerCallback(jobject jobj);
    virtual ~XControllerServiceManagerCallback();

    virtual void GetControllerServiceVersionReplyCB(const uint32_t& version) LSF_OVERRIDE;
    virtual void LightingResetControllerServiceReplyCB(const LSFResponseCode& responseCode) LSF_OVERRIDE;
    virtual void ControllerServiceLightingResetCB(void) LSF_OVERRIDE;
    virtual void ControllerServiceNameChangedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName) LSF_OVERRIDE;

protected:
    jweak jdelegate;
};

} /* namespace lsf */
#endif /* LSF_JNI_XCONTROLLERSERVICEMANAGERCALLBACK_H_ */

