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

#import "AJGWCAnnouncementData.h"

@interface AJGWCAnnouncementData ()

@property (nonatomic) uint16_t port;
@property (nonatomic) NSString* busName;
@property (strong, nonatomic) NSDictionary* objectDescriptions;
@property (strong, nonatomic) NSDictionary* aboutData;

@end

@implementation AJGWCAnnouncementData

- (id)initWithPort:(uint16_t) port busName:(NSString *)busName aboutData:(NSDictionary *)aboutData objectDescriptions:(NSDictionary *) objectDescs
{
    self = [super init];
    if (self) {
        self.port = port;
        self.busName = busName;
        self.objectDescriptions = [[NSDictionary alloc] initWithDictionary:objectDescs];
        self.aboutData = [[NSDictionary alloc] initWithDictionary:aboutData];
    }
    return self;
}

- (NSDictionary *)objectDescriptions
{
    return _objectDescriptions;
}

- (NSDictionary *)aboutData
{
    return _aboutData;
}

- (uint16_t)port
{
    return _port;
}

- (NSString*)busName
{
    return _busName;
}
@end
