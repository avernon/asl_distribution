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

#import "FTMMockTransmitter.h"

@implementation FTMMockTransmitter

@synthesize delegate = _delegate;
@synthesize statusCodeToReturn = _statusCodeToReturn;

-(FTMStatusCode)sendAnnouncementWithFileList: (NSArray *)fileList toPeer: (NSString *)peer andIsFileIDResponse: (BOOL)isFileIDResponse
{
    [self.delegate sendAnnouncementWithFileList: fileList toPeer: peer andIsFileIDResponse: isFileIDResponse];
    return FTMOK;
}

-(FTMStatusCode)sendRequestDataUsingFileID: (NSData *)fileID startByte: (int)startByte length: (int)length andMaxChunkSize: (int)maxChunkSize toPeer: (NSString *)peer
{
    [self.delegate sendRequestDataUsingFileID: fileID startByte: startByte length: length andMaxChunkSize: maxChunkSize toPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendDataChunkUsingFileID: (NSData *)fileID startByte: (int)startByte chunkLength: (int)chunkLength andFileData: (NSData *)chunk toPeer: (NSString *)peer
{
    [self.delegate sendDataChunkUsingFileID: fileID startByte: startByte chunkLength: chunkLength andFileData: chunk toPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendOfferFileWithFileDescriptor: (FTMFileDescriptor *)fd toPeer: (NSString *)peer
{
    [self.delegate sendOfferFileWithFileDescriptor: fd toPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendAnnouncementRequestToPeer: (NSString *)peer
{
    [self.delegate sendAnnouncementRequestToPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendStopDataXferForFileID: (NSData *)fileID toPeer: (NSString *)peer
{
    [self.delegate sendStopDataXferForFileID: fileID toPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendXferCancelledForFileID: (NSData *)fileID toPeer: (NSString *)peer
{
    [self.delegate sendXferCancelledForFileID: fileID toPeer: peer];
    return FTMOK;
}

-(FTMStatusCode)sendRequestOfferForFileWithPath: (NSString *)filePath toPeer: (NSString *)peer
{
    [self.delegate sendRequestOfferForFileWithPath: filePath toPeer: peer];
    return self.statusCodeToReturn;
}

@end
