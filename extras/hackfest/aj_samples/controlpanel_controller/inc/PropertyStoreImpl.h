/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
#ifndef PROPERTYSTOREIMPL_H_
#define PROPERTYSTOREIMPL_H_

#include <stdio.h>
#include <iostream>

#include <alljoyn/about/AboutServiceApi.h>
#include <alljoyn/about/AboutPropertyStoreImpl.h>


class PropertyStoreImpl : public ajn::services::AboutPropertyStoreImpl {

  public:
    PropertyStoreImpl(const char* factoryConfigFile, const char* configFile);

    void FactoryReset();

    const qcc::String& GetConfigFileName();

    virtual ~PropertyStoreImpl();

    virtual QStatus ReadAll(const char* languageTag, Filter filter, ajn::MsgArg& all);

    virtual QStatus Update(const char* name, const char* languageTag, const ajn::MsgArg* value);

    virtual QStatus Delete(const char* name, const char* languageTag);

    void Initialize();

  private:

    ajn::services::PropertyMap m_PropertiesReadOnly;

    bool m_IsInitialized;

    qcc::String m_configFileName;

    qcc::String m_factoryConfigFileName;

    bool persistUpdate(const char* key, const char* value);

    ajn::services::PropertyStoreKey getPropertyStoreKeyFromName(qcc::String const& propertyStoreName);
};

#endif /* PROPERTYSTOREIMPL_H_ */
