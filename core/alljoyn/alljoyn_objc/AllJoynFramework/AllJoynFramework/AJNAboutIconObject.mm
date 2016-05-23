////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <alljoyn/BusAttachment.h>
#import <alljoyn/AboutIconObj.h>
#import "AJNAboutIconObject.h"
#import "AJNAboutIcon.h"

using namespace ajn;

@interface AJNBusAttachment(Private)

@property (nonatomic, readonly) BusAttachment *busAttachment;

@end

@interface AJNAboutIconObject()

/**
 * The bus attachment this object is associated with.
 */
@property (nonatomic, strong) AJNBusAttachment *bus;
@property (nonatomic, readonly) AboutIconObj *aboutIconObject;
@property (nonatomic, strong) AJNAboutIcon *aboutIcon;
@end

@implementation AJNAboutIconObject

static uint16_t version;

@synthesize bus = _bus;
@synthesize aboutIconObject = _aboutIconObject;

+ (uint16_t)version
{
    return version;
}

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (AboutIconObj*)aboutIconObject
{
    return static_cast<AboutIconObj*>(self.handle);
}


- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment aboutIcon:(AJNAboutIcon *)aboutIcon
{
    self = [super init];
    if (self) {
        self.bus = busAttachment;
        self.aboutIcon = aboutIcon;
        self.handle = new AboutIconObj(*((BusAttachment*)busAttachment.handle), *(AboutIcon*)aboutIcon.handle);
        version = self.aboutIconObject->VERSION;
    }
    return self;
    
}

@end