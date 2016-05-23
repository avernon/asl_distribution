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

#import "ConfigServiceViewController.h"
#import "AJNVersion.h"
#import "AJNPasswordManager.h"
#import "alljoyn/about/AJNAboutServiceApi.h"
#import "alljoyn/config/AJCFGPropertyStoreImpl.h"
#import "alljoyn/config/AJCFGConfigService.h"
#import "alljoyn/config/AJCFGConfigServiceListenerImpl.h"
#import "alljoyn/services_common/AJSVCGenericLoggerDefaultImpl.h"
#import "alljoyn/config/AJCFGConfigLogger.h"
#import "ConfigServiceListener.h"
#import "CommonBusListener.h"

#define DEFAULTPASSCODE @"000000"

// Property store strings
static NSString *const DEFAULT_LANGUAGE_STR = @"DefaultLanguage";
static NSString *const DEVICE_NAME_STR = @"DeviceName";
static NSString *const DEVICE_ID_STR = @"DeviceId";
static NSString *const PASS_CODE_STR = @"passcode";

static NSString *const DAEMON_QUIET_PREFIX = @"quiet@";  // About Client - quiet advertising
static NSString *const ABOUT_CONFIG_OBJECT_PATH = @"/Config";  // Config Service
static NSString *const ABOUT_CONFIG_INTERFACE_NAME = @"org.alljoyn.Config";  //Config Service
static bool ALLOWREMOTEMESSAGES = true; // About Client -  allow Remote Messages flag
static AJNSessionPort SERVICE_PORT; // About Service - service port

@interface ConfigServiceViewController ()

@property (strong, nonatomic) AJNBusAttachment *busAttachment;
@property (strong, nonatomic) AJCFGConfigServiceListenerImpl *configServiceListenerImpl;
@property (strong, nonatomic) AJCFGConfigService *configService;
@property (strong, nonatomic) AJCFGPropertyStoreImpl *propertyStore;
@property (strong, nonatomic) CommonBusListener *aboutSessionPortListener;
@property (strong, nonatomic) ConfigServiceListener *configServiceListener;
@property (strong, nonatomic) AJNAboutServiceApi *aboutServiceApi;
@property (strong, nonatomic) AJSVCGenericLoggerDefaultImpl *logger;

@property (nonatomic) bool isServiceOn;
@property (strong, nonatomic) NSString *uniqueID;
@property (nonatomic, strong) NSString *password;
@property (weak, nonatomic) IBOutlet UIButton *btnStartStopService;

@end

@implementation ConfigServiceViewController

- (void)viewDidLoad
{
	[super viewDidLoad];
    
	// create unique ID*/
	self.uniqueID = [[NSUUID UUID] UUIDString];
	self.isServiceOn = NO;
    
	self.logger = [[AJCFGConfigLogger sharedInstance] logger];
}

- (QStatus)startAboutService
{
	QStatus serviceStatus;
    
	// Set port
	int port = 900;
	SERVICE_PORT = (AJNSessionPort)port;
    
	serviceStatus = [AJNPasswordManager setCredentialsForAuthMechanism:@"ALLJOYN_PIN_KEYX" usingPassword:@"000000"];
	if (serviceStatus != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to SetCredentials: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
		exit(1);
	}
    
	// Create message bus
	self.busAttachment = [[AJNBusAttachment alloc] initWithApplicationName:@"ConfigService" allowRemoteMessages:ALLOWREMOTEMESSAGES];
	if (!self.busAttachment) {
		[self.logger errorTag:[[self class] description] text:@"Failed to create a message bus - exiting application."];
		serviceStatus = ER_OUT_OF_MEMORY;
		return serviceStatus;
	}
    
	//start the bus
	serviceStatus = [self.busAttachment start];
	if (serviceStatus != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to start bus - exiting application %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
		return serviceStatus;
	}
    
	// Allocate and fill property store
	self.propertyStore = [[AJCFGPropertyStoreImpl alloc] initPointerToFactorySettingFile:[[NSBundle mainBundle] pathForResource:@"FactoryProperties" ofType:@"plist"]];
    
	serviceStatus = [self fillAboutPropertyStoreImplData];
    
	if (serviceStatus != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to fill propertyStore - exiting application: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
		return serviceStatus;
	}
    
	serviceStatus = [self.busAttachment connectWithArguments:@""];
	if (serviceStatus != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to connectWithArguments - exiting application: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
	}
    
	self.aboutSessionPortListener = [[CommonBusListener alloc] initWithServicePort:(SERVICE_PORT)];
    
	if (self.aboutSessionPortListener) {
		[self.busAttachment registerBusListener:self.aboutSessionPortListener];
	}
    
	[self.logger debugTag:[[self class] description] text:@"Create aboutServiceApi"];
	self.aboutServiceApi = [AJNAboutServiceApi sharedInstance];
	if (!self.aboutServiceApi) {
		serviceStatus =  ER_BUS_NOT_ALLOWED;
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to create aboutServiceApi - exiting application: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
		return serviceStatus;
	}
    
	[self.logger debugTag:[[self class] description] text:@"Start aboutServiceApi"];
	[self.aboutServiceApi startWithBus:self.busAttachment andPropertyStore:self.propertyStore];
    
	//Register Port
	[self.logger debugTag:[[self class] description] text:@"Register the AboutService on the AllJoyn bus"];
	if (self.aboutServiceApi.isServiceStarted) {
		serviceStatus = [self.aboutServiceApi registerPort:(SERVICE_PORT)];
	}
    
	if (serviceStatus != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed register port - exiting application: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
		return serviceStatus;
	}
    
	// bind session port
	AJNSessionOptions *opt = [[AJNSessionOptions alloc] initWithTrafficType:(kAJNTrafficMessages) supportsMultipoint:(false) proximity:(kAJNProximityAny) transportMask:(kAJNTransportMaskAny)];
	[self.logger debugTag:[[self class] description] text:@"Bind session"];
	serviceStatus = [self.busAttachment bindSessionOnPort:SERVICE_PORT withOptions:opt withDelegate:self.aboutSessionPortListener];
    
	if (serviceStatus == ER_ALLJOYN_BINDSESSIONPORT_REPLY_ALREADY_EXISTS) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"SessionPort already exists: %@", [AJNStatus descriptionForStatusCode:serviceStatus]]];
	}
	return serviceStatus;
}

- (QStatus)startConfigService
{
	QStatus status;
    
	status = [self startAboutService];
	if (status != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"About service failed to start: %@", [AJNStatus descriptionForStatusCode:status]]];
		return status;
	}
    
	status = [self enableServiceSecurity];
    
	if (ER_OK != status) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to enable security on the bus: %@", [AJNStatus descriptionForStatusCode:status]]];
	}
	else {
		[self.logger debugTag:[[self class] description] text:@"Successfully enabled security for the bus"];
	}
    
	self.configServiceListener = [[ConfigServiceListener alloc] initWithPropertyStore:self.propertyStore andBus:self.busAttachment];
    
	self.configServiceListenerImpl = [[AJCFGConfigServiceListenerImpl alloc] initWithConfigServiceListener:self.configServiceListener];
    
	self.configService = [[AJCFGConfigService alloc] initWithBus:self.busAttachment propertyStore:self.propertyStore listener:self.configServiceListenerImpl];
    
	// Set logger
	self.logger = [[AJSVCGenericLoggerDefaultImpl alloc] init];
	[self.configService setLogger:self.logger];
    
	NSMutableArray *interfaces = [[NSMutableArray alloc] init];
	[interfaces addObject:ABOUT_CONFIG_INTERFACE_NAME];
	NSString *path = ABOUT_CONFIG_OBJECT_PATH;
	status = [self.aboutServiceApi addObjectDescriptionWithPath:path andInterfaceNames:interfaces];
    
	if (status != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to addObjectDescription: %@", [AJNStatus descriptionForStatusCode:status]]];
		return status;
	}
    
	status = [self.configService registerService];
	if (status != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to register configService: %@", [AJNStatus descriptionForStatusCode:status]]];
		return status;
	}
    
	status = [self.busAttachment registerBusObject:(AJNBusObject *)self.configService];
	if (status != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to register registerBusObject: %@", [AJNStatus descriptionForStatusCode:status]]];
		return status;
	}
    
	status = [self.busAttachment advertiseName:[self.busAttachment uniqueName] withTransportMask:kAJNTransportMaskAny];
	if (status != ER_OK) {
		[self.logger errorTag:[[self class] description] text:[NSString stringWithFormat:@"Failed to advertiseName [%@]: %@", [self.busAttachment uniqueName], [AJNStatus descriptionForStatusCode:status]]];
		return status;
	}
    
	if (status == ER_OK) {
		if (self.aboutServiceApi.isServiceStarted) {
			[self.logger debugTag:[[self class] description] text:@"Calling Announce"];
			status = [self.aboutServiceApi announce];
		}
		if (status == ER_OK) {
			[self.logger debugTag:[[self class] description] text:@"Successfully announced"];
		}
	}
    
	return status;
}

- (QStatus)enableServiceSecurity
{
	QStatus status;
    
	status = [self.busAttachment enablePeerSecurity:@"ALLJOYN_SRP_KEYX ALLJOYN_PIN_KEYX" authenticationListener:self keystoreFileName:@"Documents/alljoyn_keystore/s_central.ks" sharing:YES];
	return status;
}

- (void)stopAboutService
{
	QStatus status;
    
	[self.logger debugTag:[[self class] description] text:@"Stop About Service"];
	// Delete AboutPropertyStoreImpl
	self.propertyStore = nil;
    
	// BusAttachment cleanup
	status = [self.busAttachment cancelAdvertisedName:[self.busAttachment uniqueName] withTransportMask:kAJNTransportMaskAny];
	if (status == ER_OK) {
		[self.logger debugTag:[[self class] description] text:@"Successfully cancel advertised nam"];
	}
    
	status = [self.busAttachment unbindSessionFromPort:SERVICE_PORT];
	if (status == ER_OK) {
		[self.logger debugTag:[[self class] description] text:@"Successfully unbind Session"];
	}
    
	// Delete AboutSessionPortListener
	[self.busAttachment unregisterBusListener:self.aboutSessionPortListener];
	self.aboutSessionPortListener = nil;
    
	// Stop bus attachment
	status = [self.busAttachment stop];
	if (status == ER_OK) {
		[self.logger debugTag:[[self class] description] text:@"Successfully stopped bus"];
	}
	self.busAttachment = nil;
} /* stopAboutService */

- (void)stopConfigService
{
	// Delete AboutServiceApi
	[self.aboutServiceApi destroyInstance];
    
	self.aboutServiceApi = nil;
    
	self.configService = nil;
    
	self.configServiceListenerImpl = nil;
    
	self.configServiceListener = nil;
    
	[self stopAboutService];
}

- (IBAction)touchUpInsideStartStopBtn:(UIButton *)sender
{
	QStatus status;
	if (self.isServiceOn == NO) {
		status = [self startConfigService];
        
		if (status == ER_OK) {
			[sender setTitle:@"Stop Service" forState:UIControlStateNormal];
			self.isServiceOn = YES;
		}
		else {
			[[[UIAlertView alloc] initWithTitle:@"Start Config Service Failed" message:[NSString stringWithFormat:@"Error occured:%@", [AJNStatus descriptionForStatusCode:status]] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil] show];
		}
	}
	else {
		[self stopConfigService];
		[sender setTitle:@"Start Service" forState:UIControlStateNormal];
		self.isServiceOn = NO;
	}
}

- (QStatus)fillAboutPropertyStoreImplData
{
	QStatus status;
    
	// AppId
	status = [self.propertyStore setAppId:self.uniqueID];
	if (status != ER_OK) return status;
    
	// AppName
	status = [self.propertyStore setAppName:@"AboutConfig"];
	if (status != ER_OK) return status;
    
	// DeviceId
	status = [self.propertyStore setDeviceId:@"1231232145667745675477"];
	if (status != ER_OK) return status;
    
	// DeviceName
	NSString *value = [self.propertyStore getPersistentValue:DEVICE_NAME_STR];
    
	value = (value ? value : @"iOS_Service"); // check that we don't have a persistent value
    
	status = [self.propertyStore setDeviceName:value];
	if (status != ER_OK) return status;
    
	// SupportedLangs
	NSArray *languages = @[@"en", @"sp", @"fr"];
	status = [self.propertyStore setSupportedLangs:languages];
	if (status != ER_OK) return status;
    
	// DefaultLang
	value = [self.propertyStore getPersistentValue:DEFAULT_LANGUAGE_STR];
    
	value = (value ? value : @"en"); // check that we don't have a persistent value
    
	status = [self.propertyStore setDefaultLang:value];
	if (status != ER_OK) return status;
    
	// ModelNumber
	status = [self.propertyStore setModelNumber:@"Wxfy388i"];
	if (status != ER_OK) return status;
    
	// DateOfManufacture
	status = [self.propertyStore setDateOfManufacture:@"10/1/2199"];
	if (status != ER_OK) return status;
    
	// SoftwareVersion
	status = [self.propertyStore setSoftwareVersion:@"12.20.44 build 44454"];
	if (status != ER_OK) return status;
    
	// AjSoftwareVersion
	status = [self.propertyStore setAjSoftwareVersion:[AJNVersion versionInformation]];
	if (status != ER_OK) return status;
    
	// HardwareVersion
	status = [self.propertyStore setHardwareVersion:@"355.499. b"];
	if (status != ER_OK) return status;
    
	// Description
	status = [self.propertyStore setDescription:@"This is an Alljoyn Application" language:@"en"];
	if (status != ER_OK) return status;
    
	status = [self.propertyStore setDescription:@"Esta es una Alljoyn aplicación" language:@"sp"];
	if (status != ER_OK) return status;
    
	status = [self.propertyStore setDescription:@"C'est une Alljoyn application"  language:@"fr"];
	if (status != ER_OK) return status;
    
	// Manufacturer
	status = [self.propertyStore setManufacturer:@"Company" language:@"en"];
	if (status != ER_OK) return status;
    
	status = [self.propertyStore setManufacturer:@"Empresa" language:@"sp"];
	if (status != ER_OK) return status;
    
	status = [self.propertyStore setManufacturer:@"Entreprise" language:@"fr"];
	if (status != ER_OK) return status;
    
	status = [self.propertyStore setPasscode:DEFAULTPASSCODE];
	if (status != ER_OK) return status;
    
	// SupportedUrl
	status = [self.propertyStore setSupportUrl:@"http://www.alljoyn.org"];
	if (status != ER_OK) return status;
    
	return status;
}

#pragma mark - AJNAuthenticationListener protocol methods
- (AJNSecurityCredentials *)requestSecurityCredentialsWithAuthenticationMechanism:(NSString *)authenticationMechanism peerName:(NSString *)peerName authenticationCount:(uint16_t)authenticationCount userName:(NSString *)userName credentialTypeMask:(AJNSecurityCredentialType)mask
{
	AJNSecurityCredentials *creds = nil;
	[self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"RequestSecurityCredentialsWithAuthenticationMechanism:%@ forRemotePeer%@ userName:%@", authenticationMechanism, peerName, userName]];
    
	if ([authenticationMechanism isEqualToString:@"ALLJOYN_SRP_KEYX"] || [authenticationMechanism isEqualToString:@"ALLJOYN_PIN_KEYX"]) {
		if (mask & kAJNSecurityCredentialTypePassword) {
			if (authenticationCount <= 3) {
				creds = [[AJNSecurityCredentials alloc] init];
				creds.password = [self.propertyStore getPasscode];
			}
		}
	}
	return creds;
}

- (void)authenticationUsing:(NSString *)authenticationMechanism forRemotePeer:(NSString *)peerName didCompleteWithStatus:(BOOL)success
{
	NSString *status;
	status = (success == YES ? @"was successful" : @"failed");
	[self.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"Authentication using:%@ for remote peer%@ %@", authenticationMechanism, peerName, status]];
}

@end
