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
#import "AllJoynFramework/AJNBusObject.h"
#import "AllJoynFramework/AJNBusAttachment.h"
#import "FTMStatusCode.h"
#import "FTMAction.h"
#import "FTMSendManagerDelegate.h"
#import "FTMDirectedAnnouncementManagerDelegate.h"
#import "FileTransferBusObject.h"
#import "FTMTransmitter.h"

/**
 * The FTMDispatcher's main job is to run in the background and provide a service queue 
 * to process all of the actions. Each action will usually correspond to an AllJoyn signal
 * or method call. The FTMDispatcher ensures that all actions are serviced in the order 
 * received and does not block or inhibit the application in any way. Additionally, the 
 * FTMDispatcher provides a method that bypasses the Dispatcher queue so alljoyn method 
 * calls can be transmitted immediately. This is only done for alljoyn method calls and 
 * not for alljoyn signals.
 *
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMDispatcher : NSObject

/** @name Class Properties */

/**
 * Sets a delegate so the FTMDispatcher can callback to the FTMSendManager.
 *
 * The FTMSendManagerDelegate will notify the FTMSendManager when an FTMDataChunkAction is
 * encountered and the FTMSendManager should queue the next file chunk.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMSendManagerDelegate> sendManagerDelegate;

/**
 * Sets a delegate so the FTMDispatcher can callback to the FTMDirectedAnnouncementManager.
 *
 * The FTMDirectedAnnouncementManagerDelegate will notify the FTMDirectedAnnouncementManager when an 
 * FTMFileIDResponseAction is encountered and the FTMDirectedAnnouncementManager should generate the
 * FTMFileDescriptor for an unannounced file.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMDirectedAnnouncementManagerDelegate> directedAnnouncementManagerDelegate;

/** @name Creating FTMDispatcher */

/**
 * Constructs an instance of the FTMDispatcher.
 *
 * @param busObject Instance of the FTMFileTransferBusObject.
 * @param busAttachment Specifies the AllJoyn bus attachment.
 * @param sessionID Specifies the ID of the active AllJoyn session.
 *
 * @return Instance of FTMDispatcher.
 */
-(id)initWithBusObject: (FTMFileTransferBusObject *)busObject busAttachment: (AJNBusAttachment *)busAttachment andSessionID: (AJNSessionId)sessionID;

/**
 * Constructs an instance of the FTMDispatcher.
 *
 * @param transmitter Instance of FTMTransmitter.
 *
 * @return Instance of FTMDispatcher.
 */
-(id)initWithTransmitter: (FTMTransmitter *)transmitter;

/** @name Transmitting Actions */

/**
 * Inserts the action parameter into the FTMDispatcher queue for processing.
 *
 * @param action Specifies the action to be inserted in the queue.
 */
-(void)insertAction: (FTMAction *)action;

/**
 * Transmits the specified action immediately.
 *
 * This function bypasses the dispatcher queue and sends the action over AllJoyn immediately. 
 * This function is used for high priority messages (i.e. alljoyn method calls).
 *
 * @param action Specifies the action to be transmitted immediately.
 *
 * @return FTMStatusCode FTMInvalid if transmit failed, FTMStatusCode of completed action otherwise.
 */
-(FTMStatusCode)transmitImmediately: (FTMAction *)action;

/** @name Reset State */

/**
 * Resets the state of the FTMDispatcher.
 *
 * This function is called by the FTMFileTransferModule when the user specifies a new AllJoyn session
 * to be used. This function is passed a new bus object, AllJoyn bus attachment, and session ID.
 *
 * @param busObject Instance of the FTMFileTransferBusObject.
 * @param busAttachment Specifies the AllJoyn bus attachment.
 * @param sessionID Specifies the ID of the active AllJoyn session.
 */
-(void)resetStateWithBusObject: (FTMFileTransferBusObject *)busObject busAttachment: (AJNBusAttachment *)busAttachment andSessionID: (AJNSessionId)sessionID;

@end