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

#import <SenTestingKit/SenTestingKit.h>
#import "AllJoynFrameWork/AJNBusAttachment.h"
#import "FTMFileTransferBusObject.h"
#import "FTMConstants.h"
#import "FTMTransmitter.h"
#import "AllJoynFrameWork/AJNSessionPortListener.h"
#import "AllJoynFrameWork/AJNInterfaceDescription.h"
#import "FTMFileDescriptor.h"

@interface FTMTransmitterTest : SenTestCase <AJNSessionPortListener, AJNSessionListener, AJNBusListener, FTMDirectedAnnouncementManagerDelegate, FTMSendManagerDelegate, FTMOfferManagerDelegate, DataTransferDelegateSignalHandler, FileDiscoveryDelegateSignalHandler>

-(void)setUp;
-(void)tearDown;
-(void)testRequestAnnouncement;
-(void)testStopDataXfer;
-(void)testDataChunk;
-(void)testDataXferCancelled;
-(void)testAnnouncement;
-(void)testRequestOffer;
-(void)testRequestData;
-(void)testOffer;

// From FileTransferBusObjectDelegateSignalHandler
-(void)didReceiveDataChunkWithFileID:(AJNMessageArgument*)fileID startByte:(NSNumber*)startByte length:(NSNumber*)chunkLength andFileChunk:(AJNMessageArgument*)chunk inSession:(AJNSessionId)sessionId fromSender:(NSString *)sender;
-(void)didReceiveStopDataXferWithFileID:(AJNMessageArgument*)fileID inSession:(AJNSessionId)sessionId fromSender:(NSString *)sender;
-(void)didReceiveDataXferCancelledWithFileID:(AJNMessageArgument*)fileID inSession:(AJNSessionId)sessionId fromSender:(NSString *)sender;
-(void)didReceiveAnnounceWithFileList:(AJNMessageArgument*)fileList andIsFileIDResponse:(BOOL)isFileIDResponse inSession:(AJNSessionId)sessionId fromSender:(NSString *)sender;
-(void)didReceiverequestAnnouncementInSession:(AJNSessionId)sessionId fromSender:(NSString *)sender;

@end
