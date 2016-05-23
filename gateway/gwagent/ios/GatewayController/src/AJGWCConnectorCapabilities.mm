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

#import "AJGWCConnectorCapabilities.h"
//#import "AJNMessageArgument.h"
#import "AJGWCRuleObjectDescription.h"

@interface AJGWCConnectorCapabilities ()

@property (nonatomic) ajn::gwc::ConnectorCapabilities* handle;

@end

@implementation AJGWCConnectorCapabilities

- (id)initWithHandle:(ajn::gwc::ConnectorCapabilities *) handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::ConnectorCapabilities *)handle;
    }
    return self;

}

//- (id)initWithConnectorCapabilities:(AJNMessageArgument*) manifRules
//{
//    self = [super init];
//    if (self) {
//        self.handle = new ajn::gwc::ConnectorCapabilities((ajn::MsgArg*)manifRules.handle);
//    }
//    return self;
//}

- (NSArray*)exposedServices
{
    std::vector<ajn::gwc::RuleObjectDescription*> exposedServicesVect = self.handle->getExposedServices();
    NSMutableArray* exposedServicesArray = [[NSMutableArray alloc] init];

    // Populate NSMutableArray with std::vector data;
    for (std::vector<ajn::gwc::RuleObjectDescription*>::const_iterator vectIt = exposedServicesVect.begin(); vectIt != exposedServicesVect.end(); vectIt++) {
        [exposedServicesArray addObject:[[AJGWCRuleObjectDescription alloc] initWithHandle:*vectIt]];
    }

    return exposedServicesArray;
}

- (NSArray*)remotedServices
{
    std::vector<ajn::gwc::RuleObjectDescription*> remotedServicesVect = self.handle->getRemotedServices();

    NSMutableArray* remotedServicesArray = [[NSMutableArray alloc] init];;
    // Populate NSMutableArray with std::vector data
    for (std::vector<ajn::gwc::RuleObjectDescription*>::const_iterator vectIt = remotedServicesVect.begin(); vectIt != remotedServicesVect.end(); vectIt++) {
        [remotedServicesArray addObject:[[AJGWCRuleObjectDescription alloc] initWithHandle:*vectIt]];
    }
    return remotedServicesArray;
}

- (ajn::gwc::ConnectorCapabilities*)handle
{
    return _handle;
}
@end
