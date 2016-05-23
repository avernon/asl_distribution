/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#import "AuthenticationListenerImpl.h"

static NSString * const DEFAULT_PASSCODE = @"000000";

@interface AuthenticationListenerImpl ()

@property (strong, nonatomic) UIAlertView *setPassCodeAlert;
@property (strong, nonatomic) NSString *passCodeText;
@property (strong, nonatomic) NSString *peerName;
@property (strong, nonatomic) NSMutableDictionary *peersPasscodes; // store the peers passcodes

@end

@implementation AuthenticationListenerImpl

- (id)init {
    self = [super init];
	if (self) {
        [self prepareAlerts];
        // Create NSMutableDictionary dictionary of peers passcodes
        self.peersPasscodes = [[NSMutableDictionary alloc] init];
	}
	return self;
}

- (void)prepareAlerts
{
    // setPassCodeAlert.tag = 1
    self.setPassCodeAlert = [[UIAlertView alloc] initWithTitle:@"" message:@"Enter device password" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
    self.setPassCodeAlert.alertViewStyle = UIAlertViewStylePlainTextInput;
    self.setPassCodeAlert.tag = 1;
}

// Get the user's input from the alert dialog
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView == self.setPassCodeAlert) {
        [self.setPassCodeAlert dismissWithClickedButtonIndex:buttonIndex animated:NO];
        
        if (buttonIndex == 1) { // User pressed OK
            // get the input pass
            self.passCodeText = [self.setPassCodeAlert textFieldAtIndex:0].text;
            //            [self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"Passcode is: %@",  self.passCodeText]];
            NSLog(@"Passcode is: %@",  self.passCodeText);
            
            bool foundPeer = false;
            
            // Check that peername is not empty
            if ([self.peerName length]) {
                if (![self.passCodeText length]) {
                    // set the pass to default if input is empty
                    self.passCodeText = DEFAULT_PASSCODE;
                }
                // Iterate over the dictionary and add/update
                for (NSString *key in self.peersPasscodes.allKeys) {
                    if ([key isEqualToString:self.peerName]) {
                        // Update passcode for key
                        (self.peersPasscodes)[self.peerName] = self.passCodeText;
                        //                        [self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"Update peer %@ with passcode %@",  self.peerName, self.passCodeText]];
                        NSLog(@"Update peer %@ with passcode %@",  self.peerName, self.passCodeText);
                        // Set flag
                        foundPeer = true;
                        break;
                    }
                }
                if (!foundPeer) {
                    // Add new set of key/value
                    [self.peersPasscodes setValue:self.passCodeText forKey:self.peerName];
                    //                    [self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"add new peers %@ %@", self.peerName, self.passCodeText]];
                    NSLog(@"add new peers %@ %@", self.peerName, self.passCodeText);
                    
                }
                
                [[NSNotificationCenter defaultCenter] postNotificationName:@"hasPasscodeForBus" object:self.peerName];
            }
        }
        else {     // User pressed Cancel
        }
        
    } else {
		NSLog(@"[%@] [%@] alertView.tag is wrong", @"ERROR", [[self class] description]);
	}
}

#pragma mark - AJNAuthenticationListener protocol methods
- (AJNSecurityCredentials *)requestSecurityCredentialsWithAuthenticationMechanism:(NSString *)authenticationMechanism peerName:(NSString *)peerName authenticationCount:(uint16_t)authenticationCount userName:(NSString *)userName credentialTypeMask:(AJNSecurityCredentialType)mask
{
	AJNSecurityCredentials *creds = nil;
	bool credFound = false;
    
    NSLog(@"requestSecurityCredentialsWithAuthenticationMechanism:%@ forRemotePeer%@ userName:%@", authenticationMechanism, peerName, userName);
    
	if ([authenticationMechanism isEqualToString:@"ALLJOYN_SRP_KEYX"] || [authenticationMechanism isEqualToString:@"ALLJOYN_PIN_KEYX"]) {
		if (mask & kAJNSecurityCredentialTypePassword) {
			if (authenticationCount <= 3) {
				creds = [[AJNSecurityCredentials alloc] init];
                
				// Check if the password stored in peersPasscodes
				for (NSString *key in self.peersPasscodes.allKeys) {
					if ([key isEqualToString:peerName]) {
						creds.password = (self.peersPasscodes)[key];
                        NSLog(@"Found password %@ for peer %@", creds.password, key);
                        
						credFound = true;
						break;
					}
				}
				// Use the default password
				if (!credFound) {
					creds.password = DEFAULT_PASSCODE;
                    NSLog(@"Using default password %@ for peer %@", DEFAULT_PASSCODE, peerName);
                    
				}
			}
		}
	}
	return creds;
}

- (void)authenticationUsing:(NSString *)authenticationMechanism forRemotePeer:(NSString *)peerName didCompleteWithStatus:(BOOL)success
{
	NSString *status;
	status = (success == YES ? @"was successful" : @"failed");
    
    NSLog(@"authenticationUsing:%@ forRemotePeer%@ %@", authenticationMechanism, peerName, status);
    
    //	[self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"authenticationUsing:%@ forRemotePeer%@ %@", authenticationMechanism, peerName, status]];
    
	//get the passcpde for this bus
	if (!success) {
		self.peerName = peerName;
		self.passCodeText = nil;
		dispatch_async(dispatch_get_main_queue(), ^{
		    [self.setPassCodeAlert show];
		});
	}
}

@end
