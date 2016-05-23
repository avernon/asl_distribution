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

// AllJoyn Objective-C Framework headers
#import "AllJoynFramework/AJNTransportMask.h"

/**
 * The PeerGroupDelegate is a protocol to be implemented if the app wishes to listen
 * to AllJoyn call-back methods. The call-back methods in this protocol are
 * equivalent to the didFindAdvertisedName:withTransportMask:namePrefix:, 
 * didLoseAdvertisedName:withTransportMask:namePrefix:, sessionWasLost:,
 * didAddMemberNamed:toSession:, and didRemoveMemberNamed:toSession: call-backs of AllJoyn.
 */
@protocol PGMPeerGroupDelegate <NSObject>

@optional
/**
 * Called when a new group advertisement is found. 
 *
 * This will not be triggered for locked groups or your own hosted groups.
 *
 * @param groupName  the groupName that was found.
 *
 * @param transport  the transport that the groupName was discovered on.
 */
- (void)didFindAdvertisedName:(NSString *)groupName withTransport:(AJNTransportMask)transport;

/**
 * Called when a group that was previously reported through
 * didFindAdvertisedName:withTransport: has become unavailable. 
 *
 * This will not be triggered for your own hosted groups. This will get
 * triggered for a group that was previously unlocked and has now become
 * locked.
 *
 * @param groupName  the group name that has become unavailable.
 *
 * @param transport  the transport that stopped receiving the groupName
 *                   advertisement.
 */
- (void)didLoseAdvertisedName:(NSString *)groupName withTransport:(AJNTransportMask)transport;

/**
 * Called when a group becomes disconnected.
 *
 * @param groupName  the group that became disconnected.
 */
- (void)groupWasLost:(NSString *)groupName;

/**
 * Called when a new peer joins a group.
 *
 * @param peerId     the id of the peer that joined.
 *
 * @param groupName  the group that the peer joined.
 *
 * @param numPeers   the current number of peers in the group.
 */
- (void)didAddPeer:(NSString *)peerId toGroup:(NSString *)groupName forATotalOf:(int)numPeers;

/**
 * Called when a new peer leaves a group.
 *
 * @param peerId     the id of the peer that left.
 *
 * @param groupName  the group that the peer left.
 *
 * @param numPeers   the current number of peers in the group.
 */
- (void)didRemovePeer:(NSString*)peerId fromGroup:(NSString *)groupName forATotalOf:(int)numPeers;
@end