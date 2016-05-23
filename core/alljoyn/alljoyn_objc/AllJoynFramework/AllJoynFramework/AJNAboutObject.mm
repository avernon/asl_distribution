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
#import <alljoyn/AboutObj.h>
#import <alljoyn/BusObject.h>
#import "AJNBusAttachment.h"
#import "AJNSessionOptions.h"
#import "AJNAboutObject.h"
#import "AJNBusObject.h"
#import "AJNStatus.h"
#import "AJNAboutDataListenerImpl.h"
#import "AJNMessageArgument.h"

using namespace ajn;

@interface AJNBusAttachment(Private)

@property (nonatomic, readonly) BusAttachment *busAttachment;

@end

@interface AJNAboutObject()

/**
 * The bus attachment this object is associated with.
 */
@property (nonatomic, strong) AJNBusAttachment *bus;
@property (nonatomic, readonly) AboutObj *aboutObject;
@end


@implementation AJNAboutObject

@synthesize bus = _bus;

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (AboutObj*)aboutObject
{
    return static_cast<AboutObj*>(self.handle);
}

- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment withAnnounceFlag:(AJNAnnounceFlag)announceFlag
{
    self = [super init];
    if (self) {
        self.bus = busAttachment;
        self.handle = new AboutObj(*((BusAttachment*)busAttachment.handle), (BusObject::AnnounceFlag)announceFlag);
    }
    return self;
}

- (QStatus)announceForSessionPort:(AJNSessionPort)sessionPort withAboutDataListener:(id<AJNAboutDataListener>)aboutDataListener
{
    AJNAboutDataListenerImpl *listenerImpl = new AJNAboutDataListenerImpl(aboutDataListener);
    return self.aboutObject->Announce(sessionPort, *listenerImpl);
}

-(QStatus)unannounce
{
    return self.aboutObject->Unannounce();
}



@end
