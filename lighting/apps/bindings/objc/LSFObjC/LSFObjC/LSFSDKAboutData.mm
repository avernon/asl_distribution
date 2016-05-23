/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSDKAboutData.h"

@interface LSFSDKAboutData()

@property (nonatomic, readonly) ajn::AboutData *myAboutData;

@end

@implementation LSFSDKAboutData

@synthesize myAboutData = _myAboutData;

-(id)initWithAboutData: (ajn::AboutData *)aboutData
{
    self = [super init];

    if (self)
    {
        self.handle = aboutData;
    }

    return self;
}

-(void)putKey: (NSString *)key withStringValue: (NSString *)value
{
    [self putKey: key withStringValue: value andLanguage: @""];
}

-(void)putKey: (NSString *)key withStringValue: (NSString *)value andLanguage: (NSString *)language
{
    ajn::MsgArg msgArg;
    msgArg.Set("s", [value UTF8String]);
    msgArg.Stabilize();
    [self putKey: key withMsgArg: &msgArg andLanguage: language];
}

-(void)putKey: (NSString *)key withStringArrayValue: (NSArray *)value
{
    [self putKey: key withStringArrayValue: value andLanguage: @""];
}

-(void)putKey: (NSString *)key withStringArrayValue: (NSArray *)value andLanguage: (NSString *)language
{
    ajn::MsgArg msgArg;
    const char* strArray[[value count]];

    for (int i = 0; i < [value count]; i++)
    {
        strArray[i] = [[value objectAtIndex: i] UTF8String];
    }

    msgArg.Set("as", (size_t)[value count], strArray);
    msgArg.Stabilize();

    [self putKey: key withMsgArg: &msgArg andLanguage: language];
}

-(void)putKey: (NSString *)key witDataValue: (NSData *)value
{
    [self putKey: key witDataValue: value andLanguage: @""];
}

-(void)putKey: (NSString *)key witDataValue: (NSData *)value andLanguage: (NSString *)language
{
    ajn::MsgArg msgArg;

    uint8_t* byteArray = (uint8_t *)[value bytes];
    msgArg.Set("ay", [value length], byteArray);
    msgArg.Stabilize();

    [self putKey: key withMsgArg: &msgArg andLanguage: language];
}

/*
 * Private
 */
-(void)putKey: (NSString *)key withMsgArg:(ajn::MsgArg *)msgArg
{
    [self putKey: key withMsgArg: msgArg andLanguage: @""];
}

-(void)putKey: (NSString *)key withMsgArg:(ajn::MsgArg *)msgArg andLanguage: (NSString *)language
{
    self.myAboutData->SetField([key UTF8String], *msgArg, [language UTF8String]);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (ajn::AboutData *)myAboutData
{
    return static_cast<ajn::AboutData*>(self.handle);
}

@end
