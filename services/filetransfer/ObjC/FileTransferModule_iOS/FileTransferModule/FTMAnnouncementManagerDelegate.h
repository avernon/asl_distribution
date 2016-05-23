/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
 * The FTMAnnouncementManagerDelegate is an internal delegate that is used by the
 * FTMReceiver to notify the FTMAnnouncementManager that various events have occurred.
 * 
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@protocol FTMAnnouncementManagerDelegate <NSObject>

@required

/** @name Required Methods */

/**
 * Triggered by the FTMReceiver when a normal announcement is received from a remote session peer.
 *
 * @param fileList Specifies the list of announced files.
 * @param peer Specifies the peer who sent the announcement.
 */
-(void)handleAnnouncedFiles: (NSArray *)fileList fromPeer: (NSString *)peer;

/**
 * Triggered by the FTMReceiver when an announcement request is received from a remote session peer.
 *
 * @param peer Specifies the peer that made the announcement request.
 */
-(void)handleAnnouncementRequestFrom: (NSString *)peer;

@end
