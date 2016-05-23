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
#import "FTMStatusCode.h"
#import "FTMAction.h"
#import "FTMDispatcher.h"
#import "FTMPermissionManager.h"
#import "FTMFileSystemAbstraction.h"
#import "FTMFileAnnouncementReceivedDelegate.h"
#import "FTMUnannouncedFileRequestDelegate.h"
#import "FTMDirectedAnnouncementManagerDelegate.h"

/**
 * The FTMDirectedAnnouncementManager is responsible for handling the events associated with 
 * requesting unannounced files from remote session peers. From the requesters perspective, 
 * the FTMDirectedAnnouncementManager is responsible for initiating requests and handling the 
 * responses to unannounced file requests from remote session peers. The FTMDirectedAnnouncementManager 
 * is also responsible for responding to the requests made by remote
 * session peers for unannounced files. The default behavior is to automatically
 * deny any and all requests for unannounced files. To enable this behavior, the
 * user must register the FTMUnannouncedFileRequestDelegate.
 *
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMDirectedAnnouncementManager : NSObject <FTMDirectedAnnouncementManagerDelegate>

/** @name Class Properties */

/**
 * Indicates whether the relative path is shown in the FTMFileDescriptor.
 *
 * By default, this property is set to true.
 *
 * @return True is the relative path is shown, false otherwise.
 */
@property (nonatomic, assign) BOOL showRelativePath;

/**
 * Indicates whether the shared path is shown in the FTMFileDescriptor.
 *
 * By default, this property is set to false.
 *
 * @return True is the shared path is shown, false otherwise.
 */
@property (nonatomic, assign) BOOL showSharedPath;

/**
 * Sets a delegate for the implementing class of the FTMFileAnnouncementReceivedDelegate protocol.
 *
 * The FTMFileAnnouncementReceivedDelegate will notify the receiving class when an announcment
 * has been received from a remote session peer.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMFileAnnouncementReceivedDelegate> fileAnnouncementReceivedDelegate;

/**
 * Sets a delegate for the implementing class of the FTMUnannouncedFileRequestDelegate protocol.
 *
 * The FTMUnannouncedFileRequestDelegate will notify the receiving class when a file request
 * has been received for an unannounced file from a remote session peer.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMUnannouncedFileRequestDelegate> unannouncedFileRequestDelegate;

/** @name Creating FTMDirectedAnnouncementManager */

/**
 * Constructs an instance of the FTMDirectedAnnouncementManager.
 *
 * @param dispatcher Instance of the FTMDispatcher.
 * @param permissionManager Instance of the FTMPermissionManager.
 * @param localBusID Specifies the Bus ID of the Bus Attachment passed in by the user.
 *
 * @return Instance of FTMDirectedAnnouncementManager.
 */
-(id)initWithDispatcher: (FTMDispatcher *)dispatcher permissionsManager: (FTMPermissionManager *)permissionManager andLocalBusID: (NSString *)localBusID;

/**
 * Constructs an instance of the FTMDirectedAnnouncementManager.
 *
 * @param dispatcher Instance of the FTMDispatcher.
 * @param permissionManager Instance of the FTMPermissionManager.
 * @param fsa Instance of FTMFileSystemAbstraction.
 * @param localBusID Specifies the Bus ID of the Bus Attachment passed in by the user.
 *
 * @return Instance of FTMDirectedAnnouncementManager.
 */
-(id)initWithDispatcher: (FTMDispatcher *)dispatcher permissionsManager: (FTMPermissionManager *)permissionManager fileSystemAbstraction: (FTMFileSystemAbstraction *)fsa andLocalBusID: (NSString *)localBusID;

/** @name Sending and Processing Offer Requests */

/**
 * Sends an offer request to specified peer for the specified file path.
 *
 * This function is called when the app wishes to request a file from the specified 
 * peer that has not been explicitly announced. This function will create a FTMRequestOffer
 * action that will ask the remote peer if they will offer the file with the specified path.
 * If the request is granted, the remote peer will send a directed announcement containing
 * the FTMFileDescriptor for the requested file, at which point the FTM will make a
 * request of the remote peer to transfer the file. Only files which reside in the remote
 * apps sandbox are available for transfer. Therefore the path of the specified file is
 * relative to the applications 'Home' folder.
 *
 * @warning *Note:* The default behavior is to deny requests for files that have not been
 * announced or shared. This behavior can only be changed by registering the
 * FTMUnannouncedFileRequestDelegate.
 *
 * @param peer Specifies the peer to which to send the offer request.
 * @param filePath Specifies the path (relative to the Home folder) of the file being requested.
 *
 * @return FTMStatusCode FTMOK or FTMRequestDenied.
 */
-(FTMStatusCode)requestOfferFromPeer: (NSString *)peer forFileWithPath: (NSString *)filePath;

/**
 * Processes the offer request made by a remote session peer.
 *
 * This function is called when a remote peer is attempting to request a file that has
 * not been announced or shared. He hopes that we will offer (announce) the file to him, 
 * at which point he will have the FileId, which he will use to explicitly request the file.
 * This function will first check to see if the specified
 * file path matches a file that has already been announced or shared. If a match is found, 
 * an announcement signal containing a single file descriptor will be sent to the remote 
 * peer. If a match is not found, the function will invoke the FTMUnannouncedFileRequestDelegate
 * to see if the app will accept the request, in which case an announcement signal containing
 * a single file descriptor will be sent to the remote peer.
 *
 * @warning *Note:* If the FTMUnannouncedFileRequestDelegate is not registered all offer requests 
 * will be denied by default.
 *
 * @param filePath Specifies the path (relative to the Home folder) of the file.
 * @param peer Specifies the peer who sent the offer request.
 *
 * @return FTMStatusCode FTMOK or FTMRequestDenied.
 */
-(FTMStatusCode)handleOfferRequestForFile: (NSString *)filePath fromPeer: (NSString *)peer;

/**
 * Processes the directed announcement in response to an offer request.
 *
 * This function passes the file list to the FTMPermissionManager to be
 * stored and, if available, notifies the user that a directed announcement has
 * been received.
 *
 * @param fileList Specifies the list of announced files.
 * @param peer Specifies the peer that sent the directed announcement.
 */
-(void)handleOfferResponseForFiles: (NSArray *)fileList fromPeer: (NSString *)peer;

/** @name Implementation of FTMDirectedAnnouncementManagerDelegate */

/**
 * Generates an FTMFileDescriptor using the provided FTMFileIDResponseAction.
 *
 * This is a callback method that is invoked when the Dispatcher encounters the FTMFileIDResponseAction
 * action. This function will build the file descriptor for the file with the specified path and insert 
 * an announce action, containing the newly created FTMFileDescriptor, into the FTMDispatcher. The 
 * announce signal with be directed to the specified peer.
 *
 * @param action Instance of FTMFileIDResponseAction.
 */
-(void)generateFileDescriptor: (FTMFileIDResponseAction *)action;

/** @name Reset State */

/**
 * Resets the state of the FTMDirectedAnnouncementManager with a new bus ID.
 *
 * This function is called by the FTMFileTransferComponent when the user specifies a new AllJoyn session
 * to be used.
 *
 * @warning *Note:* For the case where the user calls [FTMFileTransferModule uninitialize], the localBusID
 * parameter will be nil.
 *
 * @param localBusID Specified the bus ID of the new AllJoyn bus attachment. This value can be nil.
 */
-(void)resetStateWithLocalBusID: (NSString *)localBusID;

@end
