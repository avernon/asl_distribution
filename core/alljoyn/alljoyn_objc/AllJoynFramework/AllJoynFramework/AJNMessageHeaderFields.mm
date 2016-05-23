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

#import <alljoyn/Message.h>
#import "AJNMessageHeaderFields.h"
#import "AJNMessageArgument.h"

@implementation AJNMessageHeaderFields

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (ajn::HeaderFields*)messageHeaderFields 
{
    return static_cast<ajn::HeaderFields*>(self.handle);
}

- (NSArray *)values
{
    NSMutableArray *theValues = [[NSMutableArray alloc] initWithCapacity:kAJNMessageHeaderFieldTypeFieldUnknown];
    for (int i = 0; i < kAJNMessageHeaderFieldTypeFieldUnknown; i++) {
        [theValues addObject:[[AJNMessageArgument alloc] initWithHandle:&(self.messageHeaderFields->field[i])]];
    }
    return theValues;
}

- (NSString *)stringValue
{
    return [NSString stringWithCString:self.messageHeaderFields->ToString().c_str() encoding:NSUTF8StringEncoding];
}

@end
