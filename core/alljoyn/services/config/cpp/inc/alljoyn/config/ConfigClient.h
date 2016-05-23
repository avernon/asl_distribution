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

#ifndef CONFIGCLIENT_H_
#define CONFIGCLIENT_H_

#include <map>
#include <vector>
#include <string>
#include <stdint.h>

#include <alljoyn/Message.h>
#include <alljoyn/BusListener.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/MsgArg.h>
#include <qcc/String.h>

namespace ajn {
namespace services {
/**
 * ConfigClient is a helper class used by an AllJoyn IoE client application to communicate with ConfigService that implements the org.alljoyn.Config
 * exposing the following methods:
 *  FactoryReset
 *  Restart
 *  SetPasscode
 *  GetConfigurations
 *  UpdateConfigurations
 *  ResetConfigurations
 *  GetVersion
 *
 */
class ConfigClient {
  public:
    /**
     *	Configurations data structure  where  key is of type qcc::String  and value is of type ajn::MsgArg
     */
    typedef std::map<qcc::String, ajn::MsgArg> Configurations;


    /**
     * Construct an ConfigClient
     * @param[in] bus is a reference to BusAttachment
     */
    ConfigClient(ajn::BusAttachment& bus);

    /**
     * Destruct ConfigClient
     */
    ~ConfigClient() { }
    /**
     * FactoryReset Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param sessionId the session received  after joining alljoyn session
     * @return status.
     */
    QStatus FactoryReset(const char* busName, ajn::SessionId sessionId = 0);
    /**
     * Restart Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus Restart(const char* busName, ajn::SessionId sessionId = 0);
    /**
     * SetPasscode Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param daemonRealm is the new DaemonRealm .
     * @param newPasscodeSize is the new pass code size.
     * @param newPasscode is the new pass code .
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus SetPasscode(const char* busName, const char* daemonRealm, size_t newPasscodeSize, const uint8_t* newPasscode, ajn::SessionId sessionId = 0);
    /**
     * GetConfigurations Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param languageTag is the language used to pull the data by.
     * @param configs reference to Configurations filled by the function
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus GetConfigurations(const char* busName, const char* languageTag, Configurations& configs, ajn::SessionId sessionId = 0);
    /**
     * UpdateConfigurations Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param languageTag is the language used to update the data by
     * @param configs reference to Configurations to be used by the function.
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus UpdateConfigurations(const char* busName, const char* languageTag, const Configurations& configs, ajn::SessionId sessionId = 0);
    /**
     * DeleteConfigurations Remote method call
     * @param busName Unique or well-known name of AllJoyn bus
     * @param languageTag languageTag is the language used to update the data by
     * @param configNames  reference to Configurations to be used by the function.
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus ResetConfigurations(const char* busName, const char* languageTag, const std::vector<qcc::String>& configNames, ajn::SessionId sessionId = 0);

    /**
     *
     * @param busName Unique or well-known name of AllJoyn bus
     * @param version reference to be filled by the function
     * @param sessionId the session received  after joining alljoyn session
     * @return status
     */
    QStatus GetVersion(const char* busName, int& version, ajn::SessionId sessionId = 0);

  private:
    /**
     * pointer to BusAttachment
     */
    ajn::BusAttachment* m_BusAttachment;
};

}
}

#endif /* CONFIGCLIENT_H_ */
