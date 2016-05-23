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

#ifndef CONFIGSERVICELISTENERIMPL_H_
#define CONFIGSERVICELISTENERIMPL_H_

#include <alljoyn/config/ConfigService.h>
#include <AboutDataStore.h>
#include <CommonBusListener.h>

/**
 * ConfigServiceListenerImpl
 */
class ConfigServiceListenerImpl : public ajn::services::ConfigService::Listener {
  public:
    /**
     * ConfigServiceListenerImpl
     * @param store
     * @param bus
     * @param busListener
     */
    ConfigServiceListenerImpl(AboutDataStore& store, ajn::BusAttachment& bus, CommonBusListener& busListener);

    /**
     * Method restart
     * @return
     */
    virtual QStatus Restart();

    /**
     * Method FactoryReset
     * @return
     */
    virtual QStatus FactoryReset();

    /**
     * SetPassphrase
     * @param daemonRealm
     * @param passcodeSize
     * @param passcode
     * @param sessionId
     * @return
     */
    virtual QStatus SetPassphrase(const char* daemonRealm, size_t passcodeSize, const char* passcode, ajn::SessionId sessionId);

    /**
     * destructor
     */
    virtual ~ConfigServiceListenerImpl();

  private:

    AboutDataStore* m_AboutDataStore;

    ajn::BusAttachment* m_Bus;

    CommonBusListener* m_BusListener;

    void PersistPassword(const char* daemonRealm, const char* passcode);
};

#endif /* CONFIGSERVICELISTENERIMPL_H_ */
