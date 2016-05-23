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
#import "AJNBusObject.h"

/**
 AJNAboutIconService is an AJNBusObject that implements the org.alljoyn.Icon standard interface.
 Applications that provide AllJoyn IoE services to receive info about the Icon of the service.
 */
__deprecated
@interface AJNAboutIconService : AJNBusObject

/**
 Designated initializer
 Create an AJNAboutIconService Object using the passed parameters.
 @param bus A reference to the AJNBusAttachment.
 @param mimetype The mimetype of the icon.
 @param url The url of the icon.
 @param content The content of the icon.
 @param csize The size of the content in bytes.
 @return AJNAboutIconService if successful.
 */
- (id)initWithBus:(AJNBusAttachment *)bus mimeType:(NSString *)mimetype url:(NSString *)url content:(uint8_t *)content csize:(size_t)csize __deprecated;

/**
 Register the AJNAboutIconService  on the AllJoyn bus.
 @return ER_OK if successful.
 */
- (QStatus)registerAboutIconService __deprecated;

@end
