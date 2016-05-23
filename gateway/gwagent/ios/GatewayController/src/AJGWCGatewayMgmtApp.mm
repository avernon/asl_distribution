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

#import "AJGWCGatewayMgmtApp.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJGWCConnectorApp.h"
#import "AJGWCSessionListenerAdapter.h"
#import "AJNStatus.h"

@interface AJGWCGatewayMgmtApp ()

@property (nonatomic) ajn::gwc::GatewayMgmtApp* handle;
@property (nonatomic) AJGWCSessionListenerAdapter* adapter;

@end

@implementation AJGWCGatewayMgmtApp

- (void)dealloc
{
    delete self.adapter;
    self.adapter = NULL;
}

- (id)initWithHandle:(ajn::gwc::GatewayMgmtApp*)handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::GatewayMgmtApp *)handle;
    }
    return self;
}

- (id)initWithbusUniqueName:(NSString*) busUniqueName aboutData:(NSDictionary *) aboutData
{
    self = [super init];
    if (self) {
        ajn::services::AboutClient::AboutData aboutDataMap;
        //Populate AboutData with NSDictionary data
        for(NSString* key in aboutData.allKeys) {
            qcc::String aboutDataMapKey = [AJNConvertUtil convertNSStringToQCCString:key]; // key
            ajn::MsgArg* aboutDataMapVal = (ajn::MsgArg*)[[aboutData objectForKey:key] handle]; //value
            aboutDataMap.insert(std::make_pair(aboutDataMapKey, *aboutDataMapVal));
        }
        self.handle = new ajn::gwc::GatewayMgmtApp();
        QStatus status = self.handle->init([AJNConvertUtil convertNSStringToQCCString:busUniqueName], aboutDataMap);
        if (status != ER_OK) {
            return nil;
        }
    }
    return self;
}

- (QStatus)retrieveConnectorApps:(AJNSessionId) sessionId connectorApps:(NSMutableArray*) connectorApps

{
    std::vector<ajn::gwc::ConnectorApp*> connectorAppsVect;
    QStatus status = self.handle->retrieveConnectorApps(sessionId, connectorAppsVect);

    // Populate NSMutableArray with std::vector data
    for (std::vector<ajn::gwc::ConnectorApp*>::const_iterator vectIt = connectorAppsVect.begin(); vectIt != connectorAppsVect.end(); vectIt++) {
        [connectorApps addObject:[[AJGWCConnectorApp alloc] initWithHandle:*vectIt]];
    }
    return status;
}

- (AJGWCSessionResult*)joinSession
{
    ajn::gwc::SessionResult ret = self.handle->joinSession();
    return [[AJGWCSessionResult alloc]initWithStatus:ret.m_status sid:ret.m_sid];
}

- (AJGWCSessionResult*)joinSession:(id<AJGWCSessionListener>) listener
{
    self.adapter = new AJGWCSessionListenerAdapter(listener);
    ajn::gwc::SessionResult ret = self.handle->joinSession(self.adapter);
    return [[AJGWCSessionResult alloc]initWithStatus:ret.m_status sid:ret.m_sid];
}

- (QStatus)joinSessionAsync:(id<AJGWCSessionListener>) listener
{
    self.adapter = new AJGWCSessionListenerAdapter(listener);
    return self.handle->joinSessionAsync(self.adapter);
}

- (QStatus)leaveSession
{
    return self.handle->leaveSession();
}

- (id<AJGWCSessionListener>)listener
{
    return self.adapter->getListener();
}

@end
