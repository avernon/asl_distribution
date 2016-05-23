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

#import <Foundation/Foundation.h>
#import "AJNAboutService.h"
#import "AJNAboutPropertyStoreImpl.h"

/**
 AJNAboutServiceApi is wrapper class that encapsulates the AJNAboutService using a shared instance.
 */
__deprecated
@interface AJNAboutServiceApi : AJNAboutService

/**
 Destroy the shared instance.
 */
- (void)destroyInstance __deprecated;

/**
 * Create an AboutServiceApi Shared instance.
 * @return AboutServiceApi instance(created only once).
 */
+ (id)sharedInstance __deprecated;

/**
 Start teh service using a given AJNBusAttachment and PropertyStore.
 @param bus A reference to the AJNBusAttachment.
 @param store A reference to a property store.
 */
- (void)startWithBus:(AJNBusAttachment *)bus andPropertyStore:(AJNAboutPropertyStoreImpl *)store __deprecated;

/**
 Return a reference to the property store.
 */
- (ajn ::services ::AboutPropertyStoreImpl *)getPropertyStore __deprecated;

@end
