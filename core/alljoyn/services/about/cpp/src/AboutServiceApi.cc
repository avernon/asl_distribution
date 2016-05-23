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

#include <alljoyn/about/AboutServiceApi.h>

using namespace ajn;
using namespace services;

AboutServiceApi* AboutServiceApi::m_instance = NULL;
BusAttachment* AboutServiceApi::m_BusAttachment = NULL;
PropertyStore* AboutServiceApi::m_PropertyStore = NULL;

AboutServiceApi::AboutServiceApi(ajn::BusAttachment& bus, PropertyStore& store) :
    AboutService(bus, store) {

}

AboutServiceApi::~AboutServiceApi() {

}

AboutServiceApi* AboutServiceApi::getInstance() {
    if (!m_BusAttachment || !m_PropertyStore) {
        return NULL;
    }
    if (!m_instance) {
        m_instance = new AboutServiceApi(*m_BusAttachment, *m_PropertyStore);
    }
    return m_instance;
}

void AboutServiceApi::Init(ajn::BusAttachment& bus, PropertyStore& store) {
    m_BusAttachment = &bus;
    m_PropertyStore = &store;
}

void AboutServiceApi::DestroyInstance() {
    if (m_instance) {
        delete m_instance;
        m_instance = NULL;
    }
}
