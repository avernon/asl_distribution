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

#include <nio/Proactor.h>
#include <nio/TCPTransport.h>
#include <nio/Buffer.h>
#include <nio/Endpoint.h>
#include <nio/TimerEvent.h>

#include <alljoyn/Init.h>

#include <signal.h>

#define MSG_SIZE 8

static nio::Proactor proactor(1);

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    proactor.Stop();
}

void ReadCB(nio::TransportBase::EndpointPtr, std::shared_ptr<nio::Buffer> buf, QStatus status)
{
    if (status == ER_OK) {
        printf("Received %u bytes\n", buf->m_length);
        /*
           std::shared_ptr<nio::Buffer> buffer = std::make_shared<nio::Buffer>(new uint8_t[MSG_SIZE], MSG_SIZE, MSG_SIZE);

           auto cb = [] (nio::TransportBase::EndpointPtr, std::shared_ptr<nio::Buffer> buffer, QStatus status) {
            printf("%s: Send complete; %u bytes\n", QCC_StatusText(status), buffer->GetCapacity());
           };
           status = ep->Send(buffer, cb);
           printf("ep->Send: %s\n", QCC_StatusText(status));
         */

        // set up to receive the next message
        //std::shared_ptr<nio::Buffer> inbuffer = std::make_shared<nio::Buffer>(new uint8_t[MSG_SIZE], 0, MSG_SIZE);
        //status = ep->Recv(inbuffer, &Received);
        //printf("ep->Recv: %s\n", QCC_StatusText(status));
    } else {
        printf("Recieved: %s\n", QCC_StatusText(status));
    }
}

static std::shared_ptr<nio::TimerEvent> timer_event;

void TimerCallback(nio::TransportBase::EndpointPtr ep)
{
    // do a send and prepare to receive!

    std::shared_ptr<nio::Buffer> inbuffer = std::make_shared<nio::Buffer>(new uint8_t[8], 0, 8);
    QStatus status = ep->Recv(inbuffer, &ReadCB);
    if (status != ER_OK) {
        proactor.Cancel(timer_event);
        timer_event.reset();
        return;
    }
    printf("ep->Recv: %s\n", QCC_StatusText(status));


    std::shared_ptr<nio::Buffer> buffer = std::make_shared<nio::Buffer>(new uint8_t[MSG_SIZE], MSG_SIZE, MSG_SIZE);
    for (uint32_t i = 0; i < MSG_SIZE; ++i) {
        buffer->m_buffer[i] = i;
    }

    auto cb = [] (nio::TransportBase::EndpointPtr, std::shared_ptr<nio::Buffer> buffer, QStatus status) {
                  printf("%s: Send complete; %u bytes\n", QCC_StatusText(status), buffer->GetCapacity());
              };
    status = ep->Send(buffer, cb);
    if (status != ER_OK) {
        proactor.Cancel(timer_event);
        timer_event.reset();
        return;
    }
    printf("ep->Send: %s\n", QCC_StatusText(status));
}


void ConnectedCB(nio::TransportBase::EndpointPtr ep, QStatus status)
{
    if (status == ER_OK) {
        printf("Connected to %s\n", ep->ToString().c_str());
        auto timercb = [ep] () {
                           TimerCallback(ep);
                       };

        timer_event = std::make_shared<nio::TimerEvent>(std::chrono::milliseconds(1000), timercb, std::chrono::milliseconds(1000));
        proactor.Register(timer_event);
    } else {
        printf("ConnectedCB: %s\n", QCC_StatusText(status));
    }
}

int CDECL_CALL main(int argc, char** argv)
{
    QCC_UNUSED(argc);
    QCC_UNUSED(argv);

    if (AllJoynInit() != ER_OK) {
        return 1;
    }
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }

    signal(SIGINT, SigIntHandler);
    nio::TCPTransport transport(proactor);
    transport.Connect("tcp:addr=127.0.0.1,port=10000", &ConnectedCB);



    proactor.Run();

    AllJoynRouterShutdown();
    AllJoynShutdown();
}
