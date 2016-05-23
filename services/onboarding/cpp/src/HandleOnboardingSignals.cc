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

#include "HandleOnboardingSignals.h"
#include "alljoyn/onboarding/LogModule.h"

using namespace ajn::services;


HandleOnboardingSignals::HandleOnboardingSignals(BusAttachment* bus, OnboardingClientListener* listener) :
    m_bus(bus), m_userListener(listener)
{
    QCC_DbgTrace(("ConnectionResultHandler::%s", __FUNCTION__));
}

HandleOnboardingSignals::~HandleOnboardingSignals()
{
    m_asyncTaskQueue->Stop();
    delete m_asyncTaskQueue;
}

QStatus HandleOnboardingSignals::RegisterConnectionResultSignalHandler(const ajn::InterfaceDescription::Member* connectionResultSignalMethod)
{
    // the incoming signals are placed in a queue so that the alljoyn thread
    // is released right away
    m_asyncTaskQueue = new AsyncTaskQueue(this);
    m_asyncTaskQueue->Start();

    QStatus status = m_bus->RegisterSignalHandler(this,
                                                  static_cast<MessageReceiver::SignalHandler>(&HandleOnboardingSignals::ConnectionResultSignal),
                                                  connectionResultSignalMethod,
                                                  0);

    return status;
}


QStatus HandleOnboardingSignals::UnregisterConnectionResultSignalHandler(const ajn::InterfaceDescription::Member* connectionResultSignalMethod)
{
    QStatus status = m_bus->UnregisterSignalHandler(this,
                                                    static_cast<MessageReceiver::SignalHandler>(&HandleOnboardingSignals::ConnectionResultSignal),
                                                    connectionResultSignalMethod,
                                                    NULL);

    m_asyncTaskQueue->Stop();
    delete m_asyncTaskQueue;

    return status;
}


void HandleOnboardingSignals::ConnectionResultSignal(const ajn::InterfaceDescription::Member* member,
                                                     const char* srcPath, Message& message)
{

    QCC_DbgTrace(("ConnectionResultHandler::%s", __FUNCTION__));

    QCC_DbgPrintf(("received signal interface=%s method=%s", message->GetInterface(), message->GetMemberName()));

    if (strcmp(message->GetInterface(), "org.alljoyn.Onboarding") != 0 || strcmp(message->GetMemberName(), "ConnectionResult") != 0) {
        QCC_DbgPrintf(("This is not the signal we are looking for"));
        return;
    }

    SignalMesssage* originalMessage = new SignalMesssage(message);
    m_asyncTaskQueue->Enqueue(originalMessage);
}

///////////////// AsyncTask Methods ////////////////////////
void HandleOnboardingSignals::OnEmptyQueue()
{
}

void HandleOnboardingSignals::OnTask(TaskData const* taskdata)
{
    SignalMesssage const* wrappedMessage = static_cast<SignalMesssage const*>(taskdata);
    Message* message = (Message*) &wrappedMessage->m_signalMessage;

    const ajn::MsgArg* args = 0;
    size_t numArgs = 0;
    QStatus status;

    short connectionResultCode;
    char*  connectionResultMessage;

    message->unwrap()->GetArgs(numArgs, args);

    if (numArgs == 1) {
        status = args[0].Get("(ns)", &connectionResultCode, &connectionResultMessage);
    } else {
        status = ER_BAD_ARG_COUNT;
    }

    if (status != ER_OK) {
        QCC_DbgPrintf(("unmarshalling ConnectionResult Signal, failed"));
        return;
    }

    qcc::String resultMessage(connectionResultMessage);
    m_userListener->ConnectionResultSignalReceived(connectionResultCode, resultMessage);
}

