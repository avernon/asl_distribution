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
#import <alljoyn/AboutListener.h>
#import <alljoyn/TransportMask.h>
#import "AJNBusListener.h"
#import "AJNBusAttachment.h"
#import "AJNAboutListener.h"

class AJNAboutListenerImpl : public ajn::AboutListener {
protected:
    static const char* AJN_ABOUT_LISTENER_DISPATCH_QUEUE_NAME;
    __weak AJNBusAttachment* busAttachment;
    
    /**
     * Objective C delegate called when one of the below virtual functions
     * is called.
     */
    __weak id<AJNAboutListener> m_delegate;
    
public:
    
    /**
     * Constructor for the AJNAboutListener implementation.
     *
     * @param aBusAttachment    Objective C bus attachment wrapper object.
     * @param aDelegate         Objective C delegate called when one of the below virtual functions is called.
     */
    AJNAboutListenerImpl(AJNBusAttachment* aBusAttachment, id<AJNAboutListener> aDelegate);
    
    /**
     * Virtual destructor for derivable class.
     */
    virtual ~AJNAboutListenerImpl();
    
    virtual void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg);
    
    /**
     * Accessor for Objective-C delegate.
     *
     * return delegate         The Objective-C delegate called to handle the above event methods.
     */
    id<AJNAboutListener> getDelegate();
    
    /**
     * Mutator for Objective-C delegate.
     *
     * @param delegate    The Objective-C delegate called to handle the above event methods.
     */
    void setDelegate(id<AJNAboutListener> delegate);
};

inline id<AJNAboutListener> AJNAboutListenerImpl::getDelegate()
{
    return m_delegate;
}

inline void AJNAboutListenerImpl::setDelegate(id<AJNAboutListener> delegate)
{
    m_delegate = delegate;
}
