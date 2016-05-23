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

#import "AJGWCConnectorAppStatus.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJGWCEnums.h"

@interface AJGWCConnectorAppStatus ()

@property (nonatomic) ajn::gwc::ConnectorAppStatus* handle;

@end

@implementation AJGWCConnectorAppStatus

- (id)initWithHandle:(ajn::gwc::ConnectorAppStatus *)handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::ConnectorAppStatus *)handle;
    }
    return self;
}

//- (id)initWithAppStatus:(AJNMessageArgument*) appStatus
//{
//    self = [super init];
//    if (self) {
//        self.handle = new ajn::gwc::ConnectorAppStatus((ajn::MsgArg*)appStatus.handle);
//    }
//    return self;
//}

- (id)initWithInstallStatus:(AJGWCInstallStatus) installStatus installDescription:(NSString*) installDescription connectionStatus:(AJGWCConnectionStatus) connectionStatus operationalStatus:(AJGWCOperationalStatus) operationalStatus
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::ConnectorAppStatus();
        QStatus status = self.handle->init((ajn::gwc::InstallStatus)installStatus, [AJNConvertUtil convertNSStringToQCCString:installDescription], (ajn::gwc::ConnectionStatus)connectionStatus, (ajn::gwc::OperationalStatus)operationalStatus);

        if (status != ER_OK) {
            delete self.handle;
            self.handle = NULL;

            NSLog(@"Failed initializing ajn::gwc::ConnectorAppStatus");
            return nil;
        }


    }
    return self;
}

- (AJGWCInstallStatus)installStatus
{
    return (AJGWCInstallStatus)self.handle->getInstallStatus();
}

- (NSString*)installDescriptions
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getInstallDescriptions()];
}

- (AJGWCConnectionStatus)connectionStatus
{
    return (AJGWCConnectionStatus)self.handle->getConnectionStatus();
}

- (AJGWCOperationalStatus)operationalStatus
{
    return (AJGWCOperationalStatus)self.handle->getOperationalStatus();
}

@end
