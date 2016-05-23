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

#import "LSFColorAverager.h"

@interface LSFColorAverager()

@property (nonatomic) long long sum;
@property (nonatomic) long long count;
@property (nonatomic) long long initial;
@property (nonatomic) BOOL uniform;

@end

@implementation LSFColorAverager

@synthesize sum = _sum;
@synthesize count = _count;
@synthesize initial = _initial;
@synthesize uniform = _uniform;

-(id)init
{
    self = [super init];

    if (self)
    {
        [self reset];
    }

    return self;
}

-(void)reset
{
    self.sum = 0;
    self.count = 0;
    self.initial = -1;
    self.uniform = YES;
}

-(void)add: (long long)value
{
    self.sum += value;
    self.count++;

    if (self.initial < 0)
    {
        self.initial = value;
    }
    else if (self.uniform)
    {
        self.uniform = (value == self.initial);
    }
}

-(long long)getSum
{
    return self.sum;
}

-(long long)getCount
{
    return self.count;
}

-(long long)getAverage
{
    double divisor = self.count > 0 ? self.count : 1.0;
    return round((double)self.sum / divisor);
}

-(BOOL)isUniform
{
    return self.uniform;
}

@end
