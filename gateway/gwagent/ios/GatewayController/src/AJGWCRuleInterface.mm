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

#import "AJGWCRuleInterface.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJGWCRuleInterface ()

@property (nonatomic) ajn::gwc::RuleInterface* handle;

@end

@implementation AJGWCRuleInterface

- (void)dealloc
{
    delete self.handle;
    self.handle = NULL;
}

- (id)initWithHandle:(ajn::gwc::RuleInterface) handle
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::RuleInterface(handle.getName(), handle.getFriendlyName(), handle.isSecured());
    }
    return self;
}

- (id)initWithInterfaceName:(NSString*) name friendlyName:(NSString*) friendlyName  isSecured:(bool) isSecured
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::RuleInterface([AJNConvertUtil convertNSStringToQCCString:name], [AJNConvertUtil convertNSStringToQCCString:friendlyName], isSecured);

    }
    return self;
}

- (NSString*)interfaceName
{
    qcc::String name = self.handle->getName();

    return [AJNConvertUtil convertQCCStringtoNSString:name];
}

- (NSString*)friendlyName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getFriendlyName()];
}

- (bool)isSecured
{
    return self.handle->isSecured();
}

- (ajn::gwc::RuleInterface*)handle
{
    return _handle;
}

- (id)copyWithZone:(NSZone *)zone {
    AJGWCRuleInterface *objectCopy = [[AJGWCRuleInterface allocWithZone:zone] initWithHandle:*(self.handle)];

    return objectCopy;
}

- (NSUInteger)hash {
    return [self.interfaceName hash];
}

- (BOOL)isEqual:(id)anObject {
    if (![anObject isKindOfClass:[AJGWCRuleInterface class]]) return NO;
    AJGWCRuleInterface *otherRuleInterface = (AJGWCRuleInterface *)anObject;
    return [otherRuleInterface.interfaceName isEqualToString:self.interfaceName];
}



@end
