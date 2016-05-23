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

#import "FTMMockFileSystemAbstraction.h"
#import "FTMFileSystemAbstraction.h"
#import "FTMFileTransferModule.h"
#import "FTMMockPermissionsManager.h"

@implementation FTMMockFileSystemAbstraction 


-(NSData *)getChunkOfFileWithPath: (NSString *)path startingOffset: (NSInteger)startOffset andLength: (NSInteger)length
{
    NSMutableData * chunk = [[NSMutableData alloc]init];
    for (int i = 0; i < length; i++) {
        [chunk appendBytes:&i length:1];
    }
    
    return chunk;
}

-(BOOL)isValidPath: (NSString *)path
{
    NSCharacterSet *invalidSet = [NSCharacterSet characterSetWithCharactersInString:@"\0"];
    
    NSRange r = [path rangeOfCharacterFromSet:invalidSet];
    if (r.location != NSNotFound)
    {
        NSLog(@"the path contains illegal characters");
        return NO;
    }
    else
    {
        return YES;
    }
}

-(int)deleteFileWithPath: (NSString *)path
{
    return 0;
}

-(void)addChunkOfFileWithPath: (NSString *)path withData: (NSData *)chunk startingOffset: (NSInteger)startOffset andLength: (NSInteger)length
{
    // Do nothing
}


-(NSArray *)getFileInfo: (NSArray *)pathList withFailedPathsArray: (NSMutableArray *)failedPaths andLocalBusID: (NSString *)localBusID
{
    if ([localBusID isEqualToString: @"AnnouncementManagerUnitTests"])
    {
        [failedPaths addObject: @"invalid_path"];
        [failedPaths addObject: @"invalid_path"];
        [failedPaths addObject: @"invalid_path"];
        [failedPaths addObject: @"invalid_path"];
        
        return [self generateDummyDescriptorArrayUsingLocalBusID: localBusID];
    }
    else
    {
        NSMutableArray *fileList = [[NSMutableArray alloc] init];
        
        for (NSString *path in pathList)
        {
            FTMMockPermissionsManager *pm = [[FTMMockPermissionsManager alloc] init];
            FTMFileDescriptor *descriptor = pm.getUnitTestDummyFileDescriptor;
            descriptor.owner = localBusID;
            
            [fileList addObject: [[FTMFileDescriptor alloc] initWithFileDescriptor: descriptor]];
        }
        
        return [fileList copy];
    }
}

-(NSArray *)generateDummyDescriptorArrayUsingLocalBusID: (NSString *)localBusID
{
    NSMutableArray * fileList = [[NSMutableArray alloc] init];
    
    const unsigned char chunkData1[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
    NSData *fileID = [[NSData alloc] initWithBytes: chunkData1 length: 20];
    FTMFileDescriptor *descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/photos";
    descriptor.relativePath = @"";
    descriptor.filename = @"house.png";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    const unsigned char chunkData2[] = { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 };
    fileID = [[NSData alloc] initWithBytes: chunkData2 length: 20];
    descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/photos";
    descriptor.relativePath = @"";
    descriptor.filename = @"backyard.png";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    const unsigned char chunkData3[] = { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 };
    fileID = [[NSData alloc] initWithBytes: chunkData3 length: 20];
    descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/photos";
    descriptor.relativePath = @"";
    descriptor.filename = @"fireplace.png";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    const unsigned char chunkData4[] = { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 };
    fileID = [[NSData alloc] initWithBytes: chunkData4 length: 20];
    descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/reports";
    descriptor.relativePath = @"";
    descriptor.filename = @"animals.txt";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    const unsigned char chunkData5[] = { 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05 };
    fileID = [[NSData alloc] initWithBytes: chunkData5 length: 20];
    descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/reports";
    descriptor.relativePath = @"";
    descriptor.filename = @"inventors.txt";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    const unsigned char chunkData6[] = { 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 };
    fileID = [[NSData alloc] initWithBytes: chunkData6 length: 20];
    descriptor = [[FTMFileDescriptor alloc] init];
    descriptor.owner = localBusID;
    descriptor.fileID = fileID;
    descriptor.sharedPath = @"/sdcard/reports";
    descriptor.relativePath = @"";
    descriptor.filename = @"driving.txt";
    descriptor.size = 1024;
    [fileList addObject: descriptor];
    
    return [[NSArray alloc] initWithArray: fileList];
}


@end
