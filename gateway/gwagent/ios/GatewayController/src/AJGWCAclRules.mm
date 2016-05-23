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

#import "AJGWCAclRules.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJGWCRuleObjectDescription.h"
#import "AJGWCRemotedApp.h"
#import "AJNStatus.h"

@interface AJGWCAclRules ()

@property (nonatomic) ajn::gwc::AclRules* handle;

@end

@implementation AJGWCAclRules

- (id)initWithHandle:(ajn::gwc::AclRules *)handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::AclRules *)handle;
    }
    return self;
}

- (id)initWithExposedServices:(NSArray*) exposedServices remotedApps:(NSArray*) remotedApps
{
    self = [super init];
    std::vector<ajn::gwc::RuleObjectDescription*> exposedServicesVect;
    std::vector<ajn::gwc::RemotedApp*> remotedAppsVect;

    if (self) {
        // Populate std::vector with the NSArray data
        for(AJGWCRuleObjectDescription* manifestObjDesc in exposedServices) {
            exposedServicesVect.insert(exposedServicesVect.end(), [manifestObjDesc handle]);
        }

        // Populate std::vector with the NSArray data
        for(AJGWCRemotedApp* remoteApp in remotedApps) {
            remotedAppsVect.insert(remotedAppsVect.end(), [remoteApp handle]);
        }

        self.handle = new ajn::gwc::AclRules();

        QStatus status = self.handle->init(exposedServicesVect, remotedAppsVect);

        if (status != ER_OK) {
            delete self.handle;
            self.handle = NULL;
            NSLog(@"Error: Failed to init AJGWCAclRules :%@", [AJNStatus descriptionForStatusCode:status]);
            return nil;
        }
    }


    return self;
}

-(NSArray*)remotedApps
{
    std::vector<ajn::gwc::RemotedApp*> remotedAppsVect = self.handle->getRemotedApps();
    NSMutableArray* remotedAppsArray = [[NSMutableArray alloc] init];

    // Populate NSArray with std::vector data
    for(std::vector<ajn::gwc::RemotedApp*>::iterator it = remotedAppsVect.begin(); it != remotedAppsVect.end(); ++it) {
        [remotedAppsArray addObject:[[AJGWCRemotedApp alloc] initWithHandle:*it]];
    }

    return remotedAppsArray;
}

-(NSArray*)exposedServices
{
    std::vector<ajn::gwc::RuleObjectDescription*> exposedServicesVect = self.handle->getExposedServices();
    NSMutableArray* exposedServicesArray = [[NSMutableArray alloc] init];

    // Populate NSArray with std::vector data
    for(std::vector<ajn::gwc::RuleObjectDescription*>::iterator it = exposedServicesVect.begin(); it != exposedServicesVect.end(); ++it) {
        [exposedServicesArray addObject:[[AJGWCRuleObjectDescription alloc] initWithHandle:*it]];
    }
    return exposedServicesArray;
}

- (void)updateMetadata:(NSDictionary*) metadata
{
    std::map<qcc::String, qcc::String> metadataMap;
    // Populate std::map with NSDictionary data
    for (NSString* key in metadata.allKeys) {
        metadataMap.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], [AJNConvertUtil convertNSStringToQCCString:[metadata objectForKey:key]]));
    }
    self.handle->setMetadata(metadataMap);
}

- (NSString*)metadata:(NSString*) key
{
    qcc::String *value = self.handle->getMetadata([AJNConvertUtil convertNSStringToQCCString:key]);

    if (value) {
        return [AJNConvertUtil convertQCCStringtoNSString:*value];
    } else {
        return nil;
    }

}

- (NSDictionary*)metadata
{
    NSMutableDictionary* metadataDict = [[NSMutableDictionary alloc] init];
    std::map<qcc::String, qcc::String> metadataMap = self.handle->getMetadata();
    // Populate NSMutableDictionary with std::map data
    for (std::map <qcc::String, qcc::String>::iterator it = metadataMap.begin(); it != metadataMap.end(); ++it) {
        [metadataDict setValue:[AJNConvertUtil convertQCCStringtoNSString:it->second] forKey:[AJNConvertUtil convertQCCStringtoNSString:it->first]];
    }

    return metadataDict;
}

- (ajn::gwc::AclRules*)handle
{
    return _handle;
}

@end
