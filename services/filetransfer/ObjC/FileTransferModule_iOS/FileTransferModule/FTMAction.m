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

#import "FTMAction.h"

@implementation FTMAction

@synthesize peer = _peer;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return FTMOK;
}

@end

@implementation FTMAnnounceAction

@synthesize fileList = _fileList;
@synthesize isFileIDResponse = _isFileIDResponse;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendAnnouncementWithFileList: self.fileList toPeer: self.peer andIsFileIDResponse: self.isFileIDResponse];
}

@end

@implementation FTMRequestDataAction

@synthesize fileID = _fileID;
@synthesize startByte = _startByte;
@synthesize length = _length;
@synthesize maxChunkSize = _maxChunkSize;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendRequestDataUsingFileID: self.fileID startByte: self.startByte length: self.length andMaxChunkSize: self.maxChunkSize toPeer: self.peer];
}

@end

@implementation FTMDataChunkAction

@synthesize fileID = _fileID;
@synthesize startByte = _startByte;
@synthesize chunkLength = _chunkLength;
@synthesize chunk = _chunk;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendDataChunkUsingFileID: self.fileID startByte: self.startByte chunkLength: self.chunkLength andFileData: self.chunk toPeer: self.peer];
}

@end

@implementation FTMOfferFileAction

@synthesize fd = _fd;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendOfferFileWithFileDescriptor: self.fd toPeer: self.peer];
}

@end

@implementation FTMRequestAnnouncementAction

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendAnnouncementRequestToPeer: self.peer];
}

@end

@implementation FTMStopXferAction

@synthesize fileID = _fileID;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendStopDataXferForFileID: self.fileID toPeer: self.peer];
}

@end

@implementation FTMXferCancelledAction

@synthesize fileID = _fileID;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendXferCancelledForFileID: self.fileID toPeer: self.peer];
}

@end

@implementation FTMRequestOfferAction

@synthesize filePath = _filePath;

-(FTMStatusCode)transmitActionWithTransmitter: (FTMTransmitter *)transmitter
{
    return [transmitter sendRequestOfferForFileWithPath: self.filePath toPeer: self.peer];
}

@end

@implementation FTMFileIDResponseAction

@synthesize filePath = _filePath;

@end



