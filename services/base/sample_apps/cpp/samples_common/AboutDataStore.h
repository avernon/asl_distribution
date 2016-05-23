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
#ifndef ABOUT_DATA_STORE_H_
#define ABOUT_DATA_STORE_H_

#include <stdio.h>
#include <iostream>
#include <alljoyn/config/AboutDataStoreInterface.h>

/**
 * class AboutDataStore
 * Property store implementation
 */
class AboutDataStore : public AboutDataStoreInterface {

  public:
    /**
     * AboutDataStore - constructor
     * @param factoryConfigFile
     * @param configFile
     */
    AboutDataStore(const char* factoryConfigFile, const char* configFile);

    /**
     * SetOBCFG
     */
    void SetOBCFG();

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
     * virtual Destructor
     */
    virtual ~AboutDataStore();

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
    void write();

    /**
     * method Initialize
     */
    void Initialize(qcc::String deviceId = qcc::String(), qcc::String appId = qcc::String());

  private:
    bool m_IsInitialized;
    qcc::String m_configFileName;
    qcc::String m_factoryConfigFileName;

    qcc::String ToXml(AboutData* aboutData);

    QStatus IsLanguageSupported(const char* languageTag);
};

#endif /* ABOUT_DATA_STORE_H_ */
