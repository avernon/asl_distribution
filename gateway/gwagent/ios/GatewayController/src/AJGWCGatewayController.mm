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

#import "AJGWCGatewayController.h"
#include <map>
#import "alljoyn/gateway/GatewayController.h"
#import "alljoyn/gateway/GatewayMgmtApp.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "alljoyn/about/AJNAboutDataConverter.h"
#import "AJGWCGatewayMgmtApp.h"

@interface AJGWCGatewayController ()

@end

@implementation AJGWCGatewayController

+ (id)sharedInstance
{
    static AJGWCGatewayController *gwController;
    static dispatch_once_t donce;
    dispatch_once(&donce, ^{
        gwController = [[self alloc] init];
    });
    return gwController;
}

- (id)init
{
    if (self = [super init]) {
    }
    return self;
}

+ (void)startWithBus:(AJNBusAttachment *) bus
{
    ajn::gwc::GatewayController::getInstance()->init((ajn::BusAttachment *)bus.handle);
}

- (void)shutdown
{
    ajn::gwc::GatewayController::getInstance()->shutdown();
}

- (AJNBusAttachment*)busAttachment
{
    AJNBusAttachment* bus = [[AJNBusAttachment alloc] initWithHandle:ajn::gwc::GatewayController::getInstance()->getBusAttachment()];
    return bus;
}

- (AJGWCGatewayMgmtApp*)createGatewayWithBusName:(NSString*) gatewayBusName objectDescs:(NSDictionary *) objectDescs  aboutData:(NSDictionary *) aboutData
{
    ajn::services::AboutClient::ObjectDescriptions objectDescsMap;
    ajn::services::AboutClient::AboutData aboutDataMap;

    // Iterate over the NSDictionary and convert to std::map<qcc::String, std::vector<qcc::String> > (ObjectDescriptions)
    for (NSString *key in objectDescs.allKeys)
    {
        std::vector <qcc::String>* tVect = new std::vector <qcc::String>;
        for (NSString *tStr in [objectDescs objectForKey:key]) {
            tVect->push_back([AJNConvertUtil convertNSStringToQCCString:tStr]);
        }
        objectDescsMap.insert(std::make_pair([AJNConvertUtil convertNSStringToConstChar:key], *tVect));
    }

    // Iterate over the NSDictionary and convert to std::map<qcc::String, ajn::MsgArg> (AboutData)
    for (NSString *key in aboutData.allKeys) {
        // Put key/ value in the std::map<qcc::String, ajn::MsgArg>
        AJNMessageArgument *ajnMsgArg = [aboutData objectForKey :key];

        ajn::MsgArg *cppValue = (ajn::MsgArg *)ajnMsgArg.handle;
        aboutDataMap.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], *cppValue));
    }

    ajn::gwc::GatewayMgmtApp* tmpGateway;
    QStatus status = ajn::gwc::GatewayController::getInstance()->createGateway([AJNConvertUtil convertNSStringToConstChar:gatewayBusName], objectDescsMap, aboutDataMap, &tmpGateway);

    if (status == ER_OK) {
        //Convert from NSDictionary * to ObjectDescriptions
        return [[AJGWCGatewayMgmtApp alloc] initWithHandle: tmpGateway ];
    }

    return nil;
}

- (AJGWCGatewayMgmtApp*)gateway:(NSString *) gatewayBusName
{
    return [[AJGWCGatewayMgmtApp alloc] initWithHandle: ajn::gwc::GatewayController::getInstance()->getGateway([AJNConvertUtil convertNSStringToQCCString:gatewayBusName])];
}

- (NSDictionary*)gateways
{
    NSMutableDictionary* gwsDict = [[NSMutableDictionary alloc] init];
    std::map<qcc::String, ajn::gwc::GatewayMgmtApp*> gwMap= ajn::gwc::GatewayController::getInstance()->getGateways();
    // Populate NSMutableDictionary with std::map data
    for (std::map <qcc::String, ajn::gwc::GatewayMgmtApp*>::iterator it = gwMap.begin(); it != gwMap.end(); ++it) {
        [gwsDict setValue:[[AJGWCGatewayMgmtApp alloc] initWithHandle:it->second ] forKey:[AJNConvertUtil convertQCCStringtoNSString:it->first]];
    }

    return gwsDict;
}

@end
