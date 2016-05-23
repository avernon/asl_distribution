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

#import "LSFSDKLightingControllerConfiguration.h"

/**
 * Provides a base class for developers to extend or use directly to define the application and device
 * specific properties for the LSFSDKLightingController. This class can be instantiated and passed directly
 * to the LSFSDKLightingController without modification. Developers can override only the functions they wish
 * to change.
 *
 * An example usage of a LightingControllerConfigurationBase can be found in the LSFTutorial project.
 *
 * @warning All parameters are set using hard coded values EXCEPT the absolute save path which must be
 * passed in to the constructor.
 *
 * @warning Once implemented, the configuration must be registered with the LSFSDKLightingController
 * using the [LSFSDKLightingController initializeWithControllerConfiguration:] method.
 */
@interface LSFSDKLightingControllerConfigurationBase : NSObject <LSFSDKLightingControllerConfiguration>
{
    @private NSString *keystoreFilePath;
}

-(id)initWithKeystorePath: (NSString *)keystorePath;

@end