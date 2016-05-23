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
#import "AJNSessionOptions.h"

/**
 AJNAboutIconClient enables the user of the class to interact with the remote AboutServiceIcon instance.
 */
__deprecated
@interface AJNAboutIconClient : NSObject
/**
 Designated initializer.
 Create an AboutIconClient Object using the passed AJNBusAttachment.
 @param bus A reference to the AJNBusAttachment.
 */
- (id)initWithBus:(AJNBusAttachment *)bus __deprecated;

/**
 Populate a given parameter with the icon url for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param url The url of the icon[out].
 @return ER_OK if successful.
 */
- (QStatus)urlFromBusName:(NSString *)busName url:(NSString **)url __deprecated;

/**
 Populate a given parameter with the icon url for a specified bus name and session id.
 @param busName Unique or well-known name of AllJoyn bus.
 @param url The url of the icon[out].
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)urlFromBusName:(NSString *)busName url:(NSString **)url sessionId:(AJNSessionId)sessionId __deprecated;

/**
 Populate a given parameter with the icon content and the content size for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param content The retrieved content of the icon payload [out].
 @param contentSize The size of the content payload [out].
 @return ER_OK if successful.
 */
- (QStatus)contentFromBusName:(NSString *)busName content:(uint8_t **)content contentSize:(size_t&)contentSize __deprecated;

/**
 Populate a given parameter with the icon content and the content size for a specified bus name and session id.
 @param busName Unique or well-known name of AllJoyn bus.
 @param content The retrieved content of the icon payload [out].
 @param contentSize The size of the content payload [out].
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)contentFromBusName:(NSString *)busName content:(uint8_t **)content contentSize:(size_t&)contentSize sessionId:(AJNSessionId)sessionId __deprecated;

/**
 Populate a given parameters with the version of the AboutIcontClient for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param version The AboutIcontClient version[out].
 @return ER_OK if successful.
 */
- (QStatus)versionFromBusName:(NSString *)busName version:(int&)version __deprecated;

/**
 Populate a given parameters with the version of the AboutIcontClient for a specified bus name and session id.
 @param busName Unique or well-known name of AllJoyn bus.
 @param version The AboutIcontClient version[out].
 @param sessionId the session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)versionFromBusName:(NSString *)busName version:(int&)version sessionId:(AJNSessionId)sessionId __deprecated;

/**
 Populate a given parameter with the icon mime type for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param mimeType The icon's mime type [out].
 @return ER_OK if successful.
 */
- (QStatus)mimeTypeFromBusName:(NSString *)busName mimeType:(NSString **)mimeType __deprecated;

/**
 Populate a given parameter with the icon mime type for a specified bus name and session id.
 @param busName Unique or well-known name of AllJoyn bus.
 @param mimeType The icon's mime type [out].
 @param sessionId The session received after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)mimeTypeFromBusName:(NSString *)busName mimeType:(NSString **)mimeType sessionId:(AJNSessionId)sessionId __deprecated;

/**
 Populate a given parameter with the icon size for a specified bus name.
 @param busName Unique or well-known name of AllJoyn bus.
 @param size The size of the icon [out].
 @return ER_OK if successful.
 */
- (QStatus)sizeFromBusName:(NSString *)busName size:(size_t&)size __deprecated;

/**
 Populate a given parameter with the icon size for a specified bus name and session id.
 @param busName Unique or well-known name of AllJoyn bus.
 @param size The size of the icon [out].
 @param sessionId The session received  after joining AllJoyn session.
 @return ER_OK if successful.
 */
- (QStatus)sizeFromBusName:(NSString *)busName size:(size_t&)size sessionId:(AJNSessionId)sessionId __deprecated;

@end
