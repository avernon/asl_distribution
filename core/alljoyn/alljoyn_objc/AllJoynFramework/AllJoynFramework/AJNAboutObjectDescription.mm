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
#import <alljoyn/AboutObjectDescription.h>
#import "AJNAboutObjectDescription.h"

using namespace ajn;

@interface AJNAboutObjectDescription()
@property (nonatomic, readonly) AboutObjectDescription *aboutObjectDescription;
@end


@interface AJNMessageArgument(Private)

@property (nonatomic, readonly) MsgArg *msgArg;

@end

@interface AJNObject(Private)

@property (nonatomic) BOOL shouldDeleteHandleOnDealloc;

@end

@implementation AJNAboutObjectDescription

/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (AboutObjectDescription*)aboutObjectDescription
{
    return static_cast<AboutObjectDescription*>(self.handle);
}

- (id)init
{
    self = [super init];
    if (self) {
        self.handle = new AboutObjectDescription();
        self.shouldDeleteHandleOnDealloc = YES;
    }
    return self;
}

- (id)initWithMsgArg:(AJNMessageArgument *)msgArg
{
    self = [super init];
    if (self) {
        self.handle = new AboutObjectDescription(*msgArg.msgArg);
        self.shouldDeleteHandleOnDealloc = YES;
    }
    return self;
}

- (void)dealloc
{
    if (self.shouldDeleteHandleOnDealloc) {
        AboutObjectDescription *ptr = (AboutObjectDescription*)self.handle;
        delete ptr;
        self.handle = nil;
    }
}

- (QStatus)createFromMsgArg:(AJNMessageArgument *)msgArg
{
    return self.aboutObjectDescription->CreateFromMsgArg(*msgArg.msgArg);
}

- (size_t)getPaths:(NSMutableArray **)path withSize:(size_t)numOfPaths
{
    size_t pathCount = self.aboutObjectDescription->GetPaths(NULL, 0);
    if (path == nil && numOfPaths == 0) {
        return pathCount;
    }
    numOfPaths = (pathCount < numOfPaths) ? pathCount : numOfPaths;
    const char** paths = new const char*[numOfPaths];
    pathCount = self.aboutObjectDescription->GetPaths(paths, numOfPaths);
    for (int i=0 ; i < numOfPaths ; i++) {
        NSString *objPath = [[NSString alloc] initWithUTF8String:paths[i]];
        [*path addObject:objPath];
    }
    delete []paths;
    return pathCount;
}

- (size_t)getInterfacesForPath:(NSString *)path interfaces:(NSMutableArray **)interfaces numOfInterfaces:(size_t)numOfInterfaces
{
    size_t interfaceCount = self.aboutObjectDescription->GetInterfaces([path UTF8String], NULL, 0);
    if (interfaces == nil && numOfInterfaces == 0) {
        return interfaceCount;
    }
    numOfInterfaces = (interfaceCount < numOfInterfaces) ? interfaceCount : numOfInterfaces;
    const char** ifaces = new const char*[numOfInterfaces];
    interfaceCount = self.aboutObjectDescription->GetInterfaces([path UTF8String], ifaces, numOfInterfaces);
    for (int i=0 ; i < numOfInterfaces ; i++) {
        NSString *ifacePath = [[NSString alloc] initWithUTF8String:ifaces[i]];
        [*interfaces addObject:ifacePath];
    }
    delete []ifaces;
    return interfaceCount;
}

- (size_t)getInterfacePathsForInterface:(NSString *)interface paths:(NSMutableArray **)paths numOfPaths:(size_t)numOfPaths
{
    size_t pathCount = self.aboutObjectDescription->GetInterfacePaths([interface UTF8String], NULL, 0);
    if (paths == nil && numOfPaths == 0) {
        return pathCount;
    }
    numOfPaths = (pathCount < numOfPaths) ? pathCount : numOfPaths;
    const char** interfacePaths = new const char*[numOfPaths];
    pathCount = self.aboutObjectDescription->GetInterfacePaths([interface UTF8String], interfacePaths, numOfPaths);
    for (int i=0 ; i < numOfPaths ; i++) {
        NSString *objPath = [[NSString alloc] initWithUTF8String:interfacePaths[i]];
        [*paths addObject:objPath];
    }
    delete []interfacePaths;
    return pathCount;
}

- (void)clear
{
    return self.aboutObjectDescription->Clear();
}

- (BOOL)hasPath:(const char *)path
{
    return self.aboutObjectDescription->HasPath(path) ? YES : NO;
}

- (BOOL)hasInterface:(const char *)interface
{
    return self.aboutObjectDescription->HasInterface(interface) ? YES : NO;
}

- (BOOL)hasInterface:(const char *)interface withPath:(const char *)path
{
    return self.aboutObjectDescription->HasInterface(path, interface) ? YES : NO;
}

- (QStatus)getMsgArg:(AJNMessageArgument *)msgArg
{
    return self.aboutObjectDescription->GetMsgArg(msgArg.msgArg);
}

@end