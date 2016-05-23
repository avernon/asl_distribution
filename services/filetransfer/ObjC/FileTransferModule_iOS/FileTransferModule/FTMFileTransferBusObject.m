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

#import "FTMFileTransferBusObject.h"

@implementation FTMFileTransferBusObject

- (NSNumber*)requestDataWithFileID:(AJNMessageArgument*)fileID startByte:(NSNumber*)startByte length:(NSNumber*)length andMaxChunkLength:(NSNumber*)maxChunkLength fromSender:(NSString *)sender
{
    NSLog(@"received request data from: %@", sender);
    
    NSData *fileIDData = [FTMMessageUtility fileIDFromMessageArgument: fileID];
    int receivedStartByte = [startByte intValue];
    int receivedLength = [length intValue];
    int receivedMaxChunkLength = [maxChunkLength intValue];
    
    FTMStatusCode returnValue = FTMInvalid;
    
    if (self.offerManagerDelegate != nil && [self.offerManagerDelegate isOfferPendingForFileWithID:fileIDData])
    {
        returnValue = [self.offerManagerDelegate handleRequestFrom:sender forFileID:fileIDData usingStartByte: receivedStartByte withLength: receivedLength andMaxChunkLength: receivedMaxChunkLength];
    }
    else if (self.sendManagerDelegate != nil)
    {
        returnValue = [self.sendManagerDelegate sendFileWithID: fileIDData withStartByte: receivedStartByte andLength: receivedLength andMaxChunkLength: receivedMaxChunkLength toPeer: sender];
    }
    return [NSNumber numberWithInt: returnValue];
}

- (NSNumber*)requestOfferWithFilePath:(NSString*)filePath fromSender:(NSString *)sender
{
    NSLog(@"received request offer from: %@", sender);
    
    FTMStatusCode returnValue = FTMInvalid;
    
    if (self.directedAnnouncementManagerDelegate != nil)
    {
        returnValue = [self.directedAnnouncementManagerDelegate handleOfferRequestForFile:filePath fromPeer:sender];
    }
    return [NSNumber numberWithInt: returnValue];
}

- (NSNumber*)offerFileWithFileDescriptor:(AJNMessageArgument*)file fromSender:(NSString *)sender
{
    NSLog(@"received offer from: %@", sender);
    
    FTMFileDescriptor *descriptor = [FTMMessageUtility descriptorFromMessageArgument: file];
    
    FTMStatusCode returnValue = FTMInvalid;
    
    if (self.offerManagerDelegate != nil)
    {
        returnValue = [self.offerManagerDelegate handleOfferFrom:sender forFile:descriptor];
    }
    return [NSNumber numberWithInt: returnValue];
}

@end
