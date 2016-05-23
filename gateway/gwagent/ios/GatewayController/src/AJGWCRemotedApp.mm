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

#import "AJGWCRemotedApp.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJGWCRuleObjectDescription.h"


@interface AJGWCRemotedApp ()

@property (nonatomic) ajn::gwc::RemotedApp* handle;

@end

@implementation AJGWCRemotedApp

- (id)initWithHandle:(ajn::gwc::RemotedApp *) handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::RemotedApp *)handle;
    }
    return self;
}

- (id)initWithBusUniqueName:(NSString*) busUniqueName appName:(NSString*) appName appId:(uint8_t*) appId deviceName:(NSString*) deviceName deviceId:(NSString*) deviceId ruleObjDescriptions:(NSArray**) ruleObjDescriptions
{
    self = [super init];
    std::vector<ajn::gwc::RuleObjectDescription*> ruleObjDescriptionsVect;
    if (self) {
        // Populate std::vector with NSArray data
        for(AJGWCRuleObjectDescription* manifestObjDesc in *ruleObjDescriptions) {
            ruleObjDescriptionsVect.insert(ruleObjDescriptionsVect.end(), [manifestObjDesc handle]);
        }
        self.handle = new ajn::gwc::RemotedApp();

        QStatus status = self.handle->init([AJNConvertUtil convertNSStringToQCCString:busUniqueName],
                                           [AJNConvertUtil convertNSStringToQCCString:appName],
                                           appId,
                                           [AJNConvertUtil convertNSStringToQCCString:deviceName],
                                           [AJNConvertUtil convertNSStringToQCCString:deviceId],
                                           ruleObjDescriptionsVect);

        if (status!=ER_OK) {
            delete self.handle;
            self.handle = NULL;
            NSLog(@"failed init of RemotedApp");
            return nil;
        }


    }
    return self;
}

- (id)initWithAboutData:(NSDictionary*) aboutData ruleObjDescriptions:(NSArray*) ruleObjDescriptions
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
        std::vector<ajn::gwc::RuleObjectDescription*> ruleObjDescriptionsVect;
        // Populate std::vector with the NSArray data
        for(AJGWCRuleObjectDescription* manifestObjDesc in ruleObjDescriptions) {
            ruleObjDescriptionsVect.insert(ruleObjDescriptionsVect.end(), [manifestObjDesc handle]);
        }
    }
    return self;
}

- (id)initWithAnnouncedApp:(AJGWCAnnouncedApp*) announcedApp ruleObjDescriptions:(NSArray**) ruleObjDescriptions
{
    self = [super init];
    std::vector<ajn::gwc::RuleObjectDescription*> ruleObjDescriptionsVect;

    if (self) {
        // Populate std::vector with NSArray data
        for(AJGWCRuleObjectDescription* manifestObjDesc in *ruleObjDescriptions) {
            ruleObjDescriptionsVect.insert(ruleObjDescriptionsVect.end(), [manifestObjDesc handle]);
        }
        self.handle = new ajn::gwc::RemotedApp();

        QStatus status = self.handle->init([announcedApp handle], ruleObjDescriptionsVect);

        if (status!=ER_OK) {
            delete self.handle;
            self.handle = NULL;

            NSLog(@"failed init of RemotedApp in initWithAnnouncedApp");
            return nil;
        }
    }
    return self;
}

- (NSArray*)ruleObjDescriptions
{
    NSMutableArray* ruleObjDescriptionsArray = [[NSMutableArray alloc] init];
    //std::vector<ajn::gwc::RuleObjectDescription*> ruleObjDescriptionsVect = self.handle->getRuleObjDesciptions();
    // Populate NSMutableArray with std::vector data
    for (std::vector<ajn::gwc::RuleObjectDescription*>::const_iterator vectIt = self.handle->getRuleObjDesciptions().begin(); vectIt != self.handle->getRuleObjDesciptions().end(); vectIt++) {
        [ruleObjDescriptionsArray addObject:[[AJGWCRuleObjectDescription alloc] initWithHandle:*vectIt]];
    }
    return ruleObjDescriptionsArray;
}

- (ajn::gwc::RemotedApp*)handle
{
    return _handle;
}
@end
