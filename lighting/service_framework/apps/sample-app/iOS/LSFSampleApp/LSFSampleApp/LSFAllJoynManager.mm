/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import "LSFAllJoynManager.h"
#import "AJNPasswordManager.h"
#import "LSFSampleLampGroupManager.h"
#import "LSFDispatchQueue.h"

@interface LSFAllJoynManager()

@property (nonatomic, strong) dispatch_queue_t backgroundQueue;
@property (nonatomic, strong) NSMutableDictionary *lampsAnnouncementData;

@end

@implementation LSFAllJoynManager

@synthesize bus = _bus;
@synthesize lsfControllerClient = _lsfControllerClient;
@synthesize lsfControllerServiceManager = _lsfControllerServiceManager;
@synthesize lsfLampManager = _lsfLampManager;
@synthesize lsfPresetManager = _lsfPresetManager;
@synthesize lsfLampGroupManager = _lsfLampGroupManager;
@synthesize lsfSceneManager = _lsfSceneManager;
@synthesize lsfMasterSceneManager = _lsfMasterSceneManager;
@synthesize isConnectedToController = _isConnectedToController;
@synthesize sccc = _sccc;
@synthesize scsmc = _scsmc;
@synthesize slmc = _slmc;
@synthesize spmc = _spmc;
@synthesize slgmc = _slgmc;
@synthesize ssmc = _ssmc;
@synthesize smsmc = _smsmc;
@synthesize backgroundQueue = _backgroundQueue;
@synthesize aboutManager = _aboutManager;
@synthesize lampsAnnouncementData = _lampsAnnouncementData;

+(LSFAllJoynManager *)getAllJoynManager
{
    static LSFAllJoynManager *ajManager = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        NSLog(@"Creating LSFAllJoynManager instance");
        ajManager = [[self alloc] init];
    });
    
    return ajManager;
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        //NSLog(@"LSFAllJoynManager - init() function executing");
        
        self.isConnectedToController = NO;
        
        //Create dispatch queue and callback objects
        self.backgroundQueue = ([LSFDispatchQueue getDispatchQueue]).queue;
        self.sccc = [[LSFSampleControllerClientCallback alloc] init];
        self.scsmc = [[LSFSampleControllerServiceManagerCallback alloc] init];
        self.slmc = [[LSFSampleLampManagerCallback alloc] init];
        self.slgmc = [[LSFSampleLampGroupManagerCallback alloc] init];
        self.spmc = [[LSFSamplePresetManagerCallback alloc] init];
        self.ssmc = [[LSFSampleSceneManagerCallback alloc] init];
        self.smsmc = [[LSFSampleMasterSceneManagerCallback alloc] init];
        
        //Create Bus
        QStatus status = ER_OK;
        self.bus = [[AJNBusAttachment alloc] initWithApplicationName: @"LSFSampleController" allowRemoteMessages: YES];
        
        //Create password for Bundled Router
        status = [AJNPasswordManager setCredentialsForAuthMechanism: @"ALLJOYN_PIN_KEYX" usingPassword: @"000000"];
        if (status != ER_OK)
        {
            NSLog(@"ERROR: Failed to set Password Manager Credentials");
        }
        
        //Start the bus
        status = [self.bus start];
        if (status != ER_OK)
        {
            NSLog(@"ERROR: Failed to start bus. %@", [AJNStatus descriptionForStatusCode: status]);
        }
        
        //Connect the bus
        status = [self.bus connectWithArguments: @"null:"];
        if (status != ER_OK)
        {
            NSLog(@"ERROR: Failed to connect bus. %@", [AJNStatus descriptionForStatusCode: status]);
        }
        
//        status = [self.bus requestWellKnownName: @"org.alljoyn.BusNode" withFlags: kAJNBusNameFlagDoNotQueue];
//        if (status != ER_OK)
//        {
//            NSLog(@"ERROR: Failed to get well-known name for bundled router");
//        }
//        
//        status = [self.bus advertiseName: @"quiet@org.alljoyn.BusNode" withTransportMask: kAJNTransportMaskAny];
//        if (status != ER_OK)
//        {
//            NSLog(@"ERROR: Failed to advertise well-known name for bundled router");
//        }
        
        self.lsfControllerClient = [[LSFControllerClient alloc] initWithBusAttachment: self.bus andControllerClientCallbackDelegate: self.sccc];
        self.lsfControllerServiceManager = [[LSFControllerServiceManager alloc] initWithControllerClient: self.lsfControllerClient andControllerServiceManagerCallbackDelegate: self.scsmc];
        self.lsfLampManager = [[LSFLampManager alloc] initWithControllerClient: self.lsfControllerClient andLampManagerCallbackDelegate: self.slmc];
        self.lsfLampGroupManager = [[LSFSampleLampGroupManager alloc] initWithControllerClient: self.lsfControllerClient andLampManagerCallbackDelegate: self.slgmc];
        self.lsfPresetManager = [[LSFPresetManager alloc] initWithControllerClient: self.lsfControllerClient andPresetManagerCallbackDelegate: self.spmc];
        self.lsfSceneManager = [[LSFSceneManager alloc] initWithControllerClient: self.lsfControllerClient andSceneManagerCallbackDelegate: self.ssmc];
        self.lsfMasterSceneManager = [[LSFMasterSceneManager alloc] initWithControllerClient: self.lsfControllerClient andMasterSceneManagerCallbackDelegate: self.smsmc];
        self.aboutManager = [[LSFAboutManager alloc] initWithBusAttachment: self.bus];
        self.lampsAnnouncementData = [[NSMutableDictionary alloc] init];
    }
    
    return self;
}

-(void)addNewLamp: (NSString*)lampID lampAnnouncementData: (LSFLampAnnouncementData*)lampAnnData
{
    if (!self.lampsAnnouncementData[lampID])
    {
        [self.lampsAnnouncementData setObject: lampAnnData forKey: lampID];
    }
    else
    {
        [self.lampsAnnouncementData setValue: lampAnnData forKey: lampID];
    }
}

-(void)getAboutDataForLampID: (NSString*)lampID
{
    LSFLampAnnouncementData* lampAnnData = [self.lampsAnnouncementData  objectForKey: lampID];
    [self.aboutManager getAboutDataFromBusName: [lampAnnData busName] onPort: [lampAnnData port]];
}
@end
