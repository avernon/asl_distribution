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

#import "FTMOfferManagerTests.h"
#import "FTMOfferManager.h"
#import "FTMSendManager.h"
#import "FTMReceiveManager.h"
#import "FTMOfferReceivedDelegate.h"
#import "FTMMockDispatcher.h"
#import "FTMMockFileSystemAbstraction.h"
#import "FTMMockPermissionsManager.h"



// Note that these tests are time-sensitive. Stepping thru them in the debugger
// may result in inconsistent behavior.
static int DEFAULT_TIMEOUT_MILLIS = 5000;

@interface FTMOfferManagerTests()

@property (nonatomic, strong) FTMMockDispatcher *ftcDispatcher;
@property (nonatomic, strong) FTMMockFileSystemAbstraction *ftcFileSystemAbstraction;
@property (nonatomic, strong) FTMMockPermissionsManager *ftcPermissionManager;
@property (nonatomic, strong) FTMSendManager *ftcSendManager;
@property (nonatomic, strong) FTMReceiveManager *ftcReceiveManager;
@property (nonatomic, strong) FTMOfferManager *ftcOfferManager;
@property (nonatomic, strong) NSData *fileID;
@property (nonatomic, strong) NSString *peer;
@property (nonatomic, strong) NSString *fileWithPath;

@end


@implementation FTMOfferManagerTests

@synthesize ftcDispatcher = _ftcDispatcher;
@synthesize ftcFileSystemAbstraction = _ftcFileSystemAbstraction;
@synthesize ftcPermissionManager = _ftcPermissionManager;
@synthesize ftcSendManager = _ftcSendManager;
@synthesize ftcReceiveManager = _ftcReceiveManager;
@synthesize ftcOfferManager = _ftcOfferManager;
@synthesize fileID = _fileID;
@synthesize peer = _peer;
@synthesize fileWithPath = _fileWithPath;


- (void)setUp
{
    [super setUp];
    
    // now initialize Dispatcher, FSA, etc
    self.ftcPermissionManager = [[FTMMockPermissionsManager alloc] init];
    self.ftcFileSystemAbstraction = [[FTMMockFileSystemAbstraction alloc] init];
    self.ftcDispatcher = [[FTMMockDispatcher alloc] init];
    self.ftcSendManager = [[FTMSendManager alloc] initWithDispatcher:self.ftcDispatcher fileSystemAbstraction:self.ftcFileSystemAbstraction andPermnissionManager:self.ftcPermissionManager];
    self.ftcReceiveManager = [[FTMReceiveManager alloc] initWithDispatcher:self.ftcDispatcher fileSystemAbstraction:self.ftcFileSystemAbstraction andPermissionManager:self.ftcPermissionManager];
    
    self.ftcOfferManager = [[FTMOfferManager alloc]initWithDispatcher:self.ftcDispatcher permissionManager:self.ftcPermissionManager fileSystemAbstraction:self.ftcFileSystemAbstraction andLocalBusID:nil];
    
    self.ftcOfferManager.sendManagerDelegate = self.ftcSendManager;
    self.ftcOfferManager.receiveManagerDelegate = self.ftcReceiveManager;
    self.ftcOfferManager.offerReceivedDelegate  = self;
    
    FTMFileDescriptor *fileDescriptor = self.ftcPermissionManager.getUnitTestDummyFileDescriptor;
    self.fileID = fileDescriptor.fileID;
    self.peer = fileDescriptor.owner;
    self.fileWithPath = [self.ftcFileSystemAbstraction buildPathFromDescriptor:fileDescriptor];
    self.ftcDispatcher.callerIs = @"OfferManagerTests";
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testOfferFileToPeer
{
    // Offer a file to peer, then timeout.
    
    // finesse the dispatcher to return what we want in this instance. The offer is accepted,
    // but the peer doesn't get around to requesting the file before we time out.
    self.ftcDispatcher.statusCodeToReturn = FTMOfferAccepted;
    
    //Create a descriptor array with your dummy descriptor
    FTMFileDescriptor *fileDescriptor = self.ftcPermissionManager.getUnitTestDummyFileDescriptor;
    NSMutableArray *fdArray = [[NSMutableArray alloc] init];
    [fdArray insertObject:fileDescriptor atIndex:0];
    [self.ftcPermissionManager addAnnouncedLocalFilesWithList: fdArray];

    FTMStatusCode statusCode = [self.ftcOfferManager offerFileToPeer:self.peer forFileWithPath:self.fileWithPath andTimeout:DEFAULT_TIMEOUT_MILLIS];
    STAssertTrue(statusCode == FTMOfferTimeout, @"offerFileToPeer");
    BOOL result = [self.ftcOfferManager isOfferPendingForFileWithID:self.fileID];
    STAssertTrue(result == NO, @"isOfferPendingForFileWithID");
}

-(void)testHandleRequestFrom
{
    FTMStatusCode statusCode;
    int startByte = 0;
    int length = 100;
    int maxChunkLength = 1024;
    
    NSThread *offerFileToPeerThread;
    offerFileToPeerThread = [[NSThread alloc] initWithTarget:self selector:@selector(offerFileToPeerThreadWorker) object:nil];
    [offerFileToPeerThread start];
    
    // give the worker thread time to make the offer
    [self waitForCompletion:2];
    
    // before worker thread has a chance to timeout, pretend that we received a request for the file
    statusCode = [self.ftcOfferManager handleRequestFrom: self.peer forFileID: self.fileID usingStartByte: startByte withLength: length andMaxChunkLength: maxChunkLength];
    // there is no sendManager delegate in this case, so request denied
    STAssertTrue(statusCode == FTMOK, @"handleRequestFrom");

}

-(void)offerFileToPeerThreadWorker
{
    FTMStatusCode statusCode;
    
    // finesse the dispatcher to return what we want in this instance...
    self.ftcDispatcher.statusCodeToReturn = FTMOfferAccepted;

    // offer file to peer and wait for him to request it
    statusCode = [self.ftcOfferManager offerFileToPeer:self.peer forFileWithPath:self.fileWithPath andTimeout:DEFAULT_TIMEOUT_MILLIS];
    STAssertTrue(statusCode == FTMOK, @"worker thread:offerFileToPeer");
    
    // now that peer has requested our offered file, the offer is no longer pending
    BOOL result = [self.ftcOfferManager isOfferPendingForFileWithID:self.fileID];
    STAssertTrue(result == NO, @"isOfferPendingForFileWithID");
}


-(void)testHandleOfferFrom
{
    FTMStatusCode statusCode = FTMOfferRejected;
    
    // Handle an offer when we have a registered listener
    FTMFileDescriptor *fileDescriptor = [self.ftcPermissionManager getUnitTestDummyFileDescriptor];
    
    
    statusCode = [self.ftcOfferManager handleOfferFrom: self.peer forFile: fileDescriptor];
    STAssertTrue(statusCode == FTMOfferAccepted, @"handleOfferFrom");
    
    // Handle an offer when we DO NOT have a registered listener
    self.ftcOfferManager.offerReceivedDelegate  = nil;
    statusCode = [self.ftcOfferManager handleOfferFrom: self.peer forFile: fileDescriptor];
    STAssertTrue(statusCode == FTMOfferRejected, @"handleOfferFrom");

}


//Helper Methods
-(void)waitForCompletion: (NSTimeInterval)timeoutSeconds
{
    NSCondition *condition = [[NSCondition alloc] init];
    
    if (timeoutSeconds > 0)
    {
        [condition waitUntilDate:[NSDate dateWithTimeIntervalSinceNow:(timeoutSeconds)]];
    }
}


-(BOOL)acceptFileOfferFrom: (NSString *)peer forFile: (FTMFileDescriptor *)file
{
    return YES;
}


@end

