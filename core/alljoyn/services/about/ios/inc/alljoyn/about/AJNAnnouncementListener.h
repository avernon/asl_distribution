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

/**
 AJNAnnouncementListener is a helper protocol used by AnnounceHandlerAdapter to receive AboutService signal notification.
 The user of the class need to implement the protocol method.
 */
__deprecated
@protocol AJNAnnouncementListener <NSObject>

/**
 Called by the AnnounceHandlerAdapter when a new announcement received. This gives the listener implementation the opportunity to save a reference to announcemet parameters.
 @param version The version of the AboutService.
 @param port The port used by the AboutService
 @param busName Unique or well-known name of AllJoyn bus.
 @param objectDescs Map of ObjectDescriptions using NSMutableDictionary, describing interfaces
 @param aboutData Map of AboutData using NSMutableDictionary, describing message args
 */
- (void)announceWithVersion:(uint16_t)version port:(uint16_t)port busName:(NSString *)busName objectDescriptions:(NSMutableDictionary *)objectDescs aboutData:(NSMutableDictionary **)aboutData __deprecated;
@end
