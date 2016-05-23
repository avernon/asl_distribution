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

#include "AboutClientAnnounceHandler.h"
#include <alljoyn/about/AboutClient.h>
#include <iostream>
#include <iomanip>

using namespace ajn;
using namespace services;

AboutClientAnnounceHandler::AboutClientAnnounceHandler(AnnounceHandlerCallback callback) :
    AnnounceHandler(), m_Callback(callback)
{

}

AboutClientAnnounceHandler::~AboutClientAnnounceHandler()
{
}

void AboutClientAnnounceHandler::Announce(unsigned short version, unsigned short port, const char* busName, const ObjectDescriptions& objectDescs,
                                          const AboutData& aboutData)
{
    std::cout << std::endl << std::endl << "*********************************************************************************"
              << std::endl;
    std::cout << "version   " << version << std::endl;
    std::cout << "port      " << port << std::endl;
    std::cout << "busName   " << busName << std::endl;
    std::cout << "ObjectDescriptions :" << std::endl;
    for (AboutClient::ObjectDescriptions::const_iterator it = objectDescs.begin(); it != objectDescs.end(); ++it) {
        qcc::String key = it->first;
        std::vector<qcc::String> vector = it->second;
        std::cout << "Object path = " << key.c_str() << std::endl;
        for (std::vector<qcc::String>::const_iterator itv = vector.begin(); itv != vector.end(); ++itv) {
            std::cout << "\tInterface = " << itv->c_str() << std::endl;
        }
    }

    std::cout << "AnnounceData :" << std::endl;
    for (AboutClient::AboutData::const_iterator it = aboutData.begin(); it != aboutData.end(); ++it) {
        qcc::String key = it->first;
        ajn::MsgArg value = it->second;
        if (value.typeId == ALLJOYN_STRING) {
            std::cout << "Key name = "  << std::setfill(' ') << std::setw(20) << std::left << key.c_str()
                      << " value = " << value.v_string.str << std::endl;
        } else if (value.typeId == ALLJOYN_BYTE_ARRAY) {
            std::cout << "Key name = "  << std::setfill(' ') << std::setw(20) << std::left << key.c_str()
                      << " value = " << std::hex << std::uppercase;
            uint8_t* AppIdBuffer;
            size_t numElements;
            value.Get("ay", &numElements, &AppIdBuffer);
            for (size_t i = 0; i < numElements; i++) {
                std::cout << (unsigned int)AppIdBuffer[i];
            }
            std::cout << std::nouppercase << std::dec << std::endl;
        }
    }

    std::cout << "*********************************************************************************" << std::endl << std::endl;

    if (m_Callback) {
        std::cout << "Calling AnnounceHandler Callback" << std::endl;
        m_Callback(busName, port);
    }
}

