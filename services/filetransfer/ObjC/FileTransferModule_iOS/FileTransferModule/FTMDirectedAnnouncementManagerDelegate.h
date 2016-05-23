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

@class FTCFileIDResponseAction;

/**
 * The FTMDirectedAnnouncementManagerDelegate is an internal delegate that is used by the
 * FTMFileTransferBusObject, FTMDispatcher, and FTMReceiver to notify the FTMDirectedAnnouncementManager
 * that various events have occurred. Such events include handling offer requests/responses and 
 * generating file descriptors when sending offer responses.
 * 
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@protocol FTMDirectedAnnouncementManagerDelegate <NSObject>

@required

/** @name Required Methods */

/**
 * Triggered by the FTMFileTransferBusObject to notify the FTMDirectedAnnouncementManager when a request for an unannounced file has been received.
 *
 * @param filePath Specifies the absolute path of the file being requested.
 * @param peer Specifies the peer requesting an unannounced file.
 *
 * @return FTMStatusCode FTMOK or FTMRequestDenied.
 */
-(int)handleOfferRequestForFile: (NSString *)filePath fromPeer: (NSString *)peer;

/**
 * Triggered by the FTMReceiver when an announcement signal is received that is in response to an offer request.
 *
 * @param fileList Specifies the list of announced files.
 * @param peer Specifies the peer that sent the directed announcement.
 */
-(void)handleOfferResponseForFiles: (NSArray *)fileList fromPeer: (NSString *)peer;

/**
 * Triggered by the FTMDispatcher to begin generating the file descriptor for a requested file.
 *
 * @param action Instance of FTMFileIDResponseAction.
 */
-(void)generateFileDescriptor: (FTCFileIDResponseAction *)action;

@end
