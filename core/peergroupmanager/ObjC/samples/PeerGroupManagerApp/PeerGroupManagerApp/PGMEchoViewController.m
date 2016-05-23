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

#import "PGMEchoViewController.h"

@interface PGMEchoViewController ()

@end

@implementation PGMEchoViewController

@synthesize peerGroupManager = _peerGroupManager;
@synthesize echoString = _echoString;
@synthesize echoButton = _echoButton;
@synthesize echoReply = _echoReply;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    self.echoString.delegate = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)echoButtonPressed:(id)sender
{
    NSString *remotePeer;
    NSString *groupName;
    
    NSMutableArray *hostedAndJoinedGroups = [[self.peerGroupManager listHostedGroupNames] mutableCopy];
    [hostedAndJoinedGroups addObjectsFromArray:[self.peerGroupManager listJoinedGroupNames]];
    
    BOOL complete = NO;
    for(NSString *group in hostedAndJoinedGroups)
    {
        if([self.peerGroupManager getNumberOfPeersInGroup:group] > 1)
        {
            NSArray *peers = [self.peerGroupManager getIdsOfPeersInGroup:group];
            for(NSString *peer in peers)
            {
                if(![peer isEqualToString:[self.peerGroupManager getMyPeerId]])
                {
                    remotePeer = [peer copy];
                    groupName = [group copy];
                    complete = YES;
                    break;
                }
            }
        }
        if(complete)
        {
            break;
        }
    }
    
    TestObjectProxy *proxy = (TestObjectProxy *) [self.peerGroupManager getRemoteObjectWithClassName:@"TestObjectProxy" forPeer:remotePeer inGroup:groupName onPath:@"/org/alljoyn/TestObject"];
    
    NSLog(@"Getting Proxy for remote peer %@ in group %@", remotePeer, groupName);
    
    NSString *replyString = [proxy echoString:self.echoString.text];
    self.echoReply.text = [NSString stringWithFormat:@"Echo from %@ - %@", remotePeer, replyString];
}

- (BOOL) textFieldShouldReturn:(UITextField *)textField
{
    [self.echoString resignFirstResponder];
    return YES;
}

@end
