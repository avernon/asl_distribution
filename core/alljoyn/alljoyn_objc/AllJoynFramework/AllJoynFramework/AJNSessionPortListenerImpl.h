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
#import <alljoyn/SessionPortListener.h>
#import <alljoyn/TransportMask.h>
#import "AJNBusListener.h"
#import "AJNBusAttachment.h"

class AJNSessionPortListenerImpl : public ajn::SessionPortListener {
  protected:
    static const char* AJN_SESSION_PORT_LISTENER_DISPATCH_QUEUE_NAME;
    __weak AJNBusAttachment* busAttachment;

    /**
     * Objective C delegate called when one of the below virtual functions
     * is called.
     */
    __weak id<AJNSessionPortListener> m_delegate;

  public:


    /**
     * Constructor for the AJN session port listener implementation.
     *
     * @param aBusAttachment    Objective C bus attachment wrapper object.
     * @param aDelegate         Objective C delegate called when one of the below virtual functions is called.
     */
    AJNSessionPortListenerImpl(AJNBusAttachment* aBusAttachment, id<AJNSessionPortListener> aDelegate);

    /**
     * Virtual destructor for derivable class.
     */
    virtual ~AJNSessionPortListenerImpl();

    /**
     * Accept or reject an incoming JoinSession request. The session does not exist until this
     * after this function returns.
     *
     * This callback is only used by session creators. Therefore it is only called on listeners
     * passed to BusAttachment::BindSessionPort.
     *
     * @param sessionPort    Session port that was joined.
     * @param joiner         Unique name of potential joiner.
     * @param opts           Session options requested by the joiner.
     * @return   Return true if JoinSession request is accepted. false if rejected.
     */
    virtual bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts);

    /**
     * Called by the bus when a session has been successfully joined. The session is now fully up.
     *
     * This callback is only used by session creators. Therefore it is only called on listeners
     * passed to BusAttachment::BindSessionPort.
     *
     * @param sessionPort    Session port that was joined.
     * @param id             Id of session.
     * @param joiner         Unique name of the joiner.
     */
    virtual void SessionJoined(ajn::SessionPort sessionPort, ajn::SessionId sessionId, const char* joiner);


    /**
     * Accessor for Objective-C delegate.
     *
     * return delegate         The Objective-C delegate called to handle the above event methods.
     */
    id<AJNSessionPortListener> getDelegate();

    /**
     * Mutator for Objective-C delegate.
     *
     * @param delegate    The Objective-C delegate called to handle the above event methods.
     */
    void setDelegate(id<AJNSessionPortListener> delegate);
};

inline id<AJNSessionPortListener> AJNSessionPortListenerImpl::getDelegate()
{
    return m_delegate;
}

inline void AJNSessionPortListenerImpl::setDelegate(id<AJNSessionPortListener> delegate)
{
    m_delegate = delegate;
}
