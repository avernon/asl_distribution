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

#import "AJGWCRuleObjectDescription.h"
#import "AJGWCRuleInterface.h"

@interface AJGWCRuleObjectDescription ()

@property (nonatomic) ajn::gwc::RuleObjectDescription* handle;

@end

@implementation AJGWCRuleObjectDescription

- (id)initWithHandle:(ajn::gwc::RuleObjectDescription *) handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::RuleObjectDescription *)handle;
    }
    return self;
}

- (id)initWithObjectPath:(AJGWCRuleObjectPath*) objectPath interfaces:(NSSet*) interfaces
{
    self = [super init];
    std::set<ajn::gwc::RuleInterface> interfacesSet;

    if (self) {
        // Populate std::set with NSArray data
        for (AJGWCRuleInterface* connAppInterface in interfaces) {
            interfacesSet.insert(*[connAppInterface handle]);
        }

        self.handle = new ajn::gwc::RuleObjectDescription(*[objectPath handle], interfacesSet);
    }
    return self;
}

- (id)initWithObjectPath:(AJGWCRuleObjectPath*) objectPath interfaces:(NSSet*) interfaces isConfigured:(bool) isConfigured
{
    self = [super init];
    std::set<ajn::gwc::RuleInterface> interfacesSet;
    if (self) {
        // Populate std::set with NSSet data
        for (AJGWCRuleInterface* connAppInterface in interfaces) {
            interfacesSet.insert(*[connAppInterface handle]);
        }
        self.handle = new ajn::gwc::RuleObjectDescription(*[objectPath handle], interfacesSet, isConfigured);
    }
    return self;
}

- (AJGWCRuleObjectPath*)objectPath
{
    return [[AJGWCRuleObjectPath alloc] initWithHandle:self.handle->getObjectPath()];
}

- (NSSet*)interfaces
{
    NSMutableSet* interfacesSet = [[NSMutableSet alloc] init];
    const std::set<ajn::gwc::RuleInterface>* interfacesVect = self.handle->getInterfaces();

    // Populate NSArray with std::set data
    for (std::set<ajn::gwc::RuleInterface>::const_iterator it = (*interfacesVect).begin(); it != (*interfacesVect).end(); it++) {
        [interfacesSet addObject:[[AJGWCRuleInterface alloc] initWithHandle:*it]];
    }

    return interfacesSet;
}

- (bool)isConfigured
{
    return self.handle->isConfigured();
}

- (void)setConfigured:(bool) configured
{
    self.handle->setConfigured(configured);
}

- (ajn::gwc::RuleObjectDescription*)handle
{
    return _handle;
}
@end
