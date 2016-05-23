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
#import "AllJoynFramework/AJNBusObject.h"
#import "AllJoynFramework/AJNMessageArgument.h"
#import "FTMConstants.h"
#import "FTMFileTransferBusObject.h"
#import "FTMAction.h"
#import "FTMStatusCode.h"
#import "FTMFileDescriptor.h"
#import "FTMMessageUtility.h"

/**
 * The FTMTransmitter class is a major piece of the FTMFileTransferModule and is
 * responsible for direct communication with AllJoyn session peers. The FTMTransmitter
 * is responsible for sending directed and broadcast signals to the various session
 * peers as well as calling the appropriate AllJoyn methods on the proxy bus objects.
 * Furthermore, this module is the driving force behind communicating with peers
 * within your AllJoyn session.
 *
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMTransmitter : NSObject

/** @name Creating FTMTransmitter */

/**
 * Constructs an instance of the FTMTransmitter.
 *
 * @param busObject Instance of the FTMFileTransferBusObject.
 * @param busAttachment Instance of an AllJoyn bus attachment.
 * @param sessionID Specifies the ID of the active AllJoyn session.
 *
 * @return Instance of FTMTransmitter.
 */
-(id)initWithBusObject: (FTMFileTransferBusObject *)busObject busAttachment: (AJNBusAttachment *)busAttachment andSessionID: (AJNSessionId)sessionID;

/** @name AllJoyn Communication */

/**
 * Sends an announcement with the specified file list to the provided peer.
 *
 * The fileList is an Array of FTMFileDescriptor objects and represents the announced files
 * that are sent to remote session peers. Generally, the peer parameter is nil and causes a
 * global announce signal to be sent to all session peer.
 *
 * @param fileList Array of FTMFileDescriptor objects.
 * @param peer Specifies the peer to receive the announcement.
 * @param isFileIDResponse Specifies whether the announcement is in response to an offer request.
 *
 * @return FTMStatusCode FTMOK.
 */
-(FTMStatusCode)sendAnnouncementWithFileList: (NSArray *)fileList toPeer: (NSString *)peer andIsFileIDResponse: (BOOL)isFileIDResponse;

/**
 * Requests the file matching the specified file ID from the provided peer.
 *
 * @param fileID Specifies the ID of the file being requested.
 * @param startByte Specifies the starting position within the file (usually zero).
 * @param length Specifies the number of bytes to be sent (usually the length of the file).
 * @param maxChunkSize Specifies the maximum file chunk size.
 * @param peer Specifies the owner of the file.
 *
 * @return FTMStatusCode FTMOK or FTMBadFileID.
 */
-(FTMStatusCode)sendRequestDataUsingFileID: (NSData *)fileID startByte: (int)startByte length: (int)length andMaxChunkSize: (int)maxChunkSize toPeer: (NSString *)peer;

/**
 * Sends the file chunk to the specified peer.
 *
 * @param fileID Specifies the ID of the file being sent.
 * @param startByte Specifies the starting position within the file.
 * @param chunkLength Specifies the number of bytes in the chunk.
 * @param chunk File data.
 * @param peer Specifies the receiver of the file chunk.
 *
 * @return FTMStatusCode FTMOK.
 */
-(FTMStatusCode)sendDataChunkUsingFileID: (NSData *)fileID startByte: (int)startByte chunkLength: (int)chunkLength andFileData: (NSData *)chunk toPeer: (NSString *)peer;

/**
 * Offers the given file to the specified peer.
 *
 * @param fd Specifies the FTMFileDescriptor of the file being offered.
 * @param peer Specifies the peer to receive the offer.
 *
 * @return FTMStatusCode FTMOK, FTMBadFileID, FTMOfferRejected, or FTMOfferTimeout.
 */
-(FTMStatusCode)sendOfferFileWithFileDescriptor: (FTMFileDescriptor *)fd toPeer: (NSString *)peer;

/**
 * Sends an announcement request to the specified peer.
 *
 * @param peer Specifies the peer to receive the announcement request.
 *
 * @return FTMStatusCode FTMOK.
 */
-(FTMStatusCode)sendAnnouncementRequestToPeer: (NSString *)peer;

/**
 * Sends the stop data xfer signal to the specified peer for the provided file ID.
 *
 * @param fileID Specifies the ID of the file being transferred.
 * @param peer Specifies the peer sending the file.
 *
 * @return FTMStatusCode FTMOK.
 */
-(FTMStatusCode)sendStopDataXferForFileID: (NSData *)fileID toPeer: (NSString *)peer;

/**
 * Sends the xfer cancelled signal to specified file receiver.
 * 
 * @param fileID Specifies the ID of the file being transferred.
 * @param peer Specifies the peer receiving the file.
 *
 * @return FTMStatusCode FTMOK.
 */
-(FTMStatusCode)sendXferCancelledForFileID: (NSData *)fileID toPeer: (NSString *)peer;

/**
 * Sends an offer request to the specified peer for the file at the provided path.
 *
 * @param filePath Specifies the absolute path of the file being requested.
 * @param peer Specifies the owner of the file.
 *
 * @return FTMStatusCode FTMOK or FTMRequestDenied.
 */
-(FTMStatusCode)sendRequestOfferForFileWithPath: (NSString *)filePath toPeer: (NSString *)peer;

@end
