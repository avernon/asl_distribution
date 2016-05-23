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

#import <alljoyn/BusObject.h>
#import <alljoyn/InterfaceDescription.h>
#import <alljoyn/MsgArg.h>
#import <alljoyn/Message.h>
#import "AJNBusAttachment.h"
#import "AJNBusObject.h"
#import "AJNBusObjectImpl.h"
#import "AJNInterfaceDescription.h"
#import "AJNMessageArgument.h"
#import "AJNTranslatorImpl.h"

using namespace ajn;

@interface AJNMessageArgument(Private)

@property (nonatomic, readonly) MsgArg *msgArg;

@end

@interface AJNBusObject()

/**
 * The bus attachment this object is associated with.
 */
@property (nonatomic, weak) AJNBusAttachment *bus;

@end

@implementation AJNBusObject

@synthesize bus = _bus;

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (AJNBusObjectImpl*)busObject
{
    return static_cast<AJNBusObjectImpl*>(self.handle);
}

- (NSString*)path
{
    return [NSString stringWithCString:self.busObject->GetPath() encoding:NSUTF8StringEncoding];
}

- (NSString*)name
{
    return [NSString stringWithCString:self.busObject->GetName().c_str() encoding:NSUTF8StringEncoding];
}

-(BOOL)isSecure
{
    return self.busObject->IsSecure() ? YES : NO;
}

- (id)initWithPath:(NSString*)path
{
    self = [super init];
    if (self) {
        // initialization
    }
    return self;
}

- (id)initWithBusAttachment:(AJNBusAttachment*)busAttachment onPath:(NSString*)path
{
    self = [super init];
    if (self) {
        self.bus = busAttachment;
    }
    return self;
}

- (void)objectWasRegistered
{
    NSLog(@"AJNBusObject::ObjectRegistered called.");
}

- (void)emitPropertyWithName:(NSString*)propertyName onInterfaceWithName:(NSString*)interfaceName changedToValue:(AJNMessageArgument*)value inSession:(AJNSessionId)sessionId
{
    self.busObject->EmitPropChanged([interfaceName UTF8String], [propertyName UTF8String], *value.msgArg, sessionId);
}

- (QStatus)cancelSessionlessMessageWithSerial:(uint32_t)serialNumber
{
    return self.busObject->CancelSessionlessMessage(serialNumber);
}

- (QStatus)cancelSessionlessMessageWithMessage:(const AJNMessage *)message
{
    return self.busObject->CancelSessionlessMessage(*(Message *)message.handle);
}

- (void)setDescription:(NSString *)description inLanguage:(NSString *)language
{
    [self busObject]->SetDescription([language UTF8String], [description UTF8String]);
}

- (void)setDescriptionTranslator:(id<AJNTranslator>)translator
{
    if(self.translator)
    {
        delete (ajn::Translator*)self.translator;
    }
    self.translator = new AJNTranslatorImpl(translator);
    [self busObject]->SetDescriptionTranslator((ajn::Translator*)self.translator);
}

- (QStatus)setAnnounceFlagForInterface:(AJNInterfaceDescription *)iface value:(AJNAnnounceFlag)flag
{
    return self.busObject->SetAnnounceFlag((ajn::InterfaceDescription *)iface.handle, (BusObject::AnnounceFlag)flag);
}

-(void)dealloc
{
    if(self.translator)
    {
        delete (AJNTranslatorImpl*)self.translator;
    }
}

@end
