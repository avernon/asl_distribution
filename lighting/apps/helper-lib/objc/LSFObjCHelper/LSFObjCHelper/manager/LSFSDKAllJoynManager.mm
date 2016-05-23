/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSDKAllJoynManager.h"
#import "LSFSDKSampleGroupManager.h"
#import "LSFSDKAboutManager.h"

static ajn::BusAttachment *bus = NULL;
static LSFSDKHelperControllerClientCallback *myCCC = nil;
static LSFSDKHelperControllerServiceManagerCallback *myCSMC = nil;
static LSFSDKHelperLampManagerCallback *myLMC = nil;
static LSFSDKHelperGroupManagerCallback *myGMC = nil;
static LSFSDKHelperPresetManagerCallback *myPMC = nil;
static LSFSDKHelperSceneElementManagerCallback *mySEMC;
static LSFSDKHelperSceneManagerCallback *mySMC = nil;
static LSFSDKHelperMasterSceneManagerCallback *myMSMC = nil;
static LSFSDKHelperTransitionEffectManagerCallback *myTEMC = nil;
static LSFSDKHelperPulseEffectManagerCallback *myPEMC = nil;
static LSFControllerClient *controllerClient = nil;
static LSFControllerServiceManager *controllerServiceManager = nil;
static LSFLampManager *lampManager = nil;
static LSFLampGroupManager *groupManager = nil;
static LSFPresetManager *presetManager = nil;
static LSFSceneElementManager *sceneElementManager = nil;
static LSFSceneManager *sceneManager = nil;
static LSFMasterSceneManager *masterSceneManager = nil;
static LSFTransitionEffectManager *transitionEffectManager = nil;
static LSFPulseEffectManager *pulseEffectManager = nil;
static LSFSDKAboutManager *aboutManager = nil;
NSMutableDictionary *lampsAnnouncementData = nil;
static BOOL controllerConnected = NO;
static unsigned int controllerServiceLeaderVersion = 0;

@implementation LSFSDKAllJoynManager

+(void)initializeWithApplicationName: (NSString *)applicationName controllerClientCallback: (LSFSDKHelperControllerClientCallback *)ccc controllerServiceManagerCallback: (LSFSDKHelperControllerServiceManagerCallback *)csmc lampManagerCallback: (LSFSDKHelperLampManagerCallback *)lmc groupManagerCallback: (LSFSDKHelperGroupManagerCallback *)gmc presetManagerCallback: (LSFSDKHelperPresetManagerCallback *)pmc transitionEffectManagerCallback: (LSFSDKHelperTransitionEffectManagerCallback *)temc pulseEffectManagerCallback: (LSFSDKHelperPulseEffectManagerCallback *)pemc sceneElementManagerCallback: (LSFSDKHelperSceneElementManagerCallback *)semc sceneManagerCallback: (LSFSDKHelperSceneManagerCallback *)smc masterSceneManagerCallback: (LSFSDKHelperMasterSceneManagerCallback *)msmc
{
    ajn::BusAttachment *myBus = new ajn::BusAttachment(applicationName != nil ? [applicationName UTF8String] : "AllJoynManager");

    [self initializeWithBusAttachment: myBus controllerClientCallback: ccc controllerServiceManagerCallback: csmc lampManagerCallback: lmc groupManagerCallback: gmc presetManagerCallback: pmc transitionEffectManagerCallback: temc pulseEffectManagerCallback: pemc sceneElementManagerCallback: semc sceneManagerCallback: smc masterSceneManagerCallback: msmc];
}

+(void)initializeWithBusAttachment: (ajn::BusAttachment *)busAttachment controllerClientCallback: (LSFSDKHelperControllerClientCallback *)ccc controllerServiceManagerCallback: (LSFSDKHelperControllerServiceManagerCallback *)csmc lampManagerCallback: (LSFSDKHelperLampManagerCallback *)lmc groupManagerCallback: (LSFSDKHelperGroupManagerCallback *)gmc presetManagerCallback: (LSFSDKHelperPresetManagerCallback *)pmc transitionEffectManagerCallback: (LSFSDKHelperTransitionEffectManagerCallback *)temc pulseEffectManagerCallback: (LSFSDKHelperPulseEffectManagerCallback *)pemc sceneElementManagerCallback: (LSFSDKHelperSceneElementManagerCallback *)semc sceneManagerCallback: (LSFSDKHelperSceneManagerCallback *)smc masterSceneManagerCallback: (LSFSDKHelperMasterSceneManagerCallback *)msmc
{
    controllerConnected = NO;
    controllerServiceLeaderVersion = 0;
    bus = busAttachment;
    myCCC = ccc;
    myCSMC = csmc;
    myLMC = lmc;
    myGMC = gmc;
    myPMC = pmc;
    myTEMC = temc;
    myPEMC = pemc;
    mySEMC = semc;
    mySMC = smc;
    myMSMC = msmc;

    //Create password for Bundled Router
    QStatus status = ER_OK;
//    status = PasswordManager::SetCredentials("ALLJOYN_PIN_KEYX", "ALLJOYN_PIN_KEYX");
//    if (status != ER_OK)
//    {
//        NSLog(@"ERROR: Failed to set Password Manager Credentials");
//    }

    //Start the bus
    status = bus->Start();
    if (status != ER_OK)
    {
        NSLog(@"ERROR: Failed to start bus. %@", [NSString stringWithUTF8String: QCC_StatusText(status)]);
    }

    //Connect the bus
    status = bus->Connect();
    if (status != ER_OK)
    {
        NSLog(@"ERROR: Failed to connect bus. %@", [NSString stringWithUTF8String: QCC_StatusText(status)]);
    }

    controllerClient = [[LSFControllerClient alloc] initWithBusAttachment: busAttachment andControllerClientCallbackDelegate: myCCC];
    controllerServiceManager = [[LSFControllerServiceManager alloc] initWithControllerClient: controllerClient andControllerServiceManagerCallbackDelegate: myCSMC];
    lampManager = [[LSFLampManager alloc] initWithControllerClient: controllerClient andLampManagerCallbackDelegate: myLMC];
    groupManager = [[LSFSDKSampleGroupManager alloc] initWithControllerClient: controllerClient andLampManagerCallback: myGMC];
    presetManager = [[LSFPresetManager alloc] initWithControllerClient: controllerClient andPresetManagerCallbackDelegate: myPMC];
    sceneElementManager = [[LSFSceneElementManager alloc] initWithControllerClient: controllerClient andSceneElementManagerCallbackDelegate: mySEMC];
    sceneManager = [[LSFSceneManager alloc] initWithControllerClient: controllerClient andSceneManagerCallbackDelegate: mySMC];
    masterSceneManager = [[LSFMasterSceneManager alloc] initWithControllerClient: controllerClient andMasterSceneManagerCallbackDelegate: myMSMC];
    transitionEffectManager = [[LSFTransitionEffectManager alloc] initWithControllerClient: controllerClient andTransitionEffectManagerCallbackDelegate: myTEMC];
    pulseEffectManager = [[LSFPulseEffectManager alloc] initWithControllerClient: controllerClient andPulseEffectManagerCallbackDelegate: myPEMC];
    aboutManager = [[LSFSDKAboutManager alloc] initWithBusAttachment: busAttachment];
    lampsAnnouncementData = [[NSMutableDictionary alloc] init];
}

+(void)startWithQueue:(dispatch_queue_t)queue
{
    ControllerClientStatus status = [controllerClient start];

    if (status == CONTROLLER_CLIENT_ERR_RETRY)
    {
        NSLog(@"Controller Client start return retry. Retrying 5 seconds later");
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), queue, ^{
            [self startWithQueue: queue];
        });
    }
    else if (status == CONTROLLER_CLIENT_OK)
    {
        [aboutManager registerAnnouncementHandler];
        NSLog(@"Controller Client started successfully");
    }
}

+(void)stop
{
    [aboutManager unregisterAnnouncementHandler];

    ControllerClientStatus status = [controllerClient stop];

    if (status == CONTROLLER_CLIENT_OK)
    {
        NSLog(@"Controller Client stop returned ok");
    }
    else
    {
        NSLog(@"Controller Client stop returned some type of error");
    }
}

+(void)addNewLamp: (NSString*)lampID lampAnnouncementData: (LSFLampAnnouncementData*)lampAnnData
{
    if (!lampsAnnouncementData[lampID])
    {
        [lampsAnnouncementData setObject: lampAnnData forKey: lampID];
    }
    else
    {
        [lampsAnnouncementData setValue: lampAnnData forKey: lampID];
    }
}

+(void)getAboutDataForLampID: (NSString*)lampID
{
    LSFLampAnnouncementData* lampAnnData = [lampsAnnouncementData  objectForKey: lampID];
    if (lampAnnData != nil)
    {
        [aboutManager getAboutDataFromBusName: [lampAnnData busName] onPort: [lampAnnData port]];
    }
}

+(void)setControllerConnected: (BOOL)isConnected
{
    controllerConnected = isConnected;
}

+(BOOL)getControllerConnected
{
    return controllerConnected;
}

+(void)setControllerServiceLeaderVersion:(unsigned int)version
{
    controllerServiceLeaderVersion = version;
}

+(unsigned int)getControllerServiceLeaderVersion
{
    return controllerServiceLeaderVersion;
}

+(BOOL)isControllerServiceLeaderV1
{
    return [LSFSDKAllJoynManager getControllerServiceLeaderVersion] < 2;
}

+(LSFControllerClient *)getControllerClient
{
    return controllerClient;
}

+(LSFControllerServiceManager *)getControllerServiceManager
{
    return controllerServiceManager;
}

+(LSFLampManager *)getLampManager
{
    return lampManager;
}

+(LSFLampGroupManager *)getGroupManager
{
    return groupManager;
}

+(LSFPresetManager *)getPresetManager
{
    return presetManager;
}

+(LSFSceneElementManager *)getSceneElementManager
{
    return sceneElementManager;
}

+(LSFSceneManager *)getSceneManager
{
    return sceneManager;
}

+(LSFMasterSceneManager *)getMasterSceneManager
{
    return masterSceneManager;
}

+(LSFTransitionEffectManager *)getTransitionEffectManager
{
    return transitionEffectManager;
}

+(LSFPulseEffectManager *)getPulseEffectManager
{
    return pulseEffectManager;
}

+(LSFSDKHelperControllerClientCallback *)getControllerClientCallback
{
    return myCCC;
}

+(LSFSDKHelperControllerServiceManagerCallback *)getControllerServiceManagerCallback
{
    return myCSMC;
}

+(LSFSDKHelperLampManagerCallback *)getLampManagerCallback
{
    return myLMC;
}

+(LSFSDKHelperGroupManagerCallback *)getGroupManagerCallback
{
    return myGMC;
}

+(LSFSDKHelperPresetManagerCallback *)getPresetManagerCallback
{
    return myPMC;
}

+(LSFSDKHelperSceneElementManagerCallback *)getSceneElementManagerCallback
{
    return mySEMC;
}

+(LSFSDKHelperSceneManagerCallback *)getSceneManagerCallback
{
    return mySMC;
}

+(LSFSDKHelperMasterSceneManagerCallback *)getMasterSceneManagerCallback
{
    return myMSMC;
}

+(LSFSDKHelperTransitionEffectManagerCallback *)getTransitionEffectManagerCallback
{
    return myTEMC;
}

+(LSFSDKHelperPulseEffectManagerCallback *)getPulseEffectManagerCallback
{
    return myPEMC;
}

+(ajn::BusAttachment *)getBusAttachment
{
    return bus;
}

@end
