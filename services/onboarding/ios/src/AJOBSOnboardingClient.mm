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

#import "AJOBSOnboardingClient.h"
#import "alljoyn/onboarding/OnboardingClient.h"
#import "alljoyn/onboarding/Onboarding.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJOBOnboardingClientListenerAdapter.h"


@interface AJOBSOnboardingClient ()
@property ajn::services::OnboardingClient *handle;
@property (nonatomic) AJOBOnboardingClientListenerAdapter * onboardingListenerAdapter;
@end

@implementation AJOBSOnboardingClient

- (void)dealloc
{
    delete self.handle;
    delete self.onboardingListenerAdapter;
}

-(id)initWithBus:(AJNBusAttachment*) bus listener:(id <AJOBOnboardingClientListener>) listener
{
    self = [super init];
    if (self) {
        self.onboardingListenerAdapter = new AJOBOnboardingClientListenerAdapter(listener);
        self.handle = new ajn::services::OnboardingClient((ajn::BusAttachment&)(*bus.handle), *self.onboardingListenerAdapter);
    }
    return self;
}

-(QStatus)configureWiFi:(NSString*) busName obInfo:(AJOBInfo&) ajOBInfo resultStatus:(short&) resultStatus sessionId:(AJNSessionId) sessionId
{
    // prepare OBInfo
    ajn::services::OBInfo obInfo;
    obInfo = [AJOBSOnboarding toOBInfo:ajOBInfo];
    QStatus status = self.handle->ConfigureWiFi([AJNConvertUtil convertNSStringToConstChar:busName], obInfo, resultStatus, sessionId);
    return status;
}

-(QStatus)configureWiFi:(NSString*) busName obInfo:(AJOBInfo&)obInfo resultStatus:(short&) resultStatus
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return [self configureWiFi:busName obInfo:obInfo resultStatus:resultStatus sessionId:0];
}

-(QStatus)connectTo:(NSString*) busName sessionId:(AJNSessionId) sessionId
{
    return self.handle->ConnectTo([AJNConvertUtil convertNSStringToConstChar:busName], sessionId);
}

-(QStatus)connectTo:(NSString*) busName
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return[self connectTo:busName sessionId:0];
}


-(QStatus)offboardFrom:(NSString*) busName sessionId:(AJNSessionId) sessionId
{
    return self.handle->OffboardFrom([AJNConvertUtil convertNSStringToConstChar:busName], sessionId);
}


-(QStatus)offboardFrom:(NSString*) busName
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return [self offboardFrom:busName sessionId:0];
}

-(QStatus)version:(NSString*) busName version:(int&) version sessionId:(AJNSessionId) sessionId
{
    return self.handle->GetVersion([AJNConvertUtil convertNSStringToConstChar:busName], version, sessionId);
}

-(QStatus)version:(NSString*) busName version:(int&) version
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return [self version:busName version:version sessionId:0];
}


-(QStatus)state:(NSString*) busName state:(short&) state sessionId:(AJNSessionId) sessionId
{
    return self.handle->GetState([AJNConvertUtil convertNSStringToConstChar:busName], state, sessionId);
}

-(QStatus)state:(NSString*) busName state:(short&) state
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return [self state:busName state:state sessionId:0];
}


-(QStatus)lastError:(NSString*) busName lastError:(AJOBLastError&) lastError sessionId:(AJNSessionId) sessionId
{
    ajn::services::OBLastError obLastError;
    QStatus status = self.handle->GetLastError([AJNConvertUtil convertNSStringToConstChar:busName], obLastError, sessionId);
    lastError = [AJOBSOnboarding toAJOBLastError:obLastError];
    return status;
}


-(QStatus)lastError:(NSString*) busName lastError:(AJOBLastError&) lastError
{
    NSLog(@"No sessionId has been specified - the service will find an existing route to end point rather than access directly.");
    return [self lastError:busName lastError:lastError sessionId:0];
}
@end
