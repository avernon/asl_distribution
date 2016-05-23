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

#import "AJGWCAnnouncedApp.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJGWCAnnouncedApp ()

@property (nonatomic) ajn::gwc::AnnouncedApp* handle;

@end

@implementation AJGWCAnnouncedApp

- (id)initWithBusName:(NSString*) busName appName:(NSString*) appName appId:(uint8_t*) appId appIdLength:(uint32_t)appIdLength deviceName:(NSString*) deviceName deviceId:(NSString*)deviceId
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::AnnouncedApp();
        self.handle->init([AJNConvertUtil convertNSStringToQCCString:busName],
                          [AJNConvertUtil convertNSStringToQCCString:appName],
                          appId,
                          appIdLength,
                          [AJNConvertUtil convertNSStringToQCCString:deviceName],
                          [AJNConvertUtil convertNSStringToQCCString:deviceId]);
    }
    return self;
}

- (id)initWithBusName:(NSString*) busName aboutData:(NSDictionary*) aboutData
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
        self.handle = new ajn::gwc::AnnouncedApp();
        QStatus status = self.handle->init([AJNConvertUtil convertNSStringToQCCString:busName], aboutDataMap);
        if (status != ER_OK) {
            NSLog(@"Error initializing AJGWCAnnouncedApp");
            delete self.handle;
            return nil;
        }
    }
    return self;
}

- (NSString*)busName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getBusName()];
}

- (NSString*)appName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getAppName()];
}

- (uint8_t*)appId
{
    return (uint8_t*)self.handle->getAppId();
}

- (NSString*)deviceName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getDeviceName()];
}

- (NSString*)deviceId
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getDeviceId()];
}

- (ajn::gwc::AnnouncedApp*)handle
{
    return _handle;
}

@end
