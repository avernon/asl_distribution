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

#import "MainViewController.h"
#import "SystemConfiguration/CaptiveNetwork.h"
#import "AJNStatus.h"
#import "AJNPasswordManager.h"
#import "alljoyn/about/AJNAnnouncement.h"
#import "alljoyn/about/AJNAnnouncementReceiver.h"
#import "alljoyn/about/AJNAboutDataConverter.h"
#import "ClientInformation.h"
#import "AnnounceTextViewController.h"
#import "GetAboutCallViewController.h"
#import "alljoyn/controlpanel/AJCPSGetControlPanelViewController.h"
#import "AuthenticationListenerImpl.h"
#include <qcc/Log.h>


static bool ALLOWREMOTEMESSAGES = true; // About Client -  allow Remote Messages flag
static NSString * const APPNAME = @"AboutClientMain"; // About Client - default application name
static NSString * const DAEMON_QUIET_PREFIX  = @"quiet@";   // About Client - quiet advertising
static NSString * const ONBOARDING_OBJECT_PATH = @"/Onboarding";
static NSString * const ONBOARDING_INTERFACE_NAME = @"org.alljoyn.Onboarding";

static NSString * const SSID_NOT_CONNECTED = @"SSID:not connected";

@interface MainViewController ()
@property NSString *className;

// About Client properties
@property (strong, nonatomic) AJNBusAttachment *clientBusAttachment;
@property (strong, nonatomic) AJNAnnouncementReceiver *announcementReceiver;
@property (strong, nonatomic) NSString *realmBusName;
@property (nonatomic) bool isAboutClientConnected;
@property (strong, nonatomic) NSMutableDictionary *clientInformationDict; // Store the client related information

// Announcement
@property (strong, nonatomic) NSString *announcementButtonCurrentTitle;                  // The pressed button's announcementUniqueName
@property (strong, nonatomic) dispatch_queue_t annBtnCreationQueue;

// About Client strings
@property (strong, nonatomic) NSString *ajconnect;
@property (strong, nonatomic) NSString *ajdisconnect;
@property (strong, nonatomic) NSString *defaultBusName;
@property (strong, nonatomic) NSString *annSubvTitleLabelDefaultTxt;

// About Client alerts
@property (strong, nonatomic) UIAlertView *busNameAlert;
@property (strong, nonatomic) UIAlertView *disconnectAlert;
@property (strong, nonatomic) UIAlertView *announcementOptionsAlert;
@property (strong, nonatomic) UIAlertView *onboardingOptionsAlert;
@property (strong, nonatomic) UITextField *alertDefaultBusName;

@property (strong, nonatomic) AuthenticationListenerImpl *authenticationListenerImpl;

@end

@implementation MainViewController

#pragma mark - Built In methods
- (void)viewDidLoad
{
	[super viewDidLoad];
    
    [self loadNewSession];

    [self updateSSIDinTitle];
    
    [NSTimer scheduledTimerWithTimeInterval:5.0
                                     target:self
                                   selector:@selector(updateSSIDinTitle)
                                   userInfo:nil
                                    repeats:YES];
    
}

-(void)updateSSIDinTitle
{
    static BOOL executing;
    
    if(executing)
        return;
    
    executing = YES;
    // this code does not work in the simulator
    NSArray *supportedInterfaces = (__bridge_transfer id)CNCopySupportedInterfaces();
//    NSLog(@"supportedInterfaces: %@", supportedInterfaces);
    id interfaceInformation = nil;
    for (NSString *interfaceName in supportedInterfaces) {
        interfaceInformation = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)interfaceName);
//        NSLog(@"    %@:%@", interfaceName, interfaceInformation);
        NSDictionary *dict = interfaceInformation;
        NSString *title = [NSString stringWithFormat:@"Devices on: %@",dict[@"SSID"]];
        if (![self.title isEqualToString:title]) {
            if (![dict[@"SSID"] hasPrefix:@"AJ_"] && ![dict[@"SSID"] isEqualToString:[[NSUserDefaults standardUserDefaults]valueForKey:@"lastVisitedNetwork"]]) {
                NSLog(@"setting lastVisitedNetwork to: %@", dict[@"SSID"]);
                [[NSUserDefaults standardUserDefaults] setValue:dict[@"SSID"] forKey:@"lastVisitedNetwork"];
                [[NSUserDefaults standardUserDefaults] synchronize];
            }

            self.title = title;
            if (self.isAboutClientConnected) {
                NSLog(@"changing network to %@ trigger a restart", dict[@"SSID"]);
                [[[UIAlertView alloc]initWithTitle:@"Network Change" message:@"The WiFi network changed. You have been disconnected, please connect again" delegate:Nil cancelButtonTitle:@"OK" otherButtonTitles: nil] show];
                [self stopAboutClient];
            }
        }
        
        if (interfaceInformation && [interfaceInformation count]) { break; }
    }
    
    if ([self.title isEqualToString:@""]) {
        self.title = SSID_NOT_CONNECTED;
    }
    
    executing = NO;
}

// Get the user's input from the alert dialog
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (alertView == self.busNameAlert) {
		if (buttonIndex == 1) { // User pressed OK
			self.realmBusName = [[alertView textFieldAtIndex:0] text];
            
			NSLog(@"[%@] [%@] realmBusName: %@", @"DEBUG", [[self class] description], self.realmBusName);
            
			[self startAboutClient];
		}
		else {   // User pressed Cancel
		}
	}
	else if (alertView == self.disconnectAlert) {
		if (buttonIndex == 1) { // User pressed OK
			[self stopAboutClient];
		}
	}
	else if (alertView == self.announcementOptionsAlert) {
		[self performAnnouncementAction:buttonIndex];
	}
	else if (alertView == self.onboardingOptionsAlert) {
		[self performAnnouncementAction:buttonIndex];
	}
    else {
		NSLog(@"[%@] [%@] alertView.tag is wrong", @"ERROR", [[self class] description]);
	}
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue
                 sender:(id)sender
{
    // GetAboutCallViewController
	if ([segue.destinationViewController isKindOfClass:[GetAboutCallViewController class]]) {
		GetAboutCallViewController *getAboutCallView = segue.destinationViewController;
		getAboutCallView.clientInformation = (self.clientInformationDict)[self.announcementButtonCurrentTitle];
		getAboutCallView.clientBusAttachment = self.clientBusAttachment;
	}
    // AnnounceTextViewController
	else if ([segue.destinationViewController isKindOfClass:[AnnounceTextViewController class]]) {
		AnnounceTextViewController *announceTextViewController = segue.destinationViewController;
		announceTextViewController.ajnAnnouncement = [(ClientInformation *)(self.clientInformationDict)[self.announcementButtonCurrentTitle] announcement];
	}
    else if ([segue.destinationViewController isKindOfClass:[OnboardingViewController class]])
    {
        OnboardingViewController *onboardingViewController = segue.destinationViewController;
        onboardingViewController.clientBusName = self.clientBusAttachment;
        onboardingViewController.clientInformation = (self.clientInformationDict)[self.announcementButtonCurrentTitle];
    }
}

#pragma mark - IBAction Methods
- (IBAction)connectButtonDidTouchUpInside:(id)sender
{
	// Present the dialog box - to get the bus name
	if (!self.isAboutClientConnected) {
		// Set default text for realm bus name
		[self.alertDefaultBusName setText:self.defaultBusName];
		[self.alertDefaultBusName setFont:([UIFont fontWithName:@"System" size:8.0])];
		[self.busNameAlert show]; // Event is forward to alertView: clickedButtonAtIndex:
	}
	else {
		// Present a dialog box - are you sure?
		[self.disconnectAlert show]; // Event is forward to alertView: clickedButtonAtIndex:
	}
}

#pragma mark - AJNAnnouncementListener protocol method
// Here we receive an announcement from AJN and add it to the client's list of services avaialble
- (void)announceWithVersion:(uint16_t)version
                       port:(uint16_t)port
                    busName:(NSString *)busName
         objectDescriptions:(NSMutableDictionary *)objectDescs
                  aboutData:(NSMutableDictionary **)aboutData
{
	NSString *announcementUniqueName; // Announcement unique name in a format of <busName DeviceName>
	ClientInformation *clientInformation = [[ClientInformation alloc] init];
    
	// Save the announcement in a AJNAnnouncement
	clientInformation.announcement = [[AJNAnnouncement alloc] initWithVersion:version port:port busName:busName objectDescriptions:objectDescs aboutData:aboutData];
    
	// Generate an announcement unique name in a format of <busName DeviceName>
	announcementUniqueName = [NSString stringWithFormat:@"%@ %@", [clientInformation.announcement busName], [AJNAboutDataConverter messageArgumentToString:[clientInformation.announcement aboutData][@"DeviceName"]]];
    
    NSLog(@"[%@] [%@] Announcement unique name [%@]", @"DEBUG", [[self class] description], announcementUniqueName);
    
	AJNMessageArgument *annObjMsgArg = [clientInformation.announcement aboutData][@"AppId"];
	uint8_t *appIdBuffer;
	size_t appIdNumElements;
	QStatus status;
	status = [annObjMsgArg value:@"ay", &appIdNumElements, &appIdBuffer];
    
	// Add the received announcement
	if (status != ER_OK) {
        NSLog(@"[%@] [%@] Failed to read appId for key [%@]", @"DEBUG", [[self class] description], announcementUniqueName);

		return;
	}
    
	// Dealing with announcement entries should be syncronized, so we add it to a queue
	dispatch_sync(self.annBtnCreationQueue, ^{
	    bool isAppIdExists = false;
	    uint8_t *tmpAppIdBuffer;
	    size_t tmpAppIdNumElements;
	    QStatus tStatus;
	    int res;
        
	    // Iterate over the announcements dictionary
	    for (NSString *key in self.clientInformationDict.allKeys) {
	        ClientInformation *clientInfo = [self.clientInformationDict valueForKey:key];
	        AJNAnnouncement *announcement = [clientInfo announcement];
	        AJNMessageArgument *tmpMsgrg = [announcement aboutData][@"AppId"];
            
	        tStatus = [tmpMsgrg value:@"ay", &tmpAppIdNumElements, &tmpAppIdBuffer];
	        if (tStatus != ER_OK) {
                NSLog(@"[%@] [%@] Failed to read appId for key [%@]", @"DEBUG", [[self class] description], key);

	            return;
			}
            
	        res = 1;
	        if (appIdNumElements == tmpAppIdNumElements) {
	            res = memcmp(appIdBuffer, tmpAppIdBuffer, appIdNumElements);
			}
            
	        // Found a matched appId - res=0
	        if (!res) {
	            isAppIdExists = true;
	            // Same AppId and the same announcementUniqueName
	            if ([key isEqualToString:announcementUniqueName]) {
	                // Update only announcements dictionary
                    
                     NSLog(@"[%@] [%@] Got an announcement from a known device - updating the announcement object", @"DEBUG", [[self class] description]);

                    (self.clientInformationDict)[announcementUniqueName] = clientInformation;
	                // Same AppId but *different* announcementUniqueName
				}
	            else {
                     NSLog(@"[%@] [%@] Got an announcement from a known device(different bus name) - updating the announcement object and UI ", @"DEBUG", [[self class] description]);
                    
	                // Cancel advertise name if the bus name has changed
	                NSString *prevBusName = [announcement busName];
	                if (!([busName isEqualToString:prevBusName])) {
	                    tStatus = [self.clientBusAttachment cancelFindAdvertisedName:prevBusName];
	                    if (status != ER_OK) {
                            NSLog(@"[%@] [%@] failed to cancelAdvertisedName for %@. status:%@", @"DEBUG", [[self class] description],prevBusName, [AJNStatus descriptionForStatusCode:tStatus]);
                        }
					}
	                // Remove existed record from the announcements dictionary
	                [self.clientInformationDict removeObjectForKey:key];
	                // Add new record to the announcements dictionary
	                [self.clientInformationDict setValue:clientInformation forKey:announcementUniqueName];
				}
	            break;
			} //if
		} //for
        
	    //appId doesn't exist and  there is no match announcementUniqueName
	    if (!(self.clientInformationDict)[announcementUniqueName] && !isAppIdExists) {
	        // Add new pair with this AboutService information (version,port,bus name, object description and about data)
	        [self.clientInformationDict setValue:clientInformation forKey:announcementUniqueName];
	        [self addNewAnnouncemetEntry];
            
	        // AppId doesn't exist and BUT there is no match announcementUniqueName
		} // else No OP
    });
    
	// Register interest in a well-known name prefix for the purpose of discovery (didLoseAdertise)
	[self.clientBusAttachment enableConcurrentCallbacks];
	status = [self.clientBusAttachment findAdvertisedName:busName];
	if (status != ER_OK) {
         NSLog(@"[%@] [%@] failed to findAdvertisedName for %@. status:%@", @"ERROR", [[self class] description],busName, [AJNStatus descriptionForStatusCode:status]);
	}
}

#pragma mark AJNBusListener protocol methods

- (void)didFindAdvertisedName:(NSString *)name
            withTransportMask:(AJNTransportMask)transport
                   namePrefix:(NSString *)namePrefix
{
	NSLog(@"didFindAdvertisedName %@", name);
}

- (void)didLoseAdvertisedName:(NSString *)name
            withTransportMask:(AJNTransportMask)transport
                   namePrefix:(NSString *)namePrefix
{
	NSLog(@"didLoseAdvertisedName");
	QStatus status;
	// Find the button title that should be removed
	for (NSString *key in[self.clientInformationDict allKeys]) {
		if ([[[[self.clientInformationDict valueForKey:key] announcement] busName] isEqualToString:name]) {
			// Cancel advertise name for that bus
			status = [self.clientBusAttachment cancelFindAdvertisedName:name];
			if (status != ER_OK) {
                 NSLog(@"[%@] [%@] failed to cancelFindAdvertisedName for %@. status:%@", @"DEBUG", [[self class] description],name, [AJNStatus descriptionForStatusCode:status]);
            }
			// Remove the anouncement from the dictionary
			[self.clientInformationDict removeObjectForKey:key];
		}
	}
    
	[self.servicesTable performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
}

#pragma mark - util methods
- (void)loadNewSession
{
    // About flags
	self.isAboutClientConnected  = false;
    
	self.annBtnCreationQueue = dispatch_queue_create("org.alljoyn.announcementbuttoncreationQueue", NULL);
    
	// Set About Client strings
	self.ajconnect = @"Connect to AllJoyn";
	self.ajdisconnect = @"Disconnect from AllJoyn";
	self.defaultBusName = @"org.alljoyn.BusNode.onboardingClient";
	self.annSubvTitleLabelDefaultTxt = @"Announcement of ";
	// Set About Client connect button
	self.connectButton.backgroundColor = [UIColor darkGrayColor]; //button bg color
	[self.connectButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal]; //button font color
	[self.connectButton setTitle:self.ajconnect forState:UIControlStateNormal]; //default text
    
	[self prepareAlerts];
    
}

//  Initialize alerts
- (void)prepareAlerts
{
	// BusNameAlert.tag = 1
	self.busNameAlert = [[UIAlertView alloc] initWithTitle:@"" message:@"Set realm name" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
	self.busNameAlert.alertViewStyle = UIAlertViewStylePlainTextInput;
	self.alertDefaultBusName = [self.busNameAlert textFieldAtIndex:0]; //connect the UITextField with the alert
    
	// disconnectAlert.tag = 2
	self.disconnectAlert = [[UIAlertView alloc] initWithTitle:@"" message:@"Are you sure you want to disconnect from alljoyn?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
	self.disconnectAlert.alertViewStyle = UIAlertViewStyleDefault;
    
	// announcementOptionsAlert.tag = 3
	self.announcementOptionsAlert = [[UIAlertView alloc] initWithTitle:@"Choose option:" message:@"" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Show Announce", @"About", nil];
	self.announcementOptionsAlert.alertViewStyle = UIAlertViewStyleDefault;
    
	// onboardingOptionsAlert.tag = 4
	self.onboardingOptionsAlert = [[UIAlertView alloc] initWithTitle:@"Choose option:" message:@"" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Show Announce", @"About", @"Onboarding", nil];
	self.onboardingOptionsAlert.alertViewStyle = UIAlertViewStyleDefault;
    
}

- (void)performAnnouncementAction:(NSInteger)opt
{
	switch (opt) {
		case 0: // "Cancel"
			break;
            
		case 1: // "Show Announce"
		{
			[self performSegueWithIdentifier:@"AboutShowAnnounceSegue" sender:self];
		}
            break;
            
		case 2: // "About"
		{
			[self performSegueWithIdentifier:@"AboutClientSegue" sender:self]; // get the announcment object
            
		}
            break;
            
		case 3: // "OnBoarding"
		{
            [self performSegueWithIdentifier:@"OnboardingClientSegue" sender:self]; // get the announcment object
        }
            break;
            
		default:
			break;
	}
}

#pragma mark - AboutClient
#pragma mark start AboutClient

- (void)startAboutClient
{
	QStatus status;
    
     NSLog(@"[%@] [%@] Start About Client", @"DEBUG", [[self class] description]);

    
	// Init AJNBusAttachment
	self.clientBusAttachment = [[AJNBusAttachment alloc] initWithApplicationName:APPNAME allowRemoteMessages:ALLOWREMOTEMESSAGES];
    
	// Start AJNBusAttachment
	status = [self.clientBusAttachment start];
	if (status != ER_OK) {
         NSLog(@"[%@] [%@] Unable to connect to Start - exiting application", @"FATAL", [[self class] description]);

		exit(1);
	}
    
    // for tcl
    status = [AJNPasswordManager setCredentialsForAuthMechanism:@"ALLJOYN_PIN_KEYX" usingPassword:@"000000"];
	if (status != ER_OK) {
        NSLog(@"[%@] [%@] Failed to SetCredentials %@", @"FATAL", [[self class] description],[AJNStatus descriptionForStatusCode:status]);
        
		exit(1);
	}
    
	// Connect AJNBusAttachment
	status = [self.clientBusAttachment connectWithArguments:@""];
	if (status != ER_OK) {
         NSLog(@"[%@] [%@] Failed to connect - exiting application", @"FATAL", [[self class] description]);

		exit(1);
	}
     NSLog(@"[%@] [%@] Create aboutClientListener", @"DEBUG", [[self class] description]);
 NSLog(@"[%@] [%@] Register aboutClientListener", @"DEBUG", [[self class] description]);

	[self.clientBusAttachment registerBusListener:self];
    
	self.announcementReceiver = [[AJNAnnouncementReceiver alloc] initWithAnnouncementListener:self andBus:self.clientBusAttachment];
	status = [self.announcementReceiver registerAnnouncementReceiver];
	if (status != ER_OK) {
        NSLog(@"[%@] [%@] Failed to registerAnnouncementReceiver - exiting application", @"FATAL", [[self class] description]);

        exit(1);
	}
    
	// Create a dictionary to contain announcements using a key in the format of: "announcementUniqueName + announcementObj"
	self.clientInformationDict = [[NSMutableDictionary alloc] init];
    
	// AddMatchRule
	status = [self.clientBusAttachment addMatchRule:@"sessionless='t',type='error'"]; // This is added because we want to listen to the about announcements which are sessionless
	if (status != ER_OK) {
        NSLog(@"[%@] [%@] Failed at addMatchRule - exiting application", @"FATAL", [[self class] description]);

		exit(1);
	}
    
	// Advertise Daemon for tcl
	status = [self.clientBusAttachment requestWellKnownName:self.realmBusName withFlags:kAJNBusNameFlagDoNotQueue];
	if (status == ER_OK) {
		// Advertise the name with a quite prefix for TC to find it
		NSUUID *UUID = [NSUUID UUID];
		NSString *stringUUID = [UUID UUIDString];
        
		self.realmBusName = [self.realmBusName stringByAppendingFormat:@"-%@", stringUUID];
        
		status = [self.clientBusAttachment advertiseName:[NSString stringWithFormat:@"%@%@", DAEMON_QUIET_PREFIX, self.realmBusName] withTransportMask:kAJNTransportMaskAny];
		if (status != ER_OK) {
            NSLog(@"[%@] [%@] Failed to advertise name - exiting application %@", @"FATAL", [[self class] description],[AJNStatus descriptionForStatusCode:status]);

			status = [self.clientBusAttachment releaseWellKnownName:self.realmBusName];
            
			exit(1);
		}
		else {
            NSLog(@"[%@] [%@] Successfully advertised: %@%@", @"DEBUG", [[self class] description], DAEMON_QUIET_PREFIX, self.realmBusName);
		}
	}
	else {
        NSLog(@"[%@] [%@] Failed to requestWellKnownName - exiting application %@", @"FATAL", [[self class] description],[AJNStatus descriptionForStatusCode:status]);

		exit(1);
	}
    
    // Enable Client Security
    self.authenticationListenerImpl = [[AuthenticationListenerImpl alloc] init];
    status = [self enableClientSecurity];
    if (ER_OK != status) {
        NSLog(@"Failed to enable security.");
    } else {
        NSLog(@"Successfully enabled security for the bus");
    }

	[self.connectButton setTitle:self.ajdisconnect forState:UIControlStateNormal]; //change title to "Disconnect from AllJoyn"
	self.isAboutClientConnected = true;
}


- (QStatus)enableClientSecurity
{
    QStatus status;
    status = [self.clientBusAttachment enablePeerSecurity:@"ALLJOYN_SRP_KEYX ALLJOYN_PIN_KEYX" authenticationListener:self.authenticationListenerImpl keystoreFileName:@"Documents/alljoyn_keystore/s_central.ks" sharing:YES];
    return status;
}

- (void)addNewAnnouncemetEntry
{
	[self.servicesTable performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
}

// announcementGetMoreInfo is an IBAction triggered by pressing a dynamic announcement button
- (void)announcementGetMoreInfo:(NSInteger)requestedRow
{
	// set the announcementButtonCurrentTitle
	self.announcementButtonCurrentTitle = [self.clientInformationDict allKeys][requestedRow];
    
     NSLog(@"[%@] [%@] Requested:  [%@]", @"DEBUG", [[self class] description],self.announcementButtonCurrentTitle);
    
    // Check if announcement has icon object path
	if (![self announcementSupportsInterface:self.announcementButtonCurrentTitle]) {
		[self.announcementOptionsAlert show]; // Event is forward to alertView: clickedButtonAtIndex:
	}
	else {
		[self.onboardingOptionsAlert show]; // Event is forward to alertView: clickedButtonAtIndex:
	}
}

// Return true if an announcement supports icon interface
- (bool)announcementSupportsInterface:(NSString *)announcementKey
{
	bool supportInterface = false;
	AJNAnnouncement *announcement = [(ClientInformation *)[self.clientInformationDict valueForKey:announcementKey] announcement];
	NSMutableDictionary *announcementObjDecs = [announcement objectDescriptions]; //Dictionary of ObjectDescriptions NSStrings
    
	// iterate over the object descriptions dictionary
	for (NSString *key in announcementObjDecs.allKeys) {
		if ([key hasPrefix:ONBOARDING_OBJECT_PATH]) {
			// Iterate over the NSMutableArray
			for (NSString *intf in[announcementObjDecs valueForKey:key]) {
				if ([intf isEqualToString:(NSString *)ONBOARDING_INTERFACE_NAME]) {
					supportInterface = true;
				}
			}
		}
	}
	return supportInterface;
}

#pragma mark stop AboutClient
- (void)stopAboutClient
{
	QStatus status;
     NSLog(@"[%@] [%@] Stop About Client", @"DEBUG", [[self class] description]);
    
	// Bus attachment cleanup
	status = [self.clientBusAttachment cancelAdvertisedName:[NSString stringWithFormat:@"%@%@", DAEMON_QUIET_PREFIX, self.realmBusName] withTransportMask:kAJNTransportMaskAny];
	if (status == ER_OK) {
         NSLog(@"[%@] [%@] Successfully cancel advertised name", @"DEBUG", [[self class] description]);
	}
	status = [self.clientBusAttachment releaseWellKnownName:self.realmBusName];
	if (status == ER_OK) {
         NSLog(@"[%@] [%@] Successfully release WellKnownName", @"DEBUG", [[self class] description]);
	}
	status = [self.clientBusAttachment removeMatchRule:@"sessionless='t',type='error'"];
	if (status == ER_OK) {
         NSLog(@"[%@] [%@] Successfully remove MatchRule", @"DEBUG", [[self class] description]);
	}
    
	// Cancel advertise name for each announcement bus
	for (NSString *key in[self.clientInformationDict allKeys]) {
		ClientInformation *clientInfo = (self.clientInformationDict)[key];
		status = [self.clientBusAttachment cancelFindAdvertisedName:[[clientInfo announcement] busName]];
		if (status != ER_OK) {
             NSLog(@"[%@] [%@] failed to cancelAdvertisedName for %@. status:%@", @"ERROR", [[self class] description],key, [AJNStatus descriptionForStatusCode:status]);
		}
	}
	self.clientInformationDict = nil;
    
	status = [self.announcementReceiver unRegisterAnnouncementReceiver];
	if (status == ER_OK) {
         NSLog(@"[%@] [%@] Successfully unregistered AnnouncementReceiver", @"DEBUG", [[self class] description]);
	}
    
	self.announcementReceiver = nil;
    
	// Stop bus attachment
	status = [self.clientBusAttachment stop];
	if (status == ER_OK) {
         NSLog(@"[%@] [%@] Successfully stopped bus", @"DEBUG", [[self class] description]);
    }
	self.clientBusAttachment = nil;
    
	// Set flag
	self.isAboutClientConnected  = false;
    
	// UI cleanup
	[self.connectButton setTitle:self.ajconnect forState:UIControlStateNormal];
    
	[self.servicesTable performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
    
     NSLog(@"[%@] [%@] About Client is stopped", @"DEBUG", [[self class] description]);
}

#pragma mark UITableView delegates
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return [self.clientInformationDict count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	static NSString *MyIdentifier = @"AnnouncementCell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:MyIdentifier forIndexPath:indexPath];
    
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
	cell.textLabel.text = [self.clientInformationDict allKeys][indexPath.row];
	return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	[self announcementGetMoreInfo:indexPath.row];
}

- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{
    [self announcementGetMoreInfo:indexPath.row];
}

@end
