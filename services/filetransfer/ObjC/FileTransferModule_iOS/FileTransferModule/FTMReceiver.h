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
#import "AllJoynFramework/AJNBusAttachment.h"
#import "FTMAnnouncementManagerDelegate.h"
#import "FTMReceiveManagerDelegate.h"
#import "FTMSendManagerDelegate.h"
#import "FTMDirectedAnnouncementManagerDelegate.h"
#import "FTMFileTransferBusObject.h"
#import "FTMMessageUtility.h"

/**
 * The FTMReceiver is the main handler for AllJoyn signals. Every AllJoyn signal is handled
 * in this class and then calls functions in other classes to initiate any responses that
 * are needed. Some of the main operations include: handling announcements from other peers,
 * handling announcement requests from other peers, processing file chunks, and handling
 * sender and receiver initiated transfer cancellations. The receiver is the driving force
 * behind handling all incoming signals from AllJoyn session peers.
 * 
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMReceiver : NSObject <DataTransferDelegateSignalHandler, FileDiscoveryDelegateSignalHandler>

/** @name Creating FTMReceiver */

/**
 * Constructs an instance of the FTMReceiver.
 *
 * @param busAttachment Instance of an AllJoyn bus attachment.
 * @param amDelegate Instance of FTMAnnouncementManagerDelegate.
 * @param smDelegate Instance of FTMSendManagerDelegate.
 * @param rmDelegate Instance of FTMReceiveManagerDelegate.
 * @param damDelegate Instance of FTMDirectedAnnouncementManagerDelegate.
 *
 * @return Instance of FTMReceiver.
 */
-(id)initWithBusAttachment: (AJNBusAttachment *)busAttachment announcementManagerDelegate: (id<FTMAnnouncementManagerDelegate>)amDelegate sendManagerDelegate: (id<FTMSendManagerDelegate>)smDelegate receiveManagerDelegate: (id<FTMReceiveManagerDelegate>)rmDelegate andDirectedAnnouncementManagerDelegate: (id<FTMDirectedAnnouncementManagerDelegate>)damDelegate;

/** @name Initialize FTMReceiver */

/**
 * Initializes the local variables of the FTMReceiver.
 *
 * This function is called by the init method and the resetState method.
 *
 * @param busAttachment Instance of an AllJoyn bus attachment.
 * @param amDelegate Instance of FTMAnnouncementManagerDelegate.
 * @param smDelegate Instance of FTMSendManagerDelegate.
 * @param rmDelegate Instance of FTMReceiveManagerDelegate.
 * @param damDelegate Instance of FTMDirectedAnnouncementManagerDelegate.
 */
-(void)initializeReceiverWithBusAttachment: (AJNBusAttachment *)busAttachment announcementManagerDelegate: (id<FTMAnnouncementManagerDelegate>)amDelegate sendManagerDelegate: (id<FTMSendManagerDelegate>)smDelegate receiveManagerDelegate: (id<FTMReceiveManagerDelegate>)rmDelegate andDirectedAnnouncementManagerDelegate: (id<FTMDirectedAnnouncementManagerDelegate>)damDelegate;

/** @name Reset State */

/**
 * Resets the state of the FTMReceiver to reinitialize the local variables.
 *
 * This function is called by the FTMFileTransferModule when the user specifies a new AllJoyn session
 * to be used.
 *
 * @param busAttachment Instance of an AllJoyn bus attachment.
 * @param amDelegate Instance of FTMAnnouncementManagerDelegate.
 * @param smDelegate Instance of FTMSendManagerDelegate.
 * @param rmDelegate Instance of FTMReceiveManagerDelegate.
 * @param damDelegate Instance of FTMDirectedAnnouncementManagerDelegate.
 */
-(void)resetStateWithBusAttachment: (AJNBusAttachment *)busAttachment announcementManagerDelegate: (id<FTMAnnouncementManagerDelegate>)amDelegate sendManagerDelegate: (id<FTMSendManagerDelegate>)smDelegate receiveManagerDelegate: (id<FTMReceiveManagerDelegate>)rmDelegate andDirectedAnnouncementManagerDelegate: (id<FTMDirectedAnnouncementManagerDelegate>)damDelegate;

@end
