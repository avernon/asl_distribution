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
 * The FTMFileAnnouncementReceivedDelegate can be utilized so the developer is notified
 * that an array of announced files has been received from a session peer. This delegate
 * is entirely optional but is necessary if the developer wishes to be able to send 
 * announcement requests to session peers.
 * 
 * See [FTMFileTransferModule setFileAnnouncementReceivedDelegate:].
 */
@protocol FTMFileAnnouncementReceivedDelegate <NSObject>

@required

/** @name Required Methods */

/**
 * Triggered when an announcement is received and notifies the user which files are now available for transfer.
 *
 * @param fileList Array of files available for transfer.
 * @param isFileIDResponse Indicates whether the announcement received is in response to an offer request.
 */
-(void)receivedAnnouncementForFiles: (NSArray *)fileList andIsFileIDResponse: (BOOL)isFileIDResponse;

@end
