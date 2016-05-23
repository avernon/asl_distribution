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

#ifndef ABOUT_DATA_API_H
#define ABOUT_DATA_API_H

#include <qcc/Log.h>
#include <alljoyn/version.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/AboutData.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4100. Function doesnt use all passed in parameters */
#pragma warning(push)
#pragma warning(disable: 4100)
#endif


namespace ajn {
namespace services {

/**
 *      AboutObjApi is wrapper class that encapsulates the AboutObj with a Singleton.
 */
class AboutObjApi {

  public:

    /**
     * GetInstance
     * @return AboutDataApi created only once.
     */
    static AboutObjApi* getInstance();
    /**
     * Init with  BusAttachment and AboutData only once.
     * After the first Init you can call getInstance to receive a proper instance of the class
     * @param bus
     * @param aboutData
     * @param aboutObj
     */
    static void Init(ajn::BusAttachment* bus, AboutData* aboutData, AboutObj* aboutObj);
    /**
     * Destroy the instance only once after finished
     */
    static void DestroyInstance();
    /**
     * SetPort - set the port for the announce
     * @param sessionPort
     */
    void SetPort(SessionPort sessionPort);
    /**
     * This is used to send the Announce signal.
     */
    QStatus Announce();

  private:
    /**
     * Constructor
     */
    AboutObjApi();
    /**
     * Desctructor
     */
    virtual ~AboutObjApi();
    /**
     *  pointer to AboutDataApi
     */
    static AboutObjApi* m_instance;
    /**
     * pointer to BusAttachment
     */
    static BusAttachment* m_BusAttachment;
    /**
     * pointer to AboutData
     */
    static AboutData* m_AboutData;
    /**
     * pointer to AboutObj
     */
    static AboutObj* m_AboutObj;
    /**
     * sesstion port for the about announcement
     */
    static SessionPort m_sessionPort;

};

}
}
#endif /* ABOUT_SERVICE_API_H */
