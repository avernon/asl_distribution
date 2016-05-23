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

#import "AJGWCRuleObjectPath.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJGWCRuleObjectPath ()

@property (nonatomic) ajn::gwc::RuleObjectPath* handle;

@end

@implementation AJGWCRuleObjectPath

- (id)initWithHandle:(ajn::gwc::RuleObjectPath *) handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::RuleObjectPath *)handle;
    }
    return self;
}

- (id)initWithObjectPath:(NSString*) objectPath friendlyName:(NSString*) friendlyName isPrefix:(bool) isPrefix isPrefixAllowed:(bool)isPrefixAllowed
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::RuleObjectPath([AJNConvertUtil convertNSStringToQCCString:objectPath], [AJNConvertUtil convertNSStringToQCCString:friendlyName], isPrefix, isPrefixAllowed);
    }
    return self;
}

- (NSString*)path
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getPath()];
}

- (NSString*)friendlyName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getFriendlyName()];
}

- (bool)isPrefix
{
    return self.handle->isPrefix();
}

- (void)setPrefix:(bool) isPrefix
{
    self.handle->setPrefix(isPrefix);
}

- (bool)isPrefixAllowed
{
    return self.handle->isPrefixAllowed();
}

- (void)setPrefixAllowed:(bool)isPrefixAllowed
{
    self.handle->setPrefixAllowed(isPrefixAllowed);
}

- (ajn::gwc::RuleObjectPath*)handle
{
    return _handle;
}

@end
