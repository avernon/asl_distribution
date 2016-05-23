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

#import "AclRulesContainer.h"
#import "alljoyn/gateway/AJGWCAclRules.h"
#import "alljoyn/gateway/AJGWCRemotedApp.h"

@interface AclRulesContainer ()

@property (strong,nonatomic) AJGWCAclRules *ajgwcAclRules;
@property (strong,nonatomic) NSMutableArray *aclRulesArray; // array of arrays of AclRules objects. position 0 is "Exposed Services" AclRules objects. each entry from 1 corresponds to a remotedApp from ajgwcAclRules

@end

@implementation AclRulesContainer
- (instancetype)initWithACL:(AJGWCAcl *)acl UsingSessionId:(AJNSessionId)sessionId connectorCapabilities:(AJGWCConnectorCapabilities *)connectorCapabilities announcements:(NSArray *)announcements status:(QStatus &)status
{
    self = [super init];
    if (self) {
        self.aclRulesArray = [[NSMutableArray alloc]init];

        AJGWCAclRules *tmpAclRules;
        status = [acl retrieveUsingSessionId:sessionId connectorCapabilities:connectorCapabilities announcements:announcements aclRules:&tmpAclRules];
        self.ajgwcAclRules = tmpAclRules;
        if (status != ER_OK) {
            return nil;
        }

        VisualAclRules *exposeServicesRules = [[VisualAclRules alloc]initWithArrayOfRuleObjectDescription:[self.ajgwcAclRules exposedServices]];

        self.aclRulesArray[0] = exposeServicesRules;

        int pos = 1;
        for (AJGWCRemotedApp *remotedApp in [self.ajgwcAclRules  remotedApps]) {
            VisualAclRules *remotedAppRules = [[VisualAclRules alloc]initWithArrayOfRuleObjectDescription:[remotedApp ruleObjDescriptions]];

            self.aclRulesArray[pos] = remotedAppRules;
            pos++;
        }
    }
    return self;
}

- (NSUInteger) numberOfEntries
{
    return [self.aclRulesArray count];
}

- (NSString *) entryNameAt:(NSUInteger)pos
{
    if (pos == 0) {
        return @"Exposed Services";
    } else {
    return [self.ajgwcAclRules.remotedApps[pos-1] appName];
    }
}

- (VisualAclRules *)aclRulesForSection:(NSInteger)section;
{
    return self.aclRulesArray[section];
}

- (AJGWCRemotedApp *)findRemotedAppInAjgwcAclRules:(NSInteger)pos
{
    return self.ajgwcAclRules.remotedApps[pos -1];
}

- (AJGWCAclRules *)createAJGWCAclRules
{
    AJGWCAclRules *rules = nil;

    // Create a list of AJGWCRuleObjectDescription based on the configured exposed services rules
    NSArray *exposedServices;
    NSMutableArray *remotedApps = [[NSMutableArray alloc]init]; // array of AJGWCRemotedApp

    exposedServices = [((VisualAclRules *)_aclRulesArray[0]) createAJGWCRuleObjectDescriptions];

    for (NSInteger pos = 1; pos != [_aclRulesArray count]; pos++) {
        VisualAclRules *aclRules = _aclRulesArray[pos];

        NSArray *remotedServicesObjectDescriptions = [aclRules createAJGWCRuleObjectDescriptions];

        AJGWCRemotedApp *remotedApp = [[AJGWCRemotedApp alloc] initWithAnnouncedApp:[self findRemotedAppInAjgwcAclRules:pos] ruleObjDescriptions:&remotedServicesObjectDescriptions];

        remotedApps[pos-1] = remotedApp;

    }


    rules = [[AJGWCAclRules alloc] initWithExposedServices:exposedServices remotedApps:remotedApps];

    return rules;
}


@end
