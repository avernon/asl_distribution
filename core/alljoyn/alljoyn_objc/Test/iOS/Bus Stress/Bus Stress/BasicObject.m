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

////////////////////////////////////////////////////////////////////////////////
//
//  BasicObject.m
//
////////////////////////////////////////////////////////////////////////////////

#import "BasicObject.h"

////////////////////////////////////////////////////////////////////////////////
//
//  Objective-C Bus Object implementation for BasicObject
//
////////////////////////////////////////////////////////////////////////////////

@implementation BasicObject

- (NSString*)concatenateString:(NSString*)str1 withString:(NSString*)str2
{
    return [str1 stringByAppendingString:str2];
}

- (void)methodWithOutString:(NSString*)str1 inString2:(NSString*)str2 outString1:(NSString**)outStr1 outString2:(NSString**)outStr2
{
    // TODO: complete the implementation of this method
    //
     @throw([NSException exceptionWithName:@"NotImplementedException" reason:@"You must implement this method" userInfo:nil]);   
}

- (void)methodWithOnlyOutString:(NSString**)outStr1 outString2:(NSString**)outStr2
{
    // TODO: complete the implementation of this method
    //
     @throw([NSException exceptionWithName:@"NotImplementedException" reason:@"You must implement this method" userInfo:nil]);   
}

- (void)methodWithNoReturnAndNoArgs
{
    // TODO: complete the implementation of this method
    //
     @throw([NSException exceptionWithName:@"NotImplementedException" reason:@"You must implement this method" userInfo:nil]);   
}


@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  Objective-C Bus Object implementation for PingObject
//
////////////////////////////////////////////////////////////////////////////////

@implementation PingObject

- (void)pingWithValue:(NSNumber*)value
{
    // TODO: complete the implementation of this method
    //
     @throw([NSException exceptionWithName:@"NotImplementedException" reason:@"You must implement this method" userInfo:nil]);   
}


@end

////////////////////////////////////////////////////////////////////////////////