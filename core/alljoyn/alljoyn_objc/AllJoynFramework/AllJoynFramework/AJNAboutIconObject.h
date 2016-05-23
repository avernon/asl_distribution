////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "AJNBusObject.h"
#import "AJNBusAttachment.h"
#import "AJNAboutIcon.h"

@interface AJNAboutIconObject : AJNBusObject
/**
 * Construct an About Icon BusObject.
 *
 * @param[in] bus  BusAttachment instance associated with this AboutService
 * @param[in] icon instance of an AboutIcon which holds the icon image
 */
- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment aboutIcon:(AJNAboutIcon *)aboutIcon;

/**
 * version of the org.alljoyn.Icon interface
 */
+ (uint16_t)version;

@end