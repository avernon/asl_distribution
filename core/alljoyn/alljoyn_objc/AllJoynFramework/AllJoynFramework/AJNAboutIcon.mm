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

#import "AJNAboutIcon.h"
#import <alljoyn/AboutIcon.h>

using namespace ajn;

@interface AJNMessageArgument(Private)
@property (nonatomic, readonly) MsgArg *msgArg;
@end

@interface AJNObject(Private)
@property (nonatomic) BOOL shouldDeleteHandleOnDealloc;
@end

@interface AJNAboutIcon()
@property (nonatomic, readonly) AboutIcon *aboutIcon;
@end

@implementation AJNAboutIcon

- (id)init
{
    self = [super init];
    if (self) {
        self.handle = new AboutIcon();
        self.shouldDeleteHandleOnDealloc = YES;
    }
    return self;
    
}


/**
 * Helper to return the C++ API object that is encapsulated by this objective-c class
 */
- (AboutIcon*)aboutIcon
{
    return static_cast<AboutIcon*>(self.handle);
}

- (void)setContent:(uint8_t *)content
{
    self.aboutIcon->content = content;
}

- (uint8_t *)getContent
{
    return self.aboutIcon->content;
}

- (void)setUrl:(NSString *)url
{
    self.aboutIcon->url = [url UTF8String];
}

- (NSString *)getUrl
{
    return [NSString stringWithCString:(self.aboutIcon->url).c_str() encoding:NSUTF8StringEncoding ];
}

- (void)setContentSize:(size_t)contentSize
{
    self.aboutIcon->contentSize = contentSize;
}

- (size_t)getContentSize
{
    return self.aboutIcon->contentSize;
}

- (void)setMimeType:(NSString *)mimeType
{
    self.aboutIcon->mimetype = [mimeType UTF8String];
}

- (NSString *)getMimeType
{
    return [NSString stringWithCString:(self.aboutIcon->mimetype).c_str() encoding:NSUTF8StringEncoding ];
}

- (QStatus)setContentWithMimeType:(NSString *)mimeType data:(uint8_t *)data size:(size_t)csize ownsFlag:(BOOL)ownsData
{
    return self.aboutIcon->SetContent([mimeType UTF8String], data, csize, ownsData);
}

- (QStatus)setUrlWithMimeType:(NSString *)mimeType url:(NSString *)url
{
    return self.aboutIcon->SetUrl([mimeType UTF8String], [url UTF8String]);
}

- (void)clear
{
    self.aboutIcon->Clear();
}

- (QStatus)setContentUsingMsgArg:(AJNMessageArgument *)msgArg
{
    return self.aboutIcon->SetContent(*(msgArg.msgArg));
}

- (void)dealloc
{
    if (self.shouldDeleteHandleOnDealloc) {
        AboutIcon *pArg = static_cast<AboutIcon*>(self.handle);
        delete pArg;
        self.handle = nil;
    }
}


@end