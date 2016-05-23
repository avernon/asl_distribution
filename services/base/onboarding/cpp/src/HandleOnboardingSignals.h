/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#ifndef HANDLEONBOARDINGSIGNALS_H_
#define HANDLEONBOARDINGSIGNALS_H_


#include <alljoyn/BusAttachment.h>
#include <alljoyn/onboarding/OnboardingClientListener.h>
#include <alljoyn/services_common/AsyncTaskQueue.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4701/4703. Potentially uninitialized local variable */
#pragma warning(push)
#pragma warning(disable: 4701)
#pragma warning(disable: 4703)
#endif


/**
 * HandleOnboardingSignals
 *
 * Class for Onboarding Client to handle incoming signals
 */
namespace ajn {
namespace services {

/**
 * SignalMsg
 * A wrapper around the ajn:Messgae received in the signal.
 * This wrapper is needed to be able to use the AsyncTask Queue
 */
class SignalMesssage : public TaskData {
  public:
    /**
     * NotificationMsg constructor
     */
    SignalMesssage(const ajn::Message& message) :
        m_signalMessage(message)
    {
    }

    /**
     * NotificationMsg destructor
     */
    ~SignalMesssage()
    {
    }

    ajn::Message m_signalMessage;

};


class HandleOnboardingSignals : public ajn::MessageReceiver, public AsyncTask {

  public:

    /**
     * Constructor
     */
    HandleOnboardingSignals(BusAttachment* bus, OnboardingClientListener* listener);

    /**
     * Destructor
     */
    ~HandleOnboardingSignals();

    /**
     * Register to handle a signal
     */
    QStatus RegisterConnectionResultSignalHandler(const ajn::InterfaceDescription::Member* connectionResultSignalMethod);

    /**
     * Unregister to handle a signal
     */
    QStatus UnregisterConnectionResultSignalHandler(const ajn::InterfaceDescription::Member* connectionResultSignalMethod);


    ///////// MessageReceiver method //////
    /**
     * ConnectionResultSignal is a callback registered to receive AllJoyn Signal.
     * @param[in] member
     * @param[in] srcPath
     * @param[in] message
     */
    void ConnectionResultSignal(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& message);

    ////// AsyncTask methods /////////////

    /**
     * callback to handle the case of empty message queue.
     */
    void OnEmptyQueue();

    /**
     * callback to handle the case of new message
     * @param taskdata - object to handle
     */
    void OnTask(TaskData const* taskdata);


  private:

    /**
     * a pointer to the users callback listener
     */
    BusAttachment* m_bus;
    OnboardingClientListener* m_userListener;
    AsyncTaskQueue* m_asyncTaskQueue;

    /**
     * Copy constructor of HandleOnboardingSignals - private. HandleOnboardingSignals is not copy-able
     * @param handler - HandleOnboardingSignals to copy
     */
    HandleOnboardingSignals(const HandleOnboardingSignals& handler);

    /**
     * Assignment operator of HandleOnboardingSignals - private. HandleOnboardingSignals is not assignable
     * @param handler
     * @return HandleOnboardingSignals
     */
    HandleOnboardingSignals& operator=(const HandleOnboardingSignals& handler);
};



}
}
#endif /* HANDLEONBOARDINGSIGNALS_H_ */
