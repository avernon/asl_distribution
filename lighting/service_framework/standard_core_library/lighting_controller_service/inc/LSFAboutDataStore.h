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
#ifndef LSF_ABOUT_DATA_STORE_H_
#define LSF_ABOUT_DATA_STORE_H_

#include <stdio.h>
#include <iostream>
#include <alljoyn/config/AboutDataStoreInterface.h>
#include <alljoyn/AboutData.h>
#include <Rank.h>
#include <Mutex.h>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

/*
 * Pre-Declarations
 */
class ControllerService;

/**
 * class LSFAboutDataStore
 * Property store implementation
 */
class LSFAboutDataStore : public AboutDataStoreInterface {

  public:
    /**
     * LSFAboutDataStore - constructor
     * @param controllerService
     * @param factoryConfigFile
     * @param configFile
     */
    LSFAboutDataStore(ControllerService* controllerService, const char* factoryConfigFile, const char* configFile);

    /**
     * LSFAboutDataStore - constructor
     * @param factoryConfigFile
     * @param configFile
     * @param deviceID
     */
    LSFAboutDataStore(const char* factoryConfigFile, const char* configFile, const char* deviceId);

    /**
     * LSFAboutDataStore - destructor
     */
    ~LSFAboutDataStore();

    void SetControllerServicePtr(ControllerService* controllerService) {
        m_controllerService = controllerService;
    }

    /**
     * FactoryReset
     */
    void FactoryReset();

    /**
     * GetConfigFileName
     * @return qcc::String&
     */
    const qcc::String& GetConfigFileName();

    /**
     * virtual method ReadAll
     * @param languageTag
     * @param filter
     * @param all
     * @return QStatus
     */
    virtual QStatus ReadAll(const char* languageTag, DataPermission::Filter filter, ajn::MsgArg& all);

    /**
     * virtual method Update
     * @param name
     * @param languageTag
     * @param value
     * @return QStatus
     */
    virtual QStatus Update(const char* name, const char* languageTag, const ajn::MsgArg* value);

    /**
     * virtual method Delete
     * @param name
     * @param languageTag
     * @return QStatus
     */
    virtual QStatus Delete(const char* name, const char* languageTag);

    /**
     * Write about data store as an xml config file
     */
    QStatus write();

    /**
     * Used to retrieve the OEM default factory settings
     */
    friend void OEM_CS_PopulateDefaultProperties(AboutData* aboutData);

    /**
     * Is this controller is a leader?
     * @return boolean
     */
    bool IsLeader(void);

    /**
     * Set true if that controller is a leader
     * @param leader - true or false
     */
    void SetIsLeader(bool leader);

    /**
     * Set the rank of the current controller
     */
    void SetRank(Rank& rank);

  private:

    ControllerService* m_controllerService;
    bool m_IsInitialized;
    qcc::String m_configFileName;
    qcc::String m_factoryConfigFileName;

    Mutex editLock;

    QStatus Initialize(const char* factoryConfigFile, const char* configFile, const char* deviceId = NULL);

    QStatus IsLanguageSupported(const char* languageTag);

    /**
     * Initialize About Data
     */
    QStatus InitializeConfigSettings(void);

    /**
     * Initialize Factory Settings
     */
    QStatus InitializeFactorySettings(const char* passedInDeviceId = NULL);

    /**
     * Write about data store as an xml config file
     */
    void writeFactorySettings(AboutData* aboutData);

    /**
     * Write about data store as an xml config file
     */
    void writeConfigSettings(void);

    /**
     * Convert About Data to XML
     */
    qcc::String ToXml(AboutData* aboutData);
};

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif /* LSF_ABOUT_DATA_STORE_H_ */
