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

#import <alljoyn/MsgArg.h>
#import "AJNMessageArgument.h"

using namespace ajn;

class MsgArgEx : public MsgArg
{
public:
    static QStatus Get(MsgArg* pMsgArg, const char* signature, va_list* argp)
    {
        size_t sigLen = (signature ? strlen(signature) : 0);
        if (sigLen == 0) {
            return ER_BAD_ARG_1;
        }
        QStatus status = VParseArgs(signature, sigLen, pMsgArg, 1, argp);
        return status;        
    }
    
    static QStatus Set(MsgArg* pMsgArg, const char* signature, va_list* argp)
    {
        QStatus status = ER_OK;
        
        pMsgArg->Clear();
        size_t sigLen = (signature ? strlen(signature) : 0);
        if ((sigLen < 1) || (sigLen > 255)) {
            status = ER_BUS_BAD_SIGNATURE;
        } else {
            status = VBuildArgs(signature, sigLen, pMsgArg, 1, argp);
            if ((status == ER_OK) && (*signature != 0)) {
                status = ER_BUS_NOT_A_COMPLETE_TYPE;
            }
        }
        return status;        
    }
};

@interface AJNObject(Private)

@property (nonatomic) BOOL shouldDeleteHandleOnDealloc;

@end


@interface AJNMessageArgument()

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
@property (nonatomic, readonly) MsgArg *msgArg;

@end

@implementation AJNMessageArgument

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (MsgArg *)msgArg
{
    return (MsgArg*)self.handle;
}

- (AJNType)type
{
    return (AJNType)self.msgArg->typeId;
}

- (NSString *)signature
{
    return [NSString stringWithCString:self.msgArg->Signature().c_str() encoding:NSUTF8StringEncoding];
}

- (NSString *)xml
{
    return [NSString stringWithCString:self.msgArg->ToString().c_str() encoding:NSUTF8StringEncoding];
}

- (id)init
{
    self = [super init];
    if (self) {
        self.handle = new MsgArg();
        self.shouldDeleteHandleOnDealloc = YES;
    }
    return self;
}

- (NSString *)signatureFromMessageArguments:(NSArray *)arguments
{
    NSString *result = nil;
    if (arguments.count) {
        MsgArg * pArgs = new MsgArg[arguments.count];
        for (int i = 0; i < arguments.count; i++) {
            pArgs[i] = *[[arguments objectAtIndex:i] msgArg];
        }
        result = [NSString stringWithCString:self.msgArg->Signature(pArgs, arguments.count).c_str() encoding:NSUTF8StringEncoding];
        delete [] pArgs;
    }
    return result;
}

- (NSString *)xmlFromMessageArguments:(NSArray*)arguments
{
    NSString *result = nil;
    if (arguments.count) {
        MsgArg * pArgs = new MsgArg[arguments.count];
        for (int i = 0; i < arguments.count; i++) {
            pArgs[i] = *[[arguments objectAtIndex:i] msgArg];
        }
        result = [NSString stringWithCString:self.msgArg->ToString(pArgs, arguments.count).c_str() encoding:NSUTF8StringEncoding];
        delete [] pArgs;
    }
    return result;
}

- (BOOL)conformsToSignature:(NSString *)signature
{
    return self.msgArg->HasSignature([signature UTF8String]);
}

- (QStatus)setValue:(NSString *)signature, ...
{
    va_list args;
    va_start(args, signature);
    QStatus status = MsgArgEx::Set(self.msgArg, [signature UTF8String], &args);
    va_end(args);
    return status;
}

- (QStatus)value:(NSString *)signature, ...
{
    va_list args;
    va_start(args, signature);
    QStatus status = MsgArgEx::Get(self.msgArg, [signature UTF8String], &args);
    va_end(args);
    return status;
}

- (void)clear
{
    self.msgArg->Clear();
}

- (void)stabilize
{
    self.msgArg->Stabilize();
}

- (void)setOwnershipFlags:(uint8_t)flags shouldApplyRecursively:(BOOL)deep
{
    self.msgArg->SetOwnershipFlags(flags, deep == YES);
}

- (void)dealloc
{
    if (self.shouldDeleteHandleOnDealloc) {
        MsgArg *pArg = static_cast<MsgArg*>(self.handle);
        delete pArg;
        self.handle = nil;
    }
}

@end
