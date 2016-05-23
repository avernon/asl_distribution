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
#import "AJNAboutIcon.h"
#import "AJNSessionOptions.h"
#import "AJNObject.h"
#import "AJNAboutIcon.h"
#import "AJNBusAttachment.h"

@interface AJNAboutIconProxy : AJNObject

/**
 * Construct an AboutIconProxy.
 * @param bus reference to BusAttachment
 * @param[in] busName Unique or well-known name of AllJoyn bus
 * @param[in] sessionId the session received  after joining AllJoyn sessio
 */
- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment busName:(NSString *)busName sessionId:(AJNSessionId)sessionId;

/**
 * @param[out] icon class that holds icon content
 * @return ER_OK if successful
 */
- (QStatus)getIcon:(AJNAboutIcon *)icon;

/**
 * Get the version of the About Icon Interface
 *
 * @param[out] version of the AboutIcontClient
 *
 * @return ER_OK if successful
 */
- (QStatus)getVersion:(uint16_t *)version;

@end
