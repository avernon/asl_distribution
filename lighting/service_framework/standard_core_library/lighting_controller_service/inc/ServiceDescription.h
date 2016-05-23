# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _SERVICE_DESCRIPTION_H_
#define _SERVICE_DESCRIPTION_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for service description
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

#include <string>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

extern const std::string ControllerServiceDescription;
extern const std::string ControllerServiceLampDescription;
extern const std::string ControllerServiceLampGroupDescription;
extern const std::string ControllerServicePresetDescription;
extern const std::string ControllerServiceTransitionEffectDescription;
extern const std::string ControllerServicePulseEffectDescription;
extern const std::string ControllerServiceSceneDescription;
extern const std::string ControllerServiceSceneWithSceneElementsDescription;
extern const std::string ControllerServiceSceneElementDescription;
extern const std::string ControllerServiceMasterSceneDescription;
extern const std::string LeaderElectionAndStateSyncDescription;
extern const std::string ControllerServiceDataSetDescription;

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif
