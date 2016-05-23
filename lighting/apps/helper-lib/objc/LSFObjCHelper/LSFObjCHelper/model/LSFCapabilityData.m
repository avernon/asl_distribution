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

#import "LSFCapabilityData.h"

@interface LSFCapabilityData()

-(int)combineA: (int)a withB: (int)b;

@end

@implementation LSFCapabilityData

@synthesize dimmable = _dimmable;
@synthesize color = _color;
@synthesize temp = _temp;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.dimmable = UNSET;
        self.color = UNSET;
        self.temp = UNSET;
    }
    
    return self;
}

-(id)initWithDimmable: (BOOL)isDimmable color: (BOOL)hasColor andTemp: (BOOL)hasTemp
{
    self = [super init];
    
    if (self)
    {
        self.dimmable = isDimmable ? ALL : NONE;
        self.color = hasColor ? ALL : NONE;
        self.temp = hasTemp ? ALL : NONE;
    }
    
    return self;
}

-(id)initWithCapabilityData: (LSFCapabilityData *)capabilityData
{
    self = [super init];

    if (self)
    {
        self.dimmable = capabilityData.dimmable;
        self.color = capabilityData.color;
        self.temp = capabilityData.temp;
    }

    return self;
}

-(void)includeData: (LSFCapabilityData *)data
{
    if (data != nil)
    {
        self.dimmable = [self combineA: self.dimmable withB: data.dimmable];
        self.color = [self combineA: self.color withB: data.color];
        self.temp = [self combineA: self.temp withB: data.temp];
    }
}

-(BOOL)isMixed
{
    return ((self.dimmable == SOME) || (self.color == SOME) || (self.temp == SOME));
}

-(int)combineA: (int)a withB: (int)b
{
    switch (a)
    {
        case UNSET:
            //No data in a, use b
            return b;
        case NONE:
            //None if b is none or unset, otherwise some
            return (b == NONE || b == UNSET) ? NONE : SOME;
        case SOME:
            return SOME;
        case ALL:
            //all if b is all or unset, otherwise some
            return (b == ALL || b == UNSET) ? ALL : SOME;
        default:
            return UNSET;
    }
}

-(NSString *)print
{
    return [NSString stringWithFormat: @"[dimmable: %i color: %i temp: %i]", self.dimmable, self.color, self.temp];
}

@end
