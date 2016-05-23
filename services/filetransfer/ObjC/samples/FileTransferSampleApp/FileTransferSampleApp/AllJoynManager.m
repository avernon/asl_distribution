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

#import "AllJoynManager.h"

//Specifies the AllJoyn service name and port number.
NSString *SERVICE_NAME = @"org.alljoyn.cops.filetransfer";
const AJNSessionPort CONTACT_PORT = 42;

@interface AllJoynManager()

@property (nonatomic) ConnectionState connectionState;

@end

@implementation AllJoynManager

@synthesize bus = _bus;
@synthesize sessionID = _sessionID;
@synthesize connectionState = _connectionState;
@synthesize peers = _peers;

/*
 * Initializes the AllJoynManager class.
 */
-(id)init
{
	self = [super init];
	
	if (self)
    {
        self.connectionState = DISCONNECTED;
        self.peers = [[NSMutableArray alloc] init];
    }
    
    return self;
}

/*
 * Creates an AllJoyn session where we are the host.
 */
-(void)createSession
{
    if (self.connectionState == JOINING)
    {
        [self.bus disconnectWithArguments:@"null:"];        
    }
    
    [self updateConnectionState: HOSTING];
    
    self.bus = [[AJNBusAttachment alloc] initWithApplicationName:@"FileTransfer" allowRemoteMessages: YES];
    int status = [self.bus start];
    status = [self.bus connectWithArguments: @"null:"];
    
    AJNSessionOptions *sessionOptions = [[AJNSessionOptions alloc] initWithTrafficType: kAJNTrafficMessages supportsMultipoint: YES proximity: kAJNProximityAny transportMask: kAJNTransportMaskAny];
    
    status = [self.bus requestWellKnownName: SERVICE_NAME withFlags: kAJNBusNameFlagReplaceExisting| kAJNBusNameFlagDoNotQueue];
    status = [self.bus bindSessionOnPort: CONTACT_PORT withOptions: sessionOptions withDelegate:self];
    status = [self.bus advertiseName: SERVICE_NAME withTransportMask: sessionOptions.transports];
}

/*
 * Attempts to join an already exisiting AllJoyn session.
 */
-(void)joinSession
{
    if (self.connectionState == HOSTING)
    {
        [self.bus disconnectWithArguments:@"null:"];
    }
    
    [self updateConnectionState: JOINING];
    
    self.bus = [[AJNBusAttachment alloc] initWithApplicationName: @"FileTransfer" allowRemoteMessages: YES];
    
    int status = [self.bus start];
    
    status = [self.bus connectWithArguments: @"null:"];
    
    [self.bus registerBusListener: self];
    
    [self.bus findAdvertisedName: SERVICE_NAME];
}

/*
 * Handles the event that is triggered when an exisiting AllJoyn session is found.
 */
-(void)didFindAdvertisedName: (NSString *)name withTransportMask: (AJNTransportMask) transport namePrefix:(NSString *)namePrefix
{
    AJNSessionOptions *sessionOptions = [[AJNSessionOptions alloc] initWithTrafficType: kAJNTrafficMessages supportsMultipoint: YES proximity: kAJNProximityAny transportMask: kAJNTransportMaskAny];
    
    self.sessionID = [self.bus joinSessionWithName: name onPort: CONTACT_PORT withDelegate:self options: sessionOptions];
    NSLog(@"joined session %i", self.sessionID);
    
    [self updateConnectionState: CONNECTED];
}

/*
 * Handles the even that is triggered when someone attempts to joing our session. This function just
 * returns yes which means the session is open to anyone attempting to join.
 */
-(BOOL)shouldAcceptSessionJoinerNamed: (NSString *)joiner onSessionPort: (AJNSessionPort)sessionPort withSessionOptions: (AJNSessionOptions *)options
{
    return YES;
}

/*
 * Handles the event that is triggered when someone joins our AllJoyn session successfully. This function adds
 * the peer to a list and notifies the ViewController class that the AllJoyn session is now connected.
 */
-(void)didJoin: (NSString *)joiner inSessionWithId: (AJNSessionId)sessionId onSessionPort: (AJNSessionPort)sessionPort
{
    self.sessionID = sessionId;
    NSLog(@"hosted session %i", self.sessionID);
    
    [self updateConnectionState: CONNECTED];
    
    [self.peers addObject: joiner];
}

/*
 * Disconnects from the current AllJoyn session and notifies the ViewController class that the we have left
 * the current AllJoyn session.
 */
-(void)disconnect
{
    if (self.connectionState == CONNECTED)
    {
        [self.bus leaveSession: self.sessionID];
        [self.bus disconnectWithArguments: @"null:"];
        
        [self updateConnectionState:DISCONNECTED];
    }
}

/*
 * Notifies the ViewController class via the connectionStateChangedDelegate that a connection state changed
 * event has occured.
 */
-(void)updateConnectionState: (ConnectionState)state
{
    self.connectionState = state;
    if (self.connectionStateChangedDelegate != nil)
    {
        [self.connectionStateChangedDelegate connectionStateChanged: state];
    }
}

/*
 * Handles the event that is triggered when a peer is added to our session. The peer name is added to an internal
 * list so we know who is in our session.
 */
-(void)didAddMemberNamed:(NSString *)memberName toSession:(AJNSessionId)sessionId
{
    [self.peers addObject: memberName];
}

/*
 * Handles the even that is triggered when the AllJoyn session we are in is lost. 
 */
-(void)sessionWasLost:(AJNSessionId)sessionId
{
    [self disconnect];
}

@end
