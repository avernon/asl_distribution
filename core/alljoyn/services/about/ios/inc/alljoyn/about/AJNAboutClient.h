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
#import "AJNBusAttachment.h"

/**
 AJNAboutClient is a helper class used by an AllJoyn IoE client application to discover services being offered by nearby AllJoyn
 IoE service applications. AJNAboutClient enables the user of the class to interact with the remote AboutService instance.
 */
__deprecated
@interface AJNAboutClient : NSObject

/**
 Designated initializer
 Create an AboutClient Object using the passed AJNBusAttachment
 @param bus A reference to the AJNBusAttachment.
 @return AboutClient if successful.
 */
- (id)initWithBus:(AJNBusAttachment *)bus __deprecated;

/**
 Populate a given dictionary with the object Description(s) for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param objectDescs Description of busName's remote objects [in,out].
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)objectDescriptionsWithBusName:(NSString *)busName andObjectDescriptions:(NSMutableDictionary **)objectDescs andSessionId:(uint32_t)sessionId __deprecated;

/**
 Populate a given dictionary with the AboutData for specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param languageTag The language used to request the AboutData.
 @param data A reference of AboutData that is filled by the function [in,out].
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)aboutDataWithBusName:(NSString *)busName andLanguageTag:(NSString *)languageTag andAboutData:(NSMutableDictionary **)data andSessionId:(uint32_t)sessionId __deprecated;

/**
 Populate a given parameter with the About version
 @param busName Unique or well-known name of AllJoyn bus.
 @param version The service version.
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)versionWithBusName:(NSString *)busName andVersion:(int)version andSessionId:(AJNSessionId)sessionId __deprecated;

@end
