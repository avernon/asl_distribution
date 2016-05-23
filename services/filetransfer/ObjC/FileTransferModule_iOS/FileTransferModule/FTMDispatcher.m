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

#import <dispatch/dispatch.h>
#import "FTMDispatcher.h"

@interface FTMDispatcher()
{
    /*
     * Instance of dispatcher_queue_t.
     *
     * @warning *Note:* This is a private variable and is not meant to be modified directly.
     */
	dispatch_queue_t dispatcherQueue;
}

/*
 * Stores an instance of the FTMTransmitter.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) FTMTransmitter *transmitter;

/*
 * Specifies a generic object used for thread synchronization. This object is used in the
 * set method of the sendManagerDeleagte.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) NSObject *sendManagerDelegateLock;

/*
 * Specifies a generic object used for thread synchronization. This object is used in the
 * set method of the directedAnnouncementManagerDeleagte.
 *
 * @warning *Note:* This is a private property and is not meant to be called directly.
 */
@property (nonatomic, strong) NSObject *damDelegateLock;

/*
 * Private helper function that is used to ensure the appropriate response to a given action
 * type. Most actions are just passed to the FTMTransmitter for processing but additional action
 * must be taken when a FTMFileIDResponse or FTMDataChunk action is encountered. 
 */
-(void)processAction: (FTMAction *)action;

@end

@implementation FTMDispatcher

@synthesize transmitter = _transmitter;
@synthesize sendManagerDelegateLock = _sendManagerDelegateLock;
@synthesize damDelegateLock = _damDelegateLock;

- (id)initWithBusObject: (FTMFileTransferBusObject *)busObject busAttachment: (AJNBusAttachment *)busAttachment andSessionID: (AJNSessionId)sessionID
{
	return [self initWithTransmitter: [[FTMTransmitter alloc] initWithBusObject: busObject busAttachment: busAttachment andSessionID: sessionID]];
}

-(id)initWithTransmitter: (FTMTransmitter *)transmitter
{
    self = [super init];
	
	if (self)
    {
		dispatcherQueue = dispatch_queue_create("FTCDispatcher", NULL);
        self.transmitter = transmitter;
        self.sendManagerDelegateLock = [[NSObject alloc] init];
        self.damDelegateLock = [[NSObject alloc] init];
        self.sendManagerDelegate = nil;
        self.damDelegateLock = nil;
	}
	
	return self;
}

-(void)insertAction: (FTMAction *)action
{
    dispatch_async(dispatcherQueue, ^{
        [self processAction: action];
    });
}

-(void)processAction: (FTMAction *)action
{
    if ([action isMemberOfClass: [FTMFileIDResponseAction class]])
    {
        if (self.directedAnnouncementManagerDelegate != nil)
        {
            [self.directedAnnouncementManagerDelegate generateFileDescriptor: (FTCFileIDResponseAction *)action];
        }
        return;
    }
    
    [action transmitActionWithTransmitter: self.transmitter];
    
    if ([action isMemberOfClass: [FTMDataChunkAction class]])
    {
        if (self.sendManagerDelegate != nil)
        {
            [self.sendManagerDelegate dataSent];
        }
    }
}

-(FTMStatusCode)transmitImmediately: (FTMAction *)action
{
    @try
    {
        return [action transmitActionWithTransmitter: self.transmitter];
    }
    @catch (NSException *ex)
    {
        NSLog(@"%@", [ex reason]);
    }
}

-(void)setDirectedAnnouncementManagerDelegate: (id<FTMDirectedAnnouncementManagerDelegate>)directedAnnouncementManagerDelegate
{
    @synchronized(self.damDelegateLock)
    {
        self->_directedAnnouncementManagerDelegate = directedAnnouncementManagerDelegate;
    }
}

-(void)setSendManagerDelegate: (id<FTMSendManagerDelegate>)sendManagerDelegate
{
    @synchronized(self.sendManagerDelegateLock)
    {
        self->_sendManagerDelegate = sendManagerDelegate;
    }
}

-(void)resetStateWithBusObject: (FTMFileTransferBusObject *)busObject busAttachment: (AJNBusAttachment *)busAttachment andSessionID: (AJNSessionId)sessionID
{
    self.transmitter = [[FTMTransmitter alloc] initWithBusObject: busObject busAttachment: busAttachment andSessionID: sessionID];
}

@end