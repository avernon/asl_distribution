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

#include <alljoyn/Init.h>

#include <signal.h>

#define MSG_SIZE 8


static void ReadCB(nio::TransportBase::EndpointPtr ep, std::shared_ptr<nio::Buffer> buffer, QStatus status)
{
    printf("%s: Received %u bytes on handle \n", QCC_StatusText(status), buffer->GetLength());

    if (status == ER_OK) {

        printf("Received %u bytes from %s; sending back!\n", buffer->GetLength(), ep->ToString().c_str());
        // compose a new message to go OUT
        std::shared_ptr<nio::Buffer> out_buffer = std::make_shared<nio::Buffer>(new uint8_t[MSG_SIZE], MSG_SIZE, MSG_SIZE);
        ::memcpy(out_buffer->m_buffer, buffer->m_buffer, MSG_SIZE);

        auto cb = [] (nio::TransportBase::EndpointPtr, std::shared_ptr<nio::Buffer> buffer, QStatus status) {
                      printf("%s: Send complete; %u bytes\n", QCC_StatusText(status), buffer->GetCapacity());
                  };
        status = ep->Send(buffer, cb);


        // now continue receiving messages
        std::shared_ptr<nio::Buffer> inbuffer = std::make_shared<nio::Buffer>(new uint8_t[MSG_SIZE], 0, MSG_SIZE);
        status = ep->Recv(inbuffer, &ReadCB);
        printf("ep->Recv: %s\n", QCC_StatusText(status));
    } else {
        printf("EP Disconnected: %s\n", QCC_StatusText(status));
    }
}

static bool AcceptCB(nio::TransportBase::EndpointPtr ep)
{
    printf("Accepted incoming connection from %s\n", ep->ToString().c_str());
    QStatus status;

    // send something!
/*
    uint8_t* buf = new uint8_t[6];
    memset(buf, 0, 6);
    memcpy(buf, "HELLO", 6);

    std::shared_ptr<nio::Buffer> buffer = std::make_shared<nio::Buffer>(buf, 6, 6);
    printf("Sending %p\n", buffer.get());

    auto cb = [] (nio::TransportBase::EndpointPtr, std::shared_ptr<nio::Buffer> buffer, QStatus status) {
        printf("%s: Send complete; %u bytes\n", QCC_StatusText(status), buffer->GetCapacity());
    };
    status = ep->Send(buffer, cb);
    printf("Send: %s\n", QCC_StatusText(status));
 */

    // start receiving...
    std::shared_ptr<nio::Buffer> inbuffer = std::make_shared<nio::Buffer>(new uint8_t[8], 0, 8);
    status = ep->Recv(inbuffer, &ReadCB);
    printf("ep->Recv: %s\n", QCC_StatusText(status));

    return true;
}

static nio::Proactor proactor(1);

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    proactor.Stop();
}

int CDECL_CALL main(int argc, char** argv)
{
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }

    signal(SIGINT, SigIntHandler);

    nio::TCPTransport transport(proactor);

    std::string spec = argc > 1 ? argv[1] : "tcp:addr=127.0.0.1,port=10000";
    transport.Listen(spec, &AcceptCB);


    proactor.Run();
    printf("Finished!\n");

    AllJoynRouterShutdown();
    AllJoynShutdown();
}


