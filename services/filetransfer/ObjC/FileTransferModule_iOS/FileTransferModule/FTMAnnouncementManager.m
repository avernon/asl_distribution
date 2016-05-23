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

#import "FTMAnnouncementManager.h"

@interface FTMAnnouncementManager()

/*
 * Stores an instance of the FTMDispatcher.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) FTMDispatcher *dispatcher;

/*
 * Stores an instance of the FTMPermissionManager.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) FTMPermissionManager *pm;

/*
 * Stores an instance of the FTMFileSystemAbstraction.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) FTMFileSystemAbstraction *fsa;

/*
 * Stores the local bus ID.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) NSString *localBusID;

/*
 * Specifies a generic object used for thread synchronization. This object is used in the
 * set method of the fileAnnouncementReceivedDeleagte.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) NSObject *fileAnnouncementReceivedDelegateLock;

/*
 * Specifies a generic object used for thread synchronization. This object is used in the
 * set method of the fileAnnouncementSentDeleagte.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) NSObject *fileAnnouncementSentDelegateLock;

/*
 * Private helper function that executes in a background thread and is responsible for delegating
 * to the FTMFileSystemAbstraction to create the FTMFileDescriptor for each file, invoking the 
 * FTMPermissionManager to store the newly announced files, and sending the announcement. If available,
 * this function will fire the fileAnnouncementSentDelegate to notify the user that an announcement
 * has been sent and pass back an array of paths that failed to be announced.
 *
 * @param pathList Specfies an array of absolute paths of files to be announced.
 *
 * @warning *Note:* This is a private function and is not meant to be called directly.
 */
-(void)announceFiles: (NSArray *)pathList;

/*
 * Private helper function that prepares an FTMAnnounceAction to be sent to the specified peer. If
 * peer is nil, the announcement is broadcast to all session peers. Otherwise, the signal is directed
 * to the specified peer.
 *
 * @param peer Specifies the peer to send the announcement. This value can be nil.
 * @param isFileIDResponse Specifies whether the announcement is a response to a file offer request.
 *
 * @warning *Note:* This is a private function and is not meant to be called directly.
 */
-(void)sendAnnouncementToPeer: (NSString *)peer isFileIDResponse: (BOOL)isFileIDResponse;

@end

@implementation FTMAnnouncementManager

@synthesize showRelativePath = _showRelativePath;
@synthesize showSharedPath = _showSharedPath;
@synthesize dispatcher = _dispatcher;
@synthesize pm = _pm;
@synthesize fsa = _fsa;
@synthesize localBusID = _localBusID;
@synthesize fileAnnouncementReceivedDelegateLock = _fileAnnouncementReceivedDelegateLock;
@synthesize fileAnnouncementSentDelegateLock = _fileAnnouncementSentDelegateLock;

-(id)initWithDispatcher: (FTMDispatcher *)dispatcher permissionsManager: (FTMPermissionManager *)permissionManager andLocalBusID: (NSString *)localBusID
{
	return [self initWithDispatcher: dispatcher permissionsManager: permissionManager fileSystemAbstraction: [FTMFileSystemAbstraction instance] andLocalBusID: localBusID];
}

-(id)initWithDispatcher: (FTMDispatcher *)dispatcher permissionsManager: (FTMPermissionManager *)permissionManager fileSystemAbstraction: (FTMFileSystemAbstraction *)fsa andLocalBusID: (NSString *)localBusID
{
    self = [super init];
	
	if (self)
    {
		self.showRelativePath = YES;
		self.showSharedPath = NO;
		self.dispatcher = dispatcher;
        self.pm = permissionManager;
        self.fsa = fsa;
        self.localBusID = localBusID;
        self.fileAnnouncementReceivedDelegateLock = [[NSObject alloc] init];
        self.fileAnnouncementSentDelegateLock = [[NSObject alloc] init];
        self.fileAnnouncementReceivedDelegate = nil;
        self.fileAnnouncementSentDelegate = nil;
	}
	
	return self;
}

-(void)announceFilePaths: (NSArray *)pathList
{
    [self performSelectorInBackground: @selector(announceFiles:) withObject: pathList];
}

-(void)announceFiles: (NSArray *)pathList
{
    NSMutableArray *failedPaths = [[NSMutableArray alloc] init];
    NSArray *files = [self.fsa getFileInfo: pathList withFailedPathsArray: failedPaths andLocalBusID: self.localBusID];
    
    [self.pm addAnnouncedLocalFilesWithList: files];
    [self sendAnnouncementToPeer: nil isFileIDResponse: NO];
    
    if (self.fileAnnouncementSentDelegate != nil)
    {
        [self.fileAnnouncementSentDelegate announcementSentWithFailedPaths: [[NSArray alloc] initWithArray: failedPaths]];
    }
}

-(void)sendAnnouncementToPeer: (NSString *)peer isFileIDResponse: (BOOL)isFileIDResponse
{
    NSArray *myAnnouncedFiles = [self.pm getAnnouncedLocalFiles];
    NSMutableArray *files = [[NSMutableArray alloc] initWithCapacity: [myAnnouncedFiles count]];
    
    for (int i = 0; i < [myAnnouncedFiles count]; i++)
    {
        FTMFileDescriptor *localDescriptor = [myAnnouncedFiles objectAtIndex: i];
        FTMFileDescriptor *announcedDescriptor = [[FTMFileDescriptor alloc] initWithFileDescriptor: localDescriptor];
        
        if (!self.showRelativePath)
        {
            announcedDescriptor.relativePath = @"";
        }
        
        if (!self.showSharedPath)
        {
            announcedDescriptor.sharedPath = @"";
        }
        
        [files addObject: announcedDescriptor];
    }
    
    FTMAnnounceAction *action = [[FTMAnnounceAction alloc] init];
    action.peer = peer;
    action.fileList = files;
    action.isFileIDResponse = isFileIDResponse;
    [self.dispatcher insertAction: action];
}

-(NSArray *)stopAnnounceFilePaths: (NSArray *)pathList
{
	pathList = [self.pm removeAnnouncedLocalFilesWithPaths: pathList];
    [self sendAnnouncementToPeer: nil isFileIDResponse: NO];
	return pathList;
}

-(FTMStatusCode)requestAnnouncementFromPeer: (NSString *)peer
{
	if (self.localBusID == nil)
    {
        return FTMNOAjConnection;
    }
    
    if (self.fileAnnouncementReceivedDelegate == nil)
    {
        return FTMNoFileAnnouncementListener;
    }
    
    FTMRequestAnnouncementAction *action = [[FTMRequestAnnouncementAction alloc] init];
    action.peer = peer;
    [self.dispatcher insertAction: action];
    
	return FTMOK;
}

-(void)handleAnnouncedFiles: (NSArray *)fileList fromPeer: (NSString *)peer
{
	[self.pm updateAnnouncedRemoteFilesWithList: fileList fromPeer: peer];
    
    if (self.fileAnnouncementReceivedDelegate != nil)
    {
        [self.fileAnnouncementReceivedDelegate receivedAnnouncementForFiles: fileList andIsFileIDResponse: NO];
    }
}

-(void)handleAnnouncementRequestFrom: (NSString *)peer
{
	[self sendAnnouncementToPeer: peer isFileIDResponse: NO];
}

-(void)setFileAnnouncementReceivedDelegate: (id<FTMFileAnnouncementReceivedDelegate>)fileAnnouncementReceivedDelegate
{
    @synchronized(self.fileAnnouncementReceivedDelegateLock)
    {
        self->_fileAnnouncementReceivedDelegate = fileAnnouncementReceivedDelegate;
    }
}

-(void)setFileAnnouncementSentDelegate: (id<FTMFileAnnouncementSentDelegate>)fileAnnouncementSentDelegate
{
    @synchronized(self.fileAnnouncementSentDelegateLock)
    {
        self->_fileAnnouncementSentDelegate = fileAnnouncementSentDelegate;
    }
}

-(void)resetStateWithLocalBusID: (NSString *)localBusID
{
    self.localBusID = localBusID;
}

@end