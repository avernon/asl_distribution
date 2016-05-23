////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "ViewController.h"
#import "PingService.h"

@interface ViewController () <PingServiceDelegate>

@property (nonatomic) BOOL isStarted;

@end

@implementation ViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        [PingService.sharedInstance setDelegate:self];
    }
    return self;
}

- (IBAction)didTouchStartButton:(id)sender
{
    if (self.isStarted) {
        [PingService.sharedInstance stop];
        [self.startButton setTitle:@"Start"];
    }
    else {
        [PingService.sharedInstance start:self.advertisedNameTextField.stringValue];
        [self.startButton setTitle:@"Stop"];
    }
    self.isStarted = !self.isStarted;
}

#pragma mark - PingServiceDelegate implementation

- (AJNTransportMask)transportType
{
    return kAJNTransportMaskAny;
}

// The delegate is called once a client joins a session with the service
//
- (void)client:(NSString *)clientName didJoinSession:(AJNSessionId)sessionId
{
    [self receivedStatusMessage:[NSString stringWithFormat:@"Client %@ joined session %u", clientName, sessionId]];
}

// The delegate is called when a client leaves a session
//
- (void)client:(NSString *)clientName didLeaveSession:(AJNSessionId)sessionId
{
    [self receivedStatusMessage:[NSString stringWithFormat:@"Client %@ left session %u", clientName, sessionId]];
}

// Send updates on internal state of Ping Service
//
- (void)receivedStatusMessage:(NSString*)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMutableString *string = self.eventsTextView.string.length ? [self.eventsTextView.string mutableCopy] : [[NSMutableString alloc] init];
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        [formatter setTimeStyle:NSDateFormatterMediumStyle];
        [formatter setDateStyle:NSDateFormatterShortStyle];
        [string appendFormat:@"[%@]\n",[formatter stringFromDate:[NSDate date]]];
        [string appendString:message];
        [string appendString:@"\n\n"];
        [self.eventsTextView setString:string];
        NSLog(@"%@",string);
    });
}

@end
