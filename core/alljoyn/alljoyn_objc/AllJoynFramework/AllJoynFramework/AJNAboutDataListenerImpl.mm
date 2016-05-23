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

#import "AJNAboutDataListenerImpl.h"
#import "AJNMessageArgument.h"
#import "AJNHandle.h"

using namespace ajn;

@interface AJNMessageArgument(Private)

@property (nonatomic, readonly) MsgArg *msgArg;

@end

const char * AJNAboutDataListenerImpl::AJN_ABOUT_DATA_LISTENER_DISPATCH_QUEUE_NAME = "org.alljoyn.about-data-listener.queue";

/**
 * Constructor for the AJN session port listener implementation.
 *
 * @param aDelegate         Objective C delegate called when one of the below virtual functions is called.

*/

AJNAboutDataListenerImpl::AJNAboutDataListenerImpl(id<AJNAboutDataListener> aDelegate) :  m_delegate(aDelegate)
{
    
}

/**
 * Virtual destructor for derivable class.
 */
AJNAboutDataListenerImpl::~AJNAboutDataListenerImpl()
{
    m_delegate = nil;
}


/**
 * Creating the MsgArg that is returned when a user calls
 * org.alljoyn.About.GetAboutData. The returned MsgArg must contain the
 * AboutData dictionary for the Language specified.
 *
 * The MsgArg will contain the signature `a{sv}`.
 *
 * TODO add more documentation for the Key/Value pair requirements here.
 *
 * @param[out] msgArg a the dictionary containing all of the AboutData fields for
 *                    the specified language.  If language is not specified the default
 *                    language will be returned
 * @param[in] language IETF language tags specified by RFC 5646 if the string
 *                     is NULL or an empty string the MsgArg for the default
 *                     language will be returned
 *
 * @return ER_OK on successful
 */
QStatus AJNAboutDataListenerImpl::GetAboutData(MsgArg* msgArg, const char* language)
{
    QStatus status = ER_OK;
    NSMutableDictionary *aboutData;
    AJNMessageArgument *ajnMsgArgContent;
    NSString *nsLang;
    int i = 0;
    size_t numEntries;
    MsgArg* dictEntries;
    
    if (language != nil) {
        nsLang = [NSString stringWithCString:language encoding:NSUTF8StringEncoding ];
    } else {
        nsLang = nil;
    }
    if ([m_delegate respondsToSelector:@selector(getAboutDataForLanguage:usingDictionary:)]) {
        status = [m_delegate getAboutDataForLanguage:nsLang usingDictionary:&aboutData];
        numEntries = aboutData.count;
        dictEntries = new MsgArg[numEntries];
        for (NSString *key in aboutData) {
            ajnMsgArgContent = aboutData[key];
            dictEntries[i].Set("{sv}",[key UTF8String],ajnMsgArgContent.msgArg);
            i++;
        }
        msgArg->Set("a{sv}", numEntries, dictEntries);
        msgArg->Stabilize();
    } else {
        status = ER_FAIL;
    }
    return status;
}

QStatus AJNAboutDataListenerImpl::GetAnnouncedAboutData(MsgArg* msgArg)
{
    QStatus status = ER_OK;
    NSMutableDictionary *aboutData;
    AJNMessageArgument *ajnMsgArgContent;
    int i = 0;
    size_t numEntries;
    MsgArg* dictEntries;

    if([m_delegate respondsToSelector:@selector(getDefaultAnnounceData:)]) {
        status = [m_delegate getDefaultAnnounceData:&aboutData];
        numEntries = aboutData.count;
        dictEntries = new MsgArg[numEntries];
        for (NSString *key in aboutData) {
            ajnMsgArgContent = aboutData[key];
            dictEntries[i].Set("{sv}",[key UTF8String],ajnMsgArgContent.msgArg);
            i++;
        }
        msgArg->Set("a{sv}", numEntries, dictEntries);
        msgArg->Stabilize();
    } else {
        status = ER_FAIL;
    }
    return status;
}

