/**
 * @file
 * Wrapper to encapsulate the AboutService with a singelton.
 */
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

#ifndef ABOUT_SERVICE_API_H
#define ABOUT_SERVICE_API_H

#include <qcc/Log.h>
#include <alljoyn/version.h>
#include <alljoyn/about/AboutService.h>
#include <alljoyn/about/PropertyStore.h>

namespace ajn {
namespace services {

/**
 * AboutServiceApi  is wrapper class that encapsulates the AboutService with a Singelton.
 *
 * @deprecated The AboutServiceApi class has been deprecated please see the
 * AboutObj class. There is no direct equivalent class to the AboutServiceApi
 * since the use of a singelton has been completely removed.
 */
class AboutServiceApi : public AboutService {

  public:

    /**
     * GetInstance
     *
     * @deprecated The AboutServiceApi class has been deprecated please see the
     * AboutObj class.
     *
     * @return AboutServiceApi created only once.
     */
    QCC_DEPRECATED(static AboutServiceApi * getInstance());

    /**
     * Init with  BusAttachment and PropertyStore only once.
     * After the first Init you can call getInstance to receive a proper
     * instance of the class
     *
     * @deprecated The AboutServiceApi::Init function has been deprecated please see the
     * AboutObj class.
     *
     * @param bus
     * @param store
     */
    QCC_DEPRECATED(static void Init(ajn::BusAttachment & bus, PropertyStore & store));

    /**
     * Destroy the instance only once after finished
     *
     * @deprecated The AboutServiceApi::DestroyInstance function has been
     * deprecated please see the AboutObj class.
     */
    QCC_DEPRECATED(static void DestroyInstance());

  private:
    /**
     * Constructor
     * @param bus
     * @param store
     */
    AboutServiceApi(ajn::BusAttachment& bus, PropertyStore& store);
    /**
     * Desctructor
     */
    virtual ~AboutServiceApi();
    /**
     *  pointer to AboutServiceApi
     */
    static AboutServiceApi* m_instance;
    /**
     * pointer to BusAttachment
     */
    static BusAttachment* m_BusAttachment;
    /**
     * pointer to PropertyStore
     */
    static PropertyStore* m_PropertyStore;

};

}
}
#endif /* ABOUT_SERVICE_API_H */
