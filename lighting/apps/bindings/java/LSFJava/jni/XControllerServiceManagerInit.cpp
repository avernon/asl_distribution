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
 *
 ******************************************************************************/

#include "XControllerServiceManagerInit.h"

namespace lsf {
namespace controllerservice {

ControllerServiceManager* managerInstance = NULL;

ControllerServiceManager* InitializeControllerServiceManager(
    const std::string& factoryConfigFile,
    const std::string& configFile,
    const std::string& lampGroupFile,
    const std::string& presetFile,
    const std::string& transitionEffectFile,
    const std::string& pulseEffectFile,
    const std::string& sceneElementsFile,
    const std::string& sceneFile,
    const std::string& sceneWithSceneElementsFile,
    const std::string& masterSceneFile)
{
    // Save a copy of the ControllerServiceManager pointer so that we can
    // later invoke the LightingReset() and FactoryReset() API methods.
    managerInstance = new ControllerServiceManager(
        factoryConfigFile,
        configFile,
        lampGroupFile,
        presetFile,
        transitionEffectFile,
        pulseEffectFile,
        sceneElementsFile,
        sceneFile,
        sceneWithSceneElementsFile,
        masterSceneFile);

    return managerInstance;
}

} /* namespace controllerservice */
} /* namespace lsf */
